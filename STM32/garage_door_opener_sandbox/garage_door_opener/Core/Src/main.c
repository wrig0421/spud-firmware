#include "cmsis_os.h"
#include "main.h"
#include "board_init.h"
#include "task_create.h"
#include "flash_access.h"

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}


int main(void)
{
	board_init();
	//HAL_Delay(3000);
	/* Check and handle if the system was resumed from Standby mode */
#if 0
	if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
	{
		/* Clear Standby flag */
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
	}
	HAL_Delay(5000);
	board_init_set_wkup_src();
	HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE);
#endif
	//HAL_PWR_EnterSTANDBYMode();
	osKernelInitialize();
	task_create();
	osKernelStart();

	while(1); // should never reach this...
}
