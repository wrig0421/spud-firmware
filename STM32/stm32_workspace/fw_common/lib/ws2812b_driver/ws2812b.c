
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
#define WS2812B_RESET_TIME_NANOSECONDS		52000.0f
#define WS2812B_RESET_TIME_CYCLES			(float)((WS2812B_RESET_TIME_NANOSECONDS / WS2812B_TIM_TIME_CYCLES) / 1000.0f)

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
p_ws2812b_led_t gp_ws28128b_strip[NUM_STRIPS];

uint16_t g_num_leds = 0;
uint16_t g_all_strip_mask = 0;
uint16_t g_max_strip_length = 0; 

p_pwm_data_t gp_pwm_data_ping;
p_pwm_data_t gp_pwm_data_pong;
p_pwm_data_t gp_pwm_data_fill;


bool g_pwm_data_ping = false;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern volatile int datasentflag;


static strip_bit_e ws2812_convert_strip_num_to_strip_bit(strip_num_e strip_num)
{
	return (strip_bit_e)(strip_num + 1);
}


static strip_num_e ws2812_convert_strip_bit_to_strip_num(strip_bit_e strip_bit)
{
	return (strip_num_e)(strip_bit - 1);
}

static uint16_t animate_led_get_strip_size(const strip_bit_e strip_bit)
{
	uint16_t strip_size = 0;
	if (STRIP_BIT_ALL_SET == strip_bit) strip_size = g_max_strip_length;
	else strip_size = strip_length[ws2812_convert_strip_num_to_strip_bit(strip_bit)];
	return strip_size;
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
	uint16_t strip_size = animate_led_get_strip_size(strip_bit);
	uint32_t color = 0;
	strip_num_e strip_num = ws2812_convert_strip_bit_to_strip_num(strip_bit);
	if (g_pwm_data_ping) gp_pwm_data_fill = gp_pwm_data_ping;
	else gp_pwm_data_fill = gp_pwm_data_pong;
	for (uint16_t iii = 0; iii < strip_size; iii++)
	{
		color = (((gp_ws28128b_strip[strip_num] + iii)->green) << 16) | (((gp_ws28128b_strip[strip_num] + iii)->red) << 8) | (((gp_ws28128b_strip[strip_num] + iii)->blue));
		for (uint8_t yyy = 0; yyy < BITS_PER_BYTE * sizeof(ws2812b_led_t); yyy++)
		{
			gp_pwm_data_fill[(iii * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + yyy] = (color & (1 << (23 - yyy))) ? (uint16_t)(WS2812B_BIT_SET_CYCLES + 1) : (uint16_t)WS2812B_BIT_RESET_CYCLES;
		}
	}
	for (uint16_t iii = 0; iii < 3000; iii++)
	{
		gp_pwm_data_fill[(strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + iii] = 0;
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)gp_pwm_data_fill, (strip_size * BITS_PER_BYTE * sizeof(ws2812b_led_t)) + 3000);
	datasentflag = 0;
	while (!datasentflag);//{HAL_Delay(1);};
	datasentflag = 0;
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
	gp_pwm_data_ping = malloc((sizeof(ws2812b_led_t) * BITS_PER_BYTE * g_max_strip_length) + 3000);
	gp_pwm_data_pong = malloc((sizeof(ws2812b_led_t) * BITS_PER_BYTE * g_max_strip_length) + 3000);
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
