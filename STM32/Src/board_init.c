/*
 * board_init.c
 *
 *  Created on: Mar 31, 2021
 *      Author: spud
 */
#if 0
#include "board.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include "board_init.h"



void board_init_green_led_on(void)
{
	HAL_GPIO_WritePin(PORTB, GRN_LED, IOPORT_PIN_LEVEL_HIGH);
}


void board_init_green_led_off(void)
{
	HAL_GPIO_WritePin(PORTB, GRN_LED, IOPORT_PIN_LEVEL_LOW);
}


void board_init_red_led_on(void)
{
	HAL_GPIO_WritePin(PORTB, RED_LED, IOPORT_PIN_LEVEL_HIGH);
}


void board_init_red_led_off(void)
{
	HAL_GPIO_WritePin(PORTB, RED_LED, IOPORT_PIN_LEVEL_LOW);
}


bool board_init_int1_is_set(void)
{
	if (IOPORT_PIN_LEVEL_HIGH == HAL_GPIO_ReadPin(PORTC, INT1)) return true;
	else return false;
}


bool board_init_int2_is_set(void)
{
	if (IOPORT_PIN_LEVEL_HIGH == HAL_GPIO_ReadPin(PORTA, INT2)) return true;
	else return false;
}


bool board_init_int3_is_set(void)
{
	if (IOPORT_PIN_LEVEL_HIGH == HAL_GPIO_ReadPin(PORTA, INT3)) return true;
	else return false;
}


void board_init_lvl_shifter_enable(void)
{
	HAL_GPIO_WritePin(PORTA, LVL_SHIFTER_EN, IOPORT_PIN_LEVEL_HIGH);
}



#endif
