#if !defined(BOARD_INIT_H)
#include <stdbool.h>

#define BOARD_INIT_H

typedef enum
{
    PUSH_BUTTON_A = 0,
    PUSH_BUTTON_B,
    PUSH_BUTTON_C,
    PUSH_BUTTON_D,
    NUM_PUSH_BUTTONS
} board_init_push_buttons_e;;

void board_init(void);

void board_init_stop_timer(void);
bool board_init_any_button_is_pressed(void);
bool board_init_button_is_pressed(board_init_push_buttons_e button);
void board_init_button_on_count_increment(board_init_push_buttons_e button);
uint32_t board_init_button_on_count(board_init_push_buttons_e button);
void board_init_button_on_count_clear(board_init_push_buttons_e button);

#endif
