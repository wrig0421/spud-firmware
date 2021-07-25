#include "main.h"
#include "cmsis_os.h"
#include "task_create.h"
#include "packet_queue.h"
#include "task_create.h"
#include "task_sensor_access.h"
#include "task_keypad_access.h"
#include "serial_com.h"
#include "FreeRTOS.h"

typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;

// local global variables
osThreadId_t g_task_sensor_rxHandle;
osThreadId_t g_task_sensor_txHandle;
osThreadId_t g_task_sensor_accHandle;
osThreadId_t g_task_keypad_accHandle;
uint32_t g_task_sensor_rxBuffer[ 512 ];
uint32_t g_task_sensor_txBuffer[ 512 ];
uint32_t g_task_sensor_accBuffer[ 512 ];
uint32_t g_task_keypad_accBuffer[ 512 ];
osStaticThreadDef_t g_task_sensor_rxControlBlock;
osStaticThreadDef_t g_task_sensor_txControlBlock;
osStaticThreadDef_t g_task_sensor_accControlBlock;
osStaticThreadDef_t g_task_keypad_accControlBlock;

const osThreadAttr_t g_task_sensor_rx_attributes = {
  .name = "task_sensor_rx",
  .stack_mem = &g_task_sensor_rxBuffer[0],
  .stack_size = sizeof(g_task_sensor_rxBuffer),
  .cb_mem = &g_task_sensor_rxControlBlock,
  .cb_size = sizeof(g_task_sensor_rxControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
const osThreadAttr_t g_task_sensor_tx_attributes = {
  .name = "task_sensor_tx",
  .stack_mem = &g_task_sensor_txBuffer[0],
  .stack_size = sizeof(g_task_sensor_txBuffer),
  .cb_mem = &g_task_sensor_txControlBlock,
  .cb_size = sizeof(g_task_sensor_txControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
const osThreadAttr_t g_task_sensor_acc_attributes = {
  .name = "task_sensor_acc",
  .stack_mem = &g_task_sensor_accBuffer[0],
  .stack_size = sizeof(g_task_sensor_accBuffer),
  .cb_mem = &g_task_sensor_accControlBlock,
  .cb_size = sizeof(g_task_sensor_accControlBlock),
  .priority = (osPriority_t) osPriorityLow,
};
const osThreadAttr_t g_task_keypad_acc_attributes = {
  .name = "task_keypad_acc",
  .stack_mem = &g_task_keypad_accBuffer[0],
  .stack_size = sizeof(g_task_keypad_accBuffer),
  .cb_mem = &g_task_keypad_accControlBlock,
  .cb_size = sizeof(g_task_keypad_accControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
  //.priority = (osPriority_t) osPriorityNormal1,
};


void task_create(void)
{
	packet_queue_init();
	serial_com_init_all();
	g_task_sensor_txHandle = osThreadNew(task_sensor_tx_entry, NULL, &g_task_sensor_tx_attributes);
	g_task_sensor_rxHandle = osThreadNew(sensor_rx_entry, NULL, &g_task_sensor_rx_attributes);
	g_task_sensor_accHandle = osThreadNew(task_sensor_access_entry, NULL, &g_task_sensor_acc_attributes);
	g_task_keypad_accHandle = osThreadNew(task_keypad_access_entry, NULL, &g_task_keypad_acc_attributes);
}
