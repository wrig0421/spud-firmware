// SRW
#include <animation_timer_access.h>
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "led_animate.h"

extern TimerHandle_t g_led_ctrl_timer_handle;


void animation_timer_access_callback(TimerHandle_t h_timer)
{
    configASSERT(h_timer);

    // trigger animation change.
    led_animate_force_exit_stimulus();
}


void animation_timer_access_reset(void)
{
	if (xTimerReset(g_led_ctrl_timer_handle, 10) != pdPASS)
	{
	    while (1);
	}
};
