#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task_dma_transfer.h"

void task_dma_transfer(void *argument)
{
	while (1)
	{
		osDelay(1000);
	}
}
