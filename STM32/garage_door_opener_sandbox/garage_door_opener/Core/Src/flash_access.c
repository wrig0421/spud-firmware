
#include <stdint.h>
#include <string.h>
#include "limits.h"
#include "main.h"
#include "flash_access.h"


#define FLASH_ACCESS_ERASE_START_PAGE	255
#define NUM_PAGES_TO_ERASE	4


typedef struct
{
	uint32_t	gt_521fx_enroll_count;
	uint32_t	gt_521fx_last_id;
} flash_access_signature_page_t;

/*
typedef struct
{
	union
	{
		flash_access_signature_page_params_t params;
		//uint32_t flat_data[(sizeof(flash_access_signature_page_params_t)) / sizeof(uint32_t)];
		uint8_t flat_data[(sizeof(flash_access_signature_page_params_t))];
	};
} flash_access_signature_page_t;
*/

flash_access_signature_page_t flash_access_signature_page;

FLASH_EraseInitTypeDef flash_erase_struct =
{
		.TypeErase = FLASH_TYPEERASE_PAGES,
		.Banks = FLASH_BANK_1,
		.Page = NUM_PAGES_TO_ERASE,
		.NbPages = FLASH_ACCESS_ERASE_START_PAGE,
};


void flash_read(uint32_t address, uint64_t *rx_buf, uint16_t num_words);
uint32_t flash_write(uint32_t address, uint64_t *data, uint32_t num_words);
uint32_t flash_get_page(uint32_t addr);


void flash_init(void)
{
	uint32_t buf;
	uint32_t start_address = FLASH_ACCESS_STORAGE_ADDR_START;
	uint32_t end_address = FLASH_ACCESS_STORAGE_ADDR_END;
	uint32_t num_pages = FLASH_ACCESS_STORAGE_SIZE / FLASH_PAGE_SIZE;
	flash_read(FLASH_ACCESS_STORAGE_ADDR_START, (uint32_t *)&flash_access_signature_page, sizeof(flash_access_signature_page_t));
	//flash_read(FLASH_ACCESS_STORAGE_ADDR_START, &buf, 1);
	if (UINT32_MAX == flash_access_signature_page.gt_521fx_enroll_count) // uinitialized
	{
		flash_access_clear_signature_page();
	}
}


void flash_access_clear_signature_page(void)
{
	memset(&flash_access_signature_page, 0, sizeof(flash_access_signature_page_t));
	flash_write(FLASH_ACCESS_STORAGE_ADDR_START, (uint64_t *)&flash_access_signature_page, sizeof(flash_access_signature_page_t));
}


void flash_access_enroll_update(void)
{
	uint32_t start_address = FLASH_ACCESS_STORAGE_ADDR_START;
	uint32_t end_address = FLASH_ACCESS_STORAGE_ADDR_END;
	flash_access_signature_page.gt_521fx_last_id++;
	flash_access_signature_page.gt_521fx_enroll_count++;
	flash_write(FLASH_ACCESS_STORAGE_ADDR_START, (uint64_t *)&flash_access_signature_page, sizeof(flash_access_signature_page_t));
}


uint16_t flash_access_gt521fx_last_id(void)
{
	return flash_access_signature_page.gt_521fx_last_id;
}


uint16_t flash_access_gt521fx_enroll_count(void)
{
	return flash_access_signature_page.gt_521fx_enroll_count;
}


uint32_t flash_get_page(uint32_t addr)
{
	uint32_t page = 0;
	if (addr < (FLASH_BASE + FLASH_BANK_SIZE))
	{
		page = (addr - FLASH_BASE) / FLASH_PAGE_SIZE;
	}
	else
	{
		page = (addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
	}
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

	if ((address + (sizeof(uint64_t) * num_dbls)) > FLASH_ACCESS_STORAGE_ADDR_END)
	{
		return -1; // error not enough allocated space
	}
	HAL_FLASH_Unlock();

	uint32_t start_page = flash_get_page(address);
	uint32_t end_page = flash_get_page(address + num_dbls * 8);

	erase_init_struct.Banks = FLASH_BANK_1;
	erase_init_struct.TypeErase = FLASH_TYPEERASE_PAGES;
	erase_init_struct.Page = start_page;
	erase_init_struct.NbPages = ((end_page - start_page) / FLASH_PAGE_SIZE) + 1;

	if (HAL_OK != HAL_FLASHEx_Erase(&erase_init_struct, &page_error))
	{
		return HAL_FLASH_GetError();
	}
	for (uint32_t i = 0; i < num_dbls; i++)
	{
		//FLASH_TYPEPROGRAM_WORD
		if (HAL_OK == HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data[i]))
		{
			address += 8;
		}
		else
		{
			return HAL_FLASH_GetError();
		}
	}
	HAL_FLASH_Lock();
	return 0;
}


void flash_erase(void)
{
	uint32_t page_error = 0;
	HAL_FLASHEx_Erase(&flash_erase_struct, &page_error);
}
