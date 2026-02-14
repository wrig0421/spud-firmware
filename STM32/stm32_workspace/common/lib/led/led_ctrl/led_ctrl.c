// SRW

#include "FreeRTOS.h"
#include "timers.h"
#include "portmacro.h"

#include "led_ctrl.h"
#include "task_button_press.h"
#include "free_rtos_convenience.h"
#include "ws2812b.h"
#include "led_ctrl_speed.h"
#include "task_button_press.h"

#define LED_CTRL_MASTER_STATE_TIME_MS	180000
extern TimerHandle_t g_led_ctrl_timer_handle;


/**
 * @brief   Start animation timer.
 * @param   void
 * @return  void
 * @note    Each animation is displayed for LED_CTRL_MASTER_STATE_TIME_MS.
 *          Specifically, each is displayed for this amount of time in demo mode.
 */
void led_ctrl_timer_start(void)
{
	xTimerStart(g_led_ctrl_timer_handle, LED_CTRL_MASTER_STATE_TIME_MS);
}


void timer_led_ctrl_callback(TimerHandle_t timer_handle)
{
//#	if defined(ENABLE_LED_STRIP_SYNC)
//		xTaskNotify(g_led_strip_sync_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//#	else
//#		if (1 == NUM_ACTIVE_STRIPS)
//			xTaskNotify(g_led_strip_1_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//#		elif (2 == NUM_ACTIVE_STRIPS)
//			xTaskNotify(g_led_strip_1_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//			xTaskNotify(g_led_strip_2_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//#		elif (3 == NUM_ACTIVE_STRIPS)
//			xTaskNotify(g_led_strip_1_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//			xTaskNotify(g_led_strip_2_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//			xTaskNotify(g_led_strip_3_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//#		endif
//#	endif
}


/**
 * @brief   Check if button press occurred pertinent to the passed mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  bool - true if interrupt occured else false.
 * @note    Function returns false for case that ENABLE_BUTTON is not defined.
 */
static bool led_ctrl_interrupt_occurred(const strip_mask_t mask)
{
#	if defined(ENABLE_BUTTON)
		return task_button_press_interrupt_occurred(mask);
#	else
		return false;
#	endif
}


/**
 * @brief   Function to delay an amount of time.
 * @param   mask - enabled strips to check if button press effects.
 * @param   time_ms - time to delay
 * @return  bool - true if interrupt occured else false.
 * @note    If interrupt occured then the function may not delay the full
 *          amount of time.
 */
bool led_ctrl_delay(const strip_mask_t mask, const uint32_t time_ms)
{
    uint32_t ms_count = 0;
    uint32_t ticks = 0;

    if (!time_ms) return false;

    ticks = time_ms / portTICK_PERIOD_MS;

    while (ms_count++ < ticks)
    {
    	free_rtos_delay_ms(portTICK_PERIOD_MS);
        if (led_ctrl_interrupt_occurred(mask)) return true;
    }
    return false;
}


