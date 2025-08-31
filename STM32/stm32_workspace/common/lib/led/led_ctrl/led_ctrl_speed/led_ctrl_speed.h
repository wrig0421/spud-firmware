// SRW
#if !defined(LED_CTRL_SPEED_H)
#define LED_CTRL_SPEED_H

#include <stdint.h>
typedef enum
{
	LED_SPEED_1,
	LED_SPEED_FIRST = LED_SPEED_1,
	LED_SPEED_FAST = LED_SPEED_1,
	LED_SPEED_2,

	LED_SPEED_3,
	LED_SPEED_NORMAL = LED_SPEED_3,
	LED_SPEED_4,

	LED_SPEED_5,
//	LED_SPEED_6,
	LED_SPEED_LAST = LED_SPEED_5,
	LED_SPEED_SLOW = LED_SPEED_5,
	NUM_LED_SPEEDS,
	LED_SPEED_INVALID
} led_speed_e;

float led_ctrl_speed(const strip_mask_t mask);
void led_ctrl_speed_adjust(const strip_mask_t mask);
void led_ctrl_speed_reset(const strip_mask_t mask);



#endif
