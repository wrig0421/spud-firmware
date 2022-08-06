/*
 * board_init_common.h
 *
 *  Created on: Aug 6, 2022
 *      Author: splat
 */

#ifndef SRC_BSP_BOARD_INIT_COMMON_H_
#define SRC_BSP_BOARD_INIT_COMMON_H_

// PORT A pins
#define PIN_PORT_A              GPIOA
#define PIN_WKUP_1              GPIO_PIN_0

#define PIN_WKUP_4              GPIO_PIN_2

#define PIN_TIM16_CH1           GPIO_PIN_6

#define PIN_TIM1_CH1            GPIO_PIN_8
#define PIN_TIM1_CH2            GPIO_PIN_9
#define PIN_TIM1_CH3            GPIO_PIN_10

// PORT B pins
#define PIN_PORT_B              GPIOB

#define PIN_TIM15_CH1           GPIO_PIN_14


// PORT C pins
#define PIN_PORT_C              GPIOC
#define PIN_LED_OUT_1           GPIO_PIN_2
#define PIN_LED_OUT_2           GPIO_PIN_3

#define PIN_WKUP_3              GPIO_PIN_5

#define PIN_LVL_EN              GPIO_PIN_7

#define PIN_WKUP_2              GPIO_PIN_13


#endif /* SRC_BSP_BOARD_INIT_COMMON_H_ */
