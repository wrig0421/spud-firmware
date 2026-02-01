// SRW
#include <string.h>
#include "stm32l4xx_hal.h"
#include "pkt.h"
#include "uart_access.h"
#include "uart_config_hal_specific.h"
#include "uart_config_hal.h"
#include "free_rtos_convenience.h"

extern UART_HandleTypeDef g_uart_handle_config[NUM_UART_CONFIG_BUSES];
extern const uart_config_t g_uart_config[NUM_UART_CONFIG_BUSES];
extern const uart_access_id_e* g_uart_chip_bus_lookup[NUM_UART_CONFIG_BUSES];
extern uint16_t g_uart_num_chips_per_bus[NUM_UART_CONFIG_BUSES];
extern uint32_t g_free_queue_pkt_index;


extern uint8_t g_rx_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];
extern uint8_t g_tx_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];

//extern uint32_t g_rx_queue_buffer_index;
//extern uint32_t g_tx_queue_buffer_index;

DMA_HandleTypeDef gh_dma_host_rx;
DMA_HandleTypeDef gh_dma_host_tx;

uint8_t g_host_rx_buffer[100] = {0};


void uart_config_hal_setup(void)
{
	bool uart_config_hal_setup_skip = false;
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
    GPIO_InitTypeDef  GPIO_InitStruct;

    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    for (uart_config_bus_e bus = UART_CONFIG_BUS_FIRST; bus < NUM_UART_CONFIG_BUSES; bus++)
    {
    	if (g_uart_num_chips_per_bus[bus])
    	{
    		uart_config_hal_setup_skip = false;
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
    	    	case UART_CONFIG_BUS_HOST:

    	    	    __HAL_RCC_DMA2_CLK_ENABLE();
    	    	    // LPUART DMA RX setup below
    	    	    gh_dma_host_rx.Instance = DMA2_Channel7;
    	    	    gh_dma_host_rx.Init.Request = DMA_REQUEST_4;
    	    	    gh_dma_host_rx.Init.Direction = DMA_PERIPH_TO_MEMORY; // take from uart periph to memory
    	    	    gh_dma_host_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    	    	    gh_dma_host_rx.Init.MemInc = DMA_MINC_ENABLE;
    	    	    gh_dma_host_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    	    	    gh_dma_host_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    	    	    gh_dma_host_rx.Init.Mode = DMA_CIRCULAR;
    	    	    gh_dma_host_rx.Init.Priority = DMA_PRIORITY_LOW;
    	    	    // init LPUART RX DMA
    	    	    if (HAL_DMA_Init(&gh_dma_host_rx) != HAL_OK)
    	    	    {
    	    	    	while (1);
    	    	    }
    	    	    // link LPUART DMA RX
    	    	    __HAL_LINKDMA(&g_uart_handle_config[bus],
    	    	    		      hdmarx, gh_dma_host_rx);

    	    	    // LPUART DMA TX setup below
    	    	    gh_dma_host_tx.Instance = DMA2_Channel6;
    	    	    gh_dma_host_tx.Init.Request = DMA_REQUEST_4;
    	    	    gh_dma_host_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    	    	    gh_dma_host_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    	    	    gh_dma_host_tx.Init.MemInc = DMA_MINC_ENABLE;
    	    	    gh_dma_host_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    	    	    gh_dma_host_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    	    	    gh_dma_host_tx.Init.Mode = DMA_NORMAL;
    	    	    gh_dma_host_tx.Init.Priority = DMA_PRIORITY_LOW;
    	    	    if (HAL_DMA_Init(&gh_dma_host_tx) != HAL_OK)
    	    	    {
    	    	    	while (1);
    	    	    }

    	    	    // link LPUART DMA TX
    	    	    __HAL_LINKDMA(&g_uart_handle_config[bus],
    	    	    		      hdmatx, gh_dma_host_tx);

    	    	    /* DMA interrupt init */
    	    	    /* DMA2_Channel6_IRQn interrupt configuration */
    	    	    HAL_NVIC_SetPriority(DMA2_Channel6_IRQn, 0, 0);
    	    	    HAL_NVIC_EnableIRQ(DMA2_Channel6_IRQn);
    	    	    HAL_NVIC_ClearPendingIRQ(DMA2_Channel6_IRQn);
    	    	    /* DMA2_Channel7_IRQn interrupt configuration */
    	    	    HAL_NVIC_SetPriority(DMA2_Channel7_IRQn, 0, 0);
    	    	    HAL_NVIC_EnableIRQ(DMA2_Channel7_IRQn);
    	    	    HAL_NVIC_ClearPendingIRQ(DMA2_Channel7_IRQn);

    	    	    HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 0);
    	    	    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
		    	    HAL_NVIC_ClearPendingIRQ(LPUART1_IRQn);

    	    	    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
    	    	    PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_SYSCLK;
    	    	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    	    	     {
    	    	         while(1);
    	    	     }
    	    	    __HAL_RCC_LPUART1_CLK_ENABLE();

				break;
//    	    	case :
//    	    	    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
//    	    	    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
//    	    	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
//    	    	     {
//    	    	         while(1);
//    	    	       //Error_Handler();
//    	    	     }
//    	    	    __HAL_RCC_USART1_CLK_ENABLE();
//
//
//
//				break;
    	    	default:
    	    		uart_config_hal_setup_skip = true;
    	    	break;
    	    }
    	    if (!uart_config_hal_setup_skip)
    	    {
				if(HAL_UART_Init(&g_uart_handle_config[bus]) != HAL_OK)
				{
					while(1);//Error_Handler();
				}
				if (UART_CONFIG_BUS_HOST == bus)
				{
					memset(g_rx_queue_buffer, 0x90, PKT_SIZE_BYTES);
//					g_uart_handle_config[bus].RxState = HAL_UART_STATE_READY;
				}
    	    }
    	    else
    	    {
    	    	uart_config_hal_setup_skip = false;
    	    }
    	}
    }
}


uint8_t* uart_config_host_rx_buffer(void)
{
	return &g_host_rx_buffer[0];
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
