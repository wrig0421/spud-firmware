

#if !defined(TIMER_CONFIG_HAL_SPECIFIC_H)
#define TIMER_CONFIG_HAL_SPECIFIC_H

#include "config.h"
#include "board_init_common.h"

#if defined(BOARD_SPUDGLO_BABY_DINOSAUR_V1)
#include "board_spudglo_baby_dinosaur_v1_timer_config.h"
#else
#error "Error - None or unknown board defined!"
#endif

#endif
