#pragma once

#include "iGdClient.h"
#include "iGdCallbacks.h"

extern "C"
{
#include "Eos.h"
#include "gd.h"
#include "gd_appl.h"
}

typedef boolean( *requestIndexDataPtr)(uint16, GdData_ts*);
typedef void   ( *signalDataResponsePtr)(uint16, GdData_ts*);
typedef void   ( *signalRequestErrorPtr )(uint16, GdData_ts*);
typedef void   ( *signalHandshakePtr )(uint16, GdData_ts*);
typedef void   ( *signalImmediateWritePtr )(uint16, GdData_ts*, uint8);
typedef void   ( *signalImmediateWriteErrorPtr )(uint16);
typedef sint16 ( *gdBlkIdxReadPtr )( uint16, uint8*, uint16 );
typedef sint16 ( *gdBlkIdxWritePtr )( uint16, uint8*, uint16 );

struct GdFunctionPtrs
{
	requestIndexDataPtr			 requestData;
	signalDataResponsePtr		 dataResponse;
	signalRequestErrorPtr		 requestError;
	signalHandshakePtr			 handshake;
	signalImmediateWritePtr		 immediateWrite;
	signalImmediateWriteErrorPtr immediateWriteError;
    gdBlkIdxReadPtr              blockRead;
    gdBlkIdxWritePtr             blockWrite;
};

template<class T>
boolean staticRequestIndexData( uint16 index, GdData_ts* data )
{
	return T::requestIndexData( index, data );
}

template<class T>
void staticSignalDataResponse( uint16 index, GdData_ts* data )
{
	T::signalDataResponse( index, data );
}

template<class T>
void staticSignalRequestError( uint16 index, GdData_ts* data )
{
	T::signalRequestError( index, data );
}

template<class T>
void staticSignalHandshake( uint16 index, GdData_ts* data )
{
	T::signalHandshake( index, data );
}

template<class T>
void staticSignalImmediateWrite( uint16 index, GdData_ts* data, uint8 source )
{
	T::signalImmediateWrite( index, data, source );
}

template<class T>
void staticSignalImmediateWriteError( uint16 index )
{
	T::signalImmediateWriteError( index );
}

template<class T>
sint16 staticGdBlkIdxRead( uint16 arrayIdx, uint8 *rdData_p, uint16 rdSize )
{
    return T::gdBlkIdxRead_s16( arrayIdx, rdData_p, rdSize );
}

template<class T>
sint16 staticGdBlkIdxWrite( uint16 arrayIdx, uint8 *wData_p, uint16 wSize )
{
    return T::gdBlkIdxWrite_s16( arrayIdx, wData_p, wSize );
}

template <class T>
struct GdFunctionPtrWrapper
{
	GdFunctionPtrWrapper(){};

	void setCallbackReceiver( iGdCallbacks* callbackReceiver )
	{
		m_callbackReceiver = callbackReceiver;
	}

	GdFunctionPtrs getPtrs()
	{
		GdFunctionPtrs retVal;

		retVal.requestData		   = &staticRequestIndexData< GdFunctionPtrWrapper<T> >;
		retVal.dataResponse		   = &staticSignalDataResponse< GdFunctionPtrWrapper<T> >;
		retVal.requestError		   = &staticSignalRequestError< GdFunctionPtrWrapper<T> >;
		retVal.handshake		   = &staticSignalHandshake< GdFunctionPtrWrapper<T> >;
		retVal.immediateWrite	   = &staticSignalImmediateWrite< GdFunctionPtrWrapper<T> >;
		retVal.immediateWriteError = &staticSignalImmediateWriteError< GdFunctionPtrWrapper<T> >;
        retVal.blockRead           = &staticGdBlkIdxRead< GdFunctionPtrWrapper<T> >;
        retVal.blockWrite          = &staticGdBlkIdxWrite< GdFunctionPtrWrapper<T> >;
        

		return retVal;
	}

	static boolean requestIndexData( uint16 index, GdData_ts* data )
	{
		return m_callbackReceiver->GetIndexData( index, data );
	}

	static void signalDataResponse( uint16 index, GdData_ts* data )
	{
		m_callbackReceiver->SignalDataResponse( index, data );
	}

	static void signalRequestError( uint16 index, GdData_ts* data )
	{
		m_callbackReceiver->SignalRequestError( index, data );
	}

	static void signalHandshake( uint16 index, GdData_ts* data )
	{
		m_callbackReceiver->SignalHandshake( index, data );
	}

	static void signalImmediateWrite( uint16 index, GdData_ts* data, uint8 source )
	{
		m_callbackReceiver->SignalImmediateWrite( index, data, source );
	}

	static void signalImmediateWriteError( uint16 index )
	{
		m_callbackReceiver->SignalImmediateWriteError( index );
	}

    static sint16 gdBlkIdxRead_s16( uint16 arrayIdx, uint8 *rdData_p, uint16 rdSize )
    {
        return m_callbackReceiver->GdBlkIdxRead_s16( arrayIdx, rdData_p, rdSize );
    }

    static sint16 gdBlkIdxWrite_s16( uint16 arrayIdx, uint8 *wData_p, uint16 wSize )
    {
        return m_callbackReceiver->GdBlkIdxWrite_s16( arrayIdx, wData_p, wSize );
    }

	static iGdCallbacks* m_callbackReceiver;
};

template<class T>
iGdCallbacks* GdFunctionPtrWrapper<T>::m_callbackReceiver = (iGdCallbacks*) NULL;


