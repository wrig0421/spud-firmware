// SRW
#if !defined(LED_CTRL_PAUSE_H)
#define LED_CTRL_PAUSE_H

#include "ws2812b.h"

typedef enum
{
    LED_CTRL_PAUSE_STATE_NOT_ACTIVE = 0,
    LED_CTRL_PAUSE_STATE_ACTIVE
} led_ctrl_pause_state_e;

void led_ctrl_pause(const strip_mask_t mask);
void led_ctrl_pause_enable(const strip_mask_t mask);
void led_ctrl_pause_disable(const strip_mask_t mask);
bool led_ctrl_pause_is_enabled(const strip_mask_t mask);

#endif // LED_CTRL_PAUSE_H
