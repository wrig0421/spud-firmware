// SRW

#if !defined(UART_CONFIG_HAL_H)
#define UART_CONFIG_HAL_H
#include "stm32l431xx.h"
#include "stm32l4xx_hal.h"
#include <stdint.h>

typedef UART_HandleTypeDef* 	uart_handle_t;
typedef USART_TypeDef* 			uart_instance_t;
typedef uint32_t 				uart_baud_rate_t;
typedef GPIO_TypeDef*  			port_t;
typedef uint8_t					alt_func_t;
typedef IRQn_Type				irqn_t;


typedef enum
{
	UART_CONFIG_BUS_HOST,
	UART_CONFIG_BUS_FIRST = UART_CONFIG_BUS_HOST,
	UART_CONFIG_BUS_ESP8266,
	NUM_UART_CONFIG_BUSES
} uart_config_bus_e;


typedef struct
{
	uint16_t 	rx;
	port_t   	rx_port;
	alt_func_t 	rx_alt_func;
	uint16_t 	tx;
	port_t	 	tx_port;
	alt_func_t 	tx_alt_func;
} uart_config_pin_t;


typedef struct
{
	uart_config_pin_t 		pin;
	irqn_t					irqn;
} uart_config_t;


void uart_config_hal_setup(void);

#endif
