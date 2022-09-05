/*
 * board_specific.h
 *
 *  Created on: Aug 6, 2022
 *      Author: splat
 */

#ifndef SRC_BSP_BOARD_SPECIFIC_BOARD_SPECIFIC_H_
#define SRC_BSP_BOARD_SPECIFIC_BOARD_SPECIFIC_H_

#include "config.h"
#include "board_init_common.h"

#if defined(BOARD_SPUD_GLO_V1)
#include "board_init_spud_glo_v1/board_init_spud_glo_v1.h"
#elif defined(BOARD_SPUD_GLO_V2)
#include "board_init_spud_glo_v2/board_init_spud_glo_v2.h"
#elif defined(BOARD_SPUD_GLO_V3)
#include "board_init_spud_glo_v3/board_init_spud_glo_v3.h"
#else
#error "Error - None or unknown board defined!"
#endif

#endif /* SRC_BSP_BOARD_SPECIFIC_BOARD_SPECIFIC_H_ */
