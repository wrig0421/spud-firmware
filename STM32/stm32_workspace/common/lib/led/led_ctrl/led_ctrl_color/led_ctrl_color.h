// SRW
#if !defined(LED_CTRL_COLOR_H)
#define LED_CTRL_COLOR_H

#include "led_color.h"

typedef struct
{
	led_color_master_state_e	led_color_master;
	led_color_t                 led_color;
} led_ctrl_color_info_t;

led_color_master_state_e led_ctrl_color_master_state(const strip_mask_t mask);
void led_ctrl_color_master_state_force_demo(const strip_mask_t mask);
void led_ctrl_color_master_state_force_fixed(const strip_mask_t mask);
void led_ctrl_color_reset(const strip_mask_t mask);
bool led_ctrl_color_adjust(const strip_mask_t mask);
led_color_e led_ctrl_color_read_active_color(const strip_mask_t mask);
void led_ctrl_color_write_active_color(const strip_mask_t mask, led_color_e led_color);
bool led_ctrl_color_active_color_is_black(const strip_mask_t mask);
led_color_hex_code_e led_ctrl_color_read_active_color_hex(const strip_mask_t mask);
uint8_t led_ctrl_color_read_active_red_hex(const strip_mask_t mask);
uint8_t led_ctrl_color_read_active_green_hex(const strip_mask_t mask);
uint8_t led_ctrl_color_read_active_blue_hex(const strip_mask_t mask);
led_color_hex_code_e led_ctrl_color_enum_to_hex(const led_color_e color);
led_color_e led_ctrl_color_randomize_active_color(const strip_mask_t mask);
led_color_hex_code_e led_ctrl_color_major_state_change_color(button_e btn);
led_color_e led_ctrl_color_random(const strip_mask_t mask);



#endif



