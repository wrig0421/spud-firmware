

#include "task_periodic.h"
#include "ssd1351_driver.h"
#include "stdbool.h"
#include "cmsis_os.h"

typedef enum
{
	SYS_STATE_INTRO,
	SYS_STATE_ENROLL,
	SYS_STATE_VERIFY,
} sys_state_e;


typedef enum
{
	SYS_SUB_STATE_ENROLL_PLACE_FINGER,
	SYS_SUB_STATE_ENROLL_REMOVE_FINGER,
	SYS_SUB_STATE_ENROLL_ERROR,
	SYS_SUB_STATE_ENROLL_SUCCESS,
	SYS_SUB_STATE_VERIFY_PLACE_FINGER,
	SYS_SUB_STATE_VERIFY_REMOVE_FINGER,
	SYS_SUB_STATE_VERIFY_ERROR,
	SYS_SUB_STATE_VERIFY_SUCCESS,
} sys_sub_state_e;


sys_state_e sys_state = SYS_STATE_INTRO;
sys_state_e sys_sub_state; // uninitialized set in task_periodic functoin


bool g_update_display_flag = true; // handle first pass
void reset_update_display_flag(void);
void reset_update_display_flag(void)
{
	g_update_display_flag = false;
}


void set_update_display_flag(void);
void set_update_display_flag(void)
{
	g_update_display_flag = true;
}


bool update_display(void);
bool update_display(void)
{
	if (g_update_display_flag)
	{
		reset_update_display_flag();
		return true;
	}
	else return false;
}

sys_state_e prev_sys_state = SYS_STATE_INTRO;
bool g_sys_first_pass = true;
bool g_state_transition = false;

/**
* @brief Function implementing the task_periodic_ thread.
* @param argument: Not used
* @retval None
*/
void task_periodic(void *argument)
{
  /* USER CODE BEGIN task_periodic */
  /* Infinite loop */
	do
	{
		if (prev_sys_state != sys_state)
		{
			set_update_display_flag();
			prev_sys_state = sys_state; // appropriate to set her
			g_sys_first_pass = true;
		}
		/*
		else
		{
			g_sys_first_pass = false;
		}
		*/
		if (update_display())
		{
			ssd1351_write_buffer_to_display();
		}
		switch(sys_state)
		{
			case SYS_STATE_INTRO:
				if (g_sys_first_pass)
				{
					ssd1351_write_string(COLOR_16BIT_BLUE, Font_7x10, "   Place Finger   ");
					ssd1351_write_string(COLOR_16BIT_BLUE, Font_7x10, "\n    on Sensor    ");
					set_update_display_flag();
				}
			break;
			case SYS_STATE_ENROLL:
			break;
			case SYS_STATE_VERIFY:
			break;
		}
		osDelay(1000);
	} while(1);
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END task_periodic */
}
