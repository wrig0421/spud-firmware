#include "packet_def.h"
#include "gt_521fx_driver.h"
#include "cmsis_os.h"
#include "packet_queue.h"
#include "queue.h"


#define SNS_RX_QUEUE_DEPTH		16 // Pkts
#define SNS_TX_QUEUE_DEPTH		16 // Pkts

typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;

osMessageQueueId_t sensor_rx_queue;
osMessageQueueId_t sensor_tx_queue;


void packet_rsp_set(void);


void packet_queue_init(void)
{
	sensor_rx_queue = osMessageQueueNew(SNS_RX_QUEUE_DEPTH, sizeof( pkt_t ), NULL);
	sensor_tx_queue = osMessageQueueNew(SNS_TX_QUEUE_DEPTH, sizeof( pkt_t ), NULL);
}

void packet_enqueue(p_packet_handle_t pkt_handle, pkt_src_dst_t dst)
{
	// todo add blocking w/ parameter
	switch (dst)
	{
		case PKT_SRC_DST_SNS_TX:
			if (osOK != osMessageQueuePut(sensor_tx_queue, pkt_handle, 0, 0)) while(1);
		break;
		case PKT_SRC_DST_SNS_RX:
			if (osOK != osMessageQueuePut(sensor_rx_queue, pkt_handle, 0, 0)) while(1); // queue full?
		break;
		default: while(1); // wtf
		break;
	}
}


void packet_dequeue(p_packet_handle_t pkt_handle, pkt_src_dst_t src)
{
	switch(src)
	{
		case PKT_SRC_DST_SNS_TX:
			if (osOK != osMessageQueueGet(sensor_tx_queue, (uint8_t *)pkt_handle, NULL, osWaitForever)) while(1); // wtf
		break;
		case PKT_SRC_DST_SNS_RX:
			if (osOK != osMessageQueueGet(sensor_rx_queue, pkt_handle, NULL, osWaitForever)) while(1); // wtf
		break;
		default: while(1); // wtf
		break;
	}
}


void packet_enqueue_to_sensor_tx(p_packet_handle_t pkt_handle)
{
	packet_enqueue(pkt_handle, PKT_SRC_DST_SNS_TX);
}


void packet_dequeue_from_sensor_tx(p_packet_handle_t pkt_handle)
{
	packet_dequeue(pkt_handle, PKT_SRC_DST_SNS_TX);
}


void packet_enqueue_to_sensor_rx(p_packet_handle_t pkt_handle)
{
	packet_enqueue(pkt_handle, PKT_SRC_DST_SNS_RX);
}


void packet_dequeue_from_sensor_rx(p_packet_handle_t pkt_handle)
{
	packet_dequeue(pkt_handle, PKT_SRC_DST_SNS_RX);
}


void packet_parse_rsp(p_packet_handle_t pkt_handle)
{
	if (RSP_RSP_ACK == pkt_handle->rsp_rsp)
	{
		gt521fx_nack_flag_set(false);
	}
	else if (RSP_RSP_NACK == pkt_handle->rsp_rsp)
	{
		gt521fx_nack_flag_set(true);
		gt521fx_nack_state_set((gt_521fx_error_e)pkt_handle->rsp_error_code);
	}
	switch(cmd_in_flight())
	{
		case GT521FX_CMD_GET_ENROLL_COUNT: // ack (enrolled fingerprint count)
			gt521fx_enrolled_fingerprint_count_set(pkt_handle->cmd_input_param);
		break;
		case GT521FX_CMD_IS_PRESS_FINGER:
			//if (0 == (pkt_handle->cmd_input_param))
			if (0 == (pkt_handle->rsp_output_param))
			{
				gt521fx_finger_is_pressed_set(true);
				//while(1);
			}
			else gt521fx_finger_is_pressed_set(false);
		break;
		case GT521FX_CMD_IDENTIFY:
			gt521fx_identified_id_set(pkt_handle->cmd_input_param);
		break;
		case GT521FX_CMD_GET_SECURITY_LEVEL:
			gt521fx_security_lvl_set(pkt_handle->cmd_input_param);
		break;
		default:
		break;
	}
	packet_rsp_set();
}


bool packet_rsp_received = false;

void packet_rsp_clear(void)
{
	packet_rsp_received = false;
}


void packet_rsp_set(void)
{
	packet_rsp_received = true;
}


bool packet_rsp_was_received(void)
{
	if (packet_rsp_received)
	{
		packet_rsp_received = false;
		return true;
	}
	else
	{
		return false;
	}
}


gt_521fx_cmd_e g_cmd_in_flight = GT521FX_CMD_OPEN;

gt_521fx_cmd_e cmd_in_flight(void)
{
	return g_cmd_in_flight;
}

void packet_create_cmd_and_send(p_packet_handle_t pkt_handle, gt_521fx_cmd_e cmd, uint32_t input_param)
{
	packet_rsp_clear();
	g_cmd_in_flight = cmd;
	pkt_handle->start_code[0] = 0x55; // default
	pkt_handle->start_code[1] = 0xAA; // default
	pkt_handle->dev_id = 0x0001; // default
	pkt_handle->cmd_input_param = input_param;
	pkt_handle->cmd_code = cmd;
	pkt_handle->check_sum = packet_calc_check_sum(pkt_handle);
	packet_enqueue_to_sensor_tx(pkt_handle);
}


uint16_t packet_calc_check_sum(p_packet_handle_t pkt_handle)
{
	uint16_t check_sum = 0;
	check_sum += pkt_handle->start_code[0];
	check_sum += pkt_handle->start_code[1];
	check_sum += pkt_handle->dev_id;
	check_sum += pkt_handle->cmd_input_param;
	check_sum += pkt_handle->cmd_code;
	return check_sum;
}



