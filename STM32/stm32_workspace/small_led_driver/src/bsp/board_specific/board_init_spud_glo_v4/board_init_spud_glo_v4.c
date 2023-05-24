// SRW

#include "stm32l4xx_hal.h"
#include "board_common.h"
#include "board_specific.h"


#if defined(BOARD_SPUD_GLO_V4)

//USART_HandleTypeDef gh_host_usart;
//SPI_HandleTypeDef   gh_disp_spi;

//void HAL_UART_MspInit(UART_HandleTypeDef* huart)
//{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
//  if(huart->Instance==USART1)
//  {
//  /* USER CODE BEGIN USART1_MspInit 0 */
//
//  /* USER CODE END USART1_MspInit 0 */
//
//  /** Initializes the peripherals clock
//  */
//    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
//    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
//    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
//    {
//      Error_Handler();
//    }
//
//    /* Peripheral clock enable */
//    __HAL_RCC_USART1_CLK_ENABLE();
//
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    /**USART1 GPIO Configuration
//    PB6     ------> USART1_TX
//    PB7     ------> USART1_RX
//    */
//    GPIO_InitStruct.Pin = PIN_XR_RX | PIN_XR_TX;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//    HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
//    HAL_NVIC_EnableIRQ(USART1_IRQn);
////
////    GPIO_InitStruct.Pin = PIN_XR_TX;
////    GPIO_InitStruct.Mode = GPIO_MODE_INPUT | MODE_AF;
////    GPIO_InitStruct.Pull = GPIO_NOPULL;
////    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
////    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
////    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//  /* USER CODE BEGIN USART1_MspInit 1 */
//
//  /* USER CODE END USART1_MspInit 1 */
//  }
//
//}

static void board_init_usart_setup(void)
{
    //__HAL_RCC_USART1_CLK_ENABLE();
//    GPIO_InitTypeDef  GPIO_InitStruct;

//    GPIO_InitStruct.Pin       = PIN_XR_TX; // L431 transmit pin
//    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull      = GPIO_NOPULL;
//    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
//
//    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);
//
//    GPIO_InitStruct.Pin = PIN_XR_RX;
//    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
//    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);

}


static void board_init_spi_setup(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    GPIO_InitStruct.Pin         = PIN_SPI1_SCK | PIN_SPI1_CIPO | PIN_SPI1_COPI;
    GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull        = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate   = GPIO_AF5_SPI1;
    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
}


static void board_init_peripheral_setup(void)
{
    board_init_usart_setup();
    board_init_spi_setup();
}

void board_init_specific(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
    PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_SYSCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        while(1);
      //Error_Handler();
    }

    /* Peripheral clock enable */
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
    //HAL_GPIO_WritePin(GPIOB, PIN_XR_TX, GPIO_PIN_RESET);

//    GPIO_InitStruct.Pin = PIN_DISP_BACKLIGHT|PIN_DISP_DC|PIN_DISP_RST;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
//
//    // spi setup (port A)
//    // PIN_SPI1_SCK, PIN_SPI1_CIPO, PIN_SPI1_COPI
//    // PIN_SPI1_NSS
//
//    GPIO_InitStruct.Pin = PIN_INT_LVL_EN;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);
//    HAL_GPIO_WritePin(GPIOB, PIN_INT_LVL_EN, GPIO_PIN_SET);
//    // setup XR_RX and XR_TX
//
//    GPIO_InitStruct.Pin = PIN_XR_GPIO | PIN_VBUS_PRESENT;
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(PIN_PORT_B, &GPIO_InitStruct);
//
//    GPIO_InitStruct.Pin = PIN_LVL_DIR;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
//
//    GPIO_InitStruct.Pin = PIN_LVL_EN;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(PIN_PORT_C, &GPIO_InitStruct);
//
//    board_init_peripheral_setup();
}


void board_init_specific_power_cycle_level_shifter(void)
{
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(PIN_PORT_C, PIN_LVL_EN, GPIO_PIN_SET);
}


#endif
