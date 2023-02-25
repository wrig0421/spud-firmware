#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "version.h"
#include "flash_info.h"

#define FLASH_INFO_DEFAULT_IMAGE_SLOT   FLASH_INFO_IMAGE_SLOT_1
#define FLASH_INFO_MINI_MAIN_SLOT       FLASH_INFO_MINI_MAIN_SLOT

#pragma pack(1)

typedef union
{
    uint32_t data[3];
} uint96_t;


// config
typedef uint8_t num_strips_t;

// image
typedef uint8_t valid_image_t;
typedef uint8_t select_image_t;


typedef union
{
    version_date_and_time_t fw_version_date;
    uint8_t                 flat_data_uint8[sizeof(version_date_and_time_t)];
} flash_info_fw_version_t;


typedef union
{
    struct
    {
        num_strips_t num_strips;
    } config_data;

    struct
    {
        uint96_t uuid;
    } status_data;

    struct
    {
        flash_info_image_slot_t active_image;
        version_date_and_time_t active_image_fw_version;
        flash_info_image_slot_t mini_main_image;
        version_date_and_time_t mini_main_image_fw_version;
        valid_image_t           valid_image;
        select_image_t          select_image;
    } image_data;
    uint8_t                     flat_data_uint8[FLASH_INFO_SIZE_BYTES];
    uint16_t                    flat_data_uint16[FLASH_INFO_SIZE_BYTES / sizeof(uint16_t)];
    uint32_t                    flat_data_uint32[FLASH_INFO_SIZE_BYTES / sizeof(uint32_t)];
    uint64_t                    flat_data_uint64[FLASH_INFO_SIZE_BYTES / sizeof(uint64_t)];
} flash_info_block_t;
#pragma pack(0)

flash_info_block_t  g_flash_info_block;

void flash_info_block_init(void)
{
    g_flash_info_block.status_data.uuid.data[0] = HAL_GetUIDw0();
    g_flash_info_block.status_data.uuid.data[1] = HAL_GetUIDw1();
    g_flash_info_block.status_data.uuid.data[2] = HAL_GetUIDw2();

    g_flash_info_block.config_data.num_strips = 1;

    g_flash_info_block.image_data.active_image = FLASH_INFO_IMAGE_SLOT_1;
    //g_flash_info_block.image_data.active_image_fw_version = ;
    g_flash_info_block.image_data.mini_main_image = FLASH_INFO_MINI_MAIN_SLOT;
//    g_flash_info_block.image_data.mini_main_image_fw_version = ;
    g_flash_info_block.image_data.select_image = FLASH_INFO_IMAGE_SLOT_1;
    g_flash_info_block.image_data.valid_image = UINT8_MAX;
    // need to write to flash!
}


void flash_info_init(void)
{
    flash_access_read_flash_info_sector(g_flash_info_block.flat_data_uint32);
    if ((UINT32_MAX == g_flash_info_block.status_data.uuid.data[0]) &&
                    (UINT32_MAX == g_flash_info_block.status_data.uuid.data[1]) &&
                    (UINT32_MAX == g_flash_info_block.status_data.uuid.data[2]))
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
    if (0 != memcmp((void *)&version_date_time,
                    (void *)(&g_flash_info_block.image_data.active_image_fw_version),
                    sizeof(version_date_and_time_t)))
    {
        memcpy((void *)(&g_flash_info_block.image_data.active_image_fw_version),
                        (void *)&version_date_time,
                        sizeof(version_date_and_time_t));
        // NEED TO WRITE THIS TO FLASH
    }

}


void flash_info_read_sector_data(void *p_data, uint16_t address)
{
    switch (address)
    {
        case offsetof(flash_info_status_block_t, status_data.uuid.data):
            memcpy(p_data, &g_flash_info_status_block.status_data.uuid.data, sizeof(uint96_t));
        break;
        case offsetof(flash_info_config_block_t, config_data.num_strips):
            memcpy(p_data, &g_flash_info_config_block.config_data.num_strips, sizeof(num_strips_t));
        break;
        case offsetof(flash_info_image_block_t, image_data.active_image):
            memcpy(p_data, &g_flash_info_image_block.image_data.active_image, sizeof(flash_info_image_slot_t));
        break;
        case offsetof(flash_info_image_block_t, image_data.active_image_fw_version):
            memcpy(p_data, &g_flash_info_image_block.image_data.active_image_fw_version, sizeof(version_date_and_time_t));
        break;
        case offsetof(flash_info_image_block_t, image_data.mini_main_image):
            memcpy(p_data, &g_flash_info_image_block.image_data.mini_main_image, sizeof(flash_info_image_slot_t));
        break;
        case offsetof(flash_info_image_block_t, image_data.mini_main_image_fw_version):
            memcpy(p_data, &g_flash_info_image_block.image_data.mini_main_image_fw_version, sizeof(version_date_and_time_t));
        break;
        case offsetof(flash_info_image_block_t, image_data.valid_image):
            memcpy(p_data, &g_flash_info_image_block.image_data.valid_image, sizeof(valid_image_t));
        break;
        case offsetof(flash_info_image_block_t, image_data.select_image):
            memcpy(p_data, &g_flash_info_image_block.image_data.select_image, sizeof(select_image_t));
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
        case offsetof(flash_info_config_block_t, config_data.num_strips):
            if (0 != memcmp(&g_flash_info_config_block.config_data.num_strips, p_data, sizeof(num_strips_t)))
            {
                write_to_flash = true;
                memcpy(&g_flash_info_config_block.config_data.num_strips, p_data, sizeof(num_strips_t));
            }
        break;
        case offsetof(flash_info_image_block_t, image_data.active_image):
            if (0 != memcmp(&g_flash_info_image_block.image_data.active_image, p_data, sizeof(flash_info_image_slot_t)))
            {
                write_to_flash = true;
                memcpy(&g_flash_info_image_block.image_data.active_image, p_data, sizeof(flash_info_image_slot_t));
            }
        break;
        case offsetof(flash_info_image_block_t, image_data.active_image_fw_version):
            if (0 != memcmp(&g_flash_info_image_block.image_data.active_image_fw_version, p_data, sizeof(version_date_and_time_t)))
            {
                write_to_flash = true;
                memcpy(&g_flash_info_image_block.image_data.active_image_fw_version, p_data, sizeof(version_date_and_time_t));
            }
        break;
        case offsetof(flash_info_image_block_t, image_data.mini_main_image):
            if (0 != memcmp(&g_flash_info_image_block.image_data.mini_main_image, p_data, sizeof(flash_info_image_slot_t)))
            {
                write_to_flash = true;
                memcpy(&g_flash_info_image_block.image_data.mini_main_image, p_data, sizeof(flash_info_image_slot_t));
            }
        break;
        case offsetof(flash_info_image_block_t, image_data.mini_main_image_fw_version):
            if (0 != memcmp(&g_flash_info_image_block.image_data.mini_main_image_fw_version, p_data, sizeof(version_date_and_time_t)))
            {
                write_to_flash = true;
                memcpy(&g_flash_info_image_block.image_data.mini_main_image_fw_version, p_data, sizeof(version_date_and_time_t));
            }
        break;
        case offsetof(flash_info_image_block_t, image_data.valid_image):
            if (0 != memcmp(&g_flash_info_image_block.image_data.valid_image, p_data, sizeof(valid_image_t)))
            {
                write_to_flash = true;
                memcpy(&g_flash_info_image_block.image_data.valid_image, p_data, sizeof(valid_image_t));
            }
        break;
        case offsetof(flash_info_image_block_t, image_data.selected_image):
            if (0 != memcmp(&g_flash_info_image_block.image_data.select_image, p_data, sizeof(select_image_t)))
            {
                write_to_flash = true;
                memcpy(&g_flash_info_image_block.image_data.select_image, p_data, sizeof(select_image_t));
            }
        break;
        default:
        break;
    }
}




