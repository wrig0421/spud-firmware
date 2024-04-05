// SRW

//#ifndef SRC_TASK_LED_CTRL_H_
#define SRC_TASK_LED_CTRL_H_
#include "led_color.h"
#include "led_animate.h"

extern color_hex_code_e g_color_hex_codes[NUM_COLORS];


typedef struct
{
	master_led_state_e		led_state_master;
	led_state_e				led_state;
	uint16_t				led_state_current_iteration;
} task_led_ctrl_state_info_t;


typedef struct
{
	master_color_state_e	led_color_master;
	led_color_e			led_color;
} task_color_ctrl_info_t;


typedef struct
{
	uint16_t				led_state_max_iteration;
	uint16_t				led_state_iteration_delay_ms;
} task_led_state_iterations_t;


typedef struct
{
	uint8_t any_set : 1;
	uint8_t state 	: 1;
	uint8_t color 	: 1;
	uint8_t	speed 	: 1;
	uint8_t pause 	: 1;
	uint8_t rsvd  	: 3;
} task_led_ctrl_interrupt_info_t;


typedef struct
{
	task_led_ctrl_state_info_t		led_state_info;
	task_color_ctrl_info_t			led_color_info;
	task_led_ctrl_interrupt_info_t	led_interrupt_info;
	led_speed_e						led_speed;
	led_brightness_e				led_brightness;
} task_led_ctrl_t;


#define GENERAL_RX_BUFFER_SIZE 5000


void task_led_1_ctrl(void *argument);
void task_led_2_ctrl(void *argument);
void task_led_3_ctrl(void *argument);
void task_led_sync_ctrl(void *argument);


