// SRW

//#ifndef SRC_TASK_LED_CTRL_H_
#define SRC_TASK_LED_CTRL_H_
#include "color_led.h"
#include "animate_led.h"

extern color_hex_code_e g_color_hex_codes[NUM_COLORS];

typedef struct
{
	master_led_state_e		led_state_master;
	led_state_e				led_state;

	led_speed_e				led_speed;

	led_brightness_e		led_brightness;

	master_color_state_e	led_color_master;
	all_colors_e			led_color;

	bool					interrupt_set;
	bool					pause_set;
} task_led_ctrl_t;

#define GENERAL_RX_BUFFER_SIZE 5000
void task_led_ctrl(void *argument);
void task_led_ctrl_delay(const uint32_t time_ms);
void task_led_ctrl_pause(void);
master_color_state_e task_led_ctrl_color_state(void);
void task_led_ctrl_color_state_demo(void);
void task_led_ctrl_color_state_fixed(void);
void task_led_ctrl_color_reset(void);
bool task_led_ctrl_color_adjust(void);
all_colors_e task_led_ctrl_color(void);
color_hex_code_e task_led_ctrl_color_hex(void);
uint8_t task_led_ctrl_color_red_hex(void);
uint8_t task_led_ctrl_color_green_hex(void);
uint8_t task_led_ctrl_color_blue_hex(void);
color_hex_code_e task_led_ctrl_color_to_hex(const all_colors_e color);
void task_led_ctrl_color_random(void);
led_state_e task_led_ctrl_animate_random(const led_state_e cur_state);
led_state_e task_led_ctrl_animate(void);
void task_led_ctrl_animate_reset(void);
float task_led_ctrl_speed(void);
void task_led_ctrl_speed_adjust(void);
void task_led_ctrl_speed_reset(void);
float task_led_ctrl_delay_time(void);
void task_led_ctrl_animate_iteration_reset(void);
bool task_led_ctrl_animate_adjust_state(void);
void task_led_ctrl_animate_state_demo(void);
void task_led_ctrl_animate_state_fixed(void);
master_led_state_e task_led_ctrl_animate_state(void);
void task_led_ctrl(void *argument);

void task_led_ctrl_clear_pause(void);



//#endif /* SRC_TASK_led_ctrl_H_ */
