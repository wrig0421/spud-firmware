// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "timer_ctrl.h"
#include "timer_create.h"

//#define TIMER_LED_STATE_TIME_MIN	2
//#define TIMER_LED_STATE_TIME_MS		TIMER_LED_STATE_TIME_MIN * 60 * 1000

#define TIMER_LED_STATE_TIME_MS		 	60000

TimerHandle_t g_led_ctrl_timer_handle = NULL;
StaticTimer_t g_led_ctrl_timer_buffer;

void timer_create(void)
{
	g_led_ctrl_timer_handle = xTimerCreateStatic("timer_led_ctrl", pdMS_TO_TICKS(TIMER_LED_STATE_TIME_MS),
												pdTRUE, (void *) 0, timer_ctrl_callback, &g_led_ctrl_timer_buffer);
	if (NULL == g_led_ctrl_timer_handle)
	{
		while (1);
	}
	else
	{
		if (pdPASS != xTimerStart(g_led_ctrl_timer_handle, 0))
		{
			while (1);
		}
	}
}


void timer_reset(void)
{
	if (xTimerReset(g_led_ctrl_timer_handle, 10) == pdPASS)
	{

	}
}
