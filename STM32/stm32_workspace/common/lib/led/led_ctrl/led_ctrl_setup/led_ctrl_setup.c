// SRW

#include "config.h"
#include "ws2812b.h"
#include "led_ctrl_state.h"
#include "led_ctrl_speed.h"
#include "led_ctrl_setup.h"
#include "led_ctrl.h"


// global arrays guaranteed to be 0 filled... Only filling in parameters below
// if they are non zero!
led_ctrl_state_iterations_t g_task_led_ctrl_state_iterations[NUM_LED_STATES] =
{
	[LED_STATE_SPELL] =
	{
		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 20,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]     	= 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	    = 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,

		.led_state_allow_black_color							    = true
	},
	[LED_STATE_WHITE_COLOR] =
	{
		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 10000,
		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 10000,
	},
	[LED_STATE_SOLID_COLOR] =
	{
		.led_state_between_animation_delay_ms[LED_SPEED_1000P]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_500P]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_100P]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_50P]		= 5000,
		.led_state_between_animation_delay_ms[LED_SPEED_25P]		= 5000,
	},
	[LED_STATE_SPARKLE_FILL] =
	{
		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 20,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	    = 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	    = 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
	},
	[LED_STATE_RAINBOW_CYCLE] =
	{
		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 20,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	    = 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	    = 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
	},
	[LED_STATE_THEATER_CHASE] =
	{
		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 10,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 45,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	    = 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	    = 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
	},
	[LED_STATE_THEATER_CHASE_RAINBOW] =
	{
		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 10,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 45,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	    = 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	    = 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   	    = 250,
	},
	[LED_STATE_FADE_IN_AND_OUT] =
	{
		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 10,
		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 45,
		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	    = 66,
		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	    = 132,
		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
	},
//	[LED_STATE_HEARTBEAT] =
//	{
//		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 50,
//		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 100,
//		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	= 150,
//		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	= 200,
//		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 250,
//	},
//	[LED_STATE_TWINKLE] =
//	{
//		.led_state_inner_animation_delay_ms[LED_SPEED_1000P]  		= 0,
//		.led_state_inner_animation_delay_ms[LED_SPEED_500P] 		= 50,
//		.led_state_inner_animation_delay_ms[LED_SPEED_100P]    	    = 100,
//		.led_state_inner_animation_delay_ms[LED_SPEED_50P]     	    = 150,
//		.led_state_inner_animation_delay_ms[LED_SPEED_25P]   		= 200,
//	},
//#	if (NUM_ACTIVE_STRIPS > 1) && defined(ENABLE_LED_STATE_TWO_COLOR)
//		[LED_STATE_TWO_COLOR] =
//		{
//			.led_state_between_animation_delay_ms[LED_SPEED_1000P]  = 5000,
//			.led_state_between_animation_delay_ms[LED_SPEED_500P]   = 5000,
//			.led_state_between_animation_delay_ms[LED_SPEED_100P]   = 5000,
//			.led_state_between_animation_delay_ms[LED_SPEED_50P]    = 5000,
//			.led_state_between_animation_delay_ms[LED_SPEED_25P]    = 5000,
//		}
//#   endif
};


led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS] =
{
	[STRIP_NUM_1] =
	{
		.led_state_info =
		{
			.led_state_master 				= LED_CTRL_STATE_MASTER_DEMO,
			.led_state 						= LED_STATE_RAINBOW_CYCLE,
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
			.led_state_master 				= LED_CTRL_STATE_MASTER_DEMO,
			.led_state 						= LED_STATE_RAINBOW_CYCLE,
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
    [STRIP_NUM_ALL_SET] =
    {
        .led_state_info =
        {
            .led_state_master               = LED_CTRL_STATE_MASTER_DEMO,
            .led_state                      = LED_STATE_RAINBOW_CYCLE,
            .led_state_current_iteration    = 0,
        },
        .led_color_info =
        {
            .led_color_master               = LED_COLOR_MASTER_STATE_DEMO,
            .led_color                      = LED_COLOR_FIRST
        },
        .led_interrupt_info =
        {
            .minor.interrupt_status_flat    = 0,
            .minor_interrupt_flag           = false,
            .major.interrupt_status_flat    = 0,
            .major_interrupt_flag           = false,
        },
        .led_speed                          = LED_SPEED_NORMAL,
        .led_brightness                     = LED_BRIGHTNESS_100_PERCENT
    }
// multiple strips that ARE NOT ALL are not supported at this time...
//	[STRIP_NUM_1_AND_2] =
//	{
//		.led_state_info =
//		{
//			.led_state_master 				= LED_CTRL_STATE_MASTER_FIXED,
////			.led_state 						= LED_STATE_SRW_DEBUG,
//			.led_state_current_iteration 	= 0,
//		},
//		.led_color_info =
//		{
//			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
//			.led_color 						= LED_COLOR_MINT
//		},
//		.led_interrupt_info =
//		{
//			.minor.interrupt_status_flat 	= 0,
//			.minor_interrupt_flag 			= false,
//			.major.interrupt_status_flat 	= 0,
//			.major_interrupt_flag 			= false,
//		},
//		.led_speed 							= LED_SPEED_100P,
//		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
//	},
//	[STRIP_NUM_1_AND_3] =
//	{
//		.led_state_info =
//		{
//			.led_state_master 				= LED_CTRL_STATE_MASTER_DEMO,
//			.led_state 						= LED_STATE_FIRST,
//			.led_state_current_iteration 	= 0,
//		},
//		.led_color_info =
//		{
//			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
//			.led_color 						= LED_COLOR_MINT
//		},
//		.led_interrupt_info =
//		{
//			.minor.interrupt_status_flat 	= 0,
//			.minor_interrupt_flag 			= false,
//			.major.interrupt_status_flat 	= 0,
//			.major_interrupt_flag 			= false,
//		},
//		.led_speed 							= LED_SPEED_100P,
//		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
//	},
//	[STRIP_NUM_2_AND_3] =
//	{
//		.led_state_info =
//		{
//			.led_state_master 				= LED_CTRL_STATE_MASTER_DEMO,
//			.led_state 						= LED_STATE_FIRST,
//			.led_state_current_iteration 	= 0,
//		},
//		.led_color_info =
//		{
//			.led_color_master 				= LED_COLOR_MASTER_STATE_DEMO,
//			.led_color 						= LED_COLOR_MINT
//		},
//		.led_interrupt_info =
//		{
//			.minor.interrupt_status_flat 	= 0,
//			.minor_interrupt_flag 			= false,
//			.major.interrupt_status_flat 	= 0,
//			.major_interrupt_flag 			= false,
//		},
//		.led_speed 							= LED_SPEED_100P,
//		.led_brightness 					= LED_BRIGHTNESS_100_PERCENT
//	},
};
