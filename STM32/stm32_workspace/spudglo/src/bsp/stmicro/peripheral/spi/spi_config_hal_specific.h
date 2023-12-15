

#if !defined(UART_CONFIG_HAL_SPECIFIC_H)
#define UART_CONFIG_HAL_SPECIFIC_H

#include "config.h"
#include "board_common.h"
#include "board_init_common.h"

#if defined(BOARD_SPUDGLO_V5P0)
#include "board_spudglo_v5_uart_config.h"
#else
#error "Error - None or unknown board defined!"
#endif

#endif
