#pragma once


#include "GdCallbacks.h"


template<class Task>
struct 
{
	requestIndexDataPtr		     getRequestIndexDataPtr() { return requestIndexData<;
	signalDataResponsePtr        getSignalDataResponsePtr();
	signalRequestErrorPtr	     getsignalRequestErrorPtr();
	signalHandshakePtr		     getsignalHandshakePtr();
	signalImmediateWritePtr      getsignalImmediateWritePtr();
	signalImmediateWriteErrorPtr getsignalImmediateWriteErrorPtr();
    gdBlkIdxReadPtr              getgdBlkIdxReadPtr();
    gdBlkIdxWritePtr             getgdBlkIdxWritePtr();
};
