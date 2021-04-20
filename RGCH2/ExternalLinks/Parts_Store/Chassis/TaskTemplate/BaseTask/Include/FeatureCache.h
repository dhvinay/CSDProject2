#pragma once
extern "C"
{
#include "Project.h"
#include "eepr.h"
#include "crc16.h"
#include "FeatureList.h"
}
#include "iFeatureCache.h"

#define VIN_ARRAY_LENGTH 17
#define NUM_FEATURES_ERROR 0xFF
#define VALUE_ERROR 0xFFFFFFFF
#define TIMESTAMP_ERROR 0xFFFFFFFF
#define CHECKSUM_BYTES 2
#define FEATURE_CACHE_END 0x1BFF
const Feature_ts defaultFeature = { NO_FEATURE_ID, FEATURE_DOES_NOT_EXIST, VALUE_ERROR };
template<int numFeaturesRequested>

class FeatureCache : public iFeatureCache
{
public:

	FeatureCache(uint32 eepAddress, const FeatureId_te featureList[numFeaturesRequested]) : FeatureCount(numFeaturesRequested), EepromAddress(eepAddress)
	{
		for(uint8 i = 0; i < numFeaturesRequested; i++)
		{
			RequestedFeatureIDs[i] = featureList[i];
			LocalFeatures[i] = defaultFeature;
		}
	}
	~FeatureCache(){};
	
	uint8 InitOk(void) // Returns 0 if init went ok, else returns nonzero number
	{
		initOk = 0;
		Feature_ts feature;
		uint16 calcChecksum_u16 = 0;
		sint32 err_s32 = 0;
		uint8 temp_u8;
		uint16 temp_u16;
		uint32 temp_u32;
		VinInEeprom = FALSE;
		Vin_Status = FEATURE_DOES_NOT_EXIST;
		FeaturesAreSame = FALSE;
		uint8 sizeOfFeature = sizeof(feature.FeatureID) + sizeof(feature.FeatureStatus) + sizeof(feature.FeatureValue);
		bool invalidFeaturesOrTimestamp = FALSE;
		for(uint8 a = 0; a < VIN_ARRAY_LENGTH; a++)
		{
			Vin_Cache[a] = 0xFF;
		}

		err_s32 |= readEEPROM32bit_s32(EepromAddress, &Timestamp);
		addCRC16Chksum32bit(Timestamp, &calcChecksum_u16);

		err_s32 |= readEEPROM8bit_s32(EepromAddress + sizeof(Timestamp), &NumOfFeaturesInEeprom);
		addCRC16Chksum8bit(NumOfFeaturesInEeprom, &calcChecksum_u16);

		if(NumOfFeaturesInEeprom != NUM_FEATURES_ERROR && Timestamp != TIMESTAMP_ERROR) //If this is the first time running the feature manager client
		{
			for(uint8 featureNum = 0; featureNum < NumOfFeaturesInEeprom; featureNum++)
			{
				err_s32 |= readEEPROM32bit_s32(EepromAddress + sizeof(NumOfFeaturesInEeprom) + sizeof(Timestamp) + featureNum * sizeOfFeature, &temp_u32);
				addCRC16Chksum32bit(temp_u32, &calcChecksum_u16);
				feature.FeatureID = (FeatureId_te)temp_u32;

				err_s32 |= readEEPROM8bit_s32(EepromAddress + sizeof(NumOfFeaturesInEeprom) + sizeof(Timestamp) + featureNum * sizeOfFeature + sizeof(feature.FeatureID), &temp_u8);
				addCRC16Chksum8bit(temp_u8, &calcChecksum_u16);
				feature.FeatureStatus = (FeatureStatus_te)temp_u8;

				if(feature.FeatureID == VEHICLE_IDENTIFICATION_NUMBER)
				{
					VinInEeprom = TRUE;
					Vin_Status = feature.FeatureStatus;
					for( uint8 i = 0; i < VIN_ARRAY_LENGTH; i++ )
					{
						err_s32 |= readEEPROM8bit_s32(EepromAddress + sizeof(NumOfFeaturesInEeprom) + sizeof(Timestamp) + featureNum * sizeOfFeature + sizeof(feature.FeatureID) + sizeof(feature.FeatureStatus) + i, &temp_u8);
						addCRC16Chksum8bit(temp_u8, &calcChecksum_u16);
						Vin_Cache[i] = temp_u8;
					}
				}
				else
				{
					err_s32 |= readEEPROM32bit_s32(EepromAddress + sizeof(NumOfFeaturesInEeprom) + sizeof(Timestamp) + featureNum * sizeOfFeature + sizeof(feature.FeatureID) + sizeof(feature.FeatureStatus), &temp_u32);
					addCRC16Chksum32bit(temp_u32, &calcChecksum_u16);
					feature.FeatureValue = temp_u32;
				}

				if(featureNum < FeatureCount && feature.FeatureID != VEHICLE_IDENTIFICATION_NUMBER)
				{
					LocalFeatures[featureNum] = feature;
				}
			}

			FeatureBytes = VinInEeprom ? (NumOfFeaturesInEeprom - 1) * sizeOfFeature + 22 : NumOfFeaturesInEeprom * sizeOfFeature;
			// Read in the checksum
			err_s32 |= readEEPROM16bit_s32( EepromAddress + sizeof(NumOfFeaturesInEeprom) + sizeof(Timestamp) + FeatureBytes, &temp_u16);

			FeaturesAreSame = SameFeatures();
		}
		else
		{
			temp_u16 = 0xFFFF;
			calcChecksum_u16 = 0xFFFF;
			invalidFeaturesOrTimestamp = TRUE;
		}

		if(invalidFeaturesOrTimestamp)
		{
			initOk |= INVALID_NUM_FEAT_TIMESTAMP; //Invalid number of features or invalid timestamp
		}

		if(temp_u16 != calcChecksum_u16)
		{
			initOk |= INCORRECT_CHECKSUM; //Incorrect checksum
		}

		if(err_s32)
		{
			initOk |= EEPROM_READ_ERROR; //Eeprom read error
		}

		if(initOk)
		{
			for(uint8 i = 0; i < FeatureCount; i++)
			{
				LocalFeatures[i] = defaultFeature; //If there is an error reading eeprom then we cannot use the eeprom data so set them all back to default
				Vin_Status = FEATURE_DOES_NOT_EXIST;
				for(uint8 a = 0; a < VIN_ARRAY_LENGTH; a++)
				{
					Vin_Cache[a] = 0xFF;
				}
			}
		}

		return initOk;
	};

	bool SameFeatures(void)
	{
		FeatureId_te sortedRequestFeatures[numFeaturesRequested];
		FeatureId_te sortedCacheFeatures[numFeaturesRequested];
		uint8 featureNum;
		
		for(featureNum = 0; featureNum < numFeaturesRequested; featureNum++)
		{
			sortedRequestFeatures[featureNum] = RequestedFeatureIDs[featureNum];
			if(VinInEeprom && LocalFeatures[featureNum].FeatureID == NO_FEATURE_ID)
			{
				sortedCacheFeatures[featureNum] = VEHICLE_IDENTIFICATION_NUMBER;
			}
			else
			{
				sortedCacheFeatures[featureNum] = LocalFeatures[featureNum].FeatureID;
			}
		}

		sortFeatures(sortedRequestFeatures);
		sortFeatures(sortedCacheFeatures);

		for(featureNum = 0; featureNum < numFeaturesRequested; featureNum++)
		{
			if(sortedRequestFeatures[featureNum] != sortedCacheFeatures[featureNum])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	void sortFeatures(FeatureId_te* sortedFeatures)
	{
		uint8 i; 
		uint8 j;
		uint8 min;
		FeatureId_te temp;
		for (i = 0; i < numFeaturesRequested - 1; i++) 
		{
			min = i;
			for (j = i + 1; j < numFeaturesRequested; j++)
			{
				if (sortedFeatures[j] < sortedFeatures[min])
				{
					min = j;
				}
			}
			temp = sortedFeatures[i];
			sortedFeatures[i] = sortedFeatures[min];
			sortedFeatures[min] = temp;
		}
	}

	bool GetFeaturesAreSame(void)
	{
		return FeaturesAreSame;
	}

	uint32 GetTimestamp(void)
	{
		return Timestamp;
	};

	uint8 GetNumFeaturesInEeprom(void)
	{
		return NumOfFeaturesInEeprom;
	}

	FeatureStatus_te GetFeatureStatus(FeatureId_te FeatureID)
	{
		FeatureStatus_te featureStatus = FEATURE_DOES_NOT_EXIST;
		if(initOk == 0)
		{
			for(uint8 featureNum = 0; featureNum < FeatureCount; featureNum++)
			{
				if(LocalFeatures[featureNum].FeatureID == FeatureID)
				{
					featureStatus = LocalFeatures[featureNum].FeatureStatus;
				}
			}
		}
		return featureStatus;
	};

	uint32 GetFeatureValue(FeatureId_te FeatureID)
	{
		uint32 featureValue = VALUE_ERROR;
		if(initOk == 0)
		{
			for(uint8 featureNum = 0; featureNum < FeatureCount; featureNum++)
			{
				if(LocalFeatures[featureNum].FeatureID == FeatureID)
				{
					featureValue = LocalFeatures[featureNum].FeatureValue;
				}
			}
		}
		return featureValue;
	};

	char* GetVin(void)
	{
		return Vin_Cache;
	}

	FeatureStatus_te GetVinStatus(void)
	{
		return Vin_Status;
	}

	bool UpdateCache(Feature_ts* NewFeatures, uint8 NewCount, uint32 NewTimestamp, bool vinReceived, char* vin)
	{
		sint32 err_s32 = 0;
		bool success = TRUE;
		uint16 calcChecksum_u16 = 0;
		uint8 temp_u8;
		uint32 temp_u32;
		uint8 sizeOfStruct = sizeof(NewFeatures[0].FeatureID) + sizeof(NewFeatures[0].FeatureStatus) + sizeof(NewFeatures[0].FeatureValue);
		uint16 FeatureBytes = VinInEeprom ? (NumOfFeaturesInEeprom - 1) * sizeOfStruct + 22 : NumOfFeaturesInEeprom * sizeOfStruct;
		uint32 ChecksumAddress = vinReceived ? EepromAddress + sizeof(NewCount) + sizeof(NewTimestamp) + (NewCount - 1) * sizeOfStruct + 22 : 
			EepromAddress + sizeof(NewCount) + sizeof(NewTimestamp) + NewCount * sizeOfStruct;

		//Now write information from ACM back into the cache
		err_s32 |= writeEEPROM32bit_s32(EepromAddress, &NewTimestamp);
		addCRC16Chksum32bit(NewTimestamp, &calcChecksum_u16);

		err_s32 |= writeEEPROM8bit_s32(EepromAddress + sizeof(NewTimestamp), &NewCount);
		addCRC16Chksum8bit(NewCount, &calcChecksum_u16);

		for(uint8 featureNum = 0; featureNum < NewCount; featureNum++)
		{
			temp_u32 = (uint32)NewFeatures[featureNum].FeatureID;
			err_s32 |= writeEEPROM32bit_s32(EepromAddress + sizeof(NewCount) + sizeof(NewTimestamp) + featureNum * sizeOfStruct, &temp_u32);
			addCRC16Chksum32bit(NewFeatures[featureNum].FeatureID, &calcChecksum_u16);

			temp_u8 = (uint8)NewFeatures[featureNum].FeatureStatus;
			err_s32 |= writeEEPROM8bit_s32(EepromAddress + sizeof(NewCount) + sizeof(NewTimestamp) + featureNum * sizeOfStruct + sizeof(NewFeatures[featureNum].FeatureID), &temp_u8);
			addCRC16Chksum8bit(NewFeatures[featureNum].FeatureStatus, &calcChecksum_u16);

			if(vinReceived && NewFeatures[featureNum].FeatureID == VEHICLE_IDENTIFICATION_NUMBER)
			{
				for(uint8 i = 0; i < VIN_ARRAY_LENGTH; i++)
				{
					temp_u8 = (uint8)vin[i];
					err_s32 |= writeEEPROM8bit_s32(EepromAddress + sizeof(NewCount) + sizeof(NewTimestamp) + featureNum * sizeOfStruct + sizeof(NewFeatures[featureNum].FeatureID) + sizeof(NewFeatures[featureNum].FeatureStatus) + i, &temp_u8);
					addCRC16Chksum8bit(temp_u8, &calcChecksum_u16);
				}
			}
			else
			{
				err_s32 |= writeEEPROM32bit_s32(EepromAddress + sizeof(NewCount) + sizeof(NewTimestamp) + featureNum * sizeOfStruct + sizeof(NewFeatures[featureNum].FeatureID) + sizeof(NewFeatures[featureNum].FeatureStatus), &NewFeatures[featureNum].FeatureValue);
				addCRC16Chksum32bit(NewFeatures[featureNum].FeatureValue, &calcChecksum_u16);
			}
		}

		err_s32 |= writeEEPROM16bit_s32( ChecksumAddress, &calcChecksum_u16);

		uint16 currentByte;
		uint32 writeValue = 0xFFFFFFFF;
		for(currentByte = ChecksumAddress + 2; currentByte + 4 < FEATURE_CACHE_END; currentByte = currentByte + 4) //Write the rest of the cache to 0xFF
		{
			err_s32 |= writeEEPROM32bit_s32(currentByte, &writeValue);
		}

		err_s32 |= writeEEPROM32bit_s32(FEATURE_CACHE_END - 3, &writeValue);

		if( err_s32 != 0 )
		{
			success = FALSE;
		}
		return success;
	};	

private:
	uint32 EepromAddress;
	uint16 FeatureCount;
	Feature_ts LocalFeatures[numFeaturesRequested];
	FeatureId_te RequestedFeatureIDs[numFeaturesRequested];
	uint8 NumOfFeaturesInEeprom;
	uint32 Timestamp;
	uint16 FeatureBytes;
	uint8 initOk;
	bool VinInEeprom;
	char Vin_Cache[VIN_ARRAY_LENGTH];
	FeatureStatus_te Vin_Status;
	bool FeaturesAreSame;
};
