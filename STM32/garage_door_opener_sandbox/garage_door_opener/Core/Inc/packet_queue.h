

#if !defined(PACKET_QUEUE_H)

#define PACKET_QUEUE_H

#include "cmsis_os.h"
#include "packet_def.h"
#include "gt_521fx_driver.h"


typedef enum
{
	PKT_QUEUE_GT521FX_RX,
	PKT_QUEUE_GT521FX_TX
} pkt_queue_e;

/*
typedef enum
{
	packet_ptr_t	pkt_ptr;
} packet_queue_entry_t;
typedef packet_queue_entry_t	*packet_queue_entry_handle_t;
*/

void packet_queue_init(void);
uint32_t packet_queue_get_count(pkt_queue_e selection);
osMessageQueueId_t packet_queue_get_queue_handle(pkt_queue_e selection);
void packet_enqueue(p_packet_handle_t pkt_handle, pkt_src_dst_t dst);
void packet_dequeue(p_packet_handle_t pkt_handle, pkt_src_dst_t src);
void packet_enqueue_to_sensor_tx(p_packet_handle_t pkt_handle);
void packet_dequeue_from_sensor_tx(p_packet_handle_t pkt_handle);
void packet_enqueue_to_sensor_rx(p_packet_handle_t pkt_handle);
void packet_dequeue_from_sensor_rx(p_packet_handle_t pkt_handle);
void packet_enqueue_to_queue(void);
void packet_parse_rsp(p_packet_handle_t pkt_handle);
void packet_create_cmd_and_send(p_packet_handle_t pkt_handle, gt_521fx_cmd_e cmd, uint32_t input_param);
uint16_t packet_calc_check_sum(p_packet_handle_t pkt_handle);
bool packet_rsp_was_received(void);
gt_521fx_cmd_e cmd_in_flight(void);
void packet_rsp_clear(void);

#endif
