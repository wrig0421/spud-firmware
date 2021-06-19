/*
 * task_sensor_access.c
 *
 *  Created on: Dec 7, 2020
 *      Author: spud
 */
#include <stdint.h>
#include "gt_521fx_driver.h"
#include "ssd1351_driver.h"
#include "flash_access.h"
#include "packet_queue.h"
#include "cmsis_os.h"
#include "task_sensor_access.h"


typedef enum
{
	GT521FX_STATE_ENROLL,
	GT521FX_STATE_VERIFY,
	GT521FX_STATE_IDENTIFY,
	GT521FX_STATE_DELETE,
	GT521FX_STATE_ERROR,
	GT521FX_STATE_NOTHING_TO_DO,
} gt521fx_state_e;


gt521fx_state_e gt521fx_state = GT521FX_STATE_ENROLL;


void task_sensor_access_entry(void *argument)
{
	bool first_pass = true;
	while(1)
	{
		if (first_pass)
		{
			gt521fx_open();
			while (!packet_rsp_was_received()) osDelay(500);
			gt521fx_led_on();
			while (!packet_rsp_was_received()) osDelay(500);
			first_pass = false;
		}
		else
		{ 
			switch(gt521fx_state)
			{
				case GT521FX_STATE_ENROLL:
					// this state should only be entered if correct keypad buttons are pressed

					// my thoughts are that enroll state would be entered via button press		
					ssd1351_printf("GT521FX enroll state");
					
					gt521fx_start_enrollment(flash_access_gt521fx_last_id() + 1);
					while (!packet_rsp_was_received()) osDelay(500);
					if (gt521fx_nack_flag()) gt521fx_state = GT521FX_STATE_ERROR;
					
					ssd1351_printf("\nPlace finger on sensor");
					while (!gt521fx_finger_is_pressed_flag()) 
					{
						gt521fx_finger_is_pressed();
						while (!packet_rsp_was_received()) osDelay(500);
					}
					
					gt521fx_capture_finger();
					while (!packet_rsp_was_received()) osDelay(500);
					if (gt521fx_nack_flag()) gt521fx_state = GT521FX_STATE_ERROR;
					
					gt521fx_enrollment(GT521FX_ENROLLMENT_STAGE_FIRST);
					while (!packet_rsp_was_received()) osDelay(500);
					if (gt521fx_nack_flag()) gt521fx_state = GT521FX_STATE_ERROR;
					
					ssd1351_printf("\nRemove finger");
					while (gt521fx_finger_is_pressed_flag()) 
					{
						gt521fx_finger_is_pressed();
						while (!packet_rsp_was_received()) osDelay(500);
					}
					ssd1351_clear_screen();
					ssd1351_printf("\nPlace finger on sensor");
					while (!gt521fx_finger_is_pressed_flag()) 
					{
						gt521fx_finger_is_pressed();
						while (!packet_rsp_was_received()) osDelay(500);
					}
					
					gt521fx_capture_finger();
					while (!packet_rsp_was_received()) osDelay(500);
					if (gt521fx_nack_flag()) gt521fx_state = GT521FX_STATE_ERROR;
					
					gt521fx_enrollment(GT521FX_ENROLLMENT_STAGE_SECOND);
					while (!packet_rsp_was_received()) osDelay(500);
					if (gt521fx_nack_flag()) gt521fx_state = GT521FX_STATE_ERROR;
					
					ssd1351_printf("\nRemove finger");
					while (gt521fx_finger_is_pressed_flag()) 
					{
						gt521fx_finger_is_pressed();
						while (!packet_rsp_was_received()) osDelay(500);
					}
					
					ssd1351_printf("\nPlace finger on sensor");
					while (!gt521fx_finger_is_pressed_flag()) 
					{
						gt521fx_finger_is_pressed();
						while (!packet_rsp_was_received()) osDelay(500);
					}
					
					gt521fx_capture_finger();
					while (!packet_rsp_was_received()) osDelay(500);
					if (gt521fx_nack_flag()) gt521fx_state = GT521FX_STATE_ERROR;
					
					gt521fx_enrollment(GT521FX_ENROLLMENT_STAGE_THIRD);
					while (!packet_rsp_was_received()) osDelay(500);
					if (gt521fx_nack_flag()) gt521fx_state = GT521FX_STATE_ERROR;
					
					ssd1351_printf("\nRemove finger");
					while (gt521fx_finger_is_pressed_flag()) 
					{
						gt521fx_finger_is_pressed();
						while (!packet_rsp_was_received()) osDelay(500);
					}
					flash_access_enroll_update();
					ssd1351_printf("\nEnroll successful");
					gt521fx_state = GT521FX_STATE_VERIFY;
				break;
				case GT521FX_STATE_IDENTIFY:
					
				break;
				case GT521FX_STATE_VERIFY:
				break;
				case GT521FX_STATE_DELETE:
				break;
				case GT521FX_STATE_ERROR:
					ssd1351_printf("\nERROR");
					while(1);
				break;
				case GT521FX_STATE_NOTHING_TO_DO:
					osDelay(1000);
				break;
			}
		}
	}
}



