/*
 * config.h
 *
 *  Created on: Aug 6, 2022
 *      Author: splat
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

// major.minor.beta
#define FIRMWARE_VERSION    (0x010101)

// define the board!
#define BOARD_SPUDGLO_V5P0
//#define BOARD_SPUD_GLO_V4P3
//#define BOARD_SPUD_GLO_V4P2
//#define BOARD_SPUD_GLO_V4P1
//#define BOARD_SPUD_GLO_V3
//#define BOARD_SPUD_GLO_V2
//#define BOARD_SPUD_GLO_V1
//#define BOARD_MN_WILD_SOUND

// define the number of strips
#define STRIP_1_LENGTH      100// shucmacher - 636// skull sign=200 // 151 for SWENSON SIGN /// FLYNN FARM SIGN = 166!!
#define STRIP_2_LENGTH      0
#define STRIP_3_LENGTH      0

#define ENABLE_LED_STATE_SPELL
//#define ENABLE_LED_STATE_WHITE_COLOR
//#define ENABLE_LED_STATE_MINT_NOHBZ
//#define ENABLE_LED_STATE_SOLID_COLOR
#define ENABLE_LED_STATE_SPARKLE_NO_FILL
#define ENABLE_LED_STATE_SPARKLE_FILL
#define ENABLE_LED_STATE_RAINBOW_CYCLE
#define ENABLE_LED_STATE_THEATER_CHASE
#define ENABLE_LED_STATE_THEATER_CHASE_RAINBOW
#define ENABLE_LED_STATE_FADE_IN_AND_OUT
#define ENABLE_LED_STATE_TWINKLE

#if defined(BOARD_SPUDGLO_V5P0)
#define BOARD_SPUDGLO_V5
#endif

#if defined(BOARD_SPUD_GLO_V4P3) || defined(BOARD_SPUD_GLO_V4P2) || defined(BOARD_SPUD_GLO_V4P1)
#define BOARD_SPUD_GLO_V4
#endif

#if defined(STRIP_3_LENGTH)
#define NUM_ACTIVE_STRIPS	3
#define NUM_LEDS        	STRIP_1_LENGTH + STRIP_2_LENGTH + STRIP_3_LENGTH
#elif defined(STRIP_2_LENGTH)
#define NUM_ACTIVE_STRIPS	2
#define NUM_LEDS        (STRIP_1_LENGTH + STRIP_2_LENGTH)
#elif defined(STRIP_1_LENGTH)
#define NUM_ACTIVE_STRIPS	1
#define NUM_LEDS        STRIP_1_LENGTH
#else
#error "Error - Invalid number of strips defined!"
#endif

#if defined(BOARD_SPUD_GLO_V2) || defined(BOARD_SPUD_GLO_V1)
#define ENABLE_RF_INTERFACE
#endif

#if defined(STRIP_1_LENGTH) && (defined(STRIP_2_LENGTH) || defined(STRIP_3_LENGTH))
#define MULTIPLE_STRIPS
#endif


#endif /* SRC_CONFIG_H_ */
