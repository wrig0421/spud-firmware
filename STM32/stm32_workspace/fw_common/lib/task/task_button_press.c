// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

#include "board_init_common.h"
#include "board_specific.h"
#include "cmsis_os.h"
#include "task_led_ctrl.h"
#include "task_button_press.h"

#define TASK_BUTTON_PRESS_ITERATION_TIME_MILLISECONDS   10
#define TASK_BUTTON_PRESS_STATE_TRANSITION_TIME_MILLISECONDS     3000
#define SWITCH_DEBOUNCE_TIME_MILLISECONDS   200
#define SWITCH_HISTORY_DEPTH                5
#define SWITCH_FAST_PRESS_TIME_MILLISECONDS 2000

uint32_t g_button_press_timestamp[NUM_PUSH_BUTTONS][NUM_TIMESTAMPS];

uint32_t    button_press_history[NUM_PUSH_BUTTONS][SWITCH_HISTORY_DEPTH] = {0};
uint32_t    g_button_pressed_task = 0;
uint8_t     fast_press_count = 0;
bool        task_button_press_major_change = false;


bool        g_animate_led_pause_flag = false;
bool        g_animate_led_interrupt = false;
bool        g_interrupt_flag[NUM_ISR] = {false};

bool task_button_press_interrupt_occurred(void)
{
    return g_animate_led_interrupt;
}


isr_e task_led_ctrl_button_to_isr(const board_init_push_buttons_e button)
{
    isr_e return_val;
    switch (button)
    {
        case PUSH_BUTTON_A:
            return_val = ISR_SPEED;
        break;
        case PUSH_BUTTON_B:
            return_val = ISR_STATE;
        break;
        case PUSH_BUTTON_C:
            return_val = ISR_COLOR;
        break;
        case PUSH_BUTTON_D:
            return_val = ISR_PAUSE;
        break;
        default: // do nothing!
        break;
    }
    return return_val;
}


void task_button_press_ctrl_set_interrupt_flag(const isr_e src)
{
    g_animate_led_interrupt = true;
    g_interrupt_flag[src] = true;
}


bool task_button_press_ctrl_interrupt_flag(const isr_e src)
{
    bool return_val = g_interrupt_flag[src];
    if (return_val) g_interrupt_flag[src] = false; // auto clear
    return return_val;
}


bool task_button_press_check_interrupts(uint8_t *red, uint8_t *green, uint8_t *blue)
{
    bool return_val = false;
    if (task_button_press_ctrl_interrupt_flag(ISR_STATE))
    {
        task_button_press_interrupt_flag_clear();
        return_val = true;
        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
    }
    else if (task_button_press_ctrl_interrupt_flag(ISR_PAUSE))
    {
        task_button_press_interrupt_flag_clear();
        while (g_animate_led_pause_flag)
        {
            osDelay(10);
        }
    }
    else if (task_button_press_ctrl_interrupt_flag(ISR_COLOR))
    {
        task_button_press_interrupt_flag_clear();
        // interrupt modifies the current color... apply it to the animation!
        *red = task_led_ctrl_color_red_hex();
        *green = task_led_ctrl_color_green_hex();
        *blue = task_led_ctrl_color_blue_hex();
    }
    return return_val;
}


void task_button_press_interrupt_flag_clear(void)
{
    g_animate_led_interrupt = false;
}


void task_button_press(void *argument)
{
    uint32_t button_pressed_bit = 0;
    uint32_t timestamp_diff = 0;
    color_hex_code_e color = COLOR_HEX_BLACK;
    IRQn_Type irq_type = 0;
    while (1)
    {
        xTaskNotifyWait(0, button_pressed_bit, &button_pressed_bit, portMAX_DELAY);

        timestamp_diff = g_button_press_timestamp[(board_init_push_buttons_e) button_pressed_bit][TIMESTAMP_CURRENT] - g_button_press_timestamp[PUSH_BUTTON_A][TIMESTAMP_PREVIOUS];
        if (timestamp_diff > SWITCH_DEBOUNCE_TIME_MILLISECONDS)
        {
            if (timestamp_diff < SWITCH_FAST_PRESS_TIME_MILLISECONDS) fast_press_count++;
            else fast_press_count = 0;
            task_button_press_ctrl_set_interrupt_flag(task_led_ctrl_button_to_isr((board_init_push_buttons_e) button_pressed_bit));
        }
        if (fast_press_count >= (SWITCH_HISTORY_DEPTH - 1))
        {
            task_button_press_major_change = true;
            switch ((board_init_push_buttons_e) button_pressed_bit)
            {
                case PUSH_BUTTON_A:
                    color = COLOR_HEX_GREEN;
                    irq_type = EXTI9_5_IRQn;
                    task_led_ctrl_speed_reset();
                break;
                case PUSH_BUTTON_B:
                    color = COLOR_HEX_RED;
                    irq_type = EXTI0_IRQn;
                    task_led_ctrl_animate_iteration_reset();
                    task_led_ctrl_animate_state_demo(); // enter demo state
                break;
                case PUSH_BUTTON_C:
                    color = COLOR_HEX_BLUE;
                    irq_type = EXTI2_IRQn;
                    // don't change iteration count.  Simply go to color demo mode.
                    task_led_ctrl_color_state_demo();
                break;
                case PUSH_BUTTON_D:
                    color = COLOR_HEX_BLACK;
                    irq_type = EXTI15_10_IRQn;

                break;
                default:
                break;
            }
            for (uint8_t iii = 0; iii < 3; iii++)
            {
                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, color);
                osDelay(500);
                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
                osDelay(500);
            }
            HAL_NVIC_SetPriority(irq_type, 24, 0);
            HAL_NVIC_EnableIRQ(irq_type);
            task_button_press_major_change = false;
        }
        else
        {
            // no state change here
            task_button_press_ctrl_set_interrupt_flag(task_led_ctrl_button_to_isr((board_init_push_buttons_e) button_pressed_bit));
            switch ((board_init_push_buttons_e) button_pressed_bit)
            {
                case PUSH_BUTTON_A:
                    task_led_ctrl_speed_adjust();
                    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 24, 0);
                    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
                break;
                case PUSH_BUTTON_B:
                    if (MASTER_LED_STATE_DEMO == task_led_ctrl_animate_state())
                    {
                        task_led_ctrl_animate_state_fixed(); // animation count is auto cleared here.
                    }
                    else
                    {
                        task_led_ctrl_animate_iteration_reset();
                        task_led_ctrl_animate_adjust_state();
                    }
                    HAL_NVIC_SetPriority(EXTI0_IRQn, 24, 0);
                    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
                break;
                case PUSH_BUTTON_C:
                    if (MASTER_COLOR_STATE_DEMO == task_led_ctrl_color_state())
                    {
                        task_led_ctrl_color_state_fixed();
                    }
                    else
                    {
                        task_led_ctrl_color_adjust();
                    }
                    HAL_NVIC_SetPriority(EXTI2_IRQn, 24, 0);
                    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
                break;
                case PUSH_BUTTON_D:
                    task_led_ctrl_pause();
                    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 24, 0);
                    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
                break;
                default:
                break;
            }
        }
    }
}
