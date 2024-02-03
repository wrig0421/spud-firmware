// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_V5P0)
#include "stm32l4xx_hal.h"
#include "gpio_config_hal_specific.h"
#include "gpio_config_hal.h"

const gpio_config_t g_gpio_config[NUM_GPIO_PINS] =
{
	// PORT C pins!!!
	[GPIO_PIOC_PIN_0] =
	{
		.pin = GPIO_PIN_XR_TX,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOC_PIN_1] =
	{
		.pin = GPIO_PIN_XR_RX,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOC_PIN_2] =
	{
		.pin = GPIO_PIN_GREEN_LED,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_OUTPUT_PUSHPULL,
		.lvl = GPIO_CONFIG_OUTPUT_LVL_RESET
	},
	[GPIO_PIOC_PIN_3] =
	{
		.pin = GPIO_PIN_RED_LED,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_OUTPUT_PUSHPULL,
		.lvl = GPIO_CONFIG_OUTPUT_LVL_SET
	},
	[GPIO_PIOC_PIN_4] = // NC
	{
		.pin = GPIO_PIOC_PIN_4,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOC_PIN_5] =
	{
		.pin = GPIO_PIN_WKUP3,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLUP,
		.interrupt_mode = GPIO_CONFIG_INTERRUPT_MODE_ENABLE,
		.interrupt_edge = GPIO_CONFIG_INTERRUPT_EDGE_FALLING,
		.irqn = EXTI9_5_IRQn
	},
	[GPIO_PIOC_PIN_6] = // NC
	{
		.pin = GPIO_PIOC_PIN_6,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOC_PIN_7] =
	{
		.pin = GPIO_PIN_LVL_EN,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_OUTPUT_PUSHPULL,
		.lvl = GPIO_CONFIG_OUTPUT_LVL_RESET
	},
	[GPIO_PIOC_PIN_8] =
	{
		.pin = GPIO_PIN_LVL_DIR,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_OUTPUT_PUSHPULL,
		.lvl = GPIO_CONFIG_OUTPUT_LVL_SET
	},
	[GPIO_PIOC_PIN_9] = // NC
	{
		.pin = GPIO_PIOC_PIN_9,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOC_PIN_10] = // NC
	{
		.pin = GPIO_PIOC_PIN_10,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOC_PIN_11] = // NC
	{
		.pin = GPIO_PIOC_PIN_11,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOC_PIN_12] = // NC
	{
		.pin = GPIO_PIOC_PIN_12,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOC_PIN_13] =
	{
		.pin = GPIO_PIN_WKUP2,
		.port = GPIO_PORT_C,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLUP,
		.interrupt_mode = GPIO_CONFIG_INTERRUPT_MODE_ENABLE,
		.interrupt_edge = GPIO_CONFIG_INTERRUPT_EDGE_FALLING,
		.irqn = EXTI15_10_IRQn
	},
	[GPIO_PIOC_PIN_14] = // PROGRAMMING SIGNAL!!!!
	{
		.pin = GPIO_PIOC_PIN_14,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},
	[GPIO_PIOC_PIN_15] = // PROGRAMMING SIGNAL!!!!
	{
		.pin = GPIO_PIOC_PIN_6,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},

	// PORT A pins!!!
	[GPIO_PIOA_PIN_0] =
	{
		.pin = GPIO_PIN_WKUP1,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLUP,
		.interrupt_mode = GPIO_CONFIG_INTERRUPT_MODE_ENABLE,
		.interrupt_edge = GPIO_CONFIG_INTERRUPT_EDGE_FALLING,
		.irqn = EXTI0_IRQn
	},
	[GPIO_PIOA_PIN_1] =
	{
		.pin = GPIO_PIN_ESP8266_SCK,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOA_PIN_2] =
	{
		.pin = GPIO_PIN_WKUP4,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLUP,
		.interrupt_mode = GPIO_CONFIG_INTERRUPT_MODE_ENABLE,
		.interrupt_edge = GPIO_CONFIG_INTERRUPT_EDGE_FALLING,
		.irqn = EXTI2_IRQn
	},
	[GPIO_PIOA_PIN_3] = // NC
	{
		.pin = GPIO_PIOC_PIN_12,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOA_PIN_4] =
	{
		.pin = GPIO_PIN_ESP8266_CSN,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_OUTPUT_PUSHPULL,
		.lvl = GPIO_CONFIG_OUTPUT_LVL_SET // deselect initially!
	},
	[GPIO_PIOA_PIN_5] =
	{
		.pin = GPIO_PIN_ESP8266_GPIO0,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOA_PIN_6] =
	{
		.pin = GPIO_PIN_ESP8266_EN,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_OUTPUT_PUSHPULL,
		.lvl = GPIO_CONFIG_OUTPUT_LVL_RESET // off initially!
	},
	[GPIO_PIOA_PIN_7] =
	{
		.pin = GPIO_PIN_ESP8266_RST,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_OUTPUT_PUSHPULL,
		.lvl = GPIO_CONFIG_OUTPUT_LVL_RESET // in reset initially
	},
	[GPIO_PIOA_PIN_8] =
	{
		.pin = GPIO_PIN_TIM1_CH1,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOA_PIN_9] =
	{
		.pin = GPIO_PIN_TIM1_CH2,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOA_PIN_10] =
	{
		.pin = GPIO_PIN_TIM1_CH3,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOA_PIN_11] =
	{
		.pin = GPIO_PIN_ESP8266_MISO,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOA_PIN_12] =
	{
		.pin = GPIO_PIN_ESP8266_MOSI,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOA_PIN_13] = // PROGRAMMING SIGNAL!
	{
		.pin = GPIO_PIOA_PIN_13,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},
	[GPIO_PIOA_PIN_14] = // PROGRAMMING SIGNAL!
	{
		.pin = GPIO_PIOA_PIN_14,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},
	[GPIO_PIOA_PIN_15] = // PROGRAMMING SIGNAL!
	{
		.pin = GPIO_PIOA_PIN_15,
		.port = GPIO_PORT_A,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},

	// PORTB pins!!!
	[GPIO_PIOB_PIN_0] = // NC
	{
		.pin = GPIO_PIOB_PIN_0,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOB_PIN_1] = // NC
	{
		.pin = GPIO_PIOB_PIN_0,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOB_PIN_2] = // NC
	{
		.pin = GPIO_PIOB_PIN_0,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOB_PIN_3] = // PROGRAMMING SIGNAL
	{
		.pin = GPIO_PIOB_PIN_3,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},
	[GPIO_PIOB_PIN_4] = // PROGRAMMING SIGNAL
	{
		.pin = GPIO_PIOB_PIN_3,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},
	[GPIO_PIOB_PIN_5] = // NC
	{
		.pin = GPIO_PIOB_PIN_5,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOB_PIN_6] = // NC
	{
		.pin = GPIO_PIN_ESP8266_RXD,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOB_PIN_7] = // NC
	{
		.pin = GPIO_PIN_ESP8266_TXD,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOB_PIN_8] = // NC
	{
		.pin = GPIO_PIOB_PIN_8,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOB_PIN_9] = // NC
	{
		.pin = GPIO_PIOB_PIN_9,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOB_PIN_10] = // NC
	{
		.pin = GPIO_PIOB_PIN_10,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOB_PIN_11] = // NC
	{
		.pin = GPIO_PIOB_PIN_11,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOB_PIN_12] = // NC
	{
		.pin = GPIO_PIN_XR_GPIO,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},
	[GPIO_PIOB_PIN_13] = // NC
	{
		.pin = GPIO_PIOB_PIN_13,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOB_PIN_14] = // NC
	{
		.pin = GPIO_PIOB_PIN_14,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},
	[GPIO_PIOB_PIN_15] = // NC
	{
		.pin = GPIO_PIOB_PIN_15,
		.port = GPIO_PORT_B,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},

	[GPIO_PIOD_PIN_2] = // NC
	{
		.pin = GPIO_PIOD_PIN_2,
		.port = GPIO_PORT_D,
		.mode = GPIO_CONFIG_MODE_INPUT_PULLDOWN
	},

	// PORT H pins!!!
	[GPIO_PIOH_PIN_0] = // NO SETTING!
	{
		.pin = GPIO_PIOH_PIN_0,
		.port = GPIO_PORT_H,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},
	[GPIO_PIOH_PIN_1] = // NO SETTING!
	{
		.pin = GPIO_PIOH_PIN_0,
		.port = GPIO_PORT_H,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},

	[GPIO_PIOH_PIN_3] = // NO SETTING!
	{
		.pin = GPIO_PIOH_PIN_3,
		.port = GPIO_PORT_H,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},

};

#endif

