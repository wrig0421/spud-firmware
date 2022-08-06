/*
 * config.h
 *
 *  Created on: Aug 6, 2022
 *      Author: splat
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

#define BOARD_SPUD_GLO_V3
//#define BOARD_SPUD_GLO_V2
//#define BOARD_SPUD_GLO_V1

#if defined(BOARD_SPUD_GLO_V2) || defined(BOARD_SPUD_GLO_V1)
#define ENABLE_RF_INTERFACE
#endif

#endif /* SRC_CONFIG_H_ */