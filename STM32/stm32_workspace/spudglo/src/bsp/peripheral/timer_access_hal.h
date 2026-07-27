// SRW

#if !defined(TIMER_ACCESS_HAL_H)
#define TIMER_ACCESS_HAL_H

#include "stm32l4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include "timer_config_hal.h"

HAL_StatusTypeDef timer_access_hal_start_timer(TIM_HandleTypeDef* p_timer_handle, uint32_t timer_channel,
												const uint32_t* p_data, uint16_t length_data);
void timer_access_hal_stop_timer(void);


#endif
