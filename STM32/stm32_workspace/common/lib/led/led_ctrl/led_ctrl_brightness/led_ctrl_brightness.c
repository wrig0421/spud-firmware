// SRW

#include "led_ctrl_power.h"
#include "led_ctrl.h"
#include "led_ctrl_brightness.h"

extern led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];

/**
 * @brief   Adjust brightness one position.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 * @note    This function is meant to be called only after the user initiates
 *          brightness change with remote control!
 */
void led_ctrl_brightness_adjust(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    if (LED_BRIGHTNESS_FIRST == g_task_led_ctrl[strip_num].led_brightness)
	{
    	g_task_led_ctrl[strip_num].led_brightness = LED_BRIGHTNESS_LAST;
	}
    else
	{
    	g_task_led_ctrl[strip_num].led_brightness = (led_brightness_e) (g_task_led_ctrl[strip_num].led_brightness - 1);
	}
    switch (g_task_led_ctrl[strip_num].led_brightness)
    {
        case LED_BRIGHTNESS_100_PERCENT: led_ctrl_power_monitor_set(1.0f); break;
//        case LED_BRIGHTNESS_50_PERCENT: led_ctrl_power_monitor_set(0.5f); break;
        case LED_BRIGHTNESS_25_PERCENT: led_ctrl_power_monitor_set(0.25f); break;
        case LED_BRIGHTNESS_1_PERCENT: led_ctrl_power_monitor_set(0.01f); break;
        default: break;
    }
}
