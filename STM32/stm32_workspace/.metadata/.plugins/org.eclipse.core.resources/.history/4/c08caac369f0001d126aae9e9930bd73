

#if !defined(PACKET_QUEUE_H)

#define PACKET_QUEUE_H

#include "cmsis_os.h"
#include "packet_def.h"


void packet_queue_init(void);
void packet_enqueue(p_packet_handle_t pkt_handle, pkt_src_dst_t dst);
void packet_dequeue(p_packet_handle_t pkt_handle, pkt_src_dst_t src);
void packet_enqueue_to_host_tx(p_packet_handle_t pkt_handle);
void packet_dequeue_from_host_tx(p_packet_handle_t pkt_handle);
void packet_enqueue_to_host_rx(p_packet_handle_t pkt_handle);
void packet_dequeue_from_host_rx(p_packet_handle_t pkt_handle);
void packet_parse_rsp(p_packet_handle_t pkt_handle);
void packet_rsp_clear(void);
void packet_rsp_set(void);
bool packet_rsp_was_received(void);



#endif
