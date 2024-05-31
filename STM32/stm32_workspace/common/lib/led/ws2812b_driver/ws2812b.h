#if !defined(WS2812B_H)
#define WS2812B_H
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "config.h"


#define WS2812B_TIM_FREQ_MHZ                48
#define WS2812B_TIM_TIME_CYCLES             (float)(1.0f / WS2812B_TIM_FREQ_MHZ)

#define WS2812B_PULSE_FREQ_KHZ              800.0f
#define WS2812B_PULSE_TIME_NANOSECONDS      1250.0f
#define WS2812B_PULSE_TIME_CYCLES           ((WS2812B_PULSE_TIME_NANOSECONDS / WS2812B_TIM_TIME_CYCLES) / 1000.0f)
#define WS2812B_RESET_TIME_NANOSECONDS      60000.0f
#define WS2812B_RESET_TIME_CYCLES         	50 //((uint32_t)(((float)((WS2812B_RESET_TIME_NANOSECONDS / WS2812B_TIM_TIME_CYCLES) / 1000.0f))))

#define WS2812B_T0H_TIME_NANOSECONDS        400.0f
#define WS2812B_T1H_TIME_NANOSECONDS        800.0f
#define WS2812B_T0L_TIME_NANOSECONDS        850.0f
#define WS2812B_T1L_TIME_NANOSECONDS        450.0f
#define WS2812B_TIME_CUSHION_NANOSECONDS    150.0f


// WS2812B reset time is >= 50 us
// WS2812B_RESET_TIME_

#define WS2812B_BIT_SET_CYCLES              (uint32_t)((((WS2812B_T1H_TIME_NANOSECONDS + WS2812B_T0L_TIME_NANOSECONDS) / 2.0f) / WS2812B_TIM_TIME_CYCLES) / 1000.0f)
#define WS2812B_BIT_RESET_CYCLES            (uint32_t)(WS2812B_PULSE_TIME_CYCLES - WS2812B_BIT_SET_CYCLES)

typedef uint8_t color_t;
typedef uint16_t strip_mask_t; // 16 strips max..


typedef enum
{
    WS2812B_PING = 0,
    WS2812B_PONG
} ws2812b_ping_pong_e;


typedef enum
{
	STRIP_NUM_1 = 0,
	STRIP_NUM_2,
	STRIP_NUM_3,


	STRIP_NUM_1_AND_2,
	STRIP_NUM_1_AND_3,
	STRIP_NUM_2_AND_3,
	STRIP_NUM_ALL_SET,

	NUM_SUPPORTED_STRIP_COMBOS,

	STRIP_NUM_INVALID,

	NUM_STRIPS = NUM_ACTIVE_STRIPS,
	ALL_STRIPS = NUM_STRIPS
} strip_num_e;


typedef enum
{
	STRIP_BIT_NONE 		= 0,
	STRIP_BIT_1 		= (1 << 0),
	STRIP_BIT_2 		= (1 << 1),
	STRIP_BIT_3 		= (1 << 2),

	STRIP_BIT_1_AND_2	= STRIP_BIT_1 | STRIP_BIT_2,
	STRIP_BIT_1_AND_3	= STRIP_BIT_1 | STRIP_BIT_3,
	STRIP_BIT_2_AND_3	= STRIP_BIT_2 | STRIP_BIT_3,

#if defined(ENABLE_STRIP_3)
	STRIP_BIT_ALL_SET 		= STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3,
#elif defined(ENABLE_STRIP_2)
	STRIP_BIT_ALL_SET 		= STRIP_BIT_1 | STRIP_BIT_2,
#elif defined(ENABLE_STRIP_1)
	STRIP_BIT_ALL_SET 		= STRIP_BIT_1,
#endif
	STRIP_BIT_INVALID	= 0xFFFF - 1
} strip_bit_e;


#pragma pack(1)
typedef struct
{
    color_t red;
    color_t green; 
    color_t blue;
} ws2812b_led_t;
typedef ws2812b_led_t* p_ws2812b_led_t;
typedef uint8_t* p_pwm_data_t;


typedef struct
{
	p_ws2812b_led_t		p_led_strip;
	uint8_t				alignment_fill_1;
	uint16_t 			led_strip_length;
	uint16_t			alignment_fill_2;
	p_pwm_data_t 		p_pwm_data;
} ws2812b_info_t;
#pragma pack(0)


//typedef uint16_t* p_pwm_data_t;


void reset_ws2812b(void);
strip_num_e ws2812_strip_bit_to_num(strip_bit_e strip_bit);
strip_num_e ws2812_strip_bit_to_strip_num(strip_bit_e strip_bit);
void ws2812b_dma_transfer(strip_bit_e strip_bit);

uint16_t ws2812_get_strip_size(const strip_bit_e strip_bit);
uint16_t ws2812_get_number_of_active_strips(const strip_mask_t strip_mask);
uint16_t ws2812_get_num_active_animation_leds(const strip_mask_t strip_mask);
uint16_t ws2812_led_get_max_strip_size(const strip_mask_t strip_mask);
bool ws2812_pixel_is_in_strip_range(const strip_bit_e strip_bit, const uint16_t pixel);
void ws2812b_set_led(const strip_bit_e strip_bit, const uint16_t led_num, const color_t red, const color_t green,
                     const color_t blue);
void ws2812b_fill_pwm_buffer_strip(strip_bit_e strip_bit);
void ws2812b_reset(void);
void ws2812b_show_strip_one(void);
void ws2812b_show_strip_two(void);
void ws2812b_show_strip_three(void);
void ws2812b_show(const strip_mask_t strip_mask);
void ws2812b_init(void);

#endif
