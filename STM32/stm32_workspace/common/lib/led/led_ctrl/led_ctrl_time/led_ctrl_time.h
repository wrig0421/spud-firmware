// SRW
#if !defined(LED_CTRL_TIME_H)
#define LED_CTRL_TIME_H

#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "ws2812b.h"

bool led_ctrl_time_delay(const strip_mask_t mask, const uint32_t time_ms);

#endif
