/*
 * ws2812b_driver.c
 *
 *  Created on: Mar 31, 2021
 *      Author: spud
 */
#include "string.h"
#if 0
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_tim2_ch1;

#define PWM_HI 38
#define PWM_LO 19

#define W28128B_BYTES_PER_PIXEL	3
#define WS2812B_STRIP_SIZE		100
#define WS2812B_TOTAL_NUM_BYTES	W28128B_BYTES_PER_PIXEL * WS2812B_STRIP_SIZE
#define WS2812B_PWM_BUF_LEN		W28128B_BYTES_PER_PIXEL * WS2812B_STRIP_SIZE


typedef struct
{
	uint8_t	brightness; // [0, 255]
	uint8_t	strip_size;
	uint8_t strip_index;
} ws2812_struct_t;

ws2812_struct_t g_ws2812_struct =
{
		.brightness = 1,
		.strip_size = WS2812B_STRIP_SIZE,
		.strip_index = 0
};


typedef struct
{
	union
	{
		struct
		{
			uint8_t	red;
			uint8_t green;
			uint8_t	blue;
		} led;
		uint8_t flat_data[WS2812B_STRIP_SIZE * sizeof(led)];
	};
	uint8_t	pwm_buf[WS2812B_STRIP_SIZE * sizeof(led)];
} ws2812_strip_t;


ws2812_strip_t ws2812_strip[WS2812B_STRIP_SIZE] =
{
		.led.red = 0,
		.led.green = 0,
		.led.blue = 0
};


void ws2812_strip_show(void)
{
	if (g_ws2812_struct != 0 || hdma_tim2_ch1.State != HAL_DMA_STATE_READY)
	{
		for (uint8_t i = 0; i < WS2812B_TOTAL_NUM_BYTES; i++)
		{
			ws2812_strip.flat_data[i] = 0;
		}
		g_ws2812_struct.strip_index = 0;
		HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_1);
		return;
	}
	for (uint_fast8_t i = 0; i < 8; i++)
	{

		ws2812_strip.pwm_buf[i + 0] = PWM_LO << (((ws2812_strip.flat_data[0] << i) & 0x80) > 0);
		ws2812_strip.pwm_buf[i + 8] = PWM_LO << (((ws2812_strip.flat_data[1] << i) & 0x80) > 0);
		ws2812_strip.pwm_buf[i + 16] = PWM_LO << (((ws2812_strip.flat_data[2] << i) & 0x80) > 0);
		ws2812_strip.pwm_buf[i + 24] = PWM_LO << (((ws2812_strip.flat_data[3] << i) & 0x80) > 0);
		ws2812_strip.pwm_buf[i + 32] = PWM_LO << (((ws2812_strip.flat_data[4] << i) & 0x80) > 0);
		ws2812_strip.pwm_buf[i + 40] = PWM_LO << (((ws2812_strip.flat_data[5] << i) & 0x80) > 0);
		ws2812_strip.pwm_buf[i + 48] = PWM_LO << (((ws2812_strip.flat_data[6] << i) & 0x80) > 0);
		ws2812_strip.pwm_buf[i + 56] = PWM_LO << (((ws2812_strip.flat_data[7] << i) & 0x80) > 0);
	}
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *) ws2812_strip.pwm_buf,
}


void ws2812_strip_init(void)
{
	memset(ws2812_strip.flat_data, 0, sizeof(ws2812_strip.flat_data));
}


void ws2812_set_brightness(uint8_t brightness)
{
	if (!brightness) brightness = 1;
	g_ws2812_struct.brightness = brightness;
}


uint8_t ws2812_get_brightness(void)
{
	return g_ws2812_struct.brightness;
}


uint32_t ws2812_get_pixel_color(uint32_t pixel)
{
	return (((ws2812_strip.led.red << 16) / g_ws2812_struct.brightness) |
			((ws2812_strip.led.green << 8) / g_ws2812_struct.brightness) |
			((ws2812_strip.led.blue) / g_ws2812_struct.brightness));
}


void ws2812_clear_strip(void)
{
	memset(ws2812_strip.flat_data, 0, sizeof(ws2812_strip.flat_data));
	// write to strip!
}


void ws2812_set_pixel_color(uint32_t pixel, uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t brightness = g_ws2812_struct.brightness;
	uint32_t index = g_ws2812_struct.strip_index;
	if (!brightness) brightness = 1; // prevent div by 0
	ws2812_strip[index].red = (red * brightness) >> 8;
	ws2812_strip[index].green = (green  * brightness) >> 8;
	ws2812_strip[index].blue = (blue  * brightness) >> 8;
}

#endif
