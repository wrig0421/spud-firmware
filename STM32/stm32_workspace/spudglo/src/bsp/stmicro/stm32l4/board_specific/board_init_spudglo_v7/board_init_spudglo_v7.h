// SRW
#include "config.h"
#if !defined(BOARD_INIT_SPUD_GLO_V7_H)
#define BOARD_INIT_SPUD_GLO_V7_H

void board_init_specific(void);
void board_init_specific_power_cycle_level_shifter(void);
void board_init_specific_esp8266_power_enable(void);
void board_init_specific_esp8266_power_disable(void);
void board_init_specific_esp8266_reset_assert(void);
void board_init_specific_esp8266_reset_deassert(void);

void board_init_specific_esp8266_uart_boot_enable(void);
void board_init_specific_esp8266_uart_boot_disable(void);
void board_init_peripheral_setup(void);

bool board_init_specific_vbus_is_present(void);

#endif
