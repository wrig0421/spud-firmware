/***********************************
 * @file   color_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(LED_STATE_H)
#define LED_COLOR_H
#include <limits.h>
#include "ws2812b.h"


typedef enum
{
    LED_STATE_FIRST = 0,                    // 0
    LED_STATE_SPELL = LED_STATE_FIRST,      // 0
    //LED_STATE_MINT_NOHBZ,
    LED_STATE_WHITE_COLOR,                  // 1
    LED_STATE_SOLID_COLOR,                  // 2
    LED_STATE_SPARKLE_NO_FILL,              // 3
    LED_STATE_SPARKLE_FILL,                 // 4
    LED_STATE_RAINBOW_CYCLE,                // 5
    LED_STATE_THEATER_CHASE,                // 6
    LED_STATE_THEATER_CHASE_RAINBOW,        // 7
    LED_STATE_FADE_IN_AND_OUT,
//    LED_STATE_HEARTBEAT,// 8
//  LED_STATE_TWINKLE,                      // 9
//    LED_STATE_RUNNING_LIGHTS,             // 10
//    LED_STATE_FIRE,                           // 11
//  LED_STATE_METEOR,                       // 12
//  LED_STATE_STROBE,                       // 13
//  LED_STATE_FADE_IN_AND_OUT_RANDOM,       // 14
    LED_STATE_LAST = LED_STATE_FADE_IN_AND_OUT,
    NUM_LED_STATES,                         // 15
    LED_STATE_SRW_DEBUG,                    // 16 this is technically out of range..
} led_state_e;

#endif
