// SRW

#include "stm32l4xx_hal.h"
#include "rng_access_hal.h"
#include "rng_config_hal.h"

extern RNG_HandleTypeDef g_rng_handle;

void rng_access_hal_generate_random_number(void)
{
    HAL_RNG_GenerateRandomNumber_IT(&g_rng_handle);
}

uint32_t rng_access_hal_read_random_number(void)
{
    return g_rng_handle.RandomNumber;
}


uint32_t rng_access_hal_read_and_generate_random_number(void)
{
    uint32_t random_number = rng_access_hal_read_random_number();
    rng_access_hal_generate_random_number();
    return random_number;
}

//
//void i2c_access_hal_write_block(i2c_access_chip_info_t* i2c_chip_info)
//{
//	i2c_handle_t i2c_handle = i2c_config_chip_id_to_bus_handle(i2c_chip_info->chip_id);
//
//	if (HAL_OK != HAL_I2C_Mem_Write(i2c_handle, i2c_chip_info->chip_address << 1, i2c_chip_info->chip_memory_address,
//									i2c_chip_info->chip_memory_address_width_bytes, i2c_chip_info->tx_rx_buffer,
//									i2c_chip_info->num_byte_to_tx_rx, I2C_DEFAULT_TIMEOUT_MS))
//	{
//		while (1);
//	}
//}
//
//
//void i2c_access_hal_read_block(i2c_access_chip_info_t* i2c_chip_info)
//{
//	i2c_handle_t i2c_handle = i2c_config_chip_id_to_bus_handle(i2c_chip_info->chip_id);
//	HAL_I2C_Mem_Read(i2c_handle, i2c_chip_info->chip_address << 1, i2c_chip_info->chip_memory_address,
//						i2c_chip_info->chip_memory_address_width_bytes, i2c_chip_info->tx_rx_buffer,
//						i2c_chip_info->num_byte_to_tx_rx, I2C_DEFAULT_TIMEOUT_MS);
//}


