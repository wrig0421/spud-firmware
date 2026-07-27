// SRW

#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "spi_config_hal.h"


extern SPI_HandleTypeDef g_spi_handle_config[NUM_SPI_CONFIG_BUSES];
extern const spi_config_t g_spi_config[NUM_SPI_CONFIG_BUSES];
extern const spi_access_chip_id_e* g_spi_chip_bus_lookup[NUM_SPI_CONFIG_BUSES];
extern uint16_t g_spi_num_chips_per_bus[NUM_SPI_CONFIG_BUSES];
extern spi_handle_t g_spi_chip_id_handle[NUM_SPI_ACCESS_CHIP_IDS];
//spi_handle_t g_spi_chip_id_handle[spi_access_chip_id_e];


static spi_handle_t spi_config_bus_lookup_from_chip_id(spi_access_chip_id_e chip_id)
{
	for (spi_config_bus_e bus = SPI_CONFIG_BUS_FIRST; bus < NUM_SPI_CONFIG_BUSES; bus++)
	{
		for (uint16_t iii = 0; iii < sizeof(g_spi_chip_bus_lookup[bus]); iii++)
		{
			if (g_spi_chip_bus_lookup[bus][iii] == chip_id)
			{
				return &g_spi_handle_config[bus];
			}
		}
	}
	return NULL;
}



void spi_config_hal_setup(void)
{
    //RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    GPIO_InitTypeDef  GPIO_InitStruct;

    for (spi_config_bus_e bus = SPI_CONFIG_BUS_FIRST; bus < NUM_SPI_CONFIG_BUSES; bus++)
    {
    	if (g_spi_num_chips_per_bus[bus])
    	{
    	    GPIO_InitStruct.Pin       = g_spi_config[bus].pin.mosi;
    	    GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
    	    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    	    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
//    	    GPIO_InitStruct.Alternate = g_spi_config[bus].pin.mosi_alt_func;
    	    HAL_GPIO_Init(g_spi_config[bus].pin.mosi_port, &GPIO_InitStruct);

    	    GPIO_InitStruct.Pin       = g_spi_config[bus].pin.miso;
    	    GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
    	    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    	    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
//    	    GPIO_InitStruct.Alternate = g_spi_config[bus].pin.miso_alt_func;
    	    HAL_GPIO_Init(g_spi_config[bus].pin.miso_port, &GPIO_InitStruct);

    	    GPIO_InitStruct.Pin       = g_spi_config[bus].pin.sck;
    	    GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
    	    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    	    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
//    	    GPIO_InitStruct.Alternate = g_spi_config[bus].pin.sck_alt_func;
    	    HAL_GPIO_Init(g_spi_config[bus].pin.sck_port, &GPIO_InitStruct);

    	    GPIO_InitStruct.Pin       = g_spi_config[bus].pin.csn;
    	    GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
    	    GPIO_InitStruct.Pull      = GPIO_NOPULL;
//    	    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    	    HAL_GPIO_Init(g_spi_config[bus].pin.csn_port, &GPIO_InitStruct);

        	switch (bus)
        	{
        		case SPI_CONFIG_BUS_WIFI:
        		    __HAL_RCC_SPI1_CLK_ENABLE();
        		break;
        		default:
				break;
        	}
    	    if(HAL_SPI_Init(g_spi_config[bus].handle) != HAL_OK)
    	    {
    	        /* Initialization Error */
    	        while(1);
    	    }
    	}
    }
    // TODO make this an array that gets populated so you don't need to lookup everytime..
//    for (spi_access_chip_id_e chip_id = SPI_ACCESS_CHIP_ID_FIRST; chip_id < NUM_SPI_ACCESS_CHIP_IDS; chip_id++)
//    {
//    	g_spi_chip_id_handle[chip_id] = spi_config_bus_lookup_from_chip_id(chip_id);
//    }
}


spi_handle_t spi_config_chip_id_to_bus(spi_access_chip_id_e chip_id)
{
	return spi_config_bus_lookup_from_chip_id(chip_id);
}



