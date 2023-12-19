// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_V5P0)
#include "stm32l4xx_hal.h"

#include "spi_config_hal.h"

#define ESP8266_SCK			GPIO_PIN_1
#define ESP8266_MISO     	GPIO_PIN_11
#define ESP8266_MOSI   		GPIO_PIN_12

SPI_HandleTypeDef       g_spi_handle_config[NUM_SPI_CONFIG_BUSES] =
{
	[SPI_CONFIG_BUS_WIFI] =
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
	[SPI_CONFIG_BUS_WIFI] =
	{
		.pin.mosi = ESP8266_MOSI,
		.pin.mosi_port = GPIOA,
		.pin.mosi_alt_func = GPIO_AF5_SPI1,
		.pin.miso = ESP8266_MISO,
		.pin.miso_port = GPIOA,
		.pin.miso_alt_func = GPIO_AF5_SPI1,
		.pin.sck = ESP8266_SCK,
		.pin.sck_port = GPIOA,
		.pin.sck_alt_func = GPIO_AF5_SPI1,
		.irqn = SPI1_IRQn,
		.handle = &g_spi_handle_config[SPI_CONFIG_BUS_WIFI]
	}
};


const spi_access_chip_id_e g_spi1_chips[] =
{
	SPI_ACCESS_CHIP_ID_ESP8266
};


#define SPI1_NUM_CHIPS (sizeof(g_spi1_chips) / sizeof(spi_access_chip_id_e))


uint16_t g_spi_num_chips_per_bus[NUM_SPI_CONFIG_BUSES] =
{
	[SPI_CONFIG_BUS_WIFI] = SPI1_NUM_CHIPS
};


const spi_access_chip_id_e* g_spi_chip_bus_lookup[NUM_SPI_CONFIG_BUSES] =
{
	[SPI_CONFIG_BUS_WIFI] = g_spi1_chips
};


//const spi_config_chip_bus_lookup_t g_spi_chip_bus_assignments =
//{
//	spi_bus_chips[SPI_CONFIG_BUS_WIFI] = g_spi1_chips
//};


spi_handle_t spi_chip_id_handle(spi_access_chip_id_e chip_id)
{


}




#endif

