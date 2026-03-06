// SRW
#if !defined(LED_CTRL_TIMdE_H)
#define LED_CTRL_TIMdE_H

#include <stdbool.h>
#include <stdint.h>
//#include "config.h"
//#include "ws2812b.h"
#include "led_state.h"
#include "led_ctrl_speed.h"

// WHY CANT THIS BE IN led_ctrl_time.h????
typedef struct
{
    uint16_t inner_animation_loop_delay_ms;
    uint16_t outer_animation_loop_delay_ms;
} led_ctrl_time_delay_t;

bool led_ctrl_time_delay(const strip_mask_t mask, const uint32_t time_ms);

#endif
