#include "global_defs.h"
#include "FreeRTOS.h"
#include "projdefs.h"
#include "stm32f4xx.h"
#include "init_tasks.h"
#include "led_flasher.h"
#include "portmacro.h"
#include "timers.h"


static void LEDFlasherTimerCallback( xTimerHandle xTimer );

static bool LED_On;

static void FlashLEDFallbackLoop(GPIO_TypeDef * port, uint16_t pin_bitfield)
{
   uint32_t blink_counter;

   while (true)
   {
      // Blink real creepy-like to indicate that FreeRTOS stopped working

      for (blink_counter = 0; blink_counter < 0x0001FFFF; blink_counter++)
      {
         // Turn on LED
         GPIO_SetBits(port, pin_bitfield);
      }

      for (blink_counter = 0; blink_counter < 0x001FFFFF; blink_counter++)
      {
         // Turn off LED
         GPIO_ResetBits(port, pin_bitfield);
      }
   }
}

void FlashLEDFallback(void)
{
   if (IsRunningOnEvalBoard())
   {
      FlashLEDFallbackLoop( GPIOG, GPIO_Pin_8 );
   }
   else
   {
      FlashLEDFallbackLoop( GPIOC, GPIO_Pin_6 );
   }

}


portTASK_FUNCTION( LED_Flash_Task, params )
{
   xTimerHandle flash_timer;
   portTickType last_wake;

   // Attempt to create the timer
   flash_timer = xTimerCreate(
         ( const signed char * const ) "led_flasher_timer",
         500,     // 500 ticks = 500 ms, assuming 1 ms/tick
         pdTRUE,  // Auto Reload timer
         NULL,    // We don't need an ID as this timer has exclusive use of the callback
         LEDFlasherTimerCallback );

   configASSERT( flash_timer != NULL );

   if ( flash_timer != NULL )
   {
      // Start the timer
      xTimerStart( flash_timer, 0 );
   }

   LED_On = true;
   last_wake = xTaskGetTickCount();

   while (true)
   {
      vTaskDelayUntil(&last_wake, 5);

      if ( IsRunningOnEvalBoard() )
      {
         if (LED_On)
         {
            GPIO_SetBits( GPIOG, GPIO_Pin_6 );
         }
         else
         {
            GPIO_ResetBits( GPIOG, GPIO_Pin_6 );
         }
      }
      else
      {
         if (LED_On)
         {
            GPIO_SetBits( GPIOC, GPIO_Pin_6 );
         }
         else
         {
            GPIO_ResetBits( GPIOC, GPIO_Pin_6 );
         }
      }
   }

}

// Called every 500ms after timer starts
static void LEDFlasherTimerCallback( xTimerHandle xTimer )
{
   LED_On = !LED_On;
}
