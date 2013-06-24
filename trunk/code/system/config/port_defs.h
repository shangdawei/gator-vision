
#ifndef __PORT_DEFS_H_
#define __PORT_DEFS_H_

#define LED_PORT_EVAL   GPIOG
#define LED_PORT_REVA   GPIOC
#define LED_PORT        MappedSetting(LED_PORT_EVAL, LED_PORT_REVA)
#define LED_PIN_EVAL    GPIO_Pin_6
#define LED_PIN_REVA    GPIO_Pin_6
#define LED_PIN         MappedSetting(LED_PIN_EVAL, LED_PIN_REVA)

#endif
