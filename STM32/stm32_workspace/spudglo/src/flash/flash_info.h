
#if !defined(FLASH_INFO_H)
#define FLASH_INFO_H
#include <stdint.h>
#include "animate_led.h"


#define FLASH_INFO_SIZE_BYTES               (512 * 4)
#define FLASH_USER_SPACE_PAGE_START         250
#define FLASH_USER_SPACE_NUM_PAGES          1
#define FLASH_MAX_PAGE_NUMBER               ((256 * 2048 / FLASH_PAGE_SIZE)) - 1
#define FLASH_MIN_PAGE_NUMBER               0

#define FLASH_USER_SPACE_START_ADDRESS      ((uint64_t)250 * 2048)
#define FLASH_START_ADDRESS                 ((uint64_t)0x08000000)

#define FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET   ((uint64_t)250 * 2048)
#define FLASH_SUB_BLOCK_STATUS_ADDRESS_OFFSET   ((uint64_t)251 * 2048)
#define FLASH_SUB_BLOCK_IMAGE_ADDRESS_OFFSET    ((uint64_t)252 * 2048)


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


void flash_info_read_unique_id(uint32_t *uuid);
void flash_access_read_sub_block(flash_info_sub_block_t sub_block, uint32_t* sub_block_uint32);
bool flash_info_animation_enabled(led_state_e animation);
void flash_info_init(void);

#endif
