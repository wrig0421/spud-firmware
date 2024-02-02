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
#include "current_monitor.h"

#define CURRENT_MONITOR_MAX_CURRENT_DRAW_A      (float)9.50
#define CURRENT_MONITOR_MAX_CURRENT_PER_LED_MA  40

// current tracking needs to be maintained per strip.
//typedef current_t* p_current_t;

float g_max_current_ratio = 1.0f;
float g_absolute_max_current_ratio = 0.0f; // DO NOT EXCEED!
//p_current_t gp_current_monitor_strip[NUM_STRIPS];


void current_monitor_set(float value)
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


float current_monitor_ratio(void)
{
    return g_max_current_ratio;
}


void current_monitor_init(void)
{
    while ((g_max_current_ratio * ((float)CURRENT_MONITOR_MAX_CURRENT_PER_LED_MA / 1000) * NUM_LEDS) > (float)CURRENT_MONITOR_MAX_CURRENT_DRAW_A)
    {
        g_max_current_ratio -= 0.05f;
    }
    //if (g_max_current_ratio <= 0) while(1); // broken..
    g_max_current_ratio = 0.1f;
    g_absolute_max_current_ratio = g_max_current_ratio;

}
