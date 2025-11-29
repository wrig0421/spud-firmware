// SRW
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "task.h"
#include "stm32l4xx_hal.h"
#include "uart_access_hal.h"

#include "task_led_ctrl.h"
#include "esp8266.h"
#include "pkt.h"
#include <string.h>
#include <stdbool.h>

TickType_t g_receive_tick_time;
uint8_t *gh_uart_rx_buffer;
uint16_t g_uart_rx_buffer_index = 0;
extern UART_HandleTypeDef g_uart_handle_config[NUM_UART_CONFIG_BUSES];

extern uint8_t g_rx_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];
extern uint8_t g_tx_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];

extern uint32_t g_rx_queue_buffer_index;
extern uint32_t g_tx_queue_buffer_index;

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
    if (huart == &g_uart_handle_config[UART_CONFIG_BUS_HOST])
    {
		HAL_UART_Receive_DMA(uart_config_host_handle(),
							g_rx_queue_buffer + (g_rx_queue_buffer_index++ * PKT_SIZE_BYTES),
							PKT_SIZE_BYTES);
		xTaskNotifyFromISR(g_task_uart_rx_handle, 0, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
    }
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

