// SRW

#if !defined(BOARD_SPECIFIC_H)
#define BOARD_SPECIFIC_H

#include "config.h"
#include "board_common.h"
#include "board_init_common.h"

#if defined(BOARD_SPUD_GLO_V3)
#	include "board_init_spudglo_v3/board_init_spudglo_v3.h"
#elif defined(BOARD_SPUDGLO_V4)
#	include "board_init_spudglo_v4/board_init_spudglo_v4.h"
#elif defined(BOARD_SPUDGLO_V5)
#	include "board_init_spudglo_v5/board_init_spudglo_v5.h"
#elif defined(BOARD_SPUDGLO_V6)
#	include "board_init_spudglo_v6/board_init_spudglo_v6.h"
#elif defined(BOARD_SPUDGLO_V7)
#	include "board_init_spudglo_v7/board_init_spudglo_v7.h"
#elif defined(BOARD_SPUDGLO_BUSINESS_CARD)
#	include "board_init_spudglo_business_card/board_init_spudglo_business_card.h"
#elif defined(BOARD_SPUDGLO_BABY_DINOSAUR_V1)
#	include "board_init_spudglo_baby_dinosaur_v1/board_init_spudglo_baby_dinosaur_v1.h"
#else
#	error "Error - None or unknown board defined!"
#endif

#endif
