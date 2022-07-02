// Spud 2021

#if !defined(ANIMATE_LED_H)

#define ANIMATE_LED_H
#include <stdint.h>
#include <stdbool.h> 

// static definitions
//#define TOGETHER_SIGN
//#define SCHUMACHER_SIGN
//#define SPUDS_PUB_SIGN
//#define GOOD_VIBES_SIGN
#define PATTYS_PUB_SIGN
//#define DEBUG

//#define SRW_DEBUG

#if defined(GOOD_VIBES_SIGN) || defined (DEBUG)
//#define MULTIPLE_STRIPS
#endif

#if defined(DEBUG)
#define STRIP_1_LENGTH	300
//#define STRIP_2_LENGTH	18*10
//#define STRIP_3_LENGTH	18*10
//#define STRIP_4_LENGTH	18*10
//#define STRIP_5_LENGTH	18*10
//#define NUM_LEDS STRIP_1_LENGTH + STRIP_2_LENGTH + STRIP_3_LENGTH + STRIP_4_LENGTH
#define NUM_LEDS 300 // Together sign

#elif defined(PATTYS_PUB_SIGN)
#define STRIP_1_LENGTH 	210 // ???? VERIFY THE FUCKING VALUE
#define NUM_LEDS 		STRIP_1_LENGTH

#elif defined(GOOD_VIBES_SIGN)
#define STRIP_1_LENGTH	294
#define STRIP_2_LENGTH	452
//#define STRIP_1_LENGTH	452
//#define STRIP_2_LENGTH	294
#define NUM_LEDS STRIP_1_LENGTH + STRIP_2_LENGTH // 294 (from upper) + 450 (from lower)
#elif defined(SCHUMACHER_SIGN)
#define STRIP_1_LENGTH	420
#define NUM_LEDS 420 //Schumacher sign
#elif defined(SPUDS_PUB_SIGN)
#define STRIP_1_LENGTH	212
#define NUM_LEDS 212 // Spud's pub sign
#elif defined(TOGETHER_SIGN)
#define STRIP_1_LENGTH	292
#define NUM_LEDS 292 // Together sign
#else
#error "No sign definition"
#endif

#if defined(STRIP_2_LENGTH) || defined(STRIP_3_LENGTH) || defined(STRIP_4_LENGTH) || defined(STRIP_5_LENGTH) || defined(STRIP_6_LENGTH) || defined(STRIP_7_LENGTH) || defined(STRIP_8_LENGTH) || defined(STRIP_9_LENGTH)
#define MULTIPLE_STRIPS
#endif

typedef uint16_t strip_mask_t;

typedef enum
{
#if defined(STRIP_1_LENGTH)
	STRIP_NUM_1 = 0,
#endif
#if defined(STRIP_2_LENGTH)
	STRIP_NUM_2,
#endif
#if defined(STRIP_3_LENGTH)
	STRIP_NUM_3,
#endif
#if defined(STRIP_4_LENGTH)
	STRIP_NUM_4,
#endif
#if defined(STRIP_5_LENGTH)
	STRIP_NUM_5,
#endif
#if defined(STRIP_6_LENGTH)
	STRIP_NUM_6,
#endif
#if defined(STRIP_7_LENGTH)
	STRIP_NUM_7,
#endif
#if defined(STRIP_8_LENGTH)
	STRIP_NUM_8,
#endif
#if defined(STRIP_9_LENGTH)
	STRIP_NUM_9,
#endif
	NUM_STRIPS,
} strip_num_e;


// I want to add support for case of say strip 1 & 3 on all others off.
// Want to pass something like STRIP_1 | STRIP_3 turn on both!
typedef enum
{
	STRIP_BIT_NONE_SET = 0,
#if defined(STRIP_1_LENGTH)
	STRIP_BIT_1 = 1,
#endif
#if defined(STRIP_2_LENGTH)
	STRIP_BIT_2 = (1 << 1),
#endif
#if defined(STRIP_3_LENGTH)
	STRIP_BIT_3 = (1 << 2),
#endif
#if defined(STRIP_4_LENGTH)
	STRIP_BIT_4 = (1 << 3),
#endif
#if defined(STRIP_5_LENGTH)
	STRIP_BIT_5 = (1 << 4),
#endif
#if defined(STRIP_6_LENGTH)
	STRIP_BIT_6 = (1 << 5),
#endif
#if defined(STRIP_7_LENGTH)
	STRIP_BIT_7 = (1 << 6),
#endif
#if defined(STRIP_8_LENGTH)
	STRIP_BIT_8 = (1 << 7),
#endif
#if defined(STRIP_9_LENGTH)
	STRIP_BIT_9 = (1 << 8),
#endif
	STRIP_BIT_NUM_STRIPS = NUM_STRIPS,
	STRIP_BIT_NO_MORE_SET, 
	// brute force assignment below 
#if defined(STRIP_9_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4 | STRIP_BIT_5 | STRIP_BIT_6 | STRIP_BIT_7 | STRIP_BIT_8 | STRIP_BIT_9
#elif defined(STRIP_8_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4 | STRIP_BIT_5 | STRIP_BIT_6 | STRIP_BIT_7 | STRIP_BIT_8
#elif defined(STRIP_7_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4 | STRIP_BIT_5 | STRIP_BIT_6 | STRIP_BIT_7
#elif defined(STRIP_6_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4 | STRIP_BIT_5 | STRIP_BIT_6			
#elif defined(STRIP_5_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4 | STRIP_BIT_5
#elif defined(STRIP_4_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4
#elif defined(STRIP_3_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3
#elif defined(STRIP_2_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2
#elif defined(STRIP_1_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1
#endif
} strip_bit_e;


// typedefs, structs, enums
typedef enum
{
    ISR_SPEED = 0,
    ISR_STATE,
    ISR_COLOR,
    ISR_PAUSE,
    NUM_ISR
} isr_e;


typedef enum
{
	LED_STATE_FIRST = 0,
	LED_STATE_WHITE_COLOR = LED_STATE_FIRST,
	LED_STATE_SOLID_COLOR,
	LED_STATE_SPARKLE_NO_FILL,
    LED_STATE_SPARKLE_FILL,
    LED_STATE_RAINBOW_CYCLE,
    LED_STATE_THEATER_CHASE,
    LED_STATE_THEATER_CHASE_RAINBOW,
    LED_STATE_FADE_IN_AND_OUT,
    LED_STATE_TWINKLE,
    LED_STATE_SPELL,
#if defined(SRW_DEBUG)
    LED_STATE_SRW_DEBUG,
#endif
#if defined(MULTIPLE_STRIPS)
	LED_STATE_FADE_IN_AND_OUT_MULTIPLE_COLORS,
	LED_STATE_MULTIPLE_COLORS,
	LED_STATE_RAINBOW_CYCLE_TWO_TONE,
	LED_STATE_THEATER_CHASE_MULTIPLE_COLORS,
	LED_STATE_TWINKLE_MULTIPLE_COLORS,
	LED_STATE_SPELL_MULTIPLE_COLORS,
	LED_STATE_SPELL_SOLID_RANDOM_COLOR,
	LED_STATE_SPELL_SPARKLE_FILL,
	LED_STATE_SPELL_SPARKLE_NO_FILL,
	LED_STATE_LAST = LED_STATE_SPELL_SPARKLE_NO_FILL,
#elif defined(SRW_DEBUG)
	LED_STATE_LAST = LED_STATE_SRW_DEBUG,
#else
	LED_STATE_LAST = LED_STATE_SPELL,
#endif
	NUM_LED_STATES,
	// future states below 
	//LED_STATE_FADE_IN_AND_OUT_RANDOM,
    //LED_STATE_METEOR,
    //LED_STATE_STROBE,
    //LED_STATE_SPELL_SOLID_WHITE_COLOR,
    //LED_STATE_KITT,
    //LED_STATE_CYCLONE_BOUNCE,
    //LED_STATE_RANDOM,
    //LED_STATE_RUNNING_LIGHTS,
    //LED_STATE_FIRE,
    //LED_STATE_BOUNCING_BALLS,
    //LED_STATE_BOUNCING_BALLS_RANDOM,
} led_state_e;


typedef enum
{
	LED_SPEED_FIRST,
	LED_SPEED_10X = LED_SPEED_FIRST,
	LED_SPEED_5X,
	LED_SPEED_2X,
	LED_SPEED_1X,
	LED_SPEED_0P5X,
	LED_SPEED_0P25X,
	//LED_SPEED_0P1X,
	LED_SPEED_LAST = LED_SPEED_0P25X,
	NUM_SPEEDS
} led_speed_e;


void animate_led_reset_state(void);
void animate_led_set_interrupt_flag(isr_e src);
bool animate_led_interrupt_flag(isr_e src);
bool animate_led_interrupt_flag_speed(void);
bool animate_led_interrupt_flag_state(void);
bool animate_led_interrupt_flag_color(void);
uint16_t animate_led_delay_between_animations(void);
float animate_led_delay_in_animations(void);
void animate_led_adjust_speed(void);
bool animate_led_adjust_state(void);
void animate_led_init(void);
void animate_led_reset_iterations(void);
void animate_led_increment_iterations(void);
uint32_t animate_led_iterations(void);
led_state_e animate_led_state(void);
void animate_led_show_strip(void);
led_state_e animate_led_state_randomize(led_state_e cur_state);
void animate_led_solid_custom_color(const strip_mask_t strip_mask, color_hex_code_e color);
void animate_led_turn_all_pixels_off(void);
void animate_led_two_tone(uint32_t color_strip_1, uint32_t color_strip_2);
void animate_led_spell_word_multiple_colors(strip_mask_t strip_mask, uint32_t* color_array, uint16_t speed_delay);
void animate_led_spell_and_sparkle(const strip_mask_t spell_mask, const strip_mask_t sparkle_mask, color_hex_code_e color, bool fill, uint16_t speed_delay);
void animate_led_only_spell_word(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay);
void animate_led_fade_in_fade_out(strip_mask_t strip_mask, color_hex_code_e color);
void animate_led_strobe(strip_mask_t strip_mask, color_hex_code_e color, uint16_t animate_led_strobe_count, uint16_t flash_delay, uint16_t end_pause);
void animate_led_cyclone_bounce(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_center_to_outside(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_outside_to_center(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_left_to_right(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_right_to_left(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_new_kitt(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_twinkle(strip_mask_t strip_mask, color_hex_code_e color, uint16_t count, uint16_t speed_delay, bool only_one);
void animate_led_twinkle_random(strip_mask_t strip_mask, uint16_t count, uint16_t speed_delay, bool only_one);
void animate_led_sparkle_only_random_color(strip_mask_t strip_mask, bool fill, uint16_t speed_delay);
void animate_led_sparkle_random_color(strip_mask_t strip_mask, bool fill, uint16_t speed_delay);
void animate_led_sparkle(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay);
void animate_led_running_lights(strip_mask_t strip_mask, color_hex_code_e color);
void animate_led_color_wipe(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay);
void animate_led_rainbow_cycle(strip_mask_t strip_mask, uint16_t speed_delay);
byte* animate_led_wheel(byte wheel_pos);
void animate_led_theater_chase(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay);
void animate_led_theater_chase_rainbow(strip_mask_t strip_mask, uint16_t speed_delay);
void animate_led_bouncing_balls(strip_mask_t strip_mask, color_hex_code_e color, int ball_count);
void animate_led_meteor_rain(strip_mask_t strip_mask, color_hex_code_e color, byte meteor_size, byte meteor_trail_decay, bool meteor_random_decay, int speed_delay);
void animate_led_fade_to_black(strip_mask_t strip_mask, uint16_t pixel, byte fade_value);
void animate_led_set_pixel(strip_mask_t strip_mask, uint16_t pixel, byte red, byte green, byte blue);
void animate_led_spell_and_solid_color(const strip_mask_t spell_mask, const strip_mask_t solid_color_mask, color_hex_code_e color, uint16_t speed_delay);
void animate_led_set_all_pixels(strip_mask_t strip_mask, byte red, byte green, byte blue);
uint16_t animate_led_get_number_of_active_strips(const strip_mask_t strip_mask);
void animate_led_fade_in_fade_out_multiple_colors(strip_mask_t strip_mask, uint32_t* color_array);
void animate_led_theater_chase_multiple_colors(strip_mask_t strip_mask, uint32_t* color, uint16_t speed_delay);
void animate_led_multiple_solid_custom_colors(strip_mask_t strip_mask, uint32_t* color_array);
void animate_led_twinkle_multiple_colors(strip_mask_t strip_mask, uint32_t* color_array, uint16_t count, uint16_t speed_delay, bool only_one);


#endif
