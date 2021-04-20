#ifndef TASK_H
#define TASK_H

#include "iTaskRegistrar.h"

class iTask
{
public:

	virtual ~iTask() {};

	virtual void initialize(iTaskRegistrar*) = 0;
    virtual void step(void) = 0;
    virtual void ignitionOnEvent(void) = 0;
	virtual void ignitionOffEvent(void) = 0;
    virtual bool shutdownOK( void ) = 0;
	virtual int getStepTime(void) = 0;
	virtual bool initOk(void) = 0;
};

#endif // TASK_H
