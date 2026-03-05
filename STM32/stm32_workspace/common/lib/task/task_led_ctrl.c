// SRW
#include <stdbool.h>
#include "stm32l4xx_hal.h"

#include "numbers.h"
#include "board_init_common.h"
#include "led_ctrl_color.h"
#include "task_button_press.h"
#include "led_ctrl_power.h"
#include "task_led_ctrl.h"
#include "board_specific.h"
#include "uart_access.h"
#include "esp8266.h"
#include "esp8266_webserver.h"
#include "uart_access_hal.h"
#include "uart_config_hal.h"
#include "flash_info.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"


#include "flash_access.h"
#include "task_notify.h"
#include "led_ctrl_color.h"
#include "led_ctrl.h"
#include "rv8803.h"
#include "rng_access.h"
#include "led_ctrl_speed.h"
#include <string.h>
extern UART_HandleTypeDef      gh_host_usart;

uint16_t g_inner_start = 0;
uint16_t g_inner_stop = 1;

uint16_t g_outer_start = 10;
uint16_t g_outer_stop = 11;
bool g_clear_colors = false;

led_color_e g_two_color_inner = LED_COLOR_BLUE;
led_color_e g_two_color_outer = LED_COLOR_RED;
//extern led_color_hex_code_e g_led_color_enum_to_hex_lookup[NUM_COLORS];
extern task_notification_value_format_t g_task_notification_value;


uint8_t                 g_animation_iterations = 0;
uint16_t                g_delay_in_animation_ms = 100; // where applicable of course

uint16_t g_start = 0;
uint16_t g_stop = 10;
bool g_clear = false;


typedef enum
{
    TASK_LED_CTRL_LOOP_ITERATIONS_0 	= 0,
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
    TASK_LED_CTRL_LOOP_ITERATIONS_50 	= 50,
    TASK_LED_CTRL_LOOP_ITERATIONS_100 	= 100
} task_led_ctrl_loop_iterations_e;


typedef enum
{
    TASK_LED_CTRL_DELAY_MS_0 		= 0,
	TASK_LED_CTRL_DELAY_MS_10 		= 10,
    TASK_LED_CTRL_DELAY_MS_1000 	= 1000,
    TASK_LED_CTRL_DELAY_MS_2000 	= 2000,
    TASK_LED_CTRL_DELAY_MS_3000 	= 3000,
    TASK_LED_CTRL_DELAY_MS_4000 	= 4000,
    TASK_LED_CTRL_DELAY_MS_5000 	= 5000,
    TASK_LED_CTRL_DELAY_MS_10000 	= 10000,
    TASK_LED_CTRL_DELAY_MS_15000 	= 15000,
    TASK_LED_CTRL_DELAY_MS_20000 	= 20000
} task_led_ctrl_delay_ms_e;

//extern uint32_t g_animation_iteration_count[MAX_NUM_STRIPS][NUM_LED_STATES][NUM_LED_SPEEDS];
//extern led_ctrl_state_iterations_t g_led_ctrl_state_iterations[NUM_LED_STATES];
//extern led_ctrl_t g_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];


bool g_skip_adjust_parameters = false;
void task_led_ctrl_set_skip_adjust_parameters(bool skip)
{
	g_skip_adjust_parameters = true;
}


bool task_led_ctrl_skip_adjust_parameters(void)
{
	return g_skip_adjust_parameters;
}


void task_led_ctrl_clear_skip_adjust_parameters(void)
{
	g_skip_adjust_parameters = false;
}


static void task_led_ctrl_adjust_parameters(const strip_mask_t mask)
{
	if (task_led_ctrl_skip_adjust_parameters())
	{
		task_led_ctrl_clear_skip_adjust_parameters();
		return;
	}
	bool skip_color_check = false;
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	led_ctrl_state_info_t *task_led_ctrl_state_info = led_ctrl_read_state_info(strip_mask);

    led_ctrl_color_info_t *led_ctrl_color_info = &g_led_ctrl[strip_num].led_color_info;
	led_speed_e led_speed = led_ctrl_speed_read_speed(strip_mask);

//	led_ctrl_state_iterations_t *task_led_ctrl_state_iterations = &g_led_ctrl_state_iterations[task_led_ctrl_state_info->led_state];
//	uint16_t max_animation_iteration_count = g_animation_iteration_count[strip_num][task_led_ctrl_state_info->led_state][led_speed];
//	p_led_ctrl_interrupt_status_t p_interrupt_status;
	led_state_e led_state_random = LED_STATE_FIRST;
	task_led_ctrl_state_info->led_state_current_iteration++;
//    if (0 < (task_led_ctrl_state_iterations->led_state_between_animation_delay_ms[led_speed]))
//    {
//    	led_ctrl_time_delay(mask, task_led_ctrl_state_iterations->led_state_between_animation_delay_ms[led_speed]);
//
////    	if (led_ctrl_time_delay(mask, task_led_ctrl_state_iterations->led_state_between_animation_delay_ms[led_speed]))
////    	{
////    		skip_color_check = true;
////    	}
//	}
    if (LED_CTRL_STATE_MASTER_DEMO == (task_led_ctrl_state_info->led_state_master))
    {
    	if (led_animate_exit_stimulus_flag())
		{
    		led_animate_clear_exit_stimulus();
    		led_state_random = (led_state_e) \
    		                (rng_access_read_and_generate_random_number() \
                                            % NUM_LED_STATES);
    		while (task_led_ctrl_state_info->led_state == led_state_random)
    		{
    		    led_state_random = (led_state_e) \
    		                    (rng_access_read_and_generate_random_number() \
    		                                    % NUM_LED_STATES);
    		}
    		task_led_ctrl_state_info->led_state = led_state_random;
//            if (NUM_LED_STATES == task_led_ctrl_state_info->led_state) task_led_ctrl_state_info->led_state = LED_STATE_FIRST;
            task_led_ctrl_state_info->led_state_current_iteration = 0;
        }
    }
    if ((!skip_color_check) && (LED_COLOR_MASTER_STATE_DEMO == led_ctrl_color_info->led_color_master))
	{
        // look up the strips and set the color based on the strip!
//#		if defined(ENABLE_LED_STATE_TWO_COLOR)
//			if (LED_STATE_TWO_COLOR == task_led_ctrl_state_info->led_state)
//			{
//				while (LED_COLOR_BLACK == led_ctrl_color_random_input(&g_two_color_inner));
//				while (LED_COLOR_BLACK == led_ctrl_color_random_input(&g_two_color_outer));
//			}
//			else if (!task_led_ctrl_state_iterations->led_state_allow_black_color)
//#		else
			if (!task_led_ctrl_state_iterations->led_state_allow_black_color)
//#		endif
			{
			    do
			    {
			        led_ctrl_color_randomize_active_color(mask);
			    } while (led_ctrl_color_current_is_black(mask));
			}
			else
			{
			    led_ctrl_color_randomize_active_color(mask);
			}
	}
}

uint32_t g_time_diff = 0;
static void task_led_iterate(led_state_e led_state, strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	uint16_t *p_led_state_inner_animation_delay_ms = \
			&g_led_ctrl_state_iterations[g_led_ctrl[strip_num].led_state_info.led_state].led_state_inner_animation_delay_ms[g_led_ctrl[strip_num].led_speed];

	led_color_e led_color = led_ctrl_color_read_active_color(mask);
	if (0)
	{
		led_animate_static_harley_color(STRIP_BIT_1, &led_color);
		// mask to control do the second strip here...
		mask = (strip_mask_t)STRIP_BIT_2;
	}
	if (1)//(flash_info_animation_enabled(g_led_ctrl.led_state))
	{
		switch(led_state)
		{
			case LED_STATE_SPELL:
				led_animate_only_spell_word(mask, &led_color, p_led_state_inner_animation_delay_ms);
			break;
			case LED_STATE_WHITE_COLOR:
				led_animate_solid_custom_color(mask, LED_COLOR_HEX_WHITE);
			break;
			case LED_STATE_SOLID_COLOR:
				led_animate_solid_custom_color(mask, led_color_enum_to_hex_code(led_color));
			break;
			case LED_STATE_SPARKLE_NO_FILL:
//				led_animate_turn_all_pixels_off();
				led_animate_sparkle_only_random_color(mask, false, p_led_state_inner_animation_delay_ms);//random(0, 50));
			break;
			case LED_STATE_SPARKLE_FILL:
				led_animate_sparkle_only_random_color(mask, true, p_led_state_inner_animation_delay_ms);
			break;
			case LED_STATE_RAINBOW_CYCLE:
				led_animate_rainbow_cycle(mask, p_led_state_inner_animation_delay_ms);//10);
			break;
			case LED_STATE_THEATER_CHASE:
				led_animate_theater_chase(mask, &led_color, p_led_state_inner_animation_delay_ms);
			break;
			case LED_STATE_THEATER_CHASE_RAINBOW:
				led_animate_theater_chase_rainbow(mask, p_led_state_inner_animation_delay_ms);
			break;
			case LED_STATE_FADE_IN_AND_OUT:
				led_animate_fade_in_fade_out(mask, &led_color, p_led_state_inner_animation_delay_ms);
			break;

			// the two states below were enabled for the fall sign!!
//			case LED_STATE_FIXED_ASSORTED_COLOR:
//				led_animate_fixed_assorted_color(mask);
//			break;
//			case LED_STATE_RANDOM_ASSORTED_COLOR:
//				led_animate_random_assorted_color(mask);
//			break;

//			case LED_STATE_TWINKLE:
//				led_animate_turn_all_pixels_off_in_strip(mask);
//				led_animate_twinkle(mask, p_led_color, (uint32_t)((float)NUM_LEDS * (float)0.9), p_led_state_inner_animation_delay_ms, false);
//			break;

//#			if	defined(ENABLE_LED_STATE_TWO_COLOR)
//				case LED_STATE_TWO_COLOR:
//					//led_animate_set_all_pixels_hex_color(STRIP_BIT_1, g_led_color_enum_to_hex_lookup[g_two_color_outer]);
//					led_animate_set_all_pixels_hex_color(STRIP_BIT_2, g_led_color_enum_to_hex_lookup[g_two_color_inner]);
//				break;
//#			endif
//			case LED_STATE_SRW_DEBUG:
//				led_animate_srw_debug();
////#				if defined(ENABLE_STRIP_1)
////					led_animate_determine_number_pixels_in_strip(STRIP_BIT_1);
////#				endif
////#				if defined(ENABLE_STRIP_2)
////					led_animate_determine_number_pixels_in_strip(STRIP_BIT_2);
////#				endif
////#				if defined(ENABLE_STRIP_3)
////					led_animate_determine_number_pixels_in_strip(STRIP_BIT_3);
////#				endif
//			break;
			default:
			    while (1);
			break;
		}
	}
}


void task_led_1_ctrl(void *argument)
{
    led_animate_turn_all_pixels_off_in_strip(STRIP_BIT_1);
    led_ctrl_state_randomize_active_state(STRIP_BIT_1);
    led_ctrl_color_randomize_active_color(STRIP_BIT_1);
    while (1)
    {
        task_led_iterate(led_ctrl_read_active_state(STRIP_BIT_1), STRIP_BIT_1);
        task_led_ctrl_adjust_parameters(STRIP_BIT_1);
    }
}


void task_led_2_ctrl(void *argument)
{
    led_animate_turn_all_pixels_off_in_strip(STRIP_BIT_2);
    led_ctrl_state_randomize_active_state(STRIP_BIT_2);
    led_ctrl_color_randomize_active_color(STRIP_BIT_2);
	while (1)
	{
		task_led_iterate(led_ctrl_read_active_state(STRIP_BIT_2), STRIP_BIT_2);
		task_led_ctrl_adjust_parameters(STRIP_BIT_2);
	}
}


void task_led_3_ctrl(void *argument)
{
    reset_ws2812b();
	led_animate_turn_all_pixels_off_in_strip(STRIP_BIT_3);
    led_ctrl_state_randomize_active_state(STRIP_BIT_3);
    led_ctrl_color_randomize_active_color(STRIP_BIT_3);
    task_led_ctrl_random_initial_state(STRIP_BIT_3);
	while (1)
	{
        task_led_iterate(led_ctrl_read_active_state(STRIP_BIT_3), STRIP_BIT_3);
		task_led_ctrl_adjust_parameters(STRIP_BIT_3);
	}
}


void task_led_sync_ctrl(void *argument)
{
    reset_ws2812b();
	led_animate_turn_all_pixels_off();
	led_ctrl_state_randomize_active_state(STRIP_BIT_ALL_SET);
	led_ctrl_color_randomize_active_color(STRIP_BIT_ALL_SET);
	while (1)
	{
//		led_animate_determine_number_pixels_in_strip(STRIP_BIT_1);
//		g_task_led_ctrl_state = g_led_ctrl[STRIP_NUM_ALL_SET].led_state_info.led_state;
        task_led_iterate(led_ctrl_read_active_state(STRIP_BIT_ALL_SET), STRIP_BIT_ALL_SET);
		task_led_ctrl_adjust_parameters(STRIP_BIT_ALL_SET);
		// do we need a delay here??
	}
}


