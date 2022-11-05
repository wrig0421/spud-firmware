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

extern uint32_t g_a_interrupt_current_timestamp;
extern uint32_t g_a_interrupt_previous_timestamp;

extern uint32_t g_b_interrupt_current_timestamp;
extern uint32_t g_b_interrupt_previous_timestamp;

extern uint32_t g_c_interrupt_current_timestamp;
extern uint32_t g_c_interrupt_previous_timestamp;

extern uint32_t g_d_interrupt_current_timestamp;
extern uint32_t g_d_interrupt_previous_timestamp;

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


isr_e task_led_ctrl_button_to_isr(board_init_push_buttons_e button)
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


void task_button_press_ctrl_set_interrupt_flag(isr_e src)
{
    g_animate_led_interrupt = true;
    g_interrupt_flag[src] = true;
}


bool task_button_press_ctrl_interrupt_flag(isr_e src)
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
    bool button_was_pressed = false;
    uint8_t a_press_count = 0;
    uint8_t b_press_count = 0;
    uint8_t c_press_count = 0;
    uint8_t d_press_count = 0;
    while (1)
    {
        button_was_pressed = false;
        xTaskNotifyWait(0, button_pressed_bit, &button_pressed_bit, portMAX_DELAY);

        switch ((board_init_push_buttons_e) button_pressed_bit)
        {
            case PUSH_BUTTON_A:
                if ((g_a_interrupt_current_timestamp - g_a_interrupt_previous_timestamp) > SWITCH_DEBOUNCE_TIME_MILLISECONDS)
                {
                    button_was_pressed = true;
                    button_press_history[PUSH_BUTTON_A][a_press_count++] = g_a_interrupt_current_timestamp;
                    if ((g_a_interrupt_current_timestamp - g_a_interrupt_previous_timestamp) < SWITCH_FAST_PRESS_TIME_MILLISECONDS) fast_press_count++;
                    else fast_press_count = 0;
                    if (a_press_count >= SWITCH_HISTORY_DEPTH) a_press_count = 0;
                    task_button_press_ctrl_set_interrupt_flag(task_led_ctrl_button_to_isr(PUSH_BUTTON_A));
                }
                else
                {
                    button_was_pressed = false;
                }
            break;
            case PUSH_BUTTON_B:
                if ((g_b_interrupt_current_timestamp - g_b_interrupt_previous_timestamp) > SWITCH_DEBOUNCE_TIME_MILLISECONDS)
                {
                    button_was_pressed = true;
                    button_press_history[PUSH_BUTTON_B][b_press_count++] = g_b_interrupt_current_timestamp;
                    if ((g_b_interrupt_current_timestamp - g_b_interrupt_previous_timestamp) < SWITCH_FAST_PRESS_TIME_MILLISECONDS) fast_press_count++;
                    else fast_press_count = 0;
                    if (b_press_count >= SWITCH_HISTORY_DEPTH) b_press_count = 0;
                    task_button_press_ctrl_set_interrupt_flag(task_led_ctrl_button_to_isr(PUSH_BUTTON_B));
                }
                else
                {
                    button_was_pressed = false;
                }
            break;
            case PUSH_BUTTON_C:
                if ((g_c_interrupt_current_timestamp - g_c_interrupt_previous_timestamp) > SWITCH_DEBOUNCE_TIME_MILLISECONDS)
                {
                    button_was_pressed = true;
                    button_press_history[PUSH_BUTTON_C][c_press_count++] = g_c_interrupt_current_timestamp;
                    if ((g_c_interrupt_current_timestamp - g_c_interrupt_previous_timestamp) < SWITCH_FAST_PRESS_TIME_MILLISECONDS) fast_press_count++;
                    else fast_press_count = 0;
                    if (c_press_count >= SWITCH_HISTORY_DEPTH) c_press_count = 0;
                    task_button_press_ctrl_set_interrupt_flag(task_led_ctrl_button_to_isr(PUSH_BUTTON_C));
                }
                else
                {
                    button_was_pressed = false;
                }
            break;
            case PUSH_BUTTON_D:
                if ((g_d_interrupt_current_timestamp - g_d_interrupt_previous_timestamp) > SWITCH_DEBOUNCE_TIME_MILLISECONDS)
                {
                    button_was_pressed = true;
                    button_press_history[PUSH_BUTTON_D][d_press_count++] = g_d_interrupt_current_timestamp;
                    if ((g_d_interrupt_current_timestamp - g_d_interrupt_previous_timestamp) < SWITCH_FAST_PRESS_TIME_MILLISECONDS) fast_press_count++;
                    else fast_press_count = 0;
                    if (d_press_count >= SWITCH_HISTORY_DEPTH) d_press_count = 0;
                    task_button_press_ctrl_set_interrupt_flag(task_led_ctrl_button_to_isr(PUSH_BUTTON_D));
                }
                else
                {
                    button_was_pressed = false;
                }
            break;
            default:
            break;
        }
        // check if
        if (fast_press_count >= (SWITCH_HISTORY_DEPTH - 1))
        {
            task_button_press_major_change = true;
            switch ((board_init_push_buttons_e) button_pressed_bit)
            {
                case PUSH_BUTTON_A:
                    for (uint8_t iii = 0; iii < 3; iii++)
                    {
                        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_GREEN);
                        osDelay(500);
                        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
                        osDelay(500);
                    }
                    task_led_ctrl_speed_reset();
                    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 24, 0);
                    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
                break;

                case PUSH_BUTTON_B:
                    // signal to the user that color state is changing
                    for (uint8_t iii = 0; iii < 3; iii++)
                    {
                        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_RED);
                        osDelay(500);
                        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
                        osDelay(500);
                    }
                    task_led_ctrl_animate_iteration_reset();
                    task_led_ctrl_animate_state_demo(); // enter demo state
                    HAL_NVIC_SetPriority(EXTI0_IRQn, 24, 0);
                    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
                break;

                case PUSH_BUTTON_C:
                    // signal to the user that color state is changing
                    task_led_ctrl_pause();
                    for (uint8_t iii = 0; iii < 3; iii++)
                    {
                        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLUE);
                        osDelay(500);
                        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
                        osDelay(500);
                    }
                    // don't change iteration count.  Simply go to color demo mode.
                    task_led_ctrl_color_state_demo();
                    HAL_NVIC_SetPriority(EXTI2_IRQn, 24, 0);
                    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
                break;

                case PUSH_BUTTON_D:
                    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 24, 0);
                    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
                    // future
                break;

                default:
                break;
            }
            task_button_press_major_change = false;
        }
        else if (button_was_pressed)
        {
            // set ISR flag
            task_button_press_ctrl_set_interrupt_flag(task_led_ctrl_button_to_isr((board_init_push_buttons_e) button_pressed_bit));
            switch ((board_init_push_buttons_e) button_pressed_bit)
            {
                case PUSH_BUTTON_A:
                    task_led_ctrl_speed_adjust();
                    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 24, 0);
                    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
                break;
                case PUSH_BUTTON_B:
                    // exit demo state if in it.
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
                    // exit demo state if in it.
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
