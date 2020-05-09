#include "stdint.h"
#include "stdbool.h"

#define STRIP_SIZE  132 // [0, 131]

// 'T' [0, 21]
#define N_LEFT_POST_PIXEL_NUM_START		0
#define N_LEFT_POST_PIXEL_NUM_STOP		10
#define N_MID_POST_PIXEL_NUM_START		11
#define N_MID_POST_PIXEL_NUM_STOP		24
#define N_RIGHT_POST_PIXEL_NUM_START	25
#define N_RIGHT_POST_PIXEL_NUM_STOP		35

#define VERTICAL_POST_NUM_PIXELS		10
#define TOP_TO_TAIL_NUM_PIXELS			4

#define O_PIXEL_NUM_START				36
#define O_PIXEL_NUM_LEFT_START			40
#define O_PIXEL_NUM_RIGHT_START			51
#define O_PIXEL_NUM_FROM_TOP_TO_MID		O_PIXEL_NUM_LEFT_START - O_PIXEL_NUM_START
#define O_PIXEL_NUM_BOTTOM_LEFT			45
#define O_PIXEL_NUM_BOTTOM_RIGHT		46
#define O_PIXEL_NUM_STOP				55

#define H_LEFT_POST_PIXEL_NUM_START		56
#define H_LEFT_POST_PIXEL_NUM_STOP		66
#define H_MID_PIXEL_NUM_START			67
#define H_MID_PIXEL_NUM_STOP			78

#define B_LEFT_POST_PIXEL_NUM_START		79
#define B_LEFT_POST_PIXEL_NUM_STOP		89
#define B_TOP_CURVE_TO_MID				8 // actually may be 7 hard to tell from my lazyboy ;)
#define B_MID_PIXEL_NUM_START			90
#define B_MID_POINT_PIXEL_NUM			98
#define B_MID_PIXEL_NUM_STOP			106

#define Z_TOP_POST_PIXEL_NUM_START		107
#define Z_TOP_POST_PIXEL_NUM_STOP		115
#define Z_MID_POST_PIXEL_NUM_START		116
#define Z_MID_POST_PIXEL_NUM_STOP		123
#define Z_BOTTOM_POST_PIXEL_NUM_START	124
#define Z_BOTTOM_POST_PIXEL_NUM_STOP	131		
#define Z_POST_LENGTH					Z_TOP_POST_PIXEL_NUM_STOP - Z_TOP_POST_PIXEL_NUM_START

typedef enum
{
    N_LETTER = 0,
    O_LETTER,
    H_LETTER,
    B_LETTER,
    Z_LETTER,
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
void blink_word(color_list_e color, uint16_t strip_size, uint16_t delay_time);
void fade_letter_l_to_r(letters_in_sign_t letter, color_list_e color, uint16_t delay_time);
void fade_letter_r_to_l(letters_in_sign_t letter, color_list_e color, uint16_t delay_time);
void fade_word_bottom_to_top(color_list_e color, uint16_t delay_time);
void fade_word(color_list_e color, uint16_t delay_time, bool l_to_r);
void fade_word_top_to_bottom(color_list_e color, uint16_t delay_time);
void draw_word(color_list_e color, uint16_t strip_size, bool spell);
