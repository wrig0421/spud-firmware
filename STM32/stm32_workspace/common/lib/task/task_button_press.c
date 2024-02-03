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
#include "gpio_config_hal_specific.h"
#include "gpio_access_hal.h"
#include "ws2812b.h"

#define 	SWITCH_HISTORY_DEPTH                		5
#define 	SWITCH_FAST_PRESS_TIME_MILLISECONDS 		1000
#define 	SWITCH_MAJOR_STATE_CHANGE_TIME_MILLISECONDS	5000
uint32_t 	g_button_press_timestamp[NUM_PUSH_BUTTONS][NUM_TIMESTAMPS];
bool 		task_button_press_major_change        = false;

extern task_led_ctrl_t g_task_led_ctrl;

bool        g_interrupt_flag[NUM_ISR] = {false};
// for debug the variables below are defined
uint32_t 	g_a_ok_count = 0;
uint32_t 	g_b_ok_count = 0;
uint32_t 	g_c_ok_count = 0;
uint32_t 	g_d_ok_count = 0;


bool task_button_press_interrupt_occurred(void)
{
    return g_task_led_ctrl.interrupt_set;
}


/**
 * @brief   Return the ISR pertaining to the button
 * @param   button: the button of interest
 * @return  isr_e: enumerated type for the interrupt pertaining to the button
 */
isr_e task_led_ctrl_button_to_isr(const board_init_push_buttons_e button)
{
    switch (button)
    {
        case PUSH_BUTTON_A: return ISR_SPEED;
        case PUSH_BUTTON_B: return ISR_STATE;
        case PUSH_BUTTON_C: return ISR_COLOR;
        case PUSH_BUTTON_D: return ISR_PAUSE;
        default: return ISR_INVALID;
    }
}


/**
 * @brief   Set global flag denoting that src interrupt has occurred
 * @param   src: source of interrupt
 * @return  void
 */
void task_button_press_ctrl_set_interrupt_flag(const isr_e src)
{
    g_task_led_ctrl.interrupt_set = true;
    g_interrupt_flag[src] = true;
}


/**
 * @brief   Check if interrupt occured due to source
 * @param   src: source of interrupt to check
 * @return  bool: true if occurred else false
 * @note	This function auto clears the flag.  If set it will
 *  		return true and clear the tracked flag.
 */
bool task_button_press_ctrl_interrupt_flag(const isr_e src)
{
    bool return_val = g_interrupt_flag[src];
    if (return_val) g_interrupt_flag[src] = false; // auto clear
    return return_val;
}


/**
 * @brief   Check for interrupts initiated via button press
 * @param   *red: pointer to current animation red color (8 bit)
 * @param   *green: pointer to current animation green color (8 bit)
 * @param  	*blue: pointer to current animation blue color (8 bit)
 * @return  bool: true if interrupt occurred since last check, else false
 */
bool task_button_press_check_interrupts(uint8_t *red, uint8_t *green, uint8_t *blue)
{
    bool return_val = false;
    if (task_button_press_major_state_change())
    {
        task_button_press_interrupt_flag_clear();
        return_val = true;
        animate_led_solid_custom_color((uint16_t)STRIP_ALL_SET, COLOR_HEX_BLACK);
    }
    else if (task_button_press_ctrl_interrupt_flag(ISR_STATE))
    {
        task_button_press_interrupt_flag_clear();
        return_val = true;
        animate_led_solid_custom_color((uint16_t)STRIP_ALL_SET, COLOR_HEX_BLACK);
    }
    else if (task_button_press_ctrl_interrupt_flag(ISR_PAUSE))
    {
        task_button_press_interrupt_flag_clear();
        while (g_task_led_ctrl.pause_set)
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


/**
 * @brief  	Clear global flag indicating that an interrupt occurred.
 * @param   void
 * @return  void
 */
void task_button_press_interrupt_flag_clear(void)
{
    g_task_led_ctrl.interrupt_set = false;
}


/**
 * @brief  	Check if a major state change was intiated
 * @param   void
 * @return  bool: true if major state change, else false
 */
bool task_button_press_major_state_change(void)
{
    return task_button_press_major_change;
}



bool g_major_state_change = false;


/**
 * @brief   Task to control all button press action
 * @param   *arguments: UNUSED!!
 * @return  void
 */
void task_button_press(void *argument)
{
	gpio_specific_pin_e button_pin;
    uint32_t button_pressed_bit = 0;
    color_hex_code_e color = COLOR_HEX_BLACK;
    IRQn_Type irq_type = 0;
    board_init_push_buttons_e pushed_button = NUM_PUSH_BUTTONS;
    while (1)
    {
    	// wait for task notification from button interrupt.
        xTaskNotifyWait(0, button_pressed_bit, &button_pressed_bit, portMAX_DELAY);
        // button_pressed_bit is passed through notification.  Convert to the button pressed enum.
        pushed_button = (board_init_push_buttons_e) button_pressed_bit;
#if !defined(BOARD_SPUDGLO_V5)
        HAL_GPIO_WritePin(gpio_config_port_lookup(GPIO_PIOB_INT_LVL_EN), gpio_config_pin_lookup(GPIO_PIOB_INT_LVL_EN), GPIO_PIN_RESET);
        osDelay(700);
        HAL_GPIO_WritePin(gpio_config_port_lookup(GPIO_PIOB_INT_LVL_EN), gpio_config_pin_lookup(GPIO_PIOB_INT_LVL_EN), GPIO_PIN_SET);
#endif
        // get the pin for button pressed
        switch (pushed_button)
        {
        	case PUSH_BUTTON_A: button_pin = GPIO_PIN_PUSH_BUTTON_A; break;
        	case PUSH_BUTTON_B: button_pin = GPIO_PIN_PUSH_BUTTON_B; break;
        	case PUSH_BUTTON_C: button_pin = GPIO_PIN_PUSH_BUTTON_C; break;
			case PUSH_BUTTON_D: button_pin = GPIO_PIN_PUSH_BUTTON_D; break;
			default: break;
        }
        // wait for push button to be released
		while (gpio_access_hal_input_is_low(button_pin))
		{
			// record the current timestamp every 100 ms while waiting for this bitch to go high
    		g_button_press_timestamp[pushed_button][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    		osDelay(100);
		}
        // set flag to signal that a button interrupt was received!
        task_button_press_ctrl_set_interrupt_flag(task_led_ctrl_button_to_isr(pushed_button));
        // check if the button was held down longer than SWITCH_MAJOR_STATE_CHANGE_TIME_MILLISECONDS
        if (SWITCH_MAJOR_STATE_CHANGE_TIME_MILLISECONDS < \
        		(g_button_press_timestamp[(board_init_push_buttons_e) button_pressed_bit][TIMESTAMP_CURRENT] - \
        				g_button_press_timestamp[pushed_button][TIMESTAMP_PREVIOUS]))
        {
        	// major state change initiated. Special action occurs below.
            task_button_press_major_change = true;
            switch (pushed_button)
            {
                case PUSH_BUTTON_A:
                	// `A` button is speed.  Reset the speed to the default value.
                    g_a_ok_count++;
                    color = COLOR_HEX_GREEN;
                    irq_type = PUSH_BUTTON_A_IRQ;
                    task_led_ctrl_speed_reset();
                break;
                case PUSH_BUTTON_B:
                	// `B` button is animation.  Reset the iteration count and also reset the master state to demo!
                    g_b_ok_count++;
                    color = COLOR_HEX_BLUE;
                    irq_type = PUSH_BUTTON_B_IRQ;
                    task_led_ctrl_animate_iteration_reset();
                    task_led_ctrl_animate_state_demo(); // enter demo state
                break;
                case PUSH_BUTTON_C:
                	// `C` button is color.  Reset the color master state back to demo mode.
                    g_c_ok_count++;
                    color = COLOR_HEX_RED;
                    irq_type = PUSH_BUTTON_C_IRQ;
                    // don't change iteration count.  Simply go to color demo mode.
                    task_led_ctrl_color_state_demo();
                break;
                case PUSH_BUTTON_D:
                	// `D` button is brightness.  Adjust the brightness and also clear pause if for some reason we are paused.
                    task_led_ctrl_brightness_adjust();
                    task_led_ctrl_clear_pause();
                    g_d_ok_count++;
                    color = COLOR_HEX_WHITE;
                    irq_type = PUSH_BUTTON_D_IRQ;
                break;
                default:
                break;
            }
            for (uint8_t iii = 0; iii < 3; iii++)
            {
            	// flash the LEDs on the sign signalling that a master state change was made!
                animate_led_solid_custom_color((uint16_t)STRIP_ALL_SET, color);
                osDelay(500);
                animate_led_solid_custom_color((uint16_t)STRIP_ALL_SET, COLOR_HEX_BLACK);
                osDelay(500);
            }
            HAL_NVIC_SetPriority(irq_type, 24, 0);
            HAL_NVIC_EnableIRQ(irq_type);
            task_button_press_major_change = false;
        }
        else
        {
        	// simple button press.  No master state change here!
            switch (pushed_button)
            {
                case PUSH_BUTTON_A:
                	// A is speed.  Adjust it!
                    g_a_ok_count++;
                    task_led_ctrl_speed_adjust();
                    HAL_NVIC_SetPriority(PUSH_BUTTON_A_IRQ, 24, 0);
                    HAL_NVIC_EnableIRQ(PUSH_BUTTON_A_IRQ);
                break;
                case PUSH_BUTTON_B:
                	// B is state.  Adjust it!
                    g_b_ok_count++;
                    if (MASTER_LED_STATE_DEMO == task_led_ctrl_animate_state())
                    {
                    	// if master state is demo then change to fixed master state!
                        task_led_ctrl_animate_state_fixed(); // animation count is auto cleared here.
                    }
                    else
                    {
                    	// reset animation state count and adjust the state
                        task_led_ctrl_animate_iteration_reset();
                        task_led_ctrl_animate_adjust_state();
                    }
                    HAL_NVIC_SetPriority(PUSH_BUTTON_B_IRQ, 24, 0);
                    HAL_NVIC_EnableIRQ(PUSH_BUTTON_B_IRQ);
                break;
                case PUSH_BUTTON_C:
                	// C is color.  Adjust it!
                    g_c_ok_count++;
                    if (MASTER_COLOR_STATE_DEMO == task_led_ctrl_color_state())
                    {
                    	// if master color state is demo then change to fixed master state!
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
                	// D is pause.
                    g_d_ok_count++;
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
