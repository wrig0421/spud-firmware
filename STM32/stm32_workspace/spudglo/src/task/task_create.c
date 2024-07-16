// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "FreeRTOS.h"
#include "task.h"


#include "FreeRTOSConfig.h"
#include "led_animate.h"
#include "task_button_press.h"
#include "task_dma_transfer.h"
#include "task_led_ctrl.h"
#include "task_create.h"


#define TASK_CREATE_STACK_SIZE_STANDARD		(2 * configMINIMAL_STACK_SIZE)

TaskHandle_t 	g_led_strip_1_ctrl_handle;
TaskHandle_t 	g_led_strip_2_ctrl_handle;
TaskHandle_t 	g_led_strip_3_ctrl_handle;
TaskHandle_t 	g_led_strip_sync_ctrl_handle;
TaskHandle_t 	g_button_press_handle;

StaticTask_t	g_task_led_strip_1_buffer;
StaticTask_t	g_task_led_strip_2_buffer;
StaticTask_t	g_task_led_strip_3_buffer;
StaticTask_t	g_task_led_sync_buffer;
StaticTask_t	g_button_press_buffer;

StackType_t		g_task_led_strip_1_stack[TASK_CREATE_STACK_SIZE_STANDARD];
StackType_t		g_task_led_strip_2_stack[TASK_CREATE_STACK_SIZE_STANDARD];
StackType_t		g_task_led_strip_3_stack[TASK_CREATE_STACK_SIZE_STANDARD];
StackType_t		g_task_led_sync_stack[TASK_CREATE_STACK_SIZE_STANDARD];

StackType_t		g_button_press_stack[TASK_CREATE_STACK_SIZE_STANDARD];

//#if defined(ENABLE_LED_STRIP_SYNC)
//
// 	// control is single threaded for this case
//	osThreadId_t 			g_led_strip_sync_ctrl_handle;
//	uint32_t 				g_led_strip_sync_ctrl_stack[TASK_CREATE_STACK_SIZE_STANDARD];
//	osStaticThreadDef_t 	g_led_strip_sync_ctrl_block;
//	const osThreadAttr_t 	g_task_led_sync_ctrl_attributes =
//	{
//		.name = 			"task_led_sync_ctrl",
//		.stack_mem = 		&g_led_strip_sync_ctrl_stack[0],
//		.stack_size = 		sizeof(g_led_strip_sync_ctrl_stack),
//		.cb_mem = 			&g_led_strip_sync_ctrl_block,
//		.cb_size = 			sizeof(g_led_strip_sync_ctrl_block),
//		.priority = 		(osPriority_t) osPriorityNormal,
//	};
//#else
//#	if defined(ENABLE_STRIP_1)
//		osThreadId_t 			g_led_strip_1_ctrl_handle;
//		uint32_t	 			g_led_strip_1_ctrl_stack[TASK_CREATE_STACK_SIZE_STANDARD];
//		osStaticThreadDef_t 	g_led_strip_1_ctrl_block;
//		const osThreadAttr_t 	g_task_led_1_ctrl_attributes =
//		{
//			.name = 			"task_led_1_ctrl",
//			.stack_mem = 		&g_led_strip_1_ctrl_stack[0],
//			.stack_size = 		sizeof(g_led_strip_1_ctrl_stack),
//			.cb_mem = 			&g_led_strip_1_ctrl_block,
//			.cb_size = 			sizeof(g_led_strip_1_ctrl_block),
//			.priority = 		(osPriority_t) osPriorityNormal,
//		};
//#	endif
//#	if defined(ENABLE_STRIP_2)
//		osThreadId_t 			g_led_strip_2_ctrl_handle;
//		uint32_t	 			g_led_strip_2_ctrl_stack[TASK_CREATE_STACK_SIZE_STANDARD];
//		osStaticThreadDef_t 	g_led_strip_2_ctrl_block;
//		const osThreadAttr_t 	g_task_led_2_ctrl_attributes =
//		{
//			.name = 			"task_led_2_ctrl",
//			.stack_mem = 		&g_led_strip_2_ctrl_stack[0],
//			.stack_size = 		sizeof(g_led_strip_2_ctrl_stack),
//			.cb_mem = 			&g_led_strip_2_ctrl_block,
//			.cb_size = 			sizeof(g_led_strip_2_ctrl_block),
//			.priority = 		(osPriority_t) osPriorityNormal,
//		};
//#	endif
//#	if defined(ENABLE_STRIP_3)
//		osThreadId_t 			g_led_strip_3_ctrl_handle;
//		uint32_t	 			g_led_strip_3_ctrl_stack[TASK_CREATE_STACK_SIZE_STANDARD];
//		osStaticThreadDef_t 	g_led_strip_3_ctrl_block;
//		const osThreadAttr_t 	g_task_led_3_ctrl_attributes =
//		{
//			.name = 			"task_led_3_ctrl",
//			.stack_mem = 		&g_led_strip_3_ctrl_stack[0],
//			.stack_size = 		sizeof(g_led_strip_3_ctrl_stack),
//			.cb_mem = 			&g_led_strip_3_ctrl_block,
//			.cb_size = 			sizeof(g_led_strip_3_ctrl_block),
//			.priority = 		(osPriority_t) osPriorityNormal,
//		};
//#	endif
//#endif


//osThreadId_t g_dma_transfer_handle;
//osThreadId_t g_button_press_handle;
//uint32_t g_dma_transfer_stack[512];
//uint32_t g_button_press_stack[512];
//osStaticThreadDef_t g_dma_transfer_control_block;
//osStaticThreadDef_t g_button_press_control_block;;

bool g_tasks_running = false;

void task_create(void)
{
//    osKernelInitialize();

#	if defined(ENABLE_LED_STRIP_SYNC)

    	g_led_strip_sync_ctrl_handle = xTaskCreateStatic(task_led_sync_ctrl, "task_strip_sync", TASK_CREATE_STACK_SIZE_STANDARD,
														NULL, tskIDLE_PRIORITY, g_task_led_sync_stack, &g_task_led_sync_buffer);

#	else
#		if (1 == NUM_ACTIVE_STRIPS)

			g_led_strip_1_ctrl_handle = xTaskCreateStatic(task_led_1_ctrl, "task_strip_1", TASK_CREATE_STACK_SIZE_STANDARD,
															(void *) 1, tskIDLE_PRIORITY, g_task_led_strip_1_stack, &g_task_led_strip_1_buffer);

#		elif (2 == NUM_ACTIVE_STRIPS)

			g_led_strip_1_ctrl_handle = xTaskCreateStatic(task_led_1_ctrl, "task_strip_1", TASK_CREATE_STACK_SIZE_STANDARD,
															(void *) 1, tskIDLE_PRIORITY, g_task_led_strip_1_stack, &g_task_led_strip_1_buffer);
			g_led_strip_2_ctrl_handle = xTaskCreateStatic(task_led_2_ctrl, "task_strip_2", TASK_CREATE_STACK_SIZE_STANDARD,
															(void *) 1, tskIDLE_PRIORITY, g_task_led_strip_2_stack, &g_task_led_strip_2_buffer);

#		elif (3 == NUM_ACTIVE_STRIPS)

			g_led_strip_1_ctrl_handle = xTaskCreateStatic(task_led_1_ctrl, "task_strip_1", TASK_CREATE_STACK_SIZE_STANDARD,
															(void *) 1, tskIDLE_PRIORITY, g_task_led_strip_1_stack, &g_task_led_strip_1_buffer);
			g_led_strip_2_ctrl_handle = xTaskCreateStatic(task_led_2_ctrl, "task_strip_2", TASK_CREATE_STACK_SIZE_STANDARD,
															(void *) 1, tskIDLE_PRIORITY, g_task_led_strip_2_stack, &g_task_led_strip_2_buffer);
			g_led_strip_3_ctrl_handle = xTaskCreateStatic(task_led_3_ctrl, "task_strip_3", TASK_CREATE_STACK_SIZE_STANDARD,
															(void *) 1, tskIDLE_PRIORITY, g_task_led_strip_3_stack, &g_task_led_strip_3_buffer);

#		endif

#endif
	g_button_press_handle = xTaskCreateStatic(task_button_press, "task_button_press", TASK_CREATE_STACK_SIZE_STANDARD,
													NULL, tskIDLE_PRIORITY, g_button_press_stack, &g_button_press_buffer);

    //g_dma_transfer_handle = osThreadNew(task_dma_transfer, NULL, &g_task_dma_transfer_attributes);
    g_tasks_running = true; // technically will be running after task scheduler started
}
