extern "C"
{
#include "Project.h"
}
#include "CanMessage.h"
#include "EosCanSend.h"
#include "iTaskRegistrar.h"
#include "J1939TP.h"

const uint8 CTRL_BYTE_ACK = 0;
const uint8 CTRL_BYTE_NACK = 1;
const uint8 CTRL_BYTE_RTS = 16;
const uint8 CTRL_BYTE_CTS = 17;
const uint8 CTRL_BYTE_EOM = 19;
const uint8 CTRL_BYTE_BAM = 32;
const uint8 CTRL_BYTE_ABORT = 255;

const uint8 PGN_ACK = 0xE8;
const uint8 PGN_DT = 0xEB;
const uint8 PGN_CM = 0xEC;
const uint8 PGN_PDU1_MAX = 0xEF;

const uint32 CAN_ID_CM = 0x00EC0000;
const uint32 CAN_ID_DT = 0x00EB0000;
const uint32 CAN_ID_PGN_MASK = 0x00FF0000;

const uint8 ABORT_REASON_TIMEOUT = 3;

const uint8 DATA_NOT_AVAILABLE = 0xFF;

#define RESPONSE_TIMEOUT_MS	1250
#define DT_TIMEOUT_MS		750

// Default Constructor
J1939TP::J1939TP() : TpResponseTimeout(RESPONSE_TIMEOUT_MS, &HandleTimeoutWrapper), TpDtTimeout(DT_TIMEOUT_MS, &HandleTimeoutWrapper){};

// Constructor
J1939TP::J1939TP(iTaskRegistrar* registrar) : TpResponseTimeout(RESPONSE_TIMEOUT_MS, &HandleTimeoutWrapper), TpDtTimeout(DT_TIMEOUT_MS, &HandleTimeoutWrapper)
{
	totalNumPackets = 0; // Total number of packets needed to send the data
	totalNumBytes = 0; // Total message size in Bytes
	packetCount = 0; // Maintain the number of packets that have been received
	packetsBetweenCTS = 0; // Peer-to-peer number of DTs between CTS
	bamMsg = false; // False if peer-to-peer connection
	pendingMsg = false; // Is a message already being processed
	correctPgn = false;
	pendingReceiveMsg = false;
	canFilterCount = 0;
	// State Machine Sending TP messages
	bytesLeft = 0;
	TPState = EXIT;
	TPframe = TransportProtocolCanFrame();

	m_taskRegistrar = registrar;
};

void J1939TP::init()
{
	// CM
	CanRequests[0].bus_u8 = CAN_J1939;
	CanRequests[0].IdMask_u32 = CAN_ID_PGN_MASK;
	CanRequests[0].IdSet_u32 = CAN_ID_CM;
	CanRequests[0].isXformat_b = 1;
	CanRequests[0].dlc_u16 = 8; 
	CanRequests[0].canAdmin_ps = 0;

	// DT
	CanRequests[1].bus_u8 = CAN_J1939;
	CanRequests[1].IdMask_u32 = CAN_ID_PGN_MASK;
	CanRequests[1].IdSet_u32 = CAN_ID_DT;
	CanRequests[1].isXformat_b = 1;
	CanRequests[1].dlc_u16 = 8;
	CanRequests[1].canAdmin_ps = 0;

	m_taskRegistrar->InitMailboxes(CanRequests, 2, this);

	m_taskRegistrar->registerTimer(&TpResponseTimeout, this);
	m_taskRegistrar->registerTimer(&TpDtTimeout, this);
}

// Destructor
J1939TP::~J1939TP() {};

// Local Functions
void J1939TP::sendCTS(uint8 nextPacket, uint8 sourceAdr, uint8 destAdr, uint16 msgPGN)
{
	SingleCanFrame canMsg;

	canMsg.data_u8[0] = CTRL_BYTE_CTS;		//control byte = Clear To Send
	canMsg.data_u8[1] = packetsBetweenCTS;	//number of packets that can be sent at once (must be no larger than the value in Byte 5 of the RTS message )
	canMsg.data_u8[2] = nextPacket;			//next packet number to be sent
	canMsg.data_u8[3] = 0xFF;				//J1939 standard
	canMsg.data_u8[4] = 0xFF;				//J1939 standard
	canMsg.data_u8[5] = (uint8)(msgPGN & 0x00FF);    //bytes 6-8: PGN of the packeted message (LSB first)
	canMsg.data_u8[6] = (uint8)((msgPGN & 0xFF00) >> 8);
	canMsg.data_u8[7] = 0x00;                        //only the 2 LSbits are used and they are 0

	canMsg.id_u32 = getJ1939CanID(6, PGN_CM, sourceAdr, destAdr);
	canMsg.isXformat_b = 1;					//J1939TP is always extended format
	canMsg.dlc_u16 = 8;
	sendCanMsg(&canMsg, CANBUS_2);
}

void J1939TP::sendEndOfMsgAck(uint8 myAdr, uint8 destAdr, uint16 msgPGN)
{
	SingleCanFrame canMsg;

	canMsg.data_u8[0] = CTRL_BYTE_EOM;		// control byte = End of Message Acknowledge
	canMsg.data_u8[1] = (uint8)(totalNumBytes & 0x00FF);		// Bytes 2-3: Total message size (num of bytes) 
	canMsg.data_u8[2] = (uint8)((totalNumBytes & 0xFF00) >> 8);	// MSB last
	canMsg.data_u8[3] = totalNumPackets;	// Total number of packets sent in TP message
	canMsg.data_u8[4] = 0xFF;				// J1939 EoMACK standard
	canMsg.data_u8[5] = (uint8)(msgPGN & 0x00FF);
	canMsg.data_u8[6] = (uint8)((msgPGN & 0xFF00) >> 8);
	canMsg.data_u8[7] = 0x00;

	canMsg.id_u32 = getJ1939CanID(6, PGN_CM, myAdr, destAdr);
	canMsg.isXformat_b = 1;
	canMsg.dlc_u16 = 8;

	sendCanMsg(&canMsg, CANBUS_2);
}

// Sending TP message helper function
void J1939TP::sendRTS(uint16 totalBytes, uint8 totalPackets, uint8 sourceAdr, uint8 destAdr, uint16 msgPGN, uint8 packetsPerGroup)
{
	SingleCanFrame canMsg;

	canMsg.data_u8[0] = CTRL_BYTE_RTS;		//control byte = Request To Send
	canMsg.data_u8[1] = totalBytes & 0xFF;	//LSB total number of bytes to be sent
	canMsg.data_u8[2] = totalBytes >> 8;	//MSB total number of bytes to be sent
	canMsg.data_u8[3] = totalPackets;		//Total number of packets to be sent
	canMsg.data_u8[4] = packetsPerGroup;	// # of packets before two cts need to be sent (= totalPackets then no double CTS is needed)
	canMsg.data_u8[5] = (uint8)(msgPGN & 0x00FF);    //bytes 6-8: PGN of the packeted message (LSB first)
	canMsg.data_u8[6] = (uint8)((msgPGN & 0xFF00) >> 8);
	canMsg.data_u8[7] = 0x00;                        //only the 2 LSbits are used and they are 0

	canMsg.id_u32 = getJ1939CanID(6, PGN_CM, destAdr, sourceAdr);
	canMsg.isXformat_b = 1;
	canMsg.dlc_u16 = totalBytes; // Instead of just 8 put totalBytes for tp message

	sendCanMsg(&canMsg, CANBUS_2);
}

void J1939TP::sendDT(uint8 numBytes, uint8 sourceAdr, uint8 destAdr)
{
	if (numBytes < SINGLEFRAME_DATA_PER_FRAME)
	{
		SingleCanFrame canMsg;

		canMsg.data_u8[0] = (uint8)packetCount;
		for (uint8 index = 1; index < SINGLEFRAME_DATA_PER_FRAME; index++)
		{
			if(index <= numBytes)
			{
				canMsg.data_u8[index] = TPframe.data_u8[((packetCount - 1) * 7) + (index - 1)];
			}
			else
			{
				canMsg.data_u8[index] = DATA_NOT_AVAILABLE; //According to SAE J1939-21 if the data bytes do not fill the 8 byte data packet, then fill the rest with 0xFF
			}
		}
		canMsg.id_u32 = getJ1939CanID(6, PGN_DT, destAdr, sourceAdr);
		canMsg.isXformat_b = 1;
		canMsg.dlc_u16 = SINGLEFRAME_DATA_PER_FRAME;

		sendCanMsg(&canMsg, CANBUS_2);
	}
}

void J1939TP::sendAbort(uint8 myAdr, uint8 destAdr, uint16 msgPGN, uint8 abortReason)
{
	SingleCanFrame canMsg;

	canMsg.data_u8[0] = CTRL_BYTE_ABORT;	//control byte = Abort
	canMsg.data_u8[1] = abortReason;
	canMsg.data_u8[2] = 0xFF;
	canMsg.data_u8[3] = 0xFF;
	canMsg.data_u8[4] = myAdr;
	canMsg.data_u8[5] = (uint8)(msgPGN & 0x00FF);
	canMsg.data_u8[6] = (uint8)((msgPGN & 0xFF00) >> 8);
	canMsg.data_u8[7] = 0x00;

	canMsg.id_u32 = getJ1939CanID(6, PGN_CM, destAdr, myAdr);
	canMsg.isXformat_b = 1;
	canMsg.dlc_u16 = 8;
	sendCanMsg(&canMsg, CANBUS_2);
}

uint32 J1939TP::getJ1939CanID(uint8 priority, uint8 PduFormat, uint8 DestAddress, uint8 SrcAddress)
{
	uint32 ID = ((uint32)priority << 26) |
		((uint32)PduFormat << 16) |
		((uint32)DestAddress << 8) |
		((uint32)SrcAddress);
	return ID;
}

void J1939TP::sendACK(uint8 myAdr, uint8 destAdr, uint16 msgPGN)
{
	SingleCanFrame canMsg;

	canMsg.data_u8[0] = CTRL_BYTE_ACK; //control byte = positive ack.
	canMsg.data_u8[1] = 0xFF;
	canMsg.data_u8[2] = 0xFF;
	canMsg.data_u8[3] = 0xFF;
	canMsg.data_u8[4] = myAdr;
	canMsg.data_u8[5] = (uint8)(msgPGN & 0x00FF);
	canMsg.data_u8[6] = (uint8)((msgPGN & 0xFF00) >> 8);
	canMsg.data_u8[7] = 0x00;

	canMsg.id_u32 = getJ1939CanID(6, PGN_ACK, myAdr, destAdr);
	canMsg.isXformat_b = 1;
	canMsg.dlc_u16 = 8;
	sendCanMsg(&canMsg, CANBUS_2);
}

void J1939TP::sendNACK(uint8 myAdr, uint8 destAdr, uint16 msgPGN)
{
	SingleCanFrame canMsg;

	canMsg.data_u8[0] = CTRL_BYTE_NACK; //control byte = neg. ack.
	canMsg.data_u8[1] = 0xFF;
	canMsg.data_u8[2] = 0xFF;
	canMsg.data_u8[3] = 0xFF;
	canMsg.data_u8[4] = myAdr;
	canMsg.data_u8[5] = (uint8)(msgPGN & 0x00FF);
	canMsg.data_u8[6] = (uint8)((msgPGN & 0xFF00) >> 8);
	canMsg.data_u8[7] = 0x00;

	canMsg.id_u32 = getJ1939CanID(6, PGN_ACK, destAdr, myAdr);
	canMsg.isXformat_b = 1;
	canMsg.dlc_u16 = 8;
	sendCanMsg(&canMsg, CANBUS_2);
}

bool J1939TP::filterCheck(CanMessage* canMsg)
{
	// Filter out with requests looking at set and mask
	for (uint32 index = 0; index < canFilterCount; index++)
	{
		if ((CanFilters[index].id_mask & CanFilters[index].id_set) == (canMsg->id_u32 & CanFilters[index].id_mask))
		{
			return true;
		}
	}
	return false;
}

void J1939TP::completeTPMsg(CanMessage* canMsg)
{ 
	pendingMsg = false;
	pendingReceiveMsg = false;
	bamMsg = false;
	if (((originalPGN & 0xFF00) >> 8) <= PGN_PDU1_MAX)
	{
		originalPGN = (originalPGN & 0xFF00) | ((uint16)(canMsg->id_u32 & 0x0000FF00) >> 8);
	}
	TPframe.id_u32 = (originalId & 0xFF0000FF) | (( ((uint32)originalPGN) & 0xFFFF) << 8); // Creates the id of the TP message

	TPframe.isXformat_b = true; // All tp messages are in extended format
	TPframe.dlc_u16 = totalNumBytes; // To actual byte length of whole tp msg
	TPframe.timestamp_u32 = canMsg->timestamp_u32; // Timestamp of last message received
	TPframe.data_u8 = temp_data;

	// Send TP MSG to any receivers that want the msg
	for (uint32 index = 0; index < canFilterCount; index++)
	{
		if ((CanFilters[index].id_mask & CanFilters[index].id_set) == (TPframe.id_u32 & CanFilters[index].id_mask))
		{
			CanFilters[index].canReceiver->canReceived(&TPframe); // Send completed message to requesting receivers
		}
	}
}

bool J1939TP::verifySADA(uint8 sourceAdr, uint8 destAdr)
{
	if (sourceAdr == SA)
	{
		if (destAdr == DA)
		{
			return true;
		}
	}
	return false;
}

void J1939TP::handleCM(CanMessage* canMsg, uint8 myAdr, uint8 senderAdr, uint32 msgPGN)
{
	if (!pendingReceiveMsg)
	{
		switch (canMsg->data_u8[0])
		{
			case CTRL_BYTE_RTS: // Control Byte = RTS (Request To Send)
			{
				if (!pendingMsg)
				{
					SingleCanFrame tempMsg;
					if (((msgPGN & 0xFF00) >> 8) <= PGN_PDU1_MAX)
					{
						tempMsg.id_u32 = ((uint32)((msgPGN & 0xFF00) | (senderAdr))) << 8;
					}
					else
					{
						tempMsg.id_u32 = (uint32)(msgPGN << 8);
					}

					if (filterCheck(&tempMsg)) //Check if the TP message matches any of the filters registered to this Task's TP handler
					{
						totalNumBytes = ((uint16)(canMsg->data_u8[2] << 8)) | (canMsg->data_u8[1]);
						totalNumPackets = canMsg->data_u8[3];
						bamMsg = false;
						packetsBetweenCTS = canMsg->data_u8[4];
						packetCount = 0;
						correctPgn = true;
						originalId = canMsg->id_u32;								
						originalPGN = msgPGN;
										
						pendingMsg = true;
						pendingReceiveMsg = true;
						SA = myAdr;
						DA = senderAdr;

						if (totalNumBytes <= TRANSPORT_PROTOCOL_MAX_DATA) // Checks if message is within size requirements
						{
							TpResponseTimeout.start();
							sendCTS(1, myAdr, senderAdr, msgPGN);
						}
						else // Message fails to meet size requirements
						{
							sendNACK(myAdr, senderAdr, msgPGN);
							pendingMsg = false;
							pendingReceiveMsg = false;
							correctPgn = false;
						}
					}
					else
					{
						//No filter is set up for this Task's TP handler that passes this TP message, so just ignore it
					}
				}
				else
				{
					sendNACK(myAdr, senderAdr, msgPGN);
				}
				break;
			}

			case CTRL_BYTE_CTS: // Control Byte = CTS (Clear to Send)
			{
				if (verifySADA(senderAdr, myAdr))
				{
					TpResponseTimeout.stop();

					static uint8 numCTS = 0;
					if (TPState == WAIT_CTS)
					{
						TPState = SEND_DT;
						pendingMsg = true;
						correctPgn = true;
					}
					else if (TPState == WAIT_BETWEEN_CTS)
					{
						if (numCTS > 0)
						{
							TPState = SEND_DT;
							numCTS = 0;
						}
						else
						{
							numCTS++;
						}
					}
				}
				else
				{
					sendNACK(myAdr, senderAdr, msgPGN);
				}
				break;
			}

			case CTRL_BYTE_EOM: // Control Byte = EOM (End of Message)
			{
				if (verifySADA(senderAdr, myAdr))
				{
					TPState = EXIT;
					pendingMsg = false;
					correctPgn = false;
					TpResponseTimeout.stop();
					break;
				}
				else
				{
					sendNACK(myAdr, senderAdr, msgPGN);
				}
				break;
			}

			case CTRL_BYTE_BAM: // Control Byte = BAM (Broadcast Announce Message)
			{
				if (!pendingMsg)
				{
					totalNumBytes = ((uint16)(canMsg->data_u8[2] << 8)) | (canMsg->data_u8[1]);
					totalNumPackets = canMsg->data_u8[3];
					bamMsg = true;
					packetsBetweenCTS = 1;
					packetCount = 0;
					correctPgn = true;
					originalId = canMsg->id_u32;
					originalPGN = msgPGN;
					pendingMsg = true;
					pendingReceiveMsg = true;
					SA = myAdr;
					DA = senderAdr;

					if (totalNumBytes > TRANSPORT_PROTOCOL_MAX_DATA) // Checks if message is within size requirements
					{
						sendNACK(myAdr, senderAdr, msgPGN);
						pendingMsg = false;
						pendingReceiveMsg = false;
						bamMsg = false;
						correctPgn = false;
					}
				}
				else
				{
					sendNACK(myAdr, senderAdr, msgPGN);
				}
				break;
			}

			default:
				break;
		}
	}
	else
	{
		sendNACK(myAdr, senderAdr, msgPGN);
	}
}

void J1939TP::handleDT(CanMessage* canMsg, uint8 sourceAdr, uint8 destAdr)
{
	if (correctPgn)
	{
		if (verifySADA(sourceAdr, destAdr))
		{
			if (packetCount <= totalNumPackets)
			{
				if (((uint16)canMsg->data_u8[0]) <= totalNumPackets)
				{
					packetCount++;

					uint16 index = 1;
					uint16 msgIndex;

					for (index = 1; index < 8; index++)
					{
						msgIndex = ((((uint16)canMsg->data_u8[0]) - 1) * 7) + (index - 1);
						temp_data[msgIndex] = canMsg->data_u8[index];
					}

					if (!bamMsg) // Peer to peer msg
					{
						if (packetCount == totalNumPackets) // Last packet
						{
							sendEndOfMsgAck(sourceAdr, destAdr, originalPGN);
							completeTPMsg(canMsg);
							correctPgn = false;
							TpResponseTimeout.stop();
							TpDtTimeout.stop();
						}
						else if ((packetCount % packetsBetweenCTS) == 0)
						{
							sendCTS(0, sourceAdr, destAdr, originalPGN); // (HOLD)
							sendCTS(packetCount + 1, sourceAdr, destAdr, originalPGN); // Tell send okay to send
							TpResponseTimeout.start();
							TpDtTimeout.stop();
						}
						else
						{
							TpResponseTimeout.stop();
							TpDtTimeout.stop();
							TpDtTimeout.start();
						}
					}
					else // BAM
					{
						if (packetCount == totalNumPackets) // Last packet
						{
							completeTPMsg(canMsg);
							correctPgn = false;
							bamMsg = false;
						}
					}
				}
				else
				{
					sendNACK(sourceAdr, destAdr, originalPGN);
				}
			}
			else
			{
				pendingMsg = false;
				pendingReceiveMsg = false;
				bamMsg = false;
				correctPgn = false;
			}
		}
		else
		{
			sendNACK(sourceAdr, destAdr, originalPGN);
		}
	}
}

void J1939TP::sendBAM(uint16 totalBytes, uint8 totalPackets, uint8 sourceAdr, uint8 groupExten, uint16 msgPGN)
{
	SingleCanFrame canMsg;

	canMsg.data_u8[0] = CTRL_BYTE_BAM;		//control byte = Broadcast Announce Message
	canMsg.data_u8[1] = totalBytes & 0xFF;	//LSB total number of bytes to be sent
	canMsg.data_u8[2] = totalBytes >> 8;	//MSB total number of bytes to be sent
	canMsg.data_u8[3] = totalPackets;		//Total number of packets to be sent
	canMsg.data_u8[4] = 0xFF;	// Reserved, fill with 0xFF
	canMsg.data_u8[5] = (uint8)(msgPGN & 0xFF);
	canMsg.data_u8[6] = (uint8)((msgPGN & 0xFF00) >> 8);
	canMsg.data_u8[7] = 0x00;                        //only the 2 LSbits are used and they are 0

	canMsg.id_u32 = getJ1939CanID(6, PGN_CM, groupExten, sourceAdr);
	canMsg.isXformat_b = 1;					//J1939TP is always extended format
	canMsg.dlc_u16 = totalBytes;
	sendCanMsg(&canMsg, CANBUS_2);
}

void J1939TP::sendTPBAM(TransportProtocolCanFrame* tpMsg)
{
	// SEND init CM BAM
	sendBAM(totalNumBytes, totalNumPackets, (tpMsg->id_u32 & 0xFF), (tpMsg->id_u32 & 0xFF00) >> 8, originalPGN);

	// Send each packet
	for (uint16 i = 0; i < totalNumPackets; i++)
	{
		packetCount++;
		if (bytesLeft < 7)
		{
			sendDT(bytesLeft, (originalId & 0xFF), (originalId & 0xFF00) >> 8);
			bytesLeft = 0;
		}
		else
		{
			sendDT(7, (originalId & 0xFF), (originalId & 0xFF00) >> 8);
			bytesLeft = bytesLeft - 7;
		}
	}
	// End of BAM
	pendingMsg = false;
}

// Public Functions
void J1939TP::addCanFilter(uint32 idSet, uint32 idMask, iCanReceiver* receiver)
{
	if (canFilterCount < MAX_CAN_FILTERS)
	{
		bool containFilter = false;
		if ((idSet == CAN_ID_CM) | (idSet == CAN_ID_DT))
		{
			containFilter = true;
		}
		else
		{
			for (uint32 index = 0; index < canFilterCount; index++)
			{
				if ((CanFilters[index].id_set == idSet) && (CanFilters[index].id_mask == idMask))
				{
					if (CanFilters[index].canReceiver == receiver)
					{
						containFilter = true;
					}
				}
			}
		}
		if (!containFilter)
		{
			// Add filter to list
			CanFilters[canFilterCount].id_set = idSet;
			CanFilters[canFilterCount].id_mask = idMask;
			CanFilters[canFilterCount].canReceiver = receiver;
			canFilterCount++;
		}
	}
}

void J1939TP::step()
{
	switch (TPState)
	{
		case WAIT_CTS:
		{
			// Wait until CTS is received
			break;
		}
		case SEND_DT:
		{
			packetCount++;
			if (packetCount <= totalNumPackets) // Any more packets to send
			{
				if (bytesLeft < 7)
				{
					sendDT(bytesLeft, (originalId & 0xFF), (originalId & 0xFF00) >> 8);
					bytesLeft = 0;
					TpResponseTimeout.start();
				}
				else
				{
					if ((packetCount % packetsBetweenCTS) == 0) // Check < num packets between CTS
					{
						TPState = WAIT_BETWEEN_CTS;
						TpResponseTimeout.start();
					}
					else
					{
						sendDT(7, (originalId & 0xFF), (originalId & 0xFF00) >> 8);
						bytesLeft = bytesLeft - 7;
					}
				}
			}
			else
			{
				TPState = WAIT_EOMACK;
			}
			break;
		}
		case WAIT_BETWEEN_CTS:
		{
			// Wait for 2 CTS before more packets can be sent
			break;
		}
		case WAIT_EOMACK:
		{
			// Wait for EOM
			break;
		}
		case EXIT:
		{
			break;
		}
		default:
			break;
	}
}

void J1939TP::canReceived(CanMessage* canMsg)
{
	// Use later to identify source and dest addrs.
	uint8 sourceAdr = (canMsg->id_u32) & 0xFF;
	uint8 destAdr = ((canMsg->id_u32) & 0xFF00) >> 8;
	uint32 msgPGN = (canMsg->data_u8[6] << 8) | (canMsg->data_u8[5]); // Gets PGN of TP msg

	// Checks if TP message
	switch (canMsg->id_u32 & CAN_ID_PGN_MASK)
	{
		case CAN_ID_CM: // CM
		{
			handleCM(canMsg, sourceAdr, destAdr, msgPGN);
			break;
		}
		case CAN_ID_DT: // DT
		{
			handleDT(canMsg, sourceAdr, destAdr);
			break;
		}
		default:
			break;
	}
}

void J1939TP::sendCanTPMsg(TransportProtocolCanFrame* tpMsg)
{
	if (TPState == EXIT && !pendingMsg)
	{
		totalNumBytes = tpMsg->dlc_u16;
		if (totalNumBytes < TRANSPORT_PROTOCOL_MAX_DATA)
		{
			// Figure out how many packets are needed for the message
			if (totalNumBytes % 7 == 0)
			{
				totalNumPackets = totalNumBytes / 7;
			}
			else
			{
				totalNumPackets = (totalNumBytes / 7) + 1;
			}

			// All information is copied from sender's TPmsg and put into member variable TPframe / member variables
			originalId = tpMsg->id_u32;
			originalPGN = (tpMsg->id_u32 & CAN_ID_PGN_MASK) >> 8;
			packetCount = 0;
			bytesLeft = totalNumBytes;

			for (uint32 index = 0; index < totalNumBytes; index++)
			{
				TPframe.data_u8[index] = tpMsg->data_u8[index];
			}

			if (((tpMsg->id_u32 & CAN_ID_PGN_MASK) >> 16) > PGN_PDU1_MAX)
			{
				pendingMsg = true;
				sendTPBAM(tpMsg);
			}
			else
			{
				pendingMsg = true;
				packetsBetweenCTS = totalNumPackets;

				// Request to send TP message
				sendRTS(totalNumBytes, totalNumPackets, (tpMsg->id_u32 & 0xFF), (tpMsg->id_u32 & 0xFF00) >> 8, (tpMsg->id_u32 & 0xFF0000) >> 8, packetsBetweenCTS);
				TpResponseTimeout.start();

				// Enter state machine
				TPState = WAIT_CTS;
			}
			SA = (tpMsg->id_u32 & 0xFF);
			DA = (tpMsg->id_u32 & 0xFF00) >> 8;
		}
	}
	else
	{
		sendNACK((tpMsg->id_u32 & 0xFF), 0xFF, (tpMsg->id_u32 & CAN_ID_PGN_MASK) >> 8);
	}
}

void J1939TP::HandleTimeout()
{
	sendAbort(SA, DA, originalPGN, ABORT_REASON_TIMEOUT);

	pendingMsg = false;
	pendingReceiveMsg = false;
	correctPgn = false;
	TPState = EXIT;
}

void J1939TP::HandleTimeoutWrapper(void* pt2Object)
{
	J1939TP* thisObject = (J1939TP*)pt2Object;
	thisObject->HandleTimeout();
}
