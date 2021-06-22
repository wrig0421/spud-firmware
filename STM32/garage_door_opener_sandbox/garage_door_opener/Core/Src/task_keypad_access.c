#include "task_keypad_access.h"
#include "ssd1351_driver.h"
#include "keypad.h"
#include "cmsis_os.h"
#include <string.h>

keypad_row_e keypad_row = KEYPAD_ROW_FIRST;
keypad_col_e keypad_col = KEYPAD_COL_FIRST;
keypad_state_e keypad_state = KEYPAD_STATE_SCAN;

uint8_t key_strokes[KEYPAD_PASSWORD_LENGTH] = {0};

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
				//ssd1351_printf("BUTTON PRESSED!\n");
				keypad_state = KEYPAD_STATE_SCAN;
				osDelay(1000);

				key_strokes[password_index++] = key_stroke;
				if (12 == key_stroke)
				{
					memset(key_strokes, 0, KEYPAD_PASSWORD_LENGTH);
					password_index = 0;
					// print display was cleared..
				}
				if (KEYPAD_PASSWORD_LENGTH == password_index)
				{
					if (keypad_password_check(key_strokes))
					{
						memset(key_strokes, 0, KEYPAD_PASSWORD_LENGTH);
						password_index = 0;
						keypad_state = KEYPAD_STATE_PASSWORD_MATCH;
					}
					else
					{
						failed_attempts++;
						memset(key_strokes, 0, KEYPAD_PASSWORD_LENGTH);
						password_index = 0;
						ssd1351_printf("Wrong. Dumbass!\n");
						/*
						if (KEYPAD_MAX_PASSWORD_ATTEMPTS == failed_attempts) // retry 5 max attempts
						{
							keypad_state = KEYPAD_STATE_LOCKOUT;
						}
						*/
					}
				}
				else
				{
					keypad_state = KEYPAD_STATE_SCAN;
				}

			break;
			case KEYPAD_STATE_PASSWORD_MATCH:
				ssd1351_printf("Correct!\n");
				keypad_state = KEYPAD_STATE_SCAN;
				// print success message
				// change state in task_sensor_access
		    break;
			case KEYPAD_STATE_LOCKOUT:
				ssd1351_printf("Wrong. Dumbass!\n");
				keypad_state = KEYPAD_STATE_SCAN;
				// if 5 failures in a row then this should lock for like an hour maybe
		    break;
		}
		osDelay(1);
	}
}

