// SRW

#include "led_ctrl_power.h"
#include "led_ctrl.h"
#include "led_ctrl_brightness.h"

extern led_ctrl_t g_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];

/**
 * @brief   Adjust brightness one position.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 * @note    This function is meant to be called only after the user initiates
 *          brightness change with remote control!
 */
void led_ctrl_brightness_adjust(const strip_mask_t mask)
{
//	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	// LED brightness update linearly.  No random select.  User will press button
	// to advance the brightness.
    if (LED_BRIGHTNESS_FIRST == led_ctrl_read_strip_brightness(mask))
	{
        led_ctrl_write_strip_brightness(mask, LED_BRIGHTNESS_LAST);
	}
    else
	{
        led_ctrl_write_strip_brightness(mask, (led_brightness_e)(led_ctrl_read_strip_brightness(mask) - 1));
	}
    // led brightness variable has been updated!
    switch (led_ctrl_read_strip_brightness(mask))
    {
        // settings below are capped at the calculated absolute max!
        case LED_BRIGHTNESS_100_PERCENT:    led_ctrl_power_monitor_set(1.0f);   break;
        case LED_BRIGHTNESS_50_PERCENT:     led_ctrl_power_monitor_set(0.5f);   break;
        case LED_BRIGHTNESS_25_PERCENT:     led_ctrl_power_monitor_set(0.25f);  break;
        case LED_BRIGHTNESS_10_PERCENT:     led_ctrl_power_monitor_set(0.10f);  break;
        default:                                                                break;
    }
}
