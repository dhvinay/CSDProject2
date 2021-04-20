#pragma once

#include "EntryPointWrapper.h"
#include "GdCallbacks.h"
#include "PxRosTask.h"


template<class Logic>
class Task
{
public:

	Task() : m_logic(), gdWrapper(), m_pxRosTask( &m_logic, gdWrapper.getPtrs() ), wrapper( &m_pxRosTask )
	{
		gdWrapper.setCallbackReceiver( m_pxRosTask.getGdCallbackReceiver() );
	}

	void init( TaskParams* params )
	{
		m_pxRosTask.init( params, wrapper.entryPtr() );

	};

private:
	Logic m_logic;
	GdFunctionPtrWrapper<Logic> gdWrapper;

	PxRosTask m_pxRosTask;
	EntryPointWrapper<Logic> wrapper;
};
