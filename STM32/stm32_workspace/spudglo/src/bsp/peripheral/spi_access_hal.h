// SRW

#if !defined(SPI_ACCESS_HAL_H)
#define SPI_ACCESS_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include "spi_config_hal.h"



spi_handle_t spi_config_host_handle(void);


void spi_access_write_and_read(uint8_t *tx_data, uint8_t *rx_data, uint16_t size);
void spi_access_hal_write_byte(spi_handle_t ph_spi, uint8_t data);
void spi_access_hal_write_block(spi_handle_t ph_spi, uint8_t* data, uint16_t len);
void spi_access_hal_read_byte(spi_handle_t ph_spi, uint8_t buf);
void spi_access_hal_read_block(spi_handle_t ph_spi, uint8_t* buf, uint16_t len);
void spi_access_hal_read_and_write_block(spi_handle_t ph_spi, uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len);


#endif
