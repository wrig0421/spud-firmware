/*
 * config.h
 *
 *  Created on: Aug 6, 2022
 *      Author: splat
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

// define the board!
#define BOARD_SPUD_GLO_V3
//#define BOARD_SPUD_GLO_V2
//#define BOARD_SPUD_GLO_V1

#if defined(BOARD_SPUD_GLO_V2) || defined(BOARD_SPUD_GLO_V1)
#define ENABLE_RF_INTERFACE
#endif

// define the number of strips
#define STRIP_1_LENGTH      200 /// FLYNN FARM SIGN!!
//#define STRIP_2_LENGTH      200
//#define STRIP_3_LENGTH      200
//#define STRIP_4_LENGTH      200
//#define STRIP_5_LENGTH      200


#define ENABLE_LED_STATE_WHITE_COLOR''


#if defined(STRIP_1_LENGTH)
#define NUM_LEDS STRIP_1_LENGTH
#elif defined(STRIP_2_LENGTH)
#define NUM_LEDS STRIP_1_LENGTH + STRIP_2_LENGTH
#elif defined(STRIP_3_LENGTH)
#define NUM_LEDS STRIP_1_LENGTH + STRIP_2_LENGTH + STRIP_3_LENGTH
#elif defined(STRIP_4_LENGTH)
#define NUM_LEDS STRIP_1_LENGTH + STRIP_2_LENGTH + STRIP_3_LENGTH + STRIP_4_LENGTH
#else
#error "invalid number of strips defined!"
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
#if defined(STRIP_4_LENGTH)
#define STRIP_4_CHECK (1 << 3)
#endif

#define STRIP_CHECK (STRIP_1_CHECK + STRIP_2_CHECK + STRIP_3_CHECK + STRIP_4_CHECK)

#if ((STRIP_CHECK != (1)) && (STRIP_CHECK != (3)) && (STRIP_CHECK != (7)) && (STRIP_CHECK != (15)))
#error "error need to define the strips in order"
#endif


#if !defined(STRIP_1_LENGTH) && (defined(STRIP_2_LENGTH) || defined(STRIP_3_LENGTH) || defined(STRIP_4_LENGTH))
#error "Please assign strip 0 as the first strip"
#endif
#if defined(STRIP_1_LENGTH) && (defined(STRIP_2_LENGTH) || defined(STRIP_3_LENGTH) || defined(STRIP_4_LENGTH))
#define MULTIPLE_STRIPS
#endif


#endif /* SRC_CONFIG_H_ */
