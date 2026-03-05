// SRW
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"

#if defined(ENABLE_BUTTON)

#include "main.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "board_init_common.h"
#include "board_specific.h"
#include "led_color.h"
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
#include "led_ctrl_color.h"
#include "free_rtos_convenience.h"

#include "led_animate.h"
#include "task_create.h"
#include "button_config_hal_specific.h"

#define					SWITCH_TURN_OFF_TIME_MILLISECONDS						10000
#define 				SWITCH_MAJOR_STATE_CHANGE_TIME_MILLISECONDS				5000
extern led_ctrl_t 		g_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS];
uint32_t 				g_button_press_timestamp[NUM_BUTTONS][NUM_TIMESTAMPS] 	= {0};
uint32_t 				g_task_button_press_button_count[NUM_BUTTONS] 			= {0};
extern TaskHandle_t 	g_led_strip_1_ctrl_handle;
extern TaskHandle_t 	g_led_strip_sync_ctrl_handle;
extern bool g_led_animate_exit_stimulus;


bool task_button_press_interrupt_occurred(const strip_mask_t mask)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);

	// todo!!!! revisit this.  This is a major hack..
	//  check for either minor or major flag interrupt
	return (g_led_ctrl[strip_num].led_ctrl_interrupt_info.major_interrupt_flag || \
			g_led_ctrl[strip_num].led_ctrl_interrupt_info.minor_interrupt_flag);
}


bool task_button_press_major_interupt_occurred(void)
{
	return g_led_ctrl[STRIP_NUM_ALL_SET].led_ctrl_interrupt_info.major_interrupt_flag;
}


bool task_button_press_minor_interupt_occurred(void)
{
    return g_led_ctrl[STRIP_NUM_ALL_SET].led_ctrl_interrupt_info.minor_interrupt_flag;
}


/**
 * @brief   Return the ISR pertaining to the button
 * @param   btn: the button of interest
 * @return  isr_e: enumerated type for the interrupt pertaining to the button
 */
button_isr_e task_led_ctrl_button_to_isr(const button_e btn)
{
    switch (btn)
    {
        case BUTTON_A: 		return BUTTON_ISR_SPEED;
        case BUTTON_B:	 	return BUTTON_ISR_STATE;
        case BUTTON_C: 		return BUTTON_ISR_COLOR;
        case BUTTON_D: 		return BUTTON_ISR_PAUSE;
        default: 			return BUTTON_ISR_INVALID;
    }
}


static void task_button_press_ctrl_set_interrupt_flag(const strip_mask_t mask, button_e btn, bool major_interrupt)
{
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	p_led_ctrl_interrupt_status_t interrupt_status;
	// check for interrupt (major or minor)
	if (major_interrupt)
	{
		// force major interrupt transition complete flag to false
		g_led_ctrl[strip_num].led_ctrl_interrupt_info.major_interrupt_transition_cmplt_flag = false;
		// set major interrupt flag to true
		g_led_ctrl[strip_num].led_ctrl_interrupt_info.major_interrupt_flag = true;
		// record major interrupt status in generic variable
		interrupt_status = &g_led_ctrl[strip_num].led_ctrl_interrupt_info.major.interrupt_status;
	}
	else
	{
		// set minor interrupt flag to true
		g_led_ctrl[strip_num].led_ctrl_interrupt_info.minor_interrupt_flag = true;
		// record minor interrupt status in generic variable
		interrupt_status = &g_led_ctrl[strip_num].led_ctrl_interrupt_info.minor.interrupt_status;
	}
	// set interrupt flag pertaining to the button
	switch (btn)
	{
		case BUTTON_A:
			// `A` button is speed.  Set speed interrupt.
			interrupt_status->bits.speed = true;
		break;
		case BUTTON_B:
			// `B` button is animation.  Set animation interrupt.
			interrupt_status->bits.state = true;
		break;
		case BUTTON_C:
			// `C` button is color.  Set color interrupt.
			interrupt_status->bits.color = true;
		break;
		case BUTTON_D:
			if (major_interrupt)
			{
				// `D` button is brightness for major interrupt.  Set brightness interrupt.
				interrupt_status->bits.pause_brightness = true;
			}
			else
			{
				// `D` button is pause for minor interrupt.  Set pause interrupt.
				interrupt_status->bits.pause_brightness = true;
			}
		break;
		default:
			while (1);
		break;
	}
}


/**
 * @brief   Check for interrupts for the vigen strip
 * @param   mask: the mask pertaining to the strip
 * @return  bool: true if interrupt occurred since last check, else false
 */
bool task_button_press_check_interrupts(const strip_mask_t mask)
{
	p_led_ctrl_interrupt_status_t p_interrupt_status;
	bool b_interrupt_occurred = false;
    bool return_val = false;
	strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
	uint8_t bit_mask = 0;
	bool* pb_interrupt_flag = NULL;
	*pb_interrupt_flag = false;
	bit_mask |= ((1 << NUM_BUTTONS)) - 1;

	bool* pb_major_interrupt_transition_cmplt_flag = &g_led_ctrl[strip_num].led_ctrl_interrupt_info.major_interrupt_transition_cmplt_flag;

	// check if major interrupt occurred
	if (g_led_ctrl[strip_num].led_ctrl_interrupt_info.major_interrupt_flag)
	{
		b_interrupt_occurred = true;
		// save major interrupt status
		p_interrupt_status = &g_led_ctrl[strip_num].led_ctrl_interrupt_info.major.interrupt_status;
		// save major interrupt flag
		pb_interrupt_flag = &g_led_ctrl[strip_num].led_ctrl_interrupt_info.major_interrupt_flag;
		// set a flag to indicate that a major state interrupt has occured
        return_val = true;
        // wait for major_interrupt_transition_cmplt_flag to clear.
        while (!(*pb_major_interrupt_transition_cmplt_flag))
		{
        	// check every 50 ms for the major state change signal to clear.
        	free_rtos_delay_ms(50);
		}
        // clear the flag for the next go
        *pb_major_interrupt_transition_cmplt_flag = false;

	}
	// else check if minor interrupt occurred
	else if (g_led_ctrl[strip_num].led_ctrl_interrupt_info.minor_interrupt_flag)
	{
		b_interrupt_occurred = true;
		// save major interrupt status
		p_interrupt_status = &g_led_ctrl[strip_num].led_ctrl_interrupt_info.minor.interrupt_status;
		// save minor interrupt flag
		pb_interrupt_flag = &g_led_ctrl[strip_num].led_ctrl_interrupt_info.minor_interrupt_flag;
	}
	if (b_interrupt_occurred)
	{
		if (LED_CTRL_INTERRUPT_BIT_STATE & p_interrupt_status->flat_interrupt_status)
		{
			task_led_ctrl_set_skip_adjust_parameters(true);
			p_interrupt_status->bits.state = false;
			return_val = true;
		}
		if (LED_CTRL_INTERRUPT_BIT_COLOR & p_interrupt_status->flat_interrupt_status)
		{
			p_interrupt_status->bits.color = false;
		}
		if (LED_CTRL_INTERRUPT_BIT_SPEED & p_interrupt_status->flat_interrupt_status)
		{
			led_animate_set_adjust_speed(true);
			p_interrupt_status->bits.speed = false;
		}
		if (LED_CTRL_INTERRUPT_BIT_PAUSE_BRIGHTNESS & p_interrupt_status->flat_interrupt_status)
		{
			if (g_led_ctrl[strip_num].led_ctrl_interrupt_info.minor_interrupt_flag)
			{
				// wait for the pause flag to reset
				while (p_interrupt_status->bits.pause_brightness)
				{
					// check for the flag to clear every 50 ms.
					free_rtos_delay_ms(50);
				}
			}
			p_interrupt_status->bits.pause_brightness = false;
		}
		*pb_interrupt_flag = false;
	}
    return return_val;
}

typedef enum
{
	STARBURST_ANIMATION_0,
	STARBURST_ANIMATION_1,
	NUM_STARBURST_ANIMATIONS
} starburst_animation_e;

starburst_animation_e g_starburst_animation = STARBURST_ANIMATION_0;

bool gb_standard_a_button = false;
led_color_e g_led_color_dummy = LED_COLOR_BROWN;
/**
 * @brief   Task to control all button press action
 * @param   *arguments: UNUSED!!
 * @return  void
 */
void task_button_press(void *argument)
{
	uint32_t off_val = 0;
	static bool button_gate_open = false;
	static bool first_pass = true;
	// variable to track the button press time
	uint32_t timestamp_button_press_ms = 0;
	// variable to track the button release time
	uint32_t timestamp_button_release_ms = 0;
	// variable to track the button active time
	uint32_t button_active_time_ms = 0;
	uint32_t zabinski_return_val = 0;
	button_e btn = BUTTON_INVALID;
    led_color_hex_code_e color = LED_COLOR_HEX_BLACK;
    IRQn_Type irq_type = 0;
	strip_num_e strip_num = STRIP_NUM_1;

	bool pb_major_interrupt_flag = led_ctrl_read_major_interrupt_flag(STRIP_BIT_ALL_SET);
	bool pb_minor_interrupt_flag = led_ctrl_read_minor_interrupt_flag(STRIP_BIT_ALL_SET);

//	bool* pb_major_interrupt_flag = &g_led_ctrl[strip_num].led_ctrl_interrupt_info.major_interrupt_flag;
	bool* pb_major_interrupt_transition_cmplt_flag = &g_led_ctrl[strip_num].led_ctrl_interrupt_info.major_interrupt_transition_cmplt_flag;

//	bool* pb_minor_interrupt_flag = &g_led_ctrl[strip_num].led_ctrl_interrupt_info.minor_interrupt_flag;

    while (1)
    {
    	// wait for notification from button press.  This task will wait forever.
        xTaskNotifyWait(0, (uint32_t)btn, (uint32_t *)&btn, portMAX_DELAY);
        // task wakes up from button press.  Record the approximate time in ms.
        if (1000 == configTICK_RATE_HZ)
		{
            timestamp_button_press_ms = xTaskGetTickCount(); // * configTICK_RATE_HZ;
		}
        else
		{
        	// nothing will work if tick rate is not 1000 Hz
        	while (1); // this is an error!
		}
#if !defined(BOARD_SPUDGLO_V5) && !defined(BOARD_SPUDGLO_V6) && !defined(BOARD_SPUDGLO_V7) && !defined(BOARD_SPUDGLO_BUSINESS_CARD)
        HAL_GPIO_WritePin(gpio_config_port_lookup(GPIO_PIOB_INT_LVL_EN), gpio_config_pin_lookup(GPIO_PIOB_INT_LVL_EN), GPIO_PIN_RESET);
        free_rtos_delay_ms(700);
        HAL_GPIO_WritePin(gpio_config_port_lookup(GPIO_PIOB_INT_LVL_EN), gpio_config_pin_lookup(GPIO_PIOB_INT_LVL_EN), GPIO_PIN_SET);
#endif
        // wait for the button press to release
        while (button_access_button_is_active(btn))
		{
        	// check for button press every 50 ms
			free_rtos_delay_ms(50);
		}
        // record the approximate time in ms after the button is released.
        timestamp_button_release_ms = xTaskGetTickCount(); // * configTICK_RATE_HZ;
        // calculate the approximate time in ms that button is pressed.
        button_active_time_ms = timestamp_button_release_ms - timestamp_button_press_ms;

        // a hack below for Keefe wedding... Power up white.  If any button held for 10 seconds or longer on first power up go into demo mode.
		irq_type = button_config_button_to_irq(btn);

//        if (button_gate_open)
//        {
			if (SWITCH_TURN_OFF_TIME_MILLISECONDS < button_active_time_ms)
			{
#if defined(ENABLE_LED_STRIP_SYNC)
				vTaskSuspend(g_led_strip_sync_ctrl_handle);
#else
				vTaskSuspend(g_led_strip_1_ctrl_handle);
#endif
				led_animate_turn_all_pixels_off();
				// re-enable the interrupt
				HAL_NVIC_SetPriority(irq_type, 24, 0);
				HAL_NVIC_EnableIRQ(irq_type);
		        xTaskNotifyWait(0, 0xffffffff, (uint32_t *)&off_val, portMAX_DELAY);
		        NVIC_SystemReset();
			}
			if (SWITCH_MAJOR_STATE_CHANGE_TIME_MILLISECONDS < button_active_time_ms)
			{
				// button active for long enough to signal major state transition
				*pb_major_interrupt_flag = true;
				*pb_major_interrupt_transition_cmplt_flag = false;
				*pb_minor_interrupt_flag = false;
			}
			else
			{
				if (BUTTON_A == btn)
				{
					gb_standard_a_button = true;
				}
				// button pressed, signal minor interrupt
				*pb_major_interrupt_flag = false;
				*pb_major_interrupt_transition_cmplt_flag = false;
				*pb_minor_interrupt_flag = true;
			}
			// set flag to signal that a button interrupt was received!  For now all strips will action on the button
			task_button_press_ctrl_set_interrupt_flag(STRIP_BIT_ALL_SET, task_led_ctrl_button_to_isr(btn), *pb_major_interrupt_flag);
			// store the IRQ associated with the button.
			irq_type = button_config_button_to_irq(btn);
			// check if the button was held down longer than SWITCH_MAJOR_STATE_CHANGE_TIME_MILLISECONDS
			g_task_button_press_button_count[btn]++;
			if (*pb_major_interrupt_flag)
			{
#if defined(ENABLE_LED_STRIP_SYNC)
				vTaskSuspend(g_led_strip_sync_ctrl_handle);
#else
				vTaskSuspend(g_led_strip_1_ctrl_handle);
#endif
				// major state change.  Store the color denoting the transition.
				color = led_ctrl_color_major_state_change_color(btn);
				switch (btn)
				{
					case BUTTON_A:
						// `A` button is speed.  Reset the speed to the default value.
						led_ctrl_speed_reset(STRIP_BIT_ALL_SET);
						led_ctrl_speed_reset(STRIP_BIT_2);
					break;
					case BUTTON_B:
						// `B` button is animation.  Reset the iteration count and also reset the master state to demo!
						led_state_ctrl_iteration_reset(STRIP_BIT_ALL_SET);
						led_state_ctrl_iteration_reset(STRIP_BIT_2);
						led_state_ctrl_force_demo(STRIP_BIT_ALL_SET); // enter demo state
						led_state_ctrl_force_demo(STRIP_BIT_2); // enter demo state
					break;
					case BUTTON_C:
						// `C` button is color.  Reset the color master state back to demo mode.
						// don't change iteration count.  Simply go to color demo mode.
						led_ctrl_color_master_state_force_demo(STRIP_BIT_ALL_SET);
						led_ctrl_color_master_state_force_demo(STRIP_BIT_2);

					break;
					case BUTTON_D:
						// `D` button is brightness.  Adjust the brightness and also clear pause if for some reason we are paused.
						led_ctrl_brightness_adjust(STRIP_BIT_ALL_SET);
						led_ctrl_brightness_adjust(STRIP_BIT_2);

						led_ctrl_pause(STRIP_BIT_ALL_SET);
						led_ctrl_pause(STRIP_BIT_2);
					break;
					default:
					break;
				}
				// turn off all LEDs for 500 ms
				led_animate_turn_all_pixels_off();
				free_rtos_delay_ms(500);
				for (uint8_t iii = 0; iii < 3; iii++)
				{
					// flash the LEDs to signal a master state change.
					// turn on all LEDs for 500 ms
					led_animate_set_all_pixels_hex_color(STRIP_BIT_ALL_SET, color);
					led_animate_set_all_pixels_hex_color(STRIP_BIT_2, color);
					free_rtos_delay_ms(500);
					// turn off all LEDs for 500 ms
					led_animate_turn_all_pixels_off();
					free_rtos_delay_ms(500);
				}
				// re-enable the button interrupt
				HAL_NVIC_SetPriority(irq_type, 24, 0);
				HAL_NVIC_EnableIRQ(irq_type);
				*pb_major_interrupt_flag = false;
				*pb_major_interrupt_transition_cmplt_flag = true;
#if defined(ENABLE_LED_STRIP_SYNC)
				vTaskSuspend(g_led_strip_sync_ctrl_handle);
#else
				vTaskSuspend(g_led_strip_1_ctrl_handle);
#endif
			}
			else
			{
				// minor state change
				switch (btn)
				{
					case BUTTON_A:
						// 'A' is speed.  Adjust it!
						if (gb_standard_a_button)
						{
							gb_standard_a_button = false;
							led_ctrl_speed_adjust(STRIP_BIT_ALL_SET);
//							led_ctrl_speed_adjust(STRIP_BIT_2);

						}
					break;
					case BUTTON_B:
						// 'B' is state.  Adjust it!
						// check if current state is the master demo state.
						if (LED_CTRL_STATE_MASTER_DEMO == led_state_ctrl_master_state(STRIP_BIT_ALL_SET))
						{
							// master state is demo, change to fixed master state.
							led_state_ctrl_force_fixed_state(STRIP_BIT_ALL_SET);
//							led_state_ctrl_force_fixed_state(STRIP_BIT_2);

						}
						g_led_animate_exit_stimulus = true;
						led_state_ctrl_iteration_reset(STRIP_BIT_ALL_SET);
//						led_state_ctrl_iteration_reset(STRIP_BIT_2);

						led_state_ctrl_adjust_state(STRIP_BIT_ALL_SET);
//						led_state_ctrl_adjust_state(STRIP_BIT_2);


					break;
					case BUTTON_C:
						// 'C' is color.  Adjust it!
						// check if current color is the master demo state
						if (LED_COLOR_MASTER_STATE_DEMO == led_ctrl_color_master_state(STRIP_BIT_ALL_SET))
						{
							// master color state is demo... change to fixed master state!
							led_ctrl_color_master_state_force_fixed(STRIP_BIT_ALL_SET);
//							led_ctrl_color_master_state_force_fixed(STRIP_BIT_2);
						}
						else
						{
							// master color state is fixed.  Adjust the color.
							led_ctrl_color_adjust(STRIP_BIT_ALL_SET);
//							led_ctrl_color_adjust(STRIP_BIT_2);

						}
					break;
					case BUTTON_D:
						// 'D' is pause.
						led_ctrl_pause(STRIP_BIT_ALL_SET);
//						led_ctrl_pause(STRIP_BIT_2);

					break;
					default:
					break;
				}
				// re-enable the interrupt
				HAL_NVIC_SetPriority(irq_type, 24, 0);
				HAL_NVIC_EnableIRQ(irq_type);
//			}
        }
	}

}


#endif
