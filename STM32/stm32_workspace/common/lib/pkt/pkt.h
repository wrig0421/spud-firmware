
#if !defined(PACKET_DEF_H)

#define PACKET_DEF_H

#include <stdbool.h>
#include <stdint.h>
#include "cmsis_os.h"
#include "pkt.h"


typedef uint16_t pkt_check_sum_t;


typedef enum
{
    PKT_SRC_PCB         = 1,
    PKT_SRC_COMP        = 2,


    PKT_SRC_MAX         = 255 // do not exceed
} pkt_src_e;


typedef enum
{
    PKT_STATUS_BEGIN    = 1,
    PKT_STATUS_CMPLT    = 2,
    PKT_STATUS_ERR      = 3,


    PKT_STATUS_MAX      = 255 // do not exceed
} pkt_status_e;


typedef enum
{
    PKT_VAR_WRITE       = 1,
    PKT_VAR_READ        = 2,
    PKT_VAR_RESET       = 3,


    PKT_VAR_MAX         = 255 // do not exceed
} pkt_var_e;


typedef enum
{
    PKT_TAG_CMD         = 0,


    PKT_TAG_MAX         = 255 // do not exceed this value!
} pkt_tag_e;


typedef struct
{
    pkt_tag_e           tag;
    pkt_var_e           var;
    pkt_src_e           src;
    pkt_status_e        status;
    uint16_t            adrs;
} pkt_header_t;


#define PKT_SIZE_BYTES          64
#define PKT_DATA_SIZE_BYTES     (PKT_SIZE_BYTES - sizeof(pkt_header_t) - sizeof(pkt_check_sum_t))


typedef union
{
    struct
    {
        uint8_t tbd[PKT_DATA_SIZE_BYTES];
    };
    uint8_t flat_data_uint8_t[PKT_DATA_SIZE_BYTES];
    uint16_t flat_data_uint16_t[PKT_DATA_SIZE_BYTES / sizeof(uint16_t)];
    uint32_t flat_data_uint32_t[PKT_DATA_SIZE_BYTES / sizeof(uint32_t)];
} pkt_data_t;


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


typedef enum
{
	RSP_RSP_ACK = 0x30,
	RSP_RSP_NACK = 0x31,
} rsp_rsp_e;


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


#endif