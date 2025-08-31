
#include "FreeRTOS.h"
#include "queue.h"
#include "pkt_queue.h"
#include <string.h>
#include "FreeRTOS.h"

#include "pkt.h"


/* The queue is to be created to hold a maximum of 10 uint64\_t
   variables. */
#define QUEUE_RX_DEPTH_ITEMS				10
#define QUEUE_TX_DEPTH_ITEMS				10
#define QUEUE_FREE_DEPTH_ITEMS 				10

#define QUEUE_RX_QUEUE_ITEM_SIZE_BYTES		PKT_SIZE_BYTES
#define QUEUE_TX_QUEUE_ITEM_SIZE_BYTES		PKT_SIZE_BYTES
#define QUEUE_FREE_QUEUE_ITEM_SIZE_BYTES	PKT_SIZE_BYTES

#define ITEM_SIZE       sizeof( uint64_t )

/* The variable used to hold the queue's data structure. */
//static StaticQueue_t xStaticQueue;

/* The array to use as the queue's storage area. This must be at least
   uxQueueLength * uxItemSize bytes. */
//uint8_t ucQueueStorageArea[ QUEUE_LENGTH * ITEM_SIZE ];
uint8_t g_queue_rx_buffer[QUEUE_RX_DEPTH_ITEMS * QUEUE_RX_QUEUE_ITEM_SIZE_BYTES];
uint8_t g_queue_tx_buffer[QUEUE_TX_DEPTH_ITEMS * QUEUE_TX_QUEUE_ITEM_SIZE_BYTES];
uint8_t g_queue_free_buffer[QUEUE_FREE_DEPTH_ITEMS * QUEUE_FREE_QUEUE_ITEM_SIZE_BYTES];
//
QueueHandle_t g_queue_rx;
QueueHandle_t g_queue_tx;
QueueHandle_t g_queue_free;
//
//queue_item_t g_queue_entry[NUM_QUEUES] =
//{
//	[QUEUE_FREE] =
//	{
////		.p_cur_item =
//	    .queue = g_queue_free,
//		.queue_index = 0
//	},
//	[QUEUE_RX] =
//	{
////		.p_cur_item =
//	    .queue = g_queue_rx,
//		.queue_index = 0
//	},
//	[QUEUE_TX] =
//	{
////		.p_cur_item =
//	    .queue = g_queue_tx,
//		.queue_index = 0
//	},
//};

/* The variable used to hold the queue's data structure. */
static StaticQueue_t g_static_queue_rx;
static StaticQueue_t g_static_queue_tx;
static StaticQueue_t g_static_queue_free;

void queue_create( void *pvParameters )
{

    /* Create a queue capable of containing 10 uint64_t values. */
	g_queue_rx = xQueueCreateStatic(QUEUE_RX_DEPTH_ITEMS,
									QUEUE_RX_QUEUE_ITEM_SIZE_BYTES,
									g_queue_rx_buffer,
									&g_static_queue_rx);
	if (NULL == g_queue_rx)
	{
		while (1);
	}

	g_queue_tx = xQueueCreateStatic(QUEUE_TX_DEPTH_ITEMS,
									QUEUE_TX_QUEUE_ITEM_SIZE_BYTES,
									g_queue_tx_buffer,
									&g_static_queue_tx);
	if (NULL == g_queue_tx)
	{
		while (1);
	}

	g_queue_free = xQueueCreateStatic(QUEUE_FREE_DEPTH_ITEMS,
									  QUEUE_FREE_QUEUE_ITEM_SIZE_BYTES,
									  g_queue_free_buffer,
									  &g_static_queue_free );
	if (NULL == g_queue_free)
	{
		while (1);
	}
}


void queue_enqueue_pkt_to_rx(p_pkt_t p_pkt)
{
    if(pdPASS != xQueueSendToBack(g_queue_rx, ( void * ) p_pkt, portMAX_DELAY))
    {
    	// log error
    }
}


void queue_enqueue_pkt_to_tx(p_pkt_t p_pkt)
{
    if(pdPASS != xQueueSendToBack(g_queue_tx, ( void * ) p_pkt, portMAX_DELAY))
    {
    	// log error
    }
}


void queue_enqueue_pkt_to_free(p_pkt_t p_pkt)
{
    if(pdPASS != xQueueSendToBack(g_queue_free, ( void * ) p_pkt, portMAX_DELAY))
    {
    	// log error
    }
}



