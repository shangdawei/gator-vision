/*
 * LEDFlasher.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: Jeff
 */

#include "LEDFlasher.h"

LEDFlasher::LEDFlasher(GPIO_TypeDef * port, uint16_t pin, portTickType flash_rate)
{
   LEDPort = port;
   LEDPin = pin;
   ToggleRate = flash_rate;
   LEDOnState = false;
}

void LEDFlasher::Run()
{
   portTickType last_wake;
   last_wake = GetTickCount();

   while (true)
   {
      LEDOnState = !LEDOnState;
      GPIO_WriteBit(LEDPort, LEDPin, LEDOnState ? Bit_SET : Bit_RESET);
      DelayUntil(&last_wake, ToggleRate);
   }

}


bool LEDFlasher::HardwareInit()
{
   GPIO_InitTypeDef init;

   EnableGPIOClock(LEDPort);

   init.GPIO_Pin = LEDPin;
   init.GPIO_OType = GPIO_OType_PP;
   init.GPIO_PuPd = GPIO_PuPd_NOPULL;
   init.GPIO_Speed = GPIO_Speed_2MHz;
   init.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_Init(LEDPort, &init);

   return true;
}

void LEDFlasher::EnableGPIOClock(GPIO_TypeDef * port)
{
   if (port == GPIOA)
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
   }
   else if (port == GPIOB)
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   }
   else if (port == GPIOC)
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
   }
   else if (port == GPIOD)
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   }
   else if (port == GPIOE)
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
   }
   else if (port == GPIOF)
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
   }
   else if (port == GPIOG)
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
   }
   else if (port == GPIOH)
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
   }
   else if (port == GPIOI)
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
   }
}

LEDFlasher::~LEDFlasher()
{

}

