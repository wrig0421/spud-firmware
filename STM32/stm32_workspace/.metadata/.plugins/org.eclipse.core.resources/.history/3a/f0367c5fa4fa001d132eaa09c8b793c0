// SRW

#include "stm32l4xx_hal.h"
#include "board_specific.h"
#include "uart_access.h"


UART_HandleTypeDef      gh_host_usart =
{
    .Instance = LPUART1,
    .Init.BaudRate = 9600,
    .Init.WordLength = UART_WORDLENGTH_8B,
    .Init.StopBits = UART_STOPBITS_1,
    .Init.Parity = UART_PARITY_NONE,
    .Init.Mode           = UART_MODE_TX_RX,
    .Init.HwFlowCtl      = UART_HWCONTROL_NONE,
    .Init.OverSampling = UART_OVERSAMPLING_16,
    .Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE,
    .AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
    .AdvancedInit.OverrunDisable = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT|UART_ADVFEATURE_DMADISABLEONERROR_INIT,
    .AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR
};


void uart_access_setup(void)
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

    if(HAL_UART_DeInit(&gh_host_usart) != HAL_OK)
    {
        //Error_Handler();
    }
    if(HAL_UART_Init(&gh_host_usart) != HAL_OK)
    {
        while(1);
        //Error_Handler();
    }
}


HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

void uart_access_rx(void)
{
    //HAL_UART_Receive_DMA(&gh_host_usart, )
}


void uart_access_tx(void)
{

}




