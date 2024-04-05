// SRW

//#ifndef SRC_TASK_LED_CTRL_H_
#define SRC_TASK_LED_CTRL_H_
#include "led_ctrl_state.h"
#include "led_ctrl_color.h"
#include "led_animate.h"

#define GENERAL_RX_BUFFER_SIZE 5000

led_state_e task_led_current_led_state(const strip_mask_t mask);
void task_led_1_ctrl(void *argument);
void task_led_2_ctrl(void *argument);
void task_led_3_ctrl(void *argument);
void task_led_sync_ctrl(void *argument);


