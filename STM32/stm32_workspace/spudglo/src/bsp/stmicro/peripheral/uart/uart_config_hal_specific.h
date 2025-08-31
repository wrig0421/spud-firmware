

#if !defined(UART_CONFIG_HAL_SPECIFIC_H)
#define UART_CONFIG_HAL_SPECIFIC_H

#include "config.h"
#include "board_init_common.h"

#if defined(BOARD_SPUDGLO_V4)
//#include "board_spudglo_v4_uart_config.h"
#elif defined(BOARD_SPUDGLO_V5)
#	include "board_spudglo_v5_uart_config.h"
#elif defined(BOARD_SPUDGLO_V6)
#	include "board_spudglo_v6_uart_config.h"
#elif defined(BOARD_SPUDGLO_V7)
#	include "board_spudglo_v7_uart_config.h"
#elif defined(BOARD_SPUDGLO_BUSINESS_CARD)
	// no UART on SPUDGLO BUSINESS CARD
#elif defined(BOARD_SPUDGLO_BABY_DINOSAUR_V1)
#	include "board_spudglo_baby_dinosaur_v1_uart_config.h"
#else
#error "Error - None or unknown board defined!"
#endif

#endif
