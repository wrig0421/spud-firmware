// SRW
#if !defined(LED_CTRL_COLOR_H)
#define LED_CTRL_COLOR_H

#include "led_color.h"

typedef struct
{
	led_color_master_state_e	led_color_master;
	led_color_e					led_color;
} led_ctrl_color_info_t;

led_color_master_state_e led_ctrl_color_master_state(const strip_mask_t mask);
void led_ctrl_color_master_state_force_demo(const strip_mask_t mask);
void led_ctrl_color_master_state_force_fixed(const strip_mask_t mask);
void led_ctrl_color_reset(const strip_mask_t mask);
bool led_ctrl_color_adjust(const strip_mask_t mask);
led_color_e led_ctrl_color(const strip_mask_t mask);
led_color_hex_code_e led_ctrl_color_hex(const strip_mask_t mask);
uint8_t led_ctrl_color_red_hex(const strip_mask_t mask);
uint8_t led_ctrl_color_green_hex(const strip_mask_t mask);
uint8_t led_ctrl_color_blue_hex(const strip_mask_t mask);
led_color_hex_code_e led_ctrl_color_to_hex(const led_color_e color);
led_color_e led_ctrl_color_random(const strip_mask_t mask);
led_color_e led_ctrl_color_random_input(led_color_e* p_color);

#endif



