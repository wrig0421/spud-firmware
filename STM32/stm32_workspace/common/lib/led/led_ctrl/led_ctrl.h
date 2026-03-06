// SRW

#if !defined(LED_CTRL_H)
#define LED_CTRL_H

#include "FreeRTOS.h"
#include "timers.h"

#include "led_color.h"
#include "led_ctrl_brightness.h"
#include "led_ctrl_color.h"
#include "led_ctrl_interrupt.h"
#include "led_ctrl_pause.h"
#include "led_ctrl_power.h"
#include "led_ctrl_speed.h"
#include "led_ctrl_state.h"
#include "led_ctrl_time.h"


typedef enum
{
	LED_CTRL_INTERRUPT_BIT_STATE 				= (1 << 0),
	LED_CTRL_INTERRUPT_BIT_COLOR 				= (1 << 1),
	LED_CTRL_INTERRUPT_BIT_SPEED 				= (1 << 2),
	LED_CTRL_INTERRUPT_BIT_PAUSE_BRIGHTNESS 	= (1 << 3)
	// future go here.
} led_ctrl_interrupt_bit_e;



#pragma pack(1)
typedef struct
{
    led_brightness_e            led_ctrl_brightness;
    led_ctrl_color_info_t       led_ctrl_color_info;
	led_ctrl_interrupt_info_t	led_ctrl_interrupt_info;
    led_ctrl_pause_state_e      led_ctrl_pause_state;
    led_ctrl_power_factor_t     led_ctrl_power_factor;
    led_speed_e                 led_ctrl_speed;
	led_ctrl_state_info_t		led_ctrl_state_info;
} led_ctrl_t;
#pragma pack()

uint16_t led_ctrl_inner_delay_ms(led_state_e state, led_speed_e speed);
uint16_t led_ctrl_outer_delay_ms(led_state_e state, led_speed_e speed);
uint16_t* led_ctrl_inner_delay_ms_ref(led_state_e state, led_speed_e speed);
uint16_t* led_ctrl_outer_delay_ms_ref(led_state_e state, led_speed_e speed);
led_ctrl_state_master_e led_ctrl_read_master_state(const strip_mask_t mask);
void led_ctrl_write_master_state(const strip_mask_t mask,
                                 led_ctrl_state_master_e master_state);
led_state_e led_ctrl_read_active_state(const strip_mask_t mask);
void led_ctrl_write_active_state(const strip_mask_t mask,
                                 led_state_e state);
uint16_t led_ctrl_read_state_current_iteration(const strip_mask_t mask);
void led_ctrl_write_state_current_iteration(const strip_mask_t mask,
                                            uint16_t value);
led_speed_e led_ctrl_read_speed(const strip_mask_t mask);
void led_ctrl_write_speed(const strip_mask_t mask, led_speed_e led_speed);
led_ctrl_pause_state_e led_ctrl_read_pause_state(const strip_mask_t mask);
void led_ctrl_write_pause_state(const strip_mask_t mask, bool pause_enable);
led_ctrl_interrupt_info_t* led_ctrl_read_interrupt_info(const strip_mask_t mask);
led_ctrl_interrupt_status_t led_ctrl_read_minor_interrupt_status(const strip_mask_t mask);
bool led_ctrl_read_minor_interrupt_flag(const strip_mask_t mask);
bool* led_ctrl_read_minor_interrupt_flag_ref(const strip_mask_t mask);
led_ctrl_interrupt_status_t led_ctrl_read_major_interrupt_status(const strip_mask_t mask);
bool led_ctrl_read_major_interrupt_flag(const strip_mask_t mask);
bool* led_ctrl_read_major_interrupt_flag_ref(const strip_mask_t mask);
led_ctrl_color_info_t  led_ctrl_read_active_color_info(const strip_mask_t mask);
led_ctrl_color_info_t* led_ctrl_read_active_color_info_ref(const strip_mask_t mask);
led_color_master_state_e led_ctrl_read_active_color_master_state(const strip_mask_t mask);
void led_ctrl_write_active_color_master_state(const strip_mask_t mask,
                                       led_color_master_state_e master_state);
led_color_e led_ctrl_read_active_color(const strip_mask_t mask);
void led_ctrl_write_active_color(const strip_mask_t mask, led_color_e led_color);
led_color_hex_code_e led_ctrl_read_active_color_hex(const strip_mask_t mask);
void led_ctrl_write_active_color_hex(const strip_mask_t mask,
                                   led_color_hex_code_e led_color_hex_code);
uint8_t led_ctrl_read_active_color_rgb_red_hex(const strip_mask_t mask);
uint8_t led_ctrl_read_active_color_rgb_green_hex(const strip_mask_t mask);
uint8_t led_ctrl_read_active_color_rgb_blue_hex(const strip_mask_t mask);
led_brightness_e led_ctrl_read_strip_brightness(const strip_mask_t mask);
void led_ctrl_write_strip_brightness(const strip_mask_t mask,
                                     led_brightness_e led_brightness);
led_ctrl_state_info_t* led_ctrl_read_state_info(const strip_mask_t);
led_ctrl_time_delay_t* led_ctrl_read_time_delay_ref(const strip_mask_t mask);
const uint16_t led_ctrl_read_time_delay_inner_loop(const strip_mask_t mask, led_state_e state, led_speed_e speed);
const uint16_t* led_ctrl_read_time_delay_inner_loop_ref(const strip_mask_t mask, led_state_e state, led_speed_e speed);
const uint16_t led_ctrl_read_time_delay_outer_loop(const strip_mask_t mask, led_state_e state, led_speed_e speed);
const uint16_t* led_ctrl_read_time_delay_outer_loop_ref(const strip_mask_t mask, led_state_e state, led_speed_e speed);


#endif
