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


//master_led_state_e g_master_led_state = MASTER_LED_STATE_DEMO;
master_led_state_e      g_master_led_state = MASTER_LED_STATE_DEMO;
led_state_e             g_led_state = LED_STATE_FIRST;
led_speed_e             g_led_speed = LED_SPEED_10X;
led_brightness_e        g_led_brightness = LED_BRIGHTNESS_100_PERCENT;

master_color_state_e    g_master_color_state = MASTER_COLOR_STATE_DEMO;
all_colors_e            g_led_color = COLORS_MINT;
//extern color_hex_code_e *g_color_hex_codes;
extern bool             g_animate_led_pause_flag;
extern bool             g_animate_led_interrupt;
extern color_hex_code_e g_color_hex_codes[NUM_COLORS];


uint8_t                 g_animation_iterations = 0;
uint16_t                g_delay_in_animation_ms = 100; // where applicable of course
extern bool             task_button_press_major_change;


static void task_led_ctrl_adjust_parameters(const task_led_ctrl_loop_iterations_e max_iterations,
                                            const task_led_ctrl_delay_ms_e animation_delay_ms)
{
    g_animation_iterations++;
    if (MASTER_LED_STATE_DEMO == g_master_led_state)
    {
        if (TASK_LED_CTRL_DELAY_MS_0 != animation_delay_ms) task_led_ctrl_delay(animation_delay_ms);
        if (max_iterations == g_animation_iterations)
        {
            g_led_state = (led_state_e) (g_led_state + 1);
            if (NUM_LED_STATES == g_led_state) g_led_state = LED_STATE_FIRST;
            g_animation_iterations = 0;
        }
    }
    if (MASTER_COLOR_STATE_DEMO == task_led_ctrl_color_state()) task_led_ctrl_color_random();
}

char g_general_rx_buffer[GENERAL_RX_BUFFER_SIZE] = {0};
extern char g_page[500];
bool gb_waiting_on_request = false;
const char* serverIndex = "<h1>Upload STM32 BinFile</h1><h2><br><br><form method='POST' action='/upload' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Upload'></form></h2>";

extern bool g_buffer_full;
extern bool g_firmware_update_in_progress;
extern uint16_t g_uart_rx_buffer_index;
char lookup[7] = "/upload";
char binary_start[25] = "application/macbinary\r\n\r\n";
extern uint8_t* g_uart_sector_full_buffer;
uint64_t flash_address = 0x8020000;
uint64_t flash_index = 0;
void task_led_ctrl_strip_one(void *argument)
{
//	flash_access_erase_slot();
//	uint32_t str_len = 0;
//	esp8266_startup();
//	esp8266_start_webserver();
//	esp8266_write_command_and_read_response(ESP8266_AT_CIPSEND, true, "0,446", (char *)g_general_rx_buffer, 30, 10000);
//
//	//if (!esp8266_write_command_and_read_response(ESP8266_AT_CIPSEND, true, "0,446", (char *)g_general_rx_buffer, 30, 10000)) while (1);
//	str_len = esp8266_webserver_make_page("Select file", serverIndex);
//	esp8266_write_data(g_page, str_len, 5000);
//	if (!esp8266_write_command_and_read_response(ESP8266_AT_CIPCLOSE, true, "0", (char *)g_general_rx_buffer, 30, 5000)) while (1);

//	board_init_specific_esp8266_power_disable();
//	osDelay(1000);
//	board_init_specific_esp8266_power_enable();

//	board_init_specific_esp8266_reset_assert();
//	board_init_specific_esp8266_uart_boot_enable();
//	osDelay(1000);
//	board_init_specific_esp8266_reset_deassert();

	//while(1);
	//esp8266_write_command(ESP8266_AT_ECHO, false, 0);
//	esp8266_write_command_and_read_response(ESP8266_AT_ECHO, false, 0, (char *)g_read_buffer, 2);
//	osDelay(200);


	//esp8266_write_command_and_read_response(ESP8266_AT_STARTUP, false, 0, (char *)g_read_buffer, 2);
	//uart_access_hal_read_block(uart_config_esp8266_handle(), g_read_buffer, 4);
	//esp8266_write_command(ESP8266_AT_STARTUP, false, 0);
	//uart_access_hal_read_block(uart_config_esp8266_handle(), g_read_buffer, 2);
	//esp8266_write_command(ESP8266_AT_STARTUP, false, 0);
	//uart_access_hal_read_block(uart_config_esp8266_handle(), g_read_buffer, 2);

	//uart_access_read_block_esp8266(g_data, 2);
//	g_uart_rx_buffer_index = 0;
//
//	while (!esp8266_response_contains(g_general_rx_buffer, lookup, sizeof(lookup), sizeof(g_general_rx_buffer)))
//	{
//		osDelay(10);
//	}
//	while (!esp8266_response_contains(g_general_rx_buffer, binary_start, sizeof(binary_start), sizeof(g_general_rx_buffer)))
//	{
//		osDelay(10);
//	}
	// need to parse the +IPD messages.  The amount of data is chunked and sent down.
	// will need to look for these and not save to buffer..
	// one thought is to look for it as it comes in on UART...
	// It ends with :.  If +IPD found then keep tossing until : is reached.  Toss that then start saving!
//	g_firmware_update_in_progress = true;
//	while (1)
//	{
//		if (g_buffer_full)
//		{
//			g_buffer_full = false;
//
//			flash_access_write_sector_with_address((uint64_t *)g_uart_sector_full_buffer, flash_address + flash_index);
//			flash_index += 2048;
//		}
//		osDelay(10); // test this.  Baud rate slowed way down..
//	}
//
//	while(1)
//	{
//		osDelay(200);
//	}
//
//    osDelay(10);
    while (1)
    {
        while(task_button_press_major_state_change()) osDelay(100);

        if (1)//(flash_info_animation_enabled(g_led_state))
        {
            switch(g_led_state)
            {
                case LED_STATE_WHITE_COLOR:
                    animate_led_solid_custom_color((uint16_t)STRIP_BIT_1, COLOR_HEX_WHITE);
                    task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_1, TASK_LED_CTRL_DELAY_MS_5000);
                break;
                case LED_STATE_SOLID_COLOR:
                    animate_led_solid_custom_color((uint16_t)STRIP_BIT_1, task_led_ctrl_color_hex());
                    if (MASTER_LED_STATE_FIXED == g_master_led_state)
                    {
                        task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_1000);
                        task_led_ctrl_delay(1000);
                    }
                    else task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_5000);
                break;
                case LED_STATE_SPARKLE_NO_FILL:
                    animate_led_turn_all_pixels_off();
                    animate_led_sparkle_only_random_color(STRIP_BIT_1, false, 100);//random(0, 50));
                    task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_0);
                break;
                case LED_STATE_SPARKLE_FILL:
                    animate_led_sparkle_only_random_color(STRIP_BIT_1, true, 100);
                    task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_10, TASK_LED_CTRL_DELAY_MS_0);
                break;
                case LED_STATE_RAINBOW_CYCLE:
                    animate_led_rainbow_cycle(STRIP_BIT_1, 10);
                    task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_0);
                break;
                case LED_STATE_THEATER_CHASE:
                    animate_led_theater_chase(STRIP_BIT_1, task_led_ctrl_color_hex(), 20);
                    task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_10, TASK_LED_CTRL_DELAY_MS_0);
                break;
                case LED_STATE_THEATER_CHASE_RAINBOW:\
                    animate_led_theater_chase_rainbow(STRIP_BIT_1, 20);
                    task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_2, TASK_LED_CTRL_DELAY_MS_0);
                break;
                case LED_STATE_FADE_IN_AND_OUT:
                    animate_led_fade_in_fade_out((uint16_t)STRIP_BIT_1, task_led_ctrl_color_hex());
                    task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_10, TASK_LED_CTRL_DELAY_MS_0);
                break;
                case LED_STATE_TWINKLE:
                    animate_led_turn_all_pixels_off();
                    animate_led_twinkle(STRIP_BIT_1, task_led_ctrl_color_hex(), (uint32_t)((float)NUM_LEDS * (float)0.9), 20, false);
                    task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_0);
                break;
                case LED_STATE_SPELL:
                    animate_led_only_spell_word(STRIP_BIT_1, task_led_ctrl_color_hex(), 20);
                    task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_10, TASK_LED_CTRL_DELAY_MS_0);
                break;
                default:
                break;
            }
        }
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
    if (LED_BRIGHTNESS_FIRST == g_led_brightness) g_led_brightness = LED_BRIGHTNESS_LAST;
    else g_led_brightness = (led_brightness_e) (g_led_brightness - 1);
    switch (g_led_brightness)
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
    g_animate_led_pause_flag = false;
}


void task_led_ctrl_pause(void)
{
    static uint8_t flip_or_flop = 1;
    if (flip_or_flop) g_animate_led_pause_flag = true;
    else g_animate_led_pause_flag = false;
    flip_or_flop ^= 1;
}


master_color_state_e task_led_ctrl_color_state(void)
{
    return g_master_color_state;
}


void task_led_ctrl_color_state_demo(void)
{
    g_master_color_state = MASTER_COLOR_STATE_DEMO;
}


void task_led_ctrl_color_state_fixed(void)
{
    g_master_color_state = MASTER_COLOR_STATE_FIXED;
    g_led_color = COLORS_FIRST;
}


void task_led_ctrl_color_reset(void)
{
    g_led_color = COLORS_RED;
}


bool task_led_ctrl_color_adjust(void)
{
    bool return_val = false;
    if (COLORS_LAST == g_led_color)
    {
        g_led_color = COLORS_FIRST;
        return_val = true;
    }
    else g_led_color = (all_colors_e) (g_led_color + 1);
    return return_val;
}


all_colors_e task_led_ctrl_color(void)
{
    return g_led_color;
}


color_hex_code_e task_led_ctrl_color_hex(void)
{
    return g_color_hex_codes[g_led_color];
}


uint8_t task_led_ctrl_color_red_hex(void)
{
    return (((g_color_hex_codes[g_led_color] & 0xFF0000) >> 16) / current_monitor_ratio());
}


uint8_t task_led_ctrl_color_green_hex(void)
{
    return (((g_color_hex_codes[g_led_color] & 0x00FF00) >> 8) / current_monitor_ratio());
}


uint8_t task_led_ctrl_color_blue_hex(void)
{
    return ((g_color_hex_codes[g_led_color] & 0x0000FF) / current_monitor_ratio());
}


color_hex_code_e task_led_ctrl_color_to_hex(const all_colors_e color)
{
    return g_color_hex_codes[color];
}


void task_led_ctrl_color_random(void)
{
    all_colors_e color = (all_colors_e)(random_num(0, NUM_COLORS));
    if (g_led_color == color)
    {
        if ((COLORS_LAST) == color) g_led_color = (all_colors_e)(color - 1);
        else g_led_color = (all_colors_e)(color + 1);
    }
    else
    {
        g_led_color = color;
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
    return g_led_state;
}


void task_led_ctrl_animate_reset(void)
{
    g_led_state = LED_STATE_FIRST;
}


float task_led_ctrl_speed(void)
{
    float speed_factor = 0.0;
    switch(g_led_speed)
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
    if (LED_SPEED_FIRST == g_led_speed) g_led_speed = LED_SPEED_LAST;
    else g_led_speed = (led_speed_e) (g_led_speed - 1);
}


void task_led_ctrl_speed_reset(void)
{
    g_led_speed = LED_SPEED_1X;
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
    if (LED_STATE_LAST == g_led_state)
    {
        g_led_state = LED_STATE_FIRST;
        return_val = true;
    }
    else g_led_state = (led_state_e) (g_led_state + 1);
    return return_val;
}


void task_led_ctrl_animate_state_demo(void)
{
    g_master_led_state = MASTER_LED_STATE_DEMO;
    g_animation_iterations = 0;
}


void task_led_ctrl_animate_state_fixed(void)
{
    g_master_led_state = MASTER_LED_STATE_FIXED;
    g_led_state = LED_STATE_FIRST; // set first state
    g_animation_iterations = 0;
}


master_led_state_e task_led_ctrl_animate_state(void)
{
    return g_master_led_state;
}


