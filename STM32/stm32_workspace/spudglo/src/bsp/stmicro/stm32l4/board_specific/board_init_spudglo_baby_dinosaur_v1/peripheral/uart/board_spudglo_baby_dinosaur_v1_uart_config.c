// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_BABY_DINOSAUR_V1)
#include "stm32l4xx_hal.h"
#include "uart_access.h"
#include "uart_config_hal.h"

#define PIN_XR_TX               GPIO_PIN_0
#define PIN_XR_RX               GPIO_PIN_1

UART_HandleTypeDef g_uart_handle_config[NUM_UART_CONFIG_BUSES] =
{
	[LPUART_CONFIG_BUS_INSTANCE_1] =
	{
		.Instance = LPUART1,
		.Init.BaudRate = 921600,
		.Init.WordLength = UART_WORDLENGTH_8B,
		.Init.StopBits = UART_STOPBITS_1,
		.Init.Parity = UART_PARITY_NONE,
		.Init.Mode           = UART_MODE_TX_RX,
		.Init.HwFlowCtl      = UART_HWCONTROL_NONE,
		.Init.OverSampling = UART_OVERSAMPLING_16,
		.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE,
		.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
		.AdvancedInit.OverrunDisable = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT|UART_ADVFEATURE_DMADISABLEONERROR_INIT,
		.AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR
	}
};


const uart_config_t g_uart_config[NUM_UART_CONFIG_BUSES] =
{
	[LPUART_CONFIG_BUS_INSTANCE_1] =
	{
		.pin.rx = PIN_XR_TX,
		.pin.rx_alt_func = GPIO_AF8_LPUART1,
		.pin.tx = PIN_XR_RX,
		.pin.tx_alt_func = GPIO_AF8_LPUART1,
		.irqn = LPUART1_IRQn
	}
};


const uart_access_id_e g_lpuart1_chips[] =
{
	UART_ACCESS_ID_HOST
};


#define LPUART1_NUM_CHIPS (sizeof(g_lpuart1_chips) / sizeof(uart_access_id_e))


uint16_t g_uart_num_chips_per_bus[NUM_UART_CONFIG_BUSES] =
{
	[UART_CONFIG_BUS_INSTANCE_1] = 0,
	[UART_CONFIG_BUS_INSTANCE_2] = 0,
	[UART_CONFIG_BUS_INSTANCE_3] = 0,
	[LPUART_CONFIG_BUS_INSTANCE_1] = LPUART1_NUM_CHIPS
};


const uart_access_id_e* g_uart_chip_bus_lookup[NUM_UART_CONFIG_BUSES] =
{
	[UART_CONFIG_BUS_HOST] = g_lpuart1_chips,
};


#endif

