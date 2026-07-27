
//SRW
#if !defined(ANIMATION_TIMER_CREATE_H)
#define ANIMATION_TIMER_CREATE_H
#include "FreeRTOS.h"
#include "timers.h"

#include "FreeRTOSConfig.h"

void animation_timer_create(void);
void animation_timer_reset(void);

TimerHandle_t animation_timer_return_handle(void);

#endif // TIMER_CREATE_H
