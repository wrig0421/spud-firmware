// SRW
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"
#include "board_common.h"
#include "board_specific.h"
#include "spi_config_hal.h"
#include "uart_config_hal.h"
#include "gpio_config_hal_specific.h"
#include "gpio_access_hal.h"


#if defined(BOARD_SPUDGLO_V5)


void board_init_peripheral_setup(void)
{
	uart_config_hal_setup();
	spi_config_hal_setup();
}



void board_init_specific_power_cycle_level_shifter(void)
{
	gpio_access_hal_write_output_level_low(GPIO_PIN_LVL_EN);
    osDelay(1000);
	gpio_access_hal_write_output_level_high(GPIO_PIN_LVL_EN);
}


void board_init_specific_esp8266_uart_boot_enable(void)
{
	gpio_access_hal_pin_output(GPIO_PIN_ESP8266_GPIO0);
	gpio_access_hal_write_output_level_low(GPIO_PIN_ESP8266_GPIO0);
}


void board_init_specific_esp8266_uart_boot_disable(void)
{
	gpio_access_hal_pin_output(GPIO_PIN_ESP8266_GPIO0);
	gpio_access_hal_write_output_level_high(GPIO_PIN_ESP8266_GPIO0);
}


void board_init_specific_esp8266_power_enable(void)
{
	gpio_access_hal_pin_output(GPIO_PIN_ESP8266_EN);
	gpio_access_hal_write_output_level_high(GPIO_PIN_ESP8266_EN);
}


void board_init_specific_esp8266_power_disable(void)
{
	gpio_access_hal_pin_output(GPIO_PIN_ESP8266_EN);
	gpio_access_hal_write_output_level_low(GPIO_PIN_ESP8266_EN);
}


void board_init_specific_esp8266_reset_assert(void)
{
	gpio_access_hal_pin_output(GPIO_PIN_ESP8266_RST);
	gpio_access_hal_write_output_level_low(GPIO_PIN_ESP8266_RST);
}


void board_init_specific_esp8266_reset_deassert(void)
{
	gpio_access_hal_pin_output(GPIO_PIN_ESP8266_RST);
	gpio_access_hal_write_output_level_high(GPIO_PIN_ESP8266_RST);
}


#endif

