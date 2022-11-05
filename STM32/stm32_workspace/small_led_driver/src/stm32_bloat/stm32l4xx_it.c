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
#include "task.h"
#include "stm32l4xx_it.h"
//#include "stm32l4xx_hal.h"
#include "board_init_common.h"
#include "board_common.h"
#include "board_specific.h"

#include "animate_led.h"
#include "color_led.h"
#include <stdbool.h>

extern volatile int datasentflag;
extern bool g_dma_done_flag;

extern DMA_HandleTypeDef hdma_tim1_ch1;
extern DMA_HandleTypeDef hdma_tim1_ch2;
extern DMA_HandleTypeDef hdma_tim1_ch3;
extern DMA_HandleTypeDef hdma_tim15_ch1_up_trig_com;
extern DMA_HandleTypeDef hdma_tim16_ch1_up;


extern osThreadId_t g_button_press_handle;

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
    while (1);
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
    while (1);
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
    while (1);
}
/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
    while (1);
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
    while (1);
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

///**
//  * @brief This function handles System tick timer.
//  */
//void SysTick_Handler(void)
//{
//  HAL_IncTick();
//}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

uint32_t g_a_interrupt_count = 0;
uint32_t g_b_interrupt_count = 0;
uint32_t g_c_interrupt_count = 0;
uint32_t g_d_interrupt_count = 0;

uint32_t g_a_interrupt_current_timestamp = 0;
uint32_t g_a_interrupt_previous_timestamp = 0;

uint32_t g_b_interrupt_current_timestamp = 0;
uint32_t g_b_interrupt_previous_timestamp = 0;

uint32_t g_c_interrupt_current_timestamp = 0;
uint32_t g_c_interrupt_previous_timestamp = 0;

uint32_t g_d_interrupt_current_timestamp = 0;
uint32_t g_d_interrupt_previous_timestamp = 0;


/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    // B button is speed!
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_1);
    g_b_interrupt_previous_timestamp = g_b_interrupt_current_timestamp;
    g_b_interrupt_current_timestamp = xTaskGetTickCountFromISR();
    board_init_common_button_pressed(PUSH_BUTTON_B);
    g_b_interrupt_count++;
    HAL_NVIC_DisableIRQ(EXTI0_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, PUSH_BUTTON_B, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
}

uint32_t g_dbg_b_interrupt_count = 0;
/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    // C button is state!
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_4);
    g_c_interrupt_previous_timestamp = g_c_interrupt_current_timestamp;
    g_c_interrupt_current_timestamp = xTaskGetTickCountFromISR();
    board_init_common_button_pressed(PUSH_BUTTON_C);
    g_c_interrupt_count++;
    HAL_NVIC_DisableIRQ(EXTI2_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, PUSH_BUTTON_C, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
}


/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    // A button is color
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_2);
    g_a_interrupt_previous_timestamp = g_a_interrupt_current_timestamp;
    g_a_interrupt_current_timestamp = xTaskGetTickCountFromISR();
    board_init_common_button_pressed(PUSH_BUTTON_A);
    g_a_interrupt_count++;
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, PUSH_BUTTON_A, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
}


/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    // D button is pause
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_3);
    g_d_interrupt_previous_timestamp = g_d_interrupt_current_timestamp;
    g_d_interrupt_current_timestamp = xTaskGetTickCountFromISR();
    board_init_common_button_pressed(PUSH_BUTTON_D);
    g_d_interrupt_count++;
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, PUSH_BUTTON_D, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    static uint32_t count = 0;
    switch (htim->Channel)
    {
        case HAL_TIM_ACTIVE_CHANNEL_1:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
        break;
        case HAL_TIM_ACTIVE_CHANNEL_2:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_2);
        break;
        case HAL_TIM_ACTIVE_CHANNEL_3:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_3);
        break;
        default:
        break;
    }
    //datasentflag = 1;
    //g_dma_done_flag = true;
    count++;
    datasentflag=1;
//
//  if (0 == (count % 2))
//  {
//        datasentflag=1;
//        g_dma_done_flag = true;
//  }
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
