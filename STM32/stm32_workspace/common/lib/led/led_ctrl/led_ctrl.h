// SRW

#if !defined(LED_CTRL_H)
#define LED_CTRL_H

#include "FreeRTOS.h"
#include "timers.h"
#include "led_ctrl_brightness.h"
#include "led_ctrl_color.h"
#include "led_ctrl_interrupt.h"
#include "led_ctrl_pause.h"
#include "led_ctrl_power.h"
#include "led_ctrl_speed.h"
#include "led_ctrl_state.h"

typedef enum
{
	LED_CTRL_INTERRUPT_BIT_STATE 				= (1 << 0),
	LED_CTRL_INTERRUPT_BIT_COLOR 				= (1 << 1),
	LED_CTRL_INTERRUPT_BIT_SPEED 				= (1 << 2),
	LED_CTRL_INTERRUPT_BIT_PAUSE_BRIGHTNESS 	= (1 << 3)
	// future go here.
} led_ctrl_interrupt_bit_e;


#pragma pack(1)
typedef struct
{
    led_brightness_e            led_ctrl_brightness;
    led_ctrl_color_info_t       led_ctrl_color_info;
    led_ctrl_pause_state_e      led_ctrl_pause_state;
    led_ctrl_power_factor_t     led_ctrl_power_factor;
    led_speed_e                 led_ctrl_speed;
	led_ctrl_state_info_t		led_ctrl_state_info;
	led_ctrl_interrupt_info_t	led_ctrl_interrupt_info;

} led_ctrl_t;
#pragma pack()


void led_ctrl_timer_callback(TimerHandle_t timer_handle);
bool led_ctrl_time_delay(const strip_mask_t mask, const uint32_t time_ms);
void led_ctrl_init(void);


#endif
