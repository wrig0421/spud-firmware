// SRW

#include "ws2812b.h"
#include "led_ctrl.h"
#include "led_ctrl_pause.h"

extern led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];

void pause_ctrl_clear(strip_num_e strip_num)
{
	g_task_led_ctrl[strip_num].led_interrupt_info.pause = false;
}


void pause_ctrl(strip_num_e strip_num)
{
    static uint8_t flip_or_flop = 1;
    if (flip_or_flop) g_task_led_ctrl[strip_num].led_interrupt_info.pause = true;
    else g_task_led_ctrl[strip_num].led_interrupt_info.pause = false;
    flip_or_flop ^= 1;
}

