#if !defined(ESP8266_H)
#define ESP8266_H

#include "config.h"

#if defined(BOARD_SPUDGLO_V5)

#include <stdint.h>
typedef enum
{
	ESP8266_AT_STARTUP,
	ESP8266_AT_RESTART,
	ESP8266_AT_VERSION_INFO,
	ESP8266_AT_DEEPSLEEP,
	ESP8266_AT_ECHO,
	ESP8266_AT_FACTORY_RESET,
	ESP8266_AT_UART_CONFIG,
	ESP8266_AT_CUR_UART_CONFIG,
	ESP8266_AT_DEFAULT_UART_CONFIG,
	ESP8266_AT_SLEEP,
	ESP8266_AT_RF_POWER,
	ESP8266_AT_RF_VDD,
	//ESP8266_AT_CW_MODE, // DEPRECATED
	ESP8266_AT_CW_MODE_CUR,
	ESP8266_AT_CW_MODE_DEF,
	//ESP8266_AT_CWJAP,
	ESP8266_AT_CWJAP_CUR,
	ESP8266_AT_CWJAP_DEF,
	ESP8266_AT_CWLAPORT,
	ESP8266_AT_CWLAP,
	ESP8266_AT_CWQAP,
	ESP8266_AT_CWSAP,
	ESP8266_AT_CWSAP_CUR,
	ESP8266_AT_CWSAP_DEF,
	ESP8266_AT_CWLIF,
	ESP8266_AT_CWDHCP,
	ESP8266_AT_CWDHCP_CUR,
	ESP8266_AT_CWDHCP_DEF,
	ESP8266_AT_CWDHCPS_CUR,
	ESP8266_AT_CWDHCPS_DEF,
	ESP8266_AT_CWAUTOCONN,
	ESP8266_AT_CIFSR,
	ESP8266_AT_CIPMUX,
	ESP8266_AT_CIPSERVER,

	NUM_ESP8266_AT_COMMANDS
} esp8266_at_commands_e;


void esp8266_write_block(uint8_t* data, uint16_t len);
void esp8266_read_block(uint8_t* data, uint16_t len);
void esp8266_write_command(esp8266_at_commands_e cmd, bool parameters, char* param);
void esp8266_write_command_and_read_response(esp8266_at_commands_e cmd_tag, bool parameters, char* param, char *read_buf, uint16_t read_len);
void esp8266_write_and_read_block(uint8_t* write_data, uint16_t write_len, uint8_t* read_buf, uint16_t read_len);
#endif

#endif



