// SRW

#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "timer_config_hal_specific.h"
#include "timer_config_hal.h"
#include "gpio_config_hal.h"

extern const timer_config_t g_tim_config[NUM_TIMER_ACCESS_TIMER_INSTANCES];

extern TIM_HandleTypeDef 	g_tim1_handle_config;
DMA_HandleTypeDef 	g_hdma_tim1_ch1;
DMA_HandleTypeDef 	g_hdma_tim1_ch2;
DMA_HandleTypeDef 	g_hdma_tim1_ch3;
RTC_HandleTypeDef 	g_rtc_handle;

void timer_config_hal_setup(void)
{
    uint32_t channel = TIM_CHANNEL_1;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    __HAL_RCC_DMA1_CLK_ENABLE(); // TODO determine a better place for this clock enable call.
    __HAL_RCC_DMA2_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;

    if (HAL_TIM_Base_Init(&g_tim1_handle_config) != HAL_OK) while (1);
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&g_tim1_handle_config, &sClockSourceConfig) != HAL_OK) while (1);
    if (HAL_TIM_PWM_Init(&g_tim1_handle_config) != HAL_OK) while (1);
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&g_tim1_handle_config, &sMasterConfig) != HAL_OK) while (1);
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.BreakFilter = 0;
    sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
    sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
    sBreakDeadTimeConfig.Break2Filter = 0;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&g_tim1_handle_config, &sBreakDeadTimeConfig) != HAL_OK) while (1);

    // this is somewhat of a hack... TIM_CHANNEL increments by 4 for each instance.
    for (timer_access_timer_instances_e inst = TIMER_ACCESS_TIMER_INSTANCE_1_FIRST;
    		inst < NUM_TIMER_ACCESS_TIMER_INSTANCES; inst++)
    {
        if (HAL_TIM_PWM_ConfigChannel(&g_tim1_handle_config, &sConfigOC, channel) != HAL_OK) while (1);
        HAL_TIM_PWM_Stop_DMA(&g_tim1_handle_config, channel);
        channel += 4;
        GPIO_InitStruct.Pin = gpio_config_pin_lookup(g_tim_config[inst].pin.timer_pin);
        HAL_GPIO_Init(gpio_config_port_lookup(g_tim_config[inst].pin.timer_pin), &GPIO_InitStruct); // all timer pins are on the same port!

    }

    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}


