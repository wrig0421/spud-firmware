// SRW

#ifndef TASK_MN_WILD_H
#define TASK_MN_WILD_H

#include "board_specific.h"


typedef enum
{
   TASK_MN_WILD_STATE_IDLE = 0,
   TASK_MN_WILD_STATE_ACTIVE
} task_mn_wild_state_e;


void task_mn_wild(void *argument);
task_mn_wild_state_e task_mn_wild_state(void);
void task_mn_wild_enter_idle(void);

#endif /* TASK_PIN_LEVEL_COUNT_H_ */
