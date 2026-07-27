/***********************************
 * @file   animate_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(LED_ANIMATE_H)
#define LED_ANIMATE_H

#include <stdint.h>
#include <stdbool.h> 
#include "config.h"
#include "board_init_common.h"
#include "ws2812b.h"
#include "led_ctrl_color.h"

typedef enum
{
	LED_ANIMATE_STARBURTS_MODE_1,
	LED_ANIMATE_STARBURTS_MODE_2
} led_animate_starburst_mode_e;

void led_animate_show_strip(const strip_mask_t strip_mask);
void led_animate_set_pixel(const strip_mask_t mask, const uint16_t pixel, led_color_t* led_color);
void led_animate_set_all_pixels(const strip_mask_t mask, led_color_t* led_color);
void led_animate_set_all_pixels_hex_color(const strip_mask_t mask, const led_color_hex_code_e color);
void led_animate_set_pixels_in_range(const strip_mask_t mask, uint16_t start, uint16_t stop, const led_color_hex_code_e color);
void led_animate_set_pixels_in_range_skip_interrupt_check(const strip_mask_t mask, uint16_t start, uint16_t stop, const led_color_hex_code_e color);
void led_animate_set_pixels_in_range_and_show(const strip_mask_t mask, uint16_t start, uint16_t stop, const led_color_hex_code_e color);
void led_animate_set_pixels_in_range_uint32(const strip_mask_t mask, uint16_t start, uint16_t stop, uint32_t color_hex_code_val);
void led_animate_set_pixels_in_range_and_show_uint32(const strip_mask_t mask, uint16_t start, uint16_t stop, uint32_t color_hex_code_val);
void led_animate_turn_all_pixels_off(void);
void led_animate_turn_all_pixels_off_in_strip(const strip_mask_t mask);
void led_animate_force_exit_stimulus(const strip_mask_t mask);
void led_animate_clear_exit_stimulus(const strip_mask_t mask);
bool led_animate_exit_stimulus_flag(const strip_mask_t mask);
bool led_animate_check_for_animation_exit_stimulus(const strip_mask_t mask, led_color_t *p_led_color,
												   const led_color_e* p_color);
void led_animate_srw_debug(void);

void led_animate_fixed_assorted_color(const strip_mask_t mask);
void led_animate_random_assorted_color(const strip_mask_t mask);

void led_animate_heart_beat(const strip_mask_t mask, const led_color_e* p_color,
							uint16_t* p_delay_ms);
void led_animate_starburst_zabinski(const strip_mask_t mask, const led_color_e* p_color,
							uint16_t* p_delay_ms, led_animate_starburst_mode_e mode,
							bool b_two_random_color);
void led_animate_starburst(const strip_mask_t mask, const led_color_e* p_color,
							uint16_t* p_delay_ms, led_animate_starburst_mode_e mode,
							bool b_two_random_color);
void led_animate_static_harley_color(const strip_mask_t mask, const led_color_e* p_color);
void led_animate_solid_custom_color(const strip_mask_t mask, const led_color_hex_code_e color);
void led_animate_only_spell_word(const strip_mask_t mask, const led_color_e* p_color,
                                 uint16_t* p_delay_ms);
void led_animate_fade_in_fade_out(const strip_mask_t mask, const led_color_e* p_color,
								  uint16_t* p_delay_ms);
void led_animate_strobe(const strip_mask_t mask, const led_color_e* p_color,
                        const uint16_t led_animate_strobe_count, const uint16_t flash_delay, const uint16_t end_pause);
void led_animate_twinkle(const strip_mask_t mask, const led_color_e* p_color, const uint16_t count,
                         uint16_t* p_delay_ms, const bool only_one);
void led_animate_twinkle_random(const strip_mask_t mask, const uint16_t count,
                                const uint16_t* p_delay_ms, const bool only_one);
void led_animate_sparkle_only_random_color(const strip_mask_t mask, const bool fill,
                                           const uint16_t* p_delay_ms);
void led_animate_sparkle_random_color(const strip_mask_t mask, const bool fill,
                                      const uint16_t* p_delay_ms);
void led_animate_sparkle(const strip_mask_t mask, const led_color_e* p_color,
                         const uint16_t* p_delay_ms);
void led_animate_running_lights(const strip_mask_t mask, const led_color_e* p_color,
								const uint16_t* p_delay_ms);
void led_animate_rainbow_cycle(const strip_mask_t mask, uint16_t* p_delay_ms);
void led_animate_theater_chase(const strip_mask_t mask, const led_color_e* p_color,
                               uint16_t* p_delay_ms);
void led_animate_theater_chase_rainbow(const strip_mask_t mask, uint16_t* p_delay_ms);
void led_animate_determine_number_pixels_in_strip(const strip_mask_t mask);


bool led_animate_need_to_adjust_speed(void);
void led_animate_set_adjust_speed(bool);
void led_animate_clear_adjust_speed(void);


void led_animate_determine_number_pixels_in_strip(const strip_mask_t mask);

void led_animate_static_snowmobile_color(const strip_mask_t mask);

void led_animate_clear_state_change(const strip_mask_t mask);
void led_animate_force_state_change(const strip_mask_t mask);
bool led_animate_read_state_change(const strip_mask_t mask);

#endif
