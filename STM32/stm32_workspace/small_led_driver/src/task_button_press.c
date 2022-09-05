// SRW

#include "cmsis_os.h"
#include "task_led_ctrl.h"
#include "task_button_press.h"

#define TASK_BUTTON_PRESS_ITERATION_TIME_MILLISECONDS  10
#define TASK_BUTTON_PRESS_STATE_TRANSITION_TIME_SEC 3000

bool g_animate_led_pause_flag = false;
bool g_animate_led_interrupt = false;
bool g_interrupt_flag[NUM_ISR] = {false};


void task_button_press_pause(void)
{
    static uint8_t flip_or_flop = 1;
    if (flip_or_flop) g_animate_led_pause_flag = true;
    else g_animate_led_pause_flag = false;
    flip_or_flop ^= 1;
}


isr_e task_button_press_button_to_isr(board_init_push_buttons_e button)
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
    g_animate_led_interrupt = true; // global indicator that interrupt occurred
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
    task_button_press_interrupt_flag_clear();
    if (task_led_ctrl_interrupt_flag(ISR_STATE))
    {
        return_val = true;
        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
        //osDelay(500); // some dormant time?
    }
    else if (task_button_press_interrupt_flag(ISR_PAUSE))
    {
        while (g_animate_led_pause_flag)
        {
            osDelay(10);
        }
    }
    else if (task_button_press_interrupt_flag(ISR_COLOR))
    {
        // interrupt modifies the current color... apply it to the animation!
        *red = task_led_ctrl_cur_color_red_hex();
        *green = task_led_ctrl_cur_color_green_hex();
        *blue = task_led_ctrl_cur_color_blue_hex();
    }
    return return_val;
}


void task_button_press_interrupt_flag_clear(void)
{
    g_animate_led_interrupt = false;
}


bool task_button_press_interrupt_occurred(void)
{
    return g_animate_led_interrupt;
}


void task_button_press(void *argument)
{
    while (1)
    {
        // TODO add a task block here waiting for execution!
        // This task will only be executed when a button press occurs
        // wait on flag to unblock..
        for (board_init_push_buttons_e button = 0; button < NUM_PUSH_BUTTONS; button = (board_init_push_buttons_e)(button + 1))
        {
            if(board_init_button_is_pressed(button))
            {
                // clear current button count
                board_init_button_on_count_clear(button);
                // wait for use to release the button
                while (board_init_button_is_pressed(button))
                {
                    board_init_button_on_count_increment(button);
                    osDelay(TASK_BUTTON_PRESS_ITERATION_TIME_MILLISECONDS);
                }
                // button is released here!
                if ((TASK_BUTTON_PRESS_STATE_TRANSITION_TIME_SEC / TASK_BUTTON_PRESS_ITERATION_TIME_MILLISECONDS) > board_init_button_on_count(button))
                {
                    board_init_button_on_count_clear(button);
                    switch (button)
                    {
                        case PUSH_BUTTON_A:
                            // perhaps go to a default speed here??
                            // future
                        break;

                        case PUSH_BUTTON_B:
                            // signal to the user that color state is changing
                            for (uint8_t iii = 0; iii < 3; iii++)
                            {
                                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_RED);
                                osDelay(100);
                                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
                                osDelay(100);
                            }
                            task_led_ctrl_reset_animate_iteration_count();
                            task_led_ctrl_enter_demo_state(); // enter demo state
                        break;

                        case PUSH_BUTTON_C:
                            // signal to the user that color state is changing
                            for (uint8_t iii = 0; iii < 3; iii++)
                            {
                                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLUE);
                                osDelay(100);
                                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
                                osDelay(100);
                            }
                            // don't change iteration count.  Simply go to color demo mode.
                            task_led_ctrl_enter_demo_state();
                        break;

                        case PUSH_BUTTON_D:
                            // future
                        break;

                        default:
                        break;
                    }
                }
                else
                {
                    // set ISR flag
                    task_led_ctrl_set_interrupt_flag(task_led_ctrl_button_to_isr(button));
                    switch (button)
                    {
                        case PUSH_BUTTON_A:
                            task_led_ctrl_adjust_speed();
                        break;
                        case PUSH_BUTTON_B:
                            // exit demo state if in it.
                            if (MASTER_LED_STATE_DEMO == task_led_ctrl_master_state())
                            {
                                task_led_ctrl_exit_demo_state(); // animation count is auto cleared here.
                            }
                            else
                            {
                                task_led_ctrl_reset_animate_iteration_count();
                                task_led_ctrl_adjust_state();
                            }
                        break;
                        case PUSH_BUTTON_C:
                            // exit demo state if in it.
                            if (MASTER_COLOR_STATE_DEMO == task_led_ctrl_cur_state())
                            {
                                task_led_ctrl_exit_demo_state();
                            }
                            else
                            {
                                task_led_ctrl_adjust_color();
                            }
                        break;
                        case PUSH_BUTTON_D:
                            task_led_ctrl_pause();
                        break;
                        default:
                        break;
                    }

                }

            }
        }
    }

}
