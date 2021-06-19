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


typedef enum
{
	GT521FX_STATE_ENROLL,
	GT521FX_STATE_VERIFY,
	GT521FX_STATE_DELETE,
	GT521FX_STATE_NOTHING_TO_DO,
} gt521fx_state_e;


gt521fx_state_e gt521fx_state = GT521FX_STATE_ENROLL;


void task_sensor_access_entry(void *argument)
{

	while(1)
	{
		switch(gt521fx_state)
		{
			case GT521FX_STATE_ENROLL:
				gt521fx_enroll_finger(5);
			break;
			case GT521FX_STATE_VERIFY:
			break;
			case GT521FX_STATE_DELETE:
			break;
			case GT521FX_STATE_NOTHING_TO_DO:
				osDelay(1000);
			break;
		}
	}
}



