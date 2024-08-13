// SRW

#include "FreeRTOS.h"
#include "portmacro.h"

#include "led_ctrl.h"
#include "task_button_press.h"
#include "free_rtos_convenience.h"
#include "ws2812b.h"
#include "led_ctrl_speed.h"


bool led_ctrl_delay(const uint32_t time_ms)
{
    uint32_t ms_count = 0;
    uint32_t ticks = 0;
    if (!time_ms) return false;

    ticks = time_ms / portTICK_PERIOD_MS;

    while (ms_count++ < ticks)
    {
    	free_rtos_delay_ms(portTICK_PERIOD_MS);
        if (task_button_press_interrupt_occurred()) return true;
    }
    return false;
}


//float led_ctrl_delay_time(strip_num_e strip_num)
//{
//    return ((float)g_delay_in_animation_ms / led_ctrl_speed(mask));
//}



uint32_t g_animation_measured_task_per_10_leds_time_ms[NUM_LED_STATES] =
{
	// this does not include any delay function calls
	// this is per 20 LEDs
	[LED_STATE_SPELL] = 1,
	[LED_STATE_WHITE_COLOR] = 1,
	[LED_STATE_SOLID_COLOR] = 1,
	[LED_STATE_SPARKLE_NO_FILL] = 2,
	[LED_STATE_SPARKLE_FILL] = 1,
	[LED_STATE_RAINBOW_CYCLE] = 1,
	[LED_STATE_THEATER_CHASE] = 10,
	[LED_STATE_THEATER_CHASE_RAINBOW] = 10,
	[LED_STATE_FADE_IN_AND_OUT] = 10,
	[LED_STATE_TWINKLE] = 10,
#	if defined(ENABLE_LED_STATE_TWO_COLOR)
		[LED_STATE_TWO_COLOR] = 10
#	endif
};


uint32_t g_animation_iteration_count[MAX_NUM_STRIPS][NUM_LED_STATES][NUM_LED_SPEEDS];
#define LED_ANIMATE_DYNAMIC_TIME_MS 	1
#define LED_ANIMATE_ANIMATION_TIME_SEC	90
#define LED_ANIMATE_ANIMATION_TIME_MS	LED_ANIMATE_ANIMATION_TIME_SEC * 1000
uint32_t g_animation_time_ms[NUM_LED_SPEEDS] =
{
	[LED_SPEED_1] = LED_ANIMATE_ANIMATION_TIME_MS,
	[LED_SPEED_2] = LED_ANIMATE_ANIMATION_TIME_MS,
	[LED_SPEED_3] = LED_ANIMATE_ANIMATION_TIME_MS * 2,
	[LED_SPEED_4] = LED_ANIMATE_ANIMATION_TIME_MS * 2,
	[LED_SPEED_5] = LED_ANIMATE_ANIMATION_TIME_MS * 3,
	[LED_SPEED_6] = LED_ANIMATE_ANIMATION_TIME_MS * 3
};


// fixed time for the animations
// different times for speed is ok.
// need to ensure number of LEDs defined fits in the time alloted...


// WORST CASE ANIMATION TIME
#define LED_CTRL_WORST_CASE_DYNAMIC_ANIMATION_TIME 	(((LARGEST_LED_STRIP_SIZE / 10) + 1) * 2)
#define LED_CTRL_WORST_CASE_STATIC_ANIMATION_TIME	(LARGEST_LED_STRIP_SIZE * 2.0f * (256.0f / 2.0f) * 2.0f)
#define LED_CTRL_WORST_CASE_TOTAL_ANIMATION_TIME  	((uint32_t)(LED_CTRL_WORST_CASE_DYNAMIC_ANIMATION_TIME + LED_CTRL_WORST_CASE_STATIC_ANIMATION_TIME))
#define LED_CTRL_MINIMUM_ANIMATION_LOOPS			3

uint32_t g_worst_case_dynamic_animation_time = 0;
uint32_t g_worst_case_static_animation_time = 0;
uint32_t g_worst_case_between_animation_time = 0;


extern led_ctrl_state_iterations_t g_task_led_ctrl_state_iterations[NUM_LED_STATES];

typedef struct
{
	uint32_t dynamic_ms;
	uint32_t static_ms;
	uint32_t between_ms;
} led_animate_ctrl_time_t;


void led_ctrl_init(void)
{
	// adjust the time so we at minimum get LED_CTRL_MINIMUM_ANIMATION_LOOPS loops
//	for (led_speed_e led_speed = LED_SPEED_FIRST; led_speed < NUM_LED_SPEEDS; led_speed++)
//	{
//		uint16_t animation_loops_remainder = (g_animation_time_ms[led_speed] % LED_CTRL_WORST_CASE_TOTAL_ANIMATION_TIME);
//		uint16_t animation_loops = (g_animation_time_ms[led_speed] / LED_CTRL_WORST_CASE_TOTAL_ANIMATION_TIME);
//		if (LED_CTRL_MINIMUM_ANIMATION_LOOPS > animation_loops)
//		{
//			switch (animation_loops)
//			{
//				case 0:
//					g_animation_time_ms[led_speed] = LED_CTRL_MINIMUM_ANIMATION_LOOPS * LED_CTRL_WORST_CASE_TOTAL_ANIMATION_TIME;
//				break;
//				case 1:
//					g_animation_time_ms[led_speed] += g_animation_time_ms[led_speed] - (animation_loops_remainder * LED_CTRL_WORST_CASE_TOTAL_ANIMATION_TIME);
//					g_animation_time_ms[led_speed] += g_animation_time_ms[led_speed] / 2;
//				break;
//				case 2:
//					g_animation_time_ms[led_speed] += g_animation_time_ms[led_speed] - (animation_loops_remainder * LED_CTRL_WORST_CASE_TOTAL_ANIMATION_TIME);
//				break;
//				default:
//				break;
//			}
//		}
//	}

	led_animate_ctrl_time_t led_animate_ctrl_time;
	led_animate_ctrl_time.dynamic_ms = 0;
	led_animate_ctrl_time.static_ms = 0;
	led_animate_ctrl_time.between_ms = 0;

	uint16_t animation_iterations = 0;
	uint16_t num_leds = 0;
	uint16_t num_10_led_chunks = 0;
	uint32_t total_time = 0;

	for (led_state_e led_state = LED_STATE_FIRST; led_state < NUM_LED_STATES; led_state++)
	{
		for (led_speed_e led_speed = LED_SPEED_FIRST; led_speed < NUM_LED_SPEEDS; led_speed++)
		{
			for (strip_num_e strip_num = STRIP_NUM_1;
#if defined(ENABLE_STRIP_3)
					strip_num <= STRIP_NUM_3;
#elif defined(ENABLE_STRIP_2)
					strip_num <= STRIP_NUM_2;
#else
					strip_num <= STRIP_NUM_1;
#endif
					strip_num++)
			{
				switch (strip_num)
				{
					case STRIP_NUM_1:
						num_leds = STRIP_1_LENGTH;
					break;
					case STRIP_NUM_2:
						num_leds = STRIP_2_LENGTH;
					break;
					case STRIP_NUM_3:
						num_leds = STRIP_3_LENGTH;
					break;
					default:
						num_leds = 0;
					break;
				}
				if (num_leds % 10) num_10_led_chunks = (num_leds / 10) + 1; // round up
				else num_10_led_chunks = num_leds;

				led_animate_ctrl_time.static_ms = \
					g_task_led_ctrl_state_iterations[led_state].led_state_inner_animation_delay_ms[led_speed];
				led_animate_ctrl_time.between_ms = \
					g_task_led_ctrl_state_iterations[led_state].led_state_between_animation_delay_ms[led_speed];
				led_animate_ctrl_time.dynamic_ms = 0;
				switch (led_state)
				{
					case LED_STATE_SPELL:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.static_ms *= num_leds; // delay is PER LED not per 10 LEDs
					break;
					case LED_STATE_WHITE_COLOR:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
					break;
					case LED_STATE_SOLID_COLOR:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
					break;
					case LED_STATE_SPARKLE_NO_FILL:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.dynamic_ms *= 2; // 2x instances of setting pixels
//						led_animate_ctrl_time.static_ms *= num_leds;
						led_animate_ctrl_time.static_ms *= (0.7f * num_leds);
					break;
					case LED_STATE_SPARKLE_FILL:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
//						led_animate_ctrl_time.static_ms *= num_leds;
						led_animate_ctrl_time.static_ms *= (0.7f * num_leds);
					break;
					case LED_STATE_RAINBOW_CYCLE:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.static_ms *= 256 * 5; // todo remove the magic number...
					break;
					case LED_STATE_THEATER_CHASE:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.static_ms *= 3 * 100; // todo remove the magic number...
					break;
					case LED_STATE_THEATER_CHASE_RAINBOW:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.static_ms *= 3 * 100; // todo remove the magic number...
					break;
					case LED_STATE_FADE_IN_AND_OUT:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.dynamic_ms *= 2; // 2x instances of setting pixels
						led_animate_ctrl_time.static_ms *= (256.0f + (256.0f / 2.0f));
					break;
					case LED_STATE_STARBURST_MODE_1:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.static_ms *= num_leds; // delay is PER LED not per 10 LEDs
					break;
					case LED_STATE_STARBURST_MODE_2:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.static_ms *= num_leds; // delay is PER LED not per 10 LEDs
					break;
					case LED_STATE_STARBURST_RANDOM_MODE_1:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.static_ms *= num_leds; // delay is PER LED not per 10 LEDs
					break;
					case LED_STATE_STARBURST_RANDOM_MODE_2:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.static_ms *= num_leds; // delay is PER LED not per 10 LEDs
					break;
					case LED_STATE_HEARTBEAT:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.static_ms *= num_leds; // delay is PER LED not per 10 LEDs
					break;
					case LED_STATE_TWINKLE:
						led_animate_ctrl_time.dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
						led_animate_ctrl_time.static_ms *= 0.9f * num_leds;
					break;
#					if defined(ENABLE_LED_STATE_TWO_COLOR)
						case LED_STATE_TWO_COLOR:
	//						animation_time_dynamic_ms = LED_ANIMATE_DYNAMIC_TIME_MS *  num_10_led_chunks;
							led_animate_ctrl_time.dynamic_ms = 1;
							led_animate_ctrl_time.static_ms = 1;
							led_animate_ctrl_time.between_ms = 1;
						break;
#					endif
					default:
						led_animate_ctrl_time.dynamic_ms = 1;
						led_animate_ctrl_time.static_ms = 1;
						led_animate_ctrl_time.between_ms = 1;
					break;
				}
				total_time = led_animate_ctrl_time.dynamic_ms + led_animate_ctrl_time.static_ms + led_animate_ctrl_time.between_ms;
				animation_iterations = (g_animation_time_ms[led_speed] / total_time);
				if (!animation_iterations)
				{
					animation_iterations = 1;
				}
				g_animation_iteration_count[strip_num][led_state][led_speed] = animation_iterations;
			}
		}
	}
}




