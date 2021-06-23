/*
 * Based on ssd1306-stm32HAL by Olivier Van den Eede(4ilo)
 */

#if !defined(FLASH_ACCESS_H)

#define FLASH_ACCESS_H


//#define FLASH_ACCESS_STORAGE_ADDR_START	(0x08038000)
//#define FLASH_ACCESS_STORAGE_ADDR_END	(0x08040000)
//FLASH_PAGE_SIZE
#define FLASH_ACCESS_STORAGE_ADDR_BASE	(0x08000000)
#define FLASH_ACCESS_STORAGE_ADDR_END	(0x0803FFFF)
#define FLASH_ACCESS_STORAGE_ADDR_START ((FLASH_ACCESS_STORAGE_ADDR_END - (FLASH_PAGE_SIZE * (8)) + 1))
//#define FLASH_ACCESS_STORAGE_ADDR_START (FLASH_ACCESS_STORAGE_ADDR_BASE + (FLASH_PAGE_SIZE * (120)))
#define FLASH_ACCESS_STORAGE_SIZE		(FLASH_ACCESS_STORAGE_ADDR_END - FLASH_ACCESS_STORAGE_ADDR_START)

void flash_access_enroll_update(void);
void flash_access_clear_signature_page(void);
uint16_t flash_access_gt521fx_last_id(void);
void flash_init(void);
void flash_access_gt521fx_reset_id_count(void);
void flash_access_gt521fx_remove_last_id(void);

#endif

