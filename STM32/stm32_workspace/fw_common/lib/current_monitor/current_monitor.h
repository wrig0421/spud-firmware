/*
 * current_monitor.h
 *
 *  Created on: Sep 11, 2022
 *      Author: spud
 */

#ifndef CURRENT_MONITOR_H
#define CURRENT_MONITOR_H


#define CURRENT_MONITOR_MAX_CURRENT_DRAW_A      3
#define CURRENT_MONITOR_MAX_CURRENT_PER_LED_MA  40
typedef float current_t;


void current_monitor_init(void);

#endif /* CURRENT_MONITOR_H */
