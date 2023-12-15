// SRW

#if !defined(SPI_ACCESS_HAL_H)
#define SPI_ACCESS_HAL_H

#include <stdint.h>
#include <stdbool.h>

void spi_access_hal_setup(void)

void spi_access_hal_write_byte(void);
void spi_access_hal_write_block(void);

void spi_access_hal_read_byte(void);
void spi_access_hal_read_block(void);

#endif
