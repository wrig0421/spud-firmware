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

#include "flash_access.h"
#include "task_notify.h"
#include "led_ctrl_color.h"
#include "led_ctrl.h"
#include "rv8803.h"
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


led_ctrl_state_iterations_t g_task_led_ctrl_state_iterations[NUM_LED_STATES] =
{
	[LED_STATE_SPELL] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 32,
		.led_state_max_iteration[LED_SPEED_5X]						= 16,
		.led_state_max_iteration[LED_SPEED_1X]						= 8,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 4,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 2,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 0,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 40,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 100,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 250,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 500,

		.led_state_allow_black_color								= true
	},
	[LED_STATE_WHITE_COLOR] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 1,
		.led_state_max_iteration[LED_SPEED_5X]						= 1,
		.led_state_max_iteration[LED_SPEED_1X]						= 1,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 1,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 1,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 5000,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_SOLID_COLOR] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 32,
		.led_state_max_iteration[LED_SPEED_5X]						= 16,
		.led_state_max_iteration[LED_SPEED_1X]						= 8,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 4,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 2,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 5000,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_SPARKLE_NO_FILL] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 4,
		.led_state_max_iteration[LED_SPEED_5X]						= 4,
		.led_state_max_iteration[LED_SPEED_1X]						= 4,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 4,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 4,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 0,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 40,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 100,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 250,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 500,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_SPARKLE_FILL] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 4,
		.led_state_max_iteration[LED_SPEED_5X]						= 4,
		.led_state_max_iteration[LED_SPEED_1X]						= 4,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 4,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 4,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 0,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 40,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 100,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 250,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 500,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_RAINBOW_CYCLE] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 4,
		.led_state_max_iteration[LED_SPEED_5X]						= 4,
		.led_state_max_iteration[LED_SPEED_1X]						= 4,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 4,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 4,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 0,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 40,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 100,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 250,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 500,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_THEATER_CHASE] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 10,
		.led_state_max_iteration[LED_SPEED_5X]						= 10,
		.led_state_max_iteration[LED_SPEED_1X]						= 10,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 10,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 10,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 0,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 40,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 100,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 250,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 500,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_THEATER_CHASE_RAINBOW] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 2,
		.led_state_max_iteration[LED_SPEED_5X]						= 2,
		.led_state_max_iteration[LED_SPEED_1X]						= 2,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 2,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 2,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 0,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 40,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 100,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 250,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 500,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_FADE_IN_AND_OUT] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 10,
		.led_state_max_iteration[LED_SPEED_5X]						= 10,
		.led_state_max_iteration[LED_SPEED_1X]						= 10,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 10,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 10,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 0,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 40,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 100,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 250,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 500,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_TWINKLE] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 5,
		.led_state_max_iteration[LED_SPEED_5X]						= 5,
		.led_state_max_iteration[LED_SPEED_1X]						= 5,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 5,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 5,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 0,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 40,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 100,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 250,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 500,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_TWO_COLOR] =
	{
		.led_state_max_iteration[LED_SPEED_10X]						= 10,
		.led_state_max_iteration[LED_SPEED_5X]						= 10,
		.led_state_max_iteration[LED_SPEED_1X]						= 10,
		.led_state_max_iteration[LED_SPEED_0P5X]					= 10,
		.led_state_max_iteration[LED_SPEED_0P25X]					= 10,

		.led_state_iteration_delay_ms[LED_SPEED_10X]				= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_5X]					= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_1X]					= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_0P5X]				= 5000,
		.led_state_iteration_delay_ms[LED_SPEED_0P25X]				= 5000,

		.led_state_allow_black_color								= false
	}
};


//typedef struct
//{
//	struct
//	{
//		union
//		{
//			led_ctrl_interrupt_status_t 	minor_interrupt_status;
//			uint8_t 						minor_interrupt_status_flat;
//		};
//		bool minor_interrupt_flag;
//	};
//	struct
//	{
//		union
//		{
//			led_ctrl_interrupt_status_t 	major_interrupt_status;
//			uint8_t 						major_intterupt_status_flat;
//		};
//		bool major_interrupt_flag;
//		bool major_interrupt_transition_cmplt_flag;
//	};
//} led_ctrl_interrupt_info_t;


led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS] =
{
	[STRIP_NUM_1] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_DEMO,//LED_CTRL_STATE_MASTER_DEMO,
			.led_state 						= LED_STATE_FIRST,//LED_STATE_FIRST,
			.led_state_current_iteration 	= 0
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_MINT
		},
		.led_interrupt_info =
		{
			.minor.interrupt_status_flat 	= 0,
			.minor_interrupt_flag 			= false,
			.major.interrupt_status_flat 	= 0,
			.major_interrupt_flag 			= false,
		},
		.led_speed 							= LED_SPEED_5X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},
	[STRIP_NUM_2] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
			.led_state 						= LED_STATE_WHITE_COLOR,
			.led_state_current_iteration 	= 0
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_MINT
		},
		.led_interrupt_info =
		{
			.minor.interrupt_status_flat 	= 0,
			.minor_interrupt_flag 			= false,
			.major.interrupt_status_flat 	= 0,
			.major_interrupt_flag 			= false,
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},
	[STRIP_NUM_3] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_DEMO,
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
			.minor.interrupt_status_flat 	= 0,
			.minor_interrupt_flag 			= false,
			.major.interrupt_status_flat 	= 0,
			.major_interrupt_flag 			= false,
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},

	[STRIP_NUM_1_AND_2] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
			.led_state 						= LED_STATE_SRW_DEBUG,
			.led_state_current_iteration 	= 0,
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_MINT
		},
		.led_interrupt_info =
		{
			.minor.interrupt_status_flat 	= 0,
			.minor_interrupt_flag 			= false,
			.major.interrupt_status_flat 	= 0,
			.major_interrupt_flag 			= false,
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},
	[STRIP_NUM_1_AND_3] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_DEMO,
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
			.minor.interrupt_status_flat 	= 0,
			.minor_interrupt_flag 			= false,
			.major.interrupt_status_flat 	= 0,
			.major_interrupt_flag 			= false,
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},
	[STRIP_NUM_2_AND_3] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_DEMO,
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
			.minor.interrupt_status_flat 	= 0,
			.minor_interrupt_flag 			= false,
			.major.interrupt_status_flat 	= 0,
			.major_interrupt_flag 			= false,
		},
		.led_speed 							= LED_SPEED_1X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},

	[STRIP_NUM_ALL_SET] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_DEMO,
			.led_state 						= LED_STATE_RAINBOW_CYCLE,
			.led_state_current_iteration 	= 0,
		},
		.led_color_info =
		{
			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
			.led_color 						= LED_COLOR_FIRST
		},
		.led_interrupt_info =
		{
			.minor.interrupt_status_flat 	= 0,
			.minor_interrupt_flag 			= false,
			.major.interrupt_status_flat 	= 0,
			.major_interrupt_flag 			= false,
		},
		.led_speed 							= LED_SPEED_5X,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	}
};


static void task_led_ctrl_adjust_parameters(const strip_mask_t mask)
{
	bool skip_color_check = false;
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	led_ctrl_state_info_t *task_led_ctrl_state_info = &g_task_led_ctrl[strip_num].led_state_info;
	led_ctrl_color_info_t *led_ctrl_color_info = &g_task_led_ctrl[strip_num].led_color_info;
	led_speed_e led_speed = g_task_led_ctrl[strip_num].led_speed;
	led_ctrl_state_iterations_t *task_led_ctrl_state_iterations = &g_task_led_ctrl_state_iterations[task_led_ctrl_state_info->led_state];

	task_led_ctrl_state_info->led_state_current_iteration++;
    if (0 < (task_led_ctrl_state_iterations->led_state_iteration_delay_ms[led_speed]))
    {
    	if (led_ctrl_delay(task_led_ctrl_state_iterations->led_state_iteration_delay_ms[led_speed]))
    	{
    		skip_color_check = true;
    	}
	}
    if (LED_CTRL_STATE_MASTER_DEMO == (task_led_ctrl_state_info->led_state_master))
    {
        if (task_led_ctrl_state_iterations->led_state_max_iteration[led_speed] == task_led_ctrl_state_info->led_state_current_iteration)
        {
        	task_led_ctrl_state_info->led_state = (led_state_e) (task_led_ctrl_state_info->led_state + 1);
            if (NUM_LED_STATES == task_led_ctrl_state_info->led_state) task_led_ctrl_state_info->led_state = LED_STATE_FIRST;
            task_led_ctrl_state_info->led_state_current_iteration = 0;
        }
    }
    if ((!skip_color_check) && (LED_COLOR_MASTER_STATE_DEMO == led_ctrl_color_info->led_color_master))
	{
    	if (LED_STATE_TWO_COLOR == task_led_ctrl_state_info->led_state)
    	{
    		while (LED_COLOR_BLACK == led_ctrl_color_random_input(&g_two_color_inner));
    		while (LED_COLOR_BLACK == led_ctrl_color_random_input(&g_two_color_outer));
    	}
    	else
    	{
    		if (!task_led_ctrl_state_iterations->led_state_allow_black_color)
    		{
    			while (LED_COLOR_BLACK == led_ctrl_color_random(mask));
    		}
    		else
    		{
    			led_ctrl_color_random(mask);
    		}
    	}
	}
}


static void task_led_iterate(led_state_e led_state, const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	uint16_t animation_delay_ms = g_task_led_ctrl_state_iterations[g_task_led_ctrl[ws2812_strip_bit_to_strip_num(mask)].led_state_info.led_state].led_state_iteration_delay_ms[g_task_led_ctrl[strip_num].led_speed];
	if (1)//(flash_info_animation_enabled(g_task_led_ctrl.led_state))
	{
		switch(led_state)
		{
			case LED_STATE_SPELL:
				led_animate_only_spell_word(mask, led_ctrl_color_hex(mask), animation_delay_ms);
			break;
			case LED_STATE_WHITE_COLOR:
				led_animate_solid_custom_color(mask, LED_COLOR_HEX_WHITE);
			break;
			case LED_STATE_SOLID_COLOR:
				led_animate_solid_custom_color(mask, led_ctrl_color_hex(mask));
			break;
			case LED_STATE_SPARKLE_NO_FILL:
				led_animate_turn_all_pixels_off();
				led_animate_sparkle_only_random_color(mask, false, animation_delay_ms);//random(0, 50));
			break;
			case LED_STATE_SPARKLE_FILL:
				led_animate_sparkle_only_random_color(mask, true, animation_delay_ms);
			break;
			case LED_STATE_RAINBOW_CYCLE:
				led_animate_rainbow_cycle(mask, animation_delay_ms);//10);
			break;
			case LED_STATE_THEATER_CHASE:
				led_animate_theater_chase(mask, led_ctrl_color_hex(mask), animation_delay_ms);
			break;
			case LED_STATE_THEATER_CHASE_RAINBOW:\
				led_animate_theater_chase_rainbow(mask, animation_delay_ms);
			break;
			case LED_STATE_FADE_IN_AND_OUT:
				led_animate_fade_in_fade_out(mask, led_ctrl_color_hex(mask));
			break;
			case LED_STATE_TWINKLE:
				led_animate_turn_all_pixels_off();
				led_animate_twinkle(mask, led_ctrl_color_hex(mask), (uint32_t)((float)NUM_LEDS * (float)0.9), animation_delay_ms, false);
			break;
			case LED_STATE_TWO_COLOR:
				led_animate_set_all_pixels_hex_color(STRIP_BIT_1, g_color_hex_codes[g_two_color_outer]);
				led_animate_set_all_pixels_hex_color(STRIP_BIT_2, g_color_hex_codes[g_two_color_inner]);
			break;
			break;
			case LED_STATE_SRW_DEBUG:
#				if defined(ENABLE_STRIP_1)
					led_animate_determine_number_pixels_in_strip(STRIP_BIT_1);
#				endif
#				if defined(ENABLE_STRIP_2)
					led_animate_determine_number_pixels_in_strip(STRIP_BIT_2);
#				endif
#				if defined(ENABLE_STRIP_3)
					led_animate_determine_number_pixels_in_strip(STRIP_BIT_3);
#				endif
			break;
			default:
			break;
		}
	}
}


led_state_e task_led_current_led_state(const strip_mask_t mask)
{
	return g_task_led_ctrl[ws2812_strip_bit_to_strip_num(mask)].led_state_info.led_state;
}


void task_led_1_ctrl(void *argument)
{
	reset_ws2812b();
	led_animate_turn_all_pixels_off_in_strip(STRIP_BIT_1);

	while (1)
	{
		task_led_iterate(g_task_led_ctrl[STRIP_NUM_1].led_state_info.led_state, STRIP_BIT_1);
		task_led_ctrl_adjust_parameters(STRIP_BIT_1);
//		task_led_iterate(LED_STATE_THEATER_CHASE_RAINBOW, STRIP_BIT_1);
	}
}


void task_led_2_ctrl(void *argument)
{
	led_animate_turn_all_pixels_off_in_strip(STRIP_BIT_2);
	while (1)
	{
		task_led_iterate(g_task_led_ctrl[STRIP_NUM_2].led_state_info.led_state, STRIP_BIT_2);
		task_led_ctrl_adjust_parameters(STRIP_BIT_2);
	}
}


void task_led_3_ctrl(void *argument)
{
	led_animate_turn_all_pixels_off_in_strip(STRIP_BIT_3);
	while (1)
	{
		task_led_iterate(g_task_led_ctrl[STRIP_NUM_3].led_state_info.led_state, STRIP_BIT_3);
		task_led_ctrl_adjust_parameters(STRIP_BIT_3);
	}
}


void task_led_sync_ctrl(void *argument)
{
	//rv8803_write_current_tod();
	led_animate_turn_all_pixels_off();
	while (1)
	{
		//task_led_iterate(LED_STATE_RAINBOW_CYCLE, STRIP_BIT_ALL_SET);
		task_led_iterate(g_task_led_ctrl[STRIP_NUM_ALL_SET].led_state_info.led_state, STRIP_BIT_ALL_SET);
		task_led_ctrl_adjust_parameters(STRIP_BIT_ALL_SET);
		// do we need a delay here??
	}
}





