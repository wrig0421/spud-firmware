#if !defined(LED_ANIMATE_DEBUG_H)
#define LED_ANIMATE_DEBUG_H

#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "board_init_common.h"
#include "ws2812b.h"
#include "led_ctrl_color.h"

void led_animate_static_snowmobile_color(const strip_mask_t mask,
                                         const led_color_e* p_color);


#endif
