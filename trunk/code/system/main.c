
#include "global_defs.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "init_tasks.h"
#include "led_flasher.h"




int main(void)
{
   // Init stuff
   InitTasks();

   // Start the FreeRTOS scheduler
   //vTaskStartScheduler();

   // If FreeRTOS stops for some reason, reinit the LED port and blink in an endless loop
   FlashLEDFallback();

   // If that stops, well then... I guess we're screwed
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
