// SRW

#ifndef TASK_BUTTON_PRESS_H
#define TASK_BUTTON_PRESS_H

#include "board_specific.h"

// typedefs, structs, enums
typedef enum
{
    ISR_SPEED = 0,
    ISR_STATE,
    ISR_COLOR,
    ISR_PAUSE,
    NUM_ISR
} isr_e;


typedef enum
{
    TIMESTAMP_CURRENT,
    TIMESTAMP_PREVIOUS,
    NUM_TIMESTAMPS
} timestamp_e;

bool task_button_press_interrupt_major_change(void);
bool task_button_press_interrupt_occurred(void);
isr_e task_led_ctrl_button_to_isr(const board_init_push_buttons_e button);
void task_button_press_ctrl_set_interrupt_flag(const isr_e src);
bool task_button_press_ctrl_interrupt_flag(const isr_e src);
bool task_button_press_check_interrupts(uint8_t *red, uint8_t *green, uint8_t *blue);
void task_button_press_interrupt_flag_clear(void);
void task_button_press(void *argument);
bool task_button_press_isr_hit(void);

#endif /* TASK_PIN_LEVEL_COUNT_H_ */
