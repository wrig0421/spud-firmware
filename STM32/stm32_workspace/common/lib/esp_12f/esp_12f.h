/*
 * current_monitor.h
 *
 *  Created on: Sep 11, 2022
 *      Author: spud
 */

#ifndef ESP_12F_H
#define ESP_12F_H

typedef enum
{
    ESP12F_STARTUP,
    ESP12F_RESTART,
    ESP12F_VERSION_INFO,
    ESP12F_ENTER_DEEP_SLEEP,
    ESP12F_ECHO_ENABLE,
    ESP12F_ECHO_DISABLE,
    ESP12F_RESET,
    ESP12F_UART_CONFIG,
    ESP12F_UART_CURRENT_CONFIG,
    ESP12F_UART_DEFAULT_CONFIG,
    ESP12F_SLEEP,
    ESP12F_SET_MAX_RF_POWER,
    ESP12F_SET_MAX_RF_POWER_VDD33
} esp12f_commands_e;


char* esp12f_construct_command(esp12f_commands_e cmd, uint16_t size);




#endif /* ESP_12F_H */
