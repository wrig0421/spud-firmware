/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/

#include "spi_access_hal.h"
#include "spi_config_hal.h"
#include "spi_access.h"


void spi_access_write_byte(spi_access_chip_id_e chip_id, uint8_t data)
{

	if (HAL_OK != HAL_SPI_Transmit(spi_config_chip_id_to_bus(chip_id), &data, 1, 10000))
	{
		while (1);
	}
}


void spi_access_write_block(spi_access_chip_id_e chip_id, uint8_t* data, uint16_t len)
{
	if (HAL_OK != HAL_SPI_Transmit(spi_config_chip_id_to_bus(chip_id), data, len, 10000))
	{
		while (1);
	}
}


void spi_access_read_byte(spi_access_chip_id_e chip_id, uint8_t buf)
{
	if (HAL_OK != HAL_SPI_Receive(spi_config_chip_id_to_bus(chip_id), &buf, 1, 10000))
	{
		while (1);
	}
}


void spi_access_read_block(spi_access_chip_id_e chip_id, uint8_t* buf, uint16_t len)
{
	if (HAL_OK != HAL_SPI_Receive(spi_config_chip_id_to_bus(chip_id), buf, len, 10000))
	{
		while (1);
	}
}


void spi_access_read_and_write_block(spi_access_chip_id_e chip_id, uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len)
{
	if (HAL_OK != HAL_SPI_TransmitReceive(spi_config_chip_id_to_bus(chip_id), tx_buf, rx_buf, len, 10000))
	{
		while (1);
	}
}



