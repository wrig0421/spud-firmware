// together sign library to support development SRW

#include "stdint.h"
#include "stdbool.h"

#define STRIP_SIZE  293

// 'T' [0, 21]
#define T_FIRST_PIXEL_NUM_START     0
#define T_FIRST_PIXEL_NUM_MID		6
#define T_FIRST_PIXEL_NUM_STOP      21
#define T_FIRST_TOP_POST_LENGTH		10
#define T_FIRST_MID_POST_LENGTH		10
#define T_FIRST_MID_POST_PIXEL_NUM_START	T_FIRST_PIXEL_NUM_START + T_FIRST_TOP_POST_LENGTH + 1

// 'O' [22, 59]
#define O_PIXEL_NUM_START           22
#define O_PIXEL_NUM_STOP            59
#define O_PIXEL_NUM_LEFT_MID		22 + 9 
#define O_PIXEL_NUM_RIGHT_MID		O_PIXEL_NUM_STOP - 9 
#define O_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_MID	9
#define O_PIXEL_NUM_BOTTOM			O_PIXEL_NUM_START + 18

// 'G' [60, 98]
#define G_PIXEL_NUM_START           60
#define G_PIXEL_NUM_STOP            98
#define G_PIXEL_NUM_LEFT_MID		60 + 14
#define G_PIXEL_NUM_RIGHT_MID		98 - 7
#define G_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_LEFT_MID	9
#define G_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_RIGHT_MID	7
#define G_PIXEL_NUM_BOTTOM			G_PIXEL_NUM_START + 24
#define G_PIXEL_NUM_TOP				G_PIXEL_NUM_START + 5
#define G_PIXEL_NUM_MID_POST		6

// 'E' [99, 143]  
#define E_FIRST_PIXEL_NUM_START     99
#define E_FIRST_PIXEL_NUM_STOP      143
#define E_FIRST_LEFT_POST_START		99
#define E_FIRST_LEFT_POST_LENGTH	11 // should this be 12?

#define E_FIRST_COMMON_POST_LENGTH	11
#define E_FIRST_TOP_POST_START		E_FIRST_LEFT_POST_START + E_FIRST_LEFT_POST_LENGTH + 1
#define E_FIRST_MID_POST_START		E_FIRST_TOP_POST_START + E_FIRST_COMMON_POST_LENGTH
#define E_FIRST_BOTTOM_POST_START	E_FIRST_MID_POST_START + E_FIRST_COMMON_POST_LENGTH 

// 'T' [144, 166]
#define T_LAST_PIXEL_NUM_START      144
#define T_LAST_PIXEL_NUM_MID		T_LAST_PIXEL_NUM_START + 6
#define T_LAST_PIXEL_NUM_STOP       166
#define T_LAST_TOP_POST_LENGTH		11	
#define T_LAST_MID_POST_LENGTH		10	
#define T_LAST_MID_POST_PIXEL_NUM_START	T_LAST_PIXEL_NUM_START + T_LAST_TOP_POST_LENGTH + 1


// 'H' [167, 200]
#define H_PIXEL_NUM_START           167
#define H_PIXEL_NUM_STOP            200
#define H_LEFT_POST_LENGTH			11
#define H_MID_PIXEL_NUM_START		H_PIXEL_NUM_START + 12
#define H_MID_POST_LENGTH			9
#define H_RIGHT_PIXEL_NUM_START		H_MID_PIXEL_NUM_START + H_MID_POST_LENGTH + 1
#define H_RIGHT_POST_LENGTH			11

// 'E' [201, 245]
#define E_LAST_PIXEL_NUM_START      201
#define E_LAST_PIXEL_NUM_STOP       245
//#define E_LAST_PIXEL_NUM_STOP       246
#define E_LAST_LEFT_POST_LENGTH		11
#define E_LAST_TOP_POST_LENGTH
#define E_LAST_MID_POST_LENGTH
#define E_LAST_BOTTOM_POST_LENGTH

#define E_LAST_COMMON_POST_LENGTH	10
#define E_LAST_LEFT_POST_START		E_LAST_PIXEL_NUM_START
#define E_LAST_TOP_POST_START		E_LAST_LEFT_POST_START + E_LAST_LEFT_POST_LENGTH + 1
#define E_LAST_MID_POST_START		E_LAST_TOP_POST_START + E_LAST_COMMON_POST_LENGTH + 1
#define E_LAST_BOTTOM_POST_START	E_LAST_MID_POST_START + E_LAST_COMMON_POST_LENGTH + 1

#define G_R_CURVE_NUM_PIXELS_FROM_TOP	3

// 'R' [246, 291]
#define R_PIXEL_NUM_START           	246
#define R_PIXEL_NUM_STOP            	291
#define R_LEFT_POST_LENGTH				12
#define R_CURVE_PIXEL_NUM_START			R_PIXEL_NUM_START + R_LEFT_POST_LENGTH + 1
#define R_CURVE_LENGTH					22
#define R_CURVE_PIXEL_NUM_STOP			R_CURVE_PIXEL_NUM_START + R_CURVE_LENGTH
#define R_CURVE_RIGHT_MID_START			R_PIXEL_NUM_START + 24
#define R_END_POST_PIXEL_NUM_START		R_CURVE_PIXEL_NUM_STOP + 1
#define R_END_POST_LENGTH		

typedef enum
{
    T_LETTER_FIRST = 0,
    O_LETTER = 1,
    G_LETTER = 2,
    E_LETTER_FIRST = 3,
    T_LETTER_LAST,
    H_LETTER,
    E_LETTER_LAST,
    R_LETTER,
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


struct colors 
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

void strip_init(void);
void show_strip(void);
void strip_set_brightness(uint8_t brightness);
void strip_turn_off_pixel(uint16_t pixel);
void strip_turn_on_pixel(uint16_t pixel, color_list_e color);
void twinkle(void);
letters_in_sign_t draw_letter(letters_in_sign_t letter, color_list_e color);
void crash(color_list_e color_left, color_list_e color_right, color_list_e blend_color, uint16_t delay_time);
void draw_letters(color_list_e color, uint16_t delay_time);
void draw_word(color_list_e color, uint16_t strip_size, uint16_t delay_time, bool spell);
void blink_word(color_list_e color, uint16_t strip_size, uint16_t delay_time);
void fade_letter_l_to_r(letters_in_sign_t letter, color_list_e color, uint16_t delay_time);
void fade_letter_r_to_l(letters_in_sign_t letter, color_list_e color, uint16_t delay_time);
void fade_word_bottom_to_top(color_list_e color, uint16_t delay_time);
void fade_word(color_list_e color, uint16_t delay_time, bool l_to_r);
void fade_word_top_to_bottom(color_list_e color, uint16_t delay_time);


