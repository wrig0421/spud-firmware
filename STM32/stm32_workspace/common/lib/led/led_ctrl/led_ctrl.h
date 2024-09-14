// SRW

#if !defined(LED_CTRL_H)
#define LED_CTRL_H

#include "FreeRTOS.h"
#include "timers.h"
#include "led_ctrl_state.h"
#include "led_ctrl_color.h"
#include "led_ctrl_speed.h"
#include "led_ctrl_brightness.h"

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
	union
	{
		struct
		{
			uint8_t state 				: 1;
			uint8_t color 				: 1;
			uint8_t speed 				: 1;
			uint8_t pause_brightness	: 1;
			uint8_t rsvd  				: 4;
		} bits;
		uint8_t flat_interrupt_status;
	};
} led_ctrl_interrupt_status_t;
#pragma pack()


typedef led_ctrl_interrupt_status_t* p_led_ctrl_interrupt_status_t;

#pragma pack(1)
typedef struct
{
	union
	{
		led_ctrl_interrupt_status_t 	interrupt_status;
		uint8_t 						interrupt_status_flat;
	} minor;
	bool minor_interrupt_flag;
	union
	{
		led_ctrl_interrupt_status_t 	interrupt_status;
		uint8_t 						interrupt_status_flat;
	} major;
	bool major_interrupt_flag;
	bool major_interrupt_transition_cmplt_flag;
} led_ctrl_interrupt_info_t;
#pragma pack()

#pragma pack(1)
typedef struct
{
	led_ctrl_state_info_t		led_state_info;
	led_ctrl_color_info_t		led_color_info;
	led_ctrl_interrupt_info_t	led_interrupt_info;
	led_speed_e					led_speed;
	led_brightness_e			led_brightness;
} led_ctrl_t;
#pragma pack()




void led_ctrl_timer_callback(TimerHandle_t timer_handle);

bool led_ctrl_delay(const uint32_t time_ms);
void led_ctrl_init(void);


#endif
