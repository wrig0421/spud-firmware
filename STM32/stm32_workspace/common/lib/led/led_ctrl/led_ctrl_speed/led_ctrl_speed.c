// SRW
#include <stdint.h>
#include "ws2812b.h"
#include "led_ctrl.h"
#include "led_ctrl_speed.h"

/**
 * @brief   Return speed "factor" for enabled strips in passed mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  speed factor [float].
 * @note    100% speed is represented by 1.0f.
 */
float led_ctrl_speed(const strip_mask_t mask)
{
    float speed_factor = 0.0;
    switch (led_ctrl_read_speed(mask))
    {
        case LED_SPEED_1000P:   speed_factor = 10.0f;   break;
        case LED_SPEED_500P:    speed_factor = 5.0f;    break;
        case LED_SPEED_100P:    speed_factor = 1.0f;    break;
        case LED_SPEED_50P:     speed_factor = 0.5f;    break;
        case LED_SPEED_25P:     speed_factor = 0.25f;   break;
        default:                                        break;
    }
    return speed_factor;
}


/**
 * @brief   Adjust the speed by one increment for enabled stirps in passed mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 */
void led_ctrl_speed_adjust(const strip_mask_t mask)
{

    if (LED_SPEED_FIRST == led_ctrl_read_speed(mask))
	{
        led_ctrl_write_speed(mask, LED_SPEED_LAST);
	}
    else
	{
        led_ctrl_write_speed(mask, (led_ctrl_read_speed(mask) - 1));
	}
}

/**
 * @brief   Reset the animation speed for enabled strips in passed mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 * @note    Speed is reset to 100% by default.
 */
void led_ctrl_speed_reset(const strip_mask_t mask)
{
    led_ctrl_write_speed(LED_SPEED_100P);
}


void led_ctrl_speed_read_speed(const strip_mask_t mask)
{
    return led_ctrl_read_speed(mask);
}


void led_ctrl_speed_write_speed(const strip_mask_t mask, led_speed_e led_speed)
{
    led_ctrl_write_speed(mask, led_speed);
}
