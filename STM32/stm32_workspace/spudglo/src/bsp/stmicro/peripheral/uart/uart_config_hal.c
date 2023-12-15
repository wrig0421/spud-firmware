// SRW

#include "stm32l4xx_hal.h"
#include "uart_config_hal_specific.h"
#include "uart_config_hal.h"

extern const uart_config_t g_uart_config[NUM_UART_CONFIG_BUSES];
extern UART_HandleTypeDef g_uart_handle_config[NUM_UART_CONFIG_BUSES];


void uart_config_hal_setup(void)
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

    GPIO_InitStruct.Pin       = g_uart_config[UART_CONFIG_BUS_HOST].pin.rx;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = g_uart_config[UART_CONFIG_BUS_HOST].pin.rx_alt_func;
    HAL_GPIO_Init(g_uart_config[UART_CONFIG_BUS_HOST].pin.rx_port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = g_uart_config[UART_CONFIG_BUS_HOST].pin.tx;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = g_uart_config[UART_CONFIG_BUS_HOST].pin.tx_alt_func;
    HAL_GPIO_Init(g_uart_config[UART_CONFIG_BUS_HOST].pin.tx_port, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(g_uart_config[UART_CONFIG_BUS_HOST].irqn, 0, 1);
    HAL_NVIC_EnableIRQ(g_uart_config[UART_CONFIG_BUS_HOST].irqn);

    if(HAL_UART_DeInit(&g_uart_handle_config[UART_CONFIG_BUS_HOST]) != HAL_OK)
    {
        //Error_Handler();
    }
    if(HAL_UART_Init(&g_uart_handle_config[UART_CONFIG_BUS_HOST]) != HAL_OK)
    {
        //Error_Handler();
    }
}


uart_handle_t uart_config_host_handle(void)
{
	return &g_uart_handle_config[UART_CONFIG_BUS_HOST];
}

