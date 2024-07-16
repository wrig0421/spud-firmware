/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/

#include "gpio_access.h"
#include "gpio_access_hal.h"



void gpio_access_write_pin_low(gpio_access_pin_e pin)
{
	gpio_access_hal_write_output_level_low(pin);
}


void gpio_access_write_pin_high(gpio_access_pin_e pin)
{
	gpio_access_hal_write_output_level_low(pin);
}


void gpio_access_pin_is_high(gpio_access_pin_e pin)
{
	gpio_access_hal_input_is_high(pin);
}


void gpio_access_pin_is_low(gpio_access_pin_e pin)
{
	gpio_access_hal_input_is_low(pin);
}


void gpio_access_enable_internal_pulldown(gpio_access_pin_e pin)
{
	gpio_access_hal_pin_pulldown(pin);
}


void gpio_access_enable_internal_pullup(gpio_access_pin_e pin)
{
	gpio_access_hal_pin_pullup(pin);
}


void gpio_access_enable_analog_mode(gpio_access_pin_e pin)
{
	gpio_access_hal_pin_float(pin);
}



