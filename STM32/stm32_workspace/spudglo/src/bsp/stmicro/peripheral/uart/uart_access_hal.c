// SRW

#include "stm32l4xx_hal.h"
#include "uart_access_hal.h"
#include "cmsis_os.h"
#include <string.h>

uint8_t g_counter = 0;


bool gb_tx_complete = false;
bool gb_rx_complete = false;


char g_general_rx_buffer[500] = {0};
uint16_t g_rx_buffer_index = 0;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	gb_tx_complete = true;
	gb_rx_complete = false;
}


TickType_t g_receive_tick_time;


bool uart_access_hal_rx_done(TickType_t cur_time)
{
	if ((cur_time - uart_access_hal_last_rx_tick_time()) < 1000) return false;
	return true;
}


TickType_t uart_access_hal_last_rx_tick_time(void)
{
	return g_receive_tick_time;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	g_receive_tick_time = xTaskGetTickCount();
	if (HAL_OK != HAL_UART_Receive_IT(huart, (uint8_t *)(g_general_rx_buffer + (++g_rx_buffer_index)), 1))
	{
		while (1);
	}
}


void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(uart_config_esp8266_handle());
}



void uart_access_hal_write_and_read_block(uart_handle_t ph_uart, uint8_t* write_data, uint16_t write_len, uint8_t* read_buf, uint16_t read_len)
{
	static bool first_pass = true;
	g_receive_tick_time = xTaskGetTickCount();
	// clear UART with 0 timeout call below.
	HAL_UART_Receive(ph_uart, g_general_rx_buffer, 1000, 0);

	g_rx_buffer_index = 0;
	memset(g_general_rx_buffer, 0, sizeof(g_general_rx_buffer));
	// start listening for receive before TX
	if (first_pass)
	{
		first_pass = false;
		if (HAL_OK != HAL_UART_Receive_IT(ph_uart, (uint8_t *)g_general_rx_buffer, 1))
		{
			while (1);
		}
	}
	// tx
	if (HAL_OK != HAL_UART_Transmit_IT(ph_uart, write_data, write_len))
	{
		while (1);
	}
}


void uart_access_hal_write_byte(uart_handle_t ph_uart, uint8_t data)
{
	if (HAL_OK != HAL_UART_Transmit(ph_uart, &data, 1, 10000))
	{
		while (1);
	}
}

uint8_t g_dummy_buf[10] = {0};


void uart_access_hal_write_block(uart_handle_t ph_uart, uint8_t* data, uint16_t len)
{
	//HAL_UART_Receive(ph_uart, g_dummy_buf, 10, 0);
    //__HAL_UART_ENABLE_IT(uart_config_esp8266_handle(), UART_IT_TC);
    //__HAL_UART_ENABLE_IT(uart_config_esp8266_handle(), UART_IT_RXNE);
    if (HAL_OK != HAL_UART_Transmit_IT(ph_uart, data, len))
	{
		while (1);
	}
}


void uart_access_hal_read_byte(uart_handle_t ph_uart, uint8_t* buf)
{
	if (HAL_OK != HAL_UART_Receive(ph_uart, buf, 1, 10000))
	{
		while (1);
	}
}


void uart_access_hal_read_block(uart_handle_t ph_uart, uint8_t* buf, uint16_t len)
{

    //__HAL_UART_ENABLE_IT(uart_config_esp8266_handle(), UART_IT_RXNE);
	if (HAL_OK != HAL_UART_Receive_IT(ph_uart, buf, len))
	{
		while (1);
	}
	while(!gb_rx_complete);
}

