/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/


#include "rng_access_hal.h"
#include "rng_config_hal.h"
#include "rng_access.h"


void rng_access_generate_random_number(void)
{
    rng_access_hal_generate_random_number();
}


uint32_t rng_access_read_and_generate_random_number(void)
{
    return rng_access_hal_read_and_generate_random_number();
}
