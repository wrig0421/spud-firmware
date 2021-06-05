// Spud 2021

// typedefs, structs, enums
typedef enum
{
    // R(8 bit)G(8 bit)B(8 bit)
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
    COLORS_WHITE,
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


// local prototypes
bool color_led_adjust_color(void);
void color_led_reset_color(void);
void color_led_randomize(void);
void color_led_init(void);
uint8_t color_led_cur_color_red_hex(void);
uint8_t color_led_cur_color_green_hex(void);
uint8_t color_led_cur_color_blue_hex(void);
uint8_t color_led_white_hex(void);
color_hex_code_e color_led_cur_color_hex(void);




