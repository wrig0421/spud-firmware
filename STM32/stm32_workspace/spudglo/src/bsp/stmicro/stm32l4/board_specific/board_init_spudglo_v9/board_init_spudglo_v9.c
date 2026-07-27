// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_V9)


#include "stm32l4xx_hal.h"

#include "board_specific.h"
#include "spi_config_hal.h"
#include "uart_config_hal.h"
#include "gpio_config_hal_specific.h"
#include "gpio_access_hal.h"
#include "free_rtos_convenience.h"

void board_init_peripheral_setup(void)
{
	uart_config_hal_setup();
//	spi_config_hal_setup();
}


void board_init_specific_power_cycle_level_shifter(void)
{
	gpio_access_hal_write_output_level_low(GPIO_PIN_LVL_EN);
    free_rtos_delay_ms(1000);
	gpio_access_hal_write_output_level_high(GPIO_PIN_LVL_EN);
}


void board_init_specific(void)
{

}

#endif

