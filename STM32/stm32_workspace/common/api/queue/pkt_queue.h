
#if !defined(PKT_QUEUE_H)

#define PKT_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "pkt.h"

void pkt_queue_create(void);
QueueHandle_t pkt_queue_handle_host_rx(void);
QueueHandle_t pkt_queue_handle_process(void);
QueueHandle_t pkt_queue_handle_host_tx(void);
QueueHandle_t pkt_queue_handle_free(void);
QueueHandle_t pkt_queue_handle_cmd(void);
bool pkt_queue_handle_valid(QueueHandle_t p_queue_handle);
bool pkt_queue_dequeue_from_queue(QueueHandle_t p_queue_handle, p_pkt_t p_pkt);
bool pkt_queue_enqueue_to_queue(QueueHandle_t p_queue_handle, p_pkt_t p_pkt);
bool pkt_queue_enqueue_pkt_to_host_rx(p_pkt_t p_pkt);
bool pkt_queue_dequeue_pkt_from_host_rx(p_pkt_t p_pkt);
bool pkt_queue_enqueue_pkt_to_host_tx(p_pkt_t p_pkt);
bool pkt_queue_dequeue_pkt_from_host_tx(p_pkt_t p_pkt);
bool pkt_queue_enqueue_pkt_to_free(p_pkt_t p_pkt);
bool pkt_queue_dequeue_pkt_from_free(p_pkt_t p_pkt);
bool pkt_queue_enqueue_pkt_to_cmd(p_pkt_t p_pkt);
bool pkt_queue_dequeue_pkt_from_cmd(p_pkt_t p_pkt);
bool pkt_queue_enqueue_pkt_to_process(p_pkt_t p_pkt);
bool pkt_queue_dequeue_pkt_from_process(p_pkt_t p_pkt);

void pkt_queue_host_rx_parse(void);


#endif
