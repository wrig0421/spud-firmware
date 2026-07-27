/***********************************
 * @file   animate_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(RNG_ACCESS_H)
#define RNG_ACCESS_H
#include <stdint.h>

void rng_access_generate_random_number(void);
uint32_t rng_access_read_and_generate_random_number(void);

#endif
