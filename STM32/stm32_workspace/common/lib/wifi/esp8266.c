#include "config.h"
#include <string.h>
#include <stdbool.h>
#include "cmsis_os.h"

#if defined(BOARD_SPUDGLO_V5)

#include "uart_access_hal.h"
#include "esp8266.h"


extern char g_general_rx_buffer[200];



char* esp8266_at_command_lookup[NUM_ESP8266_AT_COMMANDS] =
{
	[ESP8266_AT_STARTUP] = "AT",
	[ESP8266_AT_RESTART] = "AT+RST",
	[ESP8266_AT_CWJAP_CUR] = "AT+CWJAP_CUR",
	[ESP8266_AT_CW_MODE_CUR] = "AT+CWMODE_CUR",
	[ESP8266_AT_CIFSR] = "AT+CIFSR",
	[ESP8266_AT_CIPMUX] = "AT+CIPMUX",
	[ESP8266_AT_CIPSERVER] = "AT+CIPSERVER",
	[ESP8266_AT_ECHO] = "ATE=0",
	[ESP8266_AT_CWJAP_CUR] = "AT+CWJAP_CUR",
	[ESP8266_AT_CIPSEND] = "AT+CIPSEND",
	[ESP8266_AT_CIPCLOSE] = "AT+CIPCLOSE",
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
char g_buffer_tx[500] = {0};

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


bool esp8266_write_data(char* data, uint16_t len, uint32_t timeout_ms)
{
	memset(g_buffer_tx, 0, sizeof(g_buffer_tx));
	memcpy(g_buffer_tx, (uint8_t *)data, len);
	g_length = strlen(g_buffer_tx);
	//g_buffer_tx[g_length] = 13;
	//g_buffer_tx[g_length+1] = 10;

	uint32_t timestamp = xTaskGetTickCount();
	esp8266_write_and_read_block((uint8_t *)g_buffer_tx, strlen(g_buffer_tx), (uint8_t *)g_general_rx_buffer, 300);

	while ((xTaskGetTickCount() - timestamp) < timeout_ms) osDelay(100);
	if (!esp8266_response_ok_received(g_general_rx_buffer, 200)) return false;
	return true;
}



uint32_t val = 0;
bool esp8266_write_command_and_read_response(esp8266_at_commands_e cmd_tag, bool parameters, char* param, char *read_buf, uint16_t read_len, uint32_t timeout_ms)
{
	memset(g_buffer_tx, 0, sizeof(g_buffer_tx));
	uint16_t index = strlen(esp8266_at_command_lookup[cmd_tag]);
	memcpy(g_buffer_tx, esp8266_at_command_lookup[cmd_tag], strlen(esp8266_at_command_lookup[cmd_tag]));
	if (parameters)
	{
		g_buffer_tx[index++] = '=';
		strcpy((char *)(g_buffer_tx + index++), param);
		g_buffer_tx[index++ + strlen(param) - 1] = 13;
		g_buffer_tx[index++ + strlen(param) - 1] = 10;
	}
	else
	{
		g_buffer_tx[index++] = 13;
		g_buffer_tx[index++] = 10;
	}
	g_length = strlen(g_buffer_tx);
	uint32_t timestamp = xTaskGetTickCount();
	esp8266_write_and_read_block((uint8_t *)g_buffer_tx, strlen(g_buffer_tx), (uint8_t *)read_buf, read_len);

	while ((xTaskGetTickCount() - timestamp) < timeout_ms) osDelay(100);
//	if ((xTaskGetTickCount() - uart_access_hal_last_rx_tick_time()) < 1000000)
//	{
//		osDelay(100);
//	}
	if (cmd_tag != ESP8266_AT_CWJAP_CUR)
	{
		if (!esp8266_response_ok_received(g_general_rx_buffer, 200)) return false;
	}
	return true;
}


bool esp8266_response_ok_received(char *buffer, uint16_t len)
{

	char ok[2] = "OK";
	for (uint16_t iii = 0; iii < len; iii++)
	{
		if ((buffer[iii] == ok[0]) && (iii < len - strlen(ok)))
		{
			if (buffer[iii + 1] == ok[1]) return true;
		}
	}
	return false;
}


bool esp8266_response_contains(char *buffer, char *msg, uint16_t len)
{
	uint8_t g_str_len = sizeof(msg);
	uint8_t msg_index = 0;
	for (uint16_t iii = 0; iii < len; iii++)
	{
//		for (uint16_t zzz = 0; zzz < strlen(msg); zzz++)
//		{
			if ((uint8_t)buffer[iii] == (uint8_t)msg[msg_index])// && (iii < (len - strlen(msg))))
			{
				msg_index++;
				if (msg_index == (g_str_len))
				{
					return true;
				}
			}
			else
			{
				msg_index = 0;
			}

//		}
	}
	return false;
}



#endif



