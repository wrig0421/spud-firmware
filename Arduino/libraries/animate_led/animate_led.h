// Spud 2021

#if !defined(ANIMATE_LED_H)

#define ANIMATE_LED_H
#include <stdint.h>
#include <stdbool.h> 

// static definitions
//#define TOGETHER_SIGN
//#define SCHUMACHER_SIGN
//#define SPUDS_PUB_SIGN
#define GOOD_VIBES_SIGN

#if defined(GOOD_VIBES_SIGN)
#define MULTIPLE_STRIPS
#endif

#if defined(GOOD_VIBES_SIGN)
#define STRIP_1_LENGTH	294
#define STRIP_2_LENGTH	452
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


typedef enum
{
#if defined(STRIP_1_LENGTH)
	STRIP_NUM_1,
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
	ALL_STRIPS = NUM_STRIPS
} strip_num_e;

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
	//LED_STATE_WHITE_COLOR = LED_STATE_FIRST,
    LED_STATE_FADE_IN_AND_OUT = LED_STATE_FIRST,
    //LED_STATE_FADE_IN_AND_OUT_RANDOM,
    LED_STATE_SOLID_COLOR,
	LED_STATE_STROBE,
	LED_STATE_SPELL_SOLID_RANDOM_COLOR,
	LED_STATE_SPELL_SOLID_WHITE_COLOR,
	LED_STATE_SPELL_SPARKLE_FILL,
	LED_STATE_SPELL_SPARKLE_NO_FILL,
	LED_STATE_SPELL,
    //LED_STATE_KITT,
    LED_STATE_CYCLONE_BOUNCE,
    //LED_STATE_RANDOM,
    LED_STATE_SPARKLE_NO_FILL,
    LED_STATE_SPARKLE_FILL,
   //LED_STATE_RUNNING_LIGHTS,
    LED_STATE_RAINBOW_CYCLE,
    LED_STATE_THEATER_CHASE,
    LED_STATE_THEATER_CHASE_RAINBOW,
    //LED_STATE_FIRE,
    //LED_STATE_BOUNCING_BALLS,
    //LED_STATE_BOUNCING_BALLS_RANDOM,
    LED_STATE_TWO_TONE,
    LED_STATE_TWINKLE,
    LED_STATE_METEOR,
	LED_STATE_LAST = LED_STATE_METEOR,
    NUM_LED_STATES
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


// local prototypes
bool animate_led_adjust_state(void);
bool animate_led_interrupt_flag(isr_e src);
void animate_led_solid_custom_color(strip_num_e strip, byte red, byte green, byte blue);
void animate_led_solid_color(strip_num_e strip);
void animate_led_set_interrupt_flag(isr_e src);
void animate_led_reset_iterations(void);
void animate_led_spell_word(strip_num_e strip, uint16_t speed_delay);
void animate_led_reset_state(void);
void animate_led_adjust_speed(void);
void animate_led_init(void);
void animate_led_increment_iterations(void);
void animate_led_show_strip(void);
void animate_led_set_pixel(strip_num_e strip, int i, byte red, byte green, byte blue);
void animate_led_set_all_pixels(strip_num_e strip, byte red, byte green, byte blue);
void animate_led_state_randomize(void);
void animate_led_cyclone_bounce(strip_num_e strip);
void animate_led_fade_in_fade_out(strip_num_e strip);
void animate_led_sparkle_random_color(strip_num_e strip, bool fill, uint16_t speed_delay);
void animate_led_strobe(strip_num_e strip, uint16_t animate_led_strobe_count, uint16_t flash_delay, uint16_t end_pause);
void animate_led_cyclone_bounce(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_new_kitt(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_center_to_outside(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_outside_to_center(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_left_to_right(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_right_to_left(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_twinkle(strip_num_e strip, uint16_t count, uint16_t speed_delay, bool only_one);
void animate_led_twinkle_random(strip_num_e strip, uint16_t count, uint16_t speed_delay, bool only_one);
void animate_led_sparkle(strip_num_e strip, uint16_t speed_delay);
void animate_led_running_lights(strip_num_e strip);
void animate_led_color_wipe(strip_num_e strip, uint16_t speed_delay);
void animate_led_rainbow_cycle(strip_num_e strip, uint16_t speed_delay);
void animate_led_set_solid_white_color(void);
void animate_led_theater_chase(strip_num_e strip, uint16_t speed_delay);
void animate_led_theater_chase_rainbow(strip_num_e strip, uint16_t speed_delay);
void animate_led_bouncing_balls(strip_num_e strip, int ball_count);
void animate_led_meteor_rain(strip_num_e strip, byte meteor_size, byte meteor_trail_decay, bool meteor_random_decay, int speed_delay);
void animate_led_fade_to_black(strip_num_e strip, int led_no, byte fade_value);
void animate_led_spell_and_sparkle(strip_num_e spell_strip, strip_num_e sparkle_strip, bool fill, uint16_t speed_delay);
float animate_led_delay_in_animations(void);
uint16_t animate_led_delay_between_animations(void);
uint32_t animate_led_iterations(void);
led_state_e animate_led_state(void);
byte* animate_led_wheel(byte wheel_pos);
void animate_led_two_tone(uint32_t color_strip_1, uint32_t color_strip_2);

#endif
