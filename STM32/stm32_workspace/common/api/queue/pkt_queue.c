
#include "FreeRTOS.h"
#include "queue.h"
#include "pkt_queue.h"
#include <stdbool.h>
#include <string.h>
#include "stm32l4xx_it.h"
#include "FreeRTOS.h"

#include "pkt.h"

#define PKT_QUEUE_RX_DEPTH_ITEMS						10
#define PKT_QUEUE_TX_DEPTH_ITEMS						10
#define PKT_QUEUE_CMD_DEPTH_ITEMS						10
#define PKT_QUEUE_PROCESS_DEPTH_ITEMS					10

#define PKT_QUEUE_FREE_DEPTH_ADDITIONAL_SLUDGE_ITEMS	50

#define PKT_QUEUE_FREE_DEPTH_ITEMS 				PKT_QUEUE_RX_DEPTH_ITEMS + \
												PKT_QUEUE_TX_DEPTH_ITEMS + \
												PKT_QUEUE_CMD_DEPTH_ITEMS + \
												PKT_QUEUE_PROCESS_DEPTH_ITEMS + \
												PKT_QUEUE_FREE_DEPTH_ADDITIONAL_SLUDGE_ITEMS

#define PKT_QUEUE_RX_QUEUE_ITEM_SIZE_BYTES		PKT_SIZE_BYTES
#define PKT_QUEUE_TX_QUEUE_ITEM_SIZE_BYTES		PKT_SIZE_BYTES
#define PKT_QUEUE_FREE_QUEUE_ITEM_SIZE_BYTES	PKT_SIZE_BYTES
#define PKT_QUEUE_CMD_QUEUE_ITEM_SIZE_BYTES			PKT_SIZE_BYTES
#define PKT_QUEUE_PROCESS_QUEUE_ITEM_SIZE_BYTES			PKT_SIZE_BYTES


#define ITEM_SIZE       sizeof( uint64_t )

uint8_t g_pkt_queue_host_rx_buffer[PKT_QUEUE_RX_DEPTH_ITEMS * PKT_QUEUE_RX_QUEUE_ITEM_SIZE_BYTES];
uint8_t g_pkt_queue_host_tx_buffer[PKT_QUEUE_TX_DEPTH_ITEMS * PKT_QUEUE_TX_QUEUE_ITEM_SIZE_BYTES];
uint8_t g_pkt_queue_free_buffer[PKT_QUEUE_FREE_DEPTH_ITEMS * PKT_QUEUE_FREE_QUEUE_ITEM_SIZE_BYTES];
uint8_t g_pkt_queue_cmd_buffer[PKT_QUEUE_CMD_DEPTH_ITEMS * PKT_QUEUE_CMD_QUEUE_ITEM_SIZE_BYTES];
uint8_t g_pkt_queue_process_buffer[PKT_QUEUE_CMD_DEPTH_ITEMS * PKT_QUEUE_CMD_QUEUE_ITEM_SIZE_BYTES];


QueueHandle_t g_pkt_queue_host_rx;
QueueHandle_t g_pkt_queue_host_tx;
QueueHandle_t g_pkt_queue_free;
QueueHandle_t g_pkt_queue_cmd;
QueueHandle_t g_pkt_queue_process;


/* The variable used to hold the queue's data structure. */
static StaticQueue_t g_static_queue_rx;
static StaticQueue_t g_static_queue_tx;
static StaticQueue_t g_static_queue_free;
static StaticQueue_t g_static_queue_cmd;
static StaticQueue_t g_static_queue_process;


void queue_create(void)
{
    /* Create a queue capable of containing 10 uint64_t values. */
	g_pkt_queue_host_rx = xQueueCreateStatic(PKT_QUEUE_RX_DEPTH_ITEMS,
									PKT_QUEUE_RX_QUEUE_ITEM_SIZE_BYTES,
									g_pkt_queue_host_rx_buffer,
									&g_static_queue_rx);
	if (NULL == g_pkt_queue_host_rx) while (1);

	g_pkt_queue_host_tx = xQueueCreateStatic(PKT_QUEUE_TX_DEPTH_ITEMS,
									PKT_QUEUE_TX_QUEUE_ITEM_SIZE_BYTES,
									g_pkt_queue_host_tx_buffer,
									&g_static_queue_tx);
	if (NULL == g_pkt_queue_host_tx) while (1);

	g_pkt_queue_free = xQueueCreateStatic(PKT_QUEUE_FREE_DEPTH_ITEMS,
									  PKT_QUEUE_FREE_QUEUE_ITEM_SIZE_BYTES,
									  g_pkt_queue_free_buffer,
									  &g_static_queue_free );
	if (NULL == g_pkt_queue_free) while (1);

	g_pkt_queue_cmd = xQueueCreateStatic(PKT_QUEUE_CMD_DEPTH_ITEMS,
										PKT_QUEUE_CMD_QUEUE_ITEM_SIZE_BYTES,
										g_pkt_queue_cmd_buffer,
										&g_static_queue_cmd);
	if (NULL == g_pkt_queue_cmd) while (1);

	g_pkt_queue_process = xQueueCreateStatic(PKT_QUEUE_PROCESS_DEPTH_ITEMS,
											PKT_QUEUE_PROCESS_QUEUE_ITEM_SIZE_BYTES,
											g_pkt_queue_process_buffer,
											&g_static_queue_process);
	if (NULL == g_pkt_queue_process) while (1);
}


QueueHandle_t pkt_queue_handle_host_rx(void)
{
	return g_pkt_queue_host_rx;
}


QueueHandle_t pkt_queue_handle_process(void)
{
	return g_pkt_queue_process;
}


QueueHandle_t pkt_queue_handle_host_tx(void)
{
	return g_pkt_queue_host_tx;
}


QueueHandle_t pkt_queue_handle_free(void)
{
	return g_pkt_queue_free;
}


QueueHandle_t pkt_queue_handle_cmd(void)
{
	return g_pkt_queue_cmd;
}


bool pkt_queue_handle_valid(QueueHandle_t p_queue_handle)
{
	bool success = false;

	if ((g_pkt_queue_host_rx == p_queue_handle) || \
		(g_pkt_queue_host_tx == p_queue_handle) || \
		(g_pkt_queue_free == p_queue_handle) || \
		(g_pkt_queue_cmd == p_queue_handle) || \
		(g_pkt_queue_process == p_queue_handle))
	{
		success = true;
	}
	return success;
}


bool pkt_queue_dequeue_from_queue(QueueHandle_t p_queue_handle, p_pkt_t p_pkt)
{
	BaseType_t success = pdFAIL;

	if (pkt_queue_handle_valid(p_queue_handle))
	{
		bool isr_active = micro_in_isr() ? true : false;
		if (isr_active)
		{
			BaseType_t xHigherPriorityTaskWoken;
			success = xQueueReceiveFromISR(pkt_queue_handle_process(), p_pkt, &xHigherPriorityTaskWoken);
		}
		else
		{
			success = xQueueReceive(pkt_queue_handle_process(), p_pkt, portMAX_DELAY);
		}
	}
	return (pdPASS == success) ? true : false;
}


bool pkt_queue_enqueue_to_queue(QueueHandle_t p_queue_handle, p_pkt_t p_pkt)
{
	BaseType_t success = pdFAIL;
	if (pkt_queue_handle_valid(p_queue_handle))
	{
	    bool isr_active = micro_in_isr() ? true : false;

	    if (isr_active)
	    {
	    	BaseType_t xHigherPriorityTaskWoken;
			success = xQueueSendToBackFromISR(p_queue_handle, (void *)p_pkt, &xHigherPriorityTaskWoken);
	    }
	    else
	    {
        	success = xQueueSendToBack(p_queue_handle, (void *)p_pkt, portMAX_DELAY);
	    }
	}
    return (pdPASS == success) ? true : false;
}


bool pkt_queue_enqueue_pkt_to_host_rx(p_pkt_t p_pkt)
{
    return pkt_queue_enqueue_to_queue(g_pkt_queue_host_rx, p_pkt);
}


bool pkt_queue_dequeue_pkt_from_host_rx(p_pkt_t p_pkt)
{
	return pkt_queue_dequeue_from_queue(g_pkt_queue_host_rx, p_pkt);
}


bool pkt_queue_enqueue_pkt_to_host_tx(p_pkt_t p_pkt)
{
    return pkt_queue_enqueue_to_queue(g_pkt_queue_host_tx, p_pkt);
}


bool pkt_queue_dequeue_pkt_from_host_tx(p_pkt_t p_pkt)
{
	return pkt_queue_dequeue_from_queue(g_pkt_queue_host_tx, p_pkt);
}


bool pkt_queue_enqueue_pkt_to_free(p_pkt_t p_pkt)
{
    return pkt_queue_enqueue_to_queue(g_pkt_queue_free, p_pkt);
}


bool pkt_queue_dequeue_pkt_from_free(p_pkt_t p_pkt)
{
	return pkt_queue_dequeue_from_queue(g_pkt_queue_free, p_pkt);
}


bool pkt_queue_enqueue_pkt_to_cmd(p_pkt_t p_pkt)
{
    return pkt_queue_enqueue_to_queue(g_pkt_queue_cmd, p_pkt);
}


bool pkt_queue_dequeue_pkt_from_cmd(p_pkt_t p_pkt)
{
	return pkt_queue_dequeue_from_queue(g_pkt_queue_free, p_pkt);
}


bool pkt_queue_enqueue_pkt_to_process(p_pkt_t p_pkt)
{
    return pkt_queue_enqueue_to_queue(g_pkt_queue_process, p_pkt);
}


bool pkt_queue_dequeue_pkt_from_process(p_pkt_t p_pkt)
{
	return pkt_queue_dequeue_from_queue(g_pkt_queue_process, p_pkt);
}



p_pkt_t gp_host_rx_pkt;
void pkt_queue_host_rx_parse(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    bool isr_active = micro_in_isr() ? true : false;
    if (isr_active)
    {
    	xQueueReceiveFromISR(pkt_queue_handle_host_rx(), gp_host_rx_pkt, &xHigherPriorityTaskWoken);
    }
    else
    {
    	xQueueReceive(pkt_queue_handle_host_rx(), gp_host_rx_pkt, portMAX_DELAY);
    }

    // check the ID of the pkt below!
    switch (gp_host_rx_pkt->pkt.header.tag)
    {
    	case PKT_TAG_CMD:
    		pkt_queue_enqueue_pkt_to_process(gp_host_rx_pkt);
    	break;
    	case PKT_TAG_MAX:
    	default:
    		while (1);
		break;
    }
    // for now I'm not going to worry about the below case...
    // if pkt is not enqueued then must enqueue it to free here..
}


