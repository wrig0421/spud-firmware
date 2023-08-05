
#if !defined(PKT_OVERHEAD_H)

#define PKT_OVERHEAD_H

typedef uint8_t pkt_adrs_t;
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
    pkt_adrs_t          adrs;
    pkt_status_e        status;
    uint8_t             rsvd0;
    uint8_t             rsvd1;
} pkt_header_t;


#endif // PKT_OVERHEAD_H
