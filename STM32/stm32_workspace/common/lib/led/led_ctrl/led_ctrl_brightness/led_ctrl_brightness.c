// SRW

#include "brightness_ctrl.h"


void led_ctrl_brightness_adjust(strip_num_e led_strip_index)
{
    if (LED_BRIGHTNESS_FIRST == g_task_led_ctrl[led_strip_index].led_brightness)
	{
    	g_task_led_ctrl[led_strip_index].led_brightness = LED_BRIGHTNESS_LAST;
	}
    else
	{
    	g_task_led_ctrl[led_strip_index].led_brightness = (led_brightness_e) (g_task_led_ctrl[led_strip_index].led_brightness - 1);
	}
    switch (g_task_led_ctrl[led_strip_index].led_brightness)
    {
        case LED_BRIGHTNESS_100_PERCENT: current_monitor_set(1.0f); break;
//        case LED_BRIGHTNESS_50_PERCENT: current_monitor_set(0.5f); break;
        case LED_BRIGHTNESS_25_PERCENT: current_monitor_set(0.25f); break;
        case LED_BRIGHTNESS_1_PERCENT: current_monitor_set(0.01f); break;
        default: break;
    }
}
