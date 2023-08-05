// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_flash.h"
#include "flash_info.h"
#include "flash_access.h"

uint64_t g_count = 0;

uint64_t* g_user_flash;
void flash_access_init(void)
{

}


void flash_access_increment_count(void)
{
    *g_user_flash = *g_user_flash + 1;
}


void flash_access_erase_user_flash(void)
{

    // this will erase the "user flash"
    uint32_t page_error = 0;
    FLASH_EraseInitTypeDef user_flash =
    {
                    .TypeErase = FLASH_TYPEERASE_PAGES,
                    .Banks = FLASH_BANK_1,
                    .Page = FLASH_USER_SPACE_PAGE_START,
                    .NbPages = FLASH_USER_SPACE_NUM_PAGES
    };
    HAL_FLASHEx_Erase(&user_flash, &page_error);
}


void flash_access_read_flash(void *p_data, void *address, uint16_t num_bytes)
{
    memcpy((void *)p_data, (void *)address, num_bytes);
}


void flash_access_write_to_flash(uint64_t *p_data, uint64_t address, uint16_t num_bytes)
{
    uint16_t num_double_words = num_bytes / sizeof(uint64_t);
    uint8_t remainder = num_bytes % sizeof(uint64_t);
    if (!num_double_words) num_double_words = 1; // need to at least write one
    else if (remainder) num_double_words += 1;
    else ; // do nothing
    for (uint16_t iii = 0; iii < num_double_words; iii++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address + iii, p_data);
    }
}


void flash_access_read_sector(void *p_data, flash_info_sub_block_t sub_block)
{
    uint64_t flash_sub_block_address = 0;
    switch (sub_block)
    {
        case FLASH_INFO_SUB_BLOCK_CONFIG:
            flash_sub_block_address = FLASH_START_ADDRESS + FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET;
        break;
//        case FLASH_INFO_SUB_BLOCK_STATUS:
//        break;
//        case FLASH_INFO_SUB_BLOCK_IMAGE:
//        break;
        default:
        break;
    }
    memcpy(p_data, (void *)flash_sub_block_address, FLASH_INFO_SUB_BLOCK_SECTOR_SIZE_BYTES);
}


void flash_access_write_sector(void *p_data, flash_info_sub_block_t sub_block)
{
    uint32_t flash_sub_block_address = 0;
    uint16_t num_double_words = FLASH_INFO_SUB_BLOCK_SECTOR_SIZE_BYTES / sizeof(uint64_t);
    switch (sub_block)
    {
        case FLASH_INFO_SUB_BLOCK_CONFIG:
            flash_sub_block_address = FLASH_START_ADDRESS + FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET;
        break;
//        case FLASH_INFO_SUB_BLOCK_STATUS:
//        break;
//        case FLASH_INFO_SUB_BLOCK_IMAGE:
//        break;
        default:
        break;
    }
    for (uint16_t iii = 0; iii < num_double_words; iii++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, flash_sub_block_address + iii, (uint64_t *)p_data);
    }
}


void flash_access_write_user_flash(void)
{
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, FLASH_START_ADDRESS + FLASH_USER_SPACE_START_ADDRESS, &g_count);
}


void flash_access_read_user_flash(void)
{

//    g_user_flash = (uint64_t)(FLASH_START_ADDRESS + FLASH_USER_SPACE_START_ADDRESS);
}


