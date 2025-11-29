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

#include "free_rtos_convenience.h"


extern UART_HandleTypeDef g_uart_handle_config[NUM_UART_CONFIG_BUSES];

TaskHandle_t 	g_task_uart_rx_handle;
StaticTask_t 	g_task_uart_rx_buffer;
StackType_t 	g_task_uart_rx_stack[TASK_CREATE_STACK_SIZE_STANDARD];

TaskHandle_t 	g_task_uart_tx_handle;
StaticTask_t 	g_task_uart_tx_buffer;
StackType_t 	g_task_uart_tx_stack[TASK_CREATE_STACK_SIZE_STANDARD];
extern uint8_t g_rx_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];
extern uint8_t g_tx_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];

extern uint32_t g_rx_queue_buffer_index;
extern uint32_t g_tx_queue_buffer_index;

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
		//HAL_UART_Transmit(&g_uart_handle_config[UART_CONFIG_BUS_HOST], g_rx_queue_buffer, 10, 5000);
//		HAL_UART_Transmit_DMA(&g_uart_handle_config[bus],
//							 g_rx_queue_buffer,
//							 10);
//
//		HAL_UART_Receive_DMA(&g_uart_handle_config[bus],
//							 g_rx_queue_buffer + g_rx_queue_buffer_index * PKT_SIZE_BYTES,
//							 10);//PKT_SIZE_BYTES);
//    	HAL_UART_Transmit(&g_uart_handle_config[UART_CONFIG_BUS_HOST], g_rx_queue_buffer, 10, 5000);
    	HAL_UART_Receive(&g_uart_handle_config[UART_CONFIG_BUS_HOST],
					     g_rx_queue_buffer, 10, 5000);
//        xTaskNotifyWait(0, 0, &notification, portMAX_DELAY);
        free_rtos_delay_ms(3000);
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
    	free_rtos_delay_ms(400);
//        uart_access_write_block_host(g_test_buffer, 10);
//        xTaskNotifyWait(0, 0, &notification, portMAX_DELAY);
    }
}
