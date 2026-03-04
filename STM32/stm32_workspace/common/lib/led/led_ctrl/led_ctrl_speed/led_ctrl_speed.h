// SRW
#if !defined(LED_CTRL_SPEED_H)
#define LED_CTRL_SPEED_H

#include <stdint.h>
typedef enum
{
	LED_SPEED_1000P,
	LED_SPEED_FIRST = LED_SPEED_1000P,
	LED_SPEED_FAST = LED_SPEED_1000P,
	LED_SPEED_500P,
	LED_SPEED_100P,
	LED_SPEED_NORMAL = LED_SPEED_100P,
	LED_SPEED_50P,
	LED_SPEED_25P,
	LED_SPEED_LAST = LED_SPEED_25P,
	LED_SPEED_SLOW = LED_SPEED_25P,
	NUM_LED_SPEEDS,
	LED_SPEED_INVALID
} led_speed_e;

float led_ctrl_speed(const strip_mask_t mask);
void led_ctrl_speed_adjust(const strip_mask_t mask);
void led_ctrl_speed_reset(const strip_mask_t mask);
void led_ctrl_speed_read_speed(const strip_mask_t mask);
void led_ctrl_speed_write_speed(const strip_mask_t mask, led_speed_e led_speed);



#endif
