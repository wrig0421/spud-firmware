#include <stdint.h>
#include <stdlib.h>
#include "numbers.h"

uint32_t random_num(uint32_t min, uint32_t max)
{
   return min + rand() % (max + 1 - min);
}
