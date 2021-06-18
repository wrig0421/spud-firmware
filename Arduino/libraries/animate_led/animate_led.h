#include <stdint.h>
#include <stdbool.h>

//#define NUM_LEDS 420 //Schumacher sign
#define NUM_LEDS 292 // Together sign


typedef enum
{
    ISR_SPEED = 0,
    ISR_STATE,
    ISR_COLOR,
    //ISR_PAUSE,
    NUM_ISR
} isr_e;




typedef enum
{
	LED_STATE_FIRST = 0,
    LED_STATE_FADE_IN_AND_OUT = LED_STATE_FIRST,
    //LED_STATE_FADE_IN_AND_OUT_RANDOM,
    LED_STATE_SOLID_COLOR,
	LED_STATE_STROBE,
	LED_STATE_SPELL,
    //LED_STATE_KITT,
    LED_STATE_TWINKLE,
    LED_STATE_CYCLONE_BOUNCE,
    //LED_STATE_RANDOM,
    LED_STATE_SPARKLE,
    LED_STATE_RUNNING_LIGHTS,
    LED_STATE_RAINBOW_CYCLE,
    LED_STATE_THEATER_CHASE,
    LED_STATE_THEATER_CHASE_RAINBOW,
    //LED_STATE_FIRE,
    //LED_STATE_BOUNCING_BALLS,
    //LED_STATE_BOUNCING_BALLS_RANDOM,
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

void animate_led_solid_color(void);
void animate_led_set_interrupt_flag(isr_e src);
void animate_led_reset_iterations(void);
//void animate_led_clear_interrupt_flag(void);
bool animate_led_interrupt_flag(isr_e src);
void animate_led_spell_word(uint16_t speed_delay);
void animate_led_reset_state(void);
uint32_t animate_led_iterations(void);
led_state_e animate_led_state(void);
byte* animate_led_wheel(byte wheel_pos);
void animate_led_adjust_speed(void);
bool animate_led_adjust_state(void);
void animate_led_init(void);
void animate_led_increment_iterations(void);
void animate_led_show_strip(void);
void animate_led_set_pixel(int Pixel, byte red, byte green, byte blue);
void animate_led_set_all_pixels(byte red, byte green, byte blue);
void animate_led_state_randomize(void);
void animate_led_cyclone_bounce(void);
void animate_led_fade_in_fade_out(void);
void animate_led_strobe(uint16_t animate_led_strobe_count, uint16_t flash_delay, uint16_t end_pause);
void animate_led_cyclone_bounce(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_new_kitt(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_center_to_outside(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_outside_to_center(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_left_to_right(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_right_to_left(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void animate_led_twinkle(uint16_t count, uint16_t speed_delay, bool only_one);
void animate_led_twinkle_random(uint16_t count, uint16_t speed_delay, bool only_one);
void animate_led_sparkle(uint16_t speed_delay);
void animate_led_running_lights(void);
void animate_led_color_wipe(uint16_t speed_delay);
void animate_led_rainbow_cycle(uint16_t speed_delay);

void animate_led_theater_chase(uint16_t speed_delay);
void animate_led_theater_chase_rainbow(uint16_t speed_delay);
void animate_led_bouncing_balls(int ball_count);
void animate_led_meteor_rain(byte meteor_size, byte meteor_trail_decay, bool meteor_random_decay, int speed_delay);
void animate_led_fade_to_black(int led_no, byte fade_value);

float animate_led_delay_in_animations(void);
uint16_t animate_led_delay_between_animations(void);
