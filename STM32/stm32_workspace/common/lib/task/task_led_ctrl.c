// SRW
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"
#include "numbers.h"
#include "board_init_common.h"
#include "led_ctrl_color.h"
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
#include "task_notify.h"
#include "led_ctrl_color.h"
#include "led_ctrl.h"
#include <string.h>
extern UART_HandleTypeDef      gh_host_usart;


//char g_general_rx_buffer[GENERAL_RX_BUFFER_SIZE] = {0};
////extern char g_page[500];
//bool gb_waiting_on_request = false;
//const char* serverIndex = "<h1>Upload STM32 BinFile</h1><h2><br><br><form method='POST' action='/upload' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Upload'></form></h2>";
//
////extern bool g_buffer_full;
////extern bool g_firmware_update_in_progress;
////extern uint16_t g_uart_rx_buffer_index;
//char lookup[7] = "/upload";
//char binary_start[25] = "application/macbinary\r\n\r\n";
////extern uint8_t* g_uart_sector_full_buffer;
//uint64_t flash_address = 0x8020000;
//uint64_t flash_index = 0;
uint16_t g_inner_start = 0;
uint16_t g_inner_stop = 1;

uint16_t g_outer_start = 10;
uint16_t g_outer_stop = 11;
bool g_clear_colors = false;

led_color_e g_two_color_inner = LED_COLOR_BLUE;
led_color_e g_two_color_outer = LED_COLOR_RED;
extern led_color_hex_code_e g_color_hex_codes[NUM_COLORS];


uint8_t                 g_animation_iterations = 0;
uint16_t                g_delay_in_animation_ms = 100; // where applicable of course

uint16_t g_start = 0;
uint16_t g_stop = 10;
bool g_clear = false;

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
	TASK_LED_CTRL_DELAY_MS_10 = 10,
    TASK_LED_CTRL_DELAY_MS_1000 = 1000,
    TASK_LED_CTRL_DELAY_MS_2000 = 2000,
    TASK_LED_CTRL_DELAY_MS_3000 = 3000,
    TASK_LED_CTRL_DELAY_MS_4000 = 4000,
    TASK_LED_CTRL_DELAY_MS_5000 = 5000,
    TASK_LED_CTRL_DELAY_MS_10000 = 10000,
    TASK_LED_CTRL_DELAY_MS_15000 = 15000,
    TASK_LED_CTRL_DELAY_MS_20000 = 20000
} task_led_ctrl_delay_ms_e;


led_ctrl_state_iterations_t g_task_led_ctrl_state_iterations[NUM_LED_STATES] =
{
	[LED_STATE_SPELL] =
	{
		.led_state_max_iteration 									= 10,
		.led_state_iteration_delay_ms 								= 0
	},
	[LED_STATE_WHITE_COLOR] =
	{
		.led_state_max_iteration 									= 5,
		.led_state_iteration_delay_ms 								= 5000
	},
	[LED_STATE_SOLID_COLOR] =
	{
		.led_state_max_iteration 									= 5,
		.led_state_iteration_delay_ms 								= 5000
	},
	[LED_STATE_SPARKLE_NO_FILL] =
	{
		.led_state_max_iteration 									= 4,
		.led_state_iteration_delay_ms 								= 0
	},
	[LED_STATE_SPARKLE_FILL] =
	{
		.led_state_max_iteration 									= 4,
		.led_state_iteration_delay_ms 								= 0
	},
	[LED_STATE_RAINBOW_CYCLE] =
	{
		.led_state_max_iteration 									= 5,
		.led_state_iteration_delay_ms 								= 0
	},
	[LED_STATE_THEATER_CHASE] =
	{
		.led_state_max_iteration 									= 10,
		.led_state_iteration_delay_ms 								= 0
	},
	[LED_STATE_THEATER_CHASE_RAINBOW] =
	{
		.led_state_max_iteration 									= 2,
		.led_state_iteration_delay_ms 								= 0
	},
	[LED_STATE_FADE_IN_AND_OUT] =
	{
		.led_state_max_iteration 									= 10,
		.led_state_iteration_delay_ms 								= 0
	},
	[LED_STATE_TWINKLE] =
	{
		.led_state_max_iteration 									= 5,
		.led_state_iteration_delay_ms 								= 0
	},
	[LED_STATE_TWO_COLOR] =
	{
		.led_state_max_iteration 									= 10,
		.led_state_iteration_delay_ms 								= 5000
	}
};


led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS] =
{
	[STRIP_NUM_1] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
			.led_state 						= LED_STATE_FIRST,
			.led_state_current_iteration 	= 0
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_MINT
		},
		.led_interrupt_info =
		{
			.state							= false,
			.color							= false,
			.speed							= false,
			.pause							= false
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},
	[STRIP_NUM_2] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
			.led_state 						= LED_STATE_FIRST,
			.led_state_current_iteration 	= 0
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_MINT
		},
		.led_interrupt_info =
		{
			.state							= false,
			.color							= false,
			.speed							= false,
			.pause							= false
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},
	[STRIP_NUM_3] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
			.led_state 						= LED_STATE_FIRST,
			.led_state_current_iteration 	= 0,
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_MINT
		},
		.led_interrupt_info =
		{
			.state							= false,
			.color							= false,
			.speed							= false,
			.pause							= false
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},

	[STRIP_NUM_1_AND_2] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
			.led_state 						= LED_STATE_FIRST,
			.led_state_current_iteration 	= 0,
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_MINT
		},
		.led_interrupt_info =
		{
			.state							= false,
			.color							= false,
			.speed							= false,
			.pause							= false
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},
	[STRIP_NUM_1_AND_3] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
			.led_state 						= LED_STATE_FIRST,
			.led_state_current_iteration 	= 0,
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_MINT
		},
		.led_interrupt_info =
		{
			.state							= false,
			.color							= false,
			.speed							= false,
			.pause							= false
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},
	[STRIP_NUM_2_AND_3] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
			.led_state 						= LED_STATE_FIRST,
			.led_state_current_iteration 	= 0,
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_MINT
		},
		.led_interrupt_info =
		{
			.state							= false,
			.color							= false,
			.speed							= false,
			.pause							= false
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},

	[STRIP_NUM_ALL_SET] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
			.led_state 						= LED_STATE_FIRST,
			.led_state_current_iteration 	= 0,
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_MINT
		},
		.led_interrupt_info =
		{
			.state							= false,
			.color							= false,
			.speed							= false,
			.pause							= false
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	}
};


static void task_led_ctrl_adjust_parameters(strip_num_e strip_num)
{
	bool skip_color_check = false;

	led_ctrl_state_info_t *task_led_ctrl_state_info = &g_task_led_ctrl[strip_num].led_state_info;
	led_color_ctrl_info_t *task_color_ctrl_info = &g_task_led_ctrl[strip_num].led_color_info;
	led_ctrl_state_iterations_t *task_led_ctrl_state_iterations = &g_task_led_ctrl_state_iterations[task_led_ctrl_state_info->led_state];

	task_led_ctrl_state_info->led_state_current_iteration++;
    if (0 < (task_led_ctrl_state_iterations->led_state_iteration_delay_ms))
    {
    	if (task_led_ctrl_delay(task_led_ctrl_state_iterations->led_state_iteration_delay_ms))
    	{
    		skip_color_check = true;
    	}
	}
    if (LED_CTRL_STATE_MASTER_DEMO == (task_led_ctrl_state_info->led_state_master))
    {
        if (task_led_ctrl_state_iterations->led_state_max_iteration == task_led_ctrl_state_info->led_state_current_iteration)
        {
        	task_led_ctrl_state_info->led_state = (led_state_e) (task_led_ctrl_state_info->led_state + 1);
            if (NUM_LED_STATES == task_led_ctrl_state_info->led_state) task_led_ctrl_state_info->led_state = LED_STATE_FIRST;
            task_led_ctrl_state_info->led_state_current_iteration = 0;
        }
    }
    if ((!skip_color_check) && (LED_COLOR_MASTER_STATE_DEMO == task_color_ctrl_info->led_color_master))
	{
    	if (LED_STATE_TWO_COLOR == task_led_ctrl_state_info->led_state)
    	{
    		task_color_ctrl_random_input(&g_two_color_inner);
    		task_color_ctrl_random_input(&g_two_color_outer);
    	}
    	else
    	{
    		task_color_ctrl_random(strip_num);
    	}
	}
}


static void task_led_iterate(led_state_e led_state, strip_bit_e strip_bit)
{
	if (1)//(flash_info_animation_enabled(g_task_led_ctrl.led_state))
	{
		switch(led_state)
		{
			case LED_STATE_SPELL:
				led_animate_only_spell_word(strip_bit, task_color_ctrl_hex(), 20);

			break;
			case LED_STATE_WHITE_COLOR:
				led_animate_solid_custom_color((uint16_t)strip_bit, LED_COLOR_HEX_WHITE);
//				if (LED_CTRL_STATE_MASTER_FIXED == g_task_led_ctrl.led_state_master)
//				{
//					task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_1000);
//					task_led_ctrl_delay(1000);
//				}
//				else
//				{
//					//led_animate_solid_custom_color((uint16_t)STRIP_BIT_2, LED_COLOR_HEX_WHITE);
//					task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_1, TASK_LED_CTRL_DELAY_MS_5000);
//				}
			break;
			case LED_STATE_SOLID_COLOR:
				led_animate_solid_custom_color((uint16_t)strip_bit, task_color_ctrl_hex());
//				if (LED_CTRL_STATE_MASTER_FIXED == g_task_led_ctrl.led_state_master)
//				{
//					task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_1000);
//					task_led_ctrl_delay(1000);
//				}
//				else task_led_ctrl_adjust_parameters(TASK_LED_CTRL_LOOP_ITERATIONS_5, TASK_LED_CTRL_DELAY_MS_5000);
			break;
			case LED_STATE_SPARKLE_NO_FILL:
				led_animate_turn_all_pixels_off();
				led_animate_sparkle_only_random_color(strip_bit, false, 100);//random(0, 50));
			break;
			case LED_STATE_SPARKLE_FILL:
				led_animate_sparkle_only_random_color(strip_bit, true, 100);
			break;
			case LED_STATE_RAINBOW_CYCLE:
				led_animate_rainbow_cycle(strip_bit, 0);//10);
			break;
			case LED_STATE_THEATER_CHASE:
				led_animate_theater_chase(strip_bit, task_color_ctrl_hex(), 20);
			break;
			case LED_STATE_THEATER_CHASE_RAINBOW:\
				led_animate_theater_chase_rainbow(strip_bit, 20);
			break;
			case LED_STATE_FADE_IN_AND_OUT:
				led_animate_fade_in_fade_out((uint16_t)strip_bit, task_color_ctrl_hex());
			break;
			case LED_STATE_TWINKLE:
				led_animate_turn_all_pixels_off();
				led_animate_twinkle(strip_bit, task_color_ctrl_hex(), (uint32_t)((float)NUM_LEDS * (float)0.9), 20, false);
			break;
			case LED_STATE_TWO_COLOR:
				led_animate_set_pixels_in_range(strip_bit, 0, 279, g_color_hex_codes[g_two_color_outer]);
				led_animate_set_pixels_in_range(strip_bit, 280, 390, g_color_hex_codes[g_two_color_inner]);
			break;
			break;
			default:
			break;
		}
	}
}


led_state_e task_led_current_led_state(const strip_mask_t mask)
{
	return g_task_led_ctrl[strip_bit_to_strip_num(mask)].led_state_info.led_state;
}


void task_led_1_ctrl(void *argument)
{
	while (1)
	{
		task_led_iterate(g_task_led_ctrl[STRIP_NUM_1].led_state_info.led_state, STRIP_BIT_1);
		task_led_ctrl_adjust_parameters(STRIP_NUM_1);
	}
}


void task_led_2_ctrl(void *argument)
{
	while (1)
	{
		task_led_iterate(g_task_led_ctrl[STRIP_NUM_2].led_state_info.led_state, STRIP_BIT_2);
		task_led_ctrl_adjust_parameters(STRIP_NUM_2);
	}
}


void task_led_3_ctrl(void *argument)
{
	while (1)
	{
		task_led_iterate(g_task_led_ctrl[STRIP_NUM_3].led_state_info.led_state, STRIP_BIT_3);
		task_led_ctrl_adjust_parameters(STRIP_NUM_3);
	}
}


void task_led_sync_ctrl(void *argument)
{
	// need a custom init function to clear all these LEDs..  Right now the funcion
	// below
	// if in sync then should be able to use any of the strips already active..
//	led_animate_turn_all_pixels_off();
//	while (1)
//	{
////		while(task_button_press_major_state_change()) osDelay(100);
//		task_led_iterate(g_task_led_ctrl[CONFIG_LED_STRIP_SYNC_INDEX].led_state, STRIP_BIT_ALL_SET);
//		task_led_ctrl_adjust_parameters(CONFIG_LED_STRIP_SYNC_INDEX);
//	}
}





