#include "GdLib.h"

extern "C"
{
#include "Eos.h"
#include "util_eosGd.h"
}

GdLib::GdLib( GdFunctionPtrs ptrs)
	: m_gdFunctionPtrs( ptrs )
{

}

void GdLib::init(uint8 logicalNode, iGdClient* myApp)
{
	GdLocList_ts* locListptr;
    GdBlkIndex_ts* locListBlkptr;
	uint16 locListSize;
    uint16 locListBlkSize;
	m_logicalNode = logicalNode;
	m_gdApp = myApp;

	myApp->getMyLocList(&locListptr, &locListSize);
    myApp->getMyLocListBlk( &locListBlkptr, &locListBlkSize );
	gdInitApplStruct(&m_GdAppl_s, locListptr, locListSize);
	gdBlkInitApplStruct(&m_GdBlkAppl_s, locListBlkptr, locListBlkSize );

	gdConnectIndexData(&m_GdAppl_s, m_gdFunctionPtrs.requestData);
	gdConnectImmediateWrite(&m_GdAppl_s, m_gdFunctionPtrs.immediateWrite);
	gdConnectDataResponse(&m_GdAppl_s, m_gdFunctionPtrs.dataResponse);
    gdConnectHandshake( &m_GdAppl_s, m_gdFunctionPtrs.handshake );
    gdConnectImmediateWriteError( &m_GdAppl_s, m_gdFunctionPtrs.immediateWriteError );
	gdBlkConnectRead(&m_GdBlkAppl_s, m_gdFunctionPtrs.blockRead );
	gdBlkConnectWrite(&m_GdBlkAppl_s, m_gdFunctionPtrs.blockWrite );

	for( uint16 Iteration = 0; Iteration < locListSize; Iteration++)
	{
		gdAddIndexToApplStruct_s32(&m_GdAppl_s, locListptr[Iteration].index_u16);
	}

    for( uint16 Iteration = 0; Iteration < locListBlkSize; Iteration++ )
    {
        gdBlkAddIndexToApplStruct_s32( &m_GdBlkAppl_s, locListBlkptr[Iteration].gdIndex_u16, GD_API_NO_ERROR, locListBlkptr[Iteration].data_pu8, locListBlkptr[Iteration].dataSize_u16 );
    }
}

void GdLib::step(bool ResetRequests)
{
	sendGdRequests(ResetRequests);
	gdServeLoclist(&m_GdAppl_s );
    m_gdApp->step();
}

void GdLib::processMessage(PxMsg_t *Msg_pps)
{
	gdProcessMessage(&m_GdAppl_s, Msg_pps);
}

void GdLib::processBlkMessage( PxMsg_t *Msg_pps )
{
    gdBlkProcessMessage( &m_GdBlkAppl_s, Msg_pps );
}

uint32 GdLib::getLocListCount(void)
{
	return gdGetLoclistCount_u32(&m_GdAppl_s );
}

void GdLib::gdKillAllRequests(void)
{
	gdKillAllRequests_s32( m_logicalNode );
}


void GdLib::logOff()
{
	gdLogoff_s32( m_logicalNode );
}

void GdLib::logOn()
{
	gdLogon_s32( m_logicalNode );
}

/* Request data from another node */
bool GdLib::sendGdRequests(bool reset_b)
{
	const sint32 countMax_cs32 = 1; // max. 1 request per cycle
	sint32 count_s32 = 0;
	uint16 iterator;
	uint16 requestCount;
	iGdClient::GdRequests_ts* requests;

	m_gdApp->getRequestGdList(&requests, &requestCount);

	for (iterator = 0; iterator < requestCount && count_s32 < countMax_cs32; iterator++)
	{
		if (reset_b || !(isNodeAliveByIndex(requests[iterator].IndexToRequest)))
		{
			gdxResetRequestData(&requests[iterator].RequestData);
			requests[iterator].RequestSent = FALSE;
		}
		else
		{
			if (!requests[iterator].RequestSent)
			{
				if (requests[iterator].Type == iGdClient::ECRR)
				{
					if (!gdxSendRequestECRR_s32( m_logicalNode, &requests[iterator].RequestData,
						requests[iterator].IndexToRequest, FALSE, 0, 0))
					{
						requests[iterator].RequestSent = TRUE;
						count_s32++;
					}
				}
				else if (requests[iterator].Type == iGdClient::TCRR)
				{
					if (!gdxSendRequestTCRR_s32( m_logicalNode, &requests[iterator].RequestData,
						requests[iterator].IndexToRequest, 100))
					{
						requests[iterator].RequestSent = TRUE;
						count_s32++;
					}
				}
			}
		}
	}

	return iterator == requestCount;
}

bool GdLib::GetIndexData( uint16 Index, GdData_ts * Data_ps )
{
	bool retVal = false;
	
	/* Forward callback call onto to iGdApp implementation */
	if( m_gdApp )
	{
		retVal = m_gdApp->getIndexData( Index, Data_ps );
	}

	return retVal;
}

void GdLib::SignalImmediateWrite( uint16 Index, GdData_ts * Data_ps, uint8 senderLN_u8 )
{
	/* Forward callback call onto to iGdApp implementation */
	if( m_gdApp )
	{
		m_gdApp->signalImmediateWrite(Index, Data_ps, senderLN_u8);
	}
}

void GdLib::SignalDataResponse( uint16 Index, GdData_ts * Data_ps )
{
	/* Forward callback call onto to iGdApp implementation */
	if( m_gdApp )
	{
		m_gdApp->signalDataResponse( Index, Data_ps );
	}
}

void GdLib::SignalRequestError( uint16, GdData_ts * )
{
	/* Unimplemented by iGdApp, do nothing */
}

void GdLib::SignalHandshake( uint16 Index, GdData_ts * Data_ps )
{
	if( m_gdApp )
    {
        m_gdApp->signalHandshake( Index, Data_ps );
    }
}

void GdLib::SignalImmediateWriteError( uint16 Index )
{
    if( m_gdApp )
    {
        m_gdApp->signalImmediateWriteError( Index );
    }
}

sint16 GdLib::GdBlkIdxRead_s16( uint16 Index, uint8* rdData_p, uint16 rdSize )
{
    sint16 retVal = -1;

    if( m_gdApp )
    {
        retVal = m_gdApp->gdBlkIdxRead_s16( Index, rdData_p, rdSize );
    }

    return retVal;
}

sint16 GdLib::GdBlkIdxWrite_s16( uint16 Index, uint8* wData_p, uint16 wSize )
{
    sint16 retVal = -1;

    if( m_gdApp )
    {
        retVal = m_gdApp->gdBlkIdxWrite_s16( Index, wData_p, wSize );
    }

    return retVal;
}
