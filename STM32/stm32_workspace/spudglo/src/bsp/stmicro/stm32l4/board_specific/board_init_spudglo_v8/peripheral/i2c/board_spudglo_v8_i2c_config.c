// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_V8P0)
#include "stm32l4xx_hal.h"
#include "gpio_config_hal.h"
#include "i2c_config_hal.h"

#define I2C2_SCL		GPIO_PIN_10
#define I2C2_SDA		GPIO_PIN_11
#define I2C2_PORT		GPIO_PORT_B


I2C_HandleTypeDef	g_i2c_handle_config[NUM_I2C_CONFIG_BUSES] =
{
	[I2C_CONFIG_BUS_I2C2] =
	{
		.Instance = I2C2,
		.Init.Timing = 0x00B0D8FF,
		.Init.OwnAddress1 = 0,
		.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT,
		.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE,
		.Init.OwnAddress2 = 0,
		.Init.OwnAddress2Masks = I2C_OA2_NOMASK,
		.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE,
		.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE
	}
};


const i2c_config_t g_i2c_config[NUM_I2C_CONFIG_BUSES] =
{
	[I2C_CONFIG_BUS_I2C2] =
	{
		.pin.scl = I2C2_SCL,
		.pin.scl_port = I2C2_PORT,
		.pin.scl_alt_func = GPIO_AF4_I2C2,
		.pin.sda = I2C2_SDA,
		.pin.sda_port = I2C2_PORT,
		.pin.sda_alt_func = GPIO_AF4_I2C2,
		.irqn = I2C2_EV_IRQn,
		.handle = &g_i2c_handle_config[I2C_CONFIG_BUS_I2C2]
	}
};


const i2c_access_chip_id_e g_i2c2_chips[] =
{
	I2C_ACCESS_CHIP_ID_RV_8803
};

#define I2C2_NUM_CHIPS (sizeof(g_i2c2_chips) / sizeof(i2c_access_chip_id_e))


uint16_t g_i2c_num_chips_per_bus[NUM_I2C_CONFIG_BUSES] =
{
	[I2C_CONFIG_BUS_I2C2] = I2C2_NUM_CHIPS
};


const i2c_access_chip_id_e* g_i2c_chip_bus_lookup[NUM_I2C_CONFIG_BUSES] =
{
	[I2C_CONFIG_BUS_I2C2] = g_i2c2_chips
};


#endif

