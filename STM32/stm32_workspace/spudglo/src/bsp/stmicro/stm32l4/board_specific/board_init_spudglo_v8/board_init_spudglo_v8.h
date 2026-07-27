// SRW
#include "config.h"
#if !defined(BOARD_INIT_SPUD_GLO_V8_H)
#define BOARD_INIT_SPUD_GLO_V8_H

void board_init_specific(void);
void board_init_specific_power_cycle_level_shifter(void);
void board_init_peripheral_setup(void);

bool board_init_specific_vbus_is_present(void);

#endif
