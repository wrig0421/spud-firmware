/*
 * Based on ssd1306-stm32HAL by Olivier Van den Eede(4ilo)
 */

#if !defined(BOARD_INIT_H)

#define BOARD_INIT_H


void board_wakeup(void);
void port_wakeup(void);
void board_init(void);
void board_init_set_wkup_src(void);
void board_init_activate_garage_door(void);
void board_init_deactivate_garage_door(void);

#endif

