// SRW

//#ifndef SRC_TASK_LED_CTRL_H_
#define SRC_TASK_LED_CTRL_H_
#include "color_led.h"
#include "animate_led.h"


void task_led_ctrl(void *argument);
void task_led_ctrl_pause(void);
master_color_state_e task_led_ctrl_color_state(void);
void task_led_ctrl_color_state_demo(void);
void task_led_ctrl_color_state_fixed(void);
void task_led_ctrl_color_reset(void);
bool task_led_ctrl_color_adjust(void);
all_colors_e task_led_ctrl_color(void);
color_hex_code_e task_led_ctrl_color_hex(void);
color_hex_code_e color_to_hex(const all_colors_e color);
void task_led_ctrl_color_random(void);
led_state_e task_led_ctrl_animate_random(const led_state_e cur_state);
void task_led_ctrl_animate_reset(void);
float task_led_ctrl_speed(void);
void task_led_ctrl_speed_adjust(void);
void task_led_ctrl_speed_reset(void);
void task_led_ctrl_animate_iteration_reset(void);
bool task_led_ctrl_animate_adjust_state(void);
void task_led_ctrl_animate_state_demo(void);
void task_led_ctrl_animate_state_fixed(void);
animate_led_state_e task_led_ctrl_animate_state(void);
void task_led_ctrl_strip_one(void *argument);
void task_led_ctrl_strip_two(void *argument);
void task_led_ctrl_strip_three(void *argument);




//#endif /* SRC_TASK_led_ctrl_H_ */
