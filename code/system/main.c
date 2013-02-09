
#include "global_defs.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

//#include "FreeRTOS.h"
//#include "task.h"
//#include "timers.h"
//#include "semphr.h"

static GPIO_InitTypeDef PG6_INIT = { GPIO_Pin_6, GPIO_Mode_OUT, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_UP };
static GPIO_InitTypeDef PG8_INIT = { GPIO_Pin_8, GPIO_Mode_OUT, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_UP };

int main(void)
{
   uint32_t blink_counter;

   // Init stuff
   //SystemInit();
   NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

   GPIO_DeInit(GPIOG);

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

   GPIO_Init(GPIOG, &PG6_INIT);
   GPIO_Init(GPIOG, &PG8_INIT);

   /* Start the scheduler. */
   vTaskStartScheduler();

   while (TRUE)
   {
      // Blink real creepy to indicate that FreeRTOS stopped working

      for (blink_counter = 0; blink_counter < 0x0001FFFF; blink_counter++)
      {
         // Turn on LED
         //GPIO_SetBits(GPIOG, GPIO_Pin_6 | GPIO_Pin_8);
         GPIO_SetBits(GPIOG, GPIO_Pin_8);
      }

      for (blink_counter = 0; blink_counter < 0x001FFFFF; blink_counter++)
      {
         // Turn off LED
         //GPIO_ResetBits(GPIOG, GPIO_Pin_6 | GPIO_Pin_8);
         GPIO_ResetBits(GPIOG, GPIO_Pin_8);
      }
   }



   return 0;
}


void vApplicationTickHook( void )
{

}

void vApplicationMallocFailedHook( void )
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created.  It is also called by various parts of the
   demo application.  If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
   taskDISABLE_INTERRUPTS();
   for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
   task.  It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()).  If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
   ( void ) pcTaskName;
   ( void ) pxTask;

   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
   function is called if a stack overflow is detected. */
   taskDISABLE_INTERRUPTS();
   for( ;; );
}
/*-----------------------------------------------------------*/
