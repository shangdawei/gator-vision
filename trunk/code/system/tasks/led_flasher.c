#include "global_defs.h"
#include "stm32f4xx.h"
#include "init_tasks.h"


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
