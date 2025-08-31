
#if !defined(GPIO_ACCESS_HAL_H)
#define GPIO_ACCESS_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include "gpio_config_hal.h"

void gpio_access_hal_write_output_level_high(gpio_hal_pin_e pin);
void gpio_access_hal_write_output_level_low(gpio_hal_pin_e pin);
void gpio_access_hal_pin_pulldown(gpio_hal_pin_e pin);
void gpio_access_hal_pin_pullup(gpio_hal_pin_e pin);
void gpio_access_hal_pin_float(gpio_hal_pin_e pin);
void gpio_access_hal_pin_input(gpio_hal_pin_e pin);
void gpio_access_hal_pin_output(gpio_hal_pin_e pin);

bool gpio_access_hal_input_is_low(gpio_hal_pin_e pin);
bool gpio_access_hal_input_is_high(gpio_hal_pin_e pin);

#endif
