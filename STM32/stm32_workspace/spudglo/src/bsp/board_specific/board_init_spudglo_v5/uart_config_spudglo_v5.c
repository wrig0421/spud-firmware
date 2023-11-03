// SRW

#include "stm32l4xx_hal.h"
#include "config.h"
#include "board_init.h"
#include "board_specific.h"
#include "gpio_config_hal.h"
#include "gpio_config_spudglo_v5.h"
#include <stdbool.h>


#if defined(BOARD_SPUD_GLO_V5)


gpio_config_t uart_config[GPIO_CONFIG_NUM_PINS] =
{
    [GPIO_CONFIG_PIOA_PIN0] =
    {
        .pin = PIN_XR_TX,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLUP,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_ENABLE,
        .interrupt_type = PIN_WKUP_1_IRQ,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOA_PIN1] =
    {
        .pin = PIN_ESP8266_SCK,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOA_PIN2] =
    {
        .pin = PIN_WKUP4,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLUP,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_ENABLE,
        .interrupt_type = PIN_WKUP_4_IRQ,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOA_PIN3] =
    {
        .pin = PIOA_PIN_3,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN,
    },
    [GPIO_CONFIG_PIOA_PIN4] =
    {
        .pin = PIN_ESP8266_CSN,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_HIGH
    },
    [GPIO_CONFIG_PIOA_PIN5] =
    {
        .pin = PIN_ESP8266_GPIO0,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOA_PIN6] =
    {
        .pin = PIN_ESP8266_EN,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_HIGH
    },
    [GPIO_CONFIG_PIOA_PIN7] =
    {
        .pin = PIN_ESP8266_RST,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_HIGH
    },
    [GPIO_CONFIG_PIOA_PIN8] =
    {
        .pin = PIN_TIM1_CH1,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOA_PIN9] =
    {
        .pin = PIN_TIM1_CH2,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOA_PIN10] =
    {
        .pin = PIN_TIM1_CH3,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOA_PIN11] =
    {
        .pin = PIN_ESP8266_CIPO,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOA_PIN12] =
    {
        .pin = PIN_ESP8266_COPI,
        .port = PIN_PORT_A,
        .pin_mode = GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOA_PIN13] =
    {
        .pin = PIN_PROG_SWDIO,
        .pin_mode = GPIO_CONFIG_PIN_MODE_NO_SETUP
    },
    [GPIO_CONFIG_PIOA_PIN14] =
    {
        .pin = PIN_PROG_SWCLK,
        .pin_mode = GPIO_CONFIG_PIN_MODE_NO_SETUP
    },
    [GPIO_CONFIG_PIOA_PIN15] =
    {
        .pin = PIN_PROG_JTDI,
        .pin_mode = GPIO_CONFIG_PIN_MODE_NO_SETUP
    },
    [GPIO_CONFIG_PIOB_PIN0] =
    {
        .pin = PIOB_PIN_0,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOB_PIN1] =
    {
        .pin = PIOB_PIN_1,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOB_PIN2] =
    {
        .pin = PIOB_PIN_2,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOB_PIN3] =
    {
        .pin = PIN_PROG_SWCLK,
        .pin_mode = GPIO_CONFIG_PIN_MODE_NO_SETUP
    },
    [GPIO_CONFIG_PIOB_PIN4] =
    {
        .pin = PIN_PROG_JTDI,
        .pin_mode = GPIO_CONFIG_PIN_MODE_NO_SETUP
    },
    [GPIO_CONFIG_PIOB_PIN5] =
    {
        .pin = PIOB_PIN_5,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOB_PIN6] =
    {
        .pin = PIN_ESP8266_RXD,
        .port = PIN_PORT_B,
        .pin_mode = GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOB_PIN7] =
    {
        .pin = PIN_ESP8266_TXD,
        .port = PIN_PORT_B,
        .pin_mode = GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOB_PIN8] =
    {
        .pin = PIOB_PIN_8,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOB_PIN9] =
    {
        .pin = PIOB_PIN_9,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOB_PIN10] =
    {
        .pin = PIOB_PIN_10,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOB_PIN11] =
    {
        .pin = PIOB_PIN_11,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOB_PIN12] =
    {
        .pin = PIN_XR_GPIO,
        .port = PIN_PORT_B,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_FLOAT,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOB_PIN13] =
    {
        .pin = PIN_VBUS_PRESENT,
        .port = PIN_PORT_B,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_FLOAT,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOB_PIN14] =
    {
        .pin = PIOB_PIN_14,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOB_PIN15] =
    {
        .pin = PIOB_PIN_15,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOC_PIN0] =
    {
        .pin = PIN_XR_TX,
        .port = PIN_PORT_C,
        .pin_mode = GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOC_PIN1] =
    {
        .pin = PIN_XR_RX,
        .port = PIN_PORT_C,
        .pin_mode = GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOC_PIN2] =
    {
        .pin = PIN_GREEN_LED,
        .port = PIN_PORT_C,
        .pin_mode = GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_LOW
    },
    [GPIO_CONFIG_PIOC_PIN3] =
    {
        .pin = PIN_RED_LED,
        .port = PIN_PORT_C,
        .pin_mode = GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_LOW
    },
    [GPIO_CONFIG_PIOC_PIN4] =
    {
        .pin = PIOC_PIN_4,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOC_PIN5] =
    {
        .pin = PIN_WKUP3,
        .port = PIN_PORT_C,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLUP,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_ENABLE,
        .interrupt_type = PIN_WKUP_3_IRQ,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOC_PIN6] =
    {
        .pin = PIOC_PIN_6,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOC_PIN7] =
    {
        .pin = PIN_LVL_EN,
        .port = PIN_PORT_C,
        .pin_mode = GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_HIGH
    },
    [GPIO_CONFIG_PIOC_PIN8] =
    {
        .pin = PIN_LVL_DIR,
        .port = PIN_PORT_C,
        .pin_mode = GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_NO_SETUP,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_HIGH
    },
    [GPIO_CONFIG_PIOC_PIN9] =
    {
        .pin = PIOC_PIN_9,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOC_PIN10] =
    {
        .pin = PIOC_PIN_10,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOC_PIN11] =
    {
        .pin = PIOC_PIN_11,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOC_PIN12] =
    {
        .pin = PIOC_PIN_12,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOC_PIN13] =
    {
        .pin = PIN_WKUP2,
        .port = PIN_PORT_C,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLUP,
        .interrupt = GPIO_CONFIG_PIN_INTERRUPT_ENABLE,
        .interrupt_type = PIN_WKUP_2_IRQ,
        .output_lvl = GPIO_CONFIG_OUTPUT_LVL_NONE
    },
    [GPIO_CONFIG_PIOC_PIN14] =
    {
        .pin = PIOC_PIN_14,
        .pin_mode = GPIO_CONFIG_PIN_MODE_NO_SETUP
    },
    [GPIO_CONFIG_PIOC_PIN15] =
    {
        .pin = PIOC_PIN_15,
        .pin_mode = GPIO_CONFIG_PIN_MODE_NO_SETUP
    },
    [GPIO_CONFIG_PIOD_PIN2] =
    {
        .pin = PIOD_PIN_2,
        .pin_mode = GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN
    },
    [GPIO_CONFIG_PIOH_PIN0] =
    {
        .pin = PIOH_PIN_0,
        .pin_mode = GPIO_CONFIG_PIN_MODE_NO_SETUP
    },
    [GPIO_CONFIG_PIOH_PIN1] =
    {
        .pin = PIOH_PIN_1,
        .pin_mode = GPIO_CONFIG_PIN_MODE_NO_SETUP
    },
    [GPIO_CONFIG_PIOH_PIN3] =
    {
        .pin = PIOH_PIN_3,
        .pin_mode = GPIO_CONFIG_PIN_MODE_NO_SETUP
    }
};


#endif

