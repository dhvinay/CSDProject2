#pragma once

#include "EntryPoint.h"
#include "PxRosTask.h"

template<class Task>
struct EntryPointWrapper
{
public:
	EntryPointWrapper( PxRosTask* instance )
	{
		staticInstance = instance;
	}

	taskEntryPtr entryPtr()
	{
		return &entryPoint<EntryPointWrapper<Task> >;
	}

	static void memberEntryPoint()
	{
		staticInstance->foreverLoop();
	}

private:
	static PxRosTask* staticInstance;
};

template<class Task>
PxRosTask* EntryPointWrapper<Task>::staticInstance = (PxRosTask*) NULL;
