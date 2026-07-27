/*
 * semaphore.c
 *
 *  Created on: Nov 12, 2022
 *      Author: spud
 */

#include "FreeRTOS.h"

#include "semphr.h"
#include "semaphore_access.h"

SemaphoreHandle_t g_dma_transfer_semaphore;
StaticSemaphore_t g_dma_transfer_semaphore_buffer;


void semaphore_create(void)
{
    g_dma_transfer_semaphore = xSemaphoreCreateBinaryStatic(&g_dma_transfer_semaphore_buffer);
    semaphore_give(SEMAPHORE_DMA_TRANSFER);
}


void semaphore_take(semaphore_assignment_e semaphore)
{
	switch (semaphore)
	{
		case SEMAPHORE_DMA_TRANSFER:
			xSemaphoreTake(g_dma_transfer_semaphore, portMAX_DELAY);
		break;
		default:
		break;
	}
}


void semaphore_give(semaphore_assignment_e semaphore)
{
	switch (semaphore)
	{
		case SEMAPHORE_DMA_TRANSFER:
			xSemaphoreGive(g_dma_transfer_semaphore);
		break;
		default:
		break;
	}
}


void semaphore_give_from_isr(semaphore_assignment_e semaphore)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	switch (semaphore)
	{
		case SEMAPHORE_DMA_TRANSFER:
			xSemaphoreGiveFromISR(g_dma_transfer_semaphore, &xHigherPriorityTaskWoken);
		break;
		default:
		break;
	}
}
