#pragma once

#include "iGdClient.h"
#include "CanMessage.h"

class TaskTimer;

class iCanReceiver
{
public:
	virtual void canReceived( CanMessage* message ) = 0;
};

class iCanSend
{
public:
	virtual void SendCanMsg(CanMessage* canMsg, BusNode canBus) = 0;
};

class iTaskRegistrar
{
public:
	virtual bool registerGdApp( uint8 logicalNode, iGdClient* app ) = 0;
	virtual void registerTimer(TaskTimer *timer, void* pt2Object) = 0;

	struct CanRequest
	{
		EosCan_te       bus_u8;
		uint32          IdMask_u32;     ///< \brief Identifier mask for receive-message
		uint32          IdSet_u32;      ///< \brief identifier of the message
		boolean         isXformat_b;    ///< \brief TRUE if extended CAN message (29-bit id)
		uint16          dlc_u16;        ///< \brief data length code; set it > CAN_DATA_MAX to say "don't care"
        EosCanAdmin_pts canAdmin_ps;    ///< \brief struct used to Install or Remove this message from the mailbox
	};

    virtual void InitMailboxes( CanRequest* request, uint8 count, iCanReceiver* receiver ) = 0;

	virtual iCanSend* getCanSend(void) = 0;
};



