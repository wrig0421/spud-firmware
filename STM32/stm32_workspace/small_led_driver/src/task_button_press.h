// SRW

#ifndef TASK_BUTTON_PRESS_H
#define TASK_BUTTON_PRESS_H


#include "board_init_common.h"
// typedefs, structs, enums
typedef enum
{
    ISR_SPEED = 0,
    ISR_STATE,
    ISR_COLOR,
    ISR_PAUSE,
    NUM_ISR
} isr_e;

void task_button_press_pause(void);
isr_e task_button_press_button_to_isr(board_init_push_buttons_e button);
void task_button_press_set_interrupt_flag(isr_e src);
bool task_button_press_interrupt_flag(isr_e src);
bool task_button_press_pause_flag_is_set(void);

void task_button_press_set_interrupt_flag(isr_e src);
bool task_button_press_check_interrupts(uint8_t *red, uint8_t *green, uint8_t *blue);
void task_button_press_interrupt_flag_clear(void);
bool task_button_press_interrupt_occurred(void);
isr_e task_led_ctrl_button_to_isr(board_init_push_buttons_e button);
void task_button_press(void *argument);

#endif /* TASK_PIN_LEVEL_COUNT_H_ */
