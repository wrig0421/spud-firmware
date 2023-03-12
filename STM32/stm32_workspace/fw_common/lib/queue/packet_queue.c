#include "packet_def.h"
#include "cmsis_os.h"
#include "packet_queue.h"
#include "queue.h"

typedef enum
{
    PKT_SRC_DST_HOST_RX = 0,
    PKT_SRC_DST_HOST_TX
} pkt_src_dst_e;


#define RX_QUEUE_DEPTH  16 // pkts
#define TX_QUEUE_DEPTH  16 // pkts
#define CMD_QUEUE_DEPTH 16 // pkts

typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;


osMessageQueueId_t rx_queue_handle;
uint8_t rx_queue_buffer[ RX_QUEUE_DEPTH * sizeof( pkt_t ) ];
osStaticMessageQDef_t rx_queue_ctrl;
const osMessageQueueAttr_t rx_queue_atrributes = {
  .name = "rx_queue",
  .cb_mem = &rx_queue_ctrl,
  .cb_size = sizeof(rx_queue_ctrl),
  .mq_mem = &rx_queue_buffer,
  .mq_size = sizeof(rx_queue_buffer)
};


osMessageQueueId_t tx_queue_handle;
uint8_t tx_queue_buffer[ TX_QUEUE_DEPTH * sizeof( pkt_t ) ];
osStaticMessageQDef_t tx_queue_ctrl;
const osMessageQueueAttr_t tx_queue_attributes = {
  .name = "tx_queue",
  .cb_mem = &tx_queue_ctrl,
  .cb_size = sizeof(tx_queue_ctrl),
  .mq_mem = &tx_queue_buffer,
  .mq_size = sizeof(tx_queue_buffer)
};


osMessageQueueId_t cmd_queue_handle;
uint8_t cmd_queue_buffer[ CMD_QUEUE_DEPTH * sizeof( pkt_t ) ];
osStaticMessageQDef_t cmd_queue_ctrl;
const osMessageQueueAttr_t cmd_queue_attributes = {
  .name = "cmd_queue",
  .cb_mem = &cmd_queue_ctrl,
  .cb_size = sizeof(cmd_queue_ctrl),
  .mq_mem = &cmd_queue_buffer,
  .mq_size = sizeof(cmd_queue_buffer)
};


#if 0
osMessageQueueId_t rx_queue_handle;
const osMessageQueueAttr_t rx_queue_atrributes = {
  .name = "sensor_rx_queue"
};
/* Definitions for sensor_tx_queue */
osMessageQueueId_t tx_queue_handle;
const osMessageQueueAttr_t tx_queue_attributes = {
  .name = "sensor_tx_queue"
};
#endif

void packet_rsp_set(void);


void packet_queue_init(void)
{
    //cmd_queue_handle = osMessageQueueNew (CMD_QUEUE_DEPTH, sizeof( pkt_t ), &cmd_queue_atrributes);
    rx_queue_handle = osMessageQueueNew (RX_QUEUE_DEPTH, sizeof( pkt_t ), &rx_queue_atrributes);
    tx_queue_handle = osMessageQueueNew (TX_QUEUE_DEPTH, sizeof( pkt_t ), &tx_queue_attributes);
}


void packet_enqueue(p_packet_handle_t pkt_handle, pkt_src_dst_t dst)
{
	// todo add blocking w/ parameter
	switch (dst)
	{
		case PKT_SRC_DST_HOST_TX:
			if (osOK != osMessageQueuePut(tx_queue_handle, pkt_handle, 0, 0))
			{
				while(1); // queue full?
			}
		break;
		case PKT_SRC_DST_HOST_RX:
			if (osOK != osMessageQueuePut(rx_queue_handle, pkt_handle, 0, 0))
			{
				while(1); // queue full?
			}
		break;
		default:
			while(1); // wtf
		break;
	}
}

void packet_enqueue_to_cmd(p_packet_handle_t pkt_handle)
{
    if (osOK != osMessageQueuePut(cmd_queue_handle, pkt_handle, 0, 0))
    {
        while(1); // queue full?
    }
}


void packet_dequeue(p_packet_handle_t pkt_handle, pkt_src_dst_t src)
{
	switch(src)
	{
		case PKT_SRC_DST_HOST_TX:
			if (osOK != osMessageQueueGet(tx_queue_handle, (uint8_t *)pkt_handle, NULL, osWaitForever))
			{
				while(1); // wtf
			}
		break;
		case PKT_SRC_DST_HOST_RX:
			if (osOK != osMessageQueueGet(rx_queue_handle, pkt_handle, NULL, osWaitForever))
			{
				while(1); // wtf
			}
		break;
		default:
		break;
	}
}


void packet_enqueue_to_host_tx(p_packet_handle_t pkt_handle)
{
	packet_enqueue(pkt_handle, PKT_SRC_DST_HOST_TX);
}


void packet_dequeue_from_host_tx(p_packet_handle_t pkt_handle)
{
	packet_dequeue(pkt_handle, PKT_SRC_DST_HOST_TX);
}


void packet_enqueue_to_host_rx(p_packet_handle_t pkt_handle)
{
	packet_enqueue(pkt_handle, PKT_SRC_DST_HOST_RX);
}


void packet_dequeue_from_host_rx(p_packet_handle_t pkt_handle)
{
	packet_dequeue(pkt_handle, PKT_SRC_DST_HOST_RX);
}


void packet_parse_rsp(p_packet_handle_t pkt_handle)
{

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


void packet_parse(p_packet_handle_t pkt_handle)
{
    pkt_id_e pkt_id;
    pkt_id = (pkt_id_e)(pkt_handle->header.pkt_id);

    switch (pkt_id)
    {
        case PKT_ID_CMD:

        break;
        default:
        break;
    }
}


