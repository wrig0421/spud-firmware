// SRW

#include "numbers.h"
#include "ws2812b.h"
#include "led_ctrl.h"
#include "rng_access.h"
#include "led_ctrl_state.h"

extern led_ctrl_t g_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];


/**
 * @brief   Reset animation count for enabled strips in passed mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 */
void led_state_ctrl_iteration_reset(const strip_mask_t mask)
{
	led_ctrl_write_state_current_iteration(mask, 0);
}


/**
 * @brief   Set "sub state" to a "random" selection
 * @param   cur_state - current sub state enabled.
 * @return  "random sub state" for enabled strips in mask.
 * @note    THIS DOES NOT SET THE STATE FOR ANY STRIPS.
 */
led_state_e led_state_ctrl_random_state(const led_state_e cur_state)
{
    led_state_e state = (led_state_e)(random_num(LED_STATE_FIRST, NUM_LED_STATES));
    if (cur_state == state)
    {
        if (LED_STATE_LAST == cur_state) state = (led_state_e)(state - 1);
        else state = (led_state_e)(state + 1);
    }
    return state;
}


led_state_e led_ctrl_state_randomize_active_state(const strip_mask_t mask)
{
    led_state_e led_state = led_ctrl_read_active_state(mask);
    do
    {
        led_state = (led_state_e)(rng_access_read_and_generate_random_number() % NUM_LED_STATES);
    } while (led_ctrl_read_active_state(mask) == led_state);

    led_ctrl_write_active_state(mask, led_state);
    return led_state; // not always used but nice to return if needed.
}


/**
 * @brief   Return the current "sub state" for enabled strips in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  current "sub state" for enabled strips in mask.
 */
led_state_e led_state_ctrl_state(const strip_mask_t mask)
{
    return led_ctrl_read_active_state(mask);
}


/**
 * @brief   Adjust the current "sub state" for enabled strips in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  true if iterated through all possible states and resetting back to
 *          the first.
 */
bool led_state_ctrl_adjust_state(const strip_mask_t mask)
{
//	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    bool return_val = false;

    if (LED_STATE_LAST == led_ctrl_read_active_state(mask))
    {
        led_ctrl_write_active_state(mask, LED_STATE_FIRST);
        return_val = true;
    }
    else
	{
        led_ctrl_write_active_state(mask, (led_ctrl_read_active_state(mask) + 1));
	}
    return return_val;
}


/**
 * @brief   Force fixed master state for the enabled strips in passed mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 */
void led_state_ctrl_force_fixed_state(const strip_mask_t mask)
{
    led_ctrl_write_master_state(mask, LED_CTRL_STATE_MASTER_FIXED);
}


/**
 * @brief   Force master demo state for the enabled strips in passed mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  void
 * @note    First state is always reset as the default... May want to make this
 *          random??
 */
void led_state_ctrl_force_demo(const strip_mask_t mask)
{
    led_ctrl_write_master_state(mask, LED_CTRL_STATE_MASTER_DEMO);
    led_ctrl_write_active_state(mask, LED_STATE_FIRST);
    led_ctrl_write_state_current_iteration(mask, 0);
}


/**
 * @brief   Return the "master" state.  Demo or Fixed.
 * @param   mask - enabled strips to check if button press effects.
 * @return  master_state -  enumerated type with DEMO or FIXED option.
 */
led_ctrl_state_master_e led_state_ctrl_master_state(const strip_mask_t mask)
{
    return led_ctrl_read_master_state(mask);
}


/**
 * @brief   Force display animation passed for strips enabled in mask.
 * @param   mask - enabled strips to check if button press effects.
 * @return  led_state -  state to force show.
 * @note    Reset the current ieration count as well...
 */
void led_state_ctrl_force_state(const strip_mask_t mask, led_state_e led_state)
{
    led_ctrl_write_active_state(mask, led_state);
    led_ctrl_write_state_current_iteration(mask, 0);
}


led_ctrl_state_info_t* led_ctrl_state_read_info(const strip_mask_t mask)
{
    return led_ctrl_read_state_info(mask);
}


