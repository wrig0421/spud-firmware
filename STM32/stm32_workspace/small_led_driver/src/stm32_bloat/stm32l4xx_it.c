/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "stm32l4xx_it.h"
//#include "stm32l4xx_hal.h"
#include "board_init_common.h"
#include "board_common.h"
#include "board_specific.h"
#include "animate_led.h"
#include "color_led.h"
#include "task_button_press.h"
#include <stdbool.h>

extern osThreadId_t g_dma_transfer_handle;
extern volatile int datasentflag;
extern bool g_dma_done_flag;

extern DMA_HandleTypeDef hdma_tim1_ch1;
extern DMA_HandleTypeDef hdma_tim1_ch2;
extern DMA_HandleTypeDef hdma_tim1_ch3;
extern DMA_HandleTypeDef hdma_tim15_ch1_up_trig_com;
extern DMA_HandleTypeDef hdma_tim16_ch1_up;
extern SemaphoreHandle_t g_dma_transfer_semaphore;

extern bool g_tasks_running;
extern osThreadId_t g_button_press_handle;

extern uint32_t g_button_press_timestamp[NUM_PUSH_BUTTONS][NUM_TIMESTAMPS];
extern UART_HandleTypeDef      gh_host_usart;


/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
    while (1)
    {
        for (uint8_t iii = 0; iii < 1; iii++)
        {
            board_init_red_led_on();
            HAL_Delay(100);
            board_init_red_led_off();
        }
        HAL_Delay(3000);
    }
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
    while (1)
    {
        for (uint8_t iii = 0; iii < 2; iii++)
        {
            board_init_red_led_on();
            HAL_Delay(100);
            board_init_red_led_off();
        }
        HAL_Delay(3000);
    }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
    while (1)
    {
        for (uint8_t iii = 0; iii < 3; iii++)
        {
            board_init_red_led_on();
            HAL_Delay(100);
            board_init_red_led_off();
        }
        HAL_Delay(3000);
    }
}
/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
    while (1)
    {
        for (uint8_t iii = 0; iii < 4; iii++)
        {
            board_init_red_led_on();
            HAL_Delay(100);
            board_init_red_led_off();
        }
        HAL_Delay(3000);
    }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
    while (1)
    {
        for (uint8_t iii = 0; iii < 5; iii++)
        {
            board_init_red_led_on();
            HAL_Delay(100);
            board_init_red_led_off();
        }
        HAL_Delay(3000);
    }
}

///**
//  * @brief This function handles System service call via SWI instruction.
//  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
}

///**
//  * @brief This function handles Pendable request for system service.
//  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}


void USARTx_IRQHandler(void)
{
  HAL_UART_IRQHandler(&gh_host_usart);
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/


/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken;

    // A button is speed
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_1);
    g_button_press_timestamp[PUSH_BUTTON_A][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[PUSH_BUTTON_A][TIMESTAMP_CURRENT];
    g_button_press_timestamp[PUSH_BUTTON_A][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    HAL_NVIC_DisableIRQ(EXTI0_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, PUSH_BUTTON_A, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
}

uint32_t g_dbg_b_interrupt_count = 0;
/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    // B button is state
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_4);
    g_button_press_timestamp[PUSH_BUTTON_D][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[PUSH_BUTTON_B][TIMESTAMP_CURRENT];
    g_button_press_timestamp[PUSH_BUTTON_D][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    HAL_NVIC_DisableIRQ(EXTI2_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, PUSH_BUTTON_D, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
}


/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    // C button is color
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_2);
    g_button_press_timestamp[PUSH_BUTTON_C][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[PUSH_BUTTON_C][TIMESTAMP_CURRENT];
    g_button_press_timestamp[PUSH_BUTTON_C][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, PUSH_BUTTON_C, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
}


/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    // D button is pause
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_3);
    g_button_press_timestamp[PUSH_BUTTON_B][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[PUSH_BUTTON_D][TIMESTAMP_CURRENT];
    g_button_press_timestamp[PUSH_BUTTON_B][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, PUSH_BUTTON_B, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
}


void HAL_DMA_CMPLT_CALLBACK(DMA_HandleTypeDef *hdma)
{
    while(1);
}


bool g_tim_pwm_transfer_cmplt = false;
bool gb_dma_cmplt_strip_1 = true;
bool gb_dma_cmplt_strip_2 = true;
bool gb_dma_cmplt_strip_3 = true;

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    switch (htim->Channel)
    {
        case HAL_TIM_ACTIVE_CHANNEL_1:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
            gb_dma_cmplt_strip_1 = true;
        break;
        case HAL_TIM_ACTIVE_CHANNEL_2:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_2);
            gb_dma_cmplt_strip_2 = true;
        break;
        case HAL_TIM_ACTIVE_CHANNEL_3:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_3);
            gb_dma_cmplt_strip_3 = true;
        break;
        default:
        break;
    }
}


/**
  * @brief This function handles DMA1 channel2 global interrupt.
  */
void DMA1_Channel2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_tim1_ch1);
}

/**
  * @brief This function handles DMA1 channel3 global interrupt.
  */
void DMA1_Channel3_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_tim1_ch2);
}

/**
  * @brief This function handles DMA1 channel5 global interrupt.
  */
void DMA1_Channel5_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_tim15_ch1_up_trig_com);
}

/**
  * @brief This function handles DMA1 channel6 global interrupt.
  */
void DMA1_Channel6_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_tim16_ch1_up);
}

/**
  * @brief This function handles DMA1 channel7 global interrupt.
  */
void DMA1_Channel7_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_tim1_ch3);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
