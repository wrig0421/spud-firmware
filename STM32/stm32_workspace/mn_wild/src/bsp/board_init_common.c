// SRW

#include "main.h"
#include "stm32l4xx_hal.h"
#include <time.h>
#include "animate_led.h"
#include "board_common.h"
#include "board_specific.h"
#include <stdlib.h>
#include "board_init_common.h"


typedef enum
{
    TIMER_1 = 0,
    TIMER_15,
    TIMER_16,
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


/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Configure LSE Drive Capability
    */
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) Error_Handler();
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) Error_Handler();
    /** Configure the main internal regulator output voltage
    */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) Error_Handler();
}


static void board_init_common_timer_init(timer_e timer)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
    switch (timer)
    {
        case TIMER_1:
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
            GPIO_InitStruct.Pin = PIN_TIM1_CH1;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
            GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        break;

        default:
        break;
    }
}


static void board_init_common_nvic_setup_interrupts(void)
{
    HAL_NVIC_SetPriority(EXTI0_IRQn, 24, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    HAL_NVIC_SetPriority(EXTI2_IRQn, 24, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    HAL_NVIC_SetPriority(EXTI9_5_IRQn , 24, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 24, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

    __HAL_GPIO_EXTI_CLEAR_IT(EXTI0_IRQn);
    __HAL_GPIO_EXTI_CLEAR_IT(EXTI9_5_IRQn);
    __HAL_GPIO_EXTI_CLEAR_IT(EXTI15_10_IRQn);
    __HAL_GPIO_EXTI_CLEAR_IT(EXTI2_IRQn);

//    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 20, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 20, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 20, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 20, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 20, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
//
//    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
//    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
}


void board_init_setup_gpio_input_no_pull(GPIO_TypeDef* port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}


static void board_init_setup_gpio_input_pullup(GPIO_TypeDef* port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}


static void board_init_setup_gpio_input_pulldown(GPIO_TypeDef* port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}


static void board_init_setup_gpio_output_no_pull(GPIO_TypeDef* port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}


static void board_init_setup_gpio_output_pullup(GPIO_TypeDef* port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}


static void board_init_setup_gpio_output_pulldown(GPIO_TypeDef* port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}


static void board_init_setup_gpio_output_high(GPIO_TypeDef* port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}


static void board_init_setup_gpio_output_low(GPIO_TypeDef* port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}


void board_init_adafruit_reset(adafruit_soundboard_reset_e reset)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_ADAFRUIT_RESET_N;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
    if (ADAFRUIT_SOUNDBOARD_RESET_ENABLE == reset)
    {
        HAL_GPIO_WritePin(PIN_PORT_A, PIN_ADAFRUIT_RESET_N, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(PIN_PORT_A, PIN_ADAFRUIT_RESET_N, GPIO_PIN_SET);
    }
}


bool board_init_adafruit_soundboard_is_playing_audio(void)
{
    bool return_val = false;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_ADAFRUIT_ACT;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(PIN_PORT_C, PIN_ADAFRUIT_ACT))
    {
        return_val = true;
    }
    return return_val;
}


void board_init_adafruit_soundboard_adjust_volume(adafruit_soundboard_volume_e volume)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    switch (volume)
    {
        case ADAFRUIT_SOUNDBOARD_VOLUME_UP:
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_VOL_UP;
            HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
            HAL_GPIO_WritePin(PIN_PORT_C, GPIO_InitStruct.Pin, GPIO_PIN_RESET);
        break;
        case ADAFRUIT_SOUNDBOARD_VOLUME_DOWN:
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_VOL_DOWN;
            HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
            HAL_GPIO_WritePin(PIN_PORT_C, GPIO_InitStruct.Pin, GPIO_PIN_RESET);
        break;
        case ADAFRUIT_SOUNDBOARD_VOLUME_RELEASE:
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_VOL_UP | PIN_ADAFRUIT_VOL_DOWN;
            HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
            HAL_GPIO_WritePin(PIN_PORT_C, GPIO_InitStruct.Pin, GPIO_PIN_SET);
        break;
        default:
        break;
    }
}


void board_init_adafruit_soundboard_power_enable_disable(adafruit_soundboard_power_enable_disable_e enable_disable)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_ADAFRUIT_PWR_EN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    if (ADAFRUIT_SOUNDBOARD_POWER_ENABLE == enable_disable)
    {
        HAL_GPIO_WritePin(PIN_PORT_C, PIN_ADAFRUIT_PWR_EN, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(PIN_PORT_C, PIN_ADAFRUIT_PWR_EN, GPIO_PIN_RESET);
    }
}


void board_init_adafruit_soundboard_enable_mode(adafruit_soundboard_mode_e mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_ADAFRUIT_UART_ENABLE_N;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    if (ADAFRUIT_SOUNDBOARD_UART_MODE == mode)
    {
        HAL_GPIO_WritePin(PIN_PORT_C, PIN_ADAFRUIT_UART_ENABLE_N, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(PIN_PORT_C, PIN_ADAFRUIT_UART_ENABLE_N, GPIO_PIN_SET);
    }
}


void board_init_adafruit_soundboard_trigger(adafruit_soundboard_trig_e trigger,
                                            adafruit_soundboard_trig_enable_disable_e enable_disable)
{
    GPIO_TypeDef* port;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    switch (trigger)
    {
        case ADAFRUIT_SOUNDBOARD_TRIG_0:
            port = PIN_PORT_A;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_0;
        break;
        case ADAFRUIT_SOUNDBOARD_TRIG_1:
            port = PIN_PORT_A;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_1;
        break;
        case ADAFRUIT_SOUNDBOARD_TRIG_2:
            port = PIN_PORT_A;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_2;
        break;
        case ADAFRUIT_SOUNDBOARD_TRIG_3:
            port = PIN_PORT_A;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_3;
        break;
        case ADAFRUIT_SOUNDBOARD_TRIG_4:
            port = PIN_PORT_A;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_4;
        break;
        case ADAFRUIT_SOUNDBOARD_TRIG_5:
            port = PIN_PORT_C;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_5;
        break;
        case ADAFRUIT_SOUNDBOARD_TRIG_6:
            port = PIN_PORT_B;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_6;
        break;
        case ADAFRUIT_SOUNDBOARD_TRIG_7:
            port = PIN_PORT_B;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_7;
        break;
        case ADAFRUIT_SOUNDBOARD_TRIG_8:
            port = PIN_PORT_B;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_8;
        break;
        case ADAFRUIT_SOUNDBOARD_TRIG_9:
            port = PIN_PORT_B;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_9;
        break;
        case ADAFRUIT_SOUNDBOARD_TRIG_10:
            port = PIN_PORT_C;
            GPIO_InitStruct.Pin = PIN_ADAFRUIT_TRIG_10;
        break;
        default:
        break;
    }
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
    if (ADAFRUIT_SOUNDBOARD_TRIG_ENABLE == enable_disable)
    {
        HAL_GPIO_WritePin(port, GPIO_InitStruct.Pin, GPIO_PIN_RESET); // LOW for enable
    }
    else
    {
        HAL_GPIO_WritePin(port, GPIO_InitStruct.Pin, GPIO_PIN_SET); // HIGH for disable
    }
}


void board_init_adafruit_soundboard_enable_relay(adafruit_soundboard_relay_e relay)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    if (ADAFRUIT_SOUNDBOARD_RELAY_LIGHT_CTRL == relay)
    {
        GPIO_InitStruct.Pin = PIN_LIGHT_CTRL;
    }
    else
    {
        GPIO_InitStruct.Pin = PIN_SPEAKER_CTRL;
    }
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_A, GPIO_InitStruct.Pin, GPIO_PIN_SET);
}


void board_init_adafruit_soundboard_disable_relay(adafruit_soundboard_relay_e relay)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    if (ADAFRUIT_SOUNDBOARD_RELAY_LIGHT_CTRL == relay)
    {
        GPIO_InitStruct.Pin = PIN_LIGHT_CTRL;
    }
    else
    {
        GPIO_InitStruct.Pin = PIN_SPEAKER_CTRL;
    }
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_A, GPIO_InitStruct.Pin, GPIO_PIN_RESET);
}


void board_init_common_board_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    srand(time(0));
    HAL_Init();
    SystemClock_Config();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    board_init_setup_gpio_output_no_pull(PIN_PORT_C, PIN_LED_OUT_1);
    board_init_setup_gpio_output_no_pull(PIN_PORT_C, PIN_LED_OUT_2);
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LED_OUT_1|PIN_LED_OUT_2, GPIO_PIN_RESET);

    board_init_setup_gpio_input_pulldown(PIN_PORT_B, PIN_GPIO_0);
    board_init_setup_gpio_input_pulldown(PIN_PORT_B, PIN_GPIO_1);
    board_init_setup_gpio_input_pulldown(PIN_PORT_B, PIN_GPIO_2);
    board_init_setup_gpio_input_pulldown(PIN_PORT_C, PIN_GPIO_3);
    board_init_setup_gpio_input_pulldown(PIN_PORT_B, PIN_GPIO_4);
    board_init_setup_gpio_input_pulldown(PIN_PORT_B, PIN_GPIO_5);
    board_init_setup_gpio_input_pulldown(PIN_PORT_B, PIN_GPIO_6);
    board_init_setup_gpio_input_pulldown(PIN_PORT_B, PIN_GPIO_7);

    board_init_adafruit_reset(ADAFRUIT_SOUNDBOARD_RESET_ENABLE);
    board_init_adafruit_soundboard_power_enable_disable(ADAFRUIT_SOUNDBOARD_POWER_DISABLE);

    board_init_setup_gpio_output_no_pull(PIN_PORT_A, PIN_LVL_DIR); // A -> B enable via pullup on board
    board_init_setup_gpio_output_no_pull(PIN_PORT_A, PIN_LVL_EN); // active low enabled by pulldown on board

    board_init_setup_gpio_output_low(PIN_PORT_A, PIN_LIGHT_CTRL);
    board_init_setup_gpio_output_low(PIN_PORT_A, PIN_SPEAKER_CTRL);

    board_init_setup_gpio_input_no_pull(PIN_PORT_A, PIN_WKUP_1);
    board_init_setup_gpio_input_no_pull(PIN_PORT_A, PIN_WKUP_4);
    board_init_setup_gpio_input_no_pull(PIN_PORT_C, PIN_WKUP_2);
    board_init_setup_gpio_input_no_pull(PIN_PORT_C, PIN_WKUP_3);

    HAL_GPIO_WritePin(PIN_PORT_A, PIN_LVL_DIR, GPIO_PIN_SET);
    HAL_GPIO_WritePin(PIN_PORT_A, PIN_LVL_EN, GPIO_PIN_RESET);
    //while (GPIO_PIN_SET == HAL_GPIO_ReadPin(PIN_PORT_A, PIN_WKUP_1));
    // setup the wakeups as only interrupts without the WKUP enabled yet... TODO
    GPIO_InitStruct.Pin = PIN_WKUP_1|PIN_WKUP_4;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);


    GPIO_InitStruct.Pin = PIN_WKUP_2|PIN_WKUP_3;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);

    board_init_common_nvic_setup_interrupts();
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
    HAL_TIM_PWM_Stop_DMA(&g_tim15_handle, TIM_CHANNEL_1);
}


void board_init_red_led_on(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = RED_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_C, RED_LED, GPIO_PIN_SET);
}


void board_init_red_led_off(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = RED_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_C, RED_LED, GPIO_PIN_RESET);
}


void board_init_green_led_on(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GREEN_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_C, GREEN_LED, GPIO_PIN_SET);
}


void board_init_green_led_off(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GREEN_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_C, GREEN_LED, GPIO_PIN_RESET);
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

