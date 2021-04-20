#pragma once

extern "C"
{
#include "Project.h"
#include "EosStdTypeTC.h"
}


#define SINGLEFRAME_DATA_PER_FRAME  8
#define TRANSPORT_PROTOCOL_MAX_DATA (7 * 255)

class CanMessage
{
public:
	CanMessage() {};

	virtual ~CanMessage() {};

	uint32   id_u32;                ///< \brief identifier of the message
	boolean  isXformat_b;           ///< \brief TRUE if extended CAN message (29-bit id)
	uint16   dlc_u16;               ///< \brief data length code; amount of data-bytes
	uint8*   data_u8;				///< \brief pointer to the message data itself
	uint32   timestamp_u32;         ///< \brief time [ms] when this message was received

private:
	virtual void setData(uint8* pointer) = 0;
};


class SingleCanFrame : public CanMessage
{
public:
	SingleCanFrame()
	{
		setData(data);
	}

	SingleCanFrame(uint32 id_u32, boolean isXformat_b, uint16 dlc_u16)
	{
		this->id_u32 = id_u32;
		this->isXformat_b = isXformat_b;
		this->dlc_u16 = dlc_u16;

		setData(data);
	}

private:
	void setData(uint8* pointer) { data_u8 = pointer; }
	uint8 data[SINGLEFRAME_DATA_PER_FRAME];
};

class TransportProtocolCanFrame : public CanMessage
{
public:
	TransportProtocolCanFrame()
	{
		setData(data);
	}

private:
	void setData(uint8* pointer) { data_u8 = pointer; }
	uint8 data[TRANSPORT_PROTOCOL_MAX_DATA];
};

typedef enum
{
	CANBUS_1,  ///< \brief node 1
	CANBUS_2,  ///< \brief node 2
	CANBUS_3,  ///< \brief node 3
	CANBUS_4,  ///< \brief node 4
	/// not actually the "last" CAN node, but the lowest ID that is NOT a valid CAN node - useful in loops and for range checks
	CANBUS_Last
} BusNode;


