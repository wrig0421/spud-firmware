// SRW
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "task.h"
#include "stm32l4xx_hal.h"
#include "uart_access_hal.h"
#include "stm32l4xx_it.h"
#include "task_led_ctrl.h"
#include "esp8266.h"
#include "pkt.h"
#include <string.h>
#include <stdbool.h>

#define UART_PKT_BUFFER_SIZE_BYTES FREE_QUEUE_DEPTH * PKT_SIZE_BYTES

TickType_t g_receive_tick_time;
uint8_t *gh_uart_rx_buffer;
uint16_t g_uart_rx_buffer_index = 0;
extern UART_HandleTypeDef g_uart_handle_config[NUM_UART_CONFIG_BUSES];

uint8_t g_rx_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];
uint8_t g_tx_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];

uint32_t g_rx_queue_buffer_index = 0;
uint32_t g_tx_queue_buffer_index = 0;

extern TaskHandle_t 	g_task_uart_rx_handle;

void USART1_IRQHandler(void)
{
#if defined (BOARD_SPUDGLO_V5)
	HAL_UART_IRQHandler(uart_config_esp8266_handle());
#endif
}


bool g_tx_complete = false;
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	g_tx_complete = true;

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    BaseType_t xHigherPriorityTaskWoken;
    bool isr_active = micro_in_isr() ? true : false;

    if (huart == &g_uart_handle_config[UART_CONFIG_BUS_HOST])
    {
    	// UART DMA pkt received from hose.  Enqueue a response back.
    	// enqueue the received pkt to the host queue
    	if (isr_active)
    	{
			xQueueSendToBackFromISR(pkt_queue_handle_host_rx(),
									uart_config_host_rx_buffer(),
									&xHigherPriorityTaskWoken);
    	}
    	else
    	{
    		xQueueSendToBack(pkt_queue_handle_host_rx(),
    						uart_config_host_rx_buffer(),
							portMAX_DELAY);
    	}
    	// Restart the UART DMA here for the next pkt! The buffer here will just wrap.
		HAL_UART_Receive_DMA(uart_config_host_handle(),
							g_rx_queue_buffer + ((g_rx_queue_buffer_index++ * sizeof(pkt_t)) % UART_PKT_BUFFER_SIZE_BYTES),
							PKT_SIZE_BYTES);
		// the pkt_queue is sufficient notification.
//		// notify the host rx task that pkt received...
//		xTaskNotifyFromISR(g_task_uart_rx_handle, TASK_NOTIFICATION_HOST_UART_PKT_RECEIVED,
//						   eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
    }
}


void uart_access_hal_host_rx(void)
{
	// the receive should be through DMA!
	// fill the memory that is shared with the pkt queue area.
	HAL_UART_Receive_DMA(uart_config_host_handle(),
					     uart_config_host_rx_buffer(), PKT_SIZE_BYTES);//PKT_SIZE_BYTES);
}


void uart_access_hal_host_tx(void)
{

}


uint16_t sizeof_array = 0;
void uart_access_hal_write_and_read_block(uart_handle_t ph_uart, uint8_t* write_data, uint16_t write_len, uint8_t* read_buf, uint16_t read_len)
{
	//HAL_
}


void uart_access_hal_write_byte(uart_handle_t ph_uart, uint8_t data)
{
	if (HAL_OK != HAL_UART_Transmit(ph_uart, &data, 1, 10000))
	{
		while (1);
	}
}


void uart_access_hal_write_block(uart_handle_t ph_uart, uint8_t* data, uint16_t len)
{
    if (HAL_OK != HAL_UART_Transmit_IT(ph_uart, data, len))
	{
		while (1);
	}
}


void uart_access_hal_read_byte(uart_handle_t ph_uart, uint8_t* buf)
{
	if (HAL_OK != HAL_UART_Receive_IT(ph_uart, buf, 1))
	{
		while (1);
	}
}


void uart_access_hal_read_block(uart_handle_t ph_uart, uint8_t* buf, uint16_t len)
{
	if (HAL_OK != HAL_UART_Receive_IT(ph_uart, buf, len))
	{
		while (1);
	}
}

