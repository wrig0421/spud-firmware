#include "animation_timer_create.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include "board_init_common.h"

#include "ws2812b.h"
#include "task_create.h"
#include "led_animate.h"
#include "flash_info.h"
#include "semaphore_access.h"
#include "FreeRTOS.h"
#include "task.h"

int main(void)
{
	board_init_common_board_init();
//    flash_info_init();
    task_create();
    animation_timer_create();
    semaphore_create();
	//semaphore_create();
    //reset_ws2812b();
    vTaskStartScheduler();
}
