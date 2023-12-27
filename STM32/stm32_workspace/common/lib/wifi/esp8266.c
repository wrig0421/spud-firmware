#include "config.h"
#include <string.h>
#include <stdbool.h>

#if defined(BOARD_SPUDGLO_V5)

#include "esp8266.h"





char* esp8266_at_command_lookup[NUM_ESP8266_AT_COMMANDS] =
{
	[ESP8266_AT_STARTUP] = "AT",
	[ESP8266_AT_RESTART] = "AT+RST",
	[ESP8266_AT_CWJAP_CUR] = "AT+CWJAP_CUR",
	[ESP8266_AT_CW_MODE_CUR] = "AT+CWMODE_CUR=2",
	[ESP8266_AT_CIFSR] = "AT+CIFSR",
	[ESP8266_AT_CIPMUX] = "AT+CIPMUX=1",
	[ESP8266_AT_CIPSERVER] = "AT+CIPSERVER=1,80",
	[ESP8266_AT_ECHO] = "ATE=0"
	//[ESP8266_AT_CIPSEND] = "AT+CIPSEND=",
};


void esp8266_write_and_read_block(uint8_t* write_data, uint16_t write_len, uint8_t* read_buf, uint16_t read_len)
{
	uart_access_write_and_read_block_esp8266(write_data, write_len, read_buf, read_len);
}


void esp8266_write_block(uint8_t* data, uint16_t len)
{
	uart_access_write_block_esp8266(data, len);
}


void esp8266_read_block(uint8_t* data, uint16_t len)
{
	uart_access_read_block_esp8266(data, len);
}


uint8_t g_length = 0;
uint8_t g_buffer_tx[20] = {0};

void esp8266_write_command(esp8266_at_commands_e cmd_tag, bool parameters, char* param)
{
	memcpy(g_buffer_tx, esp8266_at_command_lookup[cmd_tag], strlen(esp8266_at_command_lookup[cmd_tag]));
	g_buffer_tx[strlen(esp8266_at_command_lookup[cmd_tag])] = 13;
	g_buffer_tx[strlen(esp8266_at_command_lookup[cmd_tag]) + 1 ] = 10;
}


void esp8266_read_response(esp8266_at_commands_e cmd_tag)
{
	// TODO
}


void esp8266_write_command_and_read_response(esp8266_at_commands_e cmd_tag, bool parameters, char* param, char *read_buf, uint16_t read_len)
{
	memcpy(g_buffer_tx, esp8266_at_command_lookup[cmd_tag], strlen(esp8266_at_command_lookup[cmd_tag]));
	g_buffer_tx[strlen(esp8266_at_command_lookup[cmd_tag])] = 13;
	g_buffer_tx[strlen(esp8266_at_command_lookup[cmd_tag]) + 1 ] = 10;

	esp8266_write_and_read_block(g_buffer_tx, strlen(esp8266_at_command_lookup[cmd_tag]) + 2, (uint8_t *)read_buf, read_len);
}


#endif



