// SRW

#include "stm32l4xx_hal.h"
#include "uart_access.h"
#include "uart_config_hal_specific.h"
#include "uart_config_hal.h"

extern UART_HandleTypeDef g_uart_handle_config[NUM_UART_CONFIG_BUSES];
extern const uart_config_t g_uart_config[NUM_UART_CONFIG_BUSES];
extern const uart_access_id_e* g_uart_chip_bus_lookup[NUM_UART_CONFIG_BUSES];
extern uint16_t g_uart_num_chips_per_bus[NUM_UART_CONFIG_BUSES];


void uart_config_hal_setup(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    for (uart_config_bus_e bus = UART_CONFIG_BUS_FIRST; bus < NUM_UART_CONFIG_BUSES; bus++)
    {
    	if (g_uart_num_chips_per_bus[bus])
    	{
    	    GPIO_InitStruct.Pin       = g_uart_config[bus].pin.rx;
    	    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    	    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    	    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    	    GPIO_InitStruct.Alternate = g_uart_config[bus].pin.rx_alt_func;
    	    HAL_GPIO_Init(g_uart_config[bus].pin.rx_port, &GPIO_InitStruct);

    	    GPIO_InitStruct.Pin       = g_uart_config[bus].pin.tx;
    	    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    	    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    	    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    	    GPIO_InitStruct.Alternate = g_uart_config[bus].pin.tx_alt_func;
    	    HAL_GPIO_Init(g_uart_config[bus].pin.tx_port, &GPIO_InitStruct);

    	    switch (bus)
    	    {
    	    	case UART_ACCESS_ID_HOST:
    	    	    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
    	    	    PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_LSE;
    	    	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    	    	     {
    	    	         while(1);
    	    	       //Error_Handler();
    	    	     }
    	    	    __HAL_RCC_LPUART1_CLK_ENABLE();
    	    	break;
    	    	case UART_ACCESS_ID_ESP8266:
    	    	    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    	    	    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    	    	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    	    	     {
    	    	         while(1);
    	    	       //Error_Handler();
    	    	     }
    	    	    __HAL_RCC_USART1_CLK_ENABLE();
				break;
    	    	default:
    	    	break;
    	    }
    	    //UART_ITConfig(USART1, UART_IT_TXE, ENABLE);
    	    //UART_ITConfig(USART1, UART_IT_RXNE, ENABLE);
    	    if(HAL_UART_DeInit(&g_uart_handle_config[bus]) != HAL_OK)
    	    {
    	        while(1);//Error_Handler();
    	    }
    	    if(HAL_UART_Init(&g_uart_handle_config[bus]) != HAL_OK)
    	    {
    	        while(1);//Error_Handler();
    	    }
    	    HAL_NVIC_SetPriority(g_uart_config[bus].irqn, 0, 1);
    	    HAL_NVIC_EnableIRQ(g_uart_config[bus].irqn);
    	    HAL_NVIC_ClearPendingIRQ(g_uart_config[bus].irqn);
    	}
    }

}


uart_handle_t uart_config_host_handle(void)
{
	return &g_uart_handle_config[UART_CONFIG_BUS_HOST];
}


#if defined(BOARD_SPUDGLO_V5)
uart_handle_t uart_config_esp8266_handle(void)
{
	return &g_uart_handle_config[UART_CONFIG_BUS_ESP8266];
}
#endif
