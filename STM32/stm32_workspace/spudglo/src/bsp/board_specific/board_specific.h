// SRW

#if !defined(BOARD_SPECIFIC_H)
#define BOARD_SPECIFIC_H

#include "config.h"
#include "board_init.h"

#if defined(BOARD_SPUD_GLO_V3)
#include "board_init_spudglo_v3/gpio_config_spudglo_v3.h"
#elif defined(BOARD_SPUD_GLO_V4)
#include "board_init_spudglo_v4/gpio_config_spudglo_v4.h"
#elif defined(BOARD_SPUD_GLO_V5)
#include "board_init_spudglo_v5/gpio_config_spudglo_v5.h"
#else
#error "Error - None or unknown board defined!"
#endif

#endif
