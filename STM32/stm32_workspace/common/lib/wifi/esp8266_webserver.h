#if !defined(ESP8266_WEBSERVER_H)
#define ESP8266_WEBSERVER_H

#include "config.h"
#include <stdint.h>
#include <stdbool.h>

#if defined(BOARD_SPUDGLO_V5)

#include <stdint.h>

bool esp8266_start_webserver(void);
char* esp8266_webserver_make_page(char* title, char* contents);


#endif

#endif



