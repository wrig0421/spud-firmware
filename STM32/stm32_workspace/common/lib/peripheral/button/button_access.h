/***********************************
 * @file   animate_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(BUTTON_ACCESS_H)
#define BUTTON_ACCESS_H
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>


typedef enum
{
    BUTTON_A = 0, 	// speed
	BUTTON_FIRST = BUTTON_A,
	BUTTON_B, 		// state
	BUTTON_C, 		// color
	BUTTON_D, 		// pause
    NUM_BUTTONS,
	BUTTON_INVALID = UINT32_MAX - 1
} button_e;


typedef enum
{
    BUTTON_ISR_SPEED = 0,
    BUTTON_ISR_STATE,
	BUTTON_ISR_COLOR,
	BUTTON_ISR_PAUSE,
    NUM_BUTTON_ISRS,
	BUTTON_ISR_INVALID
} button_isr_e;


void button_access_setup(void);
bool button_access_button_is_active(button_e btn);
bool button_access_button_is_not_active(button_e btn);
bool button_access_button_is_high(button_e btn);
bool button_access_button_is_low(button_e btn);


#endif
