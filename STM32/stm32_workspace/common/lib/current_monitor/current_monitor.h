/*
 * current_monitor.h
 *
 *  Created on: Sep 11, 2022
 *      Author: spud
 */

#ifndef CURRENT_MONITOR_H
#define CURRENT_MONITOR_H
#include <stdint.h>

void current_monitor_set(float value);
float current_monitor_ratio(void);
void current_monitor_init(void);

#endif /* CURRENT_MONITOR_H */
