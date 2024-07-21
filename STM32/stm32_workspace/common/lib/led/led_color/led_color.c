/***********************************
 * @file   color_led.c
 * @author SpudGlo LLC
 ***********************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "numbers.h"
#include "task_led_ctrl.h"
#include "button_access.h"


led_color_t g_led_color_current_strip_color[NUM_SUPPORTED_STRIP_COMBOS] =
{
	[STRIP_NUM_1].color_hex 				= LED_COLOR_WHITE,
	[STRIP_NUM_2].color_hex 				= LED_COLOR_WHITE,
	[STRIP_NUM_3].color_hex 				= LED_COLOR_WHITE,

	[STRIP_NUM_1_AND_2].color_hex	 		= LED_COLOR_WHITE,
	[STRIP_NUM_1_AND_3].color_hex	 		= LED_COLOR_WHITE,
	[STRIP_NUM_2_AND_3].color_hex	 		= LED_COLOR_WHITE,

	[STRIP_NUM_ALL_SET].color_hex	 		= LED_COLOR_WHITE,
};


void led_color_set_current_strip_color(const strip_mask_t mask,
									   led_color_hex_code_e color_hex_code)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	g_led_color_current_strip_color[strip_num].color_hex = color_hex_code;
}


void led_color_strip_color(const strip_mask_t mask, led_color_t* led_color)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	led_color = &g_led_color_current_strip_color[strip_num];
}

//led_color_t g_led_color[NUM_COLORS] =
//{
//	[LED_COLOR_WHITE].color 			= LED_COLOR_HEX_WHITE,
//	[LED_COLOR_BLACK].color 			= LED_COLOR_HEX_BLACK,
//	[LED_COLOR_YELLOW].color 			= LED_COLOR_HEX_YELLOW,
//	[LED_COLOR_GREEN].color 			= LED_COLOR_HEX_GREEN,
//	[LED_COLOR_LAWN_GREEN].color 		= LED_COLOR_HEX_LAWN_GREEN,
//	[LED_COLOR_SPRING_GREEN].color 		= LED_COLOR_HEX_SPRING_GREEN,
//	[LED_COLOR_LIME].color 				= LED_COLOR_HEX_LIME,
//	[LED_COLOR_MINT].color 				= LED_COLOR_HEX_MINT,
//	[LED_COLOR_TEAL].color 				= LED_COLOR_HEX_TEAL,
//	[LED_COLOR_CYAN].color 				= LED_COLOR_HEX_CYAN,
//	[LED_COLOR_NAVY].color 				= LED_COLOR_HEX_NAVY,
//	[LED_COLOR_BLUE].color 				= LED_COLOR_HEX_BLUE,
//	[LED_COLOR_MIDNIGHT_BLUE].color 	= LED_COLOR_HEX_MIDNIGHT_BLUE,
//	[LED_COLOR_BLUE_VIOLET].color 		= LED_COLOR_HEX_BLUE_VIOLET,
//	[LED_COLOR_PURPLE].color 			= LED_COLOR_HEX_PURPLE,
//	[LED_COLOR_ORANGE].color 			= LED_COLOR_HEX_ORANGE,
//	[LED_COLOR_ORANGE_RED].color 		= LED_COLOR_HEX_ORANGE_RED,
//	[LED_COLOR_RED].color 				= LED_COLOR_HEX_RED,
//	[LED_COLOR_MAGENTA].color 			= LED_COLOR_HEX_MAGENTA,
//	[LED_COLOR_DARK_MAGENTA].color 		= LED_COLOR_HEX_DARK_MAGENTA,
//	[LED_COLOR_HOT_PINK].color 			= LED_COLOR_HEX_HOT_PINK,
//	[LED_COLOR_KHAKI].color 			= LED_COLOR_HEX_KHAKI,
//	[LED_COLOR_BROWN].color 			= LED_COLOR_HEX_BROWN
//};
//
//
//
//
//
led_color_hex_code_e g_color_hex_codes[NUM_COLORS] =
{
	[LED_COLOR_WHITE] = LED_COLOR_HEX_WHITE,
	[LED_COLOR_BLACK] = LED_COLOR_HEX_BLACK,
    [LED_COLOR_YELLOW] = LED_COLOR_HEX_YELLOW,

    [LED_COLOR_GREEN] = LED_COLOR_HEX_GREEN,
    [LED_COLOR_LAWN_GREEN] = LED_COLOR_HEX_LAWN_GREEN,
    [LED_COLOR_SPRING_GREEN] = LED_COLOR_HEX_SPRING_GREEN,
    [LED_COLOR_LIME] = LED_COLOR_HEX_LIME,
    [LED_COLOR_MINT] = LED_COLOR_HEX_MINT,
    [LED_COLOR_TEAL] = LED_COLOR_HEX_TEAL,

    [LED_COLOR_CYAN] = LED_COLOR_HEX_CYAN,
    [LED_COLOR_NAVY] = LED_COLOR_HEX_NAVY,
    [LED_COLOR_BLUE] = LED_COLOR_HEX_BLUE,
    [LED_COLOR_MIDNIGHT_BLUE] = LED_COLOR_HEX_MIDNIGHT_BLUE,
    [LED_COLOR_BLUE_VIOLET] = LED_COLOR_HEX_BLUE_VIOLET,

    [LED_COLOR_PURPLE] = LED_COLOR_HEX_PURPLE,
    [LED_COLOR_ORANGE] = LED_COLOR_HEX_ORANGE,
    [LED_COLOR_ORANGE_RED] = LED_COLOR_HEX_ORANGE_RED,

	[LED_COLOR_RED] = LED_COLOR_HEX_RED,
    [LED_COLOR_MAGENTA] = LED_COLOR_HEX_MAGENTA,
    [LED_COLOR_DARK_MAGENTA] = LED_COLOR_HEX_DARK_MAGENTA,
    [LED_COLOR_HOT_PINK] = LED_COLOR_HEX_HOT_PINK,

    [LED_COLOR_KHAKI] = LED_COLOR_HEX_KHAKI,
    [LED_COLOR_BROWN] = LED_COLOR_HEX_BROWN
};

led_color_hex_code_e led_color_major_state_change_color(button_e btn)
{
	switch (btn)
	{
		case BUTTON_A: return LED_COLOR_MAJOR_STATE_CHANGE_SPEED;
		case BUTTON_B: return LED_COLOR_MAJOR_STATE_CHANGE_STATE;
		case BUTTON_C: return LED_COLOR_MAJOR_STATE_CHANGE_COLOR;
		case BUTTON_D: return LED_COLOR_MAJOR_STATE_CHANGE_BRIGHTNESS;
		default: while (1);
	}
}


led_color_hex_code_e led_color_to_hex_code(led_color_e led_color)
{
	return g_color_hex_codes[led_color];
}

//
//
//void led_color_hex_to_rgb(const led_color_hex_code_e)
//{
//
//}
//
//
//
//void led_color_hex_to_rgb(const led_color_hex_code_e color, uint8_t *color_array)
//{
//    color_array[offsetof(ws2812b_led_t, red)] = ((color & 0xFF0000) >> (BITS_PER_BYTE * (2 - offsetof(ws2812b_led_t, red))));
//    color_array[offsetof(ws2812b_led_t, green)] = ((color & 0x00FF00) >> (BITS_PER_BYTE * (2 - offsetof(ws2812b_led_t, green))));
//    color_array[offsetof(ws2812b_led_t, blue)] = ((color & 0x0000FF) >> (BITS_PER_BYTE * (2 - offsetof(ws2812b_led_t, blue))));
//}

