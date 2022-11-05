// SRW

#include "stm32l4xx_hal.h"
#include "board_specific.h"


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

    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_DIR, GPIO_PIN_SET);
}
