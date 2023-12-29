#include "config.h"
#include <string.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include <string.h>

#if defined(BOARD_SPUDGLO_V5)

#include "board_specific.h"
#include "uart_access_hal.h"
#include "uart_config_hal.h"
#include "esp8266.h"
#include "esp8266_webserver.h"
#include <string.h>

//char ssid[60] = "\"Pretty Fly for a Wi-Fi\",\"hot_trash**\"";
//char search[4] = "+IPD";
char ssid[60] = "\"Thistle Friend\",\"newroad437\"";
char search[4] = "+IPD";

char html[300] = {"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Connection: close\r\n"
		"\r\n"
		"<!DOCTYPE HTML>"
		"<html>"
		"ESP8266 web server example by Spenny <a href = \"https://electronza.com\">https://electronza.com</a>"
		"</html>\r\n"};

extern bool gb_waiting_on_request;
extern char g_general_rx_buffer[500];

bool esp8266_start_webserver(void)
{
	if (!esp8266_write_command_and_read_response(ESP8266_AT_STARTUP, false, 0, (char *)g_general_rx_buffer, 10, 1000)) while (1);
	if (!esp8266_write_command_and_read_response(ESP8266_AT_RESTART, false, 0, (char *)g_general_rx_buffer, 10, 1000)) while (1);
	osDelay(1000);
	if (!esp8266_write_command_and_read_response(ESP8266_AT_CW_MODE_CUR, true, "1", (char *)g_general_rx_buffer, 10, 500)) while (1);
	if (!esp8266_write_command_and_read_response(ESP8266_AT_CWJAP_CUR, true, ssid, (char *)g_general_rx_buffer, 10, 10000)) while (1);
	if (!esp8266_write_command_and_read_response(ESP8266_AT_CIFSR, false, 0, (char *)g_general_rx_buffer, 75, 1000)) while (1);
	if (!esp8266_write_command_and_read_response(ESP8266_AT_CIPMUX, true, "1", (char *)g_general_rx_buffer, 10, 500)) while (1);
	if (!esp8266_write_command_and_read_response(ESP8266_AT_CIPSERVER, true, "1,80", (char *)g_general_rx_buffer, 30, 500)) while (1);
	gb_waiting_on_request = true;
	while (!esp8266_response_contains(g_general_rx_buffer, search, sizeof(g_general_rx_buffer))) while (1);
	if (!esp8266_write_command_and_read_response(ESP8266_AT_CIPSEND, true, "0,190", (char *)g_general_rx_buffer, 30, 5000)) while (1);
	esp8266_write_data(html, 190, 10000);
	if (!esp8266_write_command_and_read_response(ESP8266_AT_CIPCLOSE, true, "0", (char *)g_general_rx_buffer, 30, 3000)) while (1);
	return true;
}

char esp8266_page_header[] =
{
	"<!DOCTYPE html><html><head>"
	"<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">"
	"<title >"
};

char esp8266_page_mid[] =
{
	"</title></head><body text=#ffffff bgcolor=##4da5b9 align=\"center\">"
};

char esp8266_page_footer[] =
{
	"</body></html>"
};



char g_page[500];
char* esp8266_webserver_make_page(char* title, char* contents)
{
	uint16_t page_index = 0;
	strcpy(g_page, esp8266_page_header);
	page_index = strlen(g_page);
	strcpy(g_page + page_index, title);
	page_index = strlen(g_page);
	strcpy(g_page + page_index, esp8266_page_mid);
	page_index = strlen(g_page);
	strcpy(g_page + page_index, contents);
	page_index = strlen(g_page);
	strcpy(g_page + page_index, esp8266_page_footer);
	return g_page;
}




#endif



