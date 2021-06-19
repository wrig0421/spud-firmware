
#include "flash_access.h"

#include "main.h"
#define FLASH_ACCESS_ERASE_START_PAGE	255
#define NUM_PAGES_TO_ERASE	4


FLASH_EraseInitTypeDef flash_erase_struct =
{
		.TypeErase = FLASH_TYPEERASE_PAGES,
		.Banks = FLASH_BANK_1,
		.Page = NUM_PAGES_TO_ERASE,
		.NbPages = FLASH_ACCESS_ERASE_START_PAGE,
};


void flash_erase(void)
{
	uint32_t page_error = 0;
	HAL_FLASHEx_Erase(&flash_erase_struct, &page_error);


}
