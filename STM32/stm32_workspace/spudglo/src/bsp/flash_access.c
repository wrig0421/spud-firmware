// SRW
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "cmsis_os.h"
#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_flash.h"
#include "flash_info.h"
#include "flash_access.h"


bool gb_flash_write_done = true;
void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue)
{
	gb_flash_write_done = true;
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
    for (uint16_t iii = 0; iii < num_double_words; iii++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address + iii, *p_data);
    }
}


void flash_access_read_sector(void *p_data, flash_info_sub_block_t sub_block)
{
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


void flash_access_erase_slot(void)
{
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t page_error = 0;
    uint16_t num_double_words = (0x8020000 - FLASH_START_ADDRESS) / sizeof(uint64_t);

	uint32_t start_page_num = (0x8020000 - FLASH_START_ADDRESS)/ FLASH_PAGE_SIZE;
	uint32_t end_page_address = 0x8020000 + num_double_words;
	uint32_t end_page_num = (end_page_address - FLASH_START_ADDRESS) / FLASH_PAGE_SIZE;

	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Page        = start_page_num;
	EraseInitStruct.Banks       = FLASH_BANK_1;
	EraseInitStruct.NbPages     = ((end_page_num - start_page_num)) +1;

	HAL_FLASH_Unlock();

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &page_error) != HAL_OK) while (1);

	HAL_FLASH_Unlock();
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
    	while (!gb_flash_write_done) osDelay(1);
    	gb_flash_write_done = false;
    	HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, \
                        flash_sub_block_address + (iii * sizeof(uint64_t)), \
                        *(p_data + (iii)));
    }

    HAL_FLASH_Lock();
}

extern bool g_buffer_full;
uint64_t g_prog_flash_val = 9;
void flash_access_write_sector_with_address(uint64_t *p_data, uint32_t address)
{
//    static FLASH_EraseInitTypeDef EraseInitStruct;
    uint16_t num_double_words = 41000 / sizeof(uint64_t);

    //uint16_t num_double_words = FLASH_INFO_SUB_BLOCK_SECTOR_SIZE_BYTES / sizeof(uint64_t);
    uint32_t page_error = 0;

    uint32_t start_page_num = (address - FLASH_START_ADDRESS)/ FLASH_PAGE_SIZE;
    uint32_t end_page_address = address + num_double_words;
    uint32_t end_page_num = (end_page_address - FLASH_START_ADDRESS) / FLASH_PAGE_SIZE;

//    /* Fill EraseInit structure*/
//    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
//    EraseInitStruct.Page        = start_page_num;
//    EraseInitStruct.Banks       = FLASH_BANK_1;
//    EraseInitStruct.NbPages     = ((end_page_num - start_page_num)) +1;

    HAL_FLASH_Unlock();

//    if (HAL_FLASHEx_Erase(&EraseInitStruct, &page_error) != HAL_OK) while (1);
    uint64_t constructed_value = 0;
    uint64_t most_sig = 0;
    uint64_t least_sig = 0;
    for (uint16_t iii = 0; iii < num_double_words; iii++)
    {
//    	least_sig = (p_data[iii] & UINT32_MAX);
//    	most_sig = (p_data[iii] & (UINT64_MAX - UINT32_MAX)) >> 32;
//    	least_sig = __builtin_bswap32(least_sig);
//    	most_sig = __builtin_bswap32(most_sig);
//    	constructed_value = (most_sig << 32) | (least_sig);
    	//while (!gb_flash_write_done) osDelay(1);
		//gb_flash_write_done = false;
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, \
						address + (iii * sizeof(uint64_t)), \
						*(p_data + (iii)));
		if (g_buffer_full) while(1);
    }

    HAL_FLASH_Lock();
}
