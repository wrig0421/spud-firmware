// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "timer_create.h"

#define TIMER_LED_STATE_TIME_MS		180000

TimerHandle_t g_led_ctrl_timer_handle;
StaticTimer_t g_led_ctrl_timer_buffer;

void timer_create(void)
{
	g_led_ctrl_timer_handle = xTimerCreateStatic("timer_led_ctrl", pdMS_TO_TICKS(TIMER_LED_STATE_TIME_MS),
												pdFALSE, (void *) 0, timer_led_ctrl_callback, &g_led_ctrl_timer_buffer);
	if (NULL == g_led_ctrl_timer_handle)
	{
		while (1);
	}
}
