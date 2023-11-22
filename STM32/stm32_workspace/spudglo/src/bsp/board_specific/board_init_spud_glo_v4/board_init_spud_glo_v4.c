// SRW

#include "stm32l4xx_hal.h"
#include "board_common.h"
#include "board_specific.h"


#if defined(BOARD_SPUD_GLO_V4)


#if defined(BOARD_SPUD_GLO_V4P2)
static void board_init_peripheral_setup(void)
{
    uart_access_setup();
    spi_access_setup();
}
#endif


void board_init_specific(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = PIN_INT_LVL_EN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_B, PIN_INT_LVL_EN, GPIO_PIN_SET);

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

    GPIO_InitStruct.Pin = PIN_DISP_RST | PIN_DISP_DC |PIN_DISP_BACKLIGHT;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);

    // setup XR_RX and XR_TX
    GPIO_InitStruct.Pin = PIN_XR_GPIO | PIN_VBUS_PRESENT;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_BLUE_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_B, PIN_BLUE_LED, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = PIN_ORANGE_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_B, PIN_ORANGE_LED, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = PIN_GREEN_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_B, PIN_GREEN_LED, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = PIN_RED_LED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_B, PIN_RED_LED, GPIO_PIN_RESET);

#if defined(BOARD_SPUD_GLO_V4P2)
    board_init_peripheral_setup();
#endif
}


void board_init_specific_power_cycle_level_shifter(void)
{
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_SET);
}


#endif

