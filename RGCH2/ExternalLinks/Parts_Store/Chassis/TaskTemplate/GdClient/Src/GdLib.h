#ifndef GDLIB_H
#define GDLIB_H

#include "iGdClient.h"
#include "GdCallbacks.h"
#include "iGdCallbacks.h"


extern "C"
{
#include "Eos.h"
#include "gd.h"
#include "gd_appl.h"
#include "gdblk_appl.h"
#include "gdx.h"
};

class GdLib : public iGdCallbacks
{
public:
	GdLib( GdFunctionPtrs ptrs );

	void init( uint8 logicalNode, iGdClient* );

    void step(bool ResetRequests);
    void processMessage(PxMsg_t *Msg_pps);
    void processBlkMessage( PxMsg_t * Msg_pps );
	uint32 getLocListCount(void);

	void gdKillAllRequests(void);
	void logOff();
	void logOn();





		// Inherited via iGdCallbacks
public:
		bool GetIndexData( uint16 Index, GdData_ts * Data_ps );
		void SignalImmediateWrite( uint16 Index, GdData_ts * Data_ps, uint8 senderLN_u8 );
		void SignalDataResponse( uint16 Index, GdData_ts * Data_ps );
		void SignalRequestError( uint16, GdData_ts * );
		void SignalHandshake( uint16 Index, GdData_ts * Data_ps );
		void SignalImmediateWriteError( uint16 Index );
        sint16 GdBlkIdxRead_s16( uint16 arrayIdx , uint8 *rdData_p , uint16 rdSize );
        sint16 GdBlkIdxWrite_s16( uint16 arrayIdx , uint8 *wData_p , uint16 wSize );


private:
	GdApplStruct_ts  m_GdAppl_s;
    GdBlkApplAdmin_ts m_GdBlkAppl_s;
	iGdClient* m_gdApp;
	uint8 m_logicalNode;
	GdFunctionPtrs m_gdFunctionPtrs;

	bool sendGdRequests(bool reset_b);


};

#endif // GDLIB_H
