// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "uart_access_hal.h"
#include "uart_access.h"

void uart_access_host_rx(void)
{
	uart_access_hal_host_rx();
}


void uart_access_host_tx(void)
{
	uart_access_hal_host_tx();
}


