// Spud
#include "FreeRTOS.h"
#include "semphr.h"
#include "cmsis_os.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "config.h"
#include "current_monitor.h"
#include "numbers.h"
#include "ws2812b.h"

//extern osThreadId_t g_dma_transfer_handle;
//extern SemaphoreHandle_t g_dma_transfer_semaphore;
//extern SemaphoreHandle_t g_dma_fill_semaphore;
extern bool g_tim_pwm_transfer_cmplt;
extern float g_max_current_ratio;
extern TIM_HandleTypeDef g_tim1_handle;

p_pwm_data_t gp_pwm_data_fill;


ws2812b_led_t g_led_strip[NUM_LEDS];
ws2812b_info_t g_ws2812b_info[5] =
{
	[STRIP_NUM_1] =
	{
		.led_strip_length = STRIP_1_LENGTH,
		.led_strip = g_led_strip,
		.pwm_dma_buffer_index_start = 0
	},
	[STRIP_NUM_2] =
	{
		.led_strip_length = STRIP_2_LENGTH,
		.led_strip = g_led_strip + STRIP_1_LENGTH,
		.pwm_dma_buffer_index_start = (STRIP_1_LENGTH * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES
	},
	[STRIP_NUM_3] =
	{
		.led_strip_length = STRIP_3_LENGTH,
		.led_strip = g_led_strip + STRIP_2_LENGTH,
		.pwm_dma_buffer_index_start = ((STRIP_2_LENGTH + STRIP_1_LENGTH) * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + (2*WS2812B_RESET_TIME_CYCLES)
	}
};


/**
 * @brief   Reset LED strip >= 50 microseconds of 0
 * @param   void
 * @return  void
 */
void reset_ws2812b(void)
{
	// something needs to change here... This should be 3000
	uint8_t g_pwm_reset[50] = {0}; // 50 bytes on stack...
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_1, (uint32_t *)g_pwm_reset, sizeof(g_pwm_reset));
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_2, (uint32_t *)g_pwm_reset, sizeof(g_pwm_reset));
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_3, (uint32_t *)g_pwm_reset, sizeof(g_pwm_reset));
}


/**
 * @brief   Return the size of the current strip
 * @param   void
 * @return  void
 */
uint16_t ws2812_get_strip_size(const strip_num_e strip_num)
{
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
	if (STRIP_NUM_1 & strip_mask) strip_size += g_ws2812b_info[STRIP_NUM_1].led_strip_length;
	if (STRIP_NUM_2 & strip_mask) strip_size += g_ws2812b_info[STRIP_NUM_2].led_strip_length;
	if (STRIP_NUM_3 & strip_mask) strip_size += g_ws2812b_info[STRIP_NUM_3].led_strip_length;
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
	if ((STRIP_NUM_1 & strip_mask) && \
			(max_strip_size < g_ws2812b_info[STRIP_NUM_1].led_strip_length)) \
					max_strip_size = g_ws2812b_info[STRIP_NUM_1].led_strip_length;
	if ((STRIP_NUM_2 & strip_mask) && \
			(max_strip_size < g_ws2812b_info[STRIP_NUM_2].led_strip_length)) \
					max_strip_size = g_ws2812b_info[STRIP_NUM_2].led_strip_length;
	if ((STRIP_NUM_3 & strip_mask) && \
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
bool ws2812_pixel_is_in_strip_range(const strip_num_e strip_num, const uint16_t pixel)
{
	bool return_val = false;
	if ((STRIP_NUM_1 == strip_num) && (pixel < g_ws2812b_info[STRIP_NUM_1].led_strip_length)) return_val = true;
	else if ((STRIP_NUM_2 == strip_num) && (pixel < g_ws2812b_info[STRIP_NUM_2].led_strip_length)) return_val = true;
	else if ((STRIP_NUM_3 == strip_num) && (pixel < g_ws2812b_info[STRIP_NUM_3].led_strip_length)) return_val = true;
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
void ws2812b_set_led(const strip_num_e strip_num, const uint16_t led_num, const color_t red, const color_t green,
                     const color_t blue)
{
	(g_ws2812b_info[strip_num].led_strip + led_num)->red = red * g_max_current_ratio;
	(g_ws2812b_info[strip_num].led_strip + led_num)->green = green * g_max_current_ratio;
	(g_ws2812b_info[strip_num].led_strip + led_num)->blue = blue * g_max_current_ratio;
}


/**
 * @brief   Fill the PWM buffer for the strip num
 * @param   strip_num: PWM buffer pertaining to strip
 * @return  void
 */
void ws2812b_fill_pwm_buffer_strip(strip_num_e strip_num)
{
    uint32_t color = 0;
    uint32_t timer_channel = 0;
    for (uint16_t iii = 0; iii < g_ws2812b_info[strip_num].led_strip_length; iii++)
    {
    	// reconstruct 24 bit color...
        color = (((g_ws2812b_info[strip_num].led_strip + iii)->green) << 16) | \
        		(((g_ws2812b_info[strip_num].led_strip + iii)->red) << 8) | \
				(((g_ws2812b_info[strip_num].led_strip + iii)->blue));
        // walk over each bit.. starting at msb
        for (uint8_t yyy = 0; yyy < BITS_PER_BYTE * sizeof(ws2812b_led_t); yyy++)
        {
        	// if bit in color is set then fill w/ WS2812B_BIT_SET_CYCLES else WS2812B_BIT_RESET_CYCLES
            gp_pwm_data_fill[g_ws2812b_info[strip_num].pwm_dma_buffer_index_start + (iii * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + yyy] = \
            		(color & (1 << ((sizeof(ws2812b_led_t) * BITS_PER_BYTE) - 1 - yyy))) ? \
            				(uint16_t)(WS2812B_BIT_SET_CYCLES + 1) : (uint16_t)WS2812B_BIT_RESET_CYCLES;
        }
    }
    for (uint16_t iii = 0; iii < WS2812B_RESET_TIME_CYCLES; iii++)
    {
        gp_pwm_data_fill[(g_ws2812b_info[strip_num].pwm_dma_buffer_index_start + (g_ws2812b_info[strip_num].led_strip_length * BITS_PER_BYTE * sizeof(ws2812b_led_t))) + iii] = 0;
    }
    switch (strip_num)
    {
    	case STRIP_NUM_1:
    		timer_channel = TIM_CHANNEL_1;
		break;
    	case STRIP_NUM_2:
    		timer_channel = TIM_CHANNEL_2;
		break;
    	case STRIP_NUM_3:
    		timer_channel = TIM_CHANNEL_3;
		break;
    	default:
    	break;

    }
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, timer_channel, (uint32_t *)(gp_pwm_data_fill + g_ws2812b_info[strip_num].pwm_dma_buffer_index_start), (g_ws2812b_info[strip_num].led_strip_length * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
}


void ws2812b_reset(void)
{
	// call TIM PWM DMA to reset.
}


void ws2812b_show_strip_one(void)
{
	ws2812b_show(STRIP_NUM_1);
}


void ws2812b_show_strip_two(void)
{
	ws2812b_show(STRIP_NUM_2);
}


void ws2812b_show_strip_three(void)
{
	ws2812b_show(STRIP_NUM_3);
}


/**
 * @brief   Show the strip(s)
 * @param   strip_mask: bit vector. 1 = show, 0 = don't
 * @return  void
 */
void ws2812b_show(const strip_mask_t strip_mask)
{
	if (STRIP_NUM_1 & strip_mask)
	{
		ws2812b_fill_pwm_buffer_strip((STRIP_NUM_1));
	}
	if (STRIP_NUM_2 & strip_mask)
	{
		ws2812b_fill_pwm_buffer_strip((STRIP_NUM_2));
	}
	if (STRIP_NUM_3 & strip_mask)
	{
		ws2812b_fill_pwm_buffer_strip((STRIP_NUM_3));
	}
}


void ws2812b_init(void)
{
	uint32_t total_led_bits_in_all_strips = (sizeof(ws2812b_led_t) * BITS_PER_BYTE * NUM_LEDS);
	//g_all_strip_mask = STRIP_ALL_SET;
    gp_pwm_data_fill = malloc(total_led_bits_in_all_strips + (NUM_STRIPS * WS2812B_RESET_TIME_CYCLES));
	current_monitor_init();
}
