// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "FreeRTOSConfig.h"
#include "led_animate.h"
#include "task_button_press.h"
#include "task_dma_transfer.h"
#include "task_led_ctrl.h"
#include "task_create.h"

typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;

#define TASK_CREATE_STACK_SIZE_STANDARD		(8 * configMINIMAL_STACK_SIZE)

//typedef struct
//{
//	osThreadId_t			task_ctrl_handle;
//	uint32_t 				task_ctrl_stack[TASK_CREATE_STACK_SIZE_STANDARD];
//	osStaticThreadDef_t		task_ctrl_block;
//	const osThreadAttr_t	task_ctrl_attributes;
//} task_create_task_ctrl_t;
//
//
//// TODO add a define for the array size
//task_create_task_ctrl_t g_task_create_task_ctrl[NUM_TASKS] =
//{
//	[]
//};


#if defined(ENABLE_LED_STRIP_SYNC)

 	// control is single threaded for this case
	osThreadId_t 			g_led_strip_sync_ctrl_handle;
	uint32_t 				g_led_strip_sync_ctrl_stack[TASK_CREATE_STACK_SIZE_STANDARD];
	osStaticThreadDef_t 	g_led_strip_sync_ctrl_block;
	const osThreadAttr_t 	g_task_led_sync_ctrl_attributes =
	{
		.name = 			"task_led_sync_ctrl",
		.stack_mem = 		&g_led_strip_sync_ctrl_stack[0],
		.stack_size = 		sizeof(g_led_strip_sync_ctrl_stack),
		.cb_mem = 			&g_led_strip_sync_ctrl_block,
		.cb_size = 			sizeof(g_led_strip_sync_ctrl_block),
		.priority = 		(osPriority_t) osPriorityNormal,
	};
#else
#	if defined(ENABLE_STRIP_1)
		osThreadId_t 			g_led_strip_1_ctrl_handle;
		uint32_t	 			g_led_strip_1_ctrl_stack[TASK_CREATE_STACK_SIZE_STANDARD];
		osStaticThreadDef_t 	g_led_strip_1_ctrl_block;
		const osThreadAttr_t 	g_task_led_1_ctrl_attributes =
		{
			.name = 			"task_led_1_ctrl",
			.stack_mem = 		&g_led_strip_1_ctrl_stack[0],
			.stack_size = 		sizeof(g_led_strip_1_ctrl_stack),
			.cb_mem = 			&g_led_strip_1_ctrl_block,
			.cb_size = 			sizeof(g_led_strip_1_ctrl_block),
			.priority = 		(osPriority_t) osPriorityNormal,
		};
#	endif
#	if defined(ENABLE_STRIP_2)
		osThreadId_t 			g_led_strip_2_ctrl_handle;
		uint32_t	 			g_led_strip_2_ctrl_stack[TASK_CREATE_STACK_SIZE_STANDARD];
		osStaticThreadDef_t 	g_led_strip_2_ctrl_block;
		const osThreadAttr_t 	g_task_led_2_ctrl_attributes =
		{
			.name = 			"task_led_2_ctrl",
			.stack_mem = 		&g_led_strip_2_ctrl_stack[0],
			.stack_size = 		sizeof(g_led_strip_2_ctrl_stack),
			.cb_mem = 			&g_led_strip_2_ctrl_block,
			.cb_size = 			sizeof(g_led_strip_2_ctrl_block),
			.priority = 		(osPriority_t) osPriorityNormal,
		};
#	endif
#	if defined(ENABLE_STRIP_3)
		osThreadId_t 			g_led_strip_3_ctrl_handle;
		uint32_t	 			g_led_strip_3_ctrl_stack[TASK_CREATE_STACK_SIZE_STANDARD];
		osStaticThreadDef_t 	g_led_strip_3_ctrl_block;
		const osThreadAttr_t 	g_task_led_3_ctrl_attributes =
		{
			.name = 			"task_led_3_ctrl",
			.stack_mem = 		&g_led_strip_3_ctrl_stack[0],
			.stack_size = 		sizeof(g_led_strip_3_ctrl_stack),
			.cb_mem = 			&g_led_strip_3_ctrl_block,
			.cb_size = 			sizeof(g_led_strip_3_ctrl_block),
			.priority = 		(osPriority_t) osPriorityNormal,
		};
#	endif
#endif


osThreadId_t g_dma_transfer_handle;
osThreadId_t g_button_press_handle;


uint32_t g_dma_transfer_stack[512];
uint32_t g_button_press_stack[512];

osStaticThreadDef_t g_dma_transfer_control_block;
osStaticThreadDef_t g_button_press_control_block;;


bool g_tasks_running = false;
const osThreadAttr_t g_task_button_press_attributes =
{
    .name = "task_button_press",
    .stack_mem = &g_button_press_stack[0],
    .stack_size = sizeof(g_button_press_stack),
    .cb_mem = &g_button_press_control_block,
    .cb_size = sizeof(g_button_press_control_block),
    .priority = (osPriority_t) osPriorityNormal,
};


const osThreadAttr_t g_task_dma_transfer_attributes =
{
	.name = "task_dma_transfer",
	.stack_mem = &g_dma_transfer_stack[0],
	.stack_size = sizeof(g_dma_transfer_stack),
	.cb_mem = &g_dma_transfer_control_block,
	.cb_size = sizeof(g_dma_transfer_control_block),
	.priority = (osPriority_t) osPriorityNormal,
};


void task_create(void)
{
    osKernelInitialize();

#if defined(ENABLE_LED_STRIP_SYNC)

    g_led_strip_sync_ctrl_handle = osThreadNew(task_led_sync_ctrl, NULL, &g_task_led_sync_ctrl_attributes);

#else
#	if (1 == NUM_ACTIVE_STRIPS)

    	g_led_strip_1_ctrl_handle = osThreadNew(task_led_1_ctrl, NULL, &g_task_led_1_ctrl_attributes);

#	elif (2 == NUM_ACTIVE_STRIPS)

		g_led_strip_1_ctrl_handle = osThreadNew(task_led_1_ctrl, NULL, &g_task_led_1_ctrl_attributes);
		g_led_strip_2_ctrl_handle = osThreadNew(task_led_2_ctrl, NULL, &g_task_led_2_ctrl_attributes);

#	elif (3 == NUM_ACTIVE_STRIPS)

		g_led_strip_1_ctrl_handle = osThreadNew(task_led_1_ctrl, NULL, &g_task_led_1_ctrl_attributes);
		g_led_strip_2_ctrl_handle = osThreadNew(task_led_2_ctrl, NULL, &g_task_led_2_ctrl_attributes);
		g_led_strip_3_ctrl_handle = osThreadNew(task_led_3_ctrl, NULL, &g_task_led_3_ctrl_attributes);

#	endif
#endif

//	g_button_press_handle = osThreadNew(task_button_press, NULL, &g_task_button_press_attributes);
    //g_dma_transfer_handle = osThreadNew(task_dma_transfer, NULL, &g_task_dma_transfer_attributes);
    g_tasks_running = true; // technically will be running after task scheduler started
}
