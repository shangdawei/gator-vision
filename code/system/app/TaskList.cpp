/*
 * TaskList.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: Jeff
 */

#include "TaskList.h"

TaskList * TaskList::GlobalTasks;

TaskList::TaskList()
{
   NetServiceManagerTask = new NetServiceManager();
   LEDFlasherTask = new LEDFlasher(LED_PORT, LED_PIN, 500);

   NetServiceManagerTask->Create("NetServices", configMINIMAL_STACK_SIZE, 3);
   LEDFlasherTask->Create("LEDFlasher", configMINIMAL_STACK_SIZE, 2);

}

TaskList::~TaskList()
{

}

bool TaskList::HardwareInit()
{
   // Set up priorities to support FreeRTOS
   NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

   return true;
}

void TaskList::Run()
{
   // Nothing to do yet, just return
   this->Delete();
}



uint16_t TaskList::MappedSetting(uint16_t eval_num, uint16_t reva_num)
{
   uint16_t retval;

   if (RunningOnEvalBoard())
   {
      retval = eval_num;
   }
   else
   {
      retval = reva_num;
   }

   return retval;
}


GPIO_TypeDef * TaskList::MappedSetting(GPIO_TypeDef * eval_port, GPIO_TypeDef * reva_port)
{
   GPIO_TypeDef * retval;

   if (RunningOnEvalBoard())
   {
      retval = eval_port;
   }
   else
   {
      retval = reva_port;
   }

   return retval;
}


bool TaskList::RunningOnEvalBoard()
{
   uint32_t device_id_1 = *((uint32_t *)0x1FFF7A10);
   uint32_t device_id_2 = *((uint32_t *)0x1FFF7A14);
   uint32_t device_id_3 = *((uint32_t *)0x1FFF7A18);

   return ((device_id_1 == 0x002F002A) && (device_id_2 == 0x31314712) && (device_id_3 == 0x30343630));
}

