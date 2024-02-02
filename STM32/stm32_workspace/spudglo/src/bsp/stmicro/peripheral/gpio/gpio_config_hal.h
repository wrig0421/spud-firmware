// SRW

#if !defined(GPIO_CONFIG_HAL_H)
#define GPIO_CONFIG_HAL_H

#include "stm32l431xx.h"
#include "stm32l4xx_hal.h"
#include <stdint.h>

typedef GPIO_TypeDef*  			port_t;
typedef uint8_t					alt_func_t;


#define GPIO_PORT_A              GPIOA
#define GPIO_PORT_B              GPIOB
#define GPIO_PORT_C              GPIOC
#define GPIO_PORT_D              GPIOD
#define GPIO_PORT_E              GPIOE
#define GPIO_PORT_F              GPIOF
#define GPIO_PORT_G              GPIOG
#define GPIO_PORT_H              GPIOH



typedef enum
{
	GPIO_PIN_FIRST,
	GPIO_PIOA_PIN_0 = GPIO_PIN_FIRST,
	GPIO_PIOA_PIN_1,
	GPIO_PIOA_PIN_2,
	GPIO_PIOA_PIN_3,
	GPIO_PIOA_PIN_4,
	GPIO_PIOA_PIN_5,
	GPIO_PIOA_PIN_6,
	GPIO_PIOA_PIN_7,
	GPIO_PIOA_PIN_8,
	GPIO_PIOA_PIN_9,
	GPIO_PIOA_PIN_10,
	GPIO_PIOA_PIN_11,
	GPIO_PIOA_PIN_12,
	GPIO_PIOA_PIN_13,
	GPIO_PIOA_PIN_14,
	GPIO_PIOA_PIN_15,

	GPIO_PIOB_PIN_0,
	GPIO_PIOB_PIN_1,
	GPIO_PIOB_PIN_2,
	GPIO_PIOB_PIN_3,
	GPIO_PIOB_PIN_4,
	GPIO_PIOB_PIN_5,
	GPIO_PIOB_PIN_6,
	GPIO_PIOB_PIN_7,
	GPIO_PIOB_PIN_8,
	GPIO_PIOB_PIN_9,
	GPIO_PIOB_PIN_10,
	GPIO_PIOB_PIN_11,
	GPIO_PIOB_PIN_12,
	GPIO_PIOB_PIN_13,
	GPIO_PIOB_PIN_14,
	GPIO_PIOB_PIN_15,

	GPIO_PIOC_PIN_0,
	GPIO_PIOC_PIN_1,
	GPIO_PIOC_PIN_2,
	GPIO_PIOC_PIN_3,
	GPIO_PIOC_PIN_4,
	GPIO_PIOC_PIN_5,
	GPIO_PIOC_PIN_6,
	GPIO_PIOC_PIN_7,
	GPIO_PIOC_PIN_8,
	GPIO_PIOC_PIN_9,
	GPIO_PIOC_PIN_10,
	GPIO_PIOC_PIN_11,
	GPIO_PIOC_PIN_12,
	GPIO_PIOC_PIN_13,
	GPIO_PIOC_PIN_14,
	GPIO_PIOC_PIN_15,

	GPIO_PIOD_PIN_2,

	GPIO_PIOH_PIN_0,
	GPIO_PIOH_PIN_1,
	// PH2 not an option
	GPIO_PIOH_PIN_3,
	NUM_GPIO_PINS

} gpio_pin_e;


typedef enum
{
	GPIO_CONFIG_MODE_NO_SETTING,
	GPIO_CONFIG_MODE_INPUT_FLOAT,
	GPIO_CONFIG_MODE_INPUT_PULLDOWN,
	GPIO_CONFIG_MODE_INPUT_PULLUP,
	GPIO_CONFIG_MODE_OUTPUT_PUSHPULL,
	GPIO_CONFIG_MODE_OUTPUT_OPEN_DRAIN,
	GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
} gpio_config_mode_e;


typedef enum
{
	GPIO_CONFIG_OUTPUT_LVL_RESET = 0,
	GPIO_CONFIG_OUTPUT_LVL_SET,
	GPIO_CONFIG_OUTPUT_LVL_NO_SETTING
} gpio_config_output_lvl_e;


typedef enum
{
	GPIO_CONFIG_INTERRUPT_MODE_DISABLE = 0,
	GPIO_CONFIG_INTERRUPT_MODE_ENABLE
} gpio_config_interrupt_mode_e;


typedef enum
{
	GPIO_CONFIG_INTERRUPT_EDGE_FALLING = 0,
	GPIO_CONFIG_INTERRUPT_EDGE_RISING,
	GPIO_CONFIG_INTERRUPT_EDGE_RISING_FALLING,
} gpio_config_interrupt_edge_e;


typedef struct
{
	uint16_t 						pin;
	port_t							port;
	gpio_config_mode_e				mode;
	gpio_config_output_lvl_e		lvl;
	gpio_config_interrupt_mode_e	interrupt_mode;
	gpio_config_interrupt_edge_e	interrupt_edge;
	IRQn_Type						irqn;
} gpio_config_t;

IRQn_Type gpio_config_irqn_lookup(gpio_pin_e pin);
port_t gpio_config_port_lookup(gpio_pin_e pin);
uint16_t gpio_config_pin_lookup(gpio_pin_e pin);
void gpio_config_hal_setup(void);

#endif // GPIO_CONFIG_HAL_H
