// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_V7P0)
#include "stm32l4xx_hal.h"
//#include "gpio_config_hal.h"
#include "button_config_hal.h"


typedef enum
{
	BUTTON_IRQ_A = EXTI9_5_IRQn,
	BUTTON_IRQ_B = EXTI15_10_IRQn,
	BUTTON_IRQ_C = EXTI0_IRQn,
	BUTTON_IRQ_D = EXTI2_IRQn
} button_irq_e;


typedef enum
{
	BUTTON_PIN_A = GPIO_PIN_5,
	BUTTON_PIN_B = GPIO_PIN_13,
	BUTTON_PIN_C = GPIO_PIN_0,
	BUTTON_PIN_D = GPIO_PIN_2
} button_pin_e;


typedef enum
{
	BUTTON_PULL_A = GPIO_PULLUP,
	BUTTON_PULL_B = GPIO_PULLUP,
	BUTTON_PULL_C = GPIO_PULLUP,
	BUTTON_PULL_D = GPIO_PULLUP
} button_pull_e;


typedef enum
{
	BUTTON_MODE_A = BUTTON_CONFIG_MODE_IT_FALLING,
	BUTTON_MODE_B = BUTTON_CONFIG_MODE_IT_FALLING,
	BUTTON_MODE_C = BUTTON_CONFIG_MODE_IT_FALLING,
	BUTTON_MODE_D = BUTTON_CONFIG_MODE_IT_FALLING
} button_mode_e;


typedef enum
{
	BUTTON_ACTIVE_LVL_A = BUTTON_CONFIG_ACTIVE_LVL_LOW,
	BUTTON_ACTIVE_LVL_B = BUTTON_CONFIG_ACTIVE_LVL_LOW,
	BUTTON_ACTIVE_LVL_C = BUTTON_CONFIG_ACTIVE_LVL_LOW,
	BUTTON_ACTIVE_LVL_D = BUTTON_CONFIG_ACTIVE_LVL_LOW
} button_active_lvl_e;


const button_config_t g_button_config[NUM_BUTTONS] =
{
	[BUTTON_A] =
	{
		.pin 		= BUTTON_PIN_A,
		.port	 	= GPIOC,
		.pull 		= BUTTON_PULL_A,
		.mode 		= BUTTON_MODE_A,
		.lvl 		= BUTTON_ACTIVE_LVL_A,
		.irqn 		= BUTTON_IRQ_A
	},
	[BUTTON_B] =
	{
		.pin 		= BUTTON_PIN_B,
		.port 		= GPIOC,
		.pull 		= BUTTON_PULL_B,
		.mode 		= BUTTON_MODE_B,
		.lvl 		= BUTTON_ACTIVE_LVL_B,
		.irqn 		= BUTTON_IRQ_B
	},
	[BUTTON_C] =
	{
		.pin 		= BUTTON_PIN_C,
		.port 		= GPIOA,
		.pull 		= BUTTON_PULL_C,
		.mode 		= BUTTON_MODE_C,
		.lvl 		= BUTTON_ACTIVE_LVL_C,
		.irqn 		= BUTTON_IRQ_C
	},
	[BUTTON_D] =
	{
		.pin 		= BUTTON_PIN_D,
		.port 		= GPIOA,
		.pull 		= BUTTON_PULL_D,
		.mode 		= BUTTON_MODE_D,
		.lvl 		= BUTTON_ACTIVE_LVL_D,
		.irqn 		= BUTTON_IRQ_D
	}
};


IRQn_Type button_config_button_to_irq(button_e btn)
{
	switch (btn)
	{
		case BUTTON_A: 	return BUTTON_IRQ_A;
		case BUTTON_B: 	return BUTTON_IRQ_B;
		case BUTTON_C: 	return BUTTON_IRQ_C;
		case BUTTON_D: 	return BUTTON_IRQ_D;
		default: 		while(1);
	}
}


button_e button_config_irq_to_button(IRQn_Type  irqn)
{
	switch (irqn)
	{
		case BUTTON_IRQ_A: return BUTTON_A;
		case BUTTON_IRQ_B: return BUTTON_B;
		case BUTTON_IRQ_C: return BUTTON_C;
		case BUTTON_IRQ_D: return BUTTON_D;
		default: while(1); // unknown...
	}
}


uint16_t button_config_button_pin(button_e btn)
{
	return g_button_config[btn].pin;
}



#endif

