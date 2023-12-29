
//SRW
#if !defined(FLASH_ACCESS_H)
#define FLASH_ACCESS_H
#include "flash_info.h"
#include <stdint.h>

void flash_access_init(void);
void flash_access_increment_count(void);
void flash_access_erase_user_flash(void);
void flash_access_read_flash(void *p_data, void *address, uint16_t num_bytes);
void flash_access_write_to_flash(uint64_t *p_data, uint64_t address, uint16_t num_bytes);
void flash_access_read_sector(void *p_data, flash_info_sub_block_t sub_block);
void flash_access_write_sector(uint64_t *p_data, flash_info_sub_block_t sub_block);
void flash_access_write_sector_with_address(uint64_t *p_data, uint32_t address);
void flash_access_erase_slot(void);

#endif
