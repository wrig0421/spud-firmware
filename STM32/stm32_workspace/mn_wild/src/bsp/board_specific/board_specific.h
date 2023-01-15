// SRW

#if !defined(BOARD_SPECIFIC_H)
#define BOARD_SPECIFIC_H

#include "config.h"
#include "board_init_common.h"

#define MN_WILD_SIGN
#if defined(MN_WILD_SIGN)
#include "board_init_mn_wild/board_init_mn_wild.h"
#else
#error "Error - None or unknown board defined!"
#endif

#endif
