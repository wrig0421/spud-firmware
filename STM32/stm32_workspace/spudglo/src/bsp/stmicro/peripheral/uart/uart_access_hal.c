// SRW

#include "stm32l4xx_hal.h"
#include "uart_access_hal.h"
#include "cmsis_os.h"

uint8_t g_counter = 0;


bool gb_tx_complete = false;
bool gb_rx_complete = false;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	gb_tx_complete = true;
	gb_rx_complete = false;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	gb_rx_complete = true;
	gb_tx_complete = false;
}

void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(uart_config_esp8266_handle());
	//__HAL_UART_CLEAR_IT(uart_config_esp8266_handle(), U ART_IT_TXE);

	//g_counter++;
}

uint8_t g_data_read[100] = {0xff};
void uart_access_hal_write_and_read_block(uart_handle_t ph_uart, uint8_t* write_data, uint16_t write_len, uint8_t* read_buf, uint16_t read_len)
{
	// clear UART with 0 timeout call below.
	HAL_UART_Receive(ph_uart, g_data_read, 10, 0);

	// start listening for receive before TX
	if (HAL_OK != HAL_UART_Receive_IT(ph_uart, read_buf, read_len))
	{
		while (1);
	}
	gb_tx_complete = false;

	// tx
	if (HAL_OK != HAL_UART_Transmit_IT(ph_uart, write_data, write_len))
	{
		while (1);
	}

	// wait for rx complete
	while (!gb_rx_complete);
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

