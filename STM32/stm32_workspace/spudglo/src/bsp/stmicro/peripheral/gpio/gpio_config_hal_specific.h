

#if !defined(GPIO_CONFIG_HAL_SPECIFIC_H)
#define GPIO_CONFIG_HAL_SPECIFIC_H

#include "config.h"

#if defined(BOARD_SPUDGLO_V5P0)
#	include "board_init_spudglo_v5/peripheral/gpio/board_spudglo_v5_gpio_config.h"
#elif defined(BOARD_SPUDGLO_V4)
#	include "board_init_spudglo_v4/peripheral/gpio/board_spudglo_v4_gpio_config.h"
#else
#	error "Error - None or unknown board defined!"
#endif

#endif // GPIO_CONFIG_HAL_SPECIFIC_H
