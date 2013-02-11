#include "global_defs.h"
#include "stm32f4xx.h"
#include "init_tasks.h"

struct GPIO_AFTypeDef_S
{
   uint16_t GPIO_PinSource;
   uint8_t  AF;

};
typedef struct GPIO_AFTypeDef_S GPIO_AFTypeDef;

// TARGET SETTINGS

#define GPIO_CONFIG(port,pin,mode,speed,otype,pupd,af) \
	{ GPIO_Pin_##pin, mode, speed, otype, pupd },

static GPIO_InitTypeDef GPIO_INIT_SETTINGS[] =
{
   #include "port_defs.h"
};

#undef GPIO_CONFIG

#define GPIO_INIT_SETTINGS_COUNT (sizeof(GPIO_INIT_SETTINGS)/sizeof(GPIO_InitTypeDef))

#define GPIO_CONFIG(port,pin,mode,speed,otype,pupd,af) \
   { GPIO_PinSource##pin, af },

static GPIO_AFTypeDef GPIO_AF_SETTINGS[] =
{
   #include "port_defs.h"
};

#undef GPIO_CONFIG

#define GPIO_CONFIG(port,pin,mode,speed,otype,pupd,af) \
		GPIO##port,

static GPIO_TypeDef * GPIO_INIT_PORT[] =
{
   #include "port_defs.h"
};

#undef GPIO_CONFIG

// EVAL BOARD SETTINGS

#define GPIO_CONFIG_EVAL(port,pin,mode,speed,otype,pupd,af) \
   { GPIO_Pin_##pin, mode, speed, otype, pupd },

static GPIO_InitTypeDef GPIO_INIT_SETTINGS_EVAL[] =
{
   #include "port_defs.h"
};

#undef GPIO_CONFIG_EVAL

#define GPIO_INIT_SETTINGS_EVAL_COUNT (sizeof(GPIO_INIT_SETTINGS_EVAL)/sizeof(GPIO_InitTypeDef))

#define GPIO_CONFIG_EVAL(port,pin,mode,speed,otype,pupd,af) \
   { GPIO_PinSource##pin, af },

static GPIO_AFTypeDef GPIO_AF_SETTINGS_EVAL[] =
{
   #include "port_defs.h"
};

#undef GPIO_CONFIG_EVAL

#define GPIO_CONFIG_EVAL(port,pin,mode,speed,otype,pupd,af) \
   GPIO##port,

static GPIO_TypeDef * GPIO_INIT_PORT_EVAL[] =
{
   #include "port_defs.h"
};

#undef GPIO_CONFIG_EVAL


bool IsRunningOnEvalBoard(void)
{
   uint32_t device_id_1 = *((uint32_t *)0x1FFF7A10);
   uint32_t device_id_2 = *((uint32_t *)0x1FFF7A14);
   uint32_t device_id_3 = *((uint32_t *)0x1FFF7A18);

   return ((device_id_1 == 0x002F002A) && (device_id_2 == 0x31314712) && (device_id_3 == 0x30343630));
}

static void InitPeripherals(void)
{
   // Set up priorities to support FreeRTOS

   NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

   // Enable most (not all) of the AHB peripheral clocks

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_BKPSRAM, ENABLE);
   //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CCMDATARAMEN, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC_Tx, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC_Rx, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC_PTP, ENABLE);
   //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_OTG_HS, ENABLE);
   //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_OTG_HS_ULPI, ENABLE);
   //RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
   //RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_CRYP, ENABLE);
   //RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_HASH, ENABLE);
   RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
   RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE);
}

static void EnableGPIOClock(GPIO_TypeDef * port, GPIOMode_TypeDef mode, uint8_t af)
{
   if (port == GPIOA && (mode == GPIO_Mode_IN || mode == GPIO_Mode_OUT))
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
   }
   else if (port == GPIOB && (mode == GPIO_Mode_IN || mode == GPIO_Mode_OUT))
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   }
   else if (port == GPIOC && (mode == GPIO_Mode_IN || mode == GPIO_Mode_OUT))
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
   }
   else if (port == GPIOD && (mode == GPIO_Mode_IN || mode == GPIO_Mode_OUT))
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   }
   else if (port == GPIOE && (mode == GPIO_Mode_IN || mode == GPIO_Mode_OUT))
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
   }
   else if (port == GPIOF && (mode == GPIO_Mode_IN || mode == GPIO_Mode_OUT))
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
   }
   else if (port == GPIOG && (mode == GPIO_Mode_IN || mode == GPIO_Mode_OUT))
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
   }
   else if (port == GPIOH && (mode == GPIO_Mode_IN || mode == GPIO_Mode_OUT))
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
   }
   else if (port == GPIOI && (mode == GPIO_Mode_IN || mode == GPIO_Mode_OUT))
   {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
   }
}

static void InitPorts(void)
{
   uint32_t i;

   GPIO_DeInit(GPIOA);
   GPIO_DeInit(GPIOB);
   GPIO_DeInit(GPIOC);
   GPIO_DeInit(GPIOD);
   GPIO_DeInit(GPIOE);
   GPIO_DeInit(GPIOF);
   GPIO_DeInit(GPIOG);
   GPIO_DeInit(GPIOH);
   GPIO_DeInit(GPIOI);

   if (IsRunningOnEvalBoard())
   {
      for ( i = 0; i < GPIO_INIT_SETTINGS_EVAL_COUNT; i++ )
      {
         EnableGPIOClock(GPIO_INIT_PORT_EVAL[i], GPIO_INIT_SETTINGS_EVAL[i].GPIO_Mode,  GPIO_AF_SETTINGS_EVAL[i].AF);
         GPIO_Init(GPIO_INIT_PORT_EVAL[i], &(GPIO_INIT_SETTINGS_EVAL[i]));
         if (GPIO_INIT_SETTINGS_EVAL[i].GPIO_Mode == GPIO_Mode_AF)
         {
            GPIO_PinAFConfig(GPIO_INIT_PORT_EVAL[i], GPIO_AF_SETTINGS_EVAL[i].GPIO_PinSource, GPIO_AF_SETTINGS_EVAL[i].AF);
         }
      }
   }
   else
   {
      for ( i = 0; i < GPIO_INIT_SETTINGS_COUNT; i++ )
      {
         EnableGPIOClock(GPIO_INIT_PORT[i], GPIO_INIT_SETTINGS[i].GPIO_Mode,  GPIO_AF_SETTINGS[i].AF);
         GPIO_Init(GPIO_INIT_PORT[i], &(GPIO_INIT_SETTINGS[i]));
         if (GPIO_INIT_SETTINGS[i].GPIO_Mode == GPIO_Mode_AF)
         {
            GPIO_PinAFConfig(GPIO_INIT_PORT[i], GPIO_AF_SETTINGS[i].GPIO_PinSource, GPIO_AF_SETTINGS[i].AF);
         }
      }
   }
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
