
#if !defined(PKT_H)

#define PKT_H

#include <stdbool.h>
#include <stdint.h>
#include "cmsis_os.h"
#include "pkt_overhead.h"
#define PKT_SIZE_BYTES          64
#define PKT_DATA_SIZE_BYTES     (PKT_SIZE_BYTES - sizeof(pkt_header_t) - sizeof(pkt_check_sum_t))
#include "pkt_data.h"


typedef union
{
    struct
    {
        pkt_header_t        header;
        pkt_data_t          data;
        pkt_check_sum_t     check_sum;
    } pkt;
    uint8_t flat_data_uint8[PKT_SIZE_BYTES];
} pkt_t;


typedef pkt_t   *p_pkt_t;


void packet_queue_init(void);
p_pkt_t pkt_dequeue_from_free(void);
void pkt_enqueue_to_free(p_pkt_t pkt_handle);
p_pkt_t pkt_dequeue_from_rx(void);
void pkt_enqueue_to_rx(p_pkt_t pkt_handle);
p_pkt_t pkt_dequeue_from_tx(void);
void pkt_enqueue_to_tx(p_pkt_t pkt_handle);
p_pkt_t pkt_dequeue_from_process(void);
void pkt_enqueue_to_process(p_pkt_t pkt_handle);
void pkt_parse_rx(p_pkt_t pkt_handle);
void pkt_parse_tx(p_pkt_t pkt_handle);


#endif // PKT_H
