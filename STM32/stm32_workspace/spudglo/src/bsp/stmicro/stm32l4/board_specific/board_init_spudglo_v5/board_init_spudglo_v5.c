// SRW

#include "stm32l4xx_hal.h"
#include "board_common.h"
#include "board_specific.h"
#include "spi_config_hal.h"
#include "uart_config_hal.h"


#if defined(BOARD_SPUDGLO_V5)


static void board_init_peripheral_setup(void)
{
	uart_config_hal_setup();
	spi_config_hal_setup();
}


void board_init_specific(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = PIN_LVL_EN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = PIN_LVL_DIR;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_DIR, GPIO_PIN_SET);

    // setup XR_RX and XR_TX
    GPIO_InitStruct.Pin = PIN_VBUS_PRESENT;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_GREEN_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_GREEN_LED, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = PIN_RED_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_RED_LED, GPIO_PIN_RESET);

    board_init_peripheral_setup();
}


void board_init_specific_power_cycle_level_shifter(void)
{
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_SET);
}


void board_init_specific_esp8266_power_enable(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_ESP8266_EN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_A, PIN_ESP8266_EN, GPIO_PIN_SET);
}


void board_init_specific_esp8266_power_disable(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_ESP8266_EN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_A, PIN_ESP8266_EN, GPIO_PIN_RESET);
}


void board_init_specific_esp8266_reset_assert(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_ESP8266_EN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_A, PIN_ESP8266_EN, GPIO_PIN_RESET);
}


void board_init_specific_esp8266_reset_deassert(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_ESP8266_EN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_A, PIN_ESP8266_RST, GPIO_PIN_SET);
}


#endif

