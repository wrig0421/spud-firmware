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

ws2812b_led_t g_led_strip[NUM_LEDS];

ws2812b_info_t g_ws2812b_info[NUM_STRIPS] =
{
	[STRIP_NUM_1] =
	{
		.led_strip_length = STRIP_1_LENGTH,
		.led_strip = g_led_strip
	},
	[STRIP_NUM_2] =
	{
		.led_strip_length = STRIP_2_LENGTH,
		.led_strip = g_led_strip + STRIP_1_LENGTH
	},
	[STRIP_NUM_3] =
	{
		.led_strip_length = STRIP_3_LENGTH,
		.led_strip = g_led_strip + STRIP_2_LENGTH
	}
};

//uint8_t g_ping_pong = 1;
//uint16_t g_num_leds = 0;
//uint16_t g_all_strip_mask = 0;
//uint16_t g_max_strip_length = 0;
//p_pwm_data_t gp_pwm_data_ping;
//p_pwm_data_t gp_pwm_data_pong;
//p_pwm_data_t gp_pwm_data_fill;


p_ws2812b_led_t gp_ws28128b_strip[NUM_STRIPS];


extern TIM_HandleTypeDef g_tim1_handle;

uint8_t g_pwm_reset[50] = {0};


/**
 * @brief   Reset LED strip >= 50 microseconds of 0
 * @param   void
 * @return  void
 */
void reset_ws2812b(void)
{
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_1, (uint32_t *)g_pwm_reset, sizeof(g_pwm_reset));
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_2, (uint32_t *)g_pwm_reset, sizeof(g_pwm_reset));
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_3, (uint32_t *)g_pwm_reset, sizeof(g_pwm_reset));
}


/**
 * @brief   Reset LED strip >= 50 microseconds of 0
 * @param   void
 * @return  void
 */
static strip_bit_e ws2812_convert_strip_num_to_strip_bit(const strip_num_e strip_num)
{
	return (strip_bit_e)(strip_num + 1);
}


static strip_num_e ws2812_convert_strip_bit_to_strip_num(const strip_bit_e strip_bit)
{
	return (strip_num_e)(strip_bit - 1);
}


uint16_t ws2812_get_pwm_strip_offset(const strip_bit_e strip_bit)
{
    uint16_t offset = 0;
    uint8_t strip_num = 0;
    switch (strip_bit)
    {
        case STRIP_BIT_1:
            offset = 0;
            strip_num = 1;
        break;
        case STRIP_BIT_2:
            offset = g_ws2812b_info[ws2812_convert_strip_bit_to_strip_num(STRIP_NUM_1)].led_strip_length;
            strip_num = 2;
        break;
        case STRIP_BIT_3:
            offset = g_ws2812b_info[ws2812_convert_strip_bit_to_strip_num(STRIP_NUM_1)].led_strip_length + \
					 g_ws2812b_info[ws2812_convert_strip_bit_to_strip_num(STRIP_NUM_2)].led_strip_length;
            strip_num = 3;
        break;
        default:
        break;
    }
    return ((offset * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + (strip_num * WS2812B_RESET_TIME_CYCLES));
}


/**
 * @brief   Return the size of the current strip
 * @param   void
 * @return  void
 */
uint16_t ws2812_get_strip_size(const strip_bit_e strip_bit)
{
	return g_ws2812b_info[ws2812_convert_strip_bit_to_strip_num(strip_bit)].led_strip_length;
}


uint16_t ws2812_get_number_of_active_strips(const strip_mask_t strip_mask)
{
	uint16_t num_active_strips = 0;
	for (strip_bit_e iii = STRIP_BIT_1; iii < STRIP_BIT_NUM_STRIPS; iii = (strip_bit_e)(iii + 1))
	{
		if (iii & strip_mask) num_active_strips++;
	}
	return num_active_strips;
}


// if STRIP_BIT_NO_MORE_SET returned then all bits have been encountered
strip_bit_e ws2812_get_next_active_strip(const strip_mask_t strip_mask, const strip_bit_e prev_strip_bit)
{
	for (strip_bit_e iii = prev_strip_bit; iii <= STRIP_BIT_NUM_STRIPS; iii = (strip_bit_e)(iii + 1))
	{
		if (iii & strip_mask) return iii;
	}
	return STRIP_BIT_NO_MORE_SET;  // if this is returned
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
	if ((STRIP_BIT_1 & strip_mask) && (max_strip_size < g_ws2812b_info[STRIP_NUM_1].led_strip_length)) max_strip_size = g_ws2812b_info[STRIP_NUM_1].led_strip_length;
	if ((STRIP_BIT_2 & strip_mask) && (max_strip_size < g_ws2812b_info[STRIP_NUM_2].led_strip_length)) max_strip_size = g_ws2812b_info[STRIP_NUM_2].led_strip_length;
	if ((STRIP_BIT_3 & strip_mask) && (max_strip_size < g_ws2812b_info[STRIP_NUM_3].led_strip_length)) max_strip_size = g_ws2812b_info[STRIP_NUM_3].led_strip_length;
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
	strip_num_e strip_num = ws2812_convert_strip_bit_to_strip_num(strip_bit);
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
    uint32_t strip_size = g_ws2812b_info[strip_num].led_strip_length;
    uint32_t strip_pwm_offset = ws2812_get_pwm_strip_offset(ws2812_convert_strip_bit_to_strip_num(strip_num));
    for (uint16_t iii = 0; iii < strip_size; iii++)
    {
        color = (((g_ws2812b_info[strip_num].led_strip + iii)->green) << 16) | \
                                (((g_ws2812b_info[strip_num].led_strip + iii)->red) << 8) | \
                                (((g_ws2812b_info[strip_num].led_strip + iii)->blue));
        for (uint8_t yyy = 0; yyy < BITS_PER_BYTE * sizeof(ws2812b_led_t); yyy++)
        {
            gp_pwm_data_fill[strip_pwm_offset + (iii * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + yyy] = \
            		(color & (1 << ((sizeof(ws2812b_led_t) * BITS_PER_BYTE) - 1 - yyy))) ? \
            				(uint16_t)(WS2812B_BIT_SET_CYCLES + 1) : (uint16_t)WS2812B_BIT_RESET_CYCLES;
        }
    }
    for (uint16_t iii = 0; iii < WS2812B_RESET_TIME_CYCLES; iii++)
    {
        gp_pwm_data_fill[(strip_pwm_offset + (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t))) + iii] = 0;
    }
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_1, (uint32_t *)(gp_pwm_data_fill + strip_pwm_offset), (g_ws2812b_info[strip_num].led_strip * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
}


void ws2812b_reset(void)
{
	// call TIM PWM DMA to reset.
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
	for (uint8_t iii = 0; iii < STRIP_BIT_NUM_STRIPS; iii++)
	{
	    if (STRIP_BIT_1 & strip_mask)
	    {
	    	ws2812b_fill_pwm_buffer_strip(ws2812_convert_strip_bit_to_strip_num(STRIP_BIT_1));
	    }
	    if (STRIP_BIT_2 & strip_mask)
	    {
	    	ws2812b_fill_pwm_buffer_strip(ws2812_convert_strip_bit_to_strip_num(STRIP_BIT_2));
	    }
        if (STRIP_BIT_3 & strip_mask)
        {
        	ws2812b_fill_pwm_buffer_strip(ws2812_convert_strip_bit_to_strip_num(STRIP_BIT_3));
	    }
	}
}


void ws2812b_init(void)
{
	uint8_t num_strips = NUM_STRIPS;
	for (int iii = 0; iii < NUM_STRIPS; iii++) g_all_strip_mask |= 1 << iii;
    gp_pwm_data_fill = malloc((sizeof(ws2812b_led_t) * BITS_PER_BYTE * NUM_LEDS) + (NUM_STRIPS * WS2812B_RESET_TIME_CYCLES));
	current_monitor_init();
}


//void ws2812b_fill_pwm_buffer(const strip_bit_e strip_bit)
//{
//	uint16_t strip_size = ws2812_get_strip_size(strip_bit); // get the size of the strip
//	ws2812b_set_strip_size(strip_bit); // why??
//	uint32_t color = 0;
//	strip_num_e strip_num = ws2812_convert_strip_bit_to_strip_num(strip_bit); // set the strip we are writing to
//	uint32_t offset = ws2812_get_pwm_strip_offset(strip_bit); // get start offset for strip in the buffer
//    uint32_t strip_pwm_offset = ws2812_get_pwm_strip_offset(ws2812_convert_strip_bit_to_strip_num(strip_num));
//    for (uint16_t iii = 0; iii < strip_size; iii++)
//    {
//        color = (((g_ws2812b_info[strip_num].led_strip + iii)->green) << 16) | \
//                                (((g_ws2812b_info[strip_num].led_strip + iii)->red) << 8) | \
//                                (((g_ws2812b_info[strip_num].led_strip + iii)->blue));
//        for (uint8_t yyy = 0; yyy < BITS_PER_BYTE * sizeof(ws2812b_led_t); yyy++)
//        {
//            gp_pwm_data_fill[strip_pwm_offset + (iii * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + yyy] = \
//            		(color & (1 << ((sizeof(ws2812b_led_t) * BITS_PER_BYTE) - 1 - yyy))) ? \
//            				(uint16_t)(WS2812B_BIT_SET_CYCLES + 1) : (uint16_t)WS2812B_BIT_RESET_CYCLES;
//        }
//    }
//    for (uint16_t iii = 0; iii < WS2812B_RESET_TIME_CYCLES; iii++)
//    {
//        gp_pwm_data_fill[(strip_pwm_offset + (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t))) + iii] = 0;
//    }
//    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_1, (uint32_t *)gp_pwm_data_fill, (NUM_LEDS * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
//    g_tim_pwm_transfer_cmplt = false;
////    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_2, (uint32_t *)gp_pwm_data_fill, (NUM_LEDS * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
////    g_tim_pwm_transfer_cmplt = false;
//    while (!g_tim_pwm_transfer_cmplt)
//    {
//        osDelay(1);
//    }
//}

