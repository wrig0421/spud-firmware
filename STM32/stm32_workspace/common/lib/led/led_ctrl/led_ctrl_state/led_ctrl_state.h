// SRW
#if !defined(LED_CTRL_STATE_H)
#define LED_CTRL_STATE_H

#include "config.h"
#include <stdint.h>
#include "ws2812b.h"
#include "led_state.h"
#include "led_ctrl_speed.h"

typedef enum
{
    LED_CTRL_STATE_MASTER_DEMO,
    LED_CTRL_STATE_MASTER_FIXED
} led_ctrl_state_master_e;


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
} led_animate_state_t;


typedef struct
{
    uint16_t                    animation_delay_per_inner_loop_ms;
    uint16_t                    animation_delay_per_outer_loop_ms;
} led_ctrl_state_parameters_t;


typedef struct
{
	led_ctrl_state_master_e		            led_state_master;
	led_state_e			                    led_state;
	uint16_t					            led_state_current_iteration;
	const led_ctrl_state_parameters_t*      led_ctrl_state_param;
} led_ctrl_state_info_t;


void led_state_ctrl_iteration_reset(const strip_mask_t mask);
led_state_e led_state_ctrl_random_state(const led_state_e cur_state);
led_state_e led_state_ctrl_state(const strip_mask_t mask);
bool led_state_ctrl_adjust_state(const strip_mask_t mask);
void led_state_ctrl_force_fixed_state(const strip_mask_t mask);
void led_state_ctrl_force_demo(const strip_mask_t mask);
led_ctrl_state_master_e led_state_ctrl_master_state(const strip_mask_t mask);
void led_state_ctrl_force_state(const strip_mask_t mask, led_state_e led_state);
void led_state_ctrl_color_decrement_inner_color(void);
void led_state_ctrl_color_decrement_outer_color(void);
void led_state_ctrl_color_increment_inner_color(void);
void led_state_ctrl_color_increment_outer_color(void);



void led_state_ctrl_color_decrement_inner_color(void);
void led_state_ctrl_color_decrement_outer_color(void);
void led_state_ctrl_color_increment_inner_color(void);
void led_state_ctrl_color_increment_outer_color(void);


#endif
