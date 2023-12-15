// SRW

#if !defined(UART_ACCESS_HAL_H)
#define UART_ACCESS_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include "uart_config_hal.h"


uart_handle_t uart_config_host_handle(void);

void uart_access_hal_write_byte(uart_handle_t ph_uart, uint8_t data);
void uart_access_hal_write_block(uart_handle_t ph_uart, uint8_t* data, uint16_t len);
void uart_access_hal_read_byte(uart_handle_t ph_uart, uint8_t* buf);
void uart_access_hal_read_block(uart_handle_t ph_uart, uint8_t* buf, uint16_t len);


#endif
