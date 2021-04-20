#pragma once

extern "C"
{
#include "Project.h"
}

#include "CanMessage.h"
#include "iTaskRegistrar.h"
#include "TaskTimer.h"

static const uint16 MAX_CAN_FILTERS = 8;

class J1939TP : public iCanReceiver
{
public:
	J1939TP();

	J1939TP(iTaskRegistrar* registrar);

	virtual ~J1939TP();

	void addCanFilter(uint32 idSet, uint32 idMask, iCanReceiver* canReceiver);

	void canReceived(CanMessage* canMsg);

	void sendCanTPMsg(TransportProtocolCanFrame* tpMsg);
	
	void step(void);

	void init(void);

	static void HandleTimeoutWrapper( void * pt2Object );

	void HandleTimeout();
	
private:

	void handleDT(CanMessage* canMsg, uint8 myAdr, uint8 senderAdr);

	void handleCM(CanMessage* canMsg, uint8 myAdr, uint8 senderAdr, uint32 msgPGN);

	void completeTPMsg(CanMessage* canMsg);

	uint32 getJ1939CanID(uint8 priority, uint8 PduFormat, uint8 DestAddress, uint8 SrcAddress);

	bool filterCheck(CanMessage* canMsg);

	bool verifySADA(uint8 sourceAdr, uint8 destAdr);

	// Sending TPCM messages
	void sendACK(uint8 myAdr, uint8 destAdr, uint16 msgPGN);

	void sendNACK(uint8 myAdr, uint8 destAdr, uint16 msgPGN);

	void sendCTS(uint8 nextPacket, uint8 myAdr, uint8 destAdr, uint16 msgPGN);

	void sendRTS(uint16 totalBytes, uint8 totalPackets, uint8 sourceAdr, uint8 destAdr, uint16 msgPGN, uint8 packetsPerGroup);

	void sendEndOfMsgAck(uint8 myAdr, uint8 destAdr, uint16 msgPGN);

	void sendAbort(uint8 myAdr, uint8 destAdr, uint16 msgPGN, uint8 abortReason);

	void sendDT(uint8 numBytes, uint8 sourceAdr, uint8 destAdr);

	void sendTPBAM(TransportProtocolCanFrame* tpMsg);

	void sendBAM(uint16 totalBytes, uint8 totalPackets, uint8 sourceAdr, uint8 groupExten, uint16 msgPGN);

	// Local Member Variables
	uint8 totalNumPackets;
	uint16 totalNumBytes;
	uint8 packetCount; // Maintain the number of packets that have been received
	uint8 packetsBetweenCTS;
	bool bamMsg; // False if peer-to-peer connection
	bool pendingMsg;
	TransportProtocolCanFrame TPframe;
	bool correctPgn;
	uint32 originalId;
	uint32 originalPGN;
	// Filtering / Requests
	uint8 canFilterCount;
	iTaskRegistrar::CanRequest CanRequests[MAX_CAN_FILTERS];
	// State Machine Sending TP messages
	uint32 bytesLeft;
	bool pendingReceiveMsg;
	uint8 DA;
	uint8 SA;
	TaskTimer TpResponseTimeout;
	TaskTimer TpDtTimeout;

	typedef enum
	{
		WAIT_CTS,
		SEND_DT,
		WAIT_EOMACK,
		WAIT_BETWEEN_CTS,
		EXIT
	} TPSendState_te;

	TPSendState_te TPState;

	typedef struct
	{
		uint32 id_set;
		uint32 id_mask;
		iCanReceiver* canReceiver;
	} CanFilter;

	CanFilter CanFilters[MAX_CAN_FILTERS];

	iTaskRegistrar* m_taskRegistrar;

	uint8 temp_data[TRANSPORT_PROTOCOL_MAX_DATA];
};
