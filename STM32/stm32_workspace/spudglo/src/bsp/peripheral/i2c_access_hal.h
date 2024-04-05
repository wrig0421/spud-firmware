// SRW

#if !defined(I2C_ACCESS_HAL_H)
#define I2C_ACCESS_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include "i2c_config_hal.h"


i2c_handle_t i2c_config_i2c2_handle(void);

void i2c_access_hal_write_block(i2c_access_chip_info_t* i2c_chip_info);
void i2c_access_hal_read_block(i2c_access_chip_info_t* i2c_chip_info);

#endif
