#include "PxRosTask.h"
#include "J1939TP.h"
#include "EosCanSend.h"
#include "CanMessage.h"

extern "C"
{
#include "pxdef.h"
}

#define PE_EVENT            EVENT( 0 )
#define IG_OFF_EVENT        EVENT( 1 )	
#define IG_ON_EVENT         EVENT( 2 )
#define GD_REQ_EVENT        EVENT( 3 )
#define GD_REC_EVENT        EVENT( 4 )
#define GD_BLK_EVENT        EVENT( 5 )
#define TIMEOUT0_EVENT		EVENT( 6 )
#define TIMEOUT1_EVENT		EVENT( 7 )
#define TIMEOUT2_EVENT		EVENT( 8 )
#define TIMEOUT3_EVENT		EVENT( 9 )
#define TIMEOUT4_EVENT		EVENT( 10 )
#define TIMEOUT5_EVENT		EVENT( 11 )
#define TIMEOUT6_EVENT		EVENT( 12 )
#define TIMEOUT7_EVENT		EVENT( 13 )
#define TIMEOUT8_EVENT		EVENT( 14 )
#define TIMEOUT9_EVENT		EVENT( 15 )
#define CAN_RCV0_EVENT		EVENT( 16 )
#define CAN_RCV1_EVENT		EVENT( 17 )
#define CAN_RCV2_EVENT		EVENT( 18 )
#define CAN_RCV3_EVENT		EVENT( 19 )
#define CAN_RCV4_EVENT		EVENT( 20 )
#define CAN_RCV5_EVENT		EVENT( 21 )
#define CAN_RCV6_EVENT		EVENT( 22 )
#define CAN_RCV7_EVENT		EVENT( 23 )
#define CAN_RCV8_EVENT		EVENT( 24 )
#define CAN_RCV9_EVENT		EVENT( 25 )

PxRosTask::PxRosTask( iTask* task, GdFunctionPtrs gdPtrs) :
	m_task(task), m_gdLib( gdPtrs ), m_Timer()
{
	m_tp = J1939TP(this);
	m_CanSend = CanSend(&m_tp);

}

void PxRosTask::init( TaskParams* params, taskEntryPtr taskEntryPtr )
{
	if(m_task->initOk())
	{
		//TODO should this be static??
		PxTask_t TaskId_ps = 0;
		PxError_t Err_e;
		
		for ( int i = 0; i < sizeof( myTaskName ) / sizeof( char ); i++ )
		{
			myTaskName[i] = params->name[i];
		}

		Err_e = CreateUsrtask( &TaskId_ps, params->name, taskEntryPtr, params->stacksize, params->priority );

		if( Err_e != PXERR_NOERROR )
		{
			PxPanic();
		}
	}
}

void PxRosTask::handleReceiveEvent(PxMsg_t msg_ps, SingleCanFrame* canMsg, uint8 receiverId)
{
	EosCanRcv_ts CanRcv_s;
	PxBcopy((PxUChar_t*)PxMsgGetData(msg_ps), (PxUChar_t*)&CanRcv_s, sizeof(EosCanRcv_ts));
	PxMsgRelease(&msg_ps);

	canMsg->id_u32 = CanRcv_s.id_u32;
	canMsg->isXformat_b = CanRcv_s.isXformat_b;
	canMsg->dlc_u16 = CanRcv_s.dlc_u16;
	canMsg->data_u8[0] = CanRcv_s.data_u8[0];
	canMsg->data_u8[1] = CanRcv_s.data_u8[1];
	canMsg->data_u8[2] = CanRcv_s.data_u8[2];
	canMsg->data_u8[3] = CanRcv_s.data_u8[3];
	canMsg->data_u8[4] = CanRcv_s.data_u8[4];
	canMsg->data_u8[5] = CanRcv_s.data_u8[5];
	canMsg->data_u8[6] = CanRcv_s.data_u8[6];
	canMsg->data_u8[7] = CanRcv_s.data_u8[7];
	canMsg->timestamp_u32 = CanRcv_s.timestamp_u32;

	m_canMbxReq[receiverId].canReceiver_ptr->canReceived(canMsg);
}

void PxRosTask::foreverLoop()
{
	PxEvents_t Ev;
	PxMsg_t msg_ps;

	//TODO block transfer somehow?

	// init periodic event
	PxPe_T Pe_s;
	PxPeInit( &Pe_s, m_task->getStepTime(), PE_EVENT );
	PxPeStart( &Pe_s );

	// init watchdog
	uint32 WatchDogId = 0;
	EosWdConnect_s32( &WatchDogId );

	// register for ignition calls
	EosIgReq_pts IgnitionReq_ps;
	IgnitionReq_ps = (EosIgReq_pts)0;
	EosIgReqInstall_s32( &IgnitionReq_ps, IG_OFF_EVENT, IG_ON_EVENT );

	m_task->initialize(this);
	bool reset = true;

	m_tp.init();

	SingleCanFrame canMsg;

	StartMailboxes();

	while( 1 )
	{
		Ev = PxAwaitEvents( PE_EVENT | IG_OFF_EVENT | IG_ON_EVENT | GD_REQ_EVENT | GD_REC_EVENT
						  | GD_BLK_EVENT | TIMEOUT0_EVENT | TIMEOUT1_EVENT | TIMEOUT2_EVENT | TIMEOUT3_EVENT 
						  | TIMEOUT4_EVENT | TIMEOUT5_EVENT | TIMEOUT6_EVENT | TIMEOUT7_EVENT | TIMEOUT8_EVENT 
						  | TIMEOUT9_EVENT | CAN_RCV0_EVENT | CAN_RCV1_EVENT | CAN_RCV2_EVENT | CAN_RCV3_EVENT 
						  | CAN_RCV4_EVENT | CAN_RCV5_EVENT | CAN_RCV6_EVENT | CAN_RCV7_EVENT | CAN_RCV8_EVENT 
						  | CAN_RCV9_EVENT );

		if( Ev & IG_OFF_EVENT )
		{
			m_task->ignitionOffEvent();
		}

		if( Ev & IG_ON_EVENT )
		{
			m_task->ignitionOnEvent();
			reset = true;
		}

		if( Ev & GD_REQ_EVENT )
		{
			while( !PxMsgReceive_NoWait( &msg_ps, MbxiGdReq_s.mbxi_mbx ) )
			{
				m_gdLib.processMessage( &msg_ps );
			}
		}

		if( Ev & GD_REC_EVENT )
		{
			while( !PxMsgReceive_NoWait( &msg_ps, MbxiGdRec_s.mbxi_mbx ) )
			{
				m_gdLib.processMessage( &msg_ps );
			}
		}

        if( Ev & GD_BLK_EVENT )
        {
            while( !PxMsgReceive_NoWait( &msg_ps, MbxiGdBlk_s.mbxi_mbx ) )
            {
                m_gdLib.processBlkMessage( &msg_ps );
            }
        }

		if (Ev & CAN_RCV0_EVENT)
		{
			while (!PxMsgReceive_NoWait(&msg_ps, m_canMbxReq[0].MbxiCanRcv_s.mbxi_mbx))
			{
				handleReceiveEvent(msg_ps, &canMsg, 0);
			}
		}

		if (Ev & CAN_RCV1_EVENT)
		{
			while (!PxMsgReceive_NoWait(&msg_ps, m_canMbxReq[1].MbxiCanRcv_s.mbxi_mbx))
			{
				handleReceiveEvent(msg_ps, &canMsg, 1);
			}
		}

		if (Ev & CAN_RCV2_EVENT)
		{
			while (!PxMsgReceive_NoWait(&msg_ps, m_canMbxReq[2].MbxiCanRcv_s.mbxi_mbx))
			{
				handleReceiveEvent(msg_ps, &canMsg, 2);
			}
		}

		if (Ev & CAN_RCV3_EVENT)
		{
			while (!PxMsgReceive_NoWait(&msg_ps, m_canMbxReq[3].MbxiCanRcv_s.mbxi_mbx))
			{
				handleReceiveEvent(msg_ps, &canMsg, 3);
			}
		}

		if (Ev & CAN_RCV4_EVENT)
		{
			while (!PxMsgReceive_NoWait(&msg_ps, m_canMbxReq[4].MbxiCanRcv_s.mbxi_mbx))
			{
				handleReceiveEvent(msg_ps, &canMsg, 4);
			}
		}

		if (Ev & CAN_RCV5_EVENT)
		{
			while (!PxMsgReceive_NoWait(&msg_ps, m_canMbxReq[5].MbxiCanRcv_s.mbxi_mbx))
			{
				handleReceiveEvent(msg_ps, &canMsg, 5);
			}
		}

		if (Ev & CAN_RCV6_EVENT)
		{
			while (!PxMsgReceive_NoWait(&msg_ps, m_canMbxReq[6].MbxiCanRcv_s.mbxi_mbx))
			{
				handleReceiveEvent(msg_ps, &canMsg, 6);
			}
		}

		if (Ev & CAN_RCV7_EVENT)
		{
			while (!PxMsgReceive_NoWait(&msg_ps, m_canMbxReq[7].MbxiCanRcv_s.mbxi_mbx))
			{
				handleReceiveEvent(msg_ps, &canMsg, 7);
			}
		}

		if (Ev & CAN_RCV8_EVENT)
		{
			while (!PxMsgReceive_NoWait(&msg_ps, m_canMbxReq[8].MbxiCanRcv_s.mbxi_mbx))
			{
				handleReceiveEvent(msg_ps, &canMsg, 8);
			}
		}

		if (Ev & CAN_RCV9_EVENT)
		{
			while (!PxMsgReceive_NoWait(&msg_ps, m_canMbxReq[9].MbxiCanRcv_s.mbxi_mbx))
			{
				handleReceiveEvent(msg_ps, &canMsg, 9);
			}
		}

		if( Ev & PE_EVENT ) // periodic event
		{
			EosWdAlive_s32( WatchDogId );
			m_gdLib.step( reset );

			m_task->step();

			m_tp.step(); // tp state update
			
			reset = false;

			if( m_task->shutdownOK( ) )
			{
				//shut it down!
				m_gdLib.gdKillAllRequests();
				m_gdLib.logOff();
                StopMailboxes();
				EosWdDisconnect_s32( &WatchDogId );
				EosIgBurryMe( &IgnitionReq_ps );
				EosWdConnect_s32( &WatchDogId );
				m_task->ignitionOnEvent();
                StartMailboxes();
				m_gdLib.logOn();
				reset = true;
			}
		}

		if(Ev & TIMEOUT0_EVENT)
		{
			timerEvent(0);
		}

		if(Ev & TIMEOUT1_EVENT)
		{
			timerEvent(1);
		}

		if(Ev & TIMEOUT2_EVENT)
		{
			timerEvent(2);
		}

		if(Ev & TIMEOUT3_EVENT)
		{
			timerEvent(3);
		}

		if(Ev & TIMEOUT4_EVENT)
		{
			timerEvent(4);
		}

		if(Ev & TIMEOUT5_EVENT)
		{
			timerEvent(5);
		}

		if(Ev & TIMEOUT6_EVENT)
		{
			timerEvent(6);
		}

		if(Ev & TIMEOUT7_EVENT)
		{
			timerEvent(7);
		}

		if(Ev & TIMEOUT8_EVENT)
		{
			timerEvent(8);
		}

		if(Ev & TIMEOUT9_EVENT)
		{
			timerEvent(9);
		}
	}
}

void PxRosTask::timerEvent(int eventNum)
{
	m_Timer[eventNum]->m_callbackFunction(m_Timer[eventNum]->m_pt2Object);
	if(m_Timer[eventNum]->m_cyclic)
	{
		m_Timer[eventNum]->reset();
	}
}

iGdCallbacks* PxRosTask::getGdCallbackReceiver()
{
	return &m_gdLib;
}

bool PxRosTask::registerGdApp( uint8 logicalNode, iGdClient* app )
{
	// init mailbox for gd requests
	PxMbxRequest_NoWait( &MbxiGdReq_s.mbxi_mbx, PXOpoolSystemdefault );
	MbxInfInit( &MbxiGdReq_s, MbxiGdReq_s.mbxi_mbx, PXMsgAnyMsg, GD_REQ_EVENT );
	MbxInfStart( &MbxiGdReq_s );

	// init mailbox for gd responses
	PxMbxRequest_NoWait( &MbxiGdRec_s.mbxi_mbx, PXOpoolSystemdefault );
	MbxInfInit( &MbxiGdRec_s, MbxiGdRec_s.mbxi_mbx, PXMsgAnyMsg, GD_REC_EVENT );
	MbxInfStart( &MbxiGdRec_s );

    // init mailbox for gd block transfer
    PxMbxRequest_NoWait( &MbxiGdBlk_s.mbxi_mbx, PXOpoolSystemdefault );
    MbxInfInit( &MbxiGdBlk_s, MbxiGdBlk_s.mbxi_mbx, PXMsgAnyMsg, GD_BLK_EVENT );
    MbxInfStart( &MbxiGdBlk_s );

	m_gdLib.init( logicalNode, app );

    gdBlkInit_s32( logicalNode, MbxiGdRec_s.mbxi_mbx, MbxiGdReq_s.mbxi_mbx, MbxiGdBlk_s.mbxi_mbx );
	gdLogon_s32( logicalNode );

	return true;
}

void PxRosTask::InitMailboxes(CanRequest* request, uint8 count, iCanReceiver* receiver)
{
	if (m_canMbxReq[MAX_RECVR_COUNT - 1].canReceiver_ptr != NULL)
	{
		asm volatile ("debug"); /* Too many receivers initialized */
		PxPanic();
		return;
	}

	for (int i = 0; i < MAX_RECVR_COUNT; i++)
	{
		if (m_canMbxReq[i].canReceiver_ptr == receiver)
		{
			asm volatile ("debug"); /* Same receiver initialized twice */
			PxPanic();
			return;
		}
		else if (m_canMbxReq[i].canReceiver_ptr == NULL)
		{
			MbxInfInit(&(m_canMbxReq[i].MbxiCanRcv_s), 0, PXMsgAnyMsg, CAN_RCV0_EVENT << i);
			m_canMbxReq[i].canReceiver_ptr = receiver;
			m_canMbxReq[i].canRequest_ptr = request;
			m_canMbxReq[i].messageCount = count;

			for (int index = 0; index < count; index++)
			{
				// When a request dlc > 8 it needs to be added to CanFilter list
				if (m_canMbxReq[i].canRequest_ptr[index].dlc_u16 > 8)
				{
					m_tp.addCanFilter(m_canMbxReq[i].canRequest_ptr[index].IdSet_u32, m_canMbxReq[i].canRequest_ptr[index].IdMask_u32, m_canMbxReq[i].canReceiver_ptr);
				}
			}
			break;
		}
	}
}

void PxRosTask::StartMailboxes(void)
{
	for (int canMbxIndex = 0; canMbxIndex < MAX_RECVR_COUNT; canMbxIndex++)
	{
		if (m_canMbxReq[canMbxIndex].canReceiver_ptr != NULL)
		{
			EosCanReq_ts eosRequest;

			for (int i = 0; i < m_canMbxReq[canMbxIndex].messageCount; i++)
			{
				eosRequest.IdSet_u32 = m_canMbxReq[canMbxIndex].canRequest_ptr[i].IdSet_u32;
				eosRequest.IdMask_u32 = m_canMbxReq[canMbxIndex].canRequest_ptr[i].IdMask_u32;
				eosRequest.dlc_u16 = m_canMbxReq[canMbxIndex].canRequest_ptr[i].dlc_u16;
				eosRequest.isXformat_b = m_canMbxReq[canMbxIndex].canRequest_ptr[i].isXformat_b;

				EosCanInstallReqMail_s32(m_canMbxReq[canMbxIndex].canRequest_ptr[i].bus_u8, &(m_canMbxReq[canMbxIndex].canRequest_ptr[i].canAdmin_ps), &eosRequest, &(m_canMbxReq[canMbxIndex].MbxiCanRcv_s).mbxi_mbx);
			}
			MbxInfStart(&(m_canMbxReq[canMbxIndex].MbxiCanRcv_s));
		}
	}
}

void PxRosTask::StopMailboxes(void)
{
	for (int canMbxIndex = 0; canMbxIndex < MAX_RECVR_COUNT; canMbxIndex++)
	{
		PxMsg_t Msg_ps;

		if (m_canMbxReq[canMbxIndex].canRequest_ptr != NULL) //null pointer check
		{
			MbxInfStop(&(m_canMbxReq[canMbxIndex].MbxiCanRcv_s));

			for (int i = 0; i < m_canMbxReq[canMbxIndex].messageCount; i++)
			{
				if (m_canMbxReq[canMbxIndex].canRequest_ptr[i].canAdmin_ps)
				{
					if (EosCanRemoveReq_s32(m_canMbxReq[canMbxIndex].canRequest_ptr[i].bus_u8, &(m_canMbxReq[canMbxIndex].canRequest_ptr[i].canAdmin_ps), (PxArg_t)0))
					{
						/*Error Handling*/
					}
				}
			}

			while (PxMsgReceive_NoWait(&Msg_ps, (m_canMbxReq[canMbxIndex].MbxiCanRcv_s).mbxi_mbx) == PXERR_NOERROR)
			{
				PxMsgRelease(&Msg_ps);
			}
		}
	}
}

void PxRosTask::registerTimer(TaskTimer *timer, void* pt2Object)
{
	PxError_t Err_e = PXERR_NOERROR;

	if(m_Timer[MAX_TIMER_COUNT - 1] != NULL)
	{
		asm volatile ("debug"); /* Too many timers initialized */
		PxPanic();
		return;
	}

	for(int i = 0; i < MAX_TIMER_COUNT; i++)
	{
		if(m_Timer[i] == timer)
		{
			asm volatile ("debug"); /* Same timer initialized twice */
			PxPanic();
			return;
		}
		else if(m_Timer[i] == NULL)
		{	
			timer->m_pt2Object = pt2Object;
			m_Timer[i] = timer;
			Err_e = PxToInit(&timer->m_To, timer->m_ticks, TIMEOUT0_EVENT << i);
			break;
		}
	}
	
	if( Err_e != PXERR_NOERROR )
	{
		PxPanic();
	}
}

void CanSend::SendCanMsg(CanMessage* canMsg, BusNode canBus)
{
	EosCan_te port = convertBusNode(canBus);

	if (canMsg->isXformat_b == true) // EXT CAN msg
	{
		if (canMsg->dlc_u16 <= 8)
		{
			EosCanSendExt_s32(port, canMsg->id_u32, canMsg->data_u8, canMsg->dlc_u16);
		}
		else
		{
			m_TP->sendCanTPMsg((TransportProtocolCanFrame*)canMsg);
		}
	}
	else
	{
		EosCanSend_s32(port, canMsg->id_u32, canMsg->data_u8, canMsg->dlc_u16);
	}
}

iCanSend* PxRosTask::getCanSend()
{
	return &m_CanSend;
}