// SRW
#include <string.h>
#include "stm32l4xx_hal.h"
#include "pkt.h"
#include "uart_access.h"
#include "uart_config_hal_specific.h"
#include "uart_config_hal.h"

extern UART_HandleTypeDef g_uart_handle_config[NUM_UART_CONFIG_BUSES];
extern const uart_config_t g_uart_config[NUM_UART_CONFIG_BUSES];
extern const uart_access_id_e* g_uart_chip_bus_lookup[NUM_UART_CONFIG_BUSES];
extern uint16_t g_uart_num_chips_per_bus[NUM_UART_CONFIG_BUSES];
extern uint32_t g_free_queue_pkt_index;


extern uint8_t g_rx_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];
extern uint8_t g_tx_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];

extern uint32_t g_rx_queue_buffer_index;
extern uint32_t g_tx_queue_buffer_index;

//
//  /* LPUART1 DMA Init */
//  /* LPUART_RX Init */
//  hdma_lpuart_rx.Instance = DMA2_Channel7;
//  hdma_lpuart_rx.Init.Request = DMA_REQUEST_4;
//  hdma_lpuart_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
//  hdma_lpuart_rx.Init.PeriphInc = DMA_PINC_DISABLE;
//  hdma_lpuart_rx.Init.MemInc = DMA_MINC_ENABLE;
//  hdma_lpuart_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//  hdma_lpuart_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//  hdma_lpuart_rx.Init.Mode = DMA_NORMAL;
//  hdma_lpuart_rx.Init.Priority = DMA_PRIORITY_LOW;
//  if (HAL_DMA_Init(&hdma_lpuart_rx) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  __HAL_LINKDMA(huart,hdmarx,hdma_lpuart_rx);
//
//  /* LPUART_TX Init */
//  hdma_lpuart_tx.Instance = DMA2_Channel6;
//  hdma_lpuart_tx.Init.Request = DMA_REQUEST_4;
//  hdma_lpuart_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
//  hdma_lpuart_tx.Init.PeriphInc = DMA_PINC_DISABLE;
//  hdma_lpuart_tx.Init.MemInc = DMA_MINC_ENABLE;
//  hdma_lpuart_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//  hdma_lpuart_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//  hdma_lpuart_tx.Init.Mode = DMA_NORMAL;
//  hdma_lpuart_tx.Init.Priority = DMA_PRIORITY_LOW;
//  if (HAL_DMA_Init(&hdma_lpuart_tx) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  __HAL_LINKDMA(huart,hdmatx,hdma_lpuart_tx);
//
//  /* LPUART1 interrupt Init */
//  HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(LPUART1_IRQn);
///* USER CODE BEGIN LPUART1_MspInit 1 */
//
///* USER CODE END LPUART1_MspInit 1 */
//
//}
DMA_HandleTypeDef gh_dma_lpuart1_rx;
DMA_HandleTypeDef gh_dma_lpuart1_tx;


void uart_config_hal_setup(void)
{
	  __HAL_RCC_SYSCFG_CLK_ENABLE();
	  __HAL_RCC_PWR_CLK_ENABLE();
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
    	    	case UART_CONFIG_BUS_HOST:
    	    	    __HAL_RCC_DMA2_CLK_ENABLE();


    	    	    gh_dma_lpuart1_rx.Instance = DMA2_Channel7;
    	    	    gh_dma_lpuart1_rx.Init.Request = DMA_REQUEST_4;
    	    	    gh_dma_lpuart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    	    	    gh_dma_lpuart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    	    	    gh_dma_lpuart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    	    	    gh_dma_lpuart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    	    	    gh_dma_lpuart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    	    	    gh_dma_lpuart1_rx.Init.Mode = DMA_NORMAL;
    	    	    gh_dma_lpuart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    	    	    if (HAL_DMA_Init(&gh_dma_lpuart1_rx) != HAL_OK)
    	    	    {
    	    	    	//Error_Handler();
    	    	    }
    	    	    __HAL_LINKDMA(&g_uart_handle_config[bus],
    	    	    		      hdmarx, gh_dma_lpuart1_rx);


    	    	    /* LPUART_TX Init */
    	    	    gh_dma_lpuart1_tx.Instance = DMA2_Channel6;
    	    	    gh_dma_lpuart1_tx.Init.Request = DMA_REQUEST_4;
    	    	    gh_dma_lpuart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    	    	    gh_dma_lpuart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    	    	    gh_dma_lpuart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    	    	    gh_dma_lpuart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    	    	    gh_dma_lpuart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    	    	    gh_dma_lpuart1_tx.Init.Mode = DMA_NORMAL;
    	    	    gh_dma_lpuart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    	    	    if (HAL_DMA_Init(&gh_dma_lpuart1_tx) != HAL_OK)
    	    	    {
//    	    	      Error_Handler();
    	    	    }

    	    	    __HAL_LINKDMA(&g_uart_handle_config[bus],
    	    	    		      hdmatx, gh_dma_lpuart1_tx);

    	    	    HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 0);
    	    	    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
    	    	    /* DMA interrupt init */
    	    	    /* DMA2_Channel6_IRQn interrupt configuration */
    	    	    HAL_NVIC_SetPriority(DMA2_Channel6_IRQn, 0, 0);
    	    	    HAL_NVIC_EnableIRQ(DMA2_Channel6_IRQn);
    	    	    /* DMA2_Channel7_IRQn interrupt configuration */
    	    	    HAL_NVIC_SetPriority(DMA2_Channel7_IRQn, 0, 0);
    	    	    HAL_NVIC_EnableIRQ(DMA2_Channel7_IRQn);

    	    	    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
    	    	    PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_SYSCLK;
    	    	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    	    	     {
    	    	         while(1);
    	    	       //Error_Handler();
    	    	     }
    	    	    __HAL_RCC_LPUART1_CLK_ENABLE();
//    	    	    HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 0);
//    	    	    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
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
    	    	break;
    	    }

    	    //UART_ITConfig(USART1, UART_IT_TXE, ENABLE);
    	    //UART_ITConfig(USART1, UART_IT_RXNE, ENABLE);
//    	    if(HAL_UART_DeInit(&g_uart_handle_config[bus]) != HAL_OK)
//    	    {
//    	        while(1);//Error_Handler();
//    	    }
    	    if(HAL_UART_Init(&g_uart_handle_config[bus]) != HAL_OK)
    	    {
    	        while(1);//Error_Handler();
    	    }
//    	    HAL_NVIC_SetPriority(g_uart_config[bus].irqn, 0, 0);
//    	    HAL_NVIC_EnableIRQ(g_uart_config[bus].irqn);
//    	    HAL_NVIC_ClearPendingIRQ(g_uart_config[bus].irqn);
    	    if (UART_CONFIG_BUS_HOST == bus)
    	    {
    	        memset(g_rx_queue_buffer, 0x90, PKT_SIZE_BYTES);

    	        while (1)
    	        {
//    	        HAL_UART_Transmit(&g_uart_handle_config[bus], g_rx_queue_buffer, PKT_SIZE_BYTES, 5000);
//					HAL_UART_Transmit_DMA(&g_uart_handle_config[bus],
//										 g_rx_queue_buffer,
//										 10);

					HAL_UART_Receive_DMA(&g_uart_handle_config[bus],
										 g_rx_queue_buffer + g_rx_queue_buffer_index++ * PKT_SIZE_BYTES,
										 PKT_SIZE_BYTES);
//    	    		HAL_Delay(500);
    	        }

//    	    	HAL_UART_Receive_DMA(&g_uart_handle_config[bus],
//									 g_rx_queue_buffer + g_rx_queue_buffer_index++ * PKT_SIZE_BYTES,
//									 PKT_SIZE_BYTES);
    	    }
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
