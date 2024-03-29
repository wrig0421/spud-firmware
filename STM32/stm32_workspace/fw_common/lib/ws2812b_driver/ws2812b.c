
#include "cmsis_os.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "ws2812b.h"

#define WS2812B_TIM_FREQ_MHZ				48
#define WS2812B_TIM_TIME_CYCLES				(float)(1.0f / WS2812B_TIM_FREQ_MHZ)

#define WS2812B_PULSE_FREQ_KHZ				800.0f
#define WS2812B_PULSE_TIME_NANOSECONDS		1250.0f
#define WS2812B_PULSE_TIME_CYCLES			((WS2812B_PULSE_TIME_NANOSECONDS / WS2812B_TIM_TIME_CYCLES) / 1000.0f)
#define WS2812B_RESET_TIME_NANOSECONDS		60000.0f
//#define WS2812B_RESET_TIME_CYCLES			((float)((WS2812B_RESET_TIME_NANOSECONDS / WS2812B_TIM_TIME_CYCLES) / 1000.0f))
#define WS2812B_RESET_TIME_CYCLES           3000.0f

#define WS2812B_T0H_TIME_NANOSECONDS		400.0f
#define WS2812B_T1H_TIME_NANOSECONDS		800.0f
#define WS2812B_T0L_TIME_NANOSECONDS		850.0f
#define WS2812B_T1L_TIME_NANOSECONDS		450.0f
#define WS2812B_TIME_CUSHION_NANOSECONDS	150.0f // +/-

#define WS2812B_BIT_SET_CYCLES 				((((WS2812B_T1H_TIME_NANOSECONDS + WS2812B_T0L_TIME_NANOSECONDS) / 2.0f) / WS2812B_TIM_TIME_CYCLES) / 1000.0f)
#define WS2812B_BIT_RESET_CYCLES			(WS2812B_PULSE_TIME_CYCLES - WS2812B_BIT_SET_CYCLES)
#define BITS_PER_BYTE	8

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

uint16_t g_num_leds = 0;
uint16_t g_all_strip_mask = 0;
uint16_t g_max_strip_length = 0;
p_pwm_data_t gp_pwm_data_ping;
p_pwm_data_t gp_pwm_data_pong;
p_pwm_data_t gp_pwm_data_fill;
p_ws2812b_led_t gp_ws28128b_strip[NUM_STRIPS];
bool g_pwm_data_ping = false;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim16;
extern bool g_dma_done_flag;


extern volatile int datasentflag;

uint16_t pwm_reset[50] = {0};
void reset_ws2812b(void)
{
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwm_reset, 50);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t *)pwm_reset, 50);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t *)pwm_reset, 50);
    HAL_TIM_PWM_Start_DMA(&htim15, TIM_CHANNEL_1, (uint32_t *)pwm_reset, 50);
    HAL_TIM_PWM_Start_DMA(&htim16, TIM_CHANNEL_1, (uint32_t *)pwm_reset, 50);
}

static strip_bit_e ws2812_convert_strip_num_to_strip_bit(strip_num_e strip_num)
{
	return (strip_bit_e)(strip_num + 1);
}


static strip_num_e ws2812_convert_strip_bit_to_strip_num(strip_bit_e strip_bit)
{
	return (strip_num_e)(strip_bit - 1);
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


bool ws2812_pixel_is_in_strip_range(strip_bit_e strip_bit, uint16_t pixel)
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


void ws2812b_set_led(const strip_bit_e strip_bit, uint16_t led_num, color_t red, color_t green, color_t blue)
{
	strip_num_e strip_num = ws2812_convert_strip_bit_to_strip_num(strip_bit);
	(gp_ws28128b_strip[strip_num] + led_num)->red = red;
	(gp_ws28128b_strip[strip_num] + led_num)->green = green;
	(gp_ws28128b_strip[strip_num] + led_num)->blue = blue;
}


void ws2812b_fill_pwm_buffer(const strip_bit_e strip_bit)
{
	// fill the pwm data here  
	uint16_t strip_size = ws2812_get_strip_size(strip_bit);
	uint32_t color = 0;
	strip_num_e strip_num = ws2812_convert_strip_bit_to_strip_num(strip_bit);
//	if (g_pwm_data_ping) gp_pwm_data_fill = gp_pwm_data_ping;
//	else gp_pwm_data_fill = gp_pwm_data_pong;
	for (uint16_t iii = 0; iii < strip_size; iii++)
	{
		color = (((gp_ws28128b_strip[strip_num] + iii)->green) << 16) | (((gp_ws28128b_strip[strip_num] + iii)->red) << 8) | (((gp_ws28128b_strip[strip_num] + iii)->blue));
		for (uint8_t yyy = 0; yyy < BITS_PER_BYTE * sizeof(ws2812b_led_t); yyy++)
		{
			gp_pwm_data_fill[(iii * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + yyy] = (color & (1 << (23 - yyy))) ? (uint16_t)(WS2812B_BIT_SET_CYCLES + 1) : (uint16_t)WS2812B_BIT_RESET_CYCLES;
		}
	}
	for (uint16_t iii = 0; iii < WS2812B_RESET_TIME_CYCLES; iii++)
	{
		gp_pwm_data_fill[(strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + iii] = 0;
	}

//	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t *)gp_pwm_data_fill, (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
//	datasentflag = 0;
//	while (!datasentflag);//{HAL_Delay(1);};
//    datasentflag = 0;

	HAL_TIM_PWM_Start_DMA(&htim15, TIM_CHANNEL_1, (uint32_t *)gp_pwm_data_fill, (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
	datasentflag = 0;
	while (!datasentflag) osDelay(10);
	datasentflag = 0;

//	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)gp_pwm_data_fill, (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
//	datasentflag = 0;
//	while (!datasentflag);//{HAL_Delay(1);};
//	datasentflag = 0;

//	HAL_TIM_PWM_Start_DMA(&htim16, TIM_CHANNEL_1, (uint32_t *)gp_pwm_data_fill, (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
//	datasentflag = 0;
//	while (!datasentflag);//{HAL_Delay(1);};
//	datasentflag = 0;

//	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t *)gp_pwm_data_fill, (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + WS2812B_RESET_TIME_CYCLES);
//	datasentflag = 0;
//	while (!datasentflag);//{HAL_Delay(1);};
//	datasentflag = 0;
}


void ws2812b_reset(void)
{
	// call TIM PWM DMA to reset.
}


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
	for (int iii = 0; iii < NUM_STRIPS; iii++)
	{
		g_all_strip_mask |= 1 << iii;
	}
	
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
	gp_pwm_data_fill = malloc((sizeof(ws2812b_led_t) * BITS_PER_BYTE * g_max_strip_length) + WS2812B_RESET_TIME_CYCLES);
//	gp_pwm_data_ping = malloc((sizeof(ws2812b_led_t) * BITS_PER_BYTE * g_max_strip_length) + WS2812B_RESET_TIME_CYCLES);
//	gp_pwm_data_pong = malloc((sizeof(ws2812b_led_t) * BITS_PER_BYTE * g_max_strip_length) + WS2812B_RESET_TIME_CYCLES);
}

void ws2812b_show(const strip_mask_t strip_mask)
{
	for (uint8_t iii = 0; iii < STRIP_BIT_NUM_STRIPS; iii++)
	{
		if ((1 << iii) & strip_mask)
		{
			ws2812b_fill_pwm_buffer(iii + 1); // iii = strip num!
			// get the data in pwm form.. 
		} // show it
	}
}
