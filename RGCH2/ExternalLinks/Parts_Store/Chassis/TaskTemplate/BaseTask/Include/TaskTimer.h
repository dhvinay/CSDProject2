#pragma once
extern "C"
{
#include "pxdef.h"
#include "pxto.h"
#include "Eos.h"
}

/*This class creates a timer object which can be used as a repeating timer or a timeout for the specified number of milliseconds. 
Once the timer runs out the callback function it is given is called. 
If the cyclic variable is true then the timer restarts, otherwise it would need to be restarted manually.*/

class TaskTimer
{
	friend class PxRosTask;
public:

	TaskTimer(long msTime, void (*callbackFunction)(void* pt2Object), bool cyclic = false);

	int start();
	int stop();
	int reset();

private:

	PxTo_T m_To;
	PxTicks_t m_ticks;
	void (*m_callbackFunction)(void* pt2Object);
	bool m_cyclic;
	void* m_pt2Object;
};

