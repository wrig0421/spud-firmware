// SRW

#include "stm32l4xx_hal.h"
#include "i2c_access_hal.h"
#include "i2c_config_hal.h"

#define I2C_DEFAULT_TIMEOUT_MS	5000



void i2c_access_hal_write_block(i2c_access_chip_info_t* i2c_chip_info)
{
	i2c_handle_t i2c_handle = i2c_config_chip_id_to_bus_handle(i2c_chip_info->chip_id);
	if (HAL_OK != HAL_I2C_Mem_Write(i2c_handle, i2c_chip_info->chip_address << 1, i2c_chip_info->chip_memory_address,
									i2c_chip_info->chip_memory_address_width_bytes, i2c_chip_info->tx_rx_buffer,
									i2c_chip_info->num_byte_to_tx_rx, I2C_DEFAULT_TIMEOUT_MS))
	{
		while (1);
	}
}


void i2c_access_hal_read_block(i2c_access_chip_info_t* i2c_chip_info)
{
	i2c_handle_t i2c_handle = i2c_config_chip_id_to_bus_handle(i2c_chip_info->chip_id);
	HAL_I2C_Mem_Read(i2c_handle, i2c_chip_info->chip_address << 1, i2c_chip_info->chip_memory_address,
						i2c_chip_info->chip_memory_address_width_bytes, i2c_chip_info->tx_rx_buffer,
						i2c_chip_info->num_byte_to_tx_rx, I2C_DEFAULT_TIMEOUT_MS);
}


