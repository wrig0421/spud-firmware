// SRW

#if !defined(SPI_ACCESS_H)
#define SPI_ACCESS_H

#include <stdint.h>
#include <stdbool.h>

void spi_access_setup(void);
void spi_access_write_and_read(uint8_t *tx_data, uint8_t *rx_data, uint16_t size);


#endif
