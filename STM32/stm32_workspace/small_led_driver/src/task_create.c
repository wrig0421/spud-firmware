#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>
#include "task_create.h"
#include "color_led.h"
#include "animate_led.h"
#include "task_dma_transfer.h"
#include "FreeRTOS.h"

typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;

// local global variables
// task for handling the DMA transfers
// task for updating animations

osThreadId_t g_animate_led_handle;
osThreadId_t g_dma_transfer_handle;
uint32_t g_dma_transfer_stack[512];
uint32_t g_animate_led_stack[512];
osStaticThreadDef_t g_dma_transfer_control_block;
osStaticThreadDef_t g_animate_led_control_block;


const osThreadAttr_t g_task_dma_transfer_attributes =
{
	.name = "task_dma_transfer",
	.stack_mem = &g_dma_transfer_stack[0],
	.stack_size = sizeof(g_dma_transfer_stack),
	.cb_mem = &g_dma_transfer_control_block,
	.cb_size = sizeof(g_dma_transfer_control_block),
	.priority = (osPriority_t) osPriorityNormal,
};


const osThreadAttr_t g_task_animate_led_attributes =
{
	.name = "task_animate_led",
	.stack_mem = &g_animate_led_stack[0],
	.stack_size = sizeof(g_animate_led_stack),
	.cb_mem = &g_animate_led_control_block,
	.cb_size = sizeof(g_animate_led_control_block),
	.priority = (osPriority_t) osPriorityNormal,
};


void task_create(void)
{
	g_dma_transfer_handle = osThreadNew(task_dma_transfer, NULL, &g_task_dma_transfer_attributes);
	g_animate_led_handle = osThreadNew(task_animate_led, NULL, &g_task_animate_led_attributes);
}
