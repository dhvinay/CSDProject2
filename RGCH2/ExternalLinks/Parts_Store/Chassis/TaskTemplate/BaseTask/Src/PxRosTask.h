#pragma once

#include "EntryPoint.h"
#include "iTaskRegistrar.h"
#include "iTask.h"
#include "gdLib.h"
#include <stdint.h>
#include "TaskTimer.h"
#include "J1939TP.h"
#include "EosCanSend.h"
#include "CanMessage.h"

extern "C"
{
#include "Eos.h"
#include "mbxinf.h"
#include <pxdef.h>
#include <pxfuncs.h>
#include <pxpe.h>
}

struct TaskParams
{
	char name[8];
	uint8 priority;
	unsigned int stacksize;
};

class CanSend : public iCanSend
{
public:
	// Default Constructor
	CanSend() {};
	// Constructor
	CanSend(J1939TP* tp) 
	{
		m_TP = tp;
	};

	void SendCanMsg(CanMessage* canMsg, BusNode canBus);

private:
	J1939TP* m_TP;
};

static const int MAX_TIMER_COUNT = 10; // If this changes, you must change #defines for events to match
static const uint16 MAX_RECVR_COUNT = 10; // If this changes, you have to change #defines for events to match number

class PxRosTask : private iTaskRegistrar
{
public:
	PxRosTask( iTask*, GdFunctionPtrs );
	virtual ~PxRosTask() {};

	void init( TaskParams*, taskEntryPtr );

	void foreverLoop();

	iGdCallbacks* getGdCallbackReceiver();

	iCanSend* getCanSend(void);

private:
	bool registerGdApp( uint8 logicalNode, iGdClient* app );

    void InitMailboxes( CanRequest * request, uint8 count, iCanReceiver * receiver );
    
	void StartMailboxes(void);
    
	void StopMailboxes(void);

	void registerTimer(TaskTimer *timer, void* pt2Object);

	void handleReceiveEvent(PxMsg_t msg_ps, SingleCanFrame* canMsg, uint8 receiverId);

	void timerEvent(int eventNum);

	iTask* m_task;
	GdLib m_gdLib;

	MbxInf_T MbxiGdReq_s;
	MbxInf_T MbxiGdRec_s;
    MbxInf_T MbxiGdBlk_s;
    
	char myTaskName[8];

	TaskTimer *m_Timer[MAX_TIMER_COUNT];

	typedef struct
	{
		CanRequest* canRequest_ptr;
		uint8 messageCount;
		iCanReceiver* canReceiver_ptr;
		MbxInf_T MbxiCanRcv_s;
	} CanRecReqMbx_ts;

	CanRecReqMbx_ts m_canMbxReq[MAX_RECVR_COUNT];

	J1939TP m_tp;

	CanSend m_CanSend;
};



