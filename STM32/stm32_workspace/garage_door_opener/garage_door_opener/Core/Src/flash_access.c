#include <stdint.h>
#include <string.h>
#include "limits.h"
#include "main.h"
#include "flash_access.h"


#define FLASH_ACCESS_ERASE_START_PAGE	255
#define NUM_PAGES_TO_ERASE	4


FLASH_EraseInitTypeDef flash_erase_struct =
{
		.TypeErase = FLASH_TYPEERASE_PAGES,
		.Banks = FLASH_BANK_1,
		.Page = NUM_PAGES_TO_ERASE,
		.NbPages = FLASH_ACCESS_ERASE_START_PAGE,
};


typedef struct
{
	uint32_t	gt_521fx_enroll_count;
	uint32_t	gt_521fx_last_id;
} g_flash_access_signature_page_t;


// local global variables
g_flash_access_signature_page_t g_flash_access_signature_page;

// local prototypes
void flash_read(uint32_t address, uint64_t *rx_buf, uint16_t num_words);
uint32_t flash_write(uint32_t address, uint64_t *data, uint32_t num_words);
uint32_t flash_get_page(uint32_t addr);


void flash_init(void)
{
	flash_read(FLASH_ACCESS_STORAGE_ADDR_START, (uint64_t *)&g_flash_access_signature_page, sizeof(g_flash_access_signature_page_t));
	if (UINT32_MAX == g_flash_access_signature_page.gt_521fx_enroll_count) flash_access_clear_signature_page();
}


void flash_access_clear_signature_page(void)
{
	memset(&g_flash_access_signature_page, 0, sizeof(g_flash_access_signature_page_t));
	flash_write(FLASH_ACCESS_STORAGE_ADDR_START, (uint64_t *)&g_flash_access_signature_page, sizeof(g_flash_access_signature_page_t));
}


void flash_access_enroll_update(void)
{
	g_flash_access_signature_page.gt_521fx_last_id++;
	g_flash_access_signature_page.gt_521fx_enroll_count++;
	flash_write(FLASH_ACCESS_STORAGE_ADDR_START, (uint64_t *)&g_flash_access_signature_page, sizeof(g_flash_access_signature_page_t));
}


uint16_t flash_access_gt521fx_last_id(void)
{
	return g_flash_access_signature_page.gt_521fx_last_id;
}


void flash_access_gt521fx_remove_last_id(void)
{
	g_flash_access_signature_page.gt_521fx_last_id -= 1; // I don't care if starting at 1
	g_flash_access_signature_page.gt_521fx_enroll_count--;
	flash_write(FLASH_ACCESS_STORAGE_ADDR_START, (uint64_t *)&g_flash_access_signature_page, sizeof(g_flash_access_signature_page_t));
}


void flash_access_gt521fx_reset_id_count(void)
{
	g_flash_access_signature_page.gt_521fx_last_id = 0; // I don't care if starting at 1
	g_flash_access_signature_page.gt_521fx_enroll_count = 0;
	flash_write(FLASH_ACCESS_STORAGE_ADDR_START, (uint64_t *)&g_flash_access_signature_page, sizeof(g_flash_access_signature_page_t));

}


uint16_t flash_access_gt521fx_enroll_count(void)
{
	return g_flash_access_signature_page.gt_521fx_enroll_count;
}


uint32_t flash_get_page(uint32_t addr)
{
	uint32_t page = 0;
	if (addr < (FLASH_BASE + FLASH_BANK_SIZE)) page = (addr - FLASH_BASE) / FLASH_PAGE_SIZE;
	else page = (addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
	return page;
}


void flash_read(uint32_t address, uint64_t *rx_buf, uint16_t num_words)
{
	while(1)
	{
		*rx_buf = *(__IO uint64_t *)address;
		address += 4;
		rx_buf++;
		if (!(num_words--)) break;
	}
}


uint32_t flash_write(uint32_t address, uint64_t *data, uint32_t num_dbls)
{
	static FLASH_EraseInitTypeDef erase_init_struct;
	uint32_t page_error;

	if ((address + (sizeof(uint64_t) * num_dbls)) > FLASH_ACCESS_STORAGE_ADDR_END) return -1; // error not enough allocated space
	HAL_FLASH_Unlock();

	uint32_t start_page = flash_get_page(address);
	uint32_t end_page = flash_get_page(address + num_dbls * 8);

	erase_init_struct.Banks = FLASH_BANK_1;
	erase_init_struct.TypeErase = FLASH_TYPEERASE_PAGES;
	erase_init_struct.Page = start_page;
	erase_init_struct.NbPages = ((end_page - start_page) / FLASH_PAGE_SIZE) + 1;

	if (HAL_OK != HAL_FLASHEx_Erase(&erase_init_struct, &page_error)) return HAL_FLASH_GetError();
	for (uint32_t i = 0; i < num_dbls; i++)
	{
		if (HAL_OK == HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data[i])) address += 8;
		else return HAL_FLASH_GetError();
	}
	HAL_FLASH_Lock();
	return 0;
}


void flash_erase(void)
{
	uint32_t page_error = 0;
	HAL_FLASHEx_Erase(&flash_erase_struct, &page_error);
}
