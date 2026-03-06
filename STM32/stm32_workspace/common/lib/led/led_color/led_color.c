/***********************************
 * @file   color_led.c
 * @author SpudGlo LLC
 ***********************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "numbers.h"
#include "led_color.h"
#include "task_led_ctrl.h"
#include "button_access.h"


const led_color_hex_code_e g_led_color_enum_to_hex_lookup[NUM_COLORS] =
{
	[LED_COLOR_BLACK] 			= LED_COLOR_HEX_BLACK,
	[LED_COLOR_WHITE] 			= LED_COLOR_HEX_WHITE,
	[LED_COLOR_RED] 			= LED_COLOR_HEX_RED,
	[LED_COLOR_LIME] 			= LED_COLOR_HEX_LIME,
	[LED_COLOR_BLUE] 			= LED_COLOR_HEX_BLUE,
	[LED_COLOR_YELLOW] 			= LED_COLOR_HEX_YELLOW,
	[LED_COLOR_CYAN] 			= LED_COLOR_HEX_CYAN,
	[LED_COLOR_MAGENTA] 		= LED_COLOR_HEX_MAGENTA,
	[LED_COLOR_SILVER] 			= LED_COLOR_HEX_SILVER,
	[LED_COLOR_GRAY] 			= LED_COLOR_HEX_GRAY,
	[LED_COLOR_DARK_GRAY] 		= LED_COLOR_HEX_DARK_GRAY,
	[LED_COLOR_CHARCOAL] 		= LED_COLOR_HEX_CHARCOAL,
	[LED_COLOR_MAROON] 			= LED_COLOR_HEX_MAROON,
	[LED_COLOR_OLIVE] 			= LED_COLOR_HEX_OLIVE,
	[LED_COLOR_GREEN] 			= LED_COLOR_HEX_GREEN,
	[LED_COLOR_PURPLE] 			= LED_COLOR_HEX_PURPLE,
	[LED_COLOR_TEAL] 			= LED_COLOR_HEX_TEAL,
	[LED_COLOR_NAVY] 			= LED_COLOR_HEX_NAVY,
	[LED_COLOR_ORANGE_RED] 		= LED_COLOR_HEX_ORANGE_RED,
	[LED_COLOR_ORANGE] 			= LED_COLOR_HEX_ORANGE,
	[LED_COLOR_KHAKI] 			= LED_COLOR_HEX_KHAKI,
	[LED_COLOR_LAWN_GREEN] 		= LED_COLOR_HEX_LAWN_GREEN,
	[LED_COLOR_SPRING_GREEN] 	= LED_COLOR_HEX_SPRING_GREEN,
	[LED_COLOR_MIDNIGHT_BLUE] 	= LED_COLOR_HEX_MIDNIGHT_BLUE,
    [LED_COLOR_BLUE_VIOLET]     = LED_COLOR_HEX_BLUE_VIOLET,
    [LED_COLOR_DARK_MAGENTA]    = LED_COLOR_HEX_DARK_MAGENTA,

	[LED_COLOR_HOT_PINK] 		= LED_COLOR_HEX_HOT_PINK,
	[LED_COLOR_MINT] 			= LED_COLOR_HEX_MINT,
	[LED_COLOR_TAN] 			= LED_COLOR_HEX_TAN,
	[LED_COLOR_BROWN] 			= LED_COLOR_HEX_BROWN,
	[LED_COLOR_RED_BROWN] 		= LED_COLOR_HEX_RED_BROWN,
	[LED_COLOR_SADDLE_BROWN] 	= LED_COLOR_HEX_SADDLE_BROWN,
	[LED_COLOR_CHOCOLATE] 		= LED_COLOR_HEX_CHOCOLATE,
	[LED_COLOR_ROSY_BROWN] 		= LED_COLOR_HEX_ROSY_BROWN,
	[LED_COLOR_DARK_TAN] 		= LED_COLOR_HEX_DARK_TAN,
	[LED_COLOR_DARK_RED] 		= LED_COLOR_HEX_DARK_RED,
	[LED_COLOR_SALMON] 			= LED_COLOR_HEX_SALMON,
	[LED_COLOR_GOLD] 			= LED_COLOR_HEX_GOLD,
	[LED_COLOR_FOREST_GREEN] 	= LED_COLOR_HEX_FOREST_GREEN,
	[LED_COLOR_AQUA_MARINE] 	= LED_COLOR_HEX_AQUA_MARINE,
	[LED_COLOR_DARK_BLUE] 		= LED_COLOR_HEX_DARK_BLUE,
	[LED_COLOR_VIOLET] 			= LED_COLOR_HEX_VIOLET,
	[LED_COLOR_INDIGO] 			= LED_COLOR_HEX_INDIGO,
	[LED_COLOR_PLUM] 			= LED_COLOR_HEX_PLUM,
	[LED_COLOR_PINK] 			= LED_COLOR_HEX_PINK,
	[LED_COLOR_DEEP_PINK] 		= LED_COLOR_HEX_DEEP_PINK
};


// no length specified here!
const led_color_e g_led_color_hex_to_enum_lookup[] =
{
    [LED_COLOR_HEX_BLACK]               = LED_COLOR_BLACK,
    [LED_COLOR_HEX_WHITE]               = LED_COLOR_WHITE,
    [LED_COLOR_HEX_RED]                 = LED_COLOR_RED,
    [LED_COLOR_HEX_LIME]                = LED_COLOR_LIME,
    [LED_COLOR_HEX_BLUE]                = LED_COLOR_BLUE,
    [LED_COLOR_HEX_YELLOW]              = LED_COLOR_YELLOW,
    [LED_COLOR_HEX_CYAN]                = LED_COLOR_CYAN,
    [LED_COLOR_HEX_MAGENTA]             = LED_COLOR_MAGENTA,
    [LED_COLOR_HEX_SILVER]              = LED_COLOR_SILVER,
    [LED_COLOR_HEX_GRAY]                = LED_COLOR_GRAY,
    [LED_COLOR_HEX_DARK_GRAY]           = LED_COLOR_DARK_GRAY,
    [LED_COLOR_HEX_CHARCOAL]            = LED_COLOR_CHARCOAL,
    [LED_COLOR_HEX_MAROON]              = LED_COLOR_MAROON,
    [LED_COLOR_HEX_OLIVE]               = LED_COLOR_OLIVE,
    [LED_COLOR_HEX_GREEN]               = LED_COLOR_GREEN,
    [LED_COLOR_HEX_PURPLE]              = LED_COLOR_PURPLE,
    [LED_COLOR_HEX_TEAL]                = LED_COLOR_TEAL,
    [LED_COLOR_HEX_NAVY]                = LED_COLOR_NAVY,
    [LED_COLOR_HEX_ORANGE_RED]          = LED_COLOR_ORANGE_RED,
    [LED_COLOR_HEX_ORANGE]              = LED_COLOR_ORANGE,
    [LED_COLOR_HEX_KHAKI]               = LED_COLOR_KHAKI,
    [LED_COLOR_HEX_LAWN_GREEN]          = LED_COLOR_LAWN_GREEN,
    [LED_COLOR_HEX_SPRING_GREEN]        = LED_COLOR_SPRING_GREEN,
    [LED_COLOR_HEX_MIDNIGHT_BLUE]       = LED_COLOR_MIDNIGHT_BLUE,
    [LED_COLOR_HEX_BLUE_VIOLET]         = LED_COLOR_BLUE_VIOLET,
    [LED_COLOR_HEX_DARK_MAGENTA]        = LED_COLOR_DARK_MAGENTA,
    [LED_COLOR_HEX_HOT_PINK]            = LED_COLOR_HOT_PINK,
    [LED_COLOR_HEX_MINT]                = LED_COLOR_MINT,
    [LED_COLOR_HEX_TAN]                 = LED_COLOR_TAN,
    [LED_COLOR_HEX_BROWN]               = LED_COLOR_BROWN,
    [LED_COLOR_HEX_RED_BROWN]           = LED_COLOR_RED_BROWN,
    [LED_COLOR_HEX_SADDLE_BROWN]        = LED_COLOR_SADDLE_BROWN,
    [LED_COLOR_HEX_CHOCOLATE]           = LED_COLOR_CHOCOLATE,
    [LED_COLOR_HEX_ROSY_BROWN]          = LED_COLOR_ROSY_BROWN,
    [LED_COLOR_HEX_DARK_TAN]            = LED_COLOR_DARK_TAN,
    [LED_COLOR_HEX_DARK_RED]            = LED_COLOR_DARK_RED,
    [LED_COLOR_HEX_SALMON]              = LED_COLOR_SALMON,
    [LED_COLOR_HEX_GOLD]                = LED_COLOR_GOLD,
    [LED_COLOR_HEX_FOREST_GREEN]        = LED_COLOR_FOREST_GREEN,
    [LED_COLOR_HEX_AQUA_MARINE]         = LED_COLOR_AQUA_MARINE,
    [LED_COLOR_HEX_DARK_BLUE]           = LED_COLOR_DARK_BLUE,
    [LED_COLOR_HEX_VIOLET]              = LED_COLOR_VIOLET,
    [LED_COLOR_HEX_INDIGO]              = LED_COLOR_INDIGO,
    [LED_COLOR_HEX_PLUM]                = LED_COLOR_PLUM,
    [LED_COLOR_HEX_PINK]                = LED_COLOR_PINK,
    [LED_COLOR_HEX_DEEP_PINK]           = LED_COLOR_DEEP_PINK
};


led_color_hex_code_e led_color_enum_to_hex_code(led_color_e led_color)
{
    return g_led_color_enum_to_hex_lookup[led_color];
}


led_color_e led_color_hex_to_enum(led_color_hex_code_e led_color_hex)
{
    switch (led_color_hex)
    {

        case LED_COLOR_HEX_BLACK:               return LED_COLOR_BLACK;
        case LED_COLOR_HEX_WHITE:               return LED_COLOR_WHITE;
        case LED_COLOR_HEX_RED:                 return LED_COLOR_RED;
        case LED_COLOR_HEX_LIME:                return LED_COLOR_LIME;
        case LED_COLOR_HEX_BLUE:                return LED_COLOR_BLUE;
        case LED_COLOR_HEX_YELLOW:              return LED_COLOR_YELLOW;
        case LED_COLOR_HEX_CYAN:                return LED_COLOR_CYAN;
        case LED_COLOR_HEX_MAGENTA:             return LED_COLOR_MAGENTA;
        case LED_COLOR_HEX_SILVER:              return LED_COLOR_SILVER;
        case LED_COLOR_HEX_GRAY:                return LED_COLOR_GRAY;
        case LED_COLOR_HEX_DARK_GRAY:           return LED_COLOR_DARK_GRAY;
        case LED_COLOR_HEX_CHARCOAL:            return LED_COLOR_CHARCOAL;
        case LED_COLOR_HEX_MAROON:              return LED_COLOR_MAROON;
        case LED_COLOR_HEX_OLIVE:               return LED_COLOR_OLIVE;
        case LED_COLOR_HEX_GREEN:               return LED_COLOR_GREEN;
        case LED_COLOR_HEX_PURPLE:              return LED_COLOR_PURPLE;
        case LED_COLOR_HEX_TEAL:                return LED_COLOR_TEAL;
        case LED_COLOR_HEX_NAVY:                return LED_COLOR_NAVY;
        case LED_COLOR_HEX_ORANGE_RED:          return LED_COLOR_ORANGE_RED;
        case LED_COLOR_HEX_ORANGE:              return LED_COLOR_ORANGE;
        case LED_COLOR_HEX_KHAKI:               return LED_COLOR_KHAKI;
        case LED_COLOR_HEX_LAWN_GREEN:          return LED_COLOR_LAWN_GREEN;
        case LED_COLOR_HEX_SPRING_GREEN:        return LED_COLOR_SPRING_GREEN;
        case LED_COLOR_HEX_MIDNIGHT_BLUE:       return LED_COLOR_MIDNIGHT_BLUE;
        case LED_COLOR_HEX_BLUE_VIOLET:         return LED_COLOR_BLUE_VIOLET;
        case LED_COLOR_HEX_DARK_MAGENTA:        return LED_COLOR_DARK_MAGENTA;
        case LED_COLOR_HEX_HOT_PINK:            return LED_COLOR_HOT_PINK;
        case LED_COLOR_HEX_MINT:                return LED_COLOR_MINT;
        case LED_COLOR_HEX_TAN:                 return LED_COLOR_TAN;
        case LED_COLOR_HEX_BROWN:               return LED_COLOR_BROWN;
        case LED_COLOR_HEX_RED_BROWN:           return LED_COLOR_RED_BROWN;
        case LED_COLOR_HEX_SADDLE_BROWN:        return LED_COLOR_SADDLE_BROWN;
        case LED_COLOR_HEX_CHOCOLATE:           return LED_COLOR_CHOCOLATE;
        case LED_COLOR_HEX_ROSY_BROWN:          return LED_COLOR_ROSY_BROWN;
        case LED_COLOR_HEX_DARK_TAN:            return LED_COLOR_DARK_TAN;
        case LED_COLOR_HEX_DARK_RED:            return LED_COLOR_DARK_RED;
        case LED_COLOR_HEX_SALMON:              return LED_COLOR_SALMON;
        case LED_COLOR_HEX_GOLD:                return LED_COLOR_GOLD;
        case LED_COLOR_HEX_FOREST_GREEN:        return LED_COLOR_FOREST_GREEN;
        case LED_COLOR_HEX_AQUA_MARINE:         return LED_COLOR_AQUA_MARINE;
        case LED_COLOR_HEX_DARK_BLUE:           return LED_COLOR_DARK_BLUE;
        case LED_COLOR_HEX_VIOLET:              return LED_COLOR_VIOLET;
        case LED_COLOR_HEX_INDIGO:              return LED_COLOR_INDIGO;
        case LED_COLOR_HEX_PLUM:                return LED_COLOR_PLUM;
        case LED_COLOR_HEX_PINK:                return LED_COLOR_PINK;
        case LED_COLOR_HEX_DEEP_PINK:           return LED_COLOR_DEEP_PINK;

        default: return LED_COLOR_BLACK;
    }

}


