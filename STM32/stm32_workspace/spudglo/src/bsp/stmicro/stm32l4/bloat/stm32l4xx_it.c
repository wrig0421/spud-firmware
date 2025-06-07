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

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "stm32l4xx_it.h"
//#include "stm32l4xx_hal.h"
#include "config.h"
#include "board_init_common.h"
#include "board_common.h"
#include "board_specific.h"
#include "led_animate.h"
#include "led_ctrl_color.h"
#include "task_button_press.h"
#include "FreeRTOSConfig.h"
#include "gpio_config_hal_specific.h"
#include <stdbool.h>
#include "semaphore_access.h"
#include "button_config_hal_specific.h"
#include "button_access.h"

//extern osThreadId_t g_dma_transfer_handle;

extern DMA_HandleTypeDef g_hdma_tim1_ch1;
extern DMA_HandleTypeDef g_hdma_tim1_ch2;
extern DMA_HandleTypeDef g_hdma_tim1_ch3;
extern SemaphoreHandle_t g_dma_transfer_semaphore;
extern TaskHandle_t 	g_button_press_handle;

extern bool g_tasks_running;
//extern osThreadId_t g_button_press_handle;

extern uint32_t g_button_press_timestamp[NUM_BUTTONS][NUM_TIMESTAMPS];
extern UART_HandleTypeDef      gh_host_usart;



#if defined(SysTick)
#undef SysTick_Handler

/* CMSIS SysTick interrupt handler prototype */
extern void SysTick_Handler     (void);
/* FreeRTOS tick timer interrupt handler prototype */
extern void xPortSysTickHandler (void);
/*
  SysTick handler implementation that also clears overflow flag.
*/
#if (USE_CUSTOM_SYSTICK_HANDLER_IMPLEMENTATION == 0)
void SysTick_Handler (void) {
  /* Clear overflow flag */
  SysTick->CTRL;

  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
    /* Call tick handler */
    xPortSysTickHandler();
  }
}
#endif
#endif


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
            //board_init_red_led_on();
            HAL_Delay(100);
            //board_init_red_led_off();
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
            //board_init_red_led_on();
            HAL_Delay(100);
            //board_init_red_led_off();
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
            //board_init_red_led_on();
            HAL_Delay(100);
            //board_init_red_led_off();
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
            //board_init_red_led_on();
            HAL_Delay(100);
            //board_init_red_led_off();
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
            //board_init_red_led_on();
            HAL_Delay(100);
            //board_init_red_led_off();
        }
        HAL_Delay(3000);
    }
}


/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{

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
volatile uint32_t valuesss = configMAX_SYSCALL_INTERRUPT_PRIORITY;
volatile uint32_t d_passes = 0;


// FROM THE LAYOUT FILE....

// A = WKUP3 PC5
// B = WKUP2 PC13
// C = WKUP1 PA0
// D = WKUP4 PA2

// 	SPUDGLO BUSINESS CARD
// 		COLOR 		PC5
// 		ANIMATION 	PC13
// 		SPEED 		PA0
//		PAUSE 		PA2



/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
#if defined(ENABLE_BUTTON)
    BaseType_t xHigherPriorityTaskWoken;
	button_e btn = button_config_irq_to_button(EXTI0_IRQn);
    HAL_GPIO_EXTI_IRQHandler(button_config_button_pin(btn));
    g_button_press_timestamp[btn][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[btn][TIMESTAMP_CURRENT];
    g_button_press_timestamp[btn][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    HAL_NVIC_DisableIRQ(EXTI0_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, btn, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
#endif
}

/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
#if defined(ENABLE_BUTTON)
    BaseType_t xHigherPriorityTaskWoken;
	button_e btn = button_config_irq_to_button(EXTI2_IRQn);
    HAL_GPIO_EXTI_IRQHandler(button_config_button_pin(btn));
    g_button_press_timestamp[btn][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[btn][TIMESTAMP_CURRENT];
    g_button_press_timestamp[btn][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    HAL_NVIC_DisableIRQ(EXTI2_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, btn, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
#endif
}


/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
#if defined(ENABLE_BUTTON)
    BaseType_t xHigherPriorityTaskWoken;
    button_e btn = button_config_irq_to_button(EXTI15_10_IRQn);
    HAL_GPIO_EXTI_IRQHandler(button_config_button_pin(btn));
    g_button_press_timestamp[btn][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[btn][TIMESTAMP_CURRENT];
    g_button_press_timestamp[btn][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, btn, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
#endif
}


/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
#if defined(ENABLE_BUTTON)
    BaseType_t xHigherPriorityTaskWoken;
    button_e btn = button_config_irq_to_button(EXTI9_5_IRQn);
    HAL_GPIO_EXTI_IRQHandler(button_config_button_pin(btn));
    g_button_press_timestamp[btn][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[btn][TIMESTAMP_CURRENT];
    g_button_press_timestamp[btn][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
    xTaskNotifyFromISR(g_button_press_handle, btn, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
#endif
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

}


void HAL_DMA_CMPLT_CALLBACK(DMA_HandleTypeDef *hdma)
{
    while(1);
}


/**
  * @brief  DMA Transfer complete callback
  * @note   This function is executed when the transfer complete interrupt
  *         is generated
  * @retval None
  */
void TransferComplete_1(DMA_HandleTypeDef *DmaHandle)
{
  /* Turn LED3 on: Transfer correct */
  while(1);
}


/**
  * @brief  DMA Transfer complete callback
  * @note   This function is executed when the transfer complete interrupt
  *         is generated
  * @retval None
  */
void TransferComplete_2(DMA_HandleTypeDef *DmaHandle)
{
  /* Turn LED3 on: Transfer correct */
  while(1);
}

/**
  * @brief  DMA Transfer complete callback
  * @note   This function is executed when the transfer complete interrupt
  *         is generated
  * @retval None
  */
void TransferComplete_3(DMA_HandleTypeDef *DmaHandle)
{
  /* Turn LED3 on: Transfer correct */
  while(1);
}


bool gb_dma_cmplt_strip_1 = true;
bool gb_dma_cmplt_strip_2 = true;
bool gb_dma_cmplt_strip_3 = true;


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{

    switch (htim->Channel)
    {
        case HAL_TIM_ACTIVE_CHANNEL_1:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
            //free_rtos_delay_ms(1);
            gb_dma_cmplt_strip_1 = true;
        break;
        case HAL_TIM_ACTIVE_CHANNEL_2:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_2);
            //free_rtos_delay_ms(1);
            gb_dma_cmplt_strip_2 = true;
        break;
        case HAL_TIM_ACTIVE_CHANNEL_3:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_3);
            gb_dma_cmplt_strip_3 = true;
        break;
        default:
        break;
    }
//    semaphore_give_from_isr(SEMAPHORE_DMA_TRANSFER);
}


/**
  * @brief This function handles DMA1 channel2 global interrupt.
  */
void DMA1_Channel2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&g_hdma_tim1_ch1);
}

/**
  * @brief This function handles DMA1 channel3 global interrupt.
  */
void DMA1_Channel3_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&g_hdma_tim1_ch2);
}

///**
//  * @brief This function handles DMA1 channel5 global interrupt.
//  */
//void DMA1_Channel5_IRQHandler(void)
//{
//    //HAL_DMA_IRQHandler(&hdma_tim15_ch1_up_trig_com);
//}
//
///**
//  * @brief This function handles DMA1 channel6 global interrupt.
//  */
//void DMA1_Channel6_IRQHandler(void)
//{
//    //HAL_DMA_IRQHandler(&hdma_tim16_ch1_up);
//}

/**
  * @brief This function handles DMA1 channel7 global interrupt.
  */
void DMA1_Channel7_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&g_hdma_tim1_ch3);
}


void vApplicationMallocFailedHook( void )
{
	while (1);
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
