// SRW
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "projdefs.h"

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


extern const animate_led_ctrl_t g_animate_led_ctrl[NUM_LED_STATES];

task_led_ctrl_t g_task_led_ctrl =
{
	.led_state_master = MASTER_LED_STATE_DEMO,
	.led_state = LED_STATE_FIRST,
	.led_state_iteration = 0,
	.led_speed = LED_SPEED_1X,
	.led_brightness = LED_BRIGHTNESS_100_PERCENT,
	.led_color_master = MASTER_COLOR_STATE_DEMO,
	.led_color = COLORS_MINT,
	.interrupt_set = false,
	.pause_set = false
};

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
//animate_led_state_e g_task_led_ctrl.led_state_master = MASTER_LED_STATE_DEMO;

//extern color_hex_code_e *g_color_hex_codes;
extern color_hex_code_e g_color_hex_codes[NUM_COLORS];


static void task_led_ctrl_adjust_parameters(void)
{
    g_task_led_ctrl.led_state_iteration++;
    // check if master LED state is demo!
    if (MASTER_LED_STATE_DEMO == g_task_led_ctrl.led_state_master)
    {
    	// if demo state selected then check and see if the animation state has a nonzero delay!
        if (!g_animate_led_ctrl[g_task_led_ctrl.led_state].animation_delay_ms)
		{
        	// if nonzero delay then delay that amount of time.
        	pdMS_TO_TICKS(g_animate_led_ctrl[g_task_led_ctrl.led_state].animation_delay_ms);
		}
        // check if the number of iterations for the animation has been reached.
        if (g_task_led_ctrl.led_state_iteration == g_animate_led_ctrl[g_task_led_ctrl.led_state].animation_loop_iterations)
        {
        	// if animation limit has been reached then increment the LED state!
            g_task_led_ctrl.led_state++;
            // if the LED state after increment is equal to NUM_LED_STATEs then wrap around to the first state (LED_STATE_FIRST)
            if (NUM_LED_STATES == g_task_led_ctrl.led_state) g_task_led_ctrl.led_state = LED_STATE_FIRST;
            //  reset the the led state count after changing the state
            g_task_led_ctrl.led_state_iteration = 0;
        }
    }
    // if COLOR master state is demo then change the color of the animation.  This does not apply to all animations...
    // for example rainbow cycle disregards led_color_master
    if (MASTER_COLOR_STATE_DEMO == g_task_led_ctrl.led_color_master) task_led_ctrl_color_random();
}


static void task_led_ctrl_strip(strip_num_e strip_num)
{
	if (1)//(flash_info_animation_enabled(g_task_led_ctrl.led_state))
	{
		switch(g_task_led_ctrl.led_state)
		{
			case LED_STATE_WHITE_COLOR:

				animate_led_solid_custom_color((uint16_t)strip_num, COLOR_HEX_RED);
				//animate_led_solid_custom_color((uint16_t)STRIP_NUM_2, COLOR_HEX_WHITE);
			break;
			case LED_STATE_SOLID_COLOR:
				animate_led_solid_custom_color((uint16_t)strip_num, task_led_ctrl_color_hex());
//				if (MASTER_LED_STATE_FIXED == g_task_led_ctrl.led_state_master)
//				{
//					task_led_ctrl_adjust_parameters(ANIMATE_LED_LOOP_ITERATIONS_5, ANIMATE_LED_DELAY_MS_1000);
//					pdMS_TO_TICKS(1000);
//				}
//				else task_led_ctrl_adjust_parameters(ANIMATE_LED_LOOP_ITERATIONS_5, ANIMATE_LED_DELAY_MS_5000);
			break;
			case LED_STATE_SPARKLE_NO_FILL:
				animate_led_turn_all_pixels_off();
				animate_led_sparkle_only_random_color(strip_num, false, 100);//random(0, 50));
			break;
			case LED_STATE_SPARKLE_FILL:
				animate_led_sparkle_only_random_color(strip_num, true, 100);
			break;
			case LED_STATE_RAINBOW_CYCLE:
				animate_led_rainbow_cycle(strip_num, 10);
			break;
			case LED_STATE_THEATER_CHASE:
				animate_led_theater_chase(strip_num, task_led_ctrl_color_hex(), 20);
			break;
			case LED_STATE_THEATER_CHASE_RAINBOW:
				animate_led_theater_chase_rainbow(strip_num, 20);
			break;
			case LED_STATE_FADE_IN_AND_OUT:
				animate_led_fade_in_fade_out((uint16_t)strip_num, task_led_ctrl_color_hex());
			break;
			case LED_STATE_TWINKLE:
				animate_led_turn_all_pixels_off();
				animate_led_twinkle(strip_num, task_led_ctrl_color_hex(), (uint32_t)((float)NUM_LEDS * (float)0.9), 20, false);
			break;
			case LED_STATE_SPELL:
				animate_led_only_spell_word(strip_num, task_led_ctrl_color_hex(), 20);
			break;
			default:
			break;
		}
		task_led_ctrl_adjust_parameters();
	}
}


void task_led_ctrl(void *argument)
{
	// init task_led before officially starting the task infinite loop
	// 1st turn off all LEDs in the display
	animate_led_turn_all_pixels_off();

	strip_num_e strip_num = STRIP_NONE;
	// set the strip_num to reflect the number of strips with non zero length.
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
		// TODO consider creating a higher priority task that only checks for button presses.
		//      if this occurs then set a variable or notify that task_led to exit immediately.  Needs some
		//      careful considerations.  Key part being to immediately stop drawing the current animation.
		while(task_button_press_major_state_change()) osDelay(100);
		task_led_ctrl_strip(strip_num);
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


void task_led_ctrl_animate_iteration_reset(void)
{
    g_task_led_ctrl.led_state_iteration = 0;
}




