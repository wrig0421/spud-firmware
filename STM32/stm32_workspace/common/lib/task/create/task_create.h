
//SRW
#if !defined(TASK_CREATE_H)
#define TASK_CREATE_H
#include "FreeRTOS.h"
#include "task.h"

#include "FreeRTOSConfig.h"

#define TASK_CREATE_STACK_SIZE_STANDARD		(2 * configMINIMAL_STACK_SIZE)

typedef enum
{
	TASK_LIST_LED_STRIP_SYNC = 0,
	TASK_LIST_LED_STRIP_1,
	TASK_LIST_LED_STRIP_2,
	TASK_LIST_LED_STRIP_3,
	TASK_LIST_BUTTON_PRESS,
	TASK_LIST_DMA_XFER,
	NUM_TASKS
} task_list_e;

void task_create(void);

#endif
