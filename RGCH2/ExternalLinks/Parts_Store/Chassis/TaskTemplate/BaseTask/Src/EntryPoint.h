#pragma once

#include "pxdef.h"

typedef void( *taskEntryPtr )(PxTask_t TaskId_ps, PxMbx_t MbxId_ps, PxEvents_t Events);

template<class TaskObject>
static void entryPoint( PxTask_t TaskId_ps, PxMbx_t MbxId_ps, PxEvents_t Events )
{
	(void)TaskId_ps;
	(void)MbxId_ps;
	(void)Events;
	TaskObject::memberEntryPoint();
}
