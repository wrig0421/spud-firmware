/*
 * current_monitor.h
 *
 *  Created on: Sep 11, 2022
 *      Author: spud
 */

#if !defined(LED_CTRL_POWER_H)
#define LED_CTRL_POWER_H
#include <stdint.h>

void led_ctrl_power_monitor_set(float value);
float led_ctrl_power_monitor_ratio(void);
void led_ctrl_power_monitor_init(void);

#endif /* LED_CTRL_POWER_H */
