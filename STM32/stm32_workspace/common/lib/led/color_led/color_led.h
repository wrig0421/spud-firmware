/***********************************
 * @file   color_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(COLOR_LED_H)
#define COLOR_LED_H


typedef enum
{
    MASTER_COLOR_STATE_DEMO,
    MASTER_COLOR_STATE_FIXED
} master_color_state_e;


// complete list of all hex color codes
typedef enum
{
    // RGB
    COLOR_HEX_RED           = 0xFF0000,
    COLOR_HEX_DARK_RED      = 0,
    COLOR_HEX_MAROON        = 0x800000,
    COLOR_HEX_SALMON      = 0,
    COLOR_HEX_ORANGE_RED    = 0xFF4500,
    COLOR_HEX_ORANGE        = 0xFFA500,
    COLOR_HEX_GOLD      = 0,
    COLOR_HEX_YELLOW        = 0xFFFF00,
    COLOR_HEX_GREEN         = 0x008000,
    COLOR_HEX_MINT          = 0x4EBD88,
    COLOR_HEX_FOREST_GREEN      = 0,
    COLOR_HEX_TEAL          = 0x008080,
    COLOR_HEX_CYAN          = 0x00FFFF,
    COLOR_HEX_AQUA_MARINE      = 0,
    COLOR_HEX_BLUE          = 0x0000FF,
    COLOR_HEX_NAVY      = 0,
    COLOR_HEX_DARK_BLUE      = 0,
    COLOR_HEX_PURPLE        = 0x800080,
    COLOR_HEX_VIOLET      = 0,
    COLOR_HEX_PLUM      = 0,
    COLOR_HEX_PINK      = 0,
    COLOR_HEX_HOT_PINK      = 0xFF69B4,
    COLOR_HEX_DEEP_PINK      = 0,
    COLOR_HEX_BROWN         = 0xA52A2A,
    COLOR_HEX_CHOCOLATE      = 0,
    COLOR_HEX_WHITE         = 0xFFFFFF,
    COLOR_HEX_GRAY          = 0x808080,
    COLOR_HEX_SILVER        = 0xC0C0C0,
    COLOR_HEX_BLACK         = 0x000000,
    COLOR_HEX_LIME          = 0x00FF00,
    COLOR_HEX_MAGENTA       = 0xFF00FF,
    COLOR_HEX_OLIVE         = 0x808000,
    COLOR_HEX_KHAKI         = 0xF0E68C,
    COLOR_HEX_LAWN_GREEN    = 0x7CFC00,
    COLOR_HEX_SPRING_GREEN  = 0x00FF7F,
    COLOR_HEX_MIDNIGHT_BLUE = 0x191970,
    COLOR_HEX_BLUE_VIOLET   = 0x8A2BE2,
    COLOR_HEX_DARK_MAGENTA  = 0x8B008B
} color_hex_code_e;


// colors actively used are selected below
typedef enum
{
	COLORS_FIRST            = 0,
    COLORS_RED              = COLORS_FIRST,
    COLORS_DARK_RED,
    COLORS_MAROON,
    COLORS_SALMON,
    COLORS_ORANGE_RED,
    COLORS_ORANGE,
    COLORS_GOLD,
    COLORS_YELLOW,
    COLORS_GREEN,
    COLORS_MINT,
    COLORS_FOREST_GREEN,
    COLORS_TEAL,
    COLORS_CYAN,
    COLORS_AQUA_MARINE,
    COLORS_BLUE,
    COLORS_NAVY,
    COLORS_DARK_BLUE,
    COLORS_PURPLE,
    COLORS_VIOLET,
    COLORS_INDIGO,
    COLORS_PLUM,
    COLORS_PINK,
    COLORS_HOT_PINK,
    COLORS_DEEP_PINK,
    COLORS_BROWN,
    COLORS_CHOCOLATE,
    COLORS_WHITE,
    COLORS_GRAY,
    COLORS_SILVER,
    COLORS_BLACK,
    COLORS_LIME,
    COLORS_MAGENTA,
    COLORS_OLIVE,
    COLORS_KHAKI,
    COLORS_LAWN_GREEN,
    COLORS_SPRING_GREEN,
    COLORS_MIDNIGHT_BLUE,
    COLORS_BLUE_VIOLET,
    COLORS_DARK_MAGENTA,
	COLORS_LAST = COLORS_DARK_MAGENTA,
    NUM_COLORS,
    COLORS_LAST_ENTRY = UINT16_MAX - 1
} all_colors_e;


void color_led_hex_to_rgb(const color_hex_code_e color, uint8_t *color_array);


#endif

