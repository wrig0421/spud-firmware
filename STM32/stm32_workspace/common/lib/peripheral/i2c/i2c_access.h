/***********************************
 * @file   animate_led.h
 * @author SpudGlo LLC
 ***********************************/
#if !defined(I2C_ACCESS_H)
#define I2C_ACCESS_H


typedef enum
{
	I2C_ACCESS_CHIP_ID_RV_8803,
	I2C_ACCESS_CHIP_ID_FIRST = I2C_ACCESS_CHIP_ID_RV_8803,
	NUM_I2C_ACCESS_CHIP_IDS
} i2c_access_chip_id_e;



typedef enum
{
	I2C_ACCESS_CHIP_ADDRESS_RV_8803 = 0x32
} i2c_access_chip_address_e;

#endif
