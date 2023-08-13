// SRW
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_flash.h"
#include "flash_info.h"
#include "flash_access.h"


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
    for (uint16_t iii = 0; iii < num_double_words; iii++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address + iii, p_data);
    }
}


void flash_access_read_sector(void *p_data, flash_info_sub_block_t sub_block)
{
    uint32_t num_words = FLASH_INFO_SUB_BLOCK_SECTOR_SIZE_BYTES / sizeof(uint32_t);
    uint32_t flash_sub_block_address = 0;

    switch (sub_block)
    {
        case FLASH_INFO_SUB_BLOCK_CONFIG:
            flash_sub_block_address = FLASH_START_ADDRESS + FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET;
        break;
        default:
            while(1);
        break;
    }
    memcpy(p_data, (void *)flash_sub_block_address, 2048);
}


void flash_access_write_sector(uint64_t *p_data, flash_info_sub_block_t sub_block)
{
    static FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t flash_sub_block_address = 0;
    uint16_t num_double_words = FLASH_INFO_SUB_BLOCK_SECTOR_SIZE_BYTES / sizeof(uint64_t);
    uint32_t page_error = 0;
    switch (sub_block)
    {
        case FLASH_INFO_SUB_BLOCK_CONFIG:
            flash_sub_block_address = FLASH_START_ADDRESS + FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET;
        break;
        default:
            while(1);
        break;
    }

    uint32_t start_page_num = (flash_sub_block_address - FLASH_START_ADDRESS)/ FLASH_PAGE_SIZE;
    uint32_t end_page_address = flash_sub_block_address + num_double_words;
    uint32_t end_page_num = (end_page_address - FLASH_START_ADDRESS) / FLASH_PAGE_SIZE;

    /* Fill EraseInit structure*/
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Page        = start_page_num;
    EraseInitStruct.Banks       = FLASH_BANK_1;
    EraseInitStruct.NbPages     = ((end_page_num - start_page_num)) +1;

    HAL_FLASH_Unlock();

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &page_error) != HAL_OK) while (1);

    for (uint16_t iii = 0; iii < num_double_words; iii++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, \
                        flash_sub_block_address + (iii * sizeof(uint64_t)), \
                        *(p_data + (iii)));
    }

    HAL_FLASH_Lock();
}



