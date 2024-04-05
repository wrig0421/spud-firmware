// SRW
#if !defined(LED_CTRL_H)
#define LED_CTRL_H

#include "led_ctrl_state.h"
#include "led_ctrl_color.h"
#include "led_ctrl_speed.h"
#include "led_ctrl_brightness.h"


typedef struct
{
	uint8_t state 	: 1;
	uint8_t color 	: 1;
	uint8_t	speed 	: 1;
	uint8_t pause 	: 1;
	uint8_t rsvd  	: 4;
} led_ctrl_interrupt_info_t;


typedef struct
{
	led_ctrl_state_info_t		led_state_info;
	led_ctrl_color_info_t		led_color_info;
	led_ctrl_interrupt_info_t	led_interrupt_info;
	led_speed_e					led_speed;
	led_brightness_e			led_brightness;
} led_ctrl_t;


bool led_ctrl_delay(const uint32_t time_ms);

#endif
