// SRW

#include "speed_ctrl.h"


float speed_ctrl(strip_num_e led_strip_index)
{
    float speed_factor = 0.0;
    switch(g_task_led_ctrl[led_strip_index].led_speed)
    {
        case LED_SPEED_10X: speed_factor = 10.0f; break;
        case LED_SPEED_5X: speed_factor = 5.0f; break;
        case LED_SPEED_1X: speed_factor = 1.0f; break;
        case LED_SPEED_0P5X: speed_factor = 0.5f; break;
        case LED_SPEED_0P25X: speed_factor = 0.25f; break;
        default: break;
    }
    return speed_factor;
}


void speed_ctrl_adjust(strip_num_e led_strip_index)
{
    if (LED_SPEED_FIRST == g_task_led_ctrl[led_strip_index].led_speed)
	{
    	g_task_led_ctrl[led_strip_index].led_speed = LED_SPEED_LAST;
	}
    else
	{
    	g_task_led_ctrl[led_strip_index].led_speed = (led_speed_e) (g_task_led_ctrl[led_strip_index].led_speed - 1);
	}
}


void speed_ctrl_reset(strip_num_e led_strip_index)
{
	g_task_led_ctrl[led_strip_index].led_speed = LED_SPEED_1X;
}
