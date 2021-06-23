
#include "main.h"
#include "cmsis_os.h"
#include "task_create.h"
#include "packet_queue.h"

#include "task_create.h"
#include "task_display_update.h"
#include "task_periodic.h"
#include "task_sensor_access.h"
#include "task_keypad_access.h"
#include "serial_com.h"

#include "FreeRTOS.h"

typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;

/* Definitions for task_sensor_rx */
osThreadId_t task_sensor_rxHandle;
uint32_t task_sensor_rxBuffer[ 128 ];
osStaticThreadDef_t task_sensor_rxControlBlock;
const osThreadAttr_t task_sensor_rx_attributes = {
  .name = "task_sensor_rx",
  .stack_mem = &task_sensor_rxBuffer[0],
  .stack_size = sizeof(task_sensor_rxBuffer),
  .cb_mem = &task_sensor_rxControlBlock,
  .cb_size = sizeof(task_sensor_rxControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task_sensor_tx */
osThreadId_t task_sensor_txHandle;
uint32_t task_sensor_txBuffer[ 128 ];
osStaticThreadDef_t task_sensor_txControlBlock;
const osThreadAttr_t task_sensor_tx_attributes = {
  .name = "task_sensor_tx",
  .stack_mem = &task_sensor_txBuffer[0],
  .stack_size = sizeof(task_sensor_txBuffer),
  .cb_mem = &task_sensor_txControlBlock,
  .cb_size = sizeof(task_sensor_txControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task_sensor_acc */
osThreadId_t task_sensor_accHandle;
uint32_t task_sensor_accBuffer[ 128 ];
osStaticThreadDef_t task_sensor_accControlBlock;
const osThreadAttr_t task_sensor_acc_attributes = {
  .name = "task_sensor_acc",
  .stack_mem = &task_sensor_accBuffer[0],
  .stack_size = sizeof(task_sensor_accBuffer),
  .cb_mem = &task_sensor_accControlBlock,
  .cb_size = sizeof(task_sensor_accControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task_display_update */
osThreadId_t task_display_upHandle;
uint32_t task_display_upBuffer[ 128 ];
osStaticThreadDef_t task_display_upControlBlock;
const osThreadAttr_t task_display_up_attributes = {
  .name = "task_display_up",
  .stack_mem = &task_display_upBuffer[0],
  .stack_size = sizeof(task_display_upBuffer),
  .cb_mem = &task_display_upControlBlock,
  .cb_size = sizeof(task_display_upControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for task_sensor_acc */
osThreadId_t task_keypad_accHandle;
uint32_t task_keypad_accBuffer[ 128 ];
osStaticThreadDef_t task_keypad_accControlBlock;
const osThreadAttr_t task_keypad_acc_attributes = {
  .name = "task_keypad_acc",
  .stack_mem = &task_keypad_accBuffer[0],
  .stack_size = sizeof(task_keypad_accBuffer),
  .cb_mem = &task_keypad_accControlBlock,
  .cb_size = sizeof(task_keypad_accControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};


void task_create(void)
{
	packet_queue_init();

	task_sensor_rxHandle = osThreadNew(sensor_rx_entry, NULL, &task_sensor_rx_attributes);
	task_sensor_txHandle = osThreadNew(task_sensor_tx_entry, NULL, &task_sensor_tx_attributes);
	task_sensor_accHandle = osThreadNew(task_sensor_access_entry, NULL, &task_sensor_acc_attributes);
	//task_display_upHandle = osThreadNew(task_display_update_entry, NULL, &task_display_up_attributes);
	task_keypad_accHandle = osThreadNew(task_keypad_access_entry, NULL, &task_keypad_acc_attributes);
}
