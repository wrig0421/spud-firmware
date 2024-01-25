
#if !defined(FLASH_INFO_H)
#define FLASH_INFO_H
#include <stdint.h>
#include "animate_led.h"
#include "color_led.h"

#define FLASH_INFO_SIZE_BYTES                       (512 * 4)
#define FLASH_USER_SPACE_PAGE_START                 250
#define FLASH_USER_SPACE_NUM_PAGES                  1
#define FLASH_MAX_PAGE_NUMBER                       ((128 * 2048 / FLASH_PAGE_SIZE)) - 1
#define FLASH_MIN_PAGE_NUMBER                       0

#define FLASH_USER_SPACE_START_ADDRESS              ((uint64_t)250 * 2048)

#define FLASH_START_ADDRESS                         ((uint64_t)0x08000000)
#define FLASH_STOP_ADDRESS                         	((uint64_t)0x08020000)

#define FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET       ((uint64_t)(FLASH_MAX_PAGE_NUMBER - 3) * 2048)
//#define FLASH_SUB_BLOCK_STATUS_ADDRESS_OFFSET   ((uint64_t)251 * 2048)
//#define FLASH_SUB_BLOCK_IMAGE_ADDRESS_OFFSET    ((uint64_t)252 * 2048)

#define FLASH_INFO_SUB_BLOCK_SECTOR_SIZE_BYTES      (2048)


typedef enum
{
    FLASH_INFO_IMAGE_SLOT_0 = 0,
    FLASH_INFO_MINI_MAIN_SLOT = FLASH_INFO_IMAGE_SLOT_0,
    FLASH_INFO_IMAGE_SLOT_1,
    FLASH_INFO_IMAGE_SLOT_2,
    NUM_FLASH_INFO_IMAGE_SLOT
} flash_info_image_slot_t;


typedef enum
{
    FLASH_INFO_SUB_BLOCK_CONFIG,
    FLASH_INFO_SUB_BLOCK_STATUS,
    FLASH_INFO_SUB_BLOCK_IMAGE,
    NUM_FLASH_INFO_SUB_BLOCKS
} flash_info_sub_block_t;


typedef struct
{
    uint8_t red             : 1;
    uint8_t dark_red        : 1;
    uint8_t maroon          : 1;
    uint8_t salmon          : 1;
    uint8_t orange_red      : 1;
    uint8_t orange          : 1;
    uint8_t gold            : 1;
    uint8_t yellow          : 1;

    uint8_t green           : 1;
    uint8_t mint            : 1;
    uint8_t forest_green    : 1;
    uint8_t teal            : 1;
    uint8_t cyan            : 1;
    uint8_t aqua_marine     : 1;
    uint8_t blue            : 1;
    uint8_t navy            : 1;

    uint8_t dark_blue       : 1;
    uint8_t purple          : 1;
    uint8_t violet          : 1;
    uint8_t indigo          : 1;
    uint8_t plum            : 1;
    uint8_t pink            : 1;
    uint8_t hot_pink        : 1;
    uint8_t deep_pink       : 1;

    uint8_t brown           : 1;
    uint8_t chocolate       : 1;
    uint8_t white           : 1;
    uint8_t gray            : 1;
    uint8_t silver          : 1;
    uint8_t black           : 1;
    uint8_t lime            : 1;
    uint8_t magenta         : 1;

    uint8_t olive           : 1;
    uint8_t khaki           : 1;
    uint8_t lawn_green      : 1;
    uint8_t spring_green    : 1;
    uint8_t midnight_blue   : 1;
    uint8_t blue_violet     : 1;
    uint8_t dark_magenta    : 1;
    uint8_t rsvd            : 1;

    // future colors go here!

} flash_info_color_select_t;


typedef struct
{
    uint8_t spell           : 1;
    uint8_t solid_color     : 1;
    uint8_t rainbow         : 1;
    uint8_t sparkle_no_fill : 1;
    uint8_t chase_rainbow   : 1;
    uint8_t chase           : 1;
    uint8_t solid_white     : 1;
    uint8_t sparkle_fill    : 1;

    uint8_t fade            : 1;
    uint8_t twinkle         : 1;
    uint8_t rsvd0           : 6;

} flash_info_animation_select_t;


typedef struct
{
    uint8_t brightness_100p : 1;
    uint8_t brightness_75p  : 1;
    uint8_t brightness_50p  : 1;
    uint8_t brightness_25p  : 1;
    uint8_t brightness_1p   : 1;
    uint8_t rsvd0           : 3;
} flash_info_brightness_select_t;


typedef struct
{
    uint8_t speed_1000p     : 1;
    uint8_t speed_500p      : 1;
    uint8_t speed_100p      : 1;
    uint8_t speed_50p       : 1;
    uint8_t speed_25p       : 1;
    uint8_t rsvd0           : 3;
} flash_info_speed_select_t;


typedef struct
{
    uint8_t     num_strips;
    uint8_t     rsvd0;
    uint8_t     rsvd1;
    uint8_t     rsvd2;

    uint16_t    strip_1_length;
    uint16_t    strip_2_length;
    uint16_t    strip_3_length;
    uint16_t    fill;
} flash_info_strip_config_t;


void flash_info_read_unique_id(uint32_t *uuid);
void flash_access_read_sub_block(flash_info_sub_block_t sub_block, uint32_t* sub_block_uint32);
bool flash_info_animation_enabled(strip_num_e strip_num,
                                  led_state_e animation);
void flash_info_init(void);

all_colors_e flash_info_read_led_color_current(void);
led_state_e flash_info_read_led_animation_current(void);
void flash_info_write_led_color_current(all_colors_e color);
void flash_info_write_led_animation_current(led_state_e state);

#endif