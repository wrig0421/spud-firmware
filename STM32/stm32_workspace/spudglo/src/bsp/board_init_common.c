// SRW

#include "main.h"
#include "stm32l4xx_hal.h"
#include <time.h>
#include "animate_led.h"
#include "board_common.h"
#include "board_specific.h"
#include <stdlib.h>
#include "FreeRTOSConfig.h"
#include "board_init_common.h"


typedef enum
{
    TIMER_1 = 0,
    NUM_TIMERS
} timer_e;


DMA_HandleTypeDef hdma_tim1_ch1;
DMA_HandleTypeDef hdma_tim1_ch2;
DMA_HandleTypeDef hdma_tim1_ch3;
DMA_HandleTypeDef hdma_tim15_ch1_up_trig_com;
DMA_HandleTypeDef hdma_tim16_ch1_up;

RTC_HandleTypeDef g_rtc_handle;
TIM_HandleTypeDef g_tim1_handle;
TIM_HandleTypeDef g_tim15_handle;
TIM_HandleTypeDef g_tim16_handle;

bool g_dma_done_flag = false;
volatile int datasentflag = 0;
uint32_t g_button_on_count[NUM_PUSH_BUTTONS] = {0};
bool button_press_state[NUM_PUSH_BUTTONS] = {false};
extern UART_HandleTypeDef      gh_host_usart;

static void board_init_common_rtc_init(void)
{
    g_rtc_handle.Instance = RTC;
    g_rtc_handle.Init.HourFormat = RTC_HOURFORMAT_24;
    g_rtc_handle.Init.AsynchPrediv = 127;
    g_rtc_handle.Init.SynchPrediv = 255;
    g_rtc_handle.Init.OutPut = RTC_OUTPUT_DISABLE;
    g_rtc_handle.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
    g_rtc_handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    g_rtc_handle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    if (HAL_RTC_Init(&g_rtc_handle) != HAL_OK) Error_Handler();
}

static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) while(1);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) while(1);
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) Error_Handler();
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) Error_Handler();
}


static void board_init_common_timer_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
    g_tim1_handle.Instance = TIM1;
    g_tim1_handle.Init.Prescaler = 0;
    g_tim1_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_tim1_handle.Init.Period = 60-1;
    g_tim1_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    g_tim1_handle.Init.RepetitionCounter = 0;
    g_tim1_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&g_tim1_handle) != HAL_OK) Error_Handler();
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&g_tim1_handle, &sClockSourceConfig) != HAL_OK) Error_Handler();
    if (HAL_TIM_PWM_Init(&g_tim1_handle) != HAL_OK) Error_Handler();
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&g_tim1_handle, &sMasterConfig) != HAL_OK) Error_Handler();
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) Error_Handler();
    if (HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) Error_Handler();
    if (HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &sConfigOC, TIM_CHANNEL_3) != HAL_OK) Error_Handler();
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
    if (HAL_TIMEx_ConfigBreakDeadTime(&g_tim1_handle, &sBreakDeadTimeConfig) != HAL_OK) Error_Handler();
    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle, TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle, TIM_CHANNEL_3);
    GPIO_InitStruct.Pin = PIN_TIM1_CH1|PIN_TIM1_CH2|PIN_TIM1_CH3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


static void board_init_common_nvic_setup_interrupts(void)
{
    __HAL_GPIO_EXTI_CLEAR_IT(EXTI0_IRQn);
    __HAL_GPIO_EXTI_CLEAR_IT(EXTI2_IRQn);
    __HAL_GPIO_EXTI_CLEAR_IT(EXTI9_5_IRQn);
    __HAL_GPIO_EXTI_CLEAR_IT(EXTI15_10_IRQn);
    HAL_NVIC_SetPriority(EXTI0_IRQn, 24, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    HAL_NVIC_SetPriority(EXTI2_IRQn, 24, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 24, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 24, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

    __HAL_GPIO_EXTI_CLEAR_IT(EXTI0_IRQn);
    __HAL_GPIO_EXTI_CLEAR_IT(EXTI2_IRQn);
    __HAL_GPIO_EXTI_CLEAR_IT(EXTI9_5_IRQn);
    __HAL_GPIO_EXTI_CLEAR_IT(EXTI15_10_IRQn);

    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
    HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
    HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
}


static void board_init_common_setup_wakeups(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // setup the wakeups as only interrupts without the WKUP enabled yet... TODO
    GPIO_InitStruct.Pin = PIN_WKUP_1|PIN_WKUP_4;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_WKUP_2|PIN_WKUP_3;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    board_init_common_nvic_setup_interrupts();

}

static void board_init_port_wakeup(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();

}

uint8_t new_buf[10] = {32,33,34,35};
void board_init_common_board_init(void)
{
    srand(time(0));
    HAL_Init();
    SystemClock_Config();

    board_init_port_wakeup();

    board_init_common_setup_wakeups();
    board_init_specific();

    board_init_common_timer_init();

    ws2812b_init();

    //animate_led_init(); // not yet defined..

    board_init_common_rtc_init();
}


void board_init_common_button_pressed(const board_init_push_buttons_e button)
{
    button_press_state[(uint8_t)button] = true;
}


void board_init_common_stop_timer(void)
{
    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle, TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop_DMA(&g_tim1_handle, TIM_CHANNEL_3);
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

