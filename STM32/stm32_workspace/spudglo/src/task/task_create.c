// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "animate_led.h"
#include "task_button_press.h"
#include "task_dma_transfer.h"
#include "task_led_ctrl.h"
#include "task_create.h"

typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;

osThreadId_t g_led_strip_1_ctrl_handle;
osThreadId_t g_led_strip_2_ctrl_handle;
osThreadId_t g_led_strip_3_ctrl_handle;

osThreadId_t g_led_ctrl_handle;
osThreadId_t g_dma_transfer_handle;
osThreadId_t g_button_press_handle;

uint32_t g_led_strip_1_ctrl_stack[512];
uint32_t g_led_strip_2_ctrl_stack[512];
uint32_t g_led_strip_3_ctrl_stack[512];

uint32_t g_dma_transfer_stack[512];
uint32_t g_led_ctrl_stack[512];
uint32_t g_button_press_stack[512];

osStaticThreadDef_t g_led_strip_1_ctrl_control_block;
osStaticThreadDef_t g_led_strip_2_ctrl_control_block;
osStaticThreadDef_t g_led_strip_3_ctrl_control_block;

osStaticThreadDef_t g_dma_transfer_control_block;
osStaticThreadDef_t g_led_ctrl_control_block;
osStaticThreadDef_t g_button_press_control_block;;

bool g_tasks_running = false;
const osThreadAttr_t g_task_button_press_attributes =
{
    .name = "task_button_press",
    .stack_mem = &g_button_press_stack[0],
    .stack_size = sizeof(g_button_press_stack),
    .cb_mem = &g_button_press_control_block,
    .cb_size = sizeof(g_button_press_control_block),
    .priority = (osPriority_t) osPriorityHigh,
};


const osThreadAttr_t g_task_led_ctrl_attributes =
{
	.name = "task_led_ctrl",
	.stack_mem = &g_led_ctrl_stack[0],
	.stack_size = sizeof(g_led_ctrl_stack),
	.cb_mem = &g_led_ctrl_control_block,
	.cb_size = sizeof(g_led_ctrl_control_block),
	.priority = (osPriority_t) osPriorityHigh,
};


const osThreadAttr_t g_task_strip_1_led_ctrl_attributes =
{
    .name = "task_strip_1_led_ctrl",
    .stack_mem = &g_led_strip_1_ctrl_stack[0],
    .stack_size = sizeof(g_led_strip_1_ctrl_stack),
    .cb_mem = &g_led_strip_1_ctrl_control_block,
    .cb_size = sizeof(g_led_strip_1_ctrl_control_block),
    .priority = (osPriority_t) osPriorityNormal,
};


const osThreadAttr_t g_task_strip_2_led_ctrl_attributes =
{
    .name = "task_strip_2_led_ctrl",
    .stack_mem = &g_led_strip_2_ctrl_stack[0],
    .stack_size = sizeof(g_led_strip_2_ctrl_stack),
    .cb_mem = &g_led_strip_2_ctrl_control_block,
    .cb_size = sizeof(g_led_strip_2_ctrl_control_block),
    .priority = (osPriority_t) osPriorityNormal,
};


const osThreadAttr_t g_task_strip_3_led_ctrl_attributes =
{
    .name = "task_strip_3_led_ctrl",
    .stack_mem = &g_led_strip_3_ctrl_stack[0],
    .stack_size = sizeof(g_led_strip_3_ctrl_stack),
    .cb_mem = &g_led_strip_3_ctrl_control_block,
    .cb_size = sizeof(g_led_strip_3_ctrl_control_block),
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
	g_button_press_handle = osThreadNew(task_button_press, NULL, &g_task_button_press_attributes);
    //g_dma_transfer_handle = osThreadNew(task_dma_transfer, NULL, &g_task_dma_transfer_attributes);
    //g_led_strip_1_ctrl_handle = osThreadNew(task_led_ctrl_strip_one, NULL, &g_task_strip_1_led_ctrl_attributes);
    g_tasks_running = true; // technically will be running after task scheduler started
}
