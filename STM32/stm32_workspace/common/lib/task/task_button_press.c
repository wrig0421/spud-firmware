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
#include "led_ctrl.h"
#include "task_notify.h"
#include "led_animate.h"
#include "led_ctrl_speed.h"
#include "led_ctrl_pause.h"

#define 	SWITCH_HISTORY_DEPTH                		5
#define 	SWITCH_FAST_PRESS_TIME_MILLISECONDS 		1000
#define 	SWITCH_MAJOR_STATE_CHANGE_TIME_MILLISECONDS	5000
uint32_t 	g_button_press_timestamp[NUM_PUSH_BUTTONS][NUM_TIMESTAMPS];
bool 		g_task_button_press_major_change        = false;

extern led_ctrl_t g_task_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];

bool g_interrupt_flag = false;

// for debug the variables below are defined
uint32_t 	g_a_ok_count = 0;
uint32_t 	g_b_ok_count = 0;
uint32_t 	g_c_ok_count = 0;
uint32_t 	g_d_ok_count = 0;


bool task_button_press_interrupt_occurred(void)
{
    return g_interrupt_flag;
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
void task_button_press_ctrl_set_interrupt_flag(const strip_mask_t mask, const isr_e isr_src)
{
	g_interrupt_flag = true;
	strip_num_e strip_num = strip_bit_to_strip_num(mask);
	switch (isr_src)
	{
		case ISR_SPEED:
			g_task_led_ctrl[strip_num].led_interrupt_info.speed = true;
		break;
		case ISR_STATE:
			g_task_led_ctrl[strip_num].led_interrupt_info.state = true;
		break;
		case ISR_COLOR:
			g_task_led_ctrl[strip_num].led_interrupt_info.color = true;
		break;
		case ISR_PAUSE:
			g_task_led_ctrl[strip_num].led_interrupt_info.pause = true;
		break;
		default:
		break;
	}
}


/**
 * @brief   Check if interrupt occured due to source
 * @param   src: source of interrupt to check
 * @return  bool: true if occurred else false
 * @note	This function auto clears the flag.  If set it will
 *  		return true and clear the tracked flag.
 */
bool task_button_press_ctrl_interrupt_flag(const strip_mask_t mask, const isr_e isr_src)
{
	bool return_val = false;
	strip_num_e strip_num = strip_bit_to_strip_num(mask);
	switch (isr_src)
	{
		case ISR_SPEED:
			if (g_task_led_ctrl[strip_num].led_interrupt_info.speed)
			{
				g_task_led_ctrl[strip_num].led_interrupt_info.speed = false;
				return_val = true;
			}
		break;
		case ISR_STATE:
			if (g_task_led_ctrl[strip_num].led_interrupt_info.state)
			{
				g_task_led_ctrl[strip_num].led_interrupt_info.state = false;
				return_val = true;
			}
		break;
		case ISR_COLOR:
			if (g_task_led_ctrl[strip_num].led_interrupt_info.color)
			{
				g_task_led_ctrl[strip_num].led_interrupt_info.color = false;
				return_val = true;
			}
		break;
		case ISR_PAUSE:
			if (g_task_led_ctrl[strip_num].led_interrupt_info.pause)
			{
				g_task_led_ctrl[strip_num].led_interrupt_info.pause = false;
				return_val = true;
			}
		break;
		default:
		break;
	}
	return return_val;
}


bool g_major_state_change_signal_cmplt = false;
bool g_major_state_change = false;
/**
 * @brief   Check for interrupts initiated via button press
 * @param   *red: pointer to current animation red color (8 bit)
 * @param   *green: pointer to current animation green color (8 bit)
 * @param  	*blue: pointer to current animation blue color (8 bit)
 * @return  bool: true if interrupt occurred since last check, else false
 */
bool task_button_press_check_interrupts(const strip_mask_t mask)
{
    bool return_val = false;
    if (task_button_press_major_state_change())
    {
        return_val = true;
        while (!g_major_state_change_signal_cmplt) osDelay(10);
        led_animate_solid_custom_color(mask, LED_COLOR_HEX_BLACK);
        osDelay(500); // delay 500 ms before major state change
    }
    else if (task_button_press_ctrl_interrupt_flag(mask, ISR_STATE))
    {
        return_val = true;
        if (LED_STATE_TWO_COLOR != task_led_current_led_state(strip_bit_to_strip_num((strip_bit_e) mask)))
        {
        	led_animate_solid_custom_color(mask, LED_COLOR_HEX_BLACK);
        }
    }
    else if (task_button_press_ctrl_interrupt_flag(mask, ISR_PAUSE))
    {
        while (g_task_led_ctrl[strip_bit_to_strip_num(mask)].led_interrupt_info.pause)
        {
            osDelay(10);
        }
    }
    else if (task_button_press_ctrl_interrupt_flag(mask, ISR_COLOR))
    {
    	// the color should be handled by the caller
//        // interrupt modifies the current color... apply it to the animation!
//        *red = led_ctrl_color_red_hex();
//        *green = led_ctrl_color_green_hex();
//        *blue = led_ctrl_color_blue_hex();
    }
    task_button_press_interrupt_flag_clear();
    return return_val;
}


/**
 * @brief  	Clear global flag indicating that an interrupt occurred.
 * @param   void
 * @return  void
 */
void task_button_press_interrupt_flag_clear(void)
{
	g_interrupt_flag = false;
}


/**
 * @brief  	Check if a major state change was intiated
 * @param   void
 * @return  bool: true if major state change, else false
 */
bool task_button_press_major_state_change(void)
{
    return g_task_button_press_major_change;
}


extern task_notification_value_format_t g_task_notification_value;
bool g_two_color_active = false;
bool g_button_was_low = false;
uint16_t g_low_count_hundred_milliseconds = 0;
/**
 * @brief   Task to control all button press action
 * @param   *arguments: UNUSED!!
 * @return  void
 */
void task_button_press(void *argument)
{
	gpio_specific_pin_e button_pin;
    //uint32_t button_pressed_bit = 0;
    led_color_hex_code_e color = LED_COLOR_HEX_BLACK;
    IRQn_Type irq_type = 0;
    board_init_push_buttons_e pushed_button = NUM_PUSH_BUTTONS;
    while (1)
    {
    	// wait for task notification from button interrupt.
        xTaskNotifyWait(0, g_task_notification_value.value, &g_task_notification_value.value, portMAX_DELAY);
        //xTaskNotifyWait(0, button_pressed_bit, &button_pressed_bit, portMAX_DELAY);
        // button_pressed_bit is passed through notification.  Convert to the button pressed enum.
//        pushed_button = (board_init_push_buttons_e) button_pressed_bit;
        pushed_button = (board_init_push_buttons_e) g_task_notification_value.value;
#if !defined(BOARD_SPUDGLO_V5) && !defined(BOARD_SPUDGLO_V6) && !defined(BOARD_SPUDGLO_V7)
        HAL_GPIO_WritePin(gpio_config_port_lookup(GPIO_PIOB_INT_LVL_EN), gpio_config_pin_lookup(GPIO_PIOB_INT_LVL_EN), GPIO_PIN_RESET);
        osDelay(700);
        HAL_GPIO_WritePin(gpio_config_port_lookup(GPIO_PIOB_INT_LVL_EN), gpio_config_pin_lookup(GPIO_PIOB_INT_LVL_EN), GPIO_PIN_SET);
#endif
//        if (LED_STATE_TWO_COLOR == task_led_current_led_state())
//		{
//			g_two_color_active = true;
//		}
//		else
//		{
//			g_two_color_active = false;
//		}
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

			//g_button_was_low = true;
			// record the current timestamp every 100 ms while waiting for this bitch to go high
    		//g_button_press_timestamp[pushed_button][TIMESTAMP_CURRENT] = xTaskGetTickCountFromISR();
    		osDelay(100);
    		g_low_count_hundred_milliseconds++;
		}
        // set flag to signal that a button interrupt was received!
        task_button_press_ctrl_set_interrupt_flag(STRIP_BIT_ALL_SET, task_led_ctrl_button_to_isr(pushed_button));
        // check if the button was held down longer than SWITCH_MAJOR_STATE_CHANGE_TIME_MILLISECONDS
        if ((g_low_count_hundred_milliseconds * 100) > SWITCH_MAJOR_STATE_CHANGE_TIME_MILLISECONDS)
        {
        	g_low_count_hundred_milliseconds = 0;
        	// major state change initiated. Special action occurs below.
            g_task_button_press_major_change = true;
            g_major_state_change_signal_cmplt = false;
            switch (pushed_button)
            {
                case PUSH_BUTTON_A:
                	// `A` button is speed.  Reset the speed to the default value.
                    g_a_ok_count++;
                    color = LED_COLOR_HEX_GREEN;
                    irq_type = PUSH_BUTTON_A_IRQ;
                    led_ctrl_speed_reset(STRIP_BIT_ALL_SET);
                break;
                case PUSH_BUTTON_B:
                	// `B` button is animation.  Reset the iteration count and also reset the master state to demo!
                    g_b_ok_count++;
                    color = LED_COLOR_HEX_BLUE;
                    irq_type = PUSH_BUTTON_B_IRQ;
                    led_state_ctrl_iteration_reset(STRIP_BIT_ALL_SET);
                    led_state_ctrl_force_demo(STRIP_BIT_ALL_SET); // enter demo state
                break;
                case PUSH_BUTTON_C:
                	// `C` button is color.  Reset the color master state back to demo mode.
                    g_c_ok_count++;

                    color = LED_COLOR_HEX_RED;
                    irq_type = PUSH_BUTTON_C_IRQ;
                    // don't change iteration count.  Simply go to color demo mode.
                    led_ctrl_color_master_state_force_demo(STRIP_BIT_ALL_SET);
                break;
                case PUSH_BUTTON_D:
                    g_d_ok_count++;

                	// `D` button is brightness.  Adjust the brightness and also clear pause if for some reason we are paused.
                    led_ctrl_brightness_adjust(STRIP_BIT_ALL_SET);
                    led_ctrl_pause(STRIP_BIT_ALL_SET);
                    color = LED_COLOR_HEX_WHITE;
                    irq_type = PUSH_BUTTON_D_IRQ;
                break;
                default:
                break;
            }
            
            led_color_t led_color;
            led_color.color_hex = LED_COLOR_HEX_BLACK;
			led_animate_set_all_pixels((uint16_t)STRIP_BIT_ALL_SET, &led_color);
			osDelay(500);
            for (uint8_t iii = 0; iii < 3; iii++)
            {
            	// flash the LEDs on the sign signalling that a master state change was made!
            	led_color.color_hex = LED_COLOR_HEX_GREEN;
                led_animate_set_all_pixels((uint16_t)STRIP_BIT_ALL_SET, &led_color);
                osDelay(500);
            	led_color.color_hex = LED_COLOR_HEX_BLACK;
                led_animate_set_all_pixels((uint16_t)STRIP_BIT_ALL_SET, &led_color);
                osDelay(500);
            }
            g_major_state_change_signal_cmplt = true;
            HAL_NVIC_SetPriority(irq_type, 24, 0);
            HAL_NVIC_EnableIRQ(irq_type);
            g_task_button_press_major_change = false;
        }
        else
        {
        	g_low_count_hundred_milliseconds = 0;
        	// simple button press.  No master state change here!
            switch (pushed_button)
            {
                case PUSH_BUTTON_A:
                	// A is speed.  Adjust it!
                    g_a_ok_count++;
                    if (g_two_color_active)
					{
                    	led_ctrl_color_master_state_force_fixed(STRIP_BIT_ALL_SET);
						led_state_ctrl_color_decrement_inner_color();
					}
                    else
                    {
                    	led_ctrl_speed_adjust(STRIP_BIT_ALL_SET);
                    }
                    HAL_NVIC_SetPriority(PUSH_BUTTON_A_IRQ, 24, 0);
                    HAL_NVIC_EnableIRQ(PUSH_BUTTON_A_IRQ);
                break;
                case PUSH_BUTTON_B:
                	// B is state.  Adjust it!
                    g_b_ok_count++;

//                    if (g_two_color_active)
//                    {
//                    	led_ctrl_color_master_state_force_fixed(STRIP_BIT_ALL_SET);
////                    	led_state_ctrl_color_decrement_outer_color();
//                    }
//                    else
//                    {
						if (LED_CTRL_STATE_MASTER_DEMO == led_state_ctrl_master_state(STRIP_BIT_ALL_SET))
						{
							// if master state is demo then change to fixed master state!
							led_state_ctrl_force_fixed_state(STRIP_BIT_ALL_SET); // animation count is auto cleared here.
						}
						else
						{
							// reset animation state count and adjust the state
							led_state_ctrl_iteration_reset(STRIP_BIT_ALL_SET);
							led_state_ctrl_adjust_state(STRIP_BIT_ALL_SET);
						}
//                    }
                    HAL_NVIC_SetPriority(PUSH_BUTTON_B_IRQ, 24, 0);
                    HAL_NVIC_EnableIRQ(PUSH_BUTTON_B_IRQ);
                break;
                case PUSH_BUTTON_C:
                	// C is color.  Adjust it!
                    g_c_ok_count++;

//                    if (g_two_color_active)
//                    {
//                    	led_ctrl_color_master_state_force_fixed(STRIP_BIT_ALL_SET);
//                    	led_state_ctrl_color_increment_inner_color();
//                    	// change inner color
//                    }
//                    else
//                    {
						if (LED_COLOR_MASTER_STATE_DEMO == led_ctrl_color_master_state(STRIP_BIT_ALL_SET))
						{
							// if master color state is demo then change to fixed master state!
							led_ctrl_color_master_state_force_fixed(STRIP_BIT_ALL_SET);
						}
						else
						{
							led_ctrl_color_adjust(STRIP_BIT_ALL_SET);
						}
//                    }
                    HAL_NVIC_SetPriority(PUSH_BUTTON_C_IRQ, 24, 0);
                    HAL_NVIC_EnableIRQ(PUSH_BUTTON_C_IRQ);
                break;
                case PUSH_BUTTON_D:
                	// D is pause.
                    g_d_ok_count++;
                	if (g_two_color_active)
					{
                		led_ctrl_color_master_state_force_fixed(STRIP_BIT_ALL_SET);
                		led_state_ctrl_color_decrement_outer_color();
						// change outer color
					}
                	else
                	{
                		led_ctrl_pause(STRIP_BIT_ALL_SET);
                	}
                    HAL_NVIC_SetPriority(PUSH_BUTTON_D_IRQ, 24, 0);
                    HAL_NVIC_EnableIRQ(PUSH_BUTTON_D_IRQ);
                break;
                default:
                break;
            }
        }
    }
}
