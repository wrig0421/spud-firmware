// SRW

#ifndef SRC_TASK_LED_CTRL_H_
#define SRC_TASK_LED_CTRL_H_
#include "color_led.h"
#include "animate_led.h"

void task_led_ctrl_delay(uint32_t time);
master_color_state_e task_led_ctrl_cur_state(void);
void task_led_ctrl_exit_color_demo_state(void);
void task_led_ctrl_enter_color_demo_state(void);
all_colors_e task_led_ctrl_cur_color(void);
uint32_t task_led_ctrl_get_random_color(void);
void task_led_ctrl_reset_color(void);
bool task_led_ctrl_adjust_color(void);
color_hex_code_e task_led_ctrl_cur_color_hex(void);
uint8_t task_led_ctrl_cur_color_red_hex(void);
uint8_t task_led_ctrl_cur_color_green_hex(void);
uint8_t task_led_ctrl_cur_color_blue_hex(void);

//color_hex_code_e task_led_ctrl_random(all_colors_e cur_color);
void task_led_ctrl_randomize(void);

void task_led_ctrl(void *argument);
float task_led_ctrl_speed_factor(void);
float task_led_ctrl_speed_factor(void);
void task_led_ctrl_pause(void);
void task_led_ctrl_reset_animate_iteration_count(void);
void task_led_ctrl_exit_demo_state(void);
master_led_state_e task_led_ctrl_master_state(void);
void task_led_ctrl_adjust_speed(void);
void task_led_ctrl_adjust_speed(void);
void task_led_ctrl_enter_demo_state(void);
float task_led_ctrl_delay_in_animations(void);
void task_led_ctrl_enter_demo_state(void);
void task_led_ctrl_delay(uint32_t time);
bool task_led_ctrl_check_interrupts(uint8_t *red, uint8_t *green, uint8_t *blue);
bool task_led_ctrl_interrupt_occurred(void);
bool task_led_ctrl_adjust_state(void);

#endif /* SRC_TASK_led_ctrl_H_ */
