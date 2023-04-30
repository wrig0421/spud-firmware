// SRW

#include "stm32l4xx_hal.h"
#include "board_common.h"
#include "board_specific.h"


#if defined(BOARD_SPUD_GLO_V4)


#if defined(BOARD_SPUD_GLO_V4P2)
static void board_init_usart_setup(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
    PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_LSE;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        while(1);
      //Error_Handler();
    }
    __HAL_RCC_LPUART1_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStruct.Pin       = PIN_XR_RX | PIN_XR_TX; //
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF8_LPUART1;

    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
    serial_com_init_usart();
}


static void board_init_spi_setup(void)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

//    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SPI1;
//    PeriphClkInit.Lpuart1ClockSelection = RCC_SPI1CLKSOURCE_HSI;
//
//    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
//    {
//        while(1);
//      //Error_Handler();
//    }
    //__HAL_RCC_LPUART1_CLK_ENABLE();
    GPIO_InitTypeDef  GPIO_InitStruct;

    GPIO_InitStruct.Pin         = PIN_SPI1_SCK | PIN_SPI1_CIPO | PIN_SPI1_COPI;
    GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull        = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate   = GPIO_AF5_SPI1;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);

    serial_com_init_spi();
}


static void board_init_peripheral_setup(void)
{
    board_init_usart_setup();
    board_init_spi_setup();
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

    GPIO_InitStruct.Pin = PIN_LVL_DIR;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);

#if defined(BOARD_SPUD_GLO_V4P2)

    GPIO_InitStruct.Pin = PIN_DISP_RST | PIN_DISP_DC |PIN_DISP_BACKLIGHT;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = PIN_INT_LVL_EN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PIN_PORT_B, PIN_INT_LVL_EN, GPIO_PIN_SET);
    // setup XR_RX and XR_TX

    GPIO_InitStruct.Pin = PIN_XR_GPIO | PIN_VBUS_PRESENT;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);

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

    board_init_peripheral_setup();
#else

#endif
}


void board_init_specific_power_cycle_level_shifter(void)
{
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_SET);
}


#endif

