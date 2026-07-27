// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_BABY_DINOSAUR_V1)
#include "stm32l4xx_hal.h"
#include "gpio_config_hal_specific.h"
#include "gpio_config_hal.h"

const gpio_config_t g_gpio_config[NUM_GPIO_PINS] =
{

	[GPIO_PIOA_PIN_9] =
	{
		.pin = GPIO_PIN_TIM1_CH1,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION
	},

	[GPIO_PIOA_PIN_13] =
	{
		.pin = GPIO_PIN_SWDIO,
		.mode = GPIO_CONFIG_MODE_PROGRAMMING
	},
	[GPIO_PIOA_PIN_14] =
	{
		.pin = GPIO_PIN_SWCLK,
		.mode = GPIO_CONFIG_MODE_PROGRAMMING
	},
	[GPIO_PIOC_PIN_0] =
	{
		.pin = GPIO_PIN_XR_TX,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION // LPUART1
	},
	[GPIO_PIOC_PIN_1] =
	{
		.pin = GPIO_PIN_XR_RX,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION // LPUART1
	},
	[GPIO_PIN_OSC48_HI] =
	{
		.pin = GPIO_PIOH_PIN_0,
		.mode = GPIO_CONFIG_MODE_NO_SETTING,
	},
	[GPIO_PIN_OSC48_LO] =
	{
		.pin = GPIO_PIOH_PIN_1,
		.mode = GPIO_CONFIG_MODE_NO_SETTING,
	},
	[GPIO_PIN_BOOT0] = // NC
	{
		.pin = GPIO_PIOH_PIN_3,
		.mode = GPIO_CONFIG_MODE_NO_SETTING
	},
};

#endif // BOARD_SPUDGLO_BABY_DINOSAUR_V1P0

