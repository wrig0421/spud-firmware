// SRW
#include <stdbool.h>
#include "numbers.h"
#include "led_ctrl.h"
#include "led_color.h"
#include "led_ctrl_color.h"
#include "rng_access.h"


/**
 * @brief   Return the master color state for the strip[s] in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  The master color state for the enabled strips
 */
led_color_master_state_e led_ctrl_color_master_state(const strip_mask_t mask)
{
    return led_ctrl_read_active_color_master_state(mask);
}


/**
 * @brief   Force the master color state to demo for the strip[s] in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 */
void led_ctrl_color_master_state_force_demo(const strip_mask_t mask)
{
    led_ctrl_write_active_color_master_state(mask, LED_COLOR_MASTER_STATE_DEMO);
}


/**
 * @brief   Force the master color state to fixed for the strip[s] in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 */
void led_ctrl_color_master_state_force_fixed(const strip_mask_t mask)
{
    led_ctrl_write_active_color_master_state(mask, LED_COLOR_MASTER_STATE_FIXED);
    led_ctrl_write_active_color(mask, LED_COLOR_FIRST);
}


/**
 * @brief   Reset the color to LED_COLOR_FIRST for strips[s] in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 * @note    Future should consider setting to a random color.
 */
void led_ctrl_color_reset(const strip_mask_t mask)
{
	led_ctrl_write_active_color(mask, LED_COLOR_FIRST);
}


/**
 * @brief   Adjust the color for strip[s] enabled in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  true if color all colors have been shown in a cycle.
 */
bool led_ctrl_color_adjust(const strip_mask_t mask)
{
    bool return_val = false;
//	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    if (LED_COLOR_LAST == led_ctrl_read_active_color(mask))
    {
    	led_ctrl_write_active_color(mask, LED_COLOR_FIRST);
        return_val = true;
    }
    else
	{
    	led_ctrl_write_active_color(mask, led_ctrl_read_active_color(mask) + 1);
	}
    return return_val;
}


/**
 * @brief   Return the enabled color for enabled strip[s] in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  Enumerated type for the enabled color for enabled strip[s] in mask.
 */
led_color_e led_ctrl_color_read_active_color(const strip_mask_t mask)
{
    return led_ctrl_read_active_color(mask);
}


void led_ctrl_color_write_active_color(const strip_mask_t mask, led_color_e led_color)
{
    led_ctrl_write_active_color(mask, led_color);
}


bool led_ctrl_color_active_color_is_black(const strip_mask_t mask)
{
    return (led_ctrl_color_read_active_color(mask) == \
                    LED_COLOR_BLACK) ? true : false;
}


/**
 * @brief   Return the enabled color for enabled strip[s] in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  Hex value for the enabled color for enabled strip[s] in mask.
 */
led_color_hex_code_e led_ctrl_color_read_active_color_hex(const strip_mask_t mask)
{
	return led_ctrl_read_active_color_hex(mask);
}


/**
 * @brief   Return the hex value for the red part of enabled color for
 *          enabled strip[s] in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  Hex value for the enabled red color for enabled strip[s] in mask.
 */
uint8_t led_ctrl_color_read_active_red_hex(const strip_mask_t mask)
{
    return led_ctrl_read_active_color_rgb_red_hex(mask);
}


/**
 * @brief   Return the hex value for the green part of enabled color for
 *          enabled strip[s] in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  Hex value for the enabled green color for enabled strip[s] in mask.
 */
uint8_t led_ctrl_color_read_active_green_hex(const strip_mask_t mask)
{
    return led_ctrl_read_active_color_rgb_green_hex(mask);
}


/**
 * @brief   Return the hex value for the blue part of enabled color for
 *          enabled strip[s] in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  Hex value for the enabled blue color for enabled strip[s] in mask.
 */
uint8_t led_ctrl_color_read_active_blue_hex(const strip_mask_t mask)
{
    return led_ctrl_read_active_color_rgb_blue_hex(mask);
}


/**
 * @brief   Return the hex value for the passed color.
 * @param   color - enumerated value for the color.
 * @return  Hex value for the enabled blue color for enabled strip[s] in mask.
 * @note    Color must be defined!  LUT used!
 */
led_color_hex_code_e led_ctrl_color_enum_to_hex(const led_color_e color)
{
    return led_color_enum_to_hex_code(color);
}


led_color_e led_ctrl_color_hex_to_enum(const led_color_hex_code_e color)
{
    return led_color_hex_to_enum(color);
}


led_color_e led_ctrl_color_randomize_active_color(const strip_mask_t mask)
{
//    strip_num_e strip_num = ws2812_strip_mask_to_strip_num(mask);
    led_color_e led_color = LED_COLOR_BLACK;
    do
    {
        led_color = (led_color_e)(rng_access_read_and_generate_random_number() % NUM_COLORS);
    } while (led_ctrl_read_active_color(mask) == led_color);

    led_ctrl_write_active_color(mask, led_color);
    return led_color; // not always used but nice to return if needed.
}


led_color_hex_code_e led_ctrl_color_major_state_change_color(button_e btn)
{
    switch (btn)
    {
        case BUTTON_A: return LED_COLOR_MAJOR_STATE_CHANGE_SPEED;
        case BUTTON_B: return LED_COLOR_MAJOR_STATE_CHANGE_STATE;
        case BUTTON_C: return LED_COLOR_MAJOR_STATE_CHANGE_COLOR;
        case BUTTON_D: return LED_COLOR_MAJOR_STATE_CHANGE_BRIGHTNESS;
        default: while (1);
    }
}


