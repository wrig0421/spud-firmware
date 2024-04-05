// SRW

#include "pause_ctrl.h"


void pause_ctrl_clear(strip_num_e led_strip_index)
{
	g_task_led_ctrl[led_strip_index].led_interrupt_info.pause_set = false;
}


void pause_ctrl(strip_num_e led_strip_index)
{
    static uint8_t flip_or_flop = 1;
    if (flip_or_flop) g_task_led_ctrl[led_strip_index].led_interrupt_info.pause_set = true;
    else g_task_led_ctrl[led_strip_index].led_interrupt_info.pause_set = false;
    flip_or_flop ^= 1;
}

