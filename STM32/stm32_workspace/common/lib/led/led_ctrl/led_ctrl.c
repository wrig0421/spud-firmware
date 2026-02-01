// SRW

#include "FreeRTOS.h"
#include "timers.h"
#include "portmacro.h"

#include "led_ctrl.h"
#include "task_button_press.h"
#include "free_rtos_convenience.h"
#include "ws2812b.h"
#include "led_ctrl_speed.h"
#include "task_button_press.h"

#define LED_CTRL_MASTER_STATE_TIME_MS	180000

extern TimerHandle_t g_led_ctrl_timer_handle;

void led_ctrl_timer_start(void)
{
	xTimerStart(g_led_ctrl_timer_handle, LED_CTRL_MASTER_STATE_TIME_MS);
}


void timer_led_ctrl_callback(TimerHandle_t timer_handle)
{
//#	if defined(ENABLE_LED_STRIP_SYNC)
//		xTaskNotify(g_led_strip_sync_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//#	else
//#		if (1 == NUM_ACTIVE_STRIPS)
//			xTaskNotify(g_led_strip_1_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//#		elif (2 == NUM_ACTIVE_STRIPS)
//			xTaskNotify(g_led_strip_1_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//			xTaskNotify(g_led_strip_2_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//#		elif (3 == NUM_ACTIVE_STRIPS)
//			xTaskNotify(g_led_strip_1_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//			xTaskNotify(g_led_strip_2_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//			xTaskNotify(g_led_strip_3_ctrl_handle, TASK_LED_CTRL_NOTIFICATION_VALUE_TIMER_ELAPSED, eSetValueWithoutOverwrite);
//#		endif
//#	endif
}


static bool led_ctrl_interrupt_occurred(const strip_mask_t mask)
{
#	if defined(ENABLE_BUTTON)
		return task_button_press_interrupt_occurred(mask);
#	else
		return false;
#	endif
}


bool led_ctrl_delay(const strip_mask_t mask, const uint32_t time_ms)
{
    uint32_t ms_count = 0;
    uint32_t ticks = 0;
    if (!time_ms) return false;

    ticks = time_ms / portTICK_PERIOD_MS;

    while (ms_count++ < ticks)
    {
    	free_rtos_delay_ms(portTICK_PERIOD_MS);
        if (led_ctrl_interrupt_occurred(mask)) return true;
    }
    return false;
}


uint32_t g_animation_iteration_count[MAX_NUM_STRIPS][NUM_LED_STATES][NUM_LED_SPEEDS];
#define LED_ANIMATE_DYNAMIC_TIME_MS 	1
#define LED_ANIMATE_ANIMATION_TIME_SEC	90
#define LED_ANIMATE_ANIMATION_TIME_MS	LED_ANIMATE_ANIMATION_TIME_SEC * 1000
uint32_t g_animation_time_ms[NUM_LED_SPEEDS] =
{
	[LED_SPEED_1000P] = LED_ANIMATE_ANIMATION_TIME_MS,
	[LED_SPEED_500P] = LED_ANIMATE_ANIMATION_TIME_MS,
	[LED_SPEED_100P] = LED_ANIMATE_ANIMATION_TIME_MS * 2,
	[LED_SPEED_50P] = LED_ANIMATE_ANIMATION_TIME_MS * 2,
	[LED_SPEED_25P] = LED_ANIMATE_ANIMATION_TIME_MS * 3,
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


