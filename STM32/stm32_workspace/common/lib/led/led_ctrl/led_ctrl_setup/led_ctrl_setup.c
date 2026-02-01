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
		.led_state_max_iteration[LED_SPEED_1000P]					= 10,
		.led_state_max_iteration[LED_SPEED_500P]					= 10,
		.led_state_max_iteration[LED_SPEED_100P]					= 10,
		.led_state_max_iteration[LED_SPEED_50P]					= 10,
		.led_state_max_iteration[LED_SPEED_25P]					= 10,

		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 20,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,

		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,

		.led_state_allow_black_color							= true
	},
	[LED_STATE_WHITE_COLOR] =
	{
		.led_state_max_iteration[LED_SPEED_1000P]					= 1,
		.led_state_max_iteration[LED_SPEED_500P]					= 1,
		.led_state_max_iteration[LED_SPEED_100P]					= 1,
		.led_state_max_iteration[LED_SPEED_50P]					= 1,
		.led_state_max_iteration[LED_SPEED_25P]					= 1,

		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 0, // NA

		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 10000,

		.led_state_allow_black_color								= false
	},
	[LED_STATE_SOLID_COLOR] =
	{
		.led_state_max_iteration[LED_SPEED_1000P]					= 6,
		.led_state_max_iteration[LED_SPEED_500P]					= 6,
		.led_state_max_iteration[LED_SPEED_100P]					= 6,
		.led_state_max_iteration[LED_SPEED_50P]					= 6,
		.led_state_max_iteration[LED_SPEED_25P]					= 6,

		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 0, // NA
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 0, // NA

		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 5000,

		.led_state_allow_black_color							= false
	},
//	[LED_STATE_SPARKLE_NO_FILL] =
//	{
//		.led_state_max_iteration[LED_SPEED_1000P]					= 4,
//		.led_state_max_iteration[LED_SPEED_500P]					= 4,
//		.led_state_max_iteration[LED_SPEED_100P]					= 4,
//		.led_state_max_iteration[LED_SPEED_50P]					= 4,
//		.led_state_max_iteration[LED_SPEED_25P]					= 4,
//		.led_state_max_iteration[LED_SPEED_6]					= 4,
//
//		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0,
//		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 20,
//		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 66,
//		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 132,
//		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
//		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,
//
////		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0,
////		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 20,
////		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 40,
////		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 60,
////		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 100,
////		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 200,
//
//		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,
//
//		.led_state_allow_black_color								= false
//	},
	[LED_STATE_SPARKLE_FILL] =
	{
		.led_state_max_iteration[LED_SPEED_1000P]					= 4,
		.led_state_max_iteration[LED_SPEED_500P]					= 4,
		.led_state_max_iteration[LED_SPEED_100P]					= 4,
		.led_state_max_iteration[LED_SPEED_50P]					= 4,
		.led_state_max_iteration[LED_SPEED_25P]					= 4,

		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 20,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,

		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,

		.led_state_allow_black_color							= false
	},
	[LED_STATE_RAINBOW_CYCLE] =
	{
		.led_state_max_iteration[LED_SPEED_1000P]					= 4,
		.led_state_max_iteration[LED_SPEED_500P]					= 4,
		.led_state_max_iteration[LED_SPEED_100P]					= 4,
		.led_state_max_iteration[LED_SPEED_50P]					= 4,
		.led_state_max_iteration[LED_SPEED_25P]					= 4,

		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 20,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,

		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,

		.led_state_allow_black_color							= false
	},
//	[LED_STATE_THEATER_CHASE] =
//	{
//		.led_state_max_iteration[LED_SPEED_1000P]					= 10,
//		.led_state_max_iteration[LED_SPEED_500P]					= 10,
//		.led_state_max_iteration[LED_SPEED_100P]					= 10,
//		.led_state_max_iteration[LED_SPEED_50P]					= 10,
//		.led_state_max_iteration[LED_SPEED_25P]					= 10,
//		.led_state_max_iteration[LED_SPEED_6]					= 10,
//
//		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 10,
//		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 45,
//		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 66,
//		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 132,
//		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
//		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,
//
//		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,
//
//		.led_state_allow_black_color							= false
//	},
//	[LED_STATE_THEATER_CHASE_RAINBOW] =
//	{
//		.led_state_max_iteration[LED_SPEED_1000P]					= 10,
//		.led_state_max_iteration[LED_SPEED_500P]					= 10,
//		.led_state_max_iteration[LED_SPEED_100P]					= 10,
//		.led_state_max_iteration[LED_SPEED_50P]					= 10,
//		.led_state_max_iteration[LED_SPEED_25P]					= 10,
//		.led_state_max_iteration[LED_SPEED_6]					= 10,
//
//		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 10,
//		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 45,
//		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 66,
//		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 132,
//		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
//		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,
//
//		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,
//
//		.led_state_allow_black_color							= false
//	},
	[LED_STATE_FADE_IN_AND_OUT] =
	{
		.led_state_max_iteration[LED_SPEED_1000P]					= 10,
		.led_state_max_iteration[LED_SPEED_500P]					= 10,
		.led_state_max_iteration[LED_SPEED_100P]					= 10,
		.led_state_max_iteration[LED_SPEED_50P]					= 10,
		.led_state_max_iteration[LED_SPEED_25P]					= 10,

		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 10,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 45,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,

		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,

		.led_state_allow_black_color							= false
	},
//	[LED_STATE_STARBURST_MODE_1] =
//	{
//		.led_state_max_iteration[LED_SPEED_1000P]					= 10,
//		.led_state_max_iteration[LED_SPEED_500P]					= 10,
//		.led_state_max_iteration[LED_SPEED_100P]					= 10,
//		.led_state_max_iteration[LED_SPEED_50P]					= 10,
//		.led_state_max_iteration[LED_SPEED_25P]					= 10,
//		.led_state_max_iteration[LED_SPEED_6]					= 10,
//
//		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 50,
//		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 100,
//		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 150,
//		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 200,
//		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
//		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 300,
//
//		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,
//
//		.led_state_allow_black_color							= false
//	},
//	[LED_STATE_STARBURST_MODE_2] =
//	{
//		.led_state_max_iteration[LED_SPEED_1000P]					= 10,
//		.led_state_max_iteration[LED_SPEED_500P]					= 10,
//		.led_state_max_iteration[LED_SPEED_100P]					= 10,
//		.led_state_max_iteration[LED_SPEED_50P]					= 10,
//		.led_state_max_iteration[LED_SPEED_25P]					= 10,
//		.led_state_max_iteration[LED_SPEED_6]					= 10,
//
//		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 50,
//		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 100,
//		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 150,
//		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 200,
//		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
//		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 300,
//
//		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,
//
//		.led_state_allow_black_color							= false
//	},
//	[LED_STATE_STARBURST_RANDOM_MODE_1] =
//	{
//		.led_state_max_iteration[LED_SPEED_1000P]					= 10,
//		.led_state_max_iteration[LED_SPEED_500P]					= 10,
//		.led_state_max_iteration[LED_SPEED_100P]					= 10,
//		.led_state_max_iteration[LED_SPEED_50P]					= 10,
//		.led_state_max_iteration[LED_SPEED_25P]					= 10,
//		.led_state_max_iteration[LED_SPEED_6]					= 10,
//
//		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 50,
//		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 100,
//		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 150,
//		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 200,
//		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
//		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 300,
//
//		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,
//
//		.led_state_allow_black_color							= false
//	},
//	[LED_STATE_STARBURST_RANDOM_MODE_2] =
//	{
//		.led_state_max_iteration[LED_SPEED_1000P]					= 10,
//		.led_state_max_iteration[LED_SPEED_500P]					= 10,
//		.led_state_max_iteration[LED_SPEED_100P]					= 10,
//		.led_state_max_iteration[LED_SPEED_50P]					= 10,
//		.led_state_max_iteration[LED_SPEED_25P]					= 10,
//		.led_state_max_iteration[LED_SPEED_6]					= 10,
//
//		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 50,
//		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 100,
//		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 150,
//		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 200,
//		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
//		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 300,
//
//		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,
//
//		.led_state_allow_black_color							= false
//	},
//	[LED_STATE_HEARTBEAT] =
//	{
//		.led_state_max_iteration[LED_SPEED_1000P]					= 10,
//		.led_state_max_iteration[LED_SPEED_500P]					= 10,
//		.led_state_max_iteration[LED_SPEED_100P]					= 10,
//		.led_state_max_iteration[LED_SPEED_50P]					= 10,
//		.led_state_max_iteration[LED_SPEED_25P]					= 10,
//		.led_state_max_iteration[LED_SPEED_6]					= 10,
//
//		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 50,
//		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 100,
//		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 150,
//		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 200,
//		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
//		.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 300,
//
//		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,
//		.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,
//
//		.led_state_allow_black_color							= false
//	},
	[LED_STATE_TWINKLE] =
	{
		.led_state_max_iteration[LED_SPEED_1000P]					= 5,
		.led_state_max_iteration[LED_SPEED_500P]					= 5,
		.led_state_max_iteration[LED_SPEED_100P]					= 5,
		.led_state_max_iteration[LED_SPEED_50P]					= 5,
		.led_state_max_iteration[LED_SPEED_25P]					= 5,

		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 50,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 100,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 150,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 200,

		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,

		.led_state_allow_black_color							= false
	},
#	if (NUM_ACTIVE_STRIPS > 1) && defined(ENABLE_LED_STATE_TWO_COLOR)
		[LED_STATE_TWO_COLOR] =
		{
			.led_state_max_iteration[LED_SPEED_1000P]					= 10,
			.led_state_max_iteration[LED_SPEED_500P]					= 10,
			.led_state_max_iteration[LED_SPEED_100P]					= 10,
			.led_state_max_iteration[LED_SPEED_50P]					= 10,
			.led_state_max_iteration[LED_SPEED_25P]					= 10,

			.led_state_inner_animation_delay_ms[LED_SPEED_1000P]     	= 0,
			.led_state_inner_animation_delay_ms[LED_SPEED_500P]   		= 0,
			.led_state_inner_animation_delay_ms[LED_SPEED_100P]   		= 0,
			.led_state_inner_animation_delay_ms[LED_SPEED_50P]      	= 0,
			.led_state_inner_animation_delay_ms[LED_SPEED_25P]      	= 0,

			.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 5000,
			.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 5000,
			.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 5000,
			.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 5000,
			.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 5000,

			.led_state_allow_black_color							= false
		},
#endif
//#	if (NUM_ACTIVE_STRIPS > 1) && defined(ENABLE_LED_STATE_STATIC_AND_RAINBOW_CHASE)
//		[LED_STATE_STATIC_AND_RAINBOW_CHASE] =
//		{
//			.led_state_max_iteration[LED_SPEED_1000P]					= 10,
//			.led_state_max_iteration[LED_SPEED_500P]					= 10,
//			.led_state_max_iteration[LED_SPEED_100P]					= 10,
//			.led_state_max_iteration[LED_SPEED_50P]					= 10,
//			.led_state_max_iteration[LED_SPEED_25P]					= 10,
//			.led_state_max_iteration[LED_SPEED_6]					= 10,
//
//			.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 10,
//			.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 45,
//			.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 66,
//			.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 132,
//			.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
//			.led_state_inner_animation_delay_ms[LED_SPEED_6]   		= 400,
//
//			.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 0,
//			.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 0,
//			.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 0,
//			.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 0,
//			.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 0,
//			.led_state_between_animation_delay_ms[LED_SPEED_6]		= 0,
//
//			.led_state_allow_black_color							= false
//		}
//#endif


};


led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS] =
{
	[STRIP_NUM_1] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_DEMO, //LED_CTRL_STATE_MASTER_DEMO,//LED_CTRL_STATE_MASTER_DEMO,
			.led_state 						= LED_STATE_RAINBOW_CYCLE, //LED_STATE_SPARKLE_NO_FILL,//LED_STATE_FIRST,
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
		.led_speed 							= LED_SPEED_NORMAL,
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
		.led_speed 							= LED_SPEED_100P,
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
		.led_speed 							= LED_SPEED_100P,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},

	[STRIP_NUM_1_AND_2] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
//			.led_state 						= LED_STATE_SRW_DEBUG,
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
		.led_speed 							= LED_SPEED_100P,
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
		.led_speed 							= LED_SPEED_100P,
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
		.led_speed 							= LED_SPEED_100P,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	},

	[STRIP_NUM_ALL_SET] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
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
		.led_speed 							= LED_SPEED_NORMAL,
		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
	}
};
