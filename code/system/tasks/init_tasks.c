#include "global_defs.h"
#include "stm32f4xx.h"
#include "init_tasks.h"


bool IsRunningOnEvalBoard(void)
{
   return true;
}

static void InitPeripherals(void)
{
   NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
}

static void InitPorts(void)
{

}

static void CreateTasks(void)
{

}

void InitTasks(void)
{
   InitPorts();
   InitPeripherals();
   CreateTasks();
}
