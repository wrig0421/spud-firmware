// SRW

#if !defined(GPIO_CONFIG_H)
#define GPIO_CONFIG_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32l4xx_hal.h"

#include "stm32l4xx_hal.h"
#define PIN_PORT_A              GPIOA
#define PIN_PORT_B              GPIOB
#define PIN_PORT_C              GPIOC
#define PIN_PORT_D              GPIOD
#define PIN_PORT_E              GPIOE
#define PIN_PORT_F              GPIOF
#define PIN_PORT_G              GPIOG
#define PIN_PORT_H              GPIOH

#define PIOA_PIN_0              GPIO_PIN_0
#define PIOA_PIN_1              GPIO_PIN_1
#define PIOA_PIN_2              GPIO_PIN_2
#define PIOA_PIN_3              GPIO_PIN_3
#define PIOA_PIN_4              GPIO_PIN_4
#define PIOA_PIN_5              GPIO_PIN_5
#define PIOA_PIN_6              GPIO_PIN_6
#define PIOA_PIN_7              GPIO_PIN_7
#define PIOA_PIN_8              GPIO_PIN_8
#define PIOA_PIN_9              GPIO_PIN_9
#define PIOA_PIN_10             GPIO_PIN_10
#define PIOA_PIN_11             GPIO_PIN_11
#define PIOA_PIN_12             GPIO_PIN_12
#define PIOA_PIN_13             GPIO_PIN_13
#define PIOA_PIN_14             GPIO_PIN_14
#define PIOA_PIN_15             GPIO_PIN_15

#define PIOB_PIN_0              GPIO_PIN_0
#define PIOB_PIN_1              GPIO_PIN_1
#define PIOB_PIN_2              GPIO_PIN_2
#define PIOB_PIN_3              GPIO_PIN_3
#define PIOB_PIN_4              GPIO_PIN_4
#define PIOB_PIN_5              GPIO_PIN_5
#define PIOB_PIN_6              GPIO_PIN_6
#define PIOB_PIN_7              GPIO_PIN_7
#define PIOB_PIN_8              GPIO_PIN_8
#define PIOB_PIN_9              GPIO_PIN_9
#define PIOB_PIN_10             GPIO_PIN_10
#define PIOB_PIN_11             GPIO_PIN_11
#define PIOB_PIN_12             GPIO_PIN_12
#define PIOB_PIN_13             GPIO_PIN_13
#define PIOB_PIN_14             GPIO_PIN_14
#define PIOB_PIN_15             GPIO_PIN_15

#define PIOC_PIN_0              GPIO_PIN_0
#define PIOC_PIN_1              GPIO_PIN_1
#define PIOC_PIN_2              GPIO_PIN_2
#define PIOC_PIN_3              GPIO_PIN_3
#define PIOC_PIN_4              GPIO_PIN_4
#define PIOC_PIN_5              GPIO_PIN_5
#define PIOC_PIN_6              GPIO_PIN_6
#define PIOC_PIN_7              GPIO_PIN_7
#define PIOC_PIN_8              GPIO_PIN_8
#define PIOC_PIN_9              GPIO_PIN_9
#define PIOC_PIN_10             GPIO_PIN_10
#define PIOC_PIN_11             GPIO_PIN_11
#define PIOC_PIN_12             GPIO_PIN_12
#define PIOC_PIN_13             GPIO_PIN_13
#define PIOC_PIN_14             GPIO_PIN_14
#define PIOC_PIN_15             GPIO_PIN_15

#define PIOD_PIN_2              GPIO_PIN_2

#define PIOH_PIN_0              GPIO_PIN_0
#define PIOH_PIN_1              GPIO_PIN_1
#define PIOH_PIN_3              GPIO_PIN_3


typedef enum
{
    GPIO_CONFIG_PIN_FIRST,
    GPIO_CONFIG_PIOA_PIN0 = GPIO_CONFIG_PIN_FIRST,
    GPIO_CONFIG_PIOA_PIN1,
    GPIO_CONFIG_PIOA_PIN2,
    GPIO_CONFIG_PIOA_PIN3,
    GPIO_CONFIG_PIOA_PIN4,
    GPIO_CONFIG_PIOA_PIN5,
    GPIO_CONFIG_PIOA_PIN6,
    GPIO_CONFIG_PIOA_PIN7,
    GPIO_CONFIG_PIOA_PIN8,
    GPIO_CONFIG_PIOA_PIN9,
    GPIO_CONFIG_PIOA_PIN10,
    GPIO_CONFIG_PIOA_PIN11,
    GPIO_CONFIG_PIOA_PIN12,
    GPIO_CONFIG_PIOA_PIN13,
    GPIO_CONFIG_PIOA_PIN14,
    GPIO_CONFIG_PIOA_PIN15,
    GPIO_CONFIG_PIOB_PIN0,
    GPIO_CONFIG_PIOB_PIN1,
    GPIO_CONFIG_PIOB_PIN2,
    GPIO_CONFIG_PIOB_PIN3,
    GPIO_CONFIG_PIOB_PIN4,
    GPIO_CONFIG_PIOB_PIN5,
    GPIO_CONFIG_PIOB_PIN6,
    GPIO_CONFIG_PIOB_PIN7,
    GPIO_CONFIG_PIOB_PIN8,
    GPIO_CONFIG_PIOB_PIN9,
    GPIO_CONFIG_PIOB_PIN10,
    GPIO_CONFIG_PIOB_PIN11,
    GPIO_CONFIG_PIOB_PIN12,
    GPIO_CONFIG_PIOB_PIN13,
    GPIO_CONFIG_PIOB_PIN14,
    GPIO_CONFIG_PIOB_PIN15,
    GPIO_CONFIG_PIOC_PIN0,
    GPIO_CONFIG_PIOC_PIN1,
    GPIO_CONFIG_PIOC_PIN2,
    GPIO_CONFIG_PIOC_PIN3,
    GPIO_CONFIG_PIOC_PIN4,
    GPIO_CONFIG_PIOC_PIN5,
    GPIO_CONFIG_PIOC_PIN6,
    GPIO_CONFIG_PIOC_PIN7,
    GPIO_CONFIG_PIOC_PIN8,
    GPIO_CONFIG_PIOC_PIN9,
    GPIO_CONFIG_PIOC_PIN10,
    GPIO_CONFIG_PIOC_PIN11,
    GPIO_CONFIG_PIOC_PIN12,
    GPIO_CONFIG_PIOC_PIN13,
    GPIO_CONFIG_PIOC_PIN14,
    GPIO_CONFIG_PIOC_PIN15,
    GPIO_CONFIG_PIOD_PIN2,
    GPIO_CONFIG_PIOH_PIN0,
    GPIO_CONFIG_PIOH_PIN1,
    GPIO_CONFIG_PIOH_PIN3,
    GPIO_CONFIG_NUM_PINS
} gpio_config_pin_e;


typedef enum
{
    GPIO_CONFIG_PIN_MODE_NO_SETUP,
    GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL,
    GPIO_CONFIG_PIN_MODE_OUTPUT_OPEN_DRAIN,
    GPIO_CONFIG_PIN_MODE_INPUT_FLOAT,
    GPIO_CONFIG_PIN_MODE_INPUT_PULLUP,
    GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN,
    GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
    GPIO_CONFIG_NUM_PIN_MODES
} gpio_config_pin_mode_e;


typedef enum
{
    GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
    GPIO_CONFIG_PIN_INTERRUPT_ENABLE,
    GPIO_CONFIG_PIN_INTERRUPT_DISABLE
} gpio_config_pin_interrupt_e;


typedef enum
{
    GPIO_CONFIG_OUTPUT_LVL_NONE,
    GPIO_CONFIG_OUTPUT_LVL_LOW,
    GPIO_CONFIG_OUTPUT_LVL_HIGH
} gpio_config_output_lvl_e;


typedef struct
{
    uint16_t                        pin;
    GPIO_TypeDef *                  port;
    gpio_config_pin_mode_e          pin_mode;
    gpio_config_pin_interrupt_e     interrupt;
    IRQn_Type                       interrupt_type;
    gpio_config_output_lvl_e        output_lvl;
} gpio_config_t;


void gpio_config_init(void);


#endif
