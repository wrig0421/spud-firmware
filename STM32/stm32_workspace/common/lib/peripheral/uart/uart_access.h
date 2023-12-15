/***********************************
 * @file   animate_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(UART_ACCESS_H)
#define UART_ACCESS_H

#include <stdint.h>
#include <stdbool.h>

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
