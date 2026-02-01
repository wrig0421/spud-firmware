

#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "free_rtos_convenience.h"

void free_rtos_delay_ms(uint32_t time_ms)
{
	uint32_t ticks = time_ms / portTICK_PERIOD_MS;
	vTaskDelay(ticks);
}


void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char * pcTaskName )
{
    /* Check pcTaskName for the name of the offending task,
     * or pxCurrentTCB if pcTaskName has itself been corrupted. */
    ( void ) xTask;
    ( void ) pcTaskName;
}


bool free_rtos_scheduler_has_been_started(void)
{
	return (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) ? false : true;
}
