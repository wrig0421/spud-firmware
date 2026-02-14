/*
 * current_monitor.c
 *
 *  Created on: Sep 11, 2022
 *      Author: spud
 */
#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "ws2812b.h"
#include "led_ctrl_power.h"

#define LED_CTRL_POWER_MONITOR_MAX_CURRENT_DRAW_A      (float)9.5
#define LED_CTRL_POWER_MONITOR_MAX_CURRENT_PER_LED_MA  40.0f

float g_max_power_factor = 1.0f;
float g_absolute_max_power_factor = 0.0f; // DO NOT EXCEED!

/**
 * @brief   Set the max power parameter after "init".
 * @param   value - the value to set the power factor to.
 * @return  void
 * @note    This function is intended to be used to allow brightness control.
 *          The brightness will only change if it DOES NOT exceed the
 *          g_absolute_max_current threshold.
 */
void led_ctrl_power_monitor_set(float value)
{
    if (value < g_absolute_max_power_factor)
    {
        g_max_power_factor = value;
    }
    else
    {
        g_max_power_factor = g_absolute_max_power_factor;
    }
}


/**
 * @brief   Return the power monitor factor.
 * @param   void
 * @return  void
 */
float led_ctrl_power_monitor_ratio(void)
{
    return g_max_power_factor;
}


/**
 * @brief   Calculate the max power factor based on number of enabled LEDs.
 * @param   void
 * @return  void
 * @note    Worst case power factor is calculated.  The power factor DOES NOT
 *          dynamically change!
 */
void led_ctrl_power_monitor_init(void)
{
	uint32_t num_leds = NUM_LEDS;
	float current_max_per_led_ampere = \
	                (float)LED_CTRL_POWER_MONITOR_MAX_CURRENT_PER_LED_MA / \
	                1000.0f;
	float current_ratio_value = (g_max_power_factor * \
	                            (current_max_per_led_ampere) * num_leds);
	// ws2812b_set_led function uses the current ratio!!
    while (current_ratio_value > \
                    (float)LED_CTRL_POWER_MONITOR_MAX_CURRENT_DRAW_A)
    {
        g_max_power_factor -= 0.0625f;
        current_ratio_value = (g_max_power_factor * \
                              (current_max_per_led_ampere) * num_leds);
    }
    if (g_max_power_factor <= 0) while(1); // broken...

    g_absolute_max_power_factor = g_max_power_factor;
}
