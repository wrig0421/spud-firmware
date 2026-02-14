// SRW

#include "config.h"
#if !defined(BOARD_SPUDGLO_V6_BUTTON_CONFIG_H) && defined(BOARD_SPUDGLO_V6P0)
#define BOARD_SPUDGLO_V6_BUTTON_CONFIG_H

IRQn_Type button_config_button_to_irq(button_e btn);
button_e button_config_irq_to_button(IRQn_Type  irqn);
uint16_t button_config_button_pin(button_e btn);

#endif
