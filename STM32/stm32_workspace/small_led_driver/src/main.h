/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

void Error_Handler(void);

#define WKUP2_Pin GPIO_PIN_13
#define WKUP2_GPIO_Port GPIOC
#define GPIO_2_Pin GPIO_PIN_0
#define GPIO_2_GPIO_Port GPIOC
#define GPIO_3_Pin GPIO_PIN_1
#define GPIO_3_GPIO_Port GPIOC
#define LED_OUT_1_Pin GPIO_PIN_2
#define LED_OUT_1_GPIO_Port GPIOC
#define LED_OUT_2_Pin GPIO_PIN_3
#define LED_OUT_2_GPIO_Port GPIOC
#define WKUP1_Pin GPIO_PIN_0
#define WKUP1_GPIO_Port GPIOA
#define WKUP4_Pin GPIO_PIN_2
#define WKUP4_GPIO_Port GPIOA
#define TIM16_CH1_Pin GPIO_PIN_6
#define TIM16_CH1_GPIO_Port GPIOA
#define TIM15_CH1_Pin GPIO_PIN_14
#define TIM15_CH1_GPIO_Port GPIOB
#define WKUP3_Pin GPIO_PIN_5
#define WKUP3_GPIO_Port GPIOC
#define TIM1_CH1_Pin GPIO_PIN_8
#define TIM1_CH1_GPIO_Port GPIOA
#define GPIO_0_Pin GPIO_PIN_8
#define GPIO_0_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
