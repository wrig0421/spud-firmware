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
#include "task_mn_wild.h"
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
extern osThreadId_t g_mn_wild_ctrl_handle;

extern uint32_t g_button_press_timestamp[NUM_PUSH_BUTTONS][NUM_TIMESTAMPS];


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




/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_1);
    if (TASK_MN_WILD_STATE_ACTIVE == task_mn_wild_state())
    {
        task_mn_wild_enter_idle();
    }
    else
    {
        xTaskNotifyFromISR(g_mn_wild_ctrl_handle, PUSH_BUTTON_B, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
    }
}

uint32_t g_dbg_b_interrupt_count = 0;
/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_4);
}


/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_2);
    if (TASK_MN_WILD_STATE_ACTIVE == task_mn_wild_state())
    {
        task_mn_wild_enter_idle();
    }
    else
    {
        xTaskNotifyFromISR(g_mn_wild_ctrl_handle, PUSH_BUTTON_A, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
    }
}


/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(PIN_WKUP_3);
}


void HAL_DMA_CMPLT_CALLBACK(DMA_HandleTypeDef *hdma)
{
    while(1);
}


bool g_tim_pwm_transfer_cmplt = false;

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
    //g_tim_pwm_transfer_cmplt = true;
    if (3 == count++)
    {
        g_tim_pwm_transfer_cmplt = true;
        count = 0;
    }
    //xTaskNotifyFromISR(g_dma_transfer_handle, 0xFF, eSetValueWithOverwrite, &xHigherPriorityTaskWokenTim);
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