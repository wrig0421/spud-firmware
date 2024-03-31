/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/


#include "uart_access_hal.h"
#include "uart_config_hal.h"
#include "uart_access.h"

void uart_access_setup(void)
{
	uart_config_hal_setup();
}


void uart_access_write_byte(uart_handle_t ph_uart, uint8_t data)
{
	uart_access_hal_write_byte(ph_uart, data);
}


void uart_access_write_block(uart_handle_t ph_uart, uint8_t* data, uint16_t len)
{
	uart_access_hal_write_block(ph_uart, data, len);
}


void uart_access_read_byte(uart_handle_t ph_uart, uint8_t* buf)
{
	uart_access_hal_read_byte(ph_uart, buf);
}


void uart_access_read_block(uart_handle_t ph_uart, uint8_t* buf, uint16_t len)
{
	uart_access_hal_read_block(ph_uart, buf, len);
}


void uart_access_write_byte_host(uint8_t data)
{
	uart_access_hal_write_byte(uart_config_host_handle(), data);
}


void uart_access_write_block_host(uint8_t* data, uint16_t len)
{
	uart_access_hal_write_block(uart_config_host_handle(), data, len);
}


void uart_access_read_byte_host(uint8_t* buf)
{
	uart_access_hal_read_byte(uart_config_host_handle(), buf);
}


void uart_access_read_block_host(uint8_t* buf, uint16_t len)
{
	uart_access_hal_read_block(uart_config_host_handle(), buf, len);
}


void uart_access_write_byte_esp8266(uint8_t data)
{
	uart_access_hal_write_byte(uart_config_esp8266_handle(), data);
}


void uart_access_write_and_read_block_esp8266(uint8_t* write_data, uint16_t write_len, uint8_t* read_buf, uint16_t read_len)
{
	uart_access_hal_write_and_read_block(uart_config_esp8266_handle(), write_data, write_len, read_buf, read_len);
}


void uart_access_write_block_esp8266(uint8_t* data, uint16_t len)
{
	uart_access_hal_write_block(uart_config_esp8266_handle(), data, len);
}


void uart_access_read_byte_esp8266(uint8_t* buf)
{
	uart_access_hal_read_byte(uart_config_esp8266_handle(), buf);
}


void uart_access_read_block_esp8266(uint8_t* buf, uint16_t len)
{
	uart_access_hal_read_block(uart_config_esp8266_handle(), buf, len);
}

