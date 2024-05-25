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

void led_animate_set_pixel(const strip_mask_t mask, const uint16_t pixel, led_color_t* led_color);
void led_animate_show_strip(const strip_mask_t strip_mask);
void led_animate_set_all_pixels(const strip_mask_t mask, led_color_t* led_color);
void led_animate_set_pixels_in_range(const strip_mask_t mask, uint16_t start, uint16_t stop, const led_color_hex_code_e color);
void led_animate_multiple_solid_custom_colors(const strip_mask_t mask_solid, const uint32_t* color_array);
void led_animate_solid_custom_color(const strip_mask_t mask_solid, const led_color_hex_code_e color_spell);
void led_animate_turn_all_pixels_off(void);
void led_animate_turn_all_pixels_off_in_strip(const strip_mask_t mask);
void led_animate_spell_and_sparkle(const strip_mask_t mask_spell, const strip_mask_t mask_sparkle,
                                   const led_color_hex_code_e color_spell, const bool fill, const uint16_t speed_delay);
void led_animate_spell_and_solid_color(const strip_mask_t mask_spell, const strip_mask_t mask_solid,
                                       const led_color_hex_code_e color_spell, const led_color_hex_code_e color_solid,
                                       const uint16_t speed_delay);
void led_animate_spell_word_multiple_colors(const strip_mask_t mask_spell, const led_color_hex_code_e* color_array,
                                            const uint16_t speed_delay);
void led_animate_only_spell_word(const strip_mask_t mask_spell, const led_color_hex_code_e color_spell,
                                 const uint16_t time_ms);
void led_animate_fade_in_fade_out_multiple_colors(const strip_mask_t strip_mask, const uint32_t* color_array);
void led_animate_fade_in_fade_out(const strip_mask_t mask_fade, const led_color_hex_code_e color_fade);
void led_animate_strobe(const strip_mask_t mask_strobe, const led_color_hex_code_e color_strobe,
                        const uint16_t led_animate_strobe_count, const uint16_t flash_delay, const uint16_t end_pause);
void led_animate_twinkle_multiple_colors(const strip_mask_t mask_twinkle, const uint32_t* color_array,
                                         const uint16_t count, const uint16_t speed_delay, const bool only_one);
void led_animate_twinkle(const strip_mask_t twinkle_mask, const led_color_hex_code_e color_twinkle, const uint16_t count,
                         const uint16_t speed_delay, const bool only_one);
void led_animate_twinkle_random(const strip_mask_t mask_twinkle_random, const uint16_t count,
                                const uint16_t speed_delay, const bool only_one);
void led_animate_sparkle_only_random_color(const strip_mask_t mask_sparkle_random, const bool fill,
                                           const uint16_t speed_delay);
void led_animate_sparkle_random_color(const strip_mask_t mask_sparkle_random, const bool fill,
                                      const uint16_t speed_delay);
void led_animate_sparkle(const strip_mask_t mask_sparkle, const led_color_hex_code_e color_sparkle,
                         const uint16_t speed_delay);
void led_animate_running_lights(const strip_mask_t mask_running_lights, const led_color_hex_code_e color_running_lights);
void led_animate_rainbow_cycle(const strip_mask_t mask_rainbow_cycle, const uint16_t speed_delay);
void led_animate_theater_chase_multiple_colors(const strip_mask_t mask_theater_chase, const uint32_t* color_array,
                                               const uint16_t speed_delay);
void led_animate_theater_chase(const strip_mask_t mask_theater_chase, const led_color_hex_code_e color_theater_chase,
                               const uint16_t speed_delay);
void led_animate_theater_chase_rainbow(const strip_mask_t mask_theater_chase, const uint16_t speed_delay);
void led_animate_determine_number_pixels_in_strip(const strip_mask_t mask);
void led_animate_set_all_pixels_hex_color(const strip_mask_t mask, const led_color_hex_code_e color);

#endif
