// SRW
#include <stdint.h>
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "gpio_config_hal.h"

extern const gpio_config_t g_gpio_config[NUM_GPIO_PINS];


const port_t g_gpio_port_lookup_table[NUM_GPIO_PINS] =
{
	[GPIO_PIOA_PIN_0] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_1] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_2] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_3] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_4] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_5] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_6] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_7] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_8] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_9] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_10] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_11] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_12] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_13] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_14] = GPIO_PORT_A,
	[GPIO_PIOA_PIN_15] = GPIO_PORT_A,

	[GPIO_PIOB_PIN_0] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_1] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_2] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_3] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_4] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_5] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_6] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_7] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_8] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_9] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_10] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_11] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_12] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_13] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_14] = GPIO_PORT_B,
	[GPIO_PIOB_PIN_15] = GPIO_PORT_B,

	[GPIO_PIOC_PIN_0] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_1] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_2] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_3] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_4] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_5] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_6] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_7] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_8] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_9] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_10] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_11] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_12] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_13] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_14] = GPIO_PORT_C,
	[GPIO_PIOC_PIN_15] = GPIO_PORT_C,

	[GPIO_PIOD_PIN_2] = GPIO_PORT_D,

	[GPIO_PIOH_PIN_0] = GPIO_PORT_H,
	[GPIO_PIOH_PIN_1] = GPIO_PORT_H,
	// PIOH2 DOES NOT EXIST!!
	[GPIO_PIOH_PIN_3] = GPIO_PORT_H
};


const uint16_t g_gpio_lookup_table[NUM_GPIO_PINS] =
{
	[GPIO_PIOA_PIN_0] = GPIO_PIN_0,
	[GPIO_PIOA_PIN_1] = GPIO_PIN_1,
	[GPIO_PIOA_PIN_2] = GPIO_PIN_2,
	[GPIO_PIOA_PIN_3] = GPIO_PIN_3,
	[GPIO_PIOA_PIN_4] = GPIO_PIN_4,
	[GPIO_PIOA_PIN_5] = GPIO_PIN_5,
	[GPIO_PIOA_PIN_6] = GPIO_PIN_6,
	[GPIO_PIOA_PIN_7] = GPIO_PIN_7,
	[GPIO_PIOA_PIN_8] = GPIO_PIN_8,
	[GPIO_PIOA_PIN_9] = GPIO_PIN_9,
	[GPIO_PIOA_PIN_10] = GPIO_PIN_10,
	[GPIO_PIOA_PIN_11] = GPIO_PIN_11,
	[GPIO_PIOA_PIN_12] = GPIO_PIN_12,
	[GPIO_PIOA_PIN_13] = GPIO_PIN_13,
	[GPIO_PIOA_PIN_14] = GPIO_PIN_14,
	[GPIO_PIOA_PIN_15] = GPIO_PIN_15,

	[GPIO_PIOB_PIN_0] = GPIO_PIN_0,
	[GPIO_PIOB_PIN_1] = GPIO_PIN_1,
	[GPIO_PIOB_PIN_2] = GPIO_PIN_2,
	[GPIO_PIOB_PIN_3] = GPIO_PIN_3,
	[GPIO_PIOB_PIN_4] = GPIO_PIN_4,
	[GPIO_PIOB_PIN_5] = GPIO_PIN_5,
	[GPIO_PIOB_PIN_6] = GPIO_PIN_6,
	[GPIO_PIOB_PIN_7] = GPIO_PIN_7,
	[GPIO_PIOB_PIN_8] = GPIO_PIN_8,
	[GPIO_PIOB_PIN_9] = GPIO_PIN_9,
	[GPIO_PIOB_PIN_10] = GPIO_PIN_10,
	[GPIO_PIOB_PIN_11] = GPIO_PIN_11,
	[GPIO_PIOB_PIN_12] = GPIO_PIN_12,
	[GPIO_PIOB_PIN_13] = GPIO_PIN_13,
	[GPIO_PIOB_PIN_14] = GPIO_PIN_14,
	[GPIO_PIOB_PIN_15] = GPIO_PIN_15,

	[GPIO_PIOC_PIN_0] = GPIO_PIN_0,
	[GPIO_PIOC_PIN_1] = GPIO_PIN_1,
	[GPIO_PIOC_PIN_2] = GPIO_PIN_2,
	[GPIO_PIOC_PIN_3] = GPIO_PIN_3,
	[GPIO_PIOC_PIN_4] = GPIO_PIN_4,
	[GPIO_PIOC_PIN_5] = GPIO_PIN_5,
	[GPIO_PIOC_PIN_6] = GPIO_PIN_6,
	[GPIO_PIOC_PIN_7] = GPIO_PIN_7,
	[GPIO_PIOC_PIN_8] = GPIO_PIN_8,
	[GPIO_PIOC_PIN_9] = GPIO_PIN_9,
	[GPIO_PIOC_PIN_10] = GPIO_PIN_10,
	[GPIO_PIOC_PIN_11] = GPIO_PIN_11,
	[GPIO_PIOC_PIN_12] = GPIO_PIN_12,
	[GPIO_PIOC_PIN_13] = GPIO_PIN_13,
	[GPIO_PIOC_PIN_14] = GPIO_PIN_14,
	[GPIO_PIOC_PIN_15] = GPIO_PIN_15,

	[GPIO_PIOD_PIN_2] = GPIO_PIN_2,

	[GPIO_PIOH_PIN_0] = GPIO_PIN_0,
	[GPIO_PIOH_PIN_1] = GPIO_PIN_1,
	// PIOH2 DOES NOT EXIST!!
	[GPIO_PIOH_PIN_3] = GPIO_PIN_3
};


IRQn_Type gpio_config_irqn_lookup(gpio_pin_e pin)
{
	if (GPIO_CONFIG_INTERRUPT_MODE_ENABLE == g_gpio_config[pin].interrupt_mode)
	{
		return g_gpio_config[pin].irqn;
	}
	else
	{
		return HardFault_IRQn; // lmfao
	}
}


port_t gpio_config_port_lookup(gpio_pin_e pin)
{
	return g_gpio_port_lookup_table[pin];
}


uint16_t gpio_config_pin_lookup(gpio_pin_e pin)
{
	return g_gpio_lookup_table[pin];
}


void gpio_config_hal_setup(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

	bool enable_interrupt = false;
	bool gpio_setup = false;
    //RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    GPIO_InitTypeDef  GPIO_InitStruct;
    for (gpio_pin_e pin = GPIO_PIN_FIRST; pin < NUM_GPIO_PINS; pin++)
    {
    	gpio_setup = true;
    	GPIO_InitStruct.Pin = g_gpio_lookup_table[pin];
    	GPIO_InitStruct.Pull = GPIO_NOPULL; // initially set no pullup here..
    	if (GPIO_CONFIG_INTERRUPT_MODE_ENABLE == g_gpio_config[pin].interrupt_mode)
    	{
    		enable_interrupt = true;
    	}
    	else
    	{
    		enable_interrupt = false;
    	}
		switch (g_gpio_config[pin].mode)
    	{
			case GPIO_CONFIG_MODE_ALTERNATE_FUNCTION: // fall through intentionally!!
    		case GPIO_CONFIG_MODE_NO_SETTING: // do nothing!
    			gpio_setup = false;
    		break;
    		case GPIO_CONFIG_MODE_INPUT_FLOAT:
    			GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
    		    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    		break;
    		case GPIO_CONFIG_MODE_INPUT_PULLDOWN:
				GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
				GPIO_InitStruct.Pull      = GPIO_PULLDOWN;
			break;
    		case GPIO_CONFIG_MODE_INPUT_PULLUP:
				GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
				GPIO_InitStruct.Pull      = GPIO_PULLUP;
			break;
    		case GPIO_CONFIG_MODE_OUTPUT_PUSHPULL:
    			GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
    		break;
			case GPIO_CONFIG_MODE_OUTPUT_OPEN_DRAIN:
				GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_OD;
			break;
				// these alternate function settings are expected to be made in the peripheral setup files
			default:
			break;
    	}
		if (enable_interrupt)
		{
			switch (g_gpio_config[pin].interrupt_edge)
			{
				case GPIO_CONFIG_INTERRUPT_EDGE_FALLING:
					GPIO_InitStruct.Mode      	= GPIO_MODE_IT_FALLING;
				break;
				case GPIO_CONFIG_INTERRUPT_EDGE_RISING:
					GPIO_InitStruct.Mode      	= GPIO_MODE_IT_RISING;
				break;
				case GPIO_CONFIG_INTERRUPT_EDGE_RISING_FALLING:
					GPIO_InitStruct.Mode 		= GPIO_MODE_IT_RISING_FALLING;
				break;
				default:
				break;
			}
			__HAL_GPIO_EXTI_CLEAR_IT(g_gpio_config[pin].irqn);
		    HAL_NVIC_SetPriority(g_gpio_config[pin].irqn, 24, 0);
		    HAL_NVIC_EnableIRQ(g_gpio_config[pin].irqn);
		    __HAL_GPIO_EXTI_CLEAR_IT(g_gpio_config[pin].irqn);
		}
		if (gpio_setup)
		{
		    HAL_GPIO_Init(g_gpio_config[pin].port, &GPIO_InitStruct);
		    if (GPIO_CONFIG_MODE_OUTPUT_PUSHPULL == g_gpio_config[pin].mode)
		    {
		    	if (GPIO_CONFIG_OUTPUT_LVL_RESET == g_gpio_config[pin].lvl)
				{
					HAL_GPIO_WritePin(g_gpio_config[pin].port, g_gpio_config[pin].pin, GPIO_PIN_RESET);
				}
				else
				{
					HAL_GPIO_WritePin(g_gpio_config[pin].port, g_gpio_config[pin].pin, GPIO_PIN_SET);
				}
		    }
		}
    }
}


