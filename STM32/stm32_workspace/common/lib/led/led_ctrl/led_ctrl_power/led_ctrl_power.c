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

// current tracking needs to be maintained per strip.
//typedef current_t* p_current_t;

float g_max_current_ratio = 1.0f;
float g_absolute_max_current_ratio = 0.0f; // DO NOT EXCEED!
//p_current_t gp_current_monitor_strip[NUM_STRIPS];


void led_ctrl_power_monitor_set(float value)
{
    if (value < g_absolute_max_current_ratio)
    {
        g_max_current_ratio = value;
    }
    else
    {
        g_max_current_ratio = g_absolute_max_current_ratio;
    }
}


float led_ctrl_power_monitor_ratio(void)
{
    return g_max_current_ratio;
}


void led_ctrl_power_monitor_init(void)
{
	uint32_t num_leds = NUM_LEDS;
	float current_max_per_led_ampere = (float)LED_CTRL_POWER_MONITOR_MAX_CURRENT_PER_LED_MA / 1000.0f;
	float current_ratio_value = (g_max_current_ratio * (current_max_per_led_ampere) * num_leds);
	// ws2812b_set_led function uses the current ratio!!
    while (current_ratio_value > (float)LED_CTRL_POWER_MONITOR_MAX_CURRENT_DRAW_A)
    {
        g_max_current_ratio -= 0.0625f;
        current_ratio_value = (g_max_current_ratio * (current_max_per_led_ampere) * num_leds);
    }
    if (g_max_current_ratio <= 0) while(1); // broken..
    //g_max_current_ratio = 0.1f;
    g_absolute_max_current_ratio = g_max_current_ratio;

}
