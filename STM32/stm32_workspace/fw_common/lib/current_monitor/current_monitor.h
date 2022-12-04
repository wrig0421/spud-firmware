/*
 * current_monitor.h
 *
 *  Created on: Sep 11, 2022
 *      Author: spud
 */

#ifndef CURRENT_MONITOR_H
#define CURRENT_MONITOR_H


#define CURRENT_MONITOR_MAX_CURRENT_DRAW_A      (float)20
#define CURRENT_MONITOR_MAX_CURRENT_PER_LED_MA  40
typedef float current_t;

float current_monitor_ratio(void);
void current_monitor_init(void);

#endif /* CURRENT_MONITOR_H */
