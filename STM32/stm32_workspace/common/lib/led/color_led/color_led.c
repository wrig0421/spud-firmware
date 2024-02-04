/***********************************
 * @file   color_led.c
 * @author SpudGlo LLC
 ***********************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "numbers.h"
#include "task_led_ctrl.h"


color_hex_code_e g_color_hex_codes[NUM_COLORS] =
{
    [COLORS_RED] = COLOR_HEX_RED,
    [COLORS_LIME] = COLOR_HEX_LIME,
    [COLORS_BLUE] = COLOR_HEX_BLUE,
    [COLORS_YELLOW] = COLOR_HEX_YELLOW,
    [COLORS_CYAN] = COLOR_HEX_CYAN,
    [COLORS_MAGENTA] = COLOR_HEX_MAGENTA,
    [COLORS_GREEN] = COLOR_HEX_GREEN,
    [COLORS_PURPLE] = COLOR_HEX_PURPLE,
    [COLORS_TEAL] = COLOR_HEX_TEAL,
    [COLORS_NAVY] = COLOR_HEX_NAVY,
    [COLORS_ORANGE_RED] = COLOR_HEX_ORANGE_RED,
    [COLORS_ORANGE] = COLOR_HEX_ORANGE,
    [COLORS_KHAKI] = COLOR_HEX_KHAKI,
    [COLORS_LAWN_GREEN] = COLOR_HEX_LAWN_GREEN,
    [COLORS_SPRING_GREEN] = COLOR_HEX_SPRING_GREEN,
    [COLORS_MIDNIGHT_BLUE] = COLOR_HEX_MIDNIGHT_BLUE,
    [COLORS_BLUE_VIOLET] = COLOR_HEX_BLUE_VIOLET,
    [COLORS_DARK_MAGENTA] = COLOR_HEX_DARK_MAGENTA,
    [COLORS_HOT_PINK] = COLOR_HEX_HOT_PINK,
    [COLORS_MINT] = COLOR_HEX_MINT,
    //[COLORS_GRAY] = COLOR_HEX_GRAY,
    [COLORS_BROWN] = COLOR_HEX_BROWN
};


void color_led_hex_to_rgb(const color_hex_code_e color, uint8_t *color_array)
{
    color_array[offsetof(ws2812b_led_t, red)] = ((color & 0xFF0000) >> (BITS_PER_BYTE * (2 - offsetof(ws2812b_led_t, red))));
    color_array[offsetof(ws2812b_led_t, green)] = ((color & 0x00FF00) >> (BITS_PER_BYTE * (2 - offsetof(ws2812b_led_t, green))));
    color_array[offsetof(ws2812b_led_t, blue)] = ((color & 0x0000FF) >> (BITS_PER_BYTE * (2 - offsetof(ws2812b_led_t, blue))));
}


color_hex_code_e color_to_hex(const all_colors_e color)
{
	return g_color_hex_codes[color];
}


uint8_t color_red_to_hex(all_colors_e color)
{
	return (((g_color_hex_codes[color] & 0xFF0000) >> 16) / current_monitor_ratio());
}


uint8_t color_green_to_hex(all_colors_e color)
{
	return (((g_color_hex_codes[color] & 0x00FF00) >> 8) / current_monitor_ratio());
}


uint8_t color_blue_to_hex(all_colors_e color)
{
	return ((g_color_hex_codes[color] & 0x0000FF) / current_monitor_ratio());
}


void color_led_adjust_color(all_colors_e* p_color)
{
    if (COLORS_LAST == *p_color) *p_color = COLORS_FIRST;
    else *p_color = *p_color + 1;
}


void color_led_random_color(all_colors_e* p_color)
{
    all_colors_e rand_color = (all_colors_e)(random_num(0, NUM_COLORS));
    if (*p_color == rand_color)
    {
        if ((COLORS_LAST) == rand_color) *p_color = (all_colors_e)(rand_color - 1);
        else *p_color = (all_colors_e)(rand_color + 1);
    }
    else
    {
    	*p_color = rand_color;
    }
}


void color_led_master_state_to_demo(master_color_state_e *p_master_color_state)
{
	*p_master_color_state = MASTER_COLOR_STATE_DEMO;
}


void color_led_master_state_to_fixed(master_color_state_e *p_master_color_state, all_colors_e* p_color_state)
{
	*p_master_color_state = MASTER_COLOR_STATE_FIXED;
	*p_color_state = COLORS_FIRST;
}



void color_led_reset_color(all_colors_e* p_color_state)
{
	*p_color_state = COLORS_FIRST;
}



