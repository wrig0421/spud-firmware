// SRW

#include "led_ctrl.h"


bool led_ctrl_strip_1_interrupt_occurred(void)
{
	return g_task_led_ctrl[STRIP_NUM_1].led_interrupt_info.interrupt_set;
}


bool led_ctrl_strip_2_interrupt_occurred(void)
{
	return g_task_led_ctrl[STRIP_NUM_2].led_interrupt_info.interrupt_set;
}


bool led_ctrl_strip_3_interrupt_occurred(void)
{
	return g_task_led_ctrl[STRIP_NUM_3].led_interrupt_info.interrupt_set;
}


bool led_ctrl_strip_sync_interrupt_occurred(void)
{
	return g_task_led_ctrl[CONFIG_LED_STRIP_SYNC_INDEX].led_interrupt_info.interrupt_set;
}


bool led_ctrl_delay(const uint32_t time_ms)
{
    uint32_t ms_count = 0;

    while (ms_count++ < time_ms)
    {
        osDelay(portTICK_PERIOD_MS);
        if (task_button_press_interrupt_occurred()) return true;
    }
    return false;
}


float led_ctrl_delay_time(strip_num_e led_strip_index)
{
    return ((float)g_delay_in_animation_ms / task_speed_ctrl());
}







