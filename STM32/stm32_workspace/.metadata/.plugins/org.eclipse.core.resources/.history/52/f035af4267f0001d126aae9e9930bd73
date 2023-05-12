/*
 * semaphore.c
 *
 *  Created on: Nov 12, 2022
 *      Author: spud
 */
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "semphr.h"


SemaphoreHandle_t g_dma_transfer_semaphore;
StaticSemaphore_t g_dma_transfer_semaphore_buffer;

SemaphoreHandle_t g_dma_fill_semaphore;
StaticSemaphore_t g_dma_fill_semaphore_buffer;


void semaphore_create(void)
{
    g_dma_transfer_semaphore = xSemaphoreCreateBinaryStatic(&g_dma_transfer_semaphore_buffer);
    g_dma_fill_semaphore = xSemaphoreCreateBinaryStatic(&g_dma_fill_semaphore_buffer);
    xSemaphoreGive(g_dma_transfer_semaphore);
    xSemaphoreGive(g_dma_fill_semaphore);
}
