// SRW

#if !defined(TIMER_CONFIG_HAL_H)
#define TIMER_CONFIG_HAL_H

#include <animation_timer_access.h>
#include "stm32l431xx.h"
#include "stm32l4xx_hal.h"
#include <stdint.h>


typedef TIM_HandleTypeDef* 		timer_handle_t;
typedef TIM_TypeDef* 			timer_instance_t;
typedef GPIO_TypeDef*  			port_t;
typedef uint8_t					alt_func_t;
typedef IRQn_Type				irqn_t;


typedef struct
{
	uint16_t 	timer_pin;
	port_t   	timer_port;
	alt_func_t  timer_alt_func;
} timer_config_pin_t;


typedef struct
{
	timer_config_pin_t 		pin;
	irqn_t					irqn;
	timer_handle_t			handle;
} timer_config_t;


typedef timer_config_t* p_timer_config_t;


void timer_config_hal_setup(void);


#endif
