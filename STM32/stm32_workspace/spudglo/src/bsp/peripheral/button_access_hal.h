// SRW

#if !defined(BUTTON_ACCESS_HAL_H)
#define BUTTON_ACCESS_HAL_H

#include <stdbool.h>
#include "button_access.h"

bool button_access_hal_button_is_active(button_e btn);
bool button_access_hal_button_is_not_active(button_e btn);
bool button_access_hal_button_is_high(button_e btn);
bool button_access_hal_button_is_low(button_e btn);

#endif
