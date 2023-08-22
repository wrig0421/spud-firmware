#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include "board_init_common.h"
#include "cmsis_os.h"
#include "ws2812b.h"
#include "semaphore_create.h"
#include "task_create.h"
#include "animate_led.h"
#include "flash_info.h"


int main(void)
{
    board_init_common_board_init();
    flash_info_init();
    task_create();
	//semaphore_create();
    reset_ws2812b();
	osKernelStart();
}
