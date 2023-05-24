
#include <string.h>
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "pkt.h"


typedef enum
{
    PKT_SRC_DST_HOST_RX = 0,
    PKT_SRC_DST_HOST_TX
} pkt_src_dst_e;


#define FREE_QUEUE_DEPTH    16 // pkts
#define RX_QUEUE_DEPTH      16 // pkts
#define TX_QUEUE_DEPTH      16 // pkts
#define PROCESS_QUEUE_DEPTH 4 // pkts


pkt_t g_pkt_pool[FREE_QUEUE_DEPTH];


typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;


osMessageQueueId_t gp_process_queue;
uint8_t g_process_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];
osStaticMessageQDef_t g_process_queue_ctrl;
const osMessageQueueAttr_t g_process_queue_attributes =
{
    .name = "process_queue",
    .cb_mem = &g_process_queue_ctrl,
    .cb_size = sizeof(g_process_queue_ctrl),
    .mq_mem = &g_process_queue_buffer,
    .mq_size = sizeof(g_process_queue_buffer)
};


osMessageQueueId_t gp_free_queue;
uint8_t g_free_queue_buffer[FREE_QUEUE_DEPTH * sizeof(pkt_t)];
osStaticMessageQDef_t g_free_queue_ctrl;
const osMessageQueueAttr_t g_free_queue_attributes =
{
    .name = "free_queue",
    .cb_mem = &g_free_queue_ctrl,
    .cb_size = sizeof(g_free_queue_ctrl),
    .mq_mem = &g_free_queue_buffer,
    .mq_size = sizeof(g_free_queue_buffer)
};


osMessageQueueId_t gp_rx_queue;
uint8_t g_rx_queue_buffer[RX_QUEUE_DEPTH * sizeof(pkt_t)];
osStaticMessageQDef_t g_rx_queue_ctrl;
const osMessageQueueAttr_t g_rx_queue_attributes =
{
    .name = "rx_queue",
    .cb_mem = &g_rx_queue_ctrl,
    .cb_size = sizeof(g_rx_queue_ctrl),
    .mq_mem = &g_rx_queue_buffer,
    .mq_size = sizeof(g_rx_queue_buffer)
};


osMessageQueueId_t gp_tx_queue;
uint8_t g_tx_queue_buffer[TX_QUEUE_DEPTH * sizeof(pkt_t)];
osStaticMessageQDef_t g_tx_queue_ctrl;
const osMessageQueueAttr_t g_tx_queue_attributes = {
    .name = "tx_queue",
    .cb_mem = &g_tx_queue_ctrl,
    .cb_size = sizeof(g_tx_queue_ctrl),
    .mq_mem = &g_tx_queue_buffer,
    .mq_size = sizeof(g_tx_queue_buffer)
};


typedef struct
{
    osMessageQueueId_t  queue_handle;
    uint16_t            index;
} pkt_queue_t;

typedef pkt_queue_t* p_pkt_queue_t;

void packet_rsp_set(void);
pkt_queue_t g_pkt_queue[2];


void packet_queue_init(void)
{
    gp_rx_queue = osMessageQueueNew(RX_QUEUE_DEPTH, sizeof(pkt_t), &g_rx_queue_attributes);
    gp_tx_queue = osMessageQueueNew(TX_QUEUE_DEPTH, sizeof(pkt_t), &g_tx_queue_attributes);
    gp_free_queue = osMessageQueueNew(FREE_QUEUE_DEPTH, sizeof(pkt_t), &g_free_queue_attributes);
    gp_process_queue = osMessageQueueNew(PROCESS_QUEUE_DEPTH, sizeof(pkt_t), &g_process_queue_attributes);

    // initialize free pkts to 0, enqueue free pkts to free queue
    for (uint16_t iii = 0; iii < FREE_QUEUE_DEPTH; iii++)
    {
        memset((void *)g_pkt_pool[iii].flat_data_uint8, 0, PKT_SIZE_BYTES);
        pkt_enqueue_to_free((p_pkt_t)&g_pkt_pool[iii].pkt);
    }
}


p_pkt_t pkt_dequeue_from_free(void)
{
    p_pkt_t pkt = NULL;
    if (osOK != osMessageQueueGet(gp_tx_queue, (uint8_t *)pkt, NULL, osWaitForever)) while(1); // queue full?
    return pkt;
}


void pkt_enqueue_to_free(p_pkt_t pkt_handle)
{
    if (osOK != osMessageQueuePut(gp_free_queue, pkt_handle->flat_data_uint8, 0, 0)) while(1); // queue full?
}


p_pkt_t pkt_dequeue_from_rx(void)
{
    p_pkt_t pkt;
    if (osOK != osMessageQueueGet(gp_rx_queue, pkt, NULL, osWaitForever)) while(1);  // queue full?
    return pkt;
}


void pkt_enqueue_to_rx(p_pkt_t pkt_handle)
{
    if (osOK != osMessageQueuePut(gp_rx_queue, pkt_handle->flat_data_uint8, 0, 0)) while(1); // queue full?
}


p_pkt_t pkt_dequeue_from_tx(void)
{
    p_pkt_t pkt;
    if (osOK != osMessageQueueGet(gp_rx_queue, pkt, NULL, osWaitForever)) while(1);  // queue full?
    return pkt;
}


void pkt_enqueue_to_tx(p_pkt_t pkt_handle)
{
    if (osOK != osMessageQueuePut(gp_tx_queue, pkt_handle->flat_data_uint8, 0, 0)) while(1); // queue full?
}


p_pkt_t pkt_dequeue_from_process(void)
{
    p_pkt_t pkt;
    if (osOK != osMessageQueueGet(gp_process_queue, pkt, NULL, osWaitForever)) while(1);  // queue full?
    return pkt;
}


void pkt_enqueue_to_process(p_pkt_t pkt_handle)
{
    if (osOK != osMessageQueuePut(gp_process_queue, pkt_handle->flat_data_uint8, 0, 0)) while(1); // queue full?
}


void pkt_parse_rx(p_pkt_t pkt_handle)
{
    pkt_src_e pkt_src = pkt_handle->pkt.header.src;
    switch(pkt_src)
    {
        case PKT_SRC_PCB: // dequeue pkt from PCB
            if (osOK != osMessageQueueGet(gp_tx_queue, (uint8_t *)pkt_handle, NULL, osWaitForever)) while(1); // queue full?
        break;
        case PKT_SRC_COMP: // dequeue pkt from computer
            if (osOK != osMessageQueueGet(gp_rx_queue, pkt_handle, NULL, osWaitForever)) while(1);  // queue full?
        break;
        default:
            while(1); // this is an error... trap it
        break;
    }
}


void pkt_parse_tx(p_pkt_t pkt_handle)
{
    pkt_src_e pkt_src = pkt_handle->pkt.header.src;
    switch(pkt_src)
    {
        case PKT_SRC_PCB: // dequeue pkt from PCB
            if (osOK != osMessageQueueGet(gp_tx_queue, (uint8_t *)pkt_handle, NULL, osWaitForever)) while(1); // queue full?
        break;
        case PKT_SRC_COMP: // dequeue pkt from computer
            if (osOK != osMessageQueueGet(gp_rx_queue, pkt_handle, NULL, osWaitForever)) while(1);  // queue full?
        break;
        default:
            while(1); // this is an error... trap it
        break;
    }
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

