// SRW

#if !defined(TASK_BUTTON_PRESS_H)
#define TASK_BUTTON_PRESS_H

#include "button_access.h"
#include "board_specific.h"
#include "ws2812b.h"

// typedefs, structs, enums



typedef enum
{
    TIMESTAMP_CURRENT,
    TIMESTAMP_PREVIOUS,
    NUM_TIMESTAMPS
} timestamp_e;

//bool task_button_press_interrupt_occurred(void);
bool task_button_press_interrupt_occurred(const strip_mask_t mask);
bool task_button_press_major_interupt_occurred(void);
bool task_button_press_minor_interupt_occurred(void);
button_isr_e task_led_ctrl_button_to_isr(const button_e btn);
bool task_button_press_check_interrupts(const strip_mask_t mask);
void task_button_press(void *argument);

#endif /* TASK_PIN_LEVEL_COUNT_H_ */
