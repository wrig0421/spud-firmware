#include "task_keypad_access.h"
#include "task_sensor_access.h"
#include "ssd1351_driver.h"
#include "keypad.h"
#include "cmsis_os.h"
#include <string.h>

keypad_row_e keypad_row = KEYPAD_ROW_FIRST;
keypad_col_e keypad_col = KEYPAD_COL_FIRST;
keypad_state_e keypad_state = KEYPAD_STATE_SCAN;

uint8_t password[KEYPAD_PASSWORD_LENGTH] = {0};

void task_keypad_access_entry(void *argument)
{
	uint8_t key_stroke = 0;
	uint8_t password_index = 0;
	uint8_t failed_attempts = 0;
	while(1)
	{
		switch(keypad_state)
		{
			case KEYPAD_STATE_SCAN:
				if (keypad_scan()) keypad_state = KEYPAD_STATE_BTN_PRESS;
			break;
			case KEYPAD_STATE_BTN_PRESS:
				key_stroke = keypad_button_pressed();
				task_sensor_access_set_btn_pause();
				keypad_state = KEYPAD_STATE_SCAN;
				//osDelay(1000);
				if (GT521FX_STATE_IDENTIFY == gt521fx_current_state())
				{
					// Attempting to enter admin menu

					password[password_index++] = key_stroke;
					if (12 == key_stroke)
					{
						memset(password, 0, KEYPAD_PASSWORD_LENGTH);
						password_index = 0;
						// print display was cleared..
					}
					if (KEYPAD_PASSWORD_LENGTH == password_index)
					{
						if (keypad_password_check(password))
						{
							memset(password, 0, KEYPAD_PASSWORD_LENGTH);
							password_index = 0;
							keypad_state = KEYPAD_STATE_PASSWORD_MATCH;
						}
						else
						{
							memset(password, 0, KEYPAD_PASSWORD_LENGTH);
							password_index = 0;
						}
#if 0
						else
						{
							failed_attempts++;
							memset(password, 0, KEYPAD_PASSWORD_LENGTH);
							password_index = 0;
							ssd1351_clear_screen(); // always clear here
							ssd1351_printf("Wrong password. Dumbass!\n");
							ssd1351_write_buffer_to_display();
							osDelay(1000);
							set_screen_refresh();
							keypad_state = KEYPAD_STATE_SCAN;
							/*
							if (KEYPAD_MAX_PASSWORD_ATTEMPTS == failed_attempts) // retry 5 max attempts
							{
								keypad_state = KEYPAD_STATE_LOCKOUT;
							}
							*/
						}
#endif
					}
					else
					{
						keypad_state = KEYPAD_STATE_SCAN;
					}
				}
				else if(GT521FX_STATE_ADMIN == gt521fx_current_state())
				{
					gt521fx_set_state(key_stroke);
					keypad_state = KEYPAD_STATE_SCAN;
				}
			break;
			case KEYPAD_STATE_PASSWORD_MATCH:
				gt521fx_set_state(0);
				ssd1351_clear_screen(); // always clear here
				ssd1351_printf("Correct password!\n");
				ssd1351_write_buffer_to_display();
				osDelay(1000);
				keypad_state = KEYPAD_STATE_SCAN;
				// print success message
				// change state in task_sensor_access
		    break;
			case KEYPAD_STATE_LOCKOUT:
				ssd1351_clear_screen(); // always clear here
				ssd1351_printf("Wrong password. Dumbass!\n");
				ssd1351_write_buffer_to_display();
				osDelay(1000);
				set_screen_refresh();
				keypad_state = KEYPAD_STATE_SCAN;
				// if 5 failures in a row then this should lock for like an hour maybe
		    break;
		}
		osDelay(1);
	}
}

