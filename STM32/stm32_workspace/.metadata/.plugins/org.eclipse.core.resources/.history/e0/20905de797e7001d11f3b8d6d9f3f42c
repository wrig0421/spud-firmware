
#if !defined(PACKET_DEF_H)

#define PACKET_DEF_H

#include <stdbool.h>
#include <stdint.h>

typedef uint16_t pkt_check_sum_t;

typedef enum
{
    PKT_ID_CMD,
    NUM_PKT_ID
} pkt_id_e;


typedef enum
{
    PKT_VAR_WRITE_BYTE      = 1,
    PKT_VAR_READ_BYTE       = 2,
    PKT_VAR_WRITE_BLOCK     = 3,
    PKT_VAR_READ_BLOCK      = 4,
    PKT_VAR_RESET           = 5

} pkt_var_e;

typedef struct
{
    uint8_t             pkt_id;
    uint8_t             pkt_var;
    uint8_t             rsvd2;
    uint8_t             rsvd3;
    union
    {
        uint16_t        src_dst;
        struct
        {
            uint8_t     src;
            uint8_t     dst;
        };
    };
    uint8_t             rsp_code;
    uint8_t             err_code;
} pkt_header_t;


#define PKT_SIZE_BYTES           256
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


typedef struct
{
    pkt_header_t    header;
    pkt_data_t      data;
    pkt_check_sum_t check_sum;
} pkt_t;


typedef enum
{
	RSP_RSP_ACK = 0x30,
	RSP_RSP_NACK = 0x31,
} rsp_rsp_e;


typedef pkt_t   *p_packet_handle_t;


typedef enum
{
	PKT_SRC_DST_SNS_TX,
	PKT_SRC_DST_SNS_RX,
} pkt_src_dst_t;


#endif
