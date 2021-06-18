/*
 * task_sensor_access.c
 *
 *  Created on: Dec 7, 2020
 *      Author: spud
 */
#include <stdint.h>
#include "gt_521fx_driver.h"
#include "cmsis_os.h"
#include "task_sensor_access.h"


void task_display_update_entry(void *argument)
{
  /* USER CODE BEGIN task_sensor_access_entry */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1000);
	  /*
	  gt521fx_fingerprint_init();
	  gt521fx_enroll_finger(3);
	  */
	  //while(1);

  }
  /* USER CODE END task_sensor_access_entry */
}
