// SRW
#if !defined(LED_CTRL_TIME_H)
#define LED_CTRL_TIME_H

#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "ws2812b.h"

typedef struct
{
	uint16_t inner_animation_loop_delay_ms[NUM_LED_STATES][NUM_LED_SPEEDS];
	uint16_t outer_animation_loop_delay_ms[NUM_LED_STATES][NUM_LED_SPEEDS];
}led_ctrl_time_delay_t;


bool led_ctrl_time_delay(const strip_mask_t mask, const uint32_t time_ms);

#endif
