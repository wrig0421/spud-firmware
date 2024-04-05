// SRW

#include "color_ctrl.h"



master_color_state_e color_ctrl_master_state(strip_num_e led_strip_index)
{
    return g_task_led_ctrl[led_strip_index].led_color_info.led_color_master;
}


void color_ctrl_master_state_demo(strip_num_e led_strip_index)
{
	g_task_led_ctrl[led_strip_index].led_color_info.led_color_master = MASTER_COLOR_STATE_DEMO;
}


void state_ctrl_state_color_force_fixed(strip_num_e led_strip_index)
{
	g_task_led_ctrl[led_strip_index].led_color_info.led_color_master = MASTER_COLOR_STATE_FIXED;
}


void color_ctrl_master_state_fixed(strip_num_e led_strip_index)
{
	g_task_led_ctrl[led_strip_index].led_color_info.led_color_master = MASTER_COLOR_STATE_FIXED;
	g_task_led_ctrl[led_strip_index].led_color_info.led_color = LED_COLOR_FIRST;
}


void color_ctrl_reset(strip_num_e led_strip_index)
{
	g_task_led_ctrl[led_strip_index].led_color_info.led_color = LED_COLOR_FIRST;
}


strip_num_e led_ctrl_strip_num_to_index(strip_bit_e strip_bit)
{
	switch (strip_bit)
	{
		case STRIP_BIT_1: 						return STRIP_NUM_1;
		case STRIP_BIT_2: 						return STRIP_NUM_2;
		case STRIP_BIT_3: 						return STRIP_NUM_3;
		case CONFIG_LED_STRIP_SYNC_INDEX: 		return STRIP_BIT_ALL_SET;
		default: 								return CONFIG_LED_STRIP_INVALID_INDEX;
	}
}


bool color_ctrl_adjust(strip_bit_e strip_bit)
{
    bool return_val = false;
    strip_num_e led_strip_index = task_led_ctrl_strip_num_to_index(strip_bit);
    if (LED_COLOR_LAST == g_task_led_ctrl[led_strip_index].led_color_info.led_color)
    {
    	g_task_led_ctrl[led_strip_index].led_color_info.led_color = LED_COLOR_FIRST;
        return_val = true;
    }
    else
	{
    	g_task_led_ctrl[led_strip_index].led_color_info.led_color = (led_color_e) (g_task_led_ctrl[led_strip_index].led_color_info.led_color + 1);
	}
    return return_val;
}


led_color_e color_ctrl(strip_num_e led_strip_index)
{
    return g_task_led_ctrl[led_strip_index].led_color_info.led_color;
}


color_hex_code_e color_ctrl_hex(strip_num_e led_strip_index)
{
    return g_color_hex_codes[g_task_led_ctrl[led_strip_index].led_color_info.led_color];
}


uint8_t color_ctrl_red_hex(strip_num_e led_strip_index)
{
    return (((g_color_hex_codes[g_task_led_ctrl[led_strip_index].led_color_info.led_color] & 0xFF0000) >> 16));// / current_monitor_ratio());
}


uint8_t color_ctrl_green_hex(strip_num_e led_strip_index)
{
    return (((g_color_hex_codes[g_task_led_ctrl[led_strip_index].led_color_info.led_color] & 0x00FF00) >> 8));// / current_monitor_ratio());
}


uint8_t color_ctrl_blue_hex(strip_num_e led_strip_index)
{
    return ((g_color_hex_codes[g_task_led_ctrl[led_strip_index].led_color_info.led_color] & 0x0000FF));// / current_monitor_ratio());
}


color_hex_code_e color_ctrl_to_hex(const led_color_e color)
{
    return g_color_hex_codes[color];
}


void color_ctrl_random_input(led_color_e* p_color)
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


void color_ctrl_random(strip_num_e led_strip_index)
{
    led_color_e color = (led_color_e)(random_num(0, NUM_COLORS));
    if (g_task_led_ctrl[led_strip_index].led_color_info.led_color == color)
    {
        if (LED_COLOR_LAST == color)
		{
        	g_task_led_ctrl[led_strip_index].led_color_info.led_color = (led_color_e)(color - 1);
		}
        else
		{
        	g_task_led_ctrl[led_strip_index].led_color_info.led_color = (led_color_e)(color + 1);
		}
    }
    else
    {
    	g_task_led_ctrl[led_strip_index].led_color_info.led_color = color;
    }
}
