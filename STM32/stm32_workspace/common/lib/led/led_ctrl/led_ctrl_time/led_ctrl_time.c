// SRW

#include "numbers.h"
#include "ws2812b.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "led_ctrl_time.h"


/**
 * @brief   Function to delay an amount of time.
 * @param   mask - enabled strips to check if button press effects.
 * @param   time_ms - time to delay
 * @return  bool - true if interrupt occured else false.
 * @note    If interrupt occured then the function may not delay the full
 *          amount of time.
 */
bool led_ctrl_time_delay(const strip_mask_t mask, const uint32_t time_ms)
{
    uint32_t ms_count = 0;
    uint32_t ticks = 0;

    if (!time_ms) return false;

    ticks = time_ms / portTICK_PERIOD_MS;

    while (ms_count++ < ticks)
    {
        free_rtos_delay_ms(portTICK_PERIOD_MS);
        if (led_ctrl_interrupt_occurred(mask)) return true;
    }
    return false;
}
