///***********************************
// * @file   animate_led.h
// * @author SpudGlo LLC
// ***********************************/
//#if !defined(I2C_ACCESS_H)
//#define I2C_ACCESS_H
//#include <stdint.h>
//
//typedef enum
//{
//	I2C_ACCESS_CHIP_ID_RV_8803,
//	I2C_ACCESS_CHIP_ID_FIRST = I2C_ACCESS_CHIP_ID_RV_8803,
//	NUM_I2C_ACCESS_CHIP_IDS
//} i2c_access_chip_id_e;
//
//
//
//typedef enum
//{
//	I2C_ACCESS_CHIP_ADDRESS_RV_8803 		= 0x32,
//	I2C_ACCESS_CHIP_ADDRESS_INVALID			= UINT32_MAX
//} i2c_access_chip_address_e;
//
//
//
//typedef struct
//{
//	uint16_t 					chip_memory_address;
//	uint16_t					chip_memory_address_width_bytes;
//} i2c_access_chip_config_t;
//
//
//// may need to pack this.. Probably..
//typedef struct
//{
//	i2c_access_chip_address_e 	chip_address;
//	uint32_t 					chip_memory_address;
//	uint16_t					chip_memory_address_width_bytes;
//	uint16_t					num_byte_to_tx_rx;
//	uint8_t*					tx_rx_buffer;
//} i2c_access_chip_info_t;
//
//#endif
