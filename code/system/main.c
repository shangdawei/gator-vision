
#include "global_defs.h"
#include "stm32f4xx.h"

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

   while (TRUE)
   {
      for (blink_counter = 0; blink_counter < 0x0001FFFF; blink_counter++)
      {
         // Turn on LED
         GPIO_SetBits(GPIOG, GPIO_Pin_6 | GPIO_Pin_8);
      }

      for (blink_counter = 0; blink_counter < 0x001FFFFF; blink_counter++)
      {
         // Turn off LED
         GPIO_ResetBits(GPIOG, GPIO_Pin_6 | GPIO_Pin_8);
      }
   }



   return 0;
}
