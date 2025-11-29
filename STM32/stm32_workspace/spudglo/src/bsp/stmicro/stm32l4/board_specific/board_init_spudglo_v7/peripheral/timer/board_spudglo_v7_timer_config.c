// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_V7P0)
#include "stm32l4xx_hal.h"
#include "gpio_config_hal.h"
#include "timer_config_hal.h"
#include "gpio_config_hal_specific.h"
#include "timer_config_hal_specific.h"

TIM_HandleTypeDef 	g_tim1_handle_config =
{
	.Instance = TIM1,
    .Init.Prescaler = 0,
    .Init.CounterMode = TIM_COUNTERMODE_UP,
    .Init.Period = 60-1,
    .Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
    .Init.RepetitionCounter = 0,
    .Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE
};

const timer_config_t g_tim_config[NUM_TIMER_ACCESS_TIMER_INSTANCES] =
{
	[TIMER_ACCESS_TIMER_INSTANCE_1_CHANNEL_1] =
	{
		.pin.timer_pin = GPIO_PIN_TIM1_CH1,
		.pin.timer_port = GPIO_PORT_A,
		.pin.timer_alt_func = GPIO_AF1_TIM1,
		.handle = &g_tim1_handle_config,
	},
//	[TIMER_ACCESS_TIMER_INSTANCE_1_CHANNEL_2] =
//	{
//		.pin.timer_pin = TIMER_INSTANCE_1_CHANNEL_2,
//		.pin.timer_port = TIMER_PORT,
//		.pin.timer_alt_func = GPIO_AF1_TIM1,
//		.handle = &g_tim1_handle_config,
//	},
//	[TIMER_ACCESS_TIMER_INSTANCE_1_CHANNEL_3] =
//	{
//		.pin.timer_pin = TIMER_INSTANCE_1_CHANNEL_3,
//		.pin.timer_port = TIMER_PORT,
//		.pin.timer_alt_func = GPIO_AF1_TIM1,
//		.handle = &g_tim1_handle_config,
//	},
};




#endif

