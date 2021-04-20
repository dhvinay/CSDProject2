#ifndef GDAPP_H
#define GDAPP_H

extern "C"
{
#include "Eos.h"
#include "gd.h"
#include "gd_appl.h"
#include "gdx.h"
#include "gdblk.h"
};

class iGdClient
{
	public:
		typedef enum
		{
			ECRR,
			TCRR
		} RequestType_te;

		typedef struct GdRequests_ts
		{
			uint16 IndexToRequest;
			GdXRequestData_ts RequestData;
			bool RequestSent;
			RequestType_te Type;
		} GdRequests_ts;

    public:
		virtual ~iGdClient(){};

        virtual void getMyLocList(GdLocList_ts* locList[], uint16* count) = 0;
        virtual void getMyLocListBlk( GdBlkIndex_ts * locList[], uint16 * count ) = 0;
        virtual void getRequestGdList(GdRequests_ts* requestList[], uint16* count) = 0;
        virtual sint16 gdBlkIdxRead_s16( uint16 arrayIdx, uint8 *rdData_p, uint16 rdSize ) = 0;
        virtual sint16 gdBlkIdxWrite_s16( uint16 arrayIdx, uint8 *wData_p, uint16 wSize ) = 0;
		virtual bool getIndexData( uint16 index , GdData_ts *data_ps ) = 0;
		virtual void signalImmediateWrite( uint16 index , GdData_ts *data_ps , uint8 senderLN_u8 ) = 0;
		virtual void signalDataResponse( uint16 index , GdData_ts *data_ps ) = 0;
        virtual void signalHandshake( uint16 index , GdData_ts *data_ps ) = 0;
        virtual void signalImmediateWriteError( uint16 index ) = 0;
        virtual void step() = 0;

	protected:
	private:

};

#endif // GDAPP_H
