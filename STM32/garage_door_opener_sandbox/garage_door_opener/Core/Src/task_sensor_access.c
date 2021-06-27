/*
 * task_sensor_access.c
 *
 *  Created on: Dec 7, 2020
 *      Author: spud
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "gt_521fx_driver.h"
#include "ssd1351_driver.h"
#include "flash_access.h"
#include "packet_queue.h"
#include "serial_com.h"
#include "cmsis_os.h"
#include "task_sensor_access.h"

bool refresh_screen = true;
gt521fx_state_e gt521fx_state = GT521FX_STATE_IDENTIFY;
bool g_gt521fx_forced_state_change = false;


void set_screen_refresh(void)
{
	refresh_screen = true;
}


gt521fx_state_e gt521fx_current_state(void)
{
	return gt521fx_state;
}

void gt521fx_set_state(uint16_t key)
{
	refresh_screen = true;
    g_gt521fx_forced_state_change = true;
	gt521fx_state = (gt521fx_state_e)key;
}


void task_sensor_access_entry(void *argument)
{
	bool first_pass = true;

	char last_id[3] = {0, 0, 0};
	while(1)
	{
		if (first_pass)
		{
			gt521fx_open();
			while (!packet_rsp_was_received())
			{
				osDelay(1);
			}
			gt521fx_led_on();
			while (!packet_rsp_was_received())
			{
				osDelay(1);
			}
			first_pass = false;
		}
		else
		{ 
			switch(gt521fx_state)
			{
				case GT521FX_STATE_ADMIN:
					if (refresh_screen)
					{
						refresh_screen = false;
						ssd1351_clear_screen();
						ssd1351_printf("Admin Menu\n");
						ssd1351_printf("1. Enroll\n");
						ssd1351_printf("2. Delete last\n");
						ssd1351_printf("3. Delete all\n");
						ssd1351_printf("4. Identify\n");
						// print FW info in ADMIN menu
						ssd1351_printf("# enrolled ");
						ssd1351_printf(itoa(flash_access_gt521fx_last_id(), last_id, 10));
						ssd1351_write_buffer_to_display();
					}
				break;
				case GT521FX_STATE_ENROLL:
					ssd1351_clear_screen(); // always clear here
					ssd1351_printf("GT521FX enroll state");
					gt521fx_start_enrollment(flash_access_gt521fx_last_id() + 1);
					while (!packet_rsp_was_received()) osDelay(500);
					if (gt521fx_nack_flag()) gt521fx_state = GT521FX_STATE_ERROR;
					
					ssd1351_printf("\nPlace finger on sensor");
					ssd1351_write_buffer_to_display();
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
					ssd1351_write_buffer_to_display();

					while (gt521fx_finger_is_pressed_flag()) 
					{
						gt521fx_finger_is_pressed();
						while (!packet_rsp_was_received()) osDelay(500);
					}
					ssd1351_clear_screen();
					ssd1351_printf("\nPlace finger on sensor");
					ssd1351_write_buffer_to_display();
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
					ssd1351_write_buffer_to_display();
					while (gt521fx_finger_is_pressed_flag()) 
					{
						gt521fx_finger_is_pressed();
						while (!packet_rsp_was_received()) osDelay(500);
					}
					ssd1351_clear_screen(); // always clear here
					ssd1351_printf("\nPlace finger on sensor");
					ssd1351_write_buffer_to_display();
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
					ssd1351_write_buffer_to_display();
					while (gt521fx_finger_is_pressed_flag()) 
					{
						gt521fx_finger_is_pressed();
						while (!packet_rsp_was_received()) osDelay(500);
					}
					ssd1351_clear_screen(); // always clear here
					flash_access_enroll_update();
					ssd1351_printf("\nEnroll successful");
					ssd1351_write_buffer_to_display();
					refresh_screen = true;
					gt521fx_state = GT521FX_STATE_ADMIN;
				break;
				case GT521FX_STATE_DELETE:
					refresh_screen = true;
					gt521fx_delete_fingerprint(flash_access_gt521fx_last_id());
					flash_access_gt521fx_remove_last_id();
					ssd1351_clear_screen();
					ssd1351_printf("\nLast print deleted!");
					ssd1351_write_buffer_to_display();
					osDelay(3000);
					refresh_screen = true;
					gt521fx_state = GT521FX_STATE_ADMIN;
				break;
				case GT521FX_STATE_DELETE_ALL:
					refresh_screen = true;
					gt521fx_delete_all_fingerprints();
					flash_access_gt521fx_reset_id_count();
					ssd1351_clear_screen();
					ssd1351_printf("\nAll prints deleted!");
					ssd1351_write_buffer_to_display();
					osDelay(3000);
					refresh_screen = true;
					gt521fx_state = GT521FX_STATE_ADMIN;
				break;
				case GT521FX_STATE_IDENTIFY:
					g_gt521fx_forced_state_change = false;
					gt521fx_finger_is_pressed_clear();
					refresh_screen = true;
					if (refresh_screen)
					{
						refresh_screen = false;
						ssd1351_clear_screen(); // always clear here
						ssd1351_printf("GT521FX identify state");
						ssd1351_printf("\nPlace finger on sensor");
						ssd1351_write_buffer_to_display();
					}
					while (!gt521fx_finger_is_pressed_flag() && !g_gt521fx_forced_state_change)
					{
						gt521fx_finger_is_pressed();
						while (!packet_rsp_was_received()) osDelay(500);
					}
					if (g_gt521fx_forced_state_change)
					{
						refresh_screen = true;
						break;
					}
					else
					{
						gt521fx_capture_finger();
						while(!pkt_received && !packet_rsp_was_received()) osDelay(500);
						//while (!packet_rsp_was_received()) osDelay(500);
						if (gt521fx_nack_flag())
						{
							gt521fx_state = GT521FX_STATE_ERROR;
							ssd1351_printf("\nFailure!");
							ssd1351_write_buffer_to_display();
						}
						else if (gt521fx_fingerprint_identify())
						{
							ssd1351_printf("\nSuccess!");
							ssd1351_write_buffer_to_display();
							gt521fx_state = GT521FX_STATE_OPEN_DOOR;
							// open garage door!
						}
						else
						{
							ssd1351_printf("\nFailure!");
							ssd1351_write_buffer_to_display();
							gt521fx_state = GT521FX_STATE_ERROR;
						}
					}
					//while(1);

				break;
				case GT521FX_STATE_VERIFY:
				break;
				case GT521FX_STATE_OPEN_DOOR:
					ssd1351_printf("\nOpen Door!");
					ssd1351_write_buffer_to_display();
					osDelay(3000);
					refresh_screen = true;
					gt521fx_state = GT521FX_STATE_IDENTIFY;
				break;
				case GT521FX_STATE_ERROR:
					ssd1351_printf("\nERROR");
					ssd1351_write_buffer_to_display();
					osDelay(3000);
					refresh_screen = true;
					gt521fx_state = GT521FX_STATE_IDENTIFY;
				break;
				case GT521FX_STATE_NOTHING_TO_DO:
					osDelay(1000);
				break;
				default:
					while(1);
				break;
			}
		}
	}
}



