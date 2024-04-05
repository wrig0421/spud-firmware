// SRW
#if !defined(LED_CTRL_SPEED_H)
#define LED_CTRL_SPEED_H

#include <stdint.h>
typedef enum
{
	LED_SPEED_FIRST,
	LED_SPEED_10X = LED_SPEED_FIRST,
	LED_SPEED_5X,
	//LED_SPEED_2X,
	LED_SPEED_1X,
	LED_SPEED_0P5X,
	LED_SPEED_0P25X,
	//LED_SPEED_0P1X,
	LED_SPEED_LAST = LED_SPEED_0P25X,
	NUM_SPEEDS
} led_speed_e;

float led_ctrl_speed(const strip_mask_t mask);
void led_ctrl_speed_adjust(const strip_mask_t mask);
void led_ctrl_speed_reset(const strip_mask_t mask);



#endif
