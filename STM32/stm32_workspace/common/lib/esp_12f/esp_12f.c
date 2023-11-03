/*
 * current_monitor.c
 *
 *  Created on: Sep 11, 2022
 *      Author: spud
 */
#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "esp_12f.h"
#include <string.h>
#include "spi_access_hal.h"
#include "board_specific.h"

char *g_esp12f_str;
uint32_t gv_size = 0;
char* esp12f_construct_command(esp12f_commands_e cmd, uint16_t size)
{
    bool param = false;
    switch (cmd)
    {
        case ESP12F_STARTUP:
            g_esp12f_str = "AT\r\n";
            gv_size = strlen(g_esp12f_str);

        break;
        case ESP12F_RESTART:
        break;
        case ESP12F_VERSION_INFO:
            param = true;
            g_esp12f_str = "AT+GMR\r\n";
        break;
        case ESP12F_ENTER_DEEP_SLEEP:
            param = true;
            g_esp12f_str = "AT+GSL";
        break;
        case ESP12F_ECHO_ENABLE:
            g_esp12f_str = "AT+ATE1";
        break;
        case ESP12F_ECHO_DISABLE:
            g_esp12f_str = "AT+ATE0";
        break;
        case ESP12F_RESET:
        break;
        case ESP12F_UART_CONFIG:
            g_esp12f_str = "AT+UART";
        break;
        case ESP12F_UART_CURRENT_CONFIG:
            g_esp12f_str = "AT+UART_CUR";
        break;
        case ESP12F_UART_DEFAULT_CONFIG:
            g_esp12f_str = "AT+UART_DEF";
        break;
        case ESP12F_SLEEP:
            g_esp12f_str = "AT+SLEEP";
        break;
        case ESP12F_SET_MAX_RF_POWER:
            g_esp12f_str = "AT+RFPOWER";
        break;
        case ESP12F_SET_MAX_RF_POWER_VDD33:
            g_esp12f_str = "AT+RFVDD";
       break;
    }
    return g_esp12f_str;
}

char g_tx_buffer[10];
char g_rx_buffer[10];


void esp12f_send_command(esp12f_commands_e cmd, uint8_t* tx_buffer, uint8_t *rx_buffer)
{
    gpio_config_esp8266_select_chip();
    esp12f_construct_command(ESP12F_STARTUP,0);
    strcpy(g_tx_buffer, g_esp12f_str);
    spi_access_write_and_read(g_tx_buffer, (uint8_t*)g_rx_buffer, strlen(g_esp12f_str));
    gpio_config_esp8266_deselect_chip();
    gpio_config_esp8266_select_chip();

    esp12f_construct_command(ESP12F_VERSION_INFO,0);
    strcpy(g_tx_buffer, g_esp12f_str);
    spi_access_write_and_read(g_tx_buffer, (uint8_t*)g_rx_buffer, strlen(g_esp12f_str));
    gpio_config_esp8266_deselect_chip();

}

