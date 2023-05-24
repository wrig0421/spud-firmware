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

// current tracking needs to be maintained per strip.
typedef current_t* p_current_t;

float g_max_current_ratio = 0.01f;
p_current_t gp_current_monitor_strip[NUM_STRIPS];


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
    if (g_max_current_ratio <= 0) while(1); // broken..
    //g_max_current_ratio = 1.0f;
}