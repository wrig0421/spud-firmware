// SRW

#include "FreeRTOS.h"
#include "portmacro.h"

#include "led_ctrl.h"
#include "task_button_press.h"
#include "free_rtos_convenience.h"


bool led_ctrl_delay(const uint32_t time_ms)
{
    uint32_t ms_count = 0;
    uint32_t ticks = 0;
    if (!time_ms) return false;

    ticks = time_ms / portTICK_PERIOD_MS;

    while (ms_count++ < time_ms)
    {
    	free_rtos_delay_ms(ticks);
        if (task_button_press_interrupt_occurred()) return true;
    }
    return false;
}


//float led_ctrl_delay_time(strip_num_e strip_num)
//{
//    return ((float)g_delay_in_animation_ms / led_ctrl_speed(mask));
//}







