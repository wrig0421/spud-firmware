// SRW
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"
#include "numbers.h"
#include "board_init_common.h"
#include "color_led.h"
#include "task_button_press.h"
#include "current_monitor.h"
#include "task_led_ctrl.h"
#include "board_specific.h"
#include "uart_access.h"
#include "esp8266.h"
#include "esp8266_webserver.h"
#include "uart_access_hal.h"
#include "uart_config_hal.h"
#include "flash_info.h"

#include "flash_access.h"
#include <string.h>
extern UART_HandleTypeDef      gh_host_usart;

typedef enum
{
    TASK_LED_CTRL_LOOP_ITERATIONS_0 = 0,
    TASK_LED_CTRL_LOOP_ITERATIONS_1,
    TASK_LED_CTRL_LOOP_ITERATIONS_2,
    TASK_LED_CTRL_LOOP_ITERATIONS_3,
    TASK_LED_CTRL_LOOP_ITERATIONS_4,
    TASK_LED_CTRL_LOOP_ITERATIONS_5,
    TASK_LED_CTRL_LOOP_ITERATIONS_6,
    TASK_LED_CTRL_LOOP_ITERATIONS_7,
    TASK_LED_CTRL_LOOP_ITERATIONS_8,
    TASK_LED_CTRL_LOOP_ITERATIONS_9,
    TASK_LED_CTRL_LOOP_ITERATIONS_10,
    TASK_LED_CTRL_LOOP_ITERATIONS_50 = 50,
    TASK_LED_CTRL_LOOP_ITERATIONS_100 = 100
} task_led_ctrl_loop_iterations_e;


typedef enum
{
    TASK_LED_CTRL_DELAY_MS_0 = 0,
    TASK_LED_CTRL_DELAY_MS_1000 = 1000,
    TASK_LED_CTRL_DELAY_MS_2000 = 2000,
    TASK_LED_CTRL_DELAY_MS_3000 = 3000,
    TASK_LED_CTRL_DELAY_MS_4000 = 4000,
    TASK_LED_CTRL_DELAY_MS_5000 = 5000,
    TASK_LED_CTRL_DELAY_MS_10000 = 10000,
    TASK_LED_CTRL_DELAY_MS_15000 = 15000,
    TASK_LED_CTRL_DELAY_MS_20000 = 20000
} task_led_ctrl_delay_ms_e;


task_led_ctrl_t g_task_led_ctrl =
{
	.led_state_master = MASTER_LED_STATE_DEMO,
	.led_state = LED_STATE_RAINBOW_CYCLE,
	.led_speed = LED_SPEED_1X,
	.led_brightness = LED_BRIGHTNESS_100_PERCENT,
	.led_color_master = MASTER_COLOR_STATE_DEMO,
	.led_color = COLORS_MINT,
	.interrupt_set = false,
	.pause_set = false
};

//master_led_state_e g_task_led_ctrl.led_state_master = MASTER_LED_STATE_DEMO;

//extern color_hex_code_e *g_color_hex_codes;
extern color_hex_code_e g_color_hex_codes[NUM_COLORS];


uint8_t                 g_animation_iterations = 0;
uint16_t                g_delay_in_animation_ms = 100; // where applicable of course


static void task_led_ctrl_adjust_parameters(const task_led_ctrl_loop_iterations_e max_iterations,
                                            const task_led_ctrl_delay_ms_e animation_delay_ms)
{
    g_animation_iterations++;
    if (MASTER_LED_STATE_DEMO == g_task_led_ctrl.led_state_master)
    {
        if (TASK_LED_CTRL_DELAY_MS_0 != animation_delay_ms) task_led_ctrl_delay(animation_delay_ms);
        if (max_iterations == g_animation_iterations)
        {
            g_task_led_ctrl.led_state = (led_state_e) (g_task_led_ctrl.led_state + 1);
            if (NUM_LED_STATES == g_task_led_ctrl.led_state) g_task_led_ctrl.led_state = LED_STATE_FIRST;
            g_animation_iterations = 0;
        }
    }
    if (MASTER_COLOR_STATE_DEMO == task_led_ctrl_color_state()) task_led_ctrl_color_random();
}

char g_general_rx_buffer[GENERAL_RX_BUFFER_SIZE] = {0};
//extern char g_page[500];
bool gb_waiting_on_request = false;
const char* serverIndex = "<h1>Upload STM32 BinFile</h1><h2><br><br><form method='POST' action='/upload' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Upload'></form></h2>";

//extern bool g_buffer_full;
//extern bool g_firmware_update_in_progress;
//extern uint16_t g_uart_rx_buffer_index;
char lookup[7] = "/upload";
char binary_start[25] = "application/macbinary\r\n\r\n";
//extern uint8_t* g_uart_sector_full_buffer;
uint64_t flash_address = 0x8020000;
uint64_t flash_index = 0;


static void task_led_ctrl_strip(strip_num_e strip_num)
{
	if (1)//(flash_info_animation_enabled(g_task_led_ctrl.led_state))
	{
		switch(g_task_led_ctrl.led_state)
		{
			case LED_STATE_WHITE_COLOR:

				animate_led_solid_custom_color((uint16_t)strip_num, COLOR_HEX_RED);
				//animate_led_solid_custom_color((uint16_t)STRIP_NUM_2, COLOR_HEX_WHITE);
				task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_1, TASK_LED_CTRL_DELAY_MS_5000);
			break;
			case LED_STATE_SOLID_COLOR:
				animate_led_solid_custom_color((uint16_t)strip_num, task_led_ctrl_color_hex());
				if (MASTER_LED_STATE_FIXED == g_task_led_ctrl.led_state_master)
				{
					task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_1000);
					task_led_ctrl_delay(1000);
				}
				else task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_5000);
			break;
			case LED_STATE_SPARKLE_NO_FILL:
				animate_led_turn_all_pixels_off();
				animate_led_sparkle_only_random_color(strip_num, false, 100);//random(0, 50));
				task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_0);
			break;
			case LED_STATE_SPARKLE_FILL:
				animate_led_sparkle_only_random_color(strip_num, true, 100);
				task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_10, TASK_LED_CTRL_DELAY_MS_0);
			break;
			case LED_STATE_RAINBOW_CYCLE:
				animate_led_rainbow_cycle(strip_num, 10);
				task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_0);
			break;
			case LED_STATE_THEATER_CHASE:
				animate_led_theater_chase(strip_num, task_led_ctrl_color_hex(), 20);
				task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_10, TASK_LED_CTRL_DELAY_MS_0);
			break;
			case LED_STATE_THEATER_CHASE_RAINBOW:\
				animate_led_theater_chase_rainbow(strip_num, 20);
				task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_2, TASK_LED_CTRL_DELAY_MS_0);
			break;
			case LED_STATE_FADE_IN_AND_OUT:
				animate_led_fade_in_fade_out((uint16_t)strip_num, task_led_ctrl_color_hex());
				task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_10, TASK_LED_CTRL_DELAY_MS_0);
			break;
			case LED_STATE_TWINKLE:
				animate_led_turn_all_pixels_off();
				animate_led_twinkle(strip_num, task_led_ctrl_color_hex(), (uint32_t)((float)NUM_LEDS * (float)0.9), 20, false);
				task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_0);
			break;
			case LED_STATE_SPELL:
				animate_led_only_spell_word(strip_num, task_led_ctrl_color_hex(), 20);
				task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_10, TASK_LED_CTRL_DELAY_MS_0);
			break;
			default:
			break;
		}
	}
}


void task_led_ctrl_strip_one(void *argument)
{


}


void task_led_ctrl(void *argument)
{
	// need a custom init function to clear all these LEDs..  Right now the funcion
	// below
	animate_led_turn_all_pixels_off();

	strip_num_e strip_num = STRIP_NONE;
	switch (NUM_ACTIVE_STRIPS)
	{
		case 1:
			strip_num = STRIP_NUM_1;
		break;
		case 2:
			strip_num = STRIP_NUM_1 | STRIP_NUM_2;
		break;
		case 3:
			strip_num = STRIP_NUM_1 | STRIP_NUM_2 | STRIP_NUM_3;
		break;
		default:
		break;
	}
	while (1)
	{
		while(task_button_press_major_state_change()) osDelay(100);
		task_led_ctrl_strip(strip_num);
	}
}


void task_led_ctrl_delay(const uint32_t time_ms)
{
    uint32_t ms_count = 0;
    while (ms_count++ < time_ms)
    {
        osDelay(portTICK_PERIOD_MS);
    }
}


void task_led_ctrl_brightness_adjust(void)
{
    if (LED_BRIGHTNESS_FIRST == g_task_led_ctrl.led_brightness) g_task_led_ctrl.led_brightness = LED_BRIGHTNESS_LAST;
    else g_task_led_ctrl.led_brightness = (led_brightness_e) (g_task_led_ctrl.led_brightness - 1);
    switch (g_task_led_ctrl.led_brightness)
    {
        case LED_BRIGHTNESS_100_PERCENT:
            current_monitor_set(1.0f);
        break;
//        case LED_BRIGHTNESS_50_PERCENT:
//            current_monitor_set(0.5f);
//        break;
        case LED_BRIGHTNESS_25_PERCENT:
            current_monitor_set(0.25f);
        break;
        case LED_BRIGHTNESS_1_PERCENT:
            current_monitor_set(0.01f);
        break;
    }
}


void task_led_ctrl_clear_pause(void)
{
    g_task_led_ctrl.pause_set = false;
}


void task_led_ctrl_pause(void)
{
    static uint8_t flip_or_flop = 1;
    if (flip_or_flop) g_task_led_ctrl.pause_set = true;
    else g_task_led_ctrl.pause_set = false;
    flip_or_flop ^= 1;
}


master_color_state_e task_led_ctrl_color_state(void)
{
    return g_task_led_ctrl.led_color_master;
}


void task_led_ctrl_color_state_demo(void)
{
    g_task_led_ctrl.led_color_master = MASTER_COLOR_STATE_DEMO;
}


void task_led_ctrl_color_state_fixed(void)
{
    g_task_led_ctrl.led_color_master = MASTER_COLOR_STATE_FIXED;
    g_task_led_ctrl.led_color = COLORS_FIRST;
}


void task_led_ctrl_color_reset(void)
{
    g_task_led_ctrl.led_color = COLORS_RED;
}


bool task_led_ctrl_color_adjust(void)
{
    bool return_val = false;
    if (COLORS_LAST == g_task_led_ctrl.led_color)
    {
        g_task_led_ctrl.led_color = COLORS_FIRST;
        return_val = true;
    }
    else g_task_led_ctrl.led_color = (all_colors_e) (g_task_led_ctrl.led_color + 1);
    return return_val;
}


all_colors_e task_led_ctrl_color(void)
{
    return g_task_led_ctrl.led_color;
}


color_hex_code_e task_led_ctrl_color_hex(void)
{
    return g_color_hex_codes[g_task_led_ctrl.led_color];
}


uint8_t task_led_ctrl_color_red_hex(void)
{
    return (((g_color_hex_codes[g_task_led_ctrl.led_color] & 0xFF0000) >> 16) / current_monitor_ratio());
}


uint8_t task_led_ctrl_color_green_hex(void)
{
    return (((g_color_hex_codes[g_task_led_ctrl.led_color] & 0x00FF00) >> 8) / current_monitor_ratio());
}


uint8_t task_led_ctrl_color_blue_hex(void)
{
    return ((g_color_hex_codes[g_task_led_ctrl.led_color] & 0x0000FF) / current_monitor_ratio());
}


color_hex_code_e task_led_ctrl_color_to_hex(const all_colors_e color)
{
    return g_color_hex_codes[color];
}


void task_led_ctrl_color_random(void)
{
    all_colors_e color = (all_colors_e)(random_num(0, NUM_COLORS));
    if (g_task_led_ctrl.led_color == color)
    {
        if ((COLORS_LAST) == color) g_task_led_ctrl.led_color = (all_colors_e)(color - 1);
        else g_task_led_ctrl.led_color = (all_colors_e)(color + 1);
    }
    else
    {
        g_task_led_ctrl.led_color = color;
    }
}


led_state_e task_led_ctrl_animate_random(const led_state_e cur_state)
{
    led_state_e state = (led_state_e)(random_num(LED_STATE_FIRST, NUM_LED_STATES));
    if (cur_state == state)
    {
        if (LED_STATE_LAST == cur_state) state = (led_state_e)(state - 1);
        else state = (led_state_e)(state + 1);
    }
    return state;
}


led_state_e task_led_ctrl_animate(void)
{
    return g_task_led_ctrl.led_state;
}


void task_led_ctrl_animate_reset(void)
{
    g_task_led_ctrl.led_state = LED_STATE_FIRST;
}


float task_led_ctrl_speed(void)
{
    float speed_factor = 0.0;
    switch(g_task_led_ctrl.led_speed)
    {
        case LED_SPEED_10X:
            speed_factor = 10;
        break;
        case LED_SPEED_5X:
            speed_factor = 5;
        break;
//        case LED_SPEED_2X:
//            speed_factor = 2;
//        break;
        case LED_SPEED_1X:
            speed_factor = 1;
        break;
        case LED_SPEED_0P5X:
            speed_factor = 0.5;
        break;
        case LED_SPEED_0P25X:
            speed_factor = 0.25;
        break;
        default:
        break;
        /*
        case LED_SPEED_0P1X:
            speed_factor = 0.1;
        break;
        */
    }
    return speed_factor;
}


void task_led_ctrl_speed_adjust(void)
{
    if (LED_SPEED_FIRST == g_task_led_ctrl.led_speed) g_task_led_ctrl.led_speed = LED_SPEED_LAST;
    else g_task_led_ctrl.led_speed = (led_speed_e) (g_task_led_ctrl.led_speed - 1);
}


void task_led_ctrl_speed_reset(void)
{
    g_task_led_ctrl.led_speed = LED_SPEED_1X;
}


float task_led_ctrl_delay_time(void)
{
    return ((float)g_delay_in_animation_ms / task_led_ctrl_speed());
}


void task_led_ctrl_animate_iteration_reset(void)
{
    g_animation_iterations = 0;
}


bool task_led_ctrl_animate_adjust_state(void)
{
    bool return_val = false;
    if (LED_STATE_LAST == g_task_led_ctrl.led_state)
    {
        g_task_led_ctrl.led_state = LED_STATE_FIRST;
        return_val = true;
    }
    else g_task_led_ctrl.led_state = (led_state_e) (g_task_led_ctrl.led_state + 1);
    return return_val;
}


void task_led_ctrl_animate_state_demo(void)
{
    g_task_led_ctrl.led_state_master = MASTER_LED_STATE_DEMO;
    g_animation_iterations = 0;
}


void task_led_ctrl_animate_state_fixed(void)
{
    g_task_led_ctrl.led_state_master = MASTER_LED_STATE_FIXED;
    g_task_led_ctrl.led_state = LED_STATE_FIRST; // set first state
    g_animation_iterations = 0;
}


master_led_state_e task_led_ctrl_animate_state(void)
{
    return g_task_led_ctrl.led_state_master;
}


