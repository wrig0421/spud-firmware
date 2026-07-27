// SRW

#include "ws2812b.h"
#include "led_ctrl.h"
#include "led_ctrl_pause.h"

extern led_ctrl_t g_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];

/**
 * @brief   Pause the enabled strips within the passed mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 */
void led_ctrl_pause(const strip_mask_t mask)
{
    static uint8_t pause_enable_disable = 1;

    if (pause_enable_disable) led_ctrl_write_pause_state(mask, true);
    else led_ctrl_write_pause_state(mask, false);
    pause_enable_disable ^= 1;
}


void led_ctrl_pause_enable(const strip_mask_t mask)
{
    led_ctrl_write_pause_state(mask, true);
}


void led_ctrl_pause_disable(const strip_mask_t mask)
{
    led_ctrl_write_pause_state(mask, false);
}


bool led_ctrl_pause_is_enabled(const strip_mask_t mask)
{
    return ((led_ctrl_read_pause_state(mask) == LED_CTRL_PAUSE_STATE_ACTIVE) \
                    ? true : false);
}
