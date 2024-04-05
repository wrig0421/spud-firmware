// SRW
#if !defined(I2C_CONFIG_HAL_H)
#define I2C_CONFIG_HAL_H
#include "i2c_access.h"

#include "stm32l431xx.h"
#include "stm32l4xx_hal.h"


typedef I2C_HandleTypeDef* 		i2c_handle_t;
typedef I2C_TypeDef* 			i2c_instance_t;
typedef GPIO_TypeDef*  			port_t;
typedef uint8_t					alt_func_t;
typedef IRQn_Type				irqn_t;


typedef enum
{
	I2C_CONFIG_BUS_I2C2,
	I2C_CONFIG_BUS_FIRST = I2C_CONFIG_BUS_I2C2,
	NUM_I2C_CONFIG_BUSES,
	I2C_CONFIG_BUS_INVALID
} i2c_config_bus_e;

typedef struct
{
	i2c_access_chip_id_e*	i2c_bus_chip_assignments[NUM_I2C_CONFIG_BUSES];
} i2c_config_chip_bus_lookup_t;


typedef struct
{
	uint16_t 	scl;
	port_t   	scl_port;
	alt_func_t  scl_alt_func;
	uint16_t 	sda;
	port_t	 	sda_port;
	alt_func_t 	sda_alt_func;
} i2c_config_pin_t;


typedef struct
{
	i2c_config_pin_t 		pin;
	irqn_t					irqn;
	i2c_handle_t			handle;
} i2c_config_t;

i2c_config_bus_e i2c_config_bus_lookup_from_chip_id(i2c_access_chip_id_e chip_id);
void i2c_config_hal_setup(void);
i2c_handle_t i2c_config_chip_id_to_bus(i2c_access_chip_id_e chip_id);
i2c_handle_t i2c_config_chip_id_to_bus_handle(i2c_access_chip_id_e chip_id);

#endif
