#if !defined(NUMBERS_H)
#define NUMBERS_H

uint32_t random_num(uint32_t min, uint32_t max)
{
   return min + rand() % (max + 1 - min);
}

#endif
