#pragma once

extern "C"
{
#include "Eos.h"
#include "gd.h"
#include "gd_appl.h"
}

/* 
 * Implement this class on a class that needs to receive callbacks from the Gd library
 */
class iGdCallbacks
{

public:
    virtual ~iGdCallbacks() {};
    virtual bool GetIndexData( uint16 Index, GdData_ts *Data_ps ) = 0;
    virtual void SignalImmediateWrite( uint16 Index, GdData_ts *Data_ps, uint8 senderLN_u8 ) = 0;
    virtual void SignalDataResponse( uint16 Index, GdData_ts *Data_ps ) = 0;
    virtual void SignalRequestError( uint16, GdData_ts* ) = 0;
    virtual void SignalHandshake( uint16 Index, GdData_ts *Data_ps ) = 0;
    virtual void SignalImmediateWriteError( uint16 Index ) = 0;
    virtual sint16 GdBlkIdxRead_s16( uint16 arrayIdx, uint8 *rdData_p, uint16 rdSize ) = 0;
    virtual sint16 GdBlkIdxWrite_s16( uint16 arrayIdx, uint8 *wData_p, uint16 wSize ) = 0;
};
