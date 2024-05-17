/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/

#include "i2c_access.h"
#include "rv8803.h"


typedef enum
{
	RV8803_REGISTER_TEN_MILLISECONDS 	= 0x10,
	RV8803_REGISTER_SECONDS 			= 0x11,
	RV8803_REGISTER_MINUTES 			= 0x12,
	RV8803_REGISTER_HOURS 				= 0x13,
	RV8803_REGISTER_WEEKDAY 			= 0x14,
	RV8803_REGISTER_DATE 				= 0x15,
	RV8803_REGISTER_MONTH 				= 0x16,
	RV8803_REGISTER_YEAR 				= 0x17,
	RV8803_REGISTER_MINUTES_ALARM 		= 0x18,
	RV8803_REGISTER_HOURS_ALARM 		= 0x19,
	RV8803_REGISTER_WEEKDAY_DATE_ALARM 	= 0x1A,
	RV8803_REGISTER_TIMER_COUNTER_0 	= 0x1B,
	RV8803_REGISTER_TIMER_COUNTER_1 	= 0x1C,
	RV8803_REGISTER_EXTENSION 			= 0x1D,
	RV8803_REGISTER_FLAG 				= 0x1E,
	RV8803_REGISTER_CONTROL 			= 0x1F
} rv8803_register_e;


void rv8803_write_register(rv8803_register_e register, uint8_t data)
{
	i2c_access_write_block(I2C_ACCESS_CHIP_ID_RV_8803, &data, )
}




void i2c_access_write_block(i2c_access_chip_id_e i2c_chip_id, uint32_t memory_address, uint8_t* data, uint16_t data_length)
{
	i2c_access_hal_write_block(i2c_struct_generator(i2c_chip_id, memory_address, data, data_length));
}


void i2c_access_write_byte(i2c_access_chip_id_e i2c_chip_id, uint32_t memory_address, uint8_t data)
{
	i2c_access_write_block(i2c_chip_id, memory_address, &data, 1);
}


void i2c_access_read_block(i2c_access_chip_id_e i2c_chip_id, uint32_t memory_address, uint8_t* data, uint16_t data_length)
{
	i2c_access_hal_read_block(i2c_struct_generator(i2c_chip_id, memory_address, data, data_length));
}


void i2c_access_read_byte(i2c_access_chip_id_e i2c_chip_id, uint32_t memory_address, uint8_t* data)
{
	i2c_access_read_block(i2c_chip_id, memory_address, data, 1);
}


