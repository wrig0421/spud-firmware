// SRW

#include "stm32l4xx_hal.h"
#include "spi_access_hal.h"


void spi_access_hal_write_byte(spi_handle_t ph_spi, uint8_t data)
{
	if (HAL_OK != HAL_SPI_Transmit(ph_spi, &data, 1, 10000))
	{
		while (1);
	}
}


void spi_access_hal_write_block(spi_handle_t ph_spi, uint8_t* data, uint16_t len)
{
	if (HAL_OK != HAL_SPI_Transmit(ph_spi, data, len, 10000))
	{
		while (1);
	}
}


void spi_access_hal_read_byte(spi_handle_t ph_spi, uint8_t buf)
{
	if (HAL_OK != HAL_SPI_Receive(ph_spi, &buf, 1, 10000))
	{
		while (1);
	}
}


void spi_access_hal_read_block(spi_handle_t ph_spi, uint8_t* buf, uint16_t len)
{
	if (HAL_OK != HAL_SPI_Receive(ph_spi, buf, len, 10000))
	{
		while (1);
	}
}


void spi_access_hal_read_and_write_block(spi_handle_t ph_spi, uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len)
{
	if (HAL_OK != HAL_SPI_TransmitReceive(ph_spi, tx_buf, rx_buf, len, 10000))
	{
		while (1);
	}
}






