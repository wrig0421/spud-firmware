#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "version.h"
#include "animate_led.h"
#include "flash_info.h"

#define FLASH_INFO_DEFAULT_IMAGE_SLOT   FLASH_INFO_IMAGE_SLOT_1
#define FLASH_INFO_MINI_MAIN_SLOT       FLASH_INFO_MINI_MAIN_SLOT
#define FLASH_INFO_SUB_BLOCK_SIZE       256
#define FLASH_INFO_SECTOR_SIZE          (8 * FLASH_INFO_SUB_BLOCK_SIZE) // 2 kB
#define MAX_NUM_STRIPS  3

typedef uint8_t     num_strips_t;
typedef uint8_t     valid_image_t;
typedef uint8_t     select_image_t;
typedef uint8_t     strip_brightness_t;
typedef uint16_t    strip_length_t;

#pragma pack(1)




typedef union
{
    uint32_t data[3];
} uint96_t;


typedef union
{
    version_date_and_time_t     fw_version_date;
    uint8_t                     flat_data_uint8[sizeof(version_date_and_time_t)];
} flash_info_fw_version_t;


typedef struct
{
    num_strips_t                num_strips;                                         // 0x00
    uint8_t                     strip_sync_animation;                               // 0x01
    strip_length_t              strip_length_one;                                   // 0x02
    strip_length_t              strip_length_two;                                   // 0x04
    strip_length_t              strip_length_three;                                 // 0x06
    strip_brightness_t          strip_one_brightness;                               // 0x08
    strip_brightness_t          strip_two_brightness;                               // 0x09
    strip_brightness_t          strip_three_brightness;                             // 0x0A
    animate_led_state_t         strip_one_active_animation_mask;                    // 0x0B
    animate_led_state_t         strip_two_active_animations_mask;                   // 0x10
    animate_led_state_t         strip_three_active_animations_mask;                 // 0x14
} flash_info_strip_info_t;


//typedef struct
//{
//    flash_info_image_slot_t     active_image;                                       // 0x00
//    uint8_t                     rsvd0;                                              // 0x01
//    version_date_and_time_t     active_image_fw_version;                            // 0x02
//    flash_info_image_slot_t     mini_main_image;                                    // 0x0A
//    version_date_and_time_t     mini_main_image_fw_version;                         // 0x0B
//    uint8_t                     rsvd1;                                              // 0x0C
//    valid_image_t               valid_image;                                        // 0x14
//    select_image_t              select_image;                                       // 0x15
//} flash_info_image_info_t;


typedef struct
{
    flash_info_strip_info_t     strip_info;                                         // 0x00
    uint8_t                     strip_info_fill[FLASH_INFO_SUB_BLOCK_SIZE - sizeof(flash_info_strip_info_t)];
//    flash_info_image_info_t     image_info;                                         // 0x100
//    uint8_t                     image_info_fill[FLASH_INFO_SUB_BLOCK_SIZE - sizeof(flash_info_image_info_t)];
    uint96_t                    uuid;                                               // 0x200
} flash_info_data_t;

typedef union
{
    struct
    {
        flash_info_data_t       flash_info_data;
        uint8_t                 rsvd[FLASH_INFO_SECTOR_SIZE - sizeof(flash_info_data_t)];
    };
    uint8_t                     flat_data_uint8[FLASH_INFO_SECTOR_SIZE];
    uint16_t                    flat_data_uint16[FLASH_INFO_SECTOR_SIZE / sizeof(uint16_t)];
    uint32_t                    flat_data_uint32[FLASH_INFO_SECTOR_SIZE / sizeof(uint32_t)];
    uint64_t                    flat_data_uint64[FLASH_INFO_SECTOR_SIZE / sizeof(uint64_t)];
} flash_info_block_t;
#pragma pack(0)

flash_info_block_t  g_flash_info_block;


bool flash_info_animation_enabled(led_state_e animation)
{
    bool return_val = false;
    switch (animation)
    {
        case LED_STATE_SPELL:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.spell) return_val = true;
        break;
        case LED_STATE_WHITE_COLOR:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.white) return_val = true;
        break;
        case LED_STATE_SOLID_COLOR:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.solid) return_val = true;
        break;
        case LED_STATE_SPARKLE_NO_FILL:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.sparkle_no_fill) return_val = true;
        break;
        case LED_STATE_SPARKLE_FILL:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.sparkle) return_val = true;
        break;
        case LED_STATE_RAINBOW_CYCLE:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.rainbow) return_val = true;
        break;
        case LED_STATE_THEATER_CHASE:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.chase) return_val = true;
        break;
        case LED_STATE_THEATER_CHASE_RAINBOW:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.chase_rainbow) return_val = true;
        break;
        case LED_STATE_FADE_IN_AND_OUT:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.fade) return_val = true;
        break;
        case LED_STATE_TWINKLE:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.twinkle) return_val = true;
        break;
        case LED_STATE_SRW_DEBUG:
            if (g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.white) return_val = true;
        break;
        default:
        break;
    }
    return return_val;
}


void flash_info_block_init(void)
{
    g_flash_info_block.flash_info_data.uuid.data[0] = HAL_GetUIDw0();
    g_flash_info_block.flash_info_data.uuid.data[1] = HAL_GetUIDw1();
    g_flash_info_block.flash_info_data.uuid.data[2] = HAL_GetUIDw2();

    g_flash_info_block.flash_info_data.strip_info.num_strips = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_sync_animation = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_length_one = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_length_two = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_length_three = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_one_brightness = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_two_brightness = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_three_brightness = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_one_brightness = 1;

    g_flash_info_block.flash_info_data.strip_info.strip_two_brightness = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_three_brightness = 1;

    g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.spell = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.white = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.solid = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.sparkle = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.sparkle_no_fill = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.rainbow = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.chase = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.chase_rainbow = 1;

    g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.fade = 1;
    g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.twinkle = 1;
    //g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.rsvd0 = 1; // future
    //g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.rsvd1 = 1; // future
    //g_flash_info_block.flash_info_data.strip_info.strip_one_active_animation_mask.rsvd2 = 1; // future

    // need to write to flash!
}


void flash_info_read_sector_data(void *p_data, uint16_t address)
{
    switch (address)
    {

        case offsetof(flash_info_block_t, flash_info_data.strip_info.num_strips):
            memcpy(p_data, &g_flash_info_block.flash_info_data.strip_info.num_strips, sizeof(num_strips_t));
        break;
        case offsetof(flash_info_block_t, flash_info_data.uuid):
            memcpy(p_data, &g_flash_info_block.flash_info_data.uuid, sizeof(uint96_t));
        break;

        default:
        break;
    }
}


void flash_info_write_sector_data(void *p_data, uint16_t address)
{
    bool write_to_flash = false;
    switch (address)
    {
        case offsetof(flash_info_block_t, flash_info_data.strip_info.num_strips):
            if (0 != memcmp(&g_flash_info_block.flash_info_data.strip_info.num_strips, p_data, sizeof(num_strips_t)))
            {
                write_to_flash = true;
                memcpy(&g_flash_info_block.flash_info_data.strip_info.num_strips, p_data, sizeof(num_strips_t));
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.uuid):
            if (0 != memcmp(&g_flash_info_block.flash_info_data.uuid, p_data, sizeof(uint96_t)))
            {
                write_to_flash = true;
                memcpy(&g_flash_info_block.flash_info_data.uuid, p_data, sizeof(uint96_t));
            }
        break;
        default:
        break;
    }
    if (write_to_flash)
    {
        // todo
    }
}


uint32_t temp = 0;
void flash_info_init(void)
{
    temp = sizeof(flash_info_data_t);
    flash_info_block_init();
    //flash_access_read_flash_info_sector(g_flash_info_block.flat_data_uint32);
    if ((UINT32_MAX == g_flash_info_block.flash_info_data.uuid.data[0]) &&
                    (UINT32_MAX == g_flash_info_block.flash_info_data.uuid.data[1]) &&
                    (UINT32_MAX == g_flash_info_block.flash_info_data.uuid.data[2]))
    {
        flash_info_block_init();
    }
}


void flash_info_firmware_version(void)
{
    version_date_and_time_t version_date_time = \
    {
        .year = BUILD_DATE_YEAR,
        .month = BUILD_DATE_MONTH,
        .day = BUILD_DATE_DAY,
        .hour = BUILD_TIME_HOUR,
        .minutes = BUILD_TIME_MINUTE,
        .seconds = BUILD_TIME_SECOND,
        .fill = 0xFF
    };
//    if (0 != memcmp((void *)&version_date_time,
//                    (void *)(&g_flash_info_block.flash_info_data.image_info.active_image_fw_version),
//                    sizeof(version_date_and_time_t)))
//    {
//        memcpy((void *)(&g_flash_info_block.flash_info_data.image_info.active_image_fw_version),
//                        (void *)&version_date_time,
//                        sizeof(version_date_and_time_t));
//        // NEED TO WRITE THIS TO FLASH
//    }

}


