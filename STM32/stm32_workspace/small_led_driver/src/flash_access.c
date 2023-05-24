// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_flash.h"
#include "flash_info.h"
#include "flash_access.h"

// stm32l4xx_hal_flash.h
//#define FLASH_PAGE_SIZE                    ((uint32_t)0x800)



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


void flash_access_write_to_flash(uint64_t address, uint64_t *p_data, uint16_t num_uint64_to_write)
{
    for (uint16_t iii = 0; iii < num_uint64_to_write; iii++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address + (iii * sizeof(uint64_t)), p_data);
    }
}


void flash_access_write_user_flash(void)
{
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, FLASH_START_ADDRESS + FLASH_USER_SPACE_START_ADDRESS, &g_count);
}



void flash_access_read_user_flash(void)
{

    g_user_flash = (uint64_t)(FLASH_START_ADDRESS + FLASH_USER_SPACE_START_ADDRESS);
}


void flash_access_write(uint64_t address, void *p_data, uint16_t num_bytes);


//void flash_access_read(uint64_t address, void *p_data, uint16_t num_bytes)
//{
//    for (uint16_t iii = 0; iii < num_bytes; iii++)
//    {
//        p_data[iii] = *(address + iii);
//        //p_data[iii] = *(__IO uint32_t *)(address + iii);
//    }
//}






