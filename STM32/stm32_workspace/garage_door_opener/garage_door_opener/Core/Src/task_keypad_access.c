#include "task_keypad_access.h"
#include "task_sensor_access.h"
#include "ssd1351_driver.h"
#include "keypad.h"
#include "cmsis_os.h"
#include <string.h>


// local global variables
uint8_t g_user_input[KEYPAD_PASSWORD_LENGTH] = {0};
keypad_state_e g_keypad_state = KEYPAD_STATE_SCAN;


void task_keypad_access_entry(void *argument)
{
	uint8_t key_stroke = 0;
	uint8_t password_index = 0;
	//uint8_t failed_attempts = 0;
	while(1)
	{
		switch(g_keypad_state)
		{
			case KEYPAD_STATE_SCAN:
				if (keypad_scan()) g_keypad_state = KEYPAD_STATE_BTN_PRESS;
			break;
			case KEYPAD_STATE_BTN_PRESS:
				key_stroke = keypad_button_pressed();
				task_sensor_access_set_btn_pause();
				g_keypad_state = KEYPAD_STATE_SCAN;
				if (GT521FX_STATE_IDENTIFY == gt521fx_current_state())
				{
					g_user_input[password_index++] = key_stroke;
					if (12 == key_stroke)
					{
						memset(g_user_input, 0, KEYPAD_PASSWORD_LENGTH);
						password_index = 0;
					}
					if (KEYPAD_PASSWORD_LENGTH == password_index)
					{
						if (keypad_password_check(g_user_input))
						{
							memset(g_user_input, 0, KEYPAD_PASSWORD_LENGTH);
							password_index = 0;
							g_keypad_state = KEYPAD_STATE_PASSWORD_MATCH;
						}
						else
						{
							memset(g_user_input, 0, KEYPAD_PASSWORD_LENGTH);
							password_index = 0;
						}
					}
					else
					{
						g_keypad_state = KEYPAD_STATE_SCAN;
					}
				}
				else if(GT521FX_STATE_ADMIN == gt521fx_current_state())
				{
					gt521fx_set_state(key_stroke);
					g_keypad_state = KEYPAD_STATE_SCAN;
				}
			break;
			case KEYPAD_STATE_PASSWORD_MATCH:
				gt521fx_set_state(0);
				ssd1351_clear_screen();
				ssd1351_printf("Correct password!\n");
				ssd1351_write_buffer_to_display();
				osDelay(1000);
				g_keypad_state = KEYPAD_STATE_SCAN;
		    break;
			case KEYPAD_STATE_LOCKOUT:
				g_keypad_state = KEYPAD_STATE_SCAN;
				// @todo if 5 failures in a row then this should lock for like an hour maybe
		    break;
		}
		osDelay(1);
	}
}

