#pragma once
#include "iTaskRegistrar.h"
#include "iFeatureClient.h"
#include "FeatureCache.h"
#include "TaskTimer.h"
#include <math.h>
#include "CanMessage.h"
#include "PxRosTask.h"

#define REQUEST_TIMEOUT_MS			5000
#define ACL_REQUEST_TIMEOUT_MS		1000
#define ACM_COMMUNICATION_TIMEOUT	90000
#define TIMESTAMP_REQUEST_XID		0x0F03
#define TIMESTAMP_RESPONSE_XID		0x0F04
#define FEATURE_REQUEST_XID			0x0F05
#define FEATURE_RESPONSE_XID		0x0F06
#define FEATURE_CLIENT_INFO_2_ID	0xFFFB
#define FEATURE_CLIENT_INFO_1_ID	0xFFFC
#define NUM_BYTES_PER_FEATURE		4
#define NUM_BYTES_BEFORE_FEATURES	8

template<int featureCount> //Using template to know size of array at compile time
class FeatureClient : public iCanReceiver, public iFeatureClient
{
public:
	FeatureClient(const FeatureId_te featureList[featureCount],  uint8 source_address, uint32 eeprom_address) : 
		cache(eeprom_address, featureList), 
		RequestedFeatureCount(featureCount), 
		SourceAddress(source_address),
		Challenge(0), //Intializing this to 0 for now utnil we figure out what needs to be done with it
		TimestampRequestTimeout(REQUEST_TIMEOUT_MS, &SendTimestampRequestWrapper),
		FeatureRequestTimeout(REQUEST_TIMEOUT_MS, &SendFeatureRequestWrapper),
		AclRequestTimeout(ACL_REQUEST_TIMEOUT_MS, &SendAclRequestWrapper),
		AcmCommTimeout(ACM_COMMUNICATION_TIMEOUT, &CommTimeoutHandlerWrapper),
		ignitionOff(FALSE)
	{
		bool VinRequested = FALSE;
		uint8 VinIndex = 0;
		for(uint8 a = 0; a < featureCount; a++) //Copy over feature IDs from the list passed in to our Features member variable
		{
			Features[a] = featureList[a];
			if(featureList[a] == VEHICLE_IDENTIFICATION_NUMBER)
			{
				VinRequested = TRUE;
				VinIndex = a;
			}
		}

		if(VinRequested) // If the vin is requested move it to the end of the feature list
		{
			Features[VinIndex] = Features[featureCount - 1];
			Features[featureCount - 1] = VEHICLE_IDENTIFICATION_NUMBER;
		}

	}
	~FeatureClient(){};

	void initialize(iTaskRegistrar* reg)
	{
		FeatureManagerIsAlive = FALSE;
		FeatureManagerTimestamp = TIMESTAMP_ERROR;
		FeatureManagerSA = 0xFF;
		TimestampReceived = FALSE;
		FeaturesReceived = FALSE;
		VinReceived = FALSE;
		State = WAIT_FOR_ACM_ACL;
		TotalNumPackets = ceil((ceil((8 + 4 * RequestedFeatureCount) / 7) + 8 + 4 * RequestedFeatureCount) / 8);
		FeatureManagerClientInfo1_s.cacheTimestamp = TIMESTAMP_ERROR;
		FeatureManagerClientInfo1_s.fmcState = WAIT_FOR_ACM_ACL;
		FeatureManagerClientInfo1_s.errorState = NO_ERRORS;
		FeatureManagerClientInfo1_s.numFeaturesRequested = RequestedFeatureCount;
		FeatureManagerClientInfo2_s.acmTimestampReceived = TIMESTAMP_ERROR;
		FeatureManagerClientInfo2_s.numberOfFeaturesUpdated = 0;
		FeatureManagerClientInfo1_s.warningBitfield = 0;
		EepromCacheChangeStatus = FALSE;
		uint8 initValue;

		for(uint8 a = 0; a < 20; a++)
		{
			Vin[a] = '\0';
		}

		for(uint8 i = 0; i < RequestedFeatureCount; i++) //Initialize received features to FeatureIDs passed in list, with status and value set to default values
		{
			ReceivedFeatures[i].FeatureID = Features[i];
			ReceivedFeatures[i].FeatureStatus = FEATURE_NOT_AVAILABLE;
			ReceivedFeatures[i].FeatureValue = VALUE_ERROR;
		}

		FeatureManagerClientInfo1_s.warningBitfield = cache.InitOk(); //Returns 0 if initialization had no errors, else nonzero number
		FeatureManagerClientInfo1_s.warningBitfield |= RequestedFeatureCount != cache.GetNumFeaturesInEeprom() ? 8 : 0;
		FeatureManagerClientInfo1_s.warningBitfield |= !cache.GetFeaturesAreSame() ? 16 : 0;

		FeatureManagerClientInfo1_s.cacheTimestamp = cache.GetTimestamp(); //update with timestamp read from cache
		
		//Feature Manager ACL
		CanRequests[0].bus_u8 = CAN_J1939;
		CanRequests[0].IdMask_u32 = 0x00FF0000;
		CanRequests[0].IdSet_u32 = 0x00EE0000;
		CanRequests[0].isXformat_b = 1;
		CanRequests[0].dlc_u16 = 8;
		CanRequests[0].canAdmin_ps = 0;

		// EF00
		CanRequests[1].bus_u8 = CAN_J1939;
		CanRequests[1].IdMask_u32 = 0x00FFFF00;
		CanRequests[1].IdSet_u32 = 0x00EF0000 | ((uint16)SourceAddress << 8);
		CanRequests[1].isXformat_b = 1;
		CanRequests[1].dlc_u16 = TRANSPORT_PROTOCOL_MAX_DATA;
		CanRequests[1].canAdmin_ps = 0;

		reg->InitMailboxes(CanRequests, ARRAY_SIZE(CanRequests), this);		

		//Register timers for resending requests if no response is received within the timeout window
		reg->registerTimer(&TimestampRequestTimeout, this);
		reg->registerTimer(&FeatureRequestTimeout, this);
		reg->registerTimer(&AclRequestTimeout, this);
		reg->registerTimer(&AcmCommTimeout, this);

		// Get CanSend ptr from taskregistrar
		canSend_ptr = reg->getCanSend();

		//Send request for address claim
		SendAclRequest();
		AcmCommTimeout.start();
	};

	void canReceived(CanMessage* message)
	{
		uint8 functionCode = 0;
		uint16 manCode = 0;
		bool vinChanged = FALSE;
		uint8 numFeaturesReceived = 0;;
		
		switch( message->id_u32 & 0x00FF0000 )
		{
			case 0x00EE0000:
				functionCode = message->data_u8[5];
				manCode = (((uint16)message->data_u8[3] << 3) | ((message->data_u8[2] & 0xE0) >> 5));

				if(!FeatureManagerIsAlive)
				{
					if (functionCode == 54)//Communications Unit/Cellular
					{
						if (manCode == 102)// AGCO GmbH & Co.
						{
							AclRequestTimeout.stop(); // stop timer so we don't send another request
							AcmCommTimeout.stop();
							FeatureManagerSA = message->id_u32 & 0x000000FF;
							FeatureManagerIsAlive = TRUE;
						}
					}
				}
				break;
			case 0x00EF0000:
				if((message->id_u32 & 0x000000FF) == FeatureManagerSA) //SA is SA from Feature Managaer ACL
				{
					if((uint16)((message->data_u8[0] << 8) | message->data_u8[1]) == TIMESTAMP_RESPONSE_XID) //XID is the XID of the timestamp response message(Big Endian)
					{
						if((message->data_u8[14] | (message->data_u8[15] << 8) | (message->data_u8[16] << 16) | (message->data_u8[17] << 24)) != TIMESTAMP_ERROR)
						{
							TimestampRequestTimeout.stop(); // stop timer so we don't send another request
							AcmCommTimeout.stop();
							//Timestamp is Bytes 15..18(base 1)
							FeatureManagerTimestamp = (message->data_u8[14] | (message->data_u8[15] << 8) | (message->data_u8[16] << 16) | (message->data_u8[17] << 24));
							TimestampReceived = TRUE;
							FeatureManagerClientInfo2_s.acmTimestampReceived = FeatureManagerTimestamp; //Update with timestamp received from ACM
						}
					}
					else if((uint16)((message->data_u8[0] << 8) | message->data_u8[1]) == FEATURE_RESPONSE_XID) //XID is the XID of the feature response message(Big Endian)
					{
						FeatureRequestTimeout.stop(); //stop the timer so we don't send another request
						AcmCommTimeout.stop();
						//MAC Bytes 3..14(base1) FeatureManagerClientInfo1_s.warningBitfield |= 0x08; if there is an error with the challenge/MAC
						uint16 numOfFeatureResponses = message->data_u8[14] | (message->data_u8[15] << 8);
						uint16 byteNum = 16;
						uint8 valueBytes = 0;
						FeatureId_te thisFeatureId;
						for(uint8 featureNum = 0; featureNum < numOfFeatureResponses; featureNum++) //For each feature received from the Feature Manager
						{
							//Check if next feature can't fit in array(Error in # of features or # of value bytes in message received from feature manager)
							valueBytes = message->data_u8[byteNum + 5];
							if(byteNum + 6 + valueBytes <= message->dlc_u16) 
							{
								thisFeatureId = (FeatureId_te)(message->data_u8[byteNum] | (message->data_u8[byteNum + 1] << 8) //Get featureID
									| (message->data_u8[byteNum + 2] << 16) | (message->data_u8[byteNum + 3] << 24));
								byteNum = byteNum + 4;
								for(uint8 i = 0; i < RequestedFeatureCount; i++) //loop through list of requested featureIDs to see if this feature ID was one of ones requested
								{
									if(thisFeatureId == Features[i]) //If it is, fill in the status and value in the corresponding index of ReceivedFeatures
									{
										numFeaturesReceived++;
										//Don't need to set FeatureID since that was done in initialization
										if(message->data_u8[byteNum] >= FEATURE_NOT_AVAILABLE && message->data_u8[byteNum] <= FEATURE_EXPIRED)
										{
											ReceivedFeatures[i].FeatureStatus = (FeatureStatus_te)message->data_u8[byteNum];	
										}
										else
										{
											State = FMC_ERROR;
											FeatureManagerClientInfo1_s.errorState = STATUS_RECEIVE_ERROR;
											return;
										}

										if(valueBytes > 4 && thisFeatureId == VEHICLE_IDENTIFICATION_NUMBER)
										{
											for(uint8 a = 0; a < valueBytes; a++)
											{
												if(a < VIN_ARRAY_LENGTH)
												{
													Vin[a] = message->data_u8[byteNum + 2 + a];
													if(!vinChanged)
													{
														if(Vin[a] != cache.GetVin()[a] || ReceivedFeatures[i].FeatureStatus != cache.GetVinStatus())
														{
															vinChanged = TRUE;
															FeatureManagerClientInfo2_s.numberOfFeaturesUpdated++;
														}
													}
												}
											}
											VinReceived = TRUE;
										}
										else
										{
											if(valueBytes > 0)
											{
												ReceivedFeatures[i].FeatureValue = 0;
												for(uint8 j = 0; j < valueBytes; j++)
												{
													ReceivedFeatures[i].FeatureValue |= (message->data_u8[byteNum + 2 + j] << (j * 8));
												}
											}
											else //If there is no value, set it to all Fs
											{
												ReceivedFeatures[i].FeatureValue = 0xFFFFFFFF;
											}

											if(ReceivedFeatures[i].FeatureStatus != cache.GetFeatureStatus(thisFeatureId) 
											|| ReceivedFeatures[i].FeatureValue != cache.GetFeatureValue(thisFeatureId))
											{
												FeatureManagerClientInfo2_s.numberOfFeaturesUpdated++;
											}
										}
										break;
									}
								}
								byteNum = byteNum + 2 + valueBytes; //Increment byteNum to correct starting byte for next feature
							}
							else //Error in # of features or # of value bytes in message received from feature manager
							{
								State = FMC_ERROR;
								FeatureManagerClientInfo1_s.errorState = DATA_RECEIVE_ERROR;
								return;
							}
						}

						if(numFeaturesReceived < RequestedFeatureCount)
						{
							State = FMC_ERROR;
							FeatureManagerClientInfo1_s.errorState = NOT_ALL_FEATURES_RECEIVED;
						}
						else
						{
							FeaturesReceived = TRUE;
						}
					}
				}
				break;
			default:
			break;
		}
	};

	void step(void)
	{
		if(!ignitionOff)
		{
			FeatureManagerClientInfo1_s.fmcState = State;
		}

		switch(State)
		{
			case WAIT_FOR_ACM_ACL:
			case ACM_NOT_ALIVE:
				if(FeatureManagerIsAlive) //Address claim has been received from feature manager
				{
					State = SEND_TIMESTAMP_REQUEST;
				}
			break;

			case SEND_TIMESTAMP_REQUEST:
				SendTimestampRequest();
				AcmCommTimeout.start();
				State = AWAIT_TIMESTAMP_RESPONSE;
			break;

			case AWAIT_TIMESTAMP_RESPONSE:
			case ACM_NOT_RESPONDING_TIMESTAMP:
				if(TimestampReceived)
				{
					/*Timestamp received was different that the one in cache or number of features requested was different than what was read from the cache
					or the feature list the FMC was initialized with is not the same as the one read from the feature cache or there was a checksum error when reading the feature cache*/
					if(FeatureManagerTimestamp != cache.GetTimestamp() || RequestedFeatureCount != cache.GetNumFeaturesInEeprom() 
						|| !cache.GetFeaturesAreSame() || FeatureManagerClientInfo1_s.warningBitfield & INCORRECT_CHECKSUM)
					{
						State = SEND_FEATURE_REQUEST;
					}
					else
					{
						State = NO_NEW_FEATURES;
					}
				}
			break;

			case SEND_FEATURE_REQUEST:
				SendFeatureRequest();
				AcmCommTimeout.start();
				State = AWAIT_FEATURE_RESPONSE;
			break;

			case AWAIT_FEATURE_RESPONSE:
			case ACM_NOT_RESPONDING_FEATURES:
				if(FeaturesReceived)
				{
					State = NEW_FEATURES_READY;
				}
				break;

			case NEW_FEATURES_READY:
				if(EepromCacheChangeStatus)
				{
					if(cache.UpdateCache(ReceivedFeatures, RequestedFeatureCount, FeatureManagerTimestamp, VinReceived, Vin))
					{
						State = NEW_FEATURES_WRITTEN;
					}
					else
					{
						State = FMC_ERROR;
						FeatureManagerClientInfo1_s.errorState = CACHE_WRITE_ERROR;
					}
				}
				break;
			case FMC_ERROR:
			case NO_NEW_FEATURES:
			case NEW_FEATURES_WRITTEN:
			default:
				break;
		}
	};

	void Shutdown(void)
	{
		TimestampRequestTimeout.stop();
		FeatureRequestTimeout.stop();
		AclRequestTimeout.stop();
		AcmCommTimeout.stop();
		ignitionOff = TRUE;
		if(State == NEW_FEATURES_WRITTEN)
		{
			FeatureManagerClientInfo1_s.fmcState = NEW_FEATURES_WRITTEN;
		}
		else
		{
			State = NO_NEW_FEATURES;
			FeatureManagerClientInfo1_s.fmcState = NO_NEW_FEATURES;
		}
	};

	void KeyOn(void)
	{
		ignitionOff = FALSE;
	}

	FeatureStatus_te getFeatureStatus( FeatureId_te featureId )
	{
		//reads from cache (eeprom) on startup
		return cache.GetFeatureStatus(featureId);
	};

	uint32 getFeatureValue( FeatureId_te featureId )
	{
		//reads from feature cache on startup.
		return cache.GetFeatureValue(featureId);
	};

	char* getVin(void)
	{
		return cache.GetVin();
	}

	FeatureStatus_te getVinStatus(void)
	{
		return cache.GetVinStatus();
	}

	FeatureManagerClientInfo1_ts getFMCInfo_1(void)
	{
		return FeatureManagerClientInfo1_s;
	}

	FeatureManagerClientInfo2_ts getFMCInfo_2(void)
	{
		return FeatureManagerClientInfo2_s;
	}

	void setEepromCacheChangeStatus(void)
	{
		EepromCacheChangeStatus = TRUE;
		FeatureManagerClientInfo1_s.warningBitfield |= 128;
	}

	uint32 getTimestamp(void)
	{
		return cache.GetTimestamp();
	}

private:
	uint8 SourceAddress;
	uint16 RequestedFeatureCount;
	FeatureId_te Features[featureCount]; 
	FeatureCache<featureCount> cache;
	FCState_te State;
	bool FeatureManagerIsAlive;
	TaskTimer TimestampRequestTimeout;
	TaskTimer FeatureRequestTimeout;
	TaskTimer AclRequestTimeout;
	TaskTimer AcmCommTimeout;
	uint32 FeatureManagerTimestamp;
	Feature_ts ReceivedFeatures[featureCount];
	uint8 FeatureManagerSA;
	uint32 Challenge;
	bool TimestampReceived;
	bool FeaturesReceived;
	uint8 TotalNumPackets;
	bool VinReceived;
	char Vin[20];
	iTaskRegistrar::CanRequest CanRequests[2];
	FeatureManagerClientInfo1_ts FeatureManagerClientInfo1_s;
	FeatureManagerClientInfo2_ts FeatureManagerClientInfo2_s;
	iCanSend* canSend_ptr;
	TransportProtocolCanFrame tpMsg;
	bool EepromCacheChangeStatus;
	bool ignitionOff;

	void SendTimestampRequest(void)
	{
		SingleCanFrame canFrame;
		canFrame.dlc_u16 = 6;
		canFrame.isXformat_b = true;
		canFrame.id_u32 = (0x18EF0000) | (FeatureManagerSA << 8) | (SourceAddress);
		canFrame.data_u8[0] = TIMESTAMP_REQUEST_XID >> 8;
		canFrame.data_u8[1] = TIMESTAMP_REQUEST_XID & 0x00FF;
		canFrame.data_u8[2] = Challenge & 0x000000FF;
		canFrame.data_u8[3] = (Challenge & 0x0000FF00) >> 8;
		canFrame.data_u8[4] = (Challenge & 0x00FF0000) >> 16;
		canFrame.data_u8[5] = Challenge >> 24;

		canSend_ptr->SendCanMsg((CanMessage*)&canFrame, (BusNode)CAN_J1939);
		TimestampRequestTimeout.start();
	}

	static void SendTimestampRequestWrapper(void* pt2Object)
	{
		FeatureClient* thisObject = (FeatureClient*)pt2Object;
		thisObject->SendTimestampRequest();
	}

	void SendAclRequest(void)
	{
		SingleCanFrame canFrame;
		canFrame.dlc_u16 = 3;
		canFrame.isXformat_b = true;
		canFrame.id_u32 = (0x18EA0000) | (0xFF << 8) | (SourceAddress);
		canFrame.data_u8[0] = 0;
		canFrame.data_u8[1] = 0xEE; //ACL PGN
		canFrame.data_u8[2] = 0;

		canSend_ptr->SendCanMsg((CanMessage*)&canFrame, (BusNode)CAN_J1939);
		AclRequestTimeout.start();
	}

	static void SendAclRequestWrapper(void* pt2Object)
	{
		FeatureClient* thisObject = (FeatureClient*)pt2Object;
		thisObject->SendAclRequest();
	}

	void SendFeatureRequest(void)
	{
		tpMsg.dlc_u16 = NUM_BYTES_BEFORE_FEATURES + RequestedFeatureCount * NUM_BYTES_PER_FEATURE;
		tpMsg.isXformat_b = true;
		
		tpMsg.data_u8[0] = FEATURE_REQUEST_XID >> 8;
		tpMsg.data_u8[1] = FEATURE_REQUEST_XID & 0x00FF;
		tpMsg.data_u8[2] = Challenge & 0x000000FF;
		tpMsg.data_u8[3] = (Challenge & 0x0000FF00) >> 8;
		tpMsg.data_u8[4] = (Challenge & 0x00FF0000) >> 16;
		tpMsg.data_u8[5] = Challenge >> 24;
		tpMsg.data_u8[6] = RequestedFeatureCount & 0x00FF;
		tpMsg.data_u8[7] = RequestedFeatureCount >> 8;

		for(uint16 CurrentFeatureNumber = 0; CurrentFeatureNumber < RequestedFeatureCount; CurrentFeatureNumber++)
		{
			for(uint8 FeatureByteNumber = 0; FeatureByteNumber < NUM_BYTES_PER_FEATURE; FeatureByteNumber++)
			{
				switch (FeatureByteNumber)
				{
					case 0:
						tpMsg.data_u8[NUM_BYTES_BEFORE_FEATURES + FeatureByteNumber + CurrentFeatureNumber * NUM_BYTES_PER_FEATURE] = Features[CurrentFeatureNumber] & 0x000000FF;
						break;
					case 1:
						tpMsg.data_u8[NUM_BYTES_BEFORE_FEATURES + FeatureByteNumber + CurrentFeatureNumber * NUM_BYTES_PER_FEATURE] = (Features[CurrentFeatureNumber] & 0x0000FF00) >> 8;
						break;
					case 2:
						tpMsg.data_u8[NUM_BYTES_BEFORE_FEATURES + FeatureByteNumber + CurrentFeatureNumber * NUM_BYTES_PER_FEATURE] = (Features[CurrentFeatureNumber] & 0x00FF0000) >> 16;
						break;
					case 3:
						tpMsg.data_u8[NUM_BYTES_BEFORE_FEATURES + FeatureByteNumber + CurrentFeatureNumber * NUM_BYTES_PER_FEATURE] = Features[CurrentFeatureNumber] >> 24;
						break;
					default:
						break;
				}
			}
		}
		
		tpMsg.id_u32 = (0x1CEF0000) | (FeatureManagerSA << 8) | (SourceAddress);

		canSend_ptr->SendCanMsg((CanMessage*)&tpMsg, (BusNode)CAN_J1939);
		FeatureRequestTimeout.start();
	}

	static void SendFeatureRequestWrapper(void* pt2Object)
	{
		FeatureClient* thisObject = (FeatureClient*)pt2Object;
		thisObject->SendFeatureRequest();
	}

	void CommTimeoutHandler(void)
	{
		switch(State)
		{
			case WAIT_FOR_ACM_ACL:
				State = ACM_NOT_ALIVE;
				break;
			case AWAIT_TIMESTAMP_RESPONSE:
				State = ACM_NOT_RESPONDING_TIMESTAMP;
				break;
			case AWAIT_FEATURE_RESPONSE:
				State = ACM_NOT_RESPONDING_FEATURES;
				break;
			default:
				break;
		}
	}

	static void CommTimeoutHandlerWrapper(void* pt2Object)
	{
		FeatureClient* thisObject = (FeatureClient*)pt2Object;
		thisObject->CommTimeoutHandler();
	}
};
