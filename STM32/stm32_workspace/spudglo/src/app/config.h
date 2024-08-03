/*
 * config.h
 *
 *  Created on: Aug 6, 2022
 *      Author: splat
 */

#ifndef CONFIG_H
#define CONFIG_H

// major.minor.beta
#define FIRMWARE_VERSION    (0x010101)

// define the board
//#define BOARD_SPUDGLO_BUSINESS_CARD
#define BOARD_SPUDGLO_V7P0
//#define BOARD_SPUDGLO_V6P0
//#define BOARD_SPUDGLO_V5P0
//#define BOARD_SPUDGLO_V4P3
//#define BOARD_SPUDGLO_V4P2
//#define BOARD_SPUDGLO_V4P1
//#define BOARD_SPUD_GLO_V3
//#define BOARD_SPUD_GLO_V2
//#define BOARD_SPUD_GLO_V1
//#define BOARD_MN_WILD_SOUND

#if defined(BOARD_SPUDGLO_V7P0)
	#define BOARD_SPUDGLO_V7
#elif defined(BOARD_SPUDGLO_V6P0)
	#define BOARD_SPUDGLO_V6
#elif defined(BOARD_SPUDGLO_V5P0)
	#define BOARD_SPUDGLO_V5
#elif defined(BOARD_SPUDGLO_V4P3) || defined(BOARD_SPUDGLO_V4P2) || defined(BOARD_SPUDGLO_V4P1)
	#define BOARD_SPUDGLO_V4
#endif

// define the number of strips
#define STRIP_1_LENGTH      400  // bar 302// biker dude 500// MN summit 214 // HELLO SPRING STRIP 1 = 459      //492// playstation controller! - 390// vice city 432// shucmacher - 636// skull sign=200 // 151 for SWENSON SIGN /// FLYNN FARM SIGN = 166!!
#define STRIP_2_LENGTH      0 // bar 220 // HELLO SPRING STRIP 2 = 156
#define STRIP_3_LENGTH      0 //20

#define MAX_NUM_STRIPS		3
//#define ENABLE_LED_STRIP_SYNC

#if defined(STRIP_3_LENGTH) && (0 < STRIP_3_LENGTH)
	#define ENABLE_STRIP_1
	#define ENABLE_STRIP_2
	#define ENABLE_STRIP_3
	#define NUM_ACTIVE_STRIPS	3
	#define NUM_LEDS        	STRIP_1_LENGTH + STRIP_2_LENGTH + STRIP_3_LENGTH
# 	if (STRIP_2_LENGTH) > (STRIP_1_LENGTH)
#		if (STRIP_3_LENGTH) > (STRIP_2_LENGTH)
#			define LARGEST_LED_STRIP_SIZE	STRIP_3_LENGTH
#		else
#			define LARGEST_LED_STRIP_SIZE	STRIP_2_LENGTH
#		endif
#	else
#		if (STRIP_3_LENGTH) > (STRIP_1_LENGTH)
#			define LARGEST_LED_STRIP_SIZE	STRIP_3_LENGTH
#		else
#			define LARGEST_LED_STRIP_SIZE	STRIP_1_LENGTH
#		endif
#	endif

#elif defined(STRIP_2_LENGTH) && (0 < STRIP_2_LENGTH)
	#define ENABLE_STRIP_1
	#define ENABLE_STRIP_2
	#define NUM_ACTIVE_STRIPS	2
	#define NUM_LEDS        	(uint32_t)(STRIP_1_LENGTH + STRIP_2_LENGTH)
# 	if (STRIP_2_LENGTH) > (STRIP_1_LENGTH)
#		define LARGEST_LED_STRIP_SIZE	STRIP_2_LENGTH
#	else
#		define LARGEST_LED_STRIP_SIZE	STRIP_1_LENGTH
#	endif
#elif defined(STRIP_1_LENGTH) && (0 < STRIP_1_LENGTH)
	#define ENABLE_STRIP_1
	#define NUM_ACTIVE_STRIPS		1
	#define NUM_LEDS        		STRIP_1_LENGTH
#	define LARGEST_LED_STRIP_SIZE	STRIP_1_LENGTH
#endif


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

#if (NUM_ACTIVE_STRIPS > 1)
#	define ENABLE_LED_STATE_TWO_COLOR
#endif

#endif
