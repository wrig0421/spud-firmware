/***********************************
 * @file   color_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(LED_STATE_H)
#define LED_STATE_H
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


//const led_ctrl_state_parameters_t g_led_ctrl_state_iterations[NUM_LED_STATES] =
//{
//    [LED_STATE_SPELL] =
//    {
//        .led_state_inner_animation_delay_ms[LED_SPEED_1000P]        = 0,
//        .led_state_inner_animation_delay_ms[LED_SPEED_500P]         = 20,
//        .led_state_inner_animation_delay_ms[LED_SPEED_100P]         = 66,
//        .led_state_inner_animation_delay_ms[LED_SPEED_50P]          = 132,
//        .led_state_inner_animation_delay_ms[LED_SPEED_25P]          = 250,
//    },
//    [LED_STATE_WHITE_COLOR] =
//    {
//        .led_state_between_animation_delay_ms[LED_SPEED_1000P]      = 10000,
//        .led_state_between_animation_delay_ms[LED_SPEED_500P]       = 10000,
//        .led_state_between_animation_delay_ms[LED_SPEED_100P]       = 10000,
//        .led_state_between_animation_delay_ms[LED_SPEED_50P]        = 10000,
//        .led_state_between_animation_delay_ms[LED_SPEED_25P]        = 10000,
//    },
//    [LED_STATE_SOLID_COLOR] =
//    {
//        .led_state_between_animation_delay_ms[LED_SPEED_1000P]      = 5000,
//        .led_state_between_animation_delay_ms[LED_SPEED_500P]       = 5000,
//        .led_state_between_animation_delay_ms[LED_SPEED_100P]       = 5000,
//        .led_state_between_animation_delay_ms[LED_SPEED_50P]        = 5000,
//        .led_state_between_animation_delay_ms[LED_SPEED_25P]        = 5000,
//    },
//    [LED_STATE_SPARKLE_NO_FILL] =
//    {
//        .led_state_inner_animation_delay_ms[LED_SPEED_1000P]        = 0,
//        .led_state_inner_animation_delay_ms[LED_SPEED_500P]         = 20,
//        .led_state_inner_animation_delay_ms[LED_SPEED_100P]         = 150,
//        .led_state_inner_animation_delay_ms[LED_SPEED_50P]          = 132,
//        .led_state_inner_animation_delay_ms[LED_SPEED_25P]          = 250,
//    },
//    [LED_STATE_SPARKLE_FILL] =
//    {
//        .led_state_inner_animation_delay_ms[LED_SPEED_1000P]        = 0,
//        .led_state_inner_animation_delay_ms[LED_SPEED_500P]         = 20,
//        .led_state_inner_animation_delay_ms[LED_SPEED_100P]         = 66,
//        .led_state_inner_animation_delay_ms[LED_SPEED_50P]          = 132,
//        .led_state_inner_animation_delay_ms[LED_SPEED_25P]          = 250,
//    },
//    [LED_STATE_RAINBOW_CYCLE] =
//    {
//        .led_state_inner_animation_delay_ms[LED_SPEED_1000P]        = 0,
//        .led_state_inner_animation_delay_ms[LED_SPEED_500P]         = 20,
//        .led_state_inner_animation_delay_ms[LED_SPEED_100P]         = 66,
//        .led_state_inner_animation_delay_ms[LED_SPEED_50P]          = 132,
//        .led_state_inner_animation_delay_ms[LED_SPEED_25P]          = 250,
//    },
//    [LED_STATE_THEATER_CHASE] =
//    {
//        .led_state_inner_animation_delay_ms[LED_SPEED_1000P]        = 10,
//        .led_state_inner_animation_delay_ms[LED_SPEED_500P]         = 45,
//        .led_state_inner_animation_delay_ms[LED_SPEED_100P]         = 66,
//        .led_state_inner_animation_delay_ms[LED_SPEED_50P]          = 132,
//        .led_state_inner_animation_delay_ms[LED_SPEED_25P]          = 250,
//    },
//    [LED_STATE_THEATER_CHASE_RAINBOW] =
//    {
//        .led_state_inner_animation_delay_ms[LED_SPEED_1000P]        = 10,
//        .led_state_inner_animation_delay_ms[LED_SPEED_500P]         = 45,
//        .led_state_inner_animation_delay_ms[LED_SPEED_100P]         = 66,
//        .led_state_inner_animation_delay_ms[LED_SPEED_50P]          = 132,
//        .led_state_inner_animation_delay_ms[LED_SPEED_25P]          = 250,
//    },
//    [LED_STATE_FADE_IN_AND_OUT] =
//    {
//        .led_state_inner_animation_delay_ms[LED_SPEED_1000P]        = 10,
//        .led_state_inner_animation_delay_ms[LED_SPEED_500P]         = 45,
//        .led_state_inner_animation_delay_ms[LED_SPEED_100P]         = 66,
//        .led_state_inner_animation_delay_ms[LED_SPEED_50P]          = 132,
//        .led_state_inner_animation_delay_ms[LED_SPEED_25P]          = 250,
//    },
////  [LED_STATE_HEARTBEAT] =
////  {
////      .led_state_inner_animation_delay_ms[LED_SPEED_1000P]        = 50,
////      .led_state_inner_animation_delay_ms[LED_SPEED_500P]         = 100,
////      .led_state_inner_animation_delay_ms[LED_SPEED_100P]     = 150,
////      .led_state_inner_animation_delay_ms[LED_SPEED_50P]      = 200,
////      .led_state_inner_animation_delay_ms[LED_SPEED_25P]          = 250,
////  },
////  [LED_STATE_TWINKLE] =
////  {
////      .led_state_inner_animation_delay_ms[LED_SPEED_1000P]        = 0,
////      .led_state_inner_animation_delay_ms[LED_SPEED_500P]         = 50,
////      .led_state_inner_animation_delay_ms[LED_SPEED_100P]         = 100,
////      .led_state_inner_animation_delay_ms[LED_SPEED_50P]          = 150,
////      .led_state_inner_animation_delay_ms[LED_SPEED_25P]          = 200,
////  },
////# if (NUM_ACTIVE_STRIPS > 1) && defined(ENABLE_LED_STATE_TWO_COLOR)
////      [LED_STATE_TWO_COLOR] =
////      {
////          .led_state_between_animation_delay_ms[LED_SPEED_1000P]  = 5000,
////          .led_state_between_animation_delay_ms[LED_SPEED_500P]   = 5000,
////          .led_state_between_animation_delay_ms[LED_SPEED_100P]   = 5000,
////          .led_state_between_animation_delay_ms[LED_SPEED_50P]    = 5000,
////          .led_state_between_animation_delay_ms[LED_SPEED_25P]    = 5000,
////      }
////#   endif
//};
