// SRW
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdbool.h>
#include "stm32l4xx_hal.h"

#include "pkt.h"
#include "uart_access.h"
#include "task_create.h"
#include "task_uart.h"

TaskHandle_t 	g_task_uart_rx_handle;
StaticTask_t 	g_task_uart_rx_buffer;
StackType_t 	g_task_uart_rx_stack[TASK_CREATE_STACK_SIZE_STANDARD];

TaskHandle_t 	g_task_uart_tx_handle;
StaticTask_t 	g_task_uart_tx_buffer;
StackType_t 	g_task_uart_tx_stack[TASK_CREATE_STACK_SIZE_STANDARD];


void task_uart_create(void)
{
	g_task_uart_rx_handle = xTaskCreateStatic(task_uart_rx,
			"task_uart_rx", TASK_CREATE_STACK_SIZE_STANDARD,
			NULL, tskIDLE_PRIORITY, g_task_uart_rx_stack,
			&g_task_uart_rx_buffer);

	g_task_uart_tx_handle = xTaskCreateStatic(task_uart_tx,
			"task_uart_tx", TASK_CREATE_STACK_SIZE_STANDARD,
			NULL, tskIDLE_PRIORITY, g_task_uart_tx_stack,
			&g_task_uart_tx_buffer);
}


// rx from computer
void task_uart_rx(void *argument)
{
	uint32_t notification = 0;
    p_pkt_t p_pkt;
    // TODO use p_pkt
    UNUSED(p_pkt);

    while (1)
    {
        xTaskNotifyWait(0, 0, &notification, portMAX_DELAY);
		// did we get a pkt?  do something with the pkt.
    }
}

//HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)

// tx to computer
uint8_t g_test_buffer[10] = {0,1,2,3,4,5};

void task_uart_tx(void *argument)
{
	uint32_t notification = 0;
	pkt_t pkt;
    // TODO use p_pkt
    UNUSED(pkt);
    while (1)
    {
        uart_access_write_block_host(g_test_buffer, 10);
        xTaskNotifyWait(0, 0, &notification, portMAX_DELAY);
    }
}
