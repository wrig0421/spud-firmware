

#if !defined(I2C_CONFIG_HAL_SPECIFIC_H)
#define I2C_CONFIG_HAL_SPECIFIC_H

#include "config.h"
#include "board_common.h"
#include "board_init_common.h"

#if defined(BOARD_SPUDGLO_V7P0)
#include "board_spudglo_v7_i2c_config.h"
#else
// Do nothing...no other boards have I2C access...
#endif

#endif
