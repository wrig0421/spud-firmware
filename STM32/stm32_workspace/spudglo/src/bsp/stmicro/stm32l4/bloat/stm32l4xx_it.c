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
#include "stm32l4xx_hal.h"
#include "config.h"
#include "board_init_common.h"

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
#include "uart_config_hal_specific.h"
#include "uart_config_hal.h"
#include "task_notify.h"
#include "rng_config_hal.h"

#if defined(ENABLE_STRIP_1)
	extern TaskHandle_t 		g_led_strip_1_ctrl_handle;
#endif

#if defined(ENABLE_STRIP_2)
	extern TaskHandle_t 		g_led_strip_2_ctrl_handle;
#endif

#if defined(ENABLE_STRIP_3)
	extern TaskHandle_t 		g_led_strip_3_ctrl_handle;
#endif

#if defined(ENABLE_LED_STRIP_SYNC)
	extern TaskHandle_t 		g_led_strip_sync_ctrl_handle;
#endif
extern DMA_HandleTypeDef 	g_hdma_tim1_ch1;
extern DMA_HandleTypeDef 	g_hdma_tim1_ch2;
extern DMA_HandleTypeDef 	g_hdma_tim1_ch3;
extern DMA_HandleTypeDef 	gh_dma_host_rx;
extern DMA_HandleTypeDef 	gh_dma_host_tx;
extern RNG_HandleTypeDef    g_rng_handle;
extern uint32_t g_random_number;

extern SemaphoreHandle_t 	g_dma_transfer_semaphore;
extern TaskHandle_t 		g_button_press_handle;
extern UART_HandleTypeDef 	g_uart_handle_config[NUM_UART_CONFIG_BUSES];

extern uint32_t 			g_button_press_timestamp[NUM_BUTTONS][NUM_TIMESTAMPS];
extern UART_HandleTypeDef 	gh_host_usart;

volatile uint32_t valuesss = configMAX_SYSCALL_INTERRUPT_PRIORITY;
volatile uint32_t d_passes = 0;

//bool gb_dma_cmplt_strip_1 = true;
//bool gb_dma_cmplt_strip_2 = true;
//bool gb_dma_cmplt_strip_3 = true;

#if defined(SysTick)
#	undef SysTick_Handler

	/* CMSIS SysTick interrupt handler prototype */
	extern void SysTick_Handler     (void);
	/* FreeRTOS tick timer interrupt handler prototype */
	extern void xPortSysTickHandler (void);
	/*
	  SysTick handler implementation that also clears overflow flag.
	*/
#	if (USE_CUSTOM_SYSTICK_HANDLER_IMPLEMENTATION == 0)
		void SysTick_Handler (void) {
		  /* Clear overflow flag */
		  SysTick->CTRL;

		  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
			/* Call tick handler */
			xPortSysTickHandler();
		  }
		}
#	endif
#endif


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


bool micro_in_isr(void)
{
	return SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk;
}


/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
#if defined(ENABLE_BUTTON)
    BaseType_t xHigherPriorityTaskWoken;
    // lookup button from IRQ
	button_e btn = button_config_irq_to_button(EXTI0_IRQn);
	// handle button IRQ
    HAL_GPIO_EXTI_IRQHandler(button_config_button_pin(btn));
    // update previous button timestamp from previous "current"
    g_button_press_timestamp[btn][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[btn][TIMESTAMP_CURRENT];
    // update current timestamp
    g_button_press_timestamp[btn][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    // disable the IRQ to prevent nested interrupts.
    HAL_NVIC_DisableIRQ(EXTI0_IRQn);
    // notify button press task
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
    // lookup button from IRQ
	button_e btn = button_config_irq_to_button(EXTI2_IRQn);
	// handle button IRQ
    HAL_GPIO_EXTI_IRQHandler(button_config_button_pin(btn));
    // update previous button timestamp from previous "current"
    g_button_press_timestamp[btn][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[btn][TIMESTAMP_CURRENT];
    // update current timestamp
    g_button_press_timestamp[btn][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    // disable the IRQ to prevent nested interrupts.
    HAL_NVIC_DisableIRQ(EXTI2_IRQn);
    // notify button press task
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
    // lookup button from IRQ
    button_e btn = button_config_irq_to_button(EXTI15_10_IRQn);
	// handle button IRQ
    HAL_GPIO_EXTI_IRQHandler(button_config_button_pin(btn));
    // update previous button timestamp from previous "current"
    g_button_press_timestamp[btn][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[btn][TIMESTAMP_CURRENT];
    // update current timestamp
    g_button_press_timestamp[btn][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    // disable the IRQ to prevent nested interrupts.
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    // notify button press task
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
    // lookup button from IRQ
    button_e btn = button_config_irq_to_button(EXTI9_5_IRQn);
	// handle button IRQ
    HAL_GPIO_EXTI_IRQHandler(button_config_button_pin(btn));
    // update previous button timestamp from previous "current"
    g_button_press_timestamp[btn][TIMESTAMP_PREVIOUS] = g_button_press_timestamp[btn][TIMESTAMP_CURRENT];
    // update current timestamp
    g_button_press_timestamp[btn][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    // disable the IRQ to prevent nested interrupts.
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
    // notify button press task
    xTaskNotifyFromISR(g_button_press_handle, btn, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
#endif
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
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


task_notification_value_format_t g_dma_transfer_notification_value;

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	TaskHandle_t *p_task_handle = NULL;
	g_dma_transfer_notification_value.value = 0;
//	g_dma_transfer_notification_value.stimulus_bits.dma_cmplt = true;

    switch (htim->Channel)
    {
        case HAL_TIM_ACTIVE_CHANNEL_1:
#          if defined(ENABLE_STRIP_1)
                // set task_handle to strip 1 task
                p_task_handle = &g_led_strip_1_ctrl_handle;
                // set flag indicating strip_1 is reason for dma cmplt
                g_dma_transfer_notification_value.entity_bits.strip_1 = true;
#         endif
        break;
        case HAL_TIM_ACTIVE_CHANNEL_2:
#         if defined(ENABLE_STRIP_2)
                // set task_handle to strip 2 task
                p_task_handle = &g_led_strip_2_ctrl_handle;
                // set flag indicating strip_2 is reason for dma cmplt
                g_dma_transfer_notification_value.entity_bits.strip_2 = true;
#         endif
        break;
        case HAL_TIM_ACTIVE_CHANNEL_3:
#         if defined(ENABLE_STRIP_3)
                // set task_handle to strip 3 task
                p_task_handle = &g_led_strip_3_ctrl_handle;
                // set flag indicating strip_3 is reason for dma cmplt
                g_dma_transfer_notification_value.entity_bits.strip_3 = true;
#         endif
        break;
        default:
            // how did we get here?  set task_handle to null and entity to false
//                task_handle = NULL;
            g_dma_transfer_notification_value.flat_entity = false;
        break;
    }
#   if defined(ENABLE_LED_STRIP_SYNC)
        // set task_handle to sync task
        p_task_handle =  &g_led_strip_sync_ctrl_handle;
        // set flag indicating sync task
        g_dma_transfer_notification_value.entity_bits.strip_sync = true;
#   endif

    switch (htim->Channel)
    {
        case HAL_TIM_ACTIVE_CHANNEL_1:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);

//            gb_dma_cmplt_strip_1 = true;
        break;
        case HAL_TIM_ACTIVE_CHANNEL_2:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_2);
//            gb_dma_cmplt_strip_2 = true;
        break;
        case HAL_TIM_ACTIVE_CHANNEL_3:
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_3);
//            gb_dma_cmplt_strip_3 = true;
        break;
        default:
        break;
    }
    g_dma_transfer_notification_value.stimulus_bits.dma_cmplt = true;

//    xTaskNotifyFromISR(*p_task_handle, task_notification_value.value,
//                       eSetValueWithOverwrite, &xHigherPriorityTaskWoken);

//
//	task_notification_value_format_t task_notification_value =
//	{
//		// set DMA CMPLT [common] in IRQ
//		.stimulus_bits.dma_cmplt = true
//	};
//    switch (htim->Channel)
//    {
//        case HAL_TIM_ACTIVE_CHANNEL_1:
//#		     if defined(ENABLE_STRIP_1)
//                // set task_handle to strip 1 task
//                p_task_handle = &g_led_strip_1_ctrl_handle;
//                // set flag indicating strip_1 is reason for dma cmplt
//                task_notification_value.entity_bits.strip_1 = true;
//#		    endif
//        break;
//        case HAL_TIM_ACTIVE_CHANNEL_2:
//#		    if defined(ENABLE_STRIP_2)
//                // set task_handle to strip 2 task
//                p_task_handle = &g_led_strip_2_ctrl_handle;
//                // set flag indicating strip_2 is reason for dma cmplt
//                task_notification_value.entity_bits.strip_2 = true;
//#		    endif
//        break;
//        case HAL_TIM_ACTIVE_CHANNEL_3:
//#		    if defined(ENABLE_STRIP_3)
//                // set task_handle to strip 3 task
//                p_task_handle = &g_led_strip_3_ctrl_handle;
//                // set flag indicating strip_3 is reason for dma cmplt
//                task_notification_value.entity_bits.strip_3 = true;
//#		    endif
//        break;
//        default:
//            // how did we get here?  set task_handle to null and entity to false
////				task_handle = NULL;
//            task_notification_value.flat_entity = false;
//        break;
//    }
//#   if defined(ENABLE_LED_STRIP_SYNC)
//        // set task_handle to sync task
//        p_task_handle =  &g_led_strip_sync_ctrl_handle;
//        // set flag indicating sync task
//        task_notification_value.entity_bits.strip_sync = true;
//#   endif
//
//    switch (htim->Channel)
//    {
//        case HAL_TIM_ACTIVE_CHANNEL_1:
//            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
////            gb_dma_cmplt_strip_1 = true;
//        break;
//        case HAL_TIM_ACTIVE_CHANNEL_2:
//            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_2);
////            gb_dma_cmplt_strip_2 = true;
//        break;
//        case HAL_TIM_ACTIVE_CHANNEL_3:
//            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_3);
////            gb_dma_cmplt_strip_3 = true;
//        break;
//        default:
//        break;
//    }
//    xTaskNotifyFromISR(*p_task_handle, task_notification_value.value,
//                       eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
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


/**
  * @brief This function handles DMA1 channel7 global interrupt.
  */
void DMA1_Channel7_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&g_hdma_tim1_ch3);
}


/**
  * @brief This function handles LPUART1 global interrupt.
  */
void LPUART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&g_uart_handle_config[UART_CONFIG_BUS_HOST]);
}


void vApplicationMallocFailedHook( void )
{
	while (1);
}


void DMA2_Channel6_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&gh_dma_host_tx);
}


/**
  * @brief This function handles DMA2 channel7 global interrupt.
  */
void DMA2_Channel7_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&gh_dma_host_rx);
}


void RNG_IRQHandler(void)
{
    HAL_RNG_IRQHandler(&g_rng_handle);
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
