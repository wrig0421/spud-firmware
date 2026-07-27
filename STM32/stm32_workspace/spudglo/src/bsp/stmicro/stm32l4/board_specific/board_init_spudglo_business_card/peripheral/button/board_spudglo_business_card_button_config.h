// SRW

#include "config.h"
#if !defined(BOARD_SPUDGLO_BUSINESS_CARD_BUTTON_CONFIG_H) && defined(BOARD_SPUDGLO_BUSINESS_CARD)
#define BOARD_SPUDGLO_BUSINESS_CARD_BUTTON_CONFIG_H

IRQn_Type button_config_button_to_irq(button_e btn);
button_e button_config_irq_to_button(IRQn_Type  irqn);
uint16_t button_config_button_pin(button_e btn);

#endif
