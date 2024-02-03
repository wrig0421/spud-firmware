/***********************************
 * @file   animate_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(SPI_ACCESS_H)
#define SPI_ACCESS_H


typedef enum
{
	SPI_ACCESS_CHIP_ID_ESP8266,
	SPI_ACCESS_CHIP_ID_FIRST = SPI_ACCESS_CHIP_ID_ESP8266,
	SPI_ACCESS_CHIP_ID_DISP,
	NUM_SPI_ACCESS_CHIP_IDS
} spi_access_chip_id_e;


void spi_access_write_byte(spi_access_chip_id_e chip_id, uint8_t data);
void spi_access_write_block(spi_access_chip_id_e chip_id, uint8_t* data, uint16_t len);
void spi_access_read_byte(spi_access_chip_id_e chip_id, uint8_t buf);
void spi_access_read_block(spi_access_chip_id_e chip_id, uint8_t* buf, uint16_t len);
void spi_access_read_and_write_block(spi_access_chip_id_e chip_id, uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len);



#endif
