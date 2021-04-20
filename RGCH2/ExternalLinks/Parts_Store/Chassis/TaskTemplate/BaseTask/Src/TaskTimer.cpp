#include "TaskTimer.h"


TaskTimer::TaskTimer(long msTime, void (*callbackFunction)(void* pt2Object), bool cyclic)
	: m_callbackFunction(callbackFunction), 
	m_cyclic(cyclic)
{
	m_ticks = MSEC(msTime);
}

int TaskTimer::start()
{
	PxError_t Err_e;
	Err_e = PxToStart(&m_To);
	if( Err_e != PXERR_NOERROR )
	{
		return -1;
	}
	return 1; 
}

int TaskTimer::stop()
{
	PxError_t Err_e;
	Err_e = PxToStop(&m_To);
	if( Err_e != PXERR_NOERROR )
	{
		return -1;
	}
	return 1; 
}

int TaskTimer::reset()
{
	PxError_t Err_e1;
	PxError_t Err_e2;
	Err_e1 = PxToStop(&m_To);
	Err_e2 = PxToStart(&m_To);
	if( (Err_e1 != PXERR_NOERROR) || (Err_e2 != PXERR_NOERROR) )
	{
		return -1;
	}
	return 1;
}
