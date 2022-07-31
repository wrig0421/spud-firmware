
#if !defined(COLOR_LED_H)
#define COLOR_LED_H

#define COLOR_LED_MAX_BRIGHTNESS_DIVISOR	(4)


typedef enum
{
    MASTER_COLOR_STATE_DEMO,
    MASTER_COLOR_STATE_FIXED
} master_color_state_e;


typedef enum
{
    // RGB
    COLOR_HEX_BLACK = 0x000000,
    COLOR_HEX_WHITE = 0xFFFFFF,
    COLOR_HEX_RED = 0xFF0000,
    COLOR_HEX_LIME = 0x00FF00,
    COLOR_HEX_BLUE = 0x0000FF,
    COLOR_HEX_YELLOW = 0xFFFF00,
    COLOR_HEX_CYAN = 0x00FFFF,
    COLOR_HEX_MAGENTA = 0xFF00FF,
    COLOR_HEX_SILVER = 0xC0C0C0,
    COLOR_HEX_GRAY = 0x808080,
    COLOR_HEX_MAROON = 0x800000,
    COLOR_HEX_OLIVE = 0x808000,
    COLOR_HEX_GREEN = 0x008000,
    COLOR_HEX_PURPLE = 0x800080,
    COLOR_HEX_TEAL = 0x008080,
    COLOR_HEX_NAVY = 0x000080
} color_hex_code_e;


typedef enum
{
    //COLORS_BLACK = 0,
    //COLORS_WHITE,
	COLORS_FIRST = 0,
    COLORS_RED = COLORS_FIRST,
    COLORS_LIME,
    COLORS_BLUE,
    COLORS_YELLOW,
    COLORS_CYAN,
    COLORS_MAGENTA,
    //COLORS_SILVER,
    //COLORS_GRAY,
    //COLORS_MAROON,
    //COLORS_OLIVE,
    COLORS_GREEN,
    COLORS_PURPLE,
    COLORS_TEAL,
    COLORS_NAVY,
	COLORS_LAST = COLORS_NAVY,
    NUM_COLORS
} all_colors_e;

master_color_state_e color_led_cur_state(void);
void color_led_exit_demo_state(void);
void color_led_enter_demo_state(void);
all_colors_e color_led_cur_color(void);
uint32_t color_led_get_random_color(void);
void color_led_reset_color(void);
bool color_led_adjust_color(void);
color_hex_code_e color_led_cur_color_hex(void);
uint8_t color_led_cur_color_red_hex(void);
uint8_t color_led_cur_color_green_hex(void);
uint8_t color_led_cur_color_blue_hex(void);

//color_hex_code_e color_led_random(all_colors_e cur_color);
void color_led_randomize(void);
void color_led_init(void);


#endif

