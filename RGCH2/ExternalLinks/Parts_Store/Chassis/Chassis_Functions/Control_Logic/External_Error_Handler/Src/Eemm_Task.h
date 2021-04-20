/**
 *  @file       emm_task.h
 *
 *  @brief      EMM Slave Task (PxROS).
 *
 *
 *  @section    Historie
 *
 *  2012-12-07 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 */

#ifndef __EEMM_TASK_H
#define __EEMM_TASK_H

void initEmmTask(void);

PxTask_t getEmmTaskId_ps(void);


#endif // __EEMM_TASK_H
