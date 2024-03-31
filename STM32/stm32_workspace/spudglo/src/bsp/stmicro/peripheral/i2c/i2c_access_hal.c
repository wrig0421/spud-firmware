// SRW

#include "stm32l4xx_hal.h"
#include "i2c_access_hal.h"
#include "i2c_config_hal.h"



HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,
                                    uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,
                                   uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);





void i2c_access_hal_write_byte(i2c_access_chip_id_e i2c_chip_id, uint8_t data)
{

}


void i2c_access_hal_write_block(i2c_access_chip_id_e i2c_chip_id, uint8_t* data, uint16_t len)
{

}


void i2c_access_hal_read_byte(i2c_access_chip_id_e i2c_chip_id, uint8_t* buf)
{

}


void i2c_access_hal_read_block(i2c_access_chip_id_e i2c_chip_id, uint8_t* buf, uint16_t len)
{

}


