// SRW

#include "ws2812b.h"
#include "led_ctrl.h"
#include "led_ctrl_pause.h"

extern led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];

void led_ctrl_pause(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
//	g_task_led_ctrl[strip_num].led_interrupt_info.minor.interrupt_status.bits.pause_brightness = true;
    static uint8_t flip_or_flop = 1;
    if (flip_or_flop)
	{
    	g_task_led_ctrl[strip_num].led_interrupt_info.minor.interrupt_status.bits.pause_brightness = true;
	}
    else
	{
    	g_task_led_ctrl[strip_num].led_interrupt_info.minor.interrupt_status.bits.pause_brightness = false;
	}
    flip_or_flop ^= 1;
}

