// Spud
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

extern float g_max_current_ratio;
extern TIM_HandleTypeDef 	g_tim1_handle_config;

// below hard coded 2880 because WS2812B_RESET_TIME_CYCLES
uint8_t g_pwm_data_strip_1[sizeof(ws2812b_led_t) * BITS_PER_BYTE * STRIP_1_LENGTH + WS2812B_RESET_TIME_CYCLES + 2*sizeof(uint32_t)];
uint8_t g_pwm_data_strip_2[sizeof(ws2812b_led_t) * BITS_PER_BYTE * STRIP_2_LENGTH + WS2812B_RESET_TIME_CYCLES + 2*sizeof(uint32_t)];
uint8_t g_pwm_data_strip_3[sizeof(ws2812b_led_t) * BITS_PER_BYTE * STRIP_3_LENGTH + WS2812B_RESET_TIME_CYCLES + 2*sizeof(uint32_t)];

uint32_t g_reset_cycles = WS2812B_RESET_TIME_CYCLES;

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
 * @brief   Reset LED strip >= 50 microseconds of 0
 * @param   void
 * @return  void
 */
void reset_ws2812b(void)
{

//    semaphore_take(SEMAPHORE_DMA_TRANSFER);
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle_config, TIM_CHANNEL_1, g_pwm_reset, sizeof(g_pwm_reset));
//    semaphore_take(SEMAPHORE_DMA_TRANSFER);
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle_config, TIM_CHANNEL_2, g_pwm_reset, sizeof(g_pwm_reset));
//    semaphore_take(SEMAPHORE_DMA_TRANSFER);
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle_config, TIM_CHANNEL_3, g_pwm_reset, sizeof(g_pwm_reset));
}


strip_num_e ws2812_strip_bit_to_strip_num(strip_bit_e strip_bit)
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
 * @brief   Return the size of the current strip
 * @param   void
 * @return  void
 */
uint16_t ws2812_get_strip_size(const strip_bit_e strip_bit)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(strip_bit);
	return g_ws2812b_info[strip_num].led_strip_length;
}


uint16_t ws2812_get_number_of_active_strips(const strip_mask_t strip_mask)
{
	uint16_t num_active_strips = 0;
	for (strip_num_e iii = STRIP_NUM_1; iii < NUM_STRIPS; iii = (strip_num_e)(iii + 1))
	{
		if (iii & strip_mask) num_active_strips++;
	}
	return num_active_strips;
}


/**
 * @brief   Get the number of active LEDs in the active strips
 * @param   strip_mask: active strips to find max of
 * @return  Number of active LEDs
 */
uint16_t ws2812_get_num_active_animation_leds(const strip_mask_t strip_mask)
{
	uint16_t strip_size = 0;
	if (STRIP_BIT_1 & strip_mask) strip_size += g_ws2812b_info[STRIP_NUM_1].led_strip_length;
	if (STRIP_BIT_2 & strip_mask) strip_size += g_ws2812b_info[STRIP_NUM_2].led_strip_length;
	if (STRIP_BIT_3 & strip_mask) strip_size += g_ws2812b_info[STRIP_NUM_3].led_strip_length;
	return strip_size;
}


/**
 * @brief   Return max strip size in the active strips
 * @param   strip_mask: active strips to find max of
 * @return  The max strip size
 */
uint16_t ws2812_led_get_max_strip_size(const strip_mask_t strip_mask)
{
	uint16_t max_strip_size = 0;
	if ((STRIP_BIT_1 & strip_mask) && \
			(max_strip_size < g_ws2812b_info[STRIP_NUM_1].led_strip_length)) \
					max_strip_size = g_ws2812b_info[STRIP_NUM_1].led_strip_length;
	if ((STRIP_BIT_2 & strip_mask) && \
			(max_strip_size < g_ws2812b_info[STRIP_NUM_2].led_strip_length)) \
					max_strip_size = g_ws2812b_info[STRIP_NUM_2].led_strip_length;
	if ((STRIP_BIT_3 & strip_mask) && \
			(max_strip_size < g_ws2812b_info[STRIP_NUM_3].led_strip_length)) \
					max_strip_size = g_ws2812b_info[STRIP_NUM_3].led_strip_length;
	return max_strip_size;
}


/**
 * @brief   Check if pixel number is in the strip range
 * @param   strip_bit: strip to check if pixel is in range
 * @param	pixel: LED # to check
 * @return  true if in range, else false
 */
bool ws2812_pixel_is_in_strip_range(const strip_bit_e strip_bit, const uint16_t pixel)
{
	bool return_val = false;
	if ((STRIP_BIT_1 == strip_bit) && (pixel < g_ws2812b_info[STRIP_NUM_1].led_strip_length)) return_val = true;
	else if ((STRIP_BIT_2 == strip_bit) && (pixel < g_ws2812b_info[STRIP_NUM_2].led_strip_length)) return_val = true;
	else if ((STRIP_BIT_3 == strip_bit) && (pixel < g_ws2812b_info[STRIP_NUM_3].led_strip_length)) return_val = true;
	return return_val;
}


/**
 * @brief   Set an LED in the strip
 * @param   strip_bit: strip to set LED in
 * @param	led_num: LED number
 * @param	red: 8 bit red
 * @param 	green: 8 bit green
 * @param 	blue: 8 bit blue
 * @return  void
 */
void ws2812b_set_led(const strip_bit_e strip_bit, const uint16_t led_num, const color_t red, const color_t green,
                     const color_t blue)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(strip_bit);
	(g_ws2812b_info[strip_num].p_led_strip + led_num)->red = red * g_max_current_ratio;
	(g_ws2812b_info[strip_num].p_led_strip + led_num)->green = green * g_max_current_ratio;
	(g_ws2812b_info[strip_num].p_led_strip + led_num)->blue = blue * g_max_current_ratio;
}



void ws2812b_dma_transfer(strip_bit_e strip_bit)
{
	static bool timer_channel_started[3] = {false, false, false};
	bool first_pass = true;
	task_notification_value_format_t task_notification_value;
	task_notification_value.value = 0;
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(strip_bit);
    uint32_t timer_channel = 0;
    switch (strip_bit)
    {
    	case STRIP_BIT_1: timer_channel = TIM_CHANNEL_1; break;
    	case STRIP_BIT_2: timer_channel = TIM_CHANNEL_2; break;
    	case STRIP_BIT_3: timer_channel = TIM_CHANNEL_3; break;
    	default: break;
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
        	// one at a time approach??
        	xTaskNotifyWait(0, (uint32_t)task_notification_value.value, (uint32_t *)&task_notification_value.value, portMAX_DELAY);
            // all transfers must be complete before we start another transfer!
            if (task_notification_value.entity_bits.strip_1) timer_channel_started[STRIP_NUM_1] = false;
            if (task_notification_value.entity_bits.strip_2) timer_channel_started[STRIP_NUM_2] = false;
            if (task_notification_value.entity_bits.strip_3) timer_channel_started[STRIP_NUM_3] = false;
        } while (timer_channel_started[STRIP_NUM_1] || \
        		 timer_channel_started[STRIP_NUM_2] || \
				 timer_channel_started[STRIP_NUM_3]);
        // wait for notification from all transfers
        // no more transfers occurgin!
        transfer_begin:
			while (HAL_OK != timer_access_hal_start_timer(&g_tim1_handle_config, timer_channel, \
														 (uint32_t *)g_ws2812b_info[strip_num].p_pwm_data, \
														 (g_ws2812b_info[strip_num].led_strip_length * BITS_PER_BYTE * \
																 sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES))
			{
				free_rtos_delay_ms(10);
			}
			timer_channel_started[strip_num] = true;
    }
}


/**
 * @brief   Fill the PWM buffer for the strip num
 * @param   strip_bit: PWM buffer pertaining to strip
 * @return  void
 */
void ws2812b_fill_pwm_buffer_strip(strip_bit_e strip_bit)
{
    uint32_t color = 0;
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(strip_bit);
    for (uint16_t iii = 0; iii < g_ws2812b_info[strip_num].led_strip_length; iii++)
    {
    	// reconstruct 24 bit color...
        color = (((g_ws2812b_info[strip_num].p_led_strip + iii)->green) << 16) | \
        		(((g_ws2812b_info[strip_num].p_led_strip + iii)->red) << 8) | \
				(((g_ws2812b_info[strip_num].p_led_strip + iii)->blue));
        // walk over each bit.. starting at msb
        for (uint16_t yyy = 0; yyy < BITS_PER_BYTE * sizeof(ws2812b_led_t); yyy++)
        {
        	// if bit in color is set then fill w/ WS2812B_BIT_SET_CYCLES else WS2812B_BIT_RESET_CYCLES

        	g_ws2812b_info[strip_num].p_pwm_data[(iii * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + yyy] = \
        			(color & (1 << ((sizeof(ws2812b_led_t) * BITS_PER_BYTE) - 1 - yyy))) ? \
        					(uint16_t)(WS2812B_BIT_SET_CYCLES + 1) : \
							(uint16_t)WS2812B_BIT_RESET_CYCLES;
        }
    }
    // reset will automatically occur.  It's filled to 0 once on init.  It will be sent out after the pwm_buffer
}


void ws2812b_show_strip_one(void)
{
	ws2812b_show(STRIP_BIT_1);
}


void ws2812b_show_strip_two(void)
{
	ws2812b_show(STRIP_BIT_2);
}


void ws2812b_show_strip_three(void)
{
	ws2812b_show(STRIP_BIT_3);
}


/**
 * @brief   Show the strip(s)
 * @param   strip_mask: bit vector. 1 = show, 0 = don't
 * @return  void
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
