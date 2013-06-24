/*
 * TaskList.h
 *
 *  Created on: Jun 23, 2013
 *      Author: Jeff
 */

#ifndef TASKLIST_H_
#define TASKLIST_H_

#include "global_defs.h"
#include "AManagedTask.h"
#include "LEDFlasher.h"
#include "port_defs.h"
#include "stm32f4xx.h"

class TaskList : public AManagedTask
{
public:
   TaskList();
   void Run();
   bool HardwareInit();
   virtual ~TaskList();

   static TaskList * GlobalTasks;
   LEDFlasher * LEDFlasherTask;

private:
   GPIO_TypeDef * MappedSetting(GPIO_TypeDef * eval_port, GPIO_TypeDef * reva_port);
   uint16_t MappedSetting(uint16_t eval_uint, uint16_t reva_uint);
   static bool RunningOnEvalBoard();
};

#endif /* TASKLIST_H_ */
