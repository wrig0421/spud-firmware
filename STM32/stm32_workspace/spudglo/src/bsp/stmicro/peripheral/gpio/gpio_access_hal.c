// SRW
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "gpio_access_hal.h"
#include "gpio_config_hal.h"

extern const gpio_config_t g_gpio_config[NUM_GPIO_PINS];

static void gpio_access_hal_write_output_level(gpio_pin_e pin, gpio_config_output_lvl_e output_lvl)
{
	// it's strictly assumed that the pin is already setup as an output here!
	if (output_lvl == GPIO_CONFIG_OUTPUT_LVL_RESET)
	{
		HAL_GPIO_WritePin(g_gpio_config[pin].port, gpio_config_pin_lookup(g_gpio_config[pin].pin), GPIO_PIN_RESET);
	}
	else if (output_lvl == GPIO_CONFIG_OUTPUT_LVL_SET)
	{
		HAL_GPIO_WritePin(g_gpio_config[pin].port, gpio_config_pin_lookup(g_gpio_config[pin].pin), GPIO_PIN_SET);
	}
	else
	{
		// no setting is only other option...
	}
}


void gpio_access_hal_write_output_level_high(gpio_pin_e pin)
{
	gpio_access_hal_write_output_level(pin, GPIO_CONFIG_OUTPUT_LVL_SET);
}


void gpio_access_hal_write_output_level_low(gpio_pin_e pin)
{
	gpio_access_hal_write_output_level(pin, GPIO_CONFIG_OUTPUT_LVL_RESET);
}


void gpio_access_hal_pin_pulldown(gpio_pin_e pin)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin = gpio_config_pin_lookup(pin);
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(g_gpio_config[pin].port, &GPIO_InitStruct);
}


void gpio_access_hal_pin_pullup(gpio_pin_e pin)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin = gpio_config_pin_lookup(pin);
	GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(g_gpio_config[pin].port, &GPIO_InitStruct);
}

void gpio_access_hal_pin_float(gpio_pin_e pin)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin = gpio_config_pin_lookup(pin);
	GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(g_gpio_config[pin].port, &GPIO_InitStruct);
}


void gpio_access_hal_pin_input(gpio_pin_e pin)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin = gpio_config_pin_lookup(pin); // need to add a pin lookup...
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(g_gpio_config[pin].port, &GPIO_InitStruct);
}


void gpio_access_hal_pin_output(gpio_pin_e pin)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin = gpio_config_pin_lookup(pin); // need to add a pin lookup...
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	// no level set just the output here!!
    HAL_GPIO_Init(g_gpio_config[pin].port, &GPIO_InitStruct);
}


bool gpio_access_hal_input_is_low(gpio_pin_e pin)
{
	return ((GPIO_PIN_RESET == HAL_GPIO_ReadPin(g_gpio_config[pin].port, gpio_config_pin_lookup(g_gpio_config[pin].pin))) ? true : false);
}


bool gpio_access_hal_input_is_high(gpio_pin_e pin)
{
	return !(gpio_access_hal_input_is_low(pin));
}


