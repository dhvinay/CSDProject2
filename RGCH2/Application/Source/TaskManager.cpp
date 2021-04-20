#include "TaskManager.h"

#include "TaskScheduler.h"

//Module Header File Includes
#include "..\..\ExternalLinks\Parts_Store\Chassis\Chassis_Functions\Control_Logic\High_Clearance\Src\HighClearance_task.h"
///////////////////////////

TaskParams highClearance = { "HC", 3, 512 };

Task <HighClearance::highClearanceTask> HC;

void initTaskManager()
{
	HC.init( &highClearance );
}

