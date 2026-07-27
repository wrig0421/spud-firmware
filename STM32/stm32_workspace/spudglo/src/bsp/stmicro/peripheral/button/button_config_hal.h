// SRW
#if !defined(BUTTON_CONFIG_HAL_H)
#define BUTTON_CONFIG_HAL_H
#include "button_access.h"

#include "stm32l431xx.h"
#include "stm32l4xx_hal.h"

typedef GPIO_TypeDef*  			port_t;
typedef IRQn_Type				irqn_t;
typedef uint32_t				pull_t;

typedef enum
{
	BUTTON_CONFIG_MODE_IT_RISING = GPIO_MODE_IT_RISING,
	BUTTON_CONFIG_MODE_IT_FALLING = GPIO_MODE_IT_FALLING,
	BUTTON_CONFIG_MODE_IT_RISING_FALLING = GPIO_MODE_IT_RISING_FALLING,
	BUTTON_CONFIG_MODE_EVT_RISING = GPIO_MODE_EVT_RISING,
	BUTTON_CONFIG_MODE_EVT_FALLING = GPIO_MODE_EVT_FALLING,
	BUTTON_CONFIG_MODE_EVT_RISING_FALLING = GPIO_MODE_EVT_RISING_FALLING
} button_config_mode_e;


typedef enum
{
	BUTTON_CONFIG_ACTIVE_LVL_LOW = GPIO_PIN_RESET,
	BUTTON_CONFIG_ACTIVE_LVL_HIGH = GPIO_PIN_SET
} button_config_active_lvl_e;


typedef struct
{
	uint16_t 						pin;
	port_t   						port;
	pull_t							pull;
	button_config_mode_e 			mode;
	button_config_active_lvl_e		lvl;
	irqn_t							irqn;
} button_config_t;


void button_config_hal_setup(void);
void button_config_clear_interrupt(button_e btn);
void button_config_disable_interrupt(button_e btn);
void button_config_enable_interrupt(button_e btn);
void button_config_irq_handler(void);




#endif
