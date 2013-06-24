/*
 * LEDFlasher.h
 *
 *  Created on: Jun 23, 2013
 *      Author: Jeff
 */

#ifndef LEDFLASHER_H_
#define LEDFLASHER_H_

#include "AManagedTask.h"
#include "stm32f4xx.h"

class LEDFlasher : public AManagedTask
{
public:
   LEDFlasher(GPIO_TypeDef *pPort, uint16_t pin, portTickType nFlashRate);
   void Run();
   bool HardwareInit();
   virtual ~LEDFlasher();
   bool IsOn() { return LEDOnState; }

private:
   void EnableGPIOClock(GPIO_TypeDef * port);

   GPIO_TypeDef *    LEDPort;
   uint16_t          LEDPin;
   portTickType      ToggleRate;
   bool              LEDOnState;

};

#endif /* LEDFLASHER_H_ */
