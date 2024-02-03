// SRW

#include "stm32l4xx_hal.h"
#include "uart_access_hal.h"
#include "cmsis_os.h"
#include "task_led_ctrl.h"
#include "esp8266.h"
#include <string.h>
#include <stdbool.h>

TickType_t g_receive_tick_time;
uint8_t *gh_uart_rx_buffer;
uint16_t g_uart_rx_buffer_index = 0;


void USART1_IRQHandler(void)
{
#if defined (BOARD_SPUDGLO_V5)
	HAL_UART_IRQHandler(uart_config_esp8266_handle());
#endif
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	// do something in future
}

typedef enum
{
	PING,
	PONG
} ping_pong_e;

bool g_buffer_full = false;
bool g_firmware_update_in_progress = false;
uint8_t g_uart_sector_ping[2048];
uint8_t g_uart_sector_pong[2048];
bool firmware_update_first_pass = true;
uint8_t* g_uart_sector_buffer = g_uart_sector_ping;
uint8_t* g_uart_sector_full_buffer;
uint16_t g_uart_sector_index = 0;
ping_pong_e ping_pong = PING;
uint32_t g_uart_firmware_count = 0;
uint8_t ipd_count = 0;
volatile uint16_t i_index = 0;
uint16_t g_search_index = 0;
uint16_t g_count_of_ipd_instances = 0;

uint8_t g_big_buffer[41000] = {0};
uint16_t g_big_buffer_index = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static bool first_pass = true;

	// save time of rx.  Unknown amounts of data are sent back from ESP8266..  Need to use timeout functionality to know we're done rxing.
	if (g_firmware_update_in_progress)
	{
		g_uart_firmware_count++;
//		if (first_pass)
//		{
//			first_pass = false;
//			memcpy(g_uart_sector_buffer, gh_uart_rx_buffer + esp8266_read_start_of_binary_index() + 1, g_uart_rx_buffer_index - (esp8266_read_start_of_binary_index() + 1));
//			g_uart_sector_index += g_uart_rx_buffer_index - (esp8266_read_start_of_binary_index() + 1);
//		}

//		switch (ipd_count)
//		{
//			case 0:
//				if ((uint8_t)'\r' == *(uint8_t *)(g_uart_sector_buffer + (g_search_index)))
//				{
//					i_index = g_search_index;
//					ipd_count++;
//				}
//				else
//				{
//					ipd_count = 0;
//				}
//			break;
//			case 1:
//				if ((uint8_t)'\n' == *(uint8_t *)(g_uart_sector_buffer + (g_search_index)))
//				{
//					ipd_count++;
//				}
//				else
//				{
//					ipd_count = 0;
//				}
//			break;
//			case 2:
//				if ((uint8_t)'+' == *(uint8_t *)(g_uart_sector_buffer + (g_search_index)))
//				{
//					ipd_count++;
//				}
//				else
//				{
//					ipd_count = 0;
//				}
//			break;
//			case 3:
//				if ((uint8_t)'I' == *(uint8_t *)(g_uart_sector_buffer + (g_search_index)))
//				{
//					ipd_count++;
//				}
//				else
//				{
//					ipd_count = 0;
//				}
//			break;
//			case 4:
//				if ((uint8_t)'P' == *(uint8_t *)(g_uart_sector_buffer + (g_search_index)))
//				{
//					ipd_count++;
//				}
//				else
//				{
//					ipd_count = 0;
//				}
//			break;
//			case 5:
//				if ((uint8_t)'D' == *(uint8_t *)(g_uart_sector_buffer + (g_search_index)))
//				{
//					g_count_of_ipd_instances++;
//					ipd_count++;
//				}
//				else
//				{
//					ipd_count = 0;
//				}
//
//			break;
//			case 6:
//				if ((uint8_t)':' == *(uint8_t *)(g_uart_sector_buffer + (g_search_index)))
//				{
//					ipd_count = 0;
//					g_uart_sector_index = i_index;
//				}
//			break;
//			default:
//
//			break;
//		}
//		g_search_index = g_uart_sector_index;
//		//g_search_index = g_uart_sector_index - 1;
//		g_uart_sector_index %= 2048;

//		if (!g_uart_sector_index)
//		{
//			g_search_index = 2047;
//			if (PING == ping_pong)
//			{
//				ping_pong = PONG;
//				g_uart_sector_buffer = g_uart_sector_pong;
//				g_uart_sector_full_buffer = g_uart_sector_ping;
//			}
//			else
//			{
//				ping_pong = PING;
//				g_uart_sector_buffer = g_uart_sector_ping;
//				g_uart_sector_full_buffer = g_uart_sector_pong;
//			}
//			g_buffer_full = true;
//		}
		if (g_big_buffer_index == 41000) g_buffer_full = true;
		else
		{
			if (HAL_OK != HAL_UART_Receive_IT(huart, (uint8_t *)(g_big_buffer + (g_big_buffer_index++)), 1))
			{
				while (1);
			}
		}
//		if (HAL_OK != HAL_UART_Receive_IT(huart, (uint8_t *)(g_uart_sector_buffer + (g_uart_sector_index++)), 1))
//		{
//			while (1);
//		}
	}
	else
	{
		g_receive_tick_time = xTaskGetTickCount();
		if (HAL_OK != HAL_UART_Receive_IT(huart, (uint8_t *)(gh_uart_rx_buffer + (g_uart_rx_buffer_index++)), 1))
		{
			while (1);
		}
	}
}


static TickType_t uart_access_hal_rx_tick_time_reset(void)
{
	g_receive_tick_time = xTaskGetTickCount();
}


static TickType_t uart_access_hal_last_rx_tick_time(void)
{
	return g_receive_tick_time;
}


bool uart_access_hal_rx_done(TickType_t cur_time, uint32_t timeout_ms)
{
	if ((cur_time - uart_access_hal_last_rx_tick_time()) < timeout_ms) return false;
	return true;
}


uint16_t sizeof_array = 0;
void uart_access_hal_write_and_read_block(uart_handle_t ph_uart, uint8_t* write_data, uint16_t write_len, uint8_t* read_buf, uint16_t read_len)
{
	static bool first_pass = true;
	// clear UART with 0 timeout call below.
	HAL_UART_Receive(ph_uart, gh_uart_rx_buffer, 1000, 0);
	gh_uart_rx_buffer = read_buf;
	sizeof_array = sizeof(gh_uart_rx_buffer);
	g_uart_rx_buffer_index = 0; // general rx buffer is used to receive the data.  Clear the index each time a new transmission is sent out.
	memset(gh_uart_rx_buffer, 0, GENERAL_RX_BUFFER_SIZE);
	// start listening for receive before TX
	if (first_pass)
	{
		// prime rx.  Need to listen prior to TX.
		first_pass = false;
		if (HAL_OK != HAL_UART_Receive_IT(ph_uart, (uint8_t *)(gh_uart_rx_buffer + g_uart_rx_buffer_index++), 1))
		{
			while (1);
		}
	}
	uart_access_hal_rx_tick_time_reset();
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

