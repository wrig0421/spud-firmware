
#include "packet_def.h"
#include "packet_queue.h"
#include <string.h>
#include "main.h"
#include "cmsis_os.h"

#define FREE_BUFFER_LENGTH 		20// in number of pkts
#define CMD_BUFFER_LENGTH 		20// in number of pkts
#define RSP_BUFFER_LENGTH 		20// in number of pkts


pkt_t sns_tx_pkt;

extern UART_HandleTypeDef huart1;
p_packet_handle_t free_buffer[FREE_BUFFER_LENGTH];
p_packet_handle_t cmd_buffer[CMD_BUFFER_LENGTH];
//p_packet_handle_t rsp_buffer[RSP_BUFFER_LENGTH];
pkt_t rsp_buffer;

uint16_t g_free_buffer_index = 0;
uint8_t rx_data[sizeof(pkt_t)] = {0};

void USART3_IRQHandler()
{
	HAL_UART_RxCpltCallback(&huart1);
}


bool uart_rx_flag = false;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//HAL_UART_Receive_DMA(&huart1, rx_data, sizeof(pkt_t));
	memcpy(rsp_buffer.flat_data, rx_data, sizeof(pkt_t));

	uart_rx_flag = true;

}


/* USER CODE BEGIN Header_task_sensor_tx_entry */
/**
* @brief Function implementing the task_sensor_tx thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_task_sensor_tx_entry */
void task_sensor_tx_entry(void *argument)
{
  /* USER CODE BEGIN task_sensor_tx_entry */
  /* Infinite loop */
  for(;;)
  {
	  packet_dequeue_from_sensor_tx(&sns_tx_pkt);
	  HAL_UART_Receive_DMA(&huart1, rx_data, sizeof(pkt_t));
	  HAL_UART_Transmit_DMA(&huart1, (uint8_t *)&sns_tx_pkt, sizeof(sns_tx_pkt));

	  //osDelay(1000);
  }
  /* USER CODE END task_sensor_tx_entry */
}


pkt_t sns_rx_pkt;
/* USER CODE BEGIN Header_sensor_rx_entry */
/**
* @brief Function implementing the task_sensor_rx thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_sensor_rx_entry */
void sensor_rx_entry(void *argument)
{
  /* USER CODE BEGIN sensor_rx_entry */
  /* Infinite loop */
	do
	{
		if(uart_rx_flag)
		{
			uart_rx_flag = false;
			packet_enqueue_to_sensor_rx(&rsp_buffer);
			packet_dequeue_from_sensor_rx(&sns_rx_pkt);
			packet_parse_rsp(&sns_rx_pkt);
			//packet_parse_rsp(&rsp_buffer);
		}

		//osDelay(1000);
	} while(1);
  /* USER CODE END sensor_rx_entry */
}


