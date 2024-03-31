// SRW
#include "i2c_config_hal.h"

extern I2C_HandleTypeDef g_i2c_handle_config[NUM_I2C_CONFIG_BUSES];
extern const i2c_config_t g_i2c_config[NUM_I2C_CONFIG_BUSES];
extern const i2c_access_chip_id_e* g_i2c_chip_bus_lookup[NUM_I2C_CONFIG_BUSES];
extern uint16_t g_i2c_num_chips_per_bus[NUM_I2C_CONFIG_BUSES];
extern i2c_handle_t g_i2c_chip_id_handle[NUM_I2C_ACCESS_CHIP_IDS];


static i2c_handle_t i2c_config_bus_lookup_from_chip_id(i2c_access_chip_id_e chip_id)
{
	for (i2c_config_bus_e bus = I2C_CONFIG_BUS_FIRST; bus < NUM_I2C_CONFIG_BUSES; bus++)
	{
		for (uint16_t iii = 0; iii < sizeof(g_i2c_chip_bus_lookup[bus]); iii++)
		{
			if (g_i2c_chip_bus_lookup[bus][iii] == chip_id)
			{
				return &g_i2c_handle_config[bus];
			}
		}
	}
	return NULL;
}



void i2c_config_hal_setup(void)
{
    //RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    for (i2c_config_bus_e bus = I2C_CONFIG_BUS_FIRST; bus < NUM_I2C_CONFIG_BUSES; bus++)
    {
    	if (g_i2c_num_chips_per_bus[bus])
    	{
    	    GPIO_InitStruct.Pin       = g_i2c_config[bus].pin.scl;
    	    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    	    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    	    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    	    GPIO_InitStruct.Alternate = g_i2c_config[bus].pin.scl_alt_func;
    	    HAL_GPIO_Init(g_i2c_config[bus].pin.scl_port, &GPIO_InitStruct);

    	    GPIO_InitStruct.Pin       = g_spi_config[bus].pin.sda;
    	    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    	    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    	    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    	    GPIO_InitStruct.Alternate = g_i2c_config[bus].pin.sda_alt_func;
    	    HAL_GPIO_Init(g_i2c_config[bus].pin.sda_port, &GPIO_InitStruct);

        	switch (bus)
        	{
        		case I2C_CONFIG_BUS_I2C2:
        		    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C2;
        		    PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
        		    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
        		    {
        		    	//Error_Handler();
        		    }
        		    __HAL_RCC_I2C2_CLK_ENABLE();
        		break;
        		default:
				break;
        	}
    	    if(HAL_OK != HAL_I2C_DeInit(g_i2c_config[bus].handle))
    	    {
    	        /* Deinitialization Error */
    	        while(1);
    	    }
    	    if(HAL_OK != HAL_I2C_Init(g_i2c_config[bus].handle))
    	    {
    	        /* Initialization Error */
    	        while(1);
    	    }
    	    HAL_NVIC_SetPriority(g_i2c_config[bus].irqn, 0, 1);
    	    HAL_NVIC_EnableIRQ(g_i2c_config[bus].irqn);
    	    HAL_NVIC_ClearPendingIRQ(g_i2c_config[bus].irqn);
    	}
    }
    // TODO make this an array that gets populated so you don't need to lookup everytime..
//    for (spi_access_chip_id_e chip_id = SPI_ACCESS_CHIP_ID_FIRST; chip_id < NUM_SPI_ACCESS_CHIP_IDS; chip_id++)
//    {
//    	g_spi_chip_id_handle[chip_id] = spi_config_bus_lookup_from_chip_id(chip_id);
//    }
}


i2c_handle_t i2c_config_chip_id_to_bus(i2c_access_chip_id_e chip_id)
{
	return i2c_config_bus_lookup_from_chip_id(chip_id);
}


