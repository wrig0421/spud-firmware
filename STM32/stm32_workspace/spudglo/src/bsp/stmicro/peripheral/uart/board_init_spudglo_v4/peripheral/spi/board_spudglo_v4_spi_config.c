// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_V4)
#include "stm32l4xx_hal.h"

#include "spi_config_hal.h"

#define SPI1_SCK			GPIO_PIN_1
#define SPI1_CIPO     		GPIO_PIN_11
#define SPI1_COPI   		GPIO_PIN_12
#define SPI1_CSN			GPIO_PIN_4

SPI_HandleTypeDef       g_spi_handle_config[NUM_SPI_CONFIG_BUSES] =
{
	[SPI_CONFIG_BUS_DISP] =
	{
		.Instance               = SPI1,
		.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256,
		.Init.Direction         = SPI_DIRECTION_2LINES,
		.Init.CLKPhase          = SPI_PHASE_1EDGE,
		.Init.CLKPolarity       = SPI_POLARITY_LOW,
		.Init.DataSize          = SPI_DATASIZE_8BIT,
		.Init.FirstBit          = SPI_FIRSTBIT_MSB,
		.Init.TIMode            = SPI_TIMODE_DISABLE,
		.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE,
		.Init.CRCPolynomial     = 7,
		.Init.CRCLength         = SPI_CRC_LENGTH_8BIT,
		.Init.NSS               = SPI_NSS_SOFT,
		.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE,
		.Init.Mode              = SPI_MODE_MASTER
	}
};


const spi_config_t g_spi_config[NUM_SPI_CONFIG_BUSES] =
{
	[SPI_CONFIG_BUS_DISP] =
	{
		.pin.mosi = SPI1_COPI,
		.pin.mosi_port = GPIOA,
		.pin.mosi_alt_func = GPIO_AF5_SPI1,
		.pin.miso = SPI1_CIPO,
		.pin.miso_port = GPIOA,
		.pin.miso_alt_func = GPIO_AF5_SPI1,
		.pin.sck = SPI1_SCK,
		.pin.sck_port = GPIOA,
		.pin.sck_alt_func = GPIO_AF5_SPI1,
		.pin.csn = SPI1_CSN,
		.pin.csn_port = GPIOA,
		.irqn = SPI1_IRQn,
		.handle = &g_spi_handle_config[SPI_CONFIG_BUS_DISP]
	}
};


const spi_access_chip_id_e g_spi1_chips[] =
{
	SPI_ACCESS_CHIP_ID_DISP
};


#define SPI1_NUM_CHIPS (sizeof(g_spi1_chips) / sizeof(spi_access_chip_id_e))


uint16_t g_spi_num_chips_per_bus[NUM_SPI_CONFIG_BUSES] =
{
	[SPI_CONFIG_BUS_DISP] = SPI1_NUM_CHIPS
};


const spi_access_chip_id_e* g_spi_chip_bus_lookup[NUM_SPI_CONFIG_BUSES] =
{
	[SPI_CONFIG_BUS_DISP] = g_spi1_chips
};



#endif

