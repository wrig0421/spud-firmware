// SRW

#if !defined(RNG_ACCESS_HAL_H)
#define RNG_ACCESS_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include "rng_config_hal.h"


void rng_access_hal_generate_random_number(void);
uint32_t rng_access_hal_read_random_number(void);
uint32_t rng_access_hal_read_and_generate_random_number(void);


#endif
