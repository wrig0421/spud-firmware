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

// red, green, blue current?

// current tracking needs to be maintained per strip.
typedef current_t* p_current_t;

#if defined(STRIP_1_LENGTH)
current_t g_current_strip_1[STRIP_1_LENGTH] = {0.0f};
#endif
#if defined(STRIP_2_LENGTH)
current_t g_current_strip_2[STRIP_2_LENGTH] = {0.0f};
#endif
#if defined(STRIP_3_LENGTH)
current_t g_current_strip_3[STRIP_3_LENGTH] = {0.0f};
#endif
#if defined(STRIP_4_LENGTH)
current_t g_current_strip_4[STRIP_4_LENGTH] = {0.0f};
#endif


float g_max_current_ratio = 1.0;
p_current_t gp_current_monitor_strip[NUM_STRIPS];

void current_monitor_init(void)
{
#if defined(STRIP_1_LENGTH)
    gp_current_monitor_strip[STRIP_NUM_1] = g_current_strip_1;
#endif
#if defined(STRIP_2_LENGTH)
    gp_current_monitor_strip[STRIP_NUM_2] = g_current_strip_2;
#endif
#if defined(STRIP_3_LENGTH)
    gp_current_monitor_strip[STRIP_NUM_3] = g_current_strip_3;
#endif
#if defined(STRIP_4_LENGTH)
    gp_current_monitor_strip[STRIP_NUM_4] = g_current_strip_4;
#endif
    while ((g_max_current_ratio * ((float)CURRENT_MONITOR_MAX_CURRENT_PER_LED_MA / 1000) * NUM_LEDS) > (float)CURRENT_MONITOR_MAX_CURRENT_DRAW_A)
    {
        g_max_current_ratio -= 0.05f;
    }
    if (g_max_current_ratio <= 0) while(1); // broken..
    //g_max_current_ratio = 1.0f;
}
