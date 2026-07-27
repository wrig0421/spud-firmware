/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/


#include "i2c_access_hal.h"
#include "i2c_config_hal.h"
#include "i2c_access.h"

i2c_access_chip_address_e 	chip_address;
uint16_t 					chip_memory_address;
uint16_t					chip_memory_address_width_bytes;
uint8_t*					tx_rx_buffer;
uint16_t					num_byte_to_tx_rx;

typedef enum
{
	I2C_ACCESS_CHIP_MEMORY_ADDRESS_WIDTH_0_BYTE = 0,
	I2C_ACCESS_CHIP_MEMORY_ADDRESS_WITDTH_1_BYTE = 1,
	I2C_ACCESS_CHIP_MEMORY_ADDRESS_WITDTH_2_BYTE = 2,
	I2C_ACCESS_CHIP_MEMORY_ADDRESS_WITDTH_3_BYTE = 3,
	I2C_ACCESS_CHIP_MEMORY_ADDRESS_WITDTH_4_BYTE = 4
} i2c_access_chip_memory_address_width_bytes_e;


i2c_access_chip_info_t g_i2c_access_chip_info[NUM_I2C_CONFIG_BUSES] =
{
	[I2C_CONFIG_BUS_I2C2] =
	{
		.chip_address 						= I2C_ACCESS_CHIP_ADDRESS_INVALID,
		.chip_memory_address 				= 0,
		.chip_memory_address_width_bytes 	= I2C_ACCESS_CHIP_MEMORY_ADDRESS_WIDTH_0_BYTE,
		.tx_rx_buffer 						= NULL,
		.num_byte_to_tx_rx					= 0
	}
};



i2c_access_chip_config_t g_i2c_access_chip_config[NUM_I2C_ACCESS_CHIP_IDS] =
{
	[I2C_ACCESS_CHIP_ID_RV_8803] =
	{
		.chip_memory_address 				= I2C_ACCESS_CHIP_ADDRESS_RV_8803,
		.chip_memory_address_width_bytes 	= I2C_ACCESS_CHIP_MEMORY_ADDRESS_WITDTH_1_BYTE
	}
};


i2c_access_chip_info_t* i2c_struct_generator(i2c_access_chip_id_e i2c_chip_id, uint32_t memory_address, uint8_t* data, uint16_t data_length)
{
	// need to look up bus from chip id here...
	i2c_config_bus_e i2c_config_bus = i2c_config_bus_lookup_from_chip_id(i2c_chip_id);
	g_i2c_access_chip_info[i2c_config_bus].chip_id = i2c_chip_id;
	g_i2c_access_chip_info[i2c_config_bus].chip_address = g_i2c_access_chip_config[I2C_ACCESS_CHIP_ID_RV_8803].chip_memory_address;
	g_i2c_access_chip_info[i2c_config_bus].chip_memory_address_width_bytes = g_i2c_access_chip_config[I2C_ACCESS_CHIP_ID_RV_8803].chip_memory_address_width_bytes;
	g_i2c_access_chip_info[i2c_config_bus].chip_memory_address = memory_address;
	g_i2c_access_chip_info[i2c_config_bus].tx_rx_buffer = data;
	g_i2c_access_chip_info[i2c_config_bus].num_byte_to_tx_rx = data_length;
	return &g_i2c_access_chip_info[i2c_config_bus];
}


void i2c_access_setup(void)
{
	i2c_config_hal_setup();
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


