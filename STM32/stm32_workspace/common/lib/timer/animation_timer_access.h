// SRW

#ifndef ANIMATION_TIMER_ACCESS_H
#define ANIMATION_TIMER_ACCESS_H

#include "FreeRTOS.h"
#include "timers.h"

#define LED_CTRL_MASTER_STATE_TIME_MS   120000


void animation_timer_access_callback(TimerHandle_t h_timer);
void animation_timer_access_reset(void);

#endif
