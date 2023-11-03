// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "task_firmware_update.h"
#include "esp_12f.h"
#include "board_specific.h"


void task_firmware_update(void *argument)
{
    //gpio_config_esp8266_en();
    osDelay(500);
    while (1)
    {
        esp12f_send_command(ESP12F_VERSION_INFO, 0);
        osDelay(500);
    }
}
