// SRW

#include "ws2812b.h"
#include "led_ctrl.h"
#include "led_ctrl_state.h"

extern led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];

void led_state_ctrl_iteration_reset(strip_num_e strip_num)
{
	g_task_led_ctrl[strip_num].led_state_info.led_state_current_iteration = 0;
}


led_state_e led_state_ctrl_random_state(const led_state_e cur_state)
{
    led_state_e state = (led_state_e)(random_num(LED_STATE_FIRST, NUM_LED_STATES));
    if (cur_state == state)
    {
        if (LED_STATE_LAST == cur_state) state = (led_state_e)(state - 1);
        else state = (led_state_e)(state + 1);
    }
    return state;
}


led_state_e led_state_ctrl_state(strip_num_e strip_num)
{
    return g_task_led_ctrl[strip_num].led_state_info.led_state;
}


bool led_state_ctrl_adjust_state(strip_num_e strip_num)
{
    bool return_val = false;
    if (LED_STATE_LAST == g_task_led_ctrl[strip_num].led_state_info.led_state)
    {
        g_task_led_ctrl[strip_num].led_state_info.led_state = LED_STATE_FIRST;
        return_val = true;
    }
    else
	{
    	g_task_led_ctrl[strip_num].led_state_info.led_state = (led_state_e) (g_task_led_ctrl[strip_num].led_state_info.led_state + 1);
	}
    return return_val;
}


void led_state_ctrl_force_fixed_state(strip_num_e strip_num)
{
	g_task_led_ctrl[strip_num].led_state_info.led_state_master = LED_CTRL_STATE_MASTER_FIXED;
}


void led_state_ctrl_force_demo(strip_num_e strip_num)
{
	g_task_led_ctrl[strip_num].led_state_info.led_state_master = LED_CTRL_STATE_MASTER_DEMO;
	g_task_led_ctrl[strip_num].led_state_info.led_state = LED_STATE_FIRST; // set first state
    g_animation_iterations = 0;
}


led_ctrl_state_master_e led_state_ctrl_master_state(strip_num_e strip_num)
{
    return g_task_led_ctrl[strip_num].led_state_info.led_state_master;
}


void led_state_ctrl_color_decrement_inner_color(void)
{
	if (LED_COLOR_FIRST == g_two_color_inner)
	{
		g_two_color_inner = LED_COLOR_LAST;
	}
	else
	{
		g_two_color_inner = (led_color_e) (g_two_color_inner - 1);
	}
}


void led_state_ctrl_color_decrement_outer_color(void)
{
	if (LED_COLOR_FIRST == g_two_color_outer)
	{
		g_two_color_outer = LED_COLOR_LAST;
	}
	else
	{
		g_two_color_outer = (led_color_e) (g_two_color_outer - 1);
	}
}


void led_state_ctrl_color_increment_inner_color(void)
{
	if (LED_COLOR_LAST == g_two_color_inner)
	{
		g_two_color_inner = LED_COLOR_FIRST;
	}
	else
	{
		g_two_color_inner = (led_color_e) (g_two_color_inner + 1);
	}
}


void led_state_ctrl_color_decrement_outer_color(void)
{
	if (LED_COLOR_LAST == g_two_color_outer)
	{
		g_two_color_outer = LED_COLOR_FIRST;
	}
	else
	{
		g_two_color_outer = (led_color_e) (g_two_color_outer + 1);
	}
}



