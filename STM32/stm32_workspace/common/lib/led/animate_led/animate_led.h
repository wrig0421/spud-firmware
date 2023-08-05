/***********************************
 * @file   animate_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(ANIMATE_LED_H)
#define ANIMATE_LED_H

#include <stdint.h>
#include <stdbool.h> 
#include "config.h"
#include "board_init_common.h"
#include "ws2812b.h"
#include "color_led.h"


typedef enum
{
    MASTER_LED_STATE_DEMO,
    MASTER_LED_STATE_FIXED
} master_led_state_e;


typedef struct
{
    // byte 0
    uint8_t spell : 1;
    uint8_t white : 1;
    uint8_t solid : 1;
    uint8_t sparkle : 1;
    uint8_t sparkle_no_fill : 1;
    uint8_t rainbow : 1;
    uint8_t chase : 1;
    uint8_t chase_rainbow : 1;

    // byte 1
    uint8_t fade : 1;
    uint8_t twinkle : 1;
    uint8_t rsvd0 : 6;

    // byte 2
    uint8_t rsvd1;

    // byte 3
    uint8_t rsvd2;

    // these can be applied to each strip..
} animate_led_state_t;


typedef enum
{
	LED_STATE_FIRST = 0,
	LED_STATE_SPELL = LED_STATE_FIRST,
	//LED_STATE_MINT_NOHBZ,
	LED_STATE_WHITE_COLOR,
	LED_STATE_SOLID_COLOR,
	LED_STATE_SPARKLE_NO_FILL,
    LED_STATE_SPARKLE_FILL,
    LED_STATE_RAINBOW_CYCLE,
    LED_STATE_THEATER_CHASE,
    LED_STATE_THEATER_CHASE_RAINBOW,
    LED_STATE_FADE_IN_AND_OUT,
    LED_STATE_TWINKLE,
    LED_STATE_LAST = LED_STATE_TWINKLE,
    NUM_LED_STATES,
    LED_STATE_SRW_DEBUG,
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
	//LED_SPEED_2X,
	LED_SPEED_1X,
	LED_SPEED_0P5X,
	LED_SPEED_0P25X,
	//LED_SPEED_0P1X,
	LED_SPEED_LAST = LED_SPEED_0P25X,
	NUM_SPEEDS,
	LED_SPEED_INVALID
} led_speed_e;


typedef enum
{
    LED_BRIGHTNESS_FIRST = 0,
    LED_BRIGHTNESS_100_PERCENT  = LED_BRIGHTNESS_FIRST,
    LED_BRIGHTNESS_75_PERCENT,
    LED_BRIGHTNESS_50_PERCENT,
    LED_BRIGHTNESS_25_PERCENT,
    LED_BRIGHTNESS_1_PERCENT,
    LED_BRIGHTNESS_LAST         = LED_BRIGHTNESS_1_PERCENT,
    LED_BRIGHTNESS_INVALID
} led_brightness_e;

void animate_led_show_strip(const strip_mask_t strip_mask);
void animate_led_set_pixel(const strip_mask_t mask, const uint16_t pixel, const uint8_t red, const uint8_t green,
                           const uint8_t blue);
void animate_led_set_all_pixels(const strip_mask_t mask, const uint8_t red, const uint8_t green, const uint8_t blue);
void animate_led_multiple_solid_custom_colors(const strip_mask_t mask_solid, const uint32_t* color_array);
void animate_led_solid_custom_color(const strip_mask_t mask_solid, const color_hex_code_e color_spell);
void animate_led_turn_all_pixels_off(void);
void animate_led_spell_and_sparkle(const strip_mask_t mask_spell, const strip_mask_t mask_sparkle,
                                   const color_hex_code_e color_spell, const bool fill, const uint16_t speed_delay);
void animate_led_spell_and_solid_color(const strip_mask_t mask_spell, const strip_mask_t mask_solid,
                                       const color_hex_code_e color_spell, const color_hex_code_e color_solid,
                                       const uint16_t speed_delay);
void animate_led_spell_word_multiple_colors(const strip_mask_t mask_spell, const color_hex_code_e* color_array,
                                            const uint16_t speed_delay);
void animate_led_only_spell_word(const strip_mask_t mask_spell, const color_hex_code_e color_spell,
                                 const uint16_t time_ms);
void animate_led_fade_in_fade_out_multiple_colors(const strip_mask_t strip_mask, const uint32_t* color_array);
void animate_led_fade_in_fade_out(const strip_mask_t mask_fade, const color_hex_code_e color_fade);
void animate_led_strobe(const strip_mask_t mask_strobe, const color_hex_code_e color_strobe,
                        const uint16_t animate_led_strobe_count, const uint16_t flash_delay, const uint16_t end_pause);
void animate_led_twinkle_multiple_colors(const strip_mask_t mask_twinkle, const uint32_t* color_array,
                                         const uint16_t count, const uint16_t speed_delay, const bool only_one);
void animate_led_twinkle(const strip_mask_t twinkle_mask, const color_hex_code_e color_twinkle, const uint16_t count,
                         const uint16_t speed_delay, const bool only_one);
void animate_led_twinkle_random(const strip_mask_t mask_twinkle_random, const uint16_t count,
                                const uint16_t speed_delay, const bool only_one);
void animate_led_sparkle_only_random_color(const strip_mask_t mask_sparkle_random, const bool fill,
                                           const uint16_t speed_delay);
void animate_led_sparkle_random_color(const strip_mask_t mask_sparkle_random, const bool fill,
                                      const uint16_t speed_delay);
void animate_led_sparkle(const strip_mask_t mask_sparkle, const color_hex_code_e color_sparkle,
                         const uint16_t speed_delay);
void animate_led_running_lights(const strip_mask_t mask_running_lights, const color_hex_code_e color_running_lights);
void animate_led_rainbow_cycle(const strip_mask_t mask_rainbow_cycle, const uint16_t speed_delay);
uint8_t* animate_led_wheel(uint8_t wheel_pos);
void animate_led_theater_chase_multiple_colors(const strip_mask_t mask_theater_chase, const uint32_t* color_array,
                                               const uint16_t speed_delay);
void animate_led_theater_chase(const strip_mask_t mask_theater_chase, const color_hex_code_e color_theater_chase,
                               const uint16_t speed_delay);
void animate_led_theater_chase_rainbow(const strip_mask_t mask_theater_chase, const uint16_t speed_delay);


#endif
