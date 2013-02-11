#include "global_defs.h"
#include "stm32f4xx.h"
#include "init_tasks.h"

static GPIO_InitTypeDef PG8_INIT = { GPIO_Pin_8, GPIO_Mode_OUT, GPIO_Speed_2MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL };
static GPIO_InitTypeDef PC6_INIT = { GPIO_Pin_6, GPIO_Mode_OUT, GPIO_Speed_2MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL };


static void FlashLEDFallbackLoop(GPIO_TypeDef * port, uint16_t pin_bitfield, GPIO_InitTypeDef * init_struct, uint32_t periph_clk)
{
   uint32_t blink_counter;

   GPIO_DeInit(port);

   RCC_AHB1PeriphClockCmd(periph_clk, ENABLE);

   GPIO_Init(port, init_struct);

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
      FlashLEDFallbackLoop( GPIOG, GPIO_Pin_8, &PG8_INIT, RCC_AHB1Periph_GPIOG );
   }
   else
   {
      FlashLEDFallbackLoop( GPIOC, GPIO_Pin_6, &PC6_INIT, RCC_AHB1Periph_GPIOC );
   }

}
