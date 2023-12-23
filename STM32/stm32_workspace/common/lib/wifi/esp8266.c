#include "config.h"

#if defined(BOARD_SPUDGLO_V5)
#include "esp8266.h"





const char* esp8266_at_command_lookup[NUM_ESP8266_AT_COMMANDS] =
{
	[ESP8266_AT_STARTUP] = "AT/r/n",


};


void esp8266_write_block(uint8_t* data, uint16_t len)
{
	uart_access_write_block_esp8266(data, len);
}

void esp8266_read_block(uint8_t* data, uint16_t len)
{
	uart_access_read_block_esp8266(data, len);
}


void esp8266_write_command(esp8266_at_commands_e cmd)
{
	esp8266_write_block((uint8_t *)esp8266_at_command_lookup[ESP8266_AT_STARTUP], sizeof(esp8266_at_command_lookup[ESP8266_AT_STARTUP]));
}


#endif



