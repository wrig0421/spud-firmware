#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include "board_init_common.h"
#include "cmsis_os.h"
#include "task_create.h"


int main(void)
{
    board_init_common_board_init();
	task_create();
	osKernelStart();
}
