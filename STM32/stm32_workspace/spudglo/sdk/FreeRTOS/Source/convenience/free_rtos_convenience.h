#if !defined(FREE_RTOS_CONVENIENCE_H)
#	define FREE_RTOS_CONVENIENCE_H

#include <stdbool.h>

void free_rtos_delay_ms(uint32_t time_ms);
bool free_rtos_scheduler_has_been_started(void);

#endif
