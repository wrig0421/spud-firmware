// SRW
#include <stdint.h>
#include "ws2812b.h"
#include "led_ctrl.h"
#include "led_ctrl_speed.h"

extern led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];

float led_ctrl_speed(const strip_mask_t mask)
{
    float speed_factor = 0.0;
    switch(g_task_led_ctrl[ws2812_strip_bit_to_strip_num(mask)].led_speed)
    {
        case LED_SPEED_1000P: speed_factor = 10.0f; break;
        case LED_SPEED_500P: speed_factor = 5.0f; break;
        case LED_SPEED_100P: speed_factor = 1.0f; break;
        case LED_SPEED_50P: speed_factor = 0.5f; break;
        case LED_SPEED_25P: speed_factor = 0.25f; break;
        default: break;
    }
    return speed_factor;
}


void led_ctrl_speed_adjust(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    if (LED_SPEED_FIRST == g_task_led_ctrl[strip_num].led_speed)
	{
    	g_task_led_ctrl[strip_num].led_speed = LED_SPEED_LAST;
	}
    else
	{
    	g_task_led_ctrl[strip_num].led_speed = (led_speed_e) (g_task_led_ctrl[strip_num].led_speed - 1);
	}
}


void led_ctrl_speed_reset(const strip_mask_t mask)
{
	g_task_led_ctrl[ws2812_strip_bit_to_strip_num(mask)].led_speed = LED_SPEED_100P;
}



