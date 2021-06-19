// file header goes here..

#include "cmsis_os.h"
#include "board_init.h"
#include "task_create.h"


int main(void)
{
	board_init();

	osKernelInitialize();
	task_create();
	osKernelStart();

	while(1); // should never reach this...
}

