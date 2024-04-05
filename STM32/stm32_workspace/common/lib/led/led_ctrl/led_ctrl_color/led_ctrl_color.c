// SRW

#include "led_ctrl.h"
#include "led_color.h"
#include "led_ctrl_color.h"

extern led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];
extern led_color_hex_code_e g_color_hex_codes[NUM_COLORS];


led_color_master_state_e led_color_ctrl_master_state(strip_num_e strip_num)
{
    return g_task_led_ctrl[strip_num].led_color_info.led_color_master;
}


void led_color_ctrl_master_state_demo(strip_num_e strip_num)
{
	g_task_led_ctrl[strip_num].led_color_info.led_color_master = LED_COLOR_MASTER_STATE_DEMO;
}


void led_color_ctrl_master_state_force_fixed(strip_num_e strip_num)
{
	g_task_led_ctrl[strip_num].led_color_info.led_color_master = LED_COLOR_MASTER_STATE_FIXED;
}


void led_color_ctrl_master_state_fixed(strip_num_e strip_num)
{
	g_task_led_ctrl[strip_num].led_color_info.led_color_master = LED_COLOR_MASTER_STATE_FIXED;
	g_task_led_ctrl[strip_num].led_color_info.led_color = LED_COLOR_FIRST;
}


void led_color_ctrl_reset(strip_num_e strip_num)
{
	g_task_led_ctrl[strip_num].led_color_info.led_color = LED_COLOR_FIRST;
}


bool led_color_ctrl_adjust(strip_bit_e strip_bit)
{
    bool return_val = false;
    strip_num_e strip_num = task_led_ctrl_strip_num_to_index(strip_bit);
    if (LED_COLOR_LAST == g_task_led_ctrl[strip_num].led_color_info.led_color)
    {
    	g_task_led_ctrl[strip_num].led_color_info.led_color = LED_COLOR_FIRST;
        return_val = true;
    }
    else
	{
    	g_task_led_ctrl[strip_num].led_color_info.led_color = (led_color_e) (g_task_led_ctrl[strip_num].led_color_info.led_color + 1);
	}
    return return_val;
}


led_color_e led_color_ctrl(strip_num_e strip_num)
{
    return g_task_led_ctrl[strip_num].led_color_info.led_color;
}


led_color_hex_code_e led_color_ctrl_hex(strip_num_e strip_num)
{
    return g_color_hex_codes[g_task_led_ctrl[strip_num].led_color_info.led_color];
}


uint8_t led_color_ctrl_red_hex(strip_num_e strip_num)
{
    return (((g_color_hex_codes[g_task_led_ctrl[strip_num].led_color_info.led_color] & 0xFF0000) >> 16));// / current_monitor_ratio());
}


uint8_t led_color_ctrl_green_hex(strip_num_e strip_num)
{
    return (((g_color_hex_codes[g_task_led_ctrl[strip_num].led_color_info.led_color] & 0x00FF00) >> 8));// / current_monitor_ratio());
}


uint8_t led_color_ctrl_blue_hex(strip_num_e strip_num)
{
    return ((g_color_hex_codes[g_task_led_ctrl[strip_num].led_color_info.led_color] & 0x0000FF));// / current_monitor_ratio());
}


led_color_hex_code_e led_color_ctrl_to_hex(const led_color_e color)
{
    return g_color_hex_codes[color];
}


void led_color_ctrl_random_input(led_color_e* p_color)
{
    led_color_e color = (led_color_e)(random_num(0, NUM_COLORS));
    if (*p_color == color)
    {
        if ((LED_COLOR_LAST) == color) *p_color = (led_color_e)(color - 1);
        else *p_color = (led_color_e)(color + 1);
    }
    else
    {
        *p_color = color;
    }
}


void led_color_ctrl_random(strip_num_e strip_num)
{
    led_color_e color = (led_color_e)(random_num(0, NUM_COLORS));
    if (g_task_led_ctrl[strip_num].led_color_info.led_color == color)
    {
        if (LED_COLOR_LAST == color)
		{
        	g_task_led_ctrl[strip_num].led_color_info.led_color = (led_color_e)(color - 1);
		}
        else
		{
        	g_task_led_ctrl[strip_num].led_color_info.led_color = (led_color_e)(color + 1);
		}
    }
    else
    {
    	g_task_led_ctrl[strip_num].led_color_info.led_color = color;
    }
}
