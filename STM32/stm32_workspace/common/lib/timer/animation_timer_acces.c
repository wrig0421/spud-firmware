// SRW
#include <animation_timer_access.h>
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "animation_timer_create.h"
#include "led_animate.h"

#define LED_CTRL_MASTER_STATE_TIME_MS   180000

void animation_timer_access_callback(TimerHandle_t h_timer)
{
    configASSERT(h_timer);

    // trigger animation change.
    led_animate_force_exit_stimulus();
}


void animation_timer_access_reset(void)
{
	if (xTimerReset(animation_timer_return_handle(), 10) != pdPASS)
	{
	    while (1);
	}
};


/**
 * @brief   Start animation timer.
 * @param   void
 * @return  void
 * @note    Each animation is displayed for LED_CTRL_MASTER_STATE_TIME_MS.
 *          Specifically, each is displayed for this amount of time in demo mode.
 */
void led_ctrl_timer_start(void)
{
    xTimerStart(animation_timer_return_handle(), LED_CTRL_MASTER_STATE_TIME_MS);
}
