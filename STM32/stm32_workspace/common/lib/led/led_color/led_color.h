/***********************************
 * @file   color_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(LED_COLOR_H)
#define LED_COLOR_H
#include "ws2812b.h"


typedef enum
{
    LED_COLOR_MASTER_STATE_DEMO,
    LED_COLOR_MASTER_STATE_FIXED
} led_color_master_state_e;


// complete list of all hex color codes
typedef enum
{
    // RGB
    LED_COLOR_HEX_BLACK         = 0x000000,
    LED_COLOR_HEX_WHITE         = 0xFFFFFF,
    LED_COLOR_HEX_RED           = 0xFF0000,
    LED_COLOR_HEX_LIME          = 0x00FF00,
    LED_COLOR_HEX_BLUE          = 0x0000FF,
    LED_COLOR_HEX_YELLOW        = 0xFFFF00,
    LED_COLOR_HEX_CYAN          = 0x00FFFF,
    LED_COLOR_HEX_MAGENTA       = 0xFF00FF,
    LED_COLOR_HEX_SILVER        = 0xC0C0C0,
    LED_COLOR_HEX_GRAY          = 0x808080,
    LED_COLOR_HEX_MAROON        = 0x800000,
    LED_COLOR_HEX_OLIVE         = 0x808000,
    LED_COLOR_HEX_GREEN         = 0x008000,
    LED_COLOR_HEX_PURPLE        = 0x800080,
    LED_COLOR_HEX_TEAL          = 0x008080,
    LED_COLOR_HEX_NAVY          = 0x000080,
    LED_COLOR_HEX_ORANGE_RED    = 0xFF4500,
    LED_COLOR_HEX_ORANGE        = 0xFFA500,
    LED_COLOR_HEX_KHAKI         = 0xF0E68C,
    LED_COLOR_HEX_LAWN_GREEN    = 0x7CFC00,
    LED_COLOR_HEX_SPRING_GREEN  = 0x00FF7F,
    LED_COLOR_HEX_MIDNIGHT_BLUE = 0x191970,
    LED_COLOR_HEX_BLUE_VIOLET   = 0x8A2BE2,
    LED_COLOR_HEX_DARK_MAGENTA  = 0x8B008B,
    LED_COLOR_HEX_HOT_PINK      = 0xFF69B4,
    LED_COLOR_HEX_MINT          = 0x4EBD88,
    LED_COLOR_HEX_BROWN         = 0xA52A2A,
} led_color_hex_code_e;


typedef union
{
	uint32_t 			color_hex;
	struct
	{
		uint8_t			rsvd;
		ws2812b_led_t	color_rgb;
	};
} led_color_t;



// colors actively used are selected below
typedef enum
{
	LED_COLOR_FIRST            = 0,
	LED_COLOR_WHITE          	= LED_COLOR_FIRST,
    LED_COLOR_BLACK,
    LED_COLOR_YELLOW,
    //LED_COLOR_SILVER,
    //LED_COLOR_GRAY,
    //LED_COLOR_MAROON,
    //LED_COLOR_OLIVE,

    LED_COLOR_GREEN,
    LED_COLOR_LAWN_GREEN,
    LED_COLOR_SPRING_GREEN,
    LED_COLOR_LIME,
    LED_COLOR_MINT,
    LED_COLOR_TEAL,

    LED_COLOR_CYAN,
    LED_COLOR_NAVY,
    LED_COLOR_BLUE,
    LED_COLOR_MIDNIGHT_BLUE,
    LED_COLOR_BLUE_VIOLET,

    LED_COLOR_PURPLE,

    LED_COLOR_ORANGE,
    LED_COLOR_ORANGE_RED,

	LED_COLOR_RED,
    LED_COLOR_MAGENTA,
    LED_COLOR_DARK_MAGENTA,
    LED_COLOR_HOT_PINK,

    //LED_COLOR_GRAY,
    LED_COLOR_KHAKI,
    LED_COLOR_BROWN,
	LED_COLOR_LAST             = LED_COLOR_BROWN,
    NUM_COLORS
} led_color_e;



void led_color_set_current_strip_color(const strip_mask_t mask,
									   led_color_hex_code_e color_hex_code);
void led_color_strip_color(const strip_mask_t mask, led_color_t* led_color);

#endif

