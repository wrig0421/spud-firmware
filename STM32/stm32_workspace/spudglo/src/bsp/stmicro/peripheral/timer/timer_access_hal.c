// SRW

#include "stm32l4xx_hal.h"
#include "free_rtos_convenience.h"
#include "timer_access_hal.h"


extern TIM_HandleTypeDef 	g_tim1_handle_config;


HAL_StatusTypeDef timer_access_hal_start_timer(TIM_HandleTypeDef* p_timer_handle, uint32_t timer_channel,
												const uint32_t* p_data, uint16_t length_data)
{
	//


    return (HAL_TIM_PWM_Start_DMA(p_timer_handle, timer_channel, p_data, length_data));
}


//void timer_access_h


void timer_access_hal_stop_timer(void)
{
    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle_config, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle_config, TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle_config, TIM_CHANNEL_3);
}


