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
#include "ws2812b.h"

#define SWITCH_HISTORY_DEPTH                5
#define SWITCH_FAST_PRESS_TIME_MILLISECONDS 1000

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
    if (task_button_press_major_state_change())
    {
        task_button_press_interrupt_flag_clear();
        return_val = true;
        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
    }
    else if (task_button_press_ctrl_interrupt_flag(ISR_STATE))
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
uint32_t a_ok_count = 0;
uint32_t b_ok_count = 0;
uint32_t c_ok_count = 0;
uint32_t d_ok_count = 0;


bool task_button_press_major_state_change(void)
{
    return task_button_press_major_change;
}


task_button_press_major_state_change_clear(void)
{
    task_button_press_major_change = false;
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
#if !defined(BOARD_SPUDGLO_V5)
        HAL_GPIO_WritePin(PIN_PORT_B, PIN_INT_LVL_EN, GPIO_PIN_RESET);
        osDelay(700);
        HAL_GPIO_WritePin(PIN_PORT_B, PIN_INT_LVL_EN, GPIO_PIN_SET);
#endif
        timestamp_diff = g_button_press_timestamp[(board_init_push_buttons_e) button_pressed_bit][TIMESTAMP_CURRENT] - \
                        g_button_press_timestamp[(board_init_push_buttons_e)button_pressed_bit][TIMESTAMP_PREVIOUS];
        if (timestamp_diff < SWITCH_FAST_PRESS_TIME_MILLISECONDS) fast_press_count++;
        else fast_press_count = 0;
        task_button_press_ctrl_set_interrupt_flag(task_led_ctrl_button_to_isr((board_init_push_buttons_e) button_pressed_bit));
        if (fast_press_count >= (SWITCH_HISTORY_DEPTH-1))
        {
            task_button_press_major_change = true;
            fast_press_count = 0;
            switch ((board_init_push_buttons_e) button_pressed_bit)
            {
                case PUSH_BUTTON_A:
                    a_ok_count++;
                    color = COLOR_HEX_GREEN;
                    irq_type = PUSH_BUTTON_A_IRQ;
                    task_led_ctrl_speed_reset();

                break;
                case PUSH_BUTTON_B:
                    b_ok_count++;
                    color = COLOR_HEX_BLUE;
                    irq_type = PUSH_BUTTON_B_IRQ;
                    task_led_ctrl_animate_iteration_reset();
                    task_led_ctrl_animate_state_demo(); // enter demo state
                break;
                case PUSH_BUTTON_C:
                    c_ok_count++;
                    color = COLOR_HEX_RED;
                    irq_type = PUSH_BUTTON_C_IRQ;
                    // don't change iteration count.  Simply go to color demo mode.
                    task_led_ctrl_color_state_demo();
                break;
                case PUSH_BUTTON_D:
                    task_led_ctrl_brightness_adjust();
                    task_led_ctrl_clear_pause();
                    d_ok_count++;
                    color = COLOR_HEX_WHITE;
                    irq_type = PUSH_BUTTON_D_IRQ;
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
                    a_ok_count++;
                    task_led_ctrl_speed_adjust();
                    HAL_NVIC_SetPriority(PUSH_BUTTON_A_IRQ, 24, 0);
                    HAL_NVIC_EnableIRQ(PUSH_BUTTON_A_IRQ);
                break;
                case PUSH_BUTTON_B:
                    b_ok_count++;
                    if (MASTER_LED_STATE_DEMO == task_led_ctrl_animate_state())
                    {
                        task_led_ctrl_animate_state_fixed(); // animation count is auto cleared here.
                    }
                    else
                    {
                        task_led_ctrl_animate_iteration_reset();
                        task_led_ctrl_animate_adjust_state();
                    }
                    HAL_NVIC_SetPriority(PUSH_BUTTON_B_IRQ, 24, 0);
                    HAL_NVIC_EnableIRQ(PUSH_BUTTON_B_IRQ);
                break;
                case PUSH_BUTTON_C:
                    c_ok_count++;
                    if (MASTER_COLOR_STATE_DEMO == task_led_ctrl_color_state())
                    {
                        task_led_ctrl_color_state_fixed();
                    }
                    else
                    {
                        task_led_ctrl_color_adjust();
                    }
                    HAL_NVIC_SetPriority(PUSH_BUTTON_C_IRQ, 24, 0);
                    HAL_NVIC_EnableIRQ(PUSH_BUTTON_C_IRQ);

                break;
                case PUSH_BUTTON_D:
                    d_ok_count++;
                    task_led_ctrl_pause();
                    HAL_NVIC_SetPriority(PUSH_BUTTON_D_IRQ, 24, 0);
                    HAL_NVIC_EnableIRQ(PUSH_BUTTON_D_IRQ);
                break;
                default:
                break;
            }
        }
    }
}
