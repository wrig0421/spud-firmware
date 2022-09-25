// SRW
#include "main.h"
#include <stdbool.h>
#include <stdint.h>

#include "board_init_common.h"
//#include "board_specific.h"
#include "ws2812b.h"
#include "cmsis_os.h"
#include "task_create.h"
#include <stdbool.h>
#include "color_led.h"
#include "animate_led.h"


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    board_init();
    //reset_ws2812b();
	task_create();
	osKernelStart();
}



