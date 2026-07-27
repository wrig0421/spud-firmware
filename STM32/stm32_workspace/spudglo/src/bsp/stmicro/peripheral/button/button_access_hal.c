// SRW

#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "button_access_hal.h"
#include "button_config_hal.h"


extern const button_config_t g_button_config[NUM_BUTTONS];


bool button_access_hal_button_is_active(button_e btn)
{
	bool ret_val = false;
	button_config_t btn_cfg = g_button_config[btn];

	if ((BUTTON_CONFIG_ACTIVE_LVL_LOW == btn_cfg.lvl) \
			&& (GPIO_PIN_RESET == HAL_GPIO_ReadPin(btn_cfg.port, btn_cfg.pin)))
	{
		ret_val = true;
	}
	else if ((BUTTON_CONFIG_ACTIVE_LVL_HIGH == btn_cfg.lvl) \
			&& (GPIO_PIN_SET == HAL_GPIO_ReadPin(btn_cfg.port, btn_cfg.pin)))
	{
		ret_val = true;
	}
	else
	{
		ret_val = false;
	}
	return ret_val;
}


bool button_access_hal_button_is_not_active(button_e btn)
{
	return !button_access_hal_button_is_active(btn);
}


bool button_access_hal_button_is_high(button_e btn)
{
	button_config_t btn_cfg = g_button_config[btn];

	return ((GPIO_PIN_SET == HAL_GPIO_ReadPin(btn_cfg.port, btn_cfg.pin)) ? true : false);
}


bool button_access_hal_button_is_low(button_e btn)
{
	return !button_access_hal_button_is_high(btn);
}
