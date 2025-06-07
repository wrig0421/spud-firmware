// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_BABY_DINOSAUR_V1)
#include "stm32l4xx_hal.h"
#include "gpio_config_hal_specific.h"
#include "gpio_config_hal.h"

const gpio_config_t g_gpio_config[NUM_GPIO_PINS] =
{
	[GPIO_PIN_SWDIO] =
	{
		.pin = GPIO_PIOA_PIN_13,
		.mode = GPIO_CONFIG_MODE_PROGRAMMING
	},
	[GPIO_PIN_SWCLK] =
	{
		.pin = GPIO_PIOA_PIN_14,
		.mode = GPIO_CONFIG_MODE_PROGRAMMING
	},
	[GPIO_PIN_XR_TX] =
	{
		.pin = GPIO_PIOC_PIN_0,
		.mode = GPIO_CONFIG_MODE_ALTERNATE_FUNCTION // LPUART1
	},
	[GPIO_PIN_XR_RX] =
	{
		.pin = GPIO_PIOC_PIN_1,
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

