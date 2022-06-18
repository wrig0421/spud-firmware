
#include "packet_def.h"
#include "packet_queue.h"
#include <string.h>
#include "main.h"
#include "cmsis_os.h"

#define FREE_BUFFER_LENGTH 		20// in number of pkts
#define CMD_BUFFER_LENGTH 		20// in number of pkts
#define RSP_BUFFER_LENGTH 		20// in number of pkts


typedef struct
{
	osMessageQueueId_t	gt521fx_rx_queue_handle;
	pkt_t				pkt;
	//p_packet_handle_t	p_pkt;
	//packet_queue_entry_handle_t cur_queue_entry;
	UART_HandleTypeDef 	rx_uart_handle;
} gt521fx_uart_rx_rec_t;


typedef struct
{
	osMessageQueueId_t 	gt521fx_tx_queue_handle;
	pkt_t				pkt;
	//p_packet_handle_t	p_pkt;
	//packet_queue_entry_handle_t p_pkt_entry;
	//packet_queue_entry_handle_t cur_queue_entry;
	UART_HandleTypeDef tx_uart_handle;
} gt521fx_uart_tx_rec_t;


gt521fx_uart_tx_rec_t gt521fx_uart_tx;
gt521fx_uart_rx_rec_t gt521fx_uart_rx;

extern UART_HandleTypeDef g_huart1;


uint32_t rx_callback_passes = 0;
bool uart_rx_flag = false;
bool rx_callback_first_pass = true;

/*
bool ok = true;
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (HAL_OK != HAL_UART_Receive_DMA(&g_huart1, gt521fx_uart_rx.pkt.flat_data, sizeof(pkt_t)))
	{
		while(1);
	}
}
*/


uint32_t rx_queue_count = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (osOK != osMessageQueuePut(packet_queue_get_queue_handle(PKT_QUEUE_GT521FX_RX), &gt521fx_uart_rx.pkt, 0, 0))//gt521fx_uart_rx.cur_queue_entry->pkt_ptr, 0, 0))
	{
		while(1); // ouch
	}
}


void serial_com_init_all(void)
{
	gt521fx_uart_rx.gt521fx_rx_queue_handle = packet_queue_get_queue_handle(PKT_QUEUE_GT521FX_RX);
	gt521fx_uart_rx.rx_uart_handle = g_huart1;
	gt521fx_uart_tx.gt521fx_tx_queue_handle = packet_queue_get_queue_handle(PKT_QUEUE_GT521FX_TX);
	gt521fx_uart_tx.tx_uart_handle = g_huart1;
}


bool g_rx_pkt_received = false;

bool pkt_received(void)
{
	if (g_rx_pkt_received)
	{
		g_rx_pkt_received = false;
		return true;
	}
	else
	{
		return false;
	}
}

void clear_pkt_received_flag(void)
{
	g_rx_pkt_received = false;
}


gt_521fx_cmd_e g_last_cmd = GT521FX_CMD_OPEN;

/**
* @brief Function implementing the task_sensor_tx thread.
* @param argument: Not used
* @retval None
*/
void task_sensor_tx_entry(void *argument)
{
  /* USER CODE BEGIN task_sensor_tx_entry */
  /* Infinite loop */
  for(;;)
  {
	  packet_dequeue_from_sensor_tx(&gt521fx_uart_tx.pkt);
	  clear_pkt_received_flag();
	  g_last_cmd = gt521fx_uart_tx.pkt.cmd_code;
	  HAL_UART_Transmit(&g_huart1, gt521fx_uart_tx.pkt.flat_data, sizeof(pkt_t), 5000);
  }
  /* USER CODE END task_sensor_tx_entry */
}


/**
* @brief Function implementing the task_sensor_rx thread.
* @param argument: Not used
* @retval None
*/
void sensor_rx_entry(void *argument)
{
	for(;;)
	{
		HAL_UART_Receive_DMA(&g_huart1, gt521fx_uart_rx.pkt.flat_data, sizeof(pkt_t));
		packet_dequeue_from_sensor_rx(&gt521fx_uart_rx.pkt);
		packet_parse_rsp(&gt521fx_uart_rx.pkt);
		g_rx_pkt_received = true;
	}
  /* USER CODE END sensor_rx_entry */
}


