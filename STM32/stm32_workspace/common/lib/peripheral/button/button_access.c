/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/
#include "config.h"
#if defined(ENABLE_BUTTON)

#include "button_access_hal.h"
#include "button_config_hal.h"
#include "button_access.h"


void button_access_setup(void)
{
	button_config_hal_setup();
}


bool button_access_button_is_active(button_e btn)
{
	return button_access_hal_button_is_active(btn);
}


bool button_access_button_is_not_active(button_e btn)
{
	return button_access_hal_button_is_not_active(btn);
}


bool button_access_button_is_high(button_e btn)
{
	return button_access_hal_button_is_high(btn);
}


bool button_access_button_is_low(button_e btn)
{
	return button_access_hal_button_is_low(btn);
}

#endif
