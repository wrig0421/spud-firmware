// SRW

//#ifndef SRC_TASK_LED_CTRL_H_
#define SRC_TASK_LED_CTRL_H_
#include "led_ctrl_brightness.h"
#include "led_ctrl_state.h"
#include "led_ctrl_color.h"
#include "led_animate.h"

#define GENERAL_RX_BUFFER_SIZE 5000


typedef enum
{
	TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED = 0x10,

} task_led_ctrl_notification_value_e;


led_state_e task_led_current_led_state(const strip_mask_t mask);

uint16_t task_led_state_max_iterations(const strip_mask_t mask, led_state_e led_state);
uint16_t task_led_state_inner_animation_delay_ms(const strip_mask_t mask, led_state_e led_state);
uint16_t task_led_state_between_animation_delay_ms(const strip_mask_t mask, led_state_e led_state);
uint16_t task_led_state_allows_black_color(const strip_mask_t mask, led_state_e led_state);
led_brightness_e task_led_brightness(const strip_mask_t mask);
led_ctrl_state_master_e task_led_master_state(const strip_mask_t mask);
led_ctrl_state_master_e task_led_state(const strip_mask_t mask);
uint16_t task_led_state_current_iteration(const strip_mask_t mask);
led_state_e task_led_current_led_state(const strip_mask_t mask);

void task_led_ctrl_set_skip_adjust_parameters(bool skip);
bool task_led_ctrl_skip_adjust_parameters(void);
void task_led_ctrl_clear_skip_adjust_parameters(void);


void task_led_1_ctrl(void *argument);
void task_led_2_ctrl(void *argument);
void task_led_3_ctrl(void *argument);
void task_led_sync_ctrl(void *argument);





