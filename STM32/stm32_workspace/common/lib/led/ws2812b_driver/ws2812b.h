#if !defined(WS2812B_H)
#define WS2812B_H
#include "config.h"
#include <stdbool.h>

#define WS2812B_TIM_FREQ_MHZ                48
#define WS2812B_TIM_TIME_CYCLES             (float)(1.0f / WS2812B_TIM_FREQ_MHZ)

#define WS2812B_PULSE_FREQ_KHZ              800.0f
#define WS2812B_PULSE_TIME_NANOSECONDS      1250.0f
#define WS2812B_PULSE_TIME_CYCLES           ((WS2812B_PULSE_TIME_NANOSECONDS / WS2812B_TIM_TIME_CYCLES) / 1000.0f)
#define WS2812B_RESET_TIME_NANOSECONDS      60000.0f
//#define WS2812B_RESET_TIME_CYCLES         ((float)((WS2812B_RESET_TIME_NANOSECONDS / WS2812B_TIM_TIME_CYCLES) / 1000.0f))
#define WS2812B_RESET_TIME_CYCLES           3000.0f

#define WS2812B_T0H_TIME_NANOSECONDS        400.0f
#define WS2812B_T1H_TIME_NANOSECONDS        800.0f
#define WS2812B_T0L_TIME_NANOSECONDS        850.0f
#define WS2812B_T1L_TIME_NANOSECONDS        450.0f
#define WS2812B_TIME_CUSHION_NANOSECONDS    150.0f

#define WS2812B_BIT_SET_CYCLES              ((((WS2812B_T1H_TIME_NANOSECONDS + WS2812B_T0L_TIME_NANOSECONDS) / 2.0f) / WS2812B_TIM_TIME_CYCLES) / 1000.0f)
#define WS2812B_BIT_RESET_CYCLES            (WS2812B_PULSE_TIME_CYCLES - WS2812B_BIT_SET_CYCLES)

typedef uint8_t color_t;
typedef uint16_t strip_mask_t; // 16 strips max..


typedef enum
{
    WS2812B_PING = 0,
    WS2812B_PONG
} ws2812b_ping_pong_e;


typedef enum
{
	STRIP_NONE = 0,
	STRIP_NUM_1 = (1 << 0),
	STRIP_NUM_2 = (1 << 1),
	STRIP_NUM_3 = (1 << 2),
	STRIP_ALL_SET = STRIP_NUM_1 | STRIP_NUM_2 | STRIP_NUM_3,
	NUM_STRIPS = NUM_ACTIVE_STRIPS,
    ALL_STRIPS = NUM_STRIPS
} strip_num_e;


//typedef enum
//{
//	STRIP_BIT_NONE_SET = 0,
//	STRIP_NUM_3 = (1 << 0),
//	STRIP_BIT_2 = (1 << 1),
//	STRIP_BIT_3 = (1 << 2),
//	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3
//} strip_bit_e;


typedef struct
{
    color_t red;
    color_t green; 
    color_t blue;
} ws2812b_led_t;


typedef struct
{
	ws2812b_led_t*	led_strip;
	uint16_t 		led_strip_length;
	uint16_t 		pwm_dma_buffer_index_start;
} ws2812b_info_t;


typedef ws2812b_led_t* p_ws2812b_led_t;
typedef uint16_t* p_pwm_data_t;


void reset_ws2812b(void);
uint16_t ws2812_get_strip_size(const strip_bit_e strip_bit);
uint16_t ws2812_get_number_of_active_strips(const strip_mask_t strip_mask);
strip_bit_e ws2812_get_next_active_strip(const strip_mask_t strip_mask, const strip_bit_e prev_strip_bit);
uint16_t ws2812_get_num_active_animation_leds(const strip_mask_t strip_mask);
uint16_t ws2812_led_get_max_strip_size(const strip_mask_t strip_mask);
bool ws2812_pixel_is_in_strip_range(const strip_bit_e strip_bit, const uint16_t pixel);
void ws2812b_set_led(const strip_bit_e strip_bit, const uint16_t led_num, const color_t red, const color_t green,
                     const color_t blue);
void ws2812b_fill_pwm_buffer(const strip_bit_e strip_bit);
void ws2812b_reset(void);
void ws2812b_init(void);
void ws2812b_show(const strip_mask_t strip_mask);
void ws2812b_show_strip_one(void);
void ws2812b_show_strip_two(void);
void ws2812b_show_strip_three(void);
uint16_t ws2812b_strip_size(void);
void ws2812b_set_strip_size(const strip_bit_e strip_bit);
void ws2812b_dma_transfer(const strip_mask_t strip_bit);
uint16_t ws2812_get_pwm_strip_offset(const strip_bit_e strip_bit);
ws2812b_ping_pong_e ws2812b_ping_or_pong(void);


#endif
