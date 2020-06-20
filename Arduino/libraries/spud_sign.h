#include "stdint.h"
#include "stdbool.h"

#define STRIP_SIZE  276  

// 'S' [0, 62]
// 'P' [63, 130]
// 'U' [131, 199]
// 'D' [200, 276]  

#define S_PIXEL_NUM_START				0
#define S_LEFT_PIXEL_NUM				0
#define S_BOTTOM_PIXEL_NUM				0
#define S_TOP_PIXEL_NUM				
#define S_RIGHT_PIXEL_NUM				0
#define S_LEFT_TO_TOP_PIXEL				
#define S_PIXEL_NUM_STOP				62

#define P_PIXEL_NUM_START				63
#define P_POST_PIXEL_NUM_STOP			64
#define P_TOP_CURVE_PIXEL_NUM_START		64 
#define P_MIDPOINT_PIXEL_NUM			66
#define P_RIGHT_PIXEL_NUM				0
#define P_PIXEL_NUM_STOP				130

#define U_PIXEL_NUM_START				131
#define U_BOTTOM_PIXEL_NUM 				131
#define U_PIXEL_NUM_STOP				199

#define D_PIXEL_NUM_START				200
#define D_POST_PIXEL_NUM_STOP			200
#define D_TOP_CURVE_PIXEL_NUM_START		200
//#define D_TOP_CURVE_PIXEL_NUM_STOP		200 // same as last pixel..
#define D_RIGHT_PIXEL_NUM				200
#define D_PIXEL_NUM_STOP				276  

#define VERTICAL_POST_NUM_PIXELS		D_PIXEL_NUM_START - D_POST_PIXEL_NUM_STOP

typedef enum
{
    S_LETTER = 0,
    P_LETTER,
    U_LETTER,
    D_LETTER,
    NUM_LETTERS,
} letters_in_sign_t;


typedef enum
{
    red = 0,
    orange,
    green,
    blue,
    indigo,
    violet,
    black,
    white,
    yellow,
    cyan,
    magenta,
    lime,
    maroon,
    olive,
    chocolate,
    gold,
    num_colors,
} color_list_e;


typedef enum
{
	disp_red = 0,
    disp_orange,
    disp_green,
    disp_blue,
    disp_indigo,
    disp_violet,
    disp_white,
    disp_yellow,
    disp_cyan,
    disp_magenta,
    //disp_chocolate,
    disp_num_colors_disp,
} display_colors_e;


struct colors 
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

void strip_init(void);
void show_strip(void);
void strip_clear(uint16_t strip_size);
void strip_set_brightness(uint8_t brightness);
void strip_turn_off_pixel(uint16_t pixel);
void strip_turn_on_pixel(uint16_t pixel, display_colors_e color);
void twinkle(void);
letters_in_sign_t draw_letter(letters_in_sign_t letter, display_colors_e color);
void crash(display_colors_e color_left, display_colors_e color_right, display_colors_e blend_color, uint16_t delay_time);
void draw_letters(display_colors_e color, uint16_t delay_time);
void blink_word(display_colors_e color, uint16_t strip_size, uint16_t delay_time);
void fade_letter_l_to_r(letters_in_sign_t letter, display_colors_e color, uint16_t delay_time);
void fade_letter_r_to_l(letters_in_sign_t letter, display_colors_e color, uint16_t delay_time);
void fade_word_bottom_to_top(display_colors_e color, uint16_t delay_time);
void fade_word(display_colors_e color, uint16_t delay_time, bool l_to_r);
void fade_word_top_to_bottom(display_colors_e color, uint16_t delay_time);
void draw_word(display_colors_e color, uint16_t strip_size, bool spell, float speed_factor);
