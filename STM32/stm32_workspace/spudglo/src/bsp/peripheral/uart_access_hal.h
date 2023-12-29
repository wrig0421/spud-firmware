// SRW

#if !defined(UART_ACCESS_HAL_H)
#define UART_ACCESS_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include "uart_config_hal.h"
#include "FreeRTOS.h"

//typedef union
//{
//	uint8_t flat_uint8[2048];
//	uint64_t flat_uint64[2048/sizeof(uint64_t)];
//} uart_flat_union_t;

uart_handle_t uart_config_host_handle(void);

bool uart_access_hal_rx_done(TickType_t cur_time, uint32_t timeout_ms);
void uart_access_hal_write_byte(uart_handle_t ph_uart, uint8_t data);
void uart_access_hal_write_block(uart_handle_t ph_uart, uint8_t* data, uint16_t len);
void uart_access_hal_read_byte(uart_handle_t ph_uart, uint8_t* buf);
void uart_access_hal_read_block(uart_handle_t ph_uart, uint8_t* buf, uint16_t len);
void uart_access_hal_write_and_read_block(uart_handle_t ph_uart, uint8_t* write_data, uint16_t write_len, uint8_t* read_buf, uint16_t read_len);

#endif
