/***********************************
 * @file   animate_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(UART_ACCESS_H)
#define UART_ACCESS_H

#include <stdint.h>
#include <stdbool.h>
#include "uart_config_hal.h"

typedef enum
{
	UART_ACCESS_ID_HOST,
	UART_ACCESS_ID_FIRST = UART_ACCESS_ID_HOST,
	UART_ACCESS_ID_ESP8266,
	NUM_UART_ACCESS_IDS
} uart_access_id_e;


void uart_access_setup(void);

void uart_access_write_byte(uart_handle_t ph_uart, uint8_t data);
void uart_access_write_block(uart_handle_t ph_uart, uint8_t* data, uint16_t len);
void uart_access_read_byte(uart_handle_t ph_uart, uint8_t* buf);
void uart_access_read_block(uart_handle_t ph_uart, uint8_t* buf, uint16_t len);


void uart_access_write_byte_host(uint8_t data);
void uart_access_write_block_host(uint8_t* data, uint16_t len);
void uart_access_read_byte_host(uint8_t* buf);
void uart_access_read_block_host(uint8_t* buf, uint16_t len);

#endif
