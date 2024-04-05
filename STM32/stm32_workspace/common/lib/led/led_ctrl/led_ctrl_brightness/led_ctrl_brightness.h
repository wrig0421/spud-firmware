// SRW
#if !defined(LED_CTRL_BRIGHTNESS_H)
#define LED_CTRL_BRIGHTNESS_H
#include "ws2812b.h"

typedef enum
{
    LED_BRIGHTNESS_FIRST = 0,
    LED_BRIGHTNESS_100_PERCENT  = LED_BRIGHTNESS_FIRST,
    //LED_BRIGHTNESS_50_PERCENT,
    LED_BRIGHTNESS_25_PERCENT,
    LED_BRIGHTNESS_1_PERCENT,
    LED_BRIGHTNESS_LAST         = LED_BRIGHTNESS_1_PERCENT
} led_brightness_e;


void led_ctrl_brightness_adjust(strip_num_e strip_num);


#endif
