// SRW

#if !defined(SPI_CONFIG_HAL_H)
#define SPI_CONFIG_HAL_H

#include "stm32l431xx.h"
#include "stm32l4xx_hal.h"
#include "spi_access.h"
#include <stdint.h>


typedef SPI_HandleTypeDef* 		spi_handle_t;
typedef SPI_TypeDef* 			spi_instance_t;
typedef GPIO_TypeDef*  			port_t;
typedef uint8_t					alt_func_t;
typedef IRQn_Type				irqn_t;


typedef enum
{
	SPI_CONFIG_BUS_WIFI,
	SPI_CONFIG_BUS_FIRST = SPI_CONFIG_BUS_WIFI,
	NUM_SPI_CONFIG_BUSES
} spi_config_bus_e;


typedef struct
{
	spi_access_chip_id_e*	spi_bus_chip_assignments[NUM_SPI_CONFIG_BUSES];
} spi_config_chip_bus_lookup_t;


typedef struct
{
	uint16_t 	mosi;
	port_t   	mosi_port;
	alt_func_t  mosi_alt_func;
	uint16_t 	miso;
	port_t	 	miso_port;
	alt_func_t 	miso_alt_func;
	uint16_t 	sck;
	port_t	 	sck_port;
	alt_func_t 	sck_alt_func;
} spi_config_pin_t;


typedef struct
{
	spi_config_pin_t 		pin;
	irqn_t					irqn;
	spi_handle_t			handle;
} spi_config_t;


void spi_config_setup(void);
spi_handle_t spi_config_chip_id_to_bus(spi_access_chip_id_e chip_id);

#endif
