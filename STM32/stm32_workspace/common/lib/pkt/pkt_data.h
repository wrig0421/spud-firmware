
#if !defined(PKT_DATA_H)

#define PKT_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "cmsis_os.h"
#include "flash_info.h"


typedef uint8_t     num_strips_t;
typedef uint8_t     valid_image_t;
typedef uint8_t     select_image_t;
typedef uint8_t     strip_brightness_t;
typedef uint16_t    strip_length_t;


typedef flash_info_color_select_t       pkt_data_color_select_t;
typedef flash_info_animation_select_t   pkt_data_animation_select_t;
typedef flash_info_brightness_select_t  pkt_data_brightness_select_t;
typedef flash_info_speed_select_t       pkt_data_speed_select_t;
typedef flash_info_strip_config_t       pkt_data_strip_config_t;


typedef union
{
    pkt_data_strip_config_t         strip;
    pkt_data_color_select_t         color;
    pkt_data_animation_select_t     animation;
    pkt_data_brightness_select_t    brightness;
    pkt_data_speed_select_t         speed;
} pkt_data_union_t;


typedef union
{
    struct
    {
        pkt_data_union_t    data;
        uint8_t             tbd[PKT_DATA_SIZE_BYTES - \
                                sizeof(pkt_data_union_t)];
    };
    uint8_t flat_data_uint8_t[PKT_DATA_SIZE_BYTES / \
                              sizeof(uint8_t)];
    uint16_t flat_data_uint16_t[PKT_DATA_SIZE_BYTES / \
                                sizeof(uint16_t)];
    uint32_t flat_data_uint32_t[PKT_DATA_SIZE_BYTES / \
                                sizeof(uint32_t)];
} pkt_data_t;




#endif // PKT_DATA_H
