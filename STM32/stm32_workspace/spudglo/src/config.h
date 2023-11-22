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

#define BOARD_SPUD_GLO_V4P3
//#define BOARD_SPUD_GLO_V4P2
//#define BOARD_SPUD_GLO_V4P1
//#define BOARD_SPUD_GLO_V3
//#define BOARD_SPUD_GLO_V2
//#define BOARD_SPUD_GLO_V1
//#define BOARD_MN_WILD_SOUND

// define the number of strips
#define STRIP_1_LENGTH      151 // 151 for SWENSON SIGN /// FLYNN FARM SIGN = 166!!
//#define STRIP_2_LENGTH      215
//#define STRIP_3_LENGTH      200

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

#if defined(BOARD_SPUD_GLO_V4P3) || defined(BOARD_SPUD_GLO_V4P2) || defined(BOARD_SPUD_GLO_V4P1)
#define BOARD_SPUD_GLO_V4
#endif


#if defined(STRIP_3_LENGTH)
#define NUM_LEDS        STRIP_1_LENGTH + STRIP_2_LENGTH + STRIP_3_LENGTH
#elif defined(STRIP_2_LENGTH)
#define NUM_LEDS        (STRIP_1_LENGTH + STRIP_2_LENGTH)
#elif defined(STRIP_1_LENGTH)
#define NUM_LEDS        STRIP_1_LENGTH
#else
#error "Error - Invalid number of strips defined!"
#endif

#if defined(STRIP_1_LENGTH)
#define STRIP_1_CHECK (1 << 0)
#endif
#if defined(STRIP_2_LENGTH)
#define STRIP_2_CHECK (1 << 1)
#endif
#if defined(STRIP_3_LENGTH)
#define STRIP_3_CHECK (1 << 2)
#endif

#define STRIP_CHECK (STRIP_1_CHECK + STRIP_2_CHECK + STRIP_3_CHECK)

#if defined(BOARD_SPUD_GLO_V2) || defined(BOARD_SPUD_GLO_V1)
#define ENABLE_RF_INTERFACE
#endif


#if ((STRIP_CHECK != (1)) && (STRIP_CHECK != (3)) && (STRIP_CHECK != (7)))
#error "Error - Need to define the strips in order.   If strip 2 is defined then strip 1 must be defined."
#endif


#if !defined(STRIP_1_LENGTH) && (defined(STRIP_2_LENGTH) || defined(STRIP_3_LENGTH))
#error "Error - Please define the strips in order!"
#endif

#if defined(STRIP_1_LENGTH) && (defined(STRIP_2_LENGTH) || defined(STRIP_3_LENGTH))
#define MULTIPLE_STRIPS
#endif


#endif /* SRC_CONFIG_H_ */
