// SRW
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "config.h"
#include "led_ctrl_power.h"
#include "numbers.h"
#include "ws2812b.h"
#include "semaphore_access.h"
#include <string.h>
#include "free_rtos_convenience.h"
#include "timer_access_hal.h"
#include "task_notify.h"

extern TIM_HandleTypeDef 	g_tim1_handle_config;

// below hard coded 2880 because WS2812B_RESET_TIME_CYCLES
uint8_t g_pwm_data_strip_1[sizeof(ws2812b_led_t) * BITS_PER_BYTE * STRIP_1_LENGTH + WS2812B_RESET_TIME_CYCLES + 2*sizeof(uint32_t)];
uint8_t g_pwm_data_strip_2[sizeof(ws2812b_led_t) * BITS_PER_BYTE * STRIP_2_LENGTH + WS2812B_RESET_TIME_CYCLES + 2*sizeof(uint32_t)];
uint8_t g_pwm_data_strip_3[sizeof(ws2812b_led_t) * BITS_PER_BYTE * STRIP_3_LENGTH + WS2812B_RESET_TIME_CYCLES + 2*sizeof(uint32_t)];

p_pwm_data_t gp_pwm_data_strip_1 = NULL;
p_pwm_data_t gp_pwm_data_strip_2 = NULL;
p_pwm_data_t gp_pwm_data_strip_3 = NULL;

ws2812b_led_t g_led_strip_1[STRIP_1_LENGTH];
ws2812b_led_t g_led_strip_2[STRIP_2_LENGTH];
ws2812b_led_t g_led_strip_3[STRIP_3_LENGTH];


ws2812b_info_t g_ws2812b_info[MAX_NUM_STRIPS] =
{
	[STRIP_NUM_1] =
	{
		.led_strip_length 	= STRIP_1_LENGTH,
		.p_led_strip 		= g_led_strip_1,
		.p_pwm_data 		= NULL // filled in ws2812b_init function
	},
	[STRIP_NUM_2] =
	{
		.led_strip_length 	= STRIP_2_LENGTH,
		.p_led_strip 		= g_led_strip_2,
		.p_pwm_data 		= NULL // filled in ws2812b_init function
	},
	[STRIP_NUM_3] =
	{
		.led_strip_length 	= STRIP_3_LENGTH,
		.p_led_strip 		= g_led_strip_3,
		.p_pwm_data 		= NULL // filled in ws2812b_init function
	}
};


uint32_t g_pwm_reset[3000];


/**
 * @brief   Check if pixel number is in the strip range
 * @param   strip_bit: strip to check if pixel is in range
 * @param   pixel: LED # to check
 * @return  true if in range, else false
 */
bool ws2812_pixel_is_in_strip_range(const strip_bit_e strip_bit, const uint16_t pixel)
{
    // must be done at individual strip level.  Can't support 2 strips as only have 1 return value... Unless filling in passed by ref value.
    bool return_val = false;
    if ((STRIP_BIT_1 == strip_bit) && (pixel < g_ws2812b_info[STRIP_NUM_1].led_strip_length)) return_val = true;
    else if ((STRIP_BIT_2 == strip_bit) && (pixel < g_ws2812b_info[STRIP_NUM_2].led_strip_length)) return_val = true;
    else if ((STRIP_BIT_3 == strip_bit) && (pixel < g_ws2812b_info[STRIP_NUM_3].led_strip_length)) return_val = true;
    return return_val;
}


/**
 * @brief   Return the size of the current strip
 * @param   void
 * @return  void
 */
uint16_t ws2812_get_strip_size(const strip_bit_e strip_bit)
{
    // must be strip_bit as this function pertains only to one strip
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(strip_bit);
    return g_ws2812b_info[strip_num].led_strip_length;
}


/**
 * @brief   Reset LED strip >= 50 microseconds of 0
 * @param   void
 * @return  void
 */
void reset_ws2812b(void)
{
    HAL_TIM_PWM_Start_DMA(timer_config_get_handle(), TIM_CHANNEL_1,
                          g_pwm_reset, sizeof(g_pwm_reset));
    HAL_TIM_PWM_Start_DMA(timer_config_get_handle(), TIM_CHANNEL_2,
                          g_pwm_reset, sizeof(g_pwm_reset));
    HAL_TIM_PWM_Start_DMA(timer_config_get_handle(), TIM_CHANNEL_3,
                          g_pwm_reset, sizeof(g_pwm_reset));
}


/**
 * @brief   Converts strip_mask_t into strip_num_e
 * @param   strip_mask - uint16_t val with bits representing individual strips
 * @return  strip_num - the strip_num_e value representing strip_mask contents
 */
strip_num_e ws2812_strip_mask_to_strip_num(const strip_mask_t strip_mask)
{
    switch ((strip_bit_e)strip_mask)
    {
        case STRIP_BIT_1:           return STRIP_NUM_1;
        case STRIP_BIT_2:           return STRIP_NUM_2;
        case STRIP_BIT_3:           return STRIP_NUM_3;
#       if defined(ENABLE_LED_STRIP_SYNC)
            case STRIP_BIT_ALL_SET: return STRIP_NUM_ALL_SET;
#       else
            case STRIP_BIT_1_AND_2: return STRIP_NUM_1_AND_2;
            case STRIP_BIT_1_AND_3: return STRIP_NUM_1_AND_3;
            case STRIP_BIT_2_AND_3: return STRIP_NUM_2_AND_3;
#       endif
        default:                return STRIP_NUM_INVALID;
    }
}


/**
 * @brief   Converts strip_bit to strip_num_e
 * @param   strip_bit - strip_bit_e value representing strip[s]
 * @return  strip_num - the strip_num_e value representing strip_bit contents
 */
strip_num_e ws2812_strip_bit_to_strip_num(const strip_bit_e strip_bit)
{
	switch (strip_bit)
	{
		case STRIP_BIT_1: 			return STRIP_NUM_1;
		case STRIP_BIT_2: 			return STRIP_NUM_2;
		case STRIP_BIT_3: 			return STRIP_NUM_3;
#		if defined(ENABLE_LED_STRIP_SYNC)
			case STRIP_BIT_ALL_SET: return STRIP_NUM_ALL_SET;
#		else
			case STRIP_BIT_1_AND_2: return STRIP_NUM_1_AND_2;
			case STRIP_BIT_1_AND_3: return STRIP_NUM_1_AND_3;
			case STRIP_BIT_2_AND_3: return STRIP_NUM_2_AND_3;
#		endif
		default: 				return STRIP_NUM_INVALID;
	}
}


/**
 * @brief   Converts strip_num to strip_bit_e
 * @param   strip_num - the strip_num_e value representing strip[s]
 * @return  strip_bit - strip_bit_e value representing strip[s]
 */
strip_bit_e ws2812_strip_num_to_strip_bit(strip_num_e strip_num)
{
	switch (strip_num)
	{
		case STRIP_NUM_1: 				return STRIP_BIT_1;
		case STRIP_NUM_2:				return STRIP_BIT_2;
		case STRIP_NUM_3:				return STRIP_BIT_3;
#		if defined(ENABLE_LED_STRIP_SYNC)
			case STRIP_NUM_ALL_SET: 	return STRIP_BIT_ALL_SET;
#		else
			case STRIP_NUM_1_AND_2:		return STRIP_BIT_1_AND_2;
			case STRIP_NUM_1_AND_3:		return STRIP_BIT_1_AND_3;
			case STRIP_NUM_2_AND_3:		return STRIP_BIT_2_AND_3;
#		endif
		default:					return STRIP_BIT_INVALID;
	}
}


/**
 * @brief   Converts strip_num to strip_mask
 * @param   strip_num - the strip_num_e value representing strip[s]
 * @return  strip_mask - strip_mask_t value representing strip[s]
 */
strip_mask_t ws2812_strip_num_to_strip_mask(strip_num_e strip_num)
{
    return (strip_mask_t)ws2812_strip_num_to_strip_bit(strip_num);
}


/**
 * @brief   Return number of active strips WITHIN THE SET MASK!
 * @param   strip_mask - strip_mask_t value representing strip[s]
 * @return  uint16_t - number of strips active within mask!
 */
uint16_t ws2812_get_number_of_active_strips_within_mask(const strip_mask_t strip_mask)
{
	uint16_t num_active_strips = 0;
	for (strip_num_e iii = STRIP_NUM_1; iii < NUM_STRIPS; iii = (strip_num_e)(iii + 1))
	{
		if (iii & strip_mask) num_active_strips++;
	}
	return num_active_strips;
}


/**
 * @brief   Get the number of active LEDs WITHIN THE SET MASK!
 * @param   strip_mask - strip_mask_t value representing strip[s]
 * @return  uint16_t - Number of active LEDs WITHIN THE SET MASK!
 * @note    This represents the lengths...NOT the number of LEDs on currently.
 */
uint16_t ws2812_get_num_leds_in_mask(const strip_mask_t strip_mask)
{
	uint16_t strip_size = 0;
	if (STRIP_BIT_1 & strip_mask)
	{
	    strip_size += g_ws2812b_info[STRIP_NUM_1].led_strip_length;
	}
	if (STRIP_BIT_2 & strip_mask)
	{
        strip_size += g_ws2812b_info[STRIP_NUM_2].led_strip_length;
	}
	if (STRIP_BIT_3 & strip_mask)
	{
        strip_size += g_ws2812b_info[STRIP_NUM_3].led_strip_length;
	}
	return strip_size;
}


/**
 * @brief   Get the MAX strip size WITHIN THE SET MASK!
 * @param   strip_mask: active strips to find max of
 * @return  uint16_t - The max strip size WITHIN THE SET MASK.
 */
uint16_t ws2812_led_get_max_strip_size_in_mask(const strip_mask_t strip_mask)
{
	uint16_t max_strip_size = 0;
	if ((STRIP_BIT_1 & strip_mask) &&
	                (max_strip_size < g_ws2812b_info[STRIP_NUM_1].led_strip_length))
	{
	    max_strip_size = g_ws2812b_info[STRIP_NUM_1].led_strip_length;
	}
	if ((STRIP_BIT_2 & strip_mask) && \
	                (max_strip_size < g_ws2812b_info[STRIP_NUM_2].led_strip_length))
	{
        max_strip_size = g_ws2812b_info[STRIP_NUM_2].led_strip_length;
	}
	if ((STRIP_BIT_3 & strip_mask) && \
	                (max_strip_size < g_ws2812b_info[STRIP_NUM_3].led_strip_length))
	{
        max_strip_size = g_ws2812b_info[STRIP_NUM_3].led_strip_length;
	}
	return max_strip_size;
}


/**
 * @brief   Set WS2812B LED WITHIN THE SET MASK.
 * @param   strip_mask - strip_mask_t value representing strip[s]
 * @param   led_num - LED number in strip mask to set
 * @param   red - red value [0, 255]
 * @param   green - green value [0, 255]
 * @param   blue - blue value [0, 255]
 * @note    If led_num is out of range of a given strip then it will not be set.
 */
void ws2812b_set_led(const strip_mask_t strip_mask, const uint16_t led_num,
                     const color_t red, const color_t green, const color_t blue)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num((strip_bit_e)strip_mask);
    float led_ctrl_power_factor = led_ctrl_power_monitor_ratio();
    // allow multiple strip num to enter this function...
    if (strip_num >= STRIP_NUM_MAX_UNIQUE_STRIPS)
    {
        switch (strip_num)
        {
            case STRIP_NUM_1_AND_2:
                if (ws2812_pixel_is_in_strip_range(STRIP_BIT_1, pixel))
                {
                    (g_ws2812b_info[STRIP_NUM_1].p_led_strip + \
                                    led_num)->red = red * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_1].p_led_strip + \
                                    led_num)->green = green * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_1].p_led_strip + \
                                    led_num)->blue = blue * led_ctrl_power_factor;
                }
                if (ws2812_pixel_is_in_strip_range(STRIP_BIT_2, pixel))
                {
                    (g_ws2812b_info[STRIP_NUM_2].p_led_strip + \
                                    led_num)->red = red * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_2].p_led_strip + \
                                    led_num)->green = green * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_2].p_led_strip + \
                                    led_num)->blue = blue * led_ctrl_power_factor;
                }
            break;
            case STRIP_NUM_1_AND_3:
                if (ws2812_pixel_is_in_strip_range(STRIP_BIT_1, pixel))
                {
                    (g_ws2812b_info[STRIP_NUM_1].p_led_strip + \
                                    led_num)->red = red * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_1].p_led_strip + \
                                    led_num)->green = green * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_1].p_led_strip + \
                                    led_num)->blue = blue * led_ctrl_power_factor;
                }
                if (ws2812_pixel_is_in_strip_range(STRIP_BIT_3, pixel))
                {
                    (g_ws2812b_info[STRIP_NUM_3].p_led_strip + \
                                    led_num)->red = red * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_3].p_led_strip + \
                                    led_num)->green = green * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_3].p_led_strip + \
                                    led_num)->blue = blue * led_ctrl_power_factor;
                }
            break;
            case STRIP_NUM_2_AND_3:
                if (ws2812_pixel_is_in_strip_range(STRIP_BIT_2, pixel))
                {
                    (g_ws2812b_info[STRIP_NUM_2].p_led_strip + \
                                    led_num)->red = red * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_2].p_led_strip + \
                                    led_num)->green = green * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_2].p_led_strip + \
                                    led_num)->blue = blue * led_ctrl_power_factor;
                }
                if (ws2812_pixel_is_in_strip_range(STRIP_BIT_3, pixel))
                {
                    (g_ws2812b_info[STRIP_NUM_3].p_led_strip + \
                                    led_num)->red = red * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_3].p_led_strip + \
                                    led_num)->green = green * led_ctrl_power_factor;
                    (g_ws2812b_info[STRIP_NUM_3].p_led_strip + \
                                    led_num)->blue = blue * led_ctrl_power_factor;
                }
            break;
            case STRIP_NUM_ALL_SET:
                for (strip_num_e strip_num = STRIP_NUM_1; strip_num < STRIP_NUM_MAX_UNIQUE_STRIPS; strip_num++)
                {
                    if (ws2812_pixel_is_in_strip_range(ws2812_strip_num_to_strip_bit(strip_num), pixel))
                    {
                        (g_ws2812b_info[strip_num].p_led_strip + \
                                        led_num)->red = red * led_ctrl_power_factor;
                        (g_ws2812b_info[strip_num].p_led_strip + \
                                        led_num)->green = green * led_ctrl_power_factor;
                        (g_ws2812b_info[strip_num].p_led_strip + \
                                        led_num)->blue = blue * led_ctrl_power_factor;
                    }
                }
            break;
            default:
                while (1); // for debug! // BETTER NOT BE INVALID!!
            break;
        }
    }
    else
    {
        strip_bit_e strip_bit = ws2812_strip_num_to_strip_bit(strip_num);
        if (ws2812_pixel_is_in_strip_range(STRIP_BIT_2, pixel))
        {
            (g_ws2812b_info[strip_num].p_led_strip + \
                            led_num)->red = red * led_ctrl_power_factor;
            (g_ws2812b_info[strip_num].p_led_strip + \
                            led_num)->green = green * led_ctrl_power_factor;
            (g_ws2812b_info[strip_num].p_led_strip + \
                            led_num)->blue = blue * led_ctrl_power_factor;
        }

    }
}


/**
 * @brief   Start timer DMA transfer for the passed strip_bit
 * @param   strip_bit - strip_bit_e value representing strip[s]
 * @return  void
 * @note    This is only functional with single threaded approach.  Multiple
 *          strips being controlled at the same time resulted in flickering
 *          within the strips.  For now... This function will only operate
 *          with STRIP_BIT_1, STRIP_BIT_2, STRIP_BIT_3 values.
 */
void ws2812b_dma_transfer(strip_bit_e strip_bit)
{
    bool first_pass = true;
	static bool timer_channel_started[3] = {false, false, false};
	task_notification_value_format_t task_notification_value;
	task_notification_value.value = 0;
    uint32_t timer_channel = 0;
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(strip_bit);
    switch (strip_bit)
    {
    	case STRIP_BIT_1: timer_channel = TIM_CHANNEL_1; break;
    	case STRIP_BIT_2: timer_channel = TIM_CHANNEL_2; break;
    	case STRIP_BIT_3: timer_channel = TIM_CHANNEL_3; break;
    	default: return;
    }
    if (first_pass)
    {
    	first_pass = false;
    	goto transfer_begin;
    }
    else
    {
        do
        {
            // flicker observed with multiple strips going at once.  Code below
            // enforces only one strip at a time. So we are enforcing that all
            // transfers must be complete before starting another!
        	xTaskNotifyWait(0, (uint32_t)task_notification_value.value,
        	                (uint32_t *)&task_notification_value.value,
        	                portMAX_DELAY);
            if (task_notification_value.entity_bits.strip_1)
            {
                timer_channel_started[STRIP_NUM_1] = false;
            }
            if (task_notification_value.entity_bits.strip_2)
            {
                timer_channel_started[STRIP_NUM_2] = false;
            }
            if (task_notification_value.entity_bits.strip_3)
            {
                timer_channel_started[STRIP_NUM_3] = false;
            }
        } while (timer_channel_started[STRIP_NUM_1] || \
        		 timer_channel_started[STRIP_NUM_2] || \
				 timer_channel_started[STRIP_NUM_3]);
        transfer_begin:
			while (HAL_OK != timer_access_hal_start_timer(&g_tim1_handle_config,
			                                              timer_channel, \
														 (uint32_t *)g_ws2812b_info[strip_num].p_pwm_data, \
														 (g_ws2812b_info[strip_num].led_strip_length * BITS_PER_BYTE * \
																 sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES))
			{
			    // retry every 10 ms to free up CPU time!
				free_rtos_delay_ms(10);
			}
			timer_channel_started[strip_num] = true;
    }
}


/**
 * @brief   Check if the strip num is set within the passed mask
 * @param   strip_mask - strip_mask_t value representing strip[s]
 * @param   strip_num - strip_num_e value representing strip[s] to check
 * @return  bool - true if passed strip_num is set in strip_mask, else false.
 */
bool ws2812b_strip_is_set_in_mask(const strip_mask_t strip_mask,
                               strip_num_e strip_num)
{
    return (strip_mask & ws2812_strip_num_to_strip_bit(strip_num));
}


/**
 * @brief   Show strip #1
 * @param   void
 * @return  void
 */
void ws2812b_show_strip_one(void)
{
	ws2812b_show(STRIP_BIT_1);
}


/**
 * @brief   Show strip #2
 * @param   void
 * @return  void
 */
void ws2812b_show_strip_two(void)
{
	ws2812b_show(STRIP_BIT_2);
}


/**
 * @brief   Show strip #3
 * @param   void
 * @return  void
 */
void ws2812b_show_strip_three(void)
{
	ws2812b_show(STRIP_BIT_3);
}


/**
 * @brief   Push out the data stored in buffer to the strip within strip_mask
 * @param   strip_mask_t value representing strip[s]
 * @return  void
 * @note    This function individually checks for all possible bit settings.
 *          Individually the buffers are filled and started per strip.  This is
 *          done due to a finding that parallel timer DMA operations resulted in
 *          unwanted flicker!  This needs further debug!
 */
void ws2812b_show(const strip_mask_t strip_mask)
{
	if (STRIP_BIT_1 & strip_mask)
	{
		ws2812b_fill_pwm_buffer_strip((STRIP_BIT_1));
		ws2812b_dma_transfer(STRIP_BIT_1);
	}
	if (STRIP_BIT_2 & strip_mask)
	{
		ws2812b_fill_pwm_buffer_strip((STRIP_BIT_2));
		ws2812b_dma_transfer(STRIP_BIT_2);
	}
	if (STRIP_BIT_3 & strip_mask)
	{
		ws2812b_fill_pwm_buffer_strip((STRIP_BIT_3));
		ws2812b_dma_transfer(STRIP_BIT_3);
	}
}


/**
 * @brief   Initialize the strip buffers.
 * @param   void
 * @return  void
 * @note    This function will allocate space for all strips regardless of use.
 *          Static allocation globally and filled dynamically.  Note, that the
 *          arrays could be allocated on an as need basis but easier to work
 *          with downstream code having all allocated and defined.
 * @note    Power montor initialization occurs in this function.  This calculates
 *          a factor to apply to each individual LED color to maintain a certain
 *          current level.  This is a coarse method of current control through
 *          FW.  The particular method uses worst case current draw per LED.
 */
void ws2812b_init(void)
{
	gp_pwm_data_strip_1 = NULL;
	gp_pwm_data_strip_2 = NULL;
	gp_pwm_data_strip_3 = NULL;
	// should only need to memset the ending once... Nothing else should touch it if things working!
	memset(g_pwm_data_strip_1 + sizeof(ws2812b_led_t) * BITS_PER_BYTE * STRIP_1_LENGTH, 0, WS2812B_RESET_TIME_CYCLES + 2 * sizeof(uint32_t));
	memset(g_pwm_data_strip_2 + sizeof(ws2812b_led_t) * BITS_PER_BYTE * STRIP_2_LENGTH, 0, WS2812B_RESET_TIME_CYCLES + 2 * sizeof(uint32_t));
	memset(g_pwm_data_strip_3 + sizeof(ws2812b_led_t) * BITS_PER_BYTE * STRIP_3_LENGTH, 0, WS2812B_RESET_TIME_CYCLES + 2 * sizeof(uint32_t));
	g_ws2812b_info[STRIP_NUM_1].p_pwm_data = g_pwm_data_strip_1;
	g_ws2812b_info[STRIP_NUM_2].p_pwm_data = g_pwm_data_strip_2;
	g_ws2812b_info[STRIP_NUM_3].p_pwm_data = g_pwm_data_strip_3;

	led_ctrl_power_monitor_init();
}
