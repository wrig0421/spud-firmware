// SRW
#include "config.h"

#if defined(BOARD_SPUDGLO_BABY_DINOSAUR_V1)

#include "uart_config_hal.h"
#include "gpio_config_hal_specific.h"


void board_init_peripheral_setup(void)
{
	uart_config_hal_setup();
}


void board_init_specific(void)
{

}


#endif


