// SRW

#include "config.h"
#include "ws2812b.h"
#include "led_ctrl_state.h"
#include "led_ctrl_speed.h"
#include "led_ctrl_setup.h"
#include "led_ctrl.h"


led_ctrl_state_iterations_t g_task_led_ctrl_state_iterations[NUM_LED_STATES] =
{
	[LED_STATE_SPELL] =
	{
		.led_state_max_iteration[LED_SPEED_1]					= 10,
		.led_state_max_iteration[LED_SPEED_2]					= 10,
		.led_state_max_iteration[LED_SPEED_3]					= 10,
		.led_state_max_iteration[LED_SPEED_4]					= 10,
		.led_state_max_iteration[LED_SPEED_5]					= 10,
		.led_state_max_iteration[LED_SPEED_6]					= 10,

		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 20,
		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 250,
		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,

		.led_state_between_animation_delay_ms[LED_SPEED_1]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_2]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_3]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_4]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_5]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,

		.led_state_allow_black_color							= true
	},
	[LED_STATE_WHITE_COLOR] =
	{
		.led_state_max_iteration[LED_SPEED_1]					= 1,
		.led_state_max_iteration[LED_SPEED_2]					= 1,
		.led_state_max_iteration[LED_SPEED_3]					= 1,
		.led_state_max_iteration[LED_SPEED_4]					= 1,
		.led_state_max_iteration[LED_SPEED_5]					= 1,
		.led_state_max_iteration[LED_SPEED_6]					= 1,

		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 0, // NA

		.led_state_between_animation_delay_ms[LED_SPEED_1]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_2]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_3]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_4]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_5]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 10000,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_SOLID_COLOR] =
	{
		.led_state_max_iteration[LED_SPEED_1]					= 6,
		.led_state_max_iteration[LED_SPEED_2]					= 6,
		.led_state_max_iteration[LED_SPEED_3]					= 6,
		.led_state_max_iteration[LED_SPEED_4]					= 6,
		.led_state_max_iteration[LED_SPEED_5]					= 6,
		.led_state_max_iteration[LED_SPEED_6]					= 6,

		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 0, // NA

		.led_state_between_animation_delay_ms[LED_SPEED_1]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_2]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_3]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_4]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_5]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 5000,

		.led_state_allow_black_color							= false
	},
	[LED_STATE_SPARKLE_NO_FILL] =
	{
		.led_state_max_iteration[LED_SPEED_1]					= 4,
		.led_state_max_iteration[LED_SPEED_2]					= 4,
		.led_state_max_iteration[LED_SPEED_3]					= 4,
		.led_state_max_iteration[LED_SPEED_4]					= 4,
		.led_state_max_iteration[LED_SPEED_5]					= 4,
		.led_state_max_iteration[LED_SPEED_6]					= 4,

		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 20,
		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 250,
		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,

//		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 0,
//		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 20,
//		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 40,
//		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 60,
//		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 100,
//		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 200,

		.led_state_between_animation_delay_ms[LED_SPEED_1]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_2]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_3]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_4]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_5]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_SPARKLE_FILL] =
	{
		.led_state_max_iteration[LED_SPEED_1]					= 4,
		.led_state_max_iteration[LED_SPEED_2]					= 4,
		.led_state_max_iteration[LED_SPEED_3]					= 4,
		.led_state_max_iteration[LED_SPEED_4]					= 4,
		.led_state_max_iteration[LED_SPEED_5]					= 4,
		.led_state_max_iteration[LED_SPEED_6]					= 4,

		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 20,
		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 250,
		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,

		.led_state_between_animation_delay_ms[LED_SPEED_1]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_2]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_3]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_4]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_5]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,

		.led_state_allow_black_color							= false
	},
	[LED_STATE_RAINBOW_CYCLE] =
	{
		.led_state_max_iteration[LED_SPEED_1]					= 4,
		.led_state_max_iteration[LED_SPEED_2]					= 4,
		.led_state_max_iteration[LED_SPEED_3]					= 4,
		.led_state_max_iteration[LED_SPEED_4]					= 4,
		.led_state_max_iteration[LED_SPEED_5]					= 4,
		.led_state_max_iteration[LED_SPEED_6]					= 4,

		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 20,
		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 250,
		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,

		.led_state_between_animation_delay_ms[LED_SPEED_1]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_2]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_3]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_4]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_5]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,

		.led_state_allow_black_color							= false
	},
	[LED_STATE_THEATER_CHASE] =
	{
		.led_state_max_iteration[LED_SPEED_1]					= 10,
		.led_state_max_iteration[LED_SPEED_2]					= 10,
		.led_state_max_iteration[LED_SPEED_3]					= 10,
		.led_state_max_iteration[LED_SPEED_4]					= 10,
		.led_state_max_iteration[LED_SPEED_5]					= 10,
		.led_state_max_iteration[LED_SPEED_6]					= 10,

		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 10,
		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 45,
		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 250,
		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,

		.led_state_between_animation_delay_ms[LED_SPEED_1]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_2]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_3]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_4]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_5]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,

		.led_state_allow_black_color							= false
	},
	[LED_STATE_THEATER_CHASE_RAINBOW] =
	{
		.led_state_max_iteration[LED_SPEED_1]					= 10,
		.led_state_max_iteration[LED_SPEED_2]					= 10,
		.led_state_max_iteration[LED_SPEED_3]					= 10,
		.led_state_max_iteration[LED_SPEED_4]					= 10,
		.led_state_max_iteration[LED_SPEED_5]					= 10,
		.led_state_max_iteration[LED_SPEED_6]					= 10,

		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 10,
		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 45,
		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 250,
		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,

		.led_state_between_animation_delay_ms[LED_SPEED_1]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_2]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_3]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_4]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_5]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,

		.led_state_allow_black_color							= false
	},
	[LED_STATE_FADE_IN_AND_OUT] =
	{
		.led_state_max_iteration[LED_SPEED_1]					= 10,
		.led_state_max_iteration[LED_SPEED_2]					= 10,
		.led_state_max_iteration[LED_SPEED_3]					= 10,
		.led_state_max_iteration[LED_SPEED_4]					= 10,
		.led_state_max_iteration[LED_SPEED_5]					= 10,
		.led_state_max_iteration[LED_SPEED_6]					= 10,

		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 10,
		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 45,
		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 250,
		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,

		.led_state_between_animation_delay_ms[LED_SPEED_1]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_2]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_3]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_4]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_5]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,

		.led_state_allow_black_color							= false
	},
	[LED_STATE_TWINKLE] =
	{
		.led_state_max_iteration[LED_SPEED_1]					= 5,
		.led_state_max_iteration[LED_SPEED_2]					= 5,
		.led_state_max_iteration[LED_SPEED_3]					= 5,
		.led_state_max_iteration[LED_SPEED_4]					= 5,
		.led_state_max_iteration[LED_SPEED_5]					= 5,
		.led_state_max_iteration[LED_SPEED_6]					= 5,

		.led_state_inner_animation_delay_ms[LED_SPEED_1]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_2] 		= 50,
		.led_state_inner_animation_delay_ms[LED_SPEED_3]    	= 100,
		.led_state_inner_animation_delay_ms[LED_SPEED_4]     	= 150,
		.led_state_inner_animation_delay_ms[LED_SPEED_5]   		= 200,
		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 250,

		.led_state_between_animation_delay_ms[LED_SPEED_1]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_2]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_3]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_4]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_5]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,

		.led_state_allow_black_color							= false
	},
#	if (NUM_ACTIVE_STRIPS > 1) && defined(ENABLE_LED_STATE_TWO_COLOR)
		[LED_STATE_TWO_COLOR] =
		{
			.led_state_max_iteration[LED_SPEED_1]					= 10,
			.led_state_max_iteration[LED_SPEED_2]					= 10,
			.led_state_max_iteration[LED_SPEED_3]					= 10,
			.led_state_max_iteration[LED_SPEED_4]					= 10,
			.led_state_max_iteration[LED_SPEED_5]					= 10,
			.led_state_max_iteration[LED_SPEED_6]					= 10,

			.led_state_inner_animation_delay_ms[LED_SPEED_1]     	= 0,
			.led_state_inner_animation_delay_ms[LED_SPEED_2]   		= 0,
			.led_state_inner_animation_delay_ms[LED_SPEED_3]   		= 0,
			.led_state_inner_animation_delay_ms[LED_SPEED_4]      	= 0,
			.led_state_inner_animation_delay_ms[LED_SPEED_5]      	= 0,
			.led_state_inner_animation_delay_ms[LED_SPEED_6]      	= 0,

			.led_state_between_animation_delay_ms[LED_SPEED_1]		= 5000,
			.led_state_between_animation_delay_ms[LED_SPEED_2]		= 5000,
			.led_state_between_animation_delay_ms[LED_SPEED_3]		= 5000,
			.led_state_between_animation_delay_ms[LED_SPEED_4]		= 5000,
			.led_state_between_animation_delay_ms[LED_SPEED_5]		= 5000,
			.led_state_between_animation_delay_ms[LED_SPEED_6]		= 5000,

			.led_state_allow_black_color							= false
		}
#endif
};


led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS] =
{
	[STRIP_NUM_1] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED, //LED_CTRL_STATE_MASTER_DEMO,//LED_CTRL_STATE_MASTER_DEMO,
			.led_state 						= LED_STATE_WHITE_COLOR, //LED_STATE_SPARKLE_NO_FILL,//LED_STATE_FIRST,
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
		.led_speed 							= LED_SPEED_2,
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
		.led_speed 							= LED_SPEED_3,
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
		.led_speed 							= LED_SPEED_3,
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
		.led_speed 							= LED_SPEED_3,
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
		.led_speed 							= LED_SPEED_3,
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
		.led_speed 							= LED_SPEED_3,
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
		.led_speed 							= LED_SPEED_1,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	}
};
