// SRW

#include "stm32l4xx_hal.h"
#include "uart_access_hal.h"

void uart_access_hal_write_byte(uart_handle_t ph_uart, uint8_t data)
{
	if (HAL_OK != HAL_UART_Transmit(ph_uart, &data, 1, 10000))
	{
		while (1);
	}
}


void uart_access_hal_write_block(uart_handle_t ph_uart, uint8_t* data, uint16_t len)
{
	if (HAL_OK != HAL_UART_Transmit(ph_uart, data, len, 10000))
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
	if (HAL_OK != HAL_UART_Receive(ph_uart, buf, len, 10000))
	{
		while (1);
	}
}

