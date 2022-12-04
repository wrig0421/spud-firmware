// SRW

#if !defined(BOARD_INIT_COMMON_H)
#define BOARD_INIT_COMMON_H

#include <stdint.h>
#include <stdbool.h>


typedef enum
{
    PUSH_BUTTON_A = 0,
    PUSH_BUTTON_B,
    PUSH_BUTTON_C,
    PUSH_BUTTON_D,
    NUM_PUSH_BUTTONS,
} board_init_push_buttons_e;

void board_init_common_board_init(void);
void board_init_common_button_pressed(const board_init_push_buttons_e button);
void board_init_common_stop_timer(void);

void board_init_red_led_on(void);
void board_init_red_led_off(void);
void board_init_green_led_on(void);
void board_init_green_led_off(void);

#endif
