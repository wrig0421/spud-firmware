// SRW

#include "numbers.h"
#include "led_ctrl.h"
#include "led_color.h"
#include "led_ctrl_color.h"

extern led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];
extern led_color_hex_code_e g_color_hex_codes[NUM_COLORS];


led_color_master_state_e led_ctrl_color_master_state(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_task_led_ctrl[strip_num].led_color_info.led_color_master;
}


void led_ctrl_color_master_state_force_demo(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	g_task_led_ctrl[strip_num].led_color_info.led_color_master = LED_COLOR_MASTER_STATE_DEMO;
}


void led_ctrl_color_master_state_force_fixed(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	g_task_led_ctrl[strip_num].led_color_info.led_color_master = LED_COLOR_MASTER_STATE_FIXED;
	g_task_led_ctrl[strip_num].led_color_info.led_color = LED_COLOR_FIRST;
}


void led_ctrl_color_reset(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	g_task_led_ctrl[strip_num].led_color_info.led_color = LED_COLOR_FIRST;
}


bool led_ctrl_color_adjust(const strip_mask_t mask)
{
    bool return_val = false;
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
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


led_color_e led_ctrl_color(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_task_led_ctrl[strip_num].led_color_info.led_color;
}


led_color_hex_code_e led_ctrl_color_hex(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_color_hex_codes[g_task_led_ctrl[strip_num].led_color_info.led_color];
}


uint8_t led_ctrl_color_red_hex(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return (((g_color_hex_codes[g_task_led_ctrl[strip_num].led_color_info.led_color] & 0xFF0000) >> 16));// / led_ctrl_power_monitor_ratio());
}


uint8_t led_ctrl_color_green_hex(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return (((g_color_hex_codes[g_task_led_ctrl[strip_num].led_color_info.led_color] & 0x00FF00) >> 8));// / led_ctrl_power_monitor_ratio());
}


uint8_t led_ctrl_color_blue_hex(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return ((g_color_hex_codes[g_task_led_ctrl[strip_num].led_color_info.led_color] & 0x0000FF));// / led_ctrl_power_monitor_ratio());
}


led_color_hex_code_e led_ctrl_color_to_hex(const led_color_e color)
{
    return g_color_hex_codes[color];
}


void led_ctrl_color_random_input(led_color_e* p_color)
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


void led_ctrl_color_random(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
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




