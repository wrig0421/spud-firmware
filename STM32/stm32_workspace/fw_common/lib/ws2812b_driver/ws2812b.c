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


extern osThreadId_t g_dma_transfer_handle;
extern SemaphoreHandle_t g_dma_transfer_semaphore;
extern SemaphoreHandle_t g_dma_fill_semaphore;

extern bool g_tim_pwm_transfer_cmplt;

extern float g_max_current_ratio;

uint16_t strip_length[NUM_STRIPS] = 
{
#if defined(STRIP_1_LENGTH)
	STRIP_1_LENGTH,
#endif
#if defined(STRIP_2_LENGTH)
	STRIP_2_LENGTH,
#endif
#if defined(STRIP_3_LENGTH)
	STRIP_3_LENGTH,
#endif
#if defined(STRIP_4_LENGTH)
	STRIP_4_LENGTH,
#endif
#if defined(STRIP_5_LENGTH)
	STRIP_5_LENGTH,
#endif
#if defined(STRIP_6_LENGTH)
	STRIP_6_LENGTH,
#endif
#if defined(STRIP_7_LENGTH)
	STRIP_7_LENGTH,
#endif
#if defined(STRIP_8_LENGTH)
	STRIP_8_LENGTH,
#endif
#if defined(STRIP_9_LENGTH)
	STRIP_9_LENGTH
#endif
};


#if defined(STRIP_1_LENGTH)
ws2812b_led_t g_strip_1[STRIP_1_LENGTH];
#endif
#if defined(STRIP_2_LENGTH)
ws2812b_led_t g_strip_2[STRIP_2_LENGTH];
#endif
#if defined(STRIP_3_LENGTH)
ws2812b_led_t g_strip_3[STRIP_3_LENGTH];
#endif
#if defined(STRIP_4_LENGTH)
ws2812b_led_t g_strip_4[STRIP_4_LENGTH];
#endif
#if defined(STRIP_5_LENGTH)
ws2812b_led_t g_strip_5[STRIP_5_LENGTH];
#endif
#if defined(STRIP_6_LENGTH)
ws2812b_led_t g_strip_6[STRIP_6_LENGTH];
#endif
#if defined(STRIP_7_LENGTH)
ws2812b_led_t g_strip_7[STRIP_7_LENGTH];
#endif
#if defined(STRIP_8_LENGTH)
ws2812b_led_t g_strip_8[STRIP_8_LENGTH];
#endif
#if defined(STRIP_9_LENGTH)
ws2812b_led_t g_strip_9[STRIP_9_LENGTH];
#endif

uint8_t g_ping_pong = 1;
uint16_t g_num_leds = 0;
uint16_t g_all_strip_mask = 0;
uint16_t g_max_strip_length = 0;

p_pwm_data_t gp_pwm_strip_1_data;
p_pwm_data_t gp_pwm_strip_2_data;
p_pwm_data_t gp_pwm_strip_3_data;


//p_pwm_data_t gp_pwm_data_ping;
//p_pwm_data_t gp_pwm_data_pong;
p_pwm_data_t gp_pwm_data_fill;


p_ws2812b_led_t gp_ws28128b_strip[NUM_STRIPS];

uint16_t g_pwm_data_offsets[NUM_STRIPS] = {0};

bool g_pwm_data_ping = false;

extern bool gb_dma_cmplt_strip_1;
extern bool gb_dma_cmplt_strip_2;
extern bool gb_dma_cmplt_strip_3;

extern TIM_HandleTypeDef g_tim1_handle;
extern TIM_HandleTypeDef g_tim15_handle;
extern TIM_HandleTypeDef g_tim16_handle;
extern bool g_dma_done_flag;


extern volatile int datasentflag;

uint16_t pwm_reset[50] = {0};
void reset_ws2812b(void)
{
    //xSemaphoreTake(g_dma_transfer_semaphore, portMAX_DELAY);
    //xTaskNotify(g_dma_transfer_handle, 0, eSetValueWithOverwrite);

    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_1, (uint32_t *)pwm_reset, sizeof(pwm_reset));
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_2, (uint32_t *)pwm_reset, sizeof(pwm_reset));
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_3, (uint32_t *)pwm_reset, sizeof(pwm_reset));
//    HAL_TIM_PWM_Start_DMA(&g_tim15_handle, TIM_CHANNEL_1, (uint32_t *)pwm_reset, sizeof(pwm_reset)));
//    HAL_TIM_PWM_Start_DMA(&g_tim16_handle, TIM_CHANNEL_1, (uint32_t *)pwm_reset, sizeof(pwm_reset)));
}

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
#if defined(STRIP_1_LENGTH)
        case STRIP_BIT_1:
            offset = 0;
            strip_num = 1;
        break;
#endif
#if defined(STRIP_2_LENGTH)
        case STRIP_BIT_2:
            offset = STRIP_1_LENGTH;
            strip_num = 2;
        break;
#endif
#if defined(STRIP_3_LENGTH)
        case STRIP_BIT_3:
            offset = STRIP_1_LENGTH + STRIP_2_LENGTH;
        break;
#endif
#if defined(STRIP_4_LENGTH)
        case STRIP_BIT_4:
            offset = STRIP_1_LENGTH + STRIP_2_LENGTH + STRIP_3_LENGTH;
        break;
#endif
#if defined(STRIP_5_LENGTH)
        case STRIP_BIT_5:
            offset = STRIP_1_LENGTH + STRIP_2_LENGTH + STRIP_3_LENGTH + STRIP_4_LENGTH;
        break;
#endif
        default:
        break;
    }
    return ((offset * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + (strip_num * WS2812B_RESET_TIME_CYCLES));
}


uint16_t ws2812_get_strip_size(const strip_bit_e strip_bit)
{
	uint16_t strip_size = 0;
	if (STRIP_BIT_ALL_SET == strip_bit) strip_size = g_max_strip_length;
	else strip_size = strip_length[ws2812_convert_strip_num_to_strip_bit(strip_bit)];
	return strip_size;
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
	// STRIP_BIT_ALL_SET is not a valid option!

	for (strip_bit_e iii = prev_strip_bit; iii <= STRIP_BIT_NUM_STRIPS; iii = (strip_bit_e)(iii + 1))
	{
		if (iii & strip_mask) return iii;
	}
	return STRIP_BIT_NO_MORE_SET;  // if this is returned
}


uint16_t ws2812_get_num_active_animation_leds(const strip_mask_t strip_mask)
{
	uint16_t strip_size = 0;
	if (STRIP_BIT_ALL_SET == strip_mask) strip_size = g_num_leds;
	else
	{
#if defined(STRIP_1_LENGTH)
		if (STRIP_BIT_1 & strip_mask) strip_size += STRIP_1_LENGTH;
#endif
#if defined(STRIP_2_LENGTH)
		if (STRIP_BIT_2 & strip_mask) strip_size += STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
		if (STRIP_BIT_3 & strip_mask) strip_size += STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
		if (STRIP_BIT_4 & strip_mask) strip_size += STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
		if (STRIP_BIT_5 & strip_mask) strip_size += STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
		if (STRIP_BIT_6 & strip_mask) strip_size += STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
		if (STRIP_BIT_7 & strip_mask) strip_size += STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
		if (STRIP_BIT_8 & strip_mask) strip_size += STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
		if (STRIP_BIT_9 & strip_mask) strip_size += STRIP_9_LENGTH;
#endif
	}
	return strip_size;
}


uint16_t ws2812_led_get_max_strip_size(const strip_mask_t strip_mask)
{
	uint16_t strip_size = 0;
	if (STRIP_BIT_ALL_SET == strip_mask) strip_size = g_max_strip_length;
	else
	{
#if defined(STRIP_1_LENGTH)
		if ((STRIP_BIT_1 & strip_mask) && (strip_size < STRIP_1_LENGTH)) strip_size = STRIP_1_LENGTH;
#endif
#if defined(STRIP_2_LENGTH)
		if ((STRIP_BIT_2 & strip_mask) && (strip_size < STRIP_2_LENGTH)) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
		if ((STRIP_BIT_3 & strip_mask) && (strip_size < STRIP_3_LENGTH)) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
		if ((STRIP_BIT_4 & strip_mask) && (strip_size < STRIP_4_LENGTH)) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
		if ((STRIP_BIT_5 & strip_mask) && (strip_size < STRIP_5_LENGTH)) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
		if ((STRIP_BIT_6 & strip_mask) && (strip_size < STRIP_6_LENGTH)) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
		if ((STRIP_BIT_7 & strip_mask) && (strip_size < STRIP_7_LENGTH)) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
		if ((STRIP_BIT_8 & strip_mask) && (strip_size < STRIP_8_LENGTH)) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
		if ((STRIP_BIT_9 & strip_mask) && (strip_size < STRIP_9_LENGTH)) strip_size = STRIP_9_LENGTH;
#endif
	}
	return strip_size;
}


bool ws2812_pixel_is_in_strip_range(const strip_bit_e strip_bit, const uint16_t pixel)
{
	bool return_val = false;
#if defined(STRIP_1_LENGTH)
	if ((STRIP_BIT_1 == strip_bit) && (pixel < STRIP_1_LENGTH)) return_val = true;
#endif
#if defined(STRIP_2_LENGTH)
	else if ((STRIP_BIT_2 == strip_bit) && (pixel < STRIP_2_LENGTH)) return_val = true;
#endif
#if defined(STRIP_3_LENGTH)
	else if ((STRIP_BIT_3 == strip_bit) && (pixel < STRIP_3_LENGTH)) return_val = true;
#endif
#if defined(STRIP_4_LENGTH)
	else if ((STRIP_BIT_4 == strip_bit) && (pixel < STRIP_4_LENGTH)) return_val = true;
#endif
#if defined(STRIP_5_LENGTH)
	else if ((STRIP_BIT_5 == strip_bit) && (pixel < STRIP_5_LENGTH)) return_val = true;
#endif
#if defined(STRIP_6_LENGTH)
	else if ((STRIP_BIT_6 == strip_bit) && (pixel < STRIP_6_LENGTH)) return_val = true;
#endif
#if defined(STRIP_7_LENGTH)
	else if ((STRIP_BIT_7 == strip_bit) && (pixel < STRIP_7_LENGTH)) return_val = true;
#endif
#if defined(STRIP_8_LENGTH)
	else if ((STRIP_BIT_8 == strip_bit) && (pixel < STRIP_8_LENGTH)) return_val = true;
#endif
#if defined(STRIP_9_LENGTH)
	else if ((STRIP_BIT_9 == strip_bit) && (pixel < STRIP_9_LENGTH)) return_val = true;
#endif
	return return_val;
}


void ws2812b_set_led(const strip_bit_e strip_bit, const uint16_t led_num, const color_t red, const color_t green,
                     const color_t blue)
{
	strip_num_e strip_num = ws2812_convert_strip_bit_to_strip_num(strip_bit);
    (gp_ws28128b_strip[strip_num] + led_num)->red = red * g_max_current_ratio;
    (gp_ws28128b_strip[strip_num] + led_num)->green = green * g_max_current_ratio;
    (gp_ws28128b_strip[strip_num] + led_num)->blue = blue * g_max_current_ratio;
}


uint16_t g_ws2812b_cur_strip_size = 0;


void ws2812b_set_strip_size(const strip_bit_e strip_bit)
{
    g_ws2812b_cur_strip_size = ws2812_get_strip_size(strip_bit);
}


uint16_t ws2812b_strip_size(void)
{
    return g_ws2812b_cur_strip_size;
}


void ws2812b_dma_transfer(const strip_mask_t strip_mask)
{
    //xSemaphoreTake(g_dma_transfer_semaphore, portMAX_DELAY);
    //xTaskNotify(g_dma_transfer_handle, strip_mask, eSetValueWithOverwrite);
}


ws2812b_ping_pong_e ws2812b_ping_or_pong(void)
{
    if (g_ping_pong) return WS2812B_PING;
    else return WS2812B_PONG;
}



#if defined(STRIP_1_LENGTH)
void ws2812b_fill_pwm_buffer_strip_one(void)
{
    uint32_t color = 0;
    uint32_t strip_size = STRIP_1_LENGTH;
    uint32_t strip_pwm_offset = ws2812_get_pwm_strip_offset(STRIP_BIT_1);
    while (!gb_dma_cmplt_strip_2)
    {
        osDelay(1);
    }
    for (uint16_t iii = 0; iii < strip_size; iii++)
    {
        color = (((gp_ws28128b_strip[STRIP_NUM_1] + iii)->green) << 16) | \
                                (((gp_ws28128b_strip[STRIP_NUM_1] + iii)->red) << 8) | \
                                (((gp_ws28128b_strip[STRIP_NUM_1] + iii)->blue));
        for (uint8_t yyy = 0; yyy < BITS_PER_BYTE * sizeof(ws2812b_led_t); yyy++)
        {
            gp_pwm_data_fill[strip_pwm_offset + (iii * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + yyy] = (color & (1 << (23 - yyy))) ? (uint16_t)(WS2812B_BIT_SET_CYCLES + 1) : (uint16_t)WS2812B_BIT_RESET_CYCLES;
        }
    }
    for (uint16_t iii = 0; iii < WS2812B_RESET_TIME_CYCLES; iii++)
    {
        gp_pwm_data_fill[(strip_pwm_offset + (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t))) + iii] = 0;
    }
    gb_dma_cmplt_strip_2 = false;
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_2, (uint32_t *)(gp_pwm_data_fill + strip_pwm_offset), (STRIP_1_LENGTH * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
}
#endif

#if defined(STRIP_2_LENGTH)
void ws2812b_fill_pwm_buffer_strip_two(void)
{
    uint32_t color = 0;
    uint32_t strip_size = STRIP_2_LENGTH;
    uint32_t strip_pwm_offset = ws2812_get_pwm_strip_offset(STRIP_BIT_2);
    while (!gb_dma_cmplt_strip_3)
    {
        osDelay(1);
    }
    for (uint16_t iii = 0; iii < strip_size; iii++)
    {
        color = (((gp_ws28128b_strip[STRIP_NUM_2] + iii)->green) << 16) | \
                                (((gp_ws28128b_strip[STRIP_NUM_2] + iii)->red) << 8) | \
                                (((gp_ws28128b_strip[STRIP_NUM_2] + iii)->blue));
        for (uint8_t yyy = 0; yyy < BITS_PER_BYTE * sizeof(ws2812b_led_t); yyy++)
        {
            gp_pwm_data_fill[strip_pwm_offset + (iii * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + yyy] = (color & (1 << (23 - yyy))) ? (uint16_t)(WS2812B_BIT_SET_CYCLES + 1) : (uint16_t)WS2812B_BIT_RESET_CYCLES;
        }
    }
    for (uint16_t iii = 0; iii < WS2812B_RESET_TIME_CYCLES; iii++)
    {
        gp_pwm_data_fill[(strip_pwm_offset + (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t))) + iii] = 0;
    }
    gb_dma_cmplt_strip_3 = false;
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_3, (uint32_t *)(gp_pwm_data_fill + strip_pwm_offset), (STRIP_2_LENGTH * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
}
#endif


#if defined(STRIP_3_LENGTH)
void ws2812b_fill_pwm_buffer_strip_three(void)
{
    uint32_t color = 0;
    uint32_t strip_size = STRIP_3_LENGTH;
    uint32_t strip_pwm_offset = ws2812_get_pwm_strip_offset(STRIP_BIT_3);
    while (!gb_dma_cmplt_strip_3)
    {
        osDelay(1);
    }
    for (uint16_t iii = 0; iii < strip_size; iii++)
    {
        color = (((gp_ws28128b_strip[STRIP_NUM_3] + iii)->green) << 16) | \
                                (((gp_ws28128b_strip[STRIP_NUM_3] + iii)->red) << 8) | \
                                (((gp_ws28128b_strip[STRIP_NUM_3] + iii)->blue));
        for (uint8_t yyy = 0; yyy < BITS_PER_BYTE * sizeof(ws2812b_led_t); yyy++)
        {
            gp_pwm_data_fill[strip_pwm_offset + (iii * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + yyy] = (color & (1 << (23 - yyy))) ? (uint16_t)(WS2812B_BIT_SET_CYCLES + 1) : (uint16_t)WS2812B_BIT_RESET_CYCLES;
        }
    }
    for (uint16_t iii = 0; iii < WS2812B_RESET_TIME_CYCLES; iii++)
    {
        gp_pwm_data_fill[(strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + iii] = 0;
    }
    gb_dma_cmplt_strip_3 = false;
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_3, (uint32_t *)gp_pwm_data_fill, (STRIP_3_LENGTH * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
}
#endif


void ws2812b_fill_pwm_buffer(const strip_bit_e strip_bit)
{
	uint16_t strip_size = ws2812_get_strip_size(strip_bit); // get the size of the strip
	ws2812b_set_strip_size(strip_bit); // why??
	uint32_t color = 0;
	strip_num_e strip_num = ws2812_convert_strip_bit_to_strip_num(strip_bit); // set the strip we are writing to
	uint32_t offset = ws2812_get_pwm_strip_offset(strip_bit); // get start offset for strip in the buffer
	uint32_t pwm_offset = offset * BITS_PER_BYTE * sizeof(ws2812b_led_t);
	for (uint16_t iii = 0; iii < strip_size; iii++)
	{
		color = (((gp_ws28128b_strip[strip_num] + iii)->green) << 16) | \
		                (((gp_ws28128b_strip[strip_num] + iii)->red) << 8) | \
		                (((gp_ws28128b_strip[strip_num] + iii)->blue));
		for (uint8_t yyy = 0; yyy < BITS_PER_BYTE * sizeof(ws2812b_led_t); yyy++)
		{
            gp_pwm_data_fill[pwm_offset + (iii * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + yyy] = (color & (1 << (23 - yyy))) ? (uint16_t)(WS2812B_BIT_SET_CYCLES + 1) : (uint16_t)WS2812B_BIT_RESET_CYCLES;
		}
	}
    for (uint16_t iii = 0; iii < WS2812B_RESET_TIME_CYCLES; iii++)
	{
        gp_pwm_data_fill[(strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + iii] = 0;
//        if (WS2812B_PING == ws2812b_ping_or_pong())
//        {
//            gp_pwm_data_ping[(strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + iii] = 0;
//        }
//        else
//        {
//            gp_pwm_data_pong[(strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + iii] = 0;
//        }
	}
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_1, (uint32_t *)gp_pwm_data_fill, (NUM_LEDS * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
    g_tim_pwm_transfer_cmplt = false;
    HAL_TIM_PWM_Start_DMA(&g_tim1_handle, TIM_CHANNEL_2, (uint32_t *)gp_pwm_data_fill, (NUM_LEDS * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
    g_tim_pwm_transfer_cmplt = false;
    while (!g_tim_pwm_transfer_cmplt)
    {
        osDelay(1);
    }




}


void ws2812b_reset(void)
{
	// call TIM PWM DMA to reset.
}


uint32_t g_size = 0;

void ws2812b_init(void)
{

#if defined(STRIP_1_LENGTH)
	gp_ws28128b_strip[STRIP_NUM_1] = g_strip_1;
#endif
#if defined(STRIP_2_LENGTH)
	gp_ws28128b_strip[STRIP_NUM_2] = g_strip_2;
#endif
#if defined(STRIP_3_LENGTH)
	gp_ws28128b_strip[STRIP_NUM_3] = g_strip_3;
#endif
#if defined(STRIP_4_LENGTH)
	gp_ws28128b_strip[STRIP_NUM_4] = g_strip_4;
#endif

	uint8_t num_strips = NUM_STRIPS;
	for (int iii = 0; iii < NUM_STRIPS; iii++) g_all_strip_mask |= 1 << iii;
	switch (num_strips)
	{
#if defined(STRIP_9_LENGTH)
		case 9:
			g_num_leds += STRIP_9_LENGTH;
			g_max_strip_length = STRIP_9_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
		case 8:
			g_num_leds += STRIP_8_LENGTH;
			if (STRIP_8_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_8_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
		case 7:
			g_num_leds += STRIP_7_LENGTH;
			if (STRIP_7_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_7_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
		case 6:
			g_num_leds += STRIP_6_LENGTH;
			if (STRIP_6_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_6_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
		case 5:
			g_num_leds += STRIP_5_LENGTH;
			if (STRIP_5_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_5_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
		case 4:
			g_num_leds += STRIP_4_LENGTH;
			if (STRIP_4_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_4_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
		case 3:
			g_num_leds += STRIP_3_LENGTH;
			if (STRIP_3_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_3_LENGTH;
#endif
#if defined(STRIP_2_LENGTH)
		case 2:
			g_num_leds += STRIP_2_LENGTH;
			if (STRIP_2_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_2_LENGTH;
#endif
		case 1:
			g_num_leds += STRIP_1_LENGTH;
			if (STRIP_1_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_1_LENGTH;
		break;
	}
    gp_pwm_data_fill = malloc((sizeof(ws2812b_led_t) * BITS_PER_BYTE * g_num_leds) + (NUM_STRIPS * WS2812B_RESET_TIME_CYCLES));
    //gp_pwm_data_ping = malloc((sizeof(ws2812b_led_t) * BITS_PER_BYTE * g_num_leds) + (NUM_STRIPS * WS2812B_RESET_TIME_CYCLES));
    //gp_pwm_data_pong = malloc((sizeof(ws2812b_led_t) * BITS_PER_BYTE * g_num_leds) + (NUM_STRIPS * WS2812B_RESET_TIME_CYCLES));
    g_size = (sizeof(ws2812b_led_t) * BITS_PER_BYTE * g_num_leds) + (NUM_STRIPS * WS2812B_RESET_TIME_CYCLES);
    //gp_pwm_data_fill = malloc((sizeof(ws2812b_led_t) * BITS_PER_BYTE * g_max_strip_length) + WS2812B_RESET_TIME_CYCLES);
	current_monitor_init();
}


void ws2812b_show_strip_one(void)
{
    ws2812b_fill_pwm_buffer_strip_one();
}


void ws2812b_show_strip_two(void)
{
    ws2812b_fill_pwm_buffer_strip_two();
}


void ws2812b_show_strip_three(void)
{
    ws2812b_fill_pwm_buffer_strip_three();
}



void ws2812b_show(const strip_mask_t strip_mask)
{
	for (uint8_t iii = 0; iii < STRIP_BIT_NUM_STRIPS; iii++)
	{
	    if (strip_mask & STRIP_BIT_1)
	    {
	        ws2812b_fill_pwm_buffer_strip_one();
	    }
#if defined(STRIP_2_LENGTH)
	    if (strip_mask & STRIP_BIT_2)
	    {
	        ws2812b_fill_pwm_buffer_strip_two();
	    }
#endif
#if defined(STRIP_3_LENGTH)
        if (strip_mask & STRIP_BIT_3)
        {
	        // STRIP_BIT_3
	        ws2812b_fill_pwm_buffer_strip_three();
	    }
#endif
	}
}
