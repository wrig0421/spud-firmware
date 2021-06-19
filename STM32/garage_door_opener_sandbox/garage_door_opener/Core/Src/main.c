#include "cmsis_os.h"
#include "main.h"
#include "board_init.h"
#include "task_create.h"
#include "flash_access.h"

int main(void)
{
	board_init();
	/* Check and handle if the system was resumed from Standby mode */
	if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
	{
		/* Clear Standby flag */
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
	}
	HAL_Delay(5000);
	board_init_set_wkup_src();
	HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE);
	//HAL_PWR_EnterSTANDBYMode();
	osKernelInitialize();
	task_create();
	osKernelStart();

	while(1); // should never reach this...
}
