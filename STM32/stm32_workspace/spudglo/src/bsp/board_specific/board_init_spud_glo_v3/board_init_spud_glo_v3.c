// SRW

#include "stm32l4xx_hal.h"
#include "board_common.h"
#include "board_specific.h"

#if defined(BOARD_SPUD_GLO_V3)

void board_init_specific(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = PIN_GPIO0|PIN_GPIO1|PIN_GPIO3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_ANALOG_IN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_SPI3_NSS;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_LVL_DIR;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
}


void board_init_specific_power_cycle_level_shifter(void)
{
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_SET);
}


void board_init_red_led_on(void)
{
    HAL_GPIO_WritePin(PIN_PORT_C, RED_LED, GPIO_PIN_SET);
}


void board_init_red_led_off(void)
{
    HAL_GPIO_WritePin(PIN_PORT_C, RED_LED, GPIO_PIN_RESET);
}


void board_init_green_led_on(void)
{
    HAL_GPIO_WritePin(PIN_PORT_C, GREEN_LED, GPIO_PIN_SET);
}


void board_init_green_led_off(void)
{
    HAL_GPIO_WritePin(PIN_PORT_C, GREEN_LED, GPIO_PIN_RESET);
}


#endif