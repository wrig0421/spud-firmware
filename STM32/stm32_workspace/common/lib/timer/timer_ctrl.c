// SRW
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "led_animate.h"
#include "timer_ctrl.h"

void timer_ctrl_callback(TimerHandle_t h_timer)
{
    configASSERT(h_timer);

    // trigger animation change.
    led_animate_force_exit_stimulus();

}
