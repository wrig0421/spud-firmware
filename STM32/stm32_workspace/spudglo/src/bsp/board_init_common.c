// SRW

#include "main.h"
#include "stm32l4xx_hal.h"
#include <time.h>
#include "led_ctrl.h"
#include "led_animate.h"

#include "board_specific.h"
#include <stdlib.h>
#include "FreeRTOSConfig.h"
#include "board_init_common.h"
#include "gpio_config_hal.h"
#include "gpio_config_hal_specific.h"
#include "button_config_hal.h"
#include "button_config_hal_specific.h"
#include "timer_config_hal.h"
#include "i2c_config_hal.h"

static void board_init_common_sysclk_init(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    // enable HSE & LSI.
    // some SpudGlo boards have LSE option.  For now only using LSI.
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSI;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSEState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) while(1);

    // select HSE as sysclk
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | \
    							  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) while(1);

    // select LSI as RTC clk source
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) Error_Handler();
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) Error_Handler();
}


static void board_init_common_timer_init(void)
{
//    __HAL_RCC_DMA1_CLK_ENABLE(); // TODO determine a better place for this clock enable call.
//    __HAL_RCC_DMA2_CLK_ENABLE();
//
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
//    TIM_MasterConfigTypeDef sMasterConfig = {0};
//    TIM_OC_InitTypeDef sConfigOC = {0};
//    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
//
////    g_tim1_handle.Instance = TIM1;
////    g_tim1_handle.Init.Prescaler = 0;
////    g_tim1_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
////    g_tim1_handle.Init.Period = 60-1;
////    g_tim1_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
////    g_tim1_handle.Init.RepetitionCounter = 0;
////    g_tim1_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//
//    if (HAL_TIM_Base_Init(&g_tim1_handle) != HAL_OK) Error_Handler();
//    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//    if (HAL_TIM_ConfigClockSource(&g_tim1_handle, &sClockSourceConfig) != HAL_OK) Error_Handler();
//    if (HAL_TIM_PWM_Init(&g_tim1_handle) != HAL_OK) Error_Handler();
//    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
//    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//    if (HAL_TIMEx_MasterConfigSynchronization(&g_tim1_handle, &sMasterConfig) != HAL_OK) Error_Handler();
//    sConfigOC.OCMode = TIM_OCMODE_PWM1;
//    sConfigOC.Pulse = 0;
//    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
//    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
//    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
//    if (HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) Error_Handler();
//    if (HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) Error_Handler();
//    if (HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &sConfigOC, TIM_CHANNEL_3) != HAL_OK) Error_Handler();
//    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
//    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
//    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
//    sBreakDeadTimeConfig.DeadTime = 0;
//    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
//    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
//    sBreakDeadTimeConfig.BreakFilter = 0;
//    sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
//    sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
//    sBreakDeadTimeConfig.Break2Filter = 0;
//    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
//    if (HAL_TIMEx_ConfigBreakDeadTime(&g_tim1_handle, &sBreakDeadTimeConfig) != HAL_OK) Error_Handler();
//    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle, TIM_CHANNEL_1);
//    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle, TIM_CHANNEL_2);
//    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle, TIM_CHANNEL_3);
//#if defined(BOARD_SPUDGLO_BUSINESS_CARD) || defined(BOARD_SPUDGLO_BABY_DINOSAUR_V1)
//    GPIO_InitStruct.Pin = gpio_config_pin_lookup(GPIO_PIN_TIM1_CH1); // hack for now...
//#else
//    GPIO_InitStruct.Pin = gpio_config_pin_lookup(GPIO_PIN_TIM1_CH1) | gpio_config_pin_lookup(GPIO_PIN_TIM1_CH2) | gpio_config_pin_lookup(GPIO_PIN_TIM1_CH3);
//#endif
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
//    HAL_GPIO_Init(gpio_config_port_lookup(GPIO_PIN_TIM1_CH1), &GPIO_InitStruct); // all timer pins are on the same port!
//
//    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
}


void board_init_common_board_init(void)
{
	// TODO replace the random seed with a flash read that will
	// see the random color
    srand(time(0));

    HAL_Init();
    board_init_common_sysclk_init();

    // setup gpio
    gpio_config_hal_setup();

    // setup i2c, spi, uart if present
    board_init_peripheral_setup();

    // setup timers on board
    board_init_common_timer_init();

    timer_config_hal_setup();

    // initialize the LED strip
    ws2812b_init();

    // setup any board specific items
    board_init_specific();
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


