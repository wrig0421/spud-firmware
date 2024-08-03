/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/
#include <stdint.h>
#include <math.h>
#include "numbers.h"
#include "led_ctrl.h"
#include "task_led_ctrl.h"
#include "led_color.h"
#include "led_animate.h"
#include "task_notify.h"
#include "task_button_press.h"
#include "led_ctrl_speed.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"


uint32_t g_time_differences[NUM_LED_STATES];
extern uint32_t g_max_strip_length;
extern uint16_t g_all_strip_mask;
extern task_notification_value_format_t g_task_notification_value;

bool g_led_animate_adjust_speed = false;
bool led_animate_need_to_adjust_speed(void)
{
	return g_led_animate_adjust_speed;
}


void led_animate_set_adjust_speed(bool)
{
	g_led_animate_adjust_speed = true;
}


void led_animate_clear_adjust_speed(void)
{
	g_led_animate_adjust_speed =false;
}


/**
 * @brief   Write data stored in `gp_ws28128b_strip` array to the strip
 * @param   strip_mask - the strip to write to
 * @return  void
 */
void led_animate_show_strip(const strip_mask_t strip_mask)
{
    if (STRIP_BIT_1 & strip_mask)
    {
    	//ws2812b_show_strip_two();
        ws2812b_show_strip_one();
    }
    if (STRIP_BIT_2 & strip_mask)
    {
        ws2812b_show_strip_two();
    }
    if (STRIP_BIT_3 & strip_mask)
    {
        ws2812b_show_strip_three();
    }
}


void led_animate_set_pixel(const strip_mask_t mask, const uint16_t pixel, led_color_t* led_color)
{
    if (STRIP_BIT_1 & mask)
    {
		if (ws2812_pixel_is_in_strip_range(STRIP_BIT_1, pixel))
		{
			 ws2812b_set_led(STRIP_BIT_1, pixel, led_color->color_rgb.red, led_color->color_rgb.green, led_color->color_rgb.blue);
		}
    }
    if (STRIP_BIT_2 & mask)
    {
		if (ws2812_pixel_is_in_strip_range(STRIP_BIT_2, pixel))
		{
			 ws2812b_set_led(STRIP_BIT_2, pixel, led_color->color_rgb.red, led_color->color_rgb.green, led_color->color_rgb.blue);
		}
    }
    if (STRIP_BIT_3 & mask)
    {
		if (ws2812_pixel_is_in_strip_range(STRIP_BIT_3, pixel))
		{
			 ws2812b_set_led(STRIP_BIT_3, pixel, led_color->color_rgb.red, led_color->color_rgb.green, led_color->color_rgb.blue);
		}
    }
}


void led_animate_set_all_pixels(const strip_mask_t mask, led_color_t* led_color)
{
    uint16_t strip_size = 0;

    if (STRIP_BIT_1 & mask)
    {
		strip_size = ws2812_get_strip_size(STRIP_BIT_1);
		for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(STRIP_BIT_1, yyy, led_color->color_rgb.red, led_color->color_rgb.green, led_color->color_rgb.blue);
    }
    if (STRIP_BIT_2 & mask)
    {
		strip_size = ws2812_get_strip_size(STRIP_BIT_2);
		for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(STRIP_BIT_2, yyy, led_color->color_rgb.red, led_color->color_rgb.green, led_color->color_rgb.blue);
    }
    if (STRIP_BIT_3 & mask)
    {
		strip_size = ws2812_get_strip_size(STRIP_BIT_3);
		for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(STRIP_BIT_3, yyy, led_color->color_rgb.red, led_color->color_rgb.green, led_color->color_rgb.blue);
    }
    led_animate_show_strip(mask);
}


void led_animate_set_all_pixels_hex_color(const strip_mask_t mask, const led_color_hex_code_e color)
{
    led_color_t led_color;
    led_color.color_hex = color;
    led_animate_set_all_pixels(mask, &led_color); // passed locally.  3 bytes nbd
}



void led_animate_set_pixels_in_range(const strip_mask_t mask, uint16_t start, uint16_t stop, const led_color_hex_code_e color)
{
    led_color_t led_color;
    led_color.color_hex = color;
    if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(mask)) return;
	for (uint16_t yyy = start; yyy <= stop; yyy++) ws2812b_set_led(mask, yyy, led_color.color_rgb.red, led_color.color_rgb.green, led_color.color_rgb.blue);
	led_animate_show_strip(mask);
}


/**
 * @brief   Set all pixels to black and show the strips
 * @param   void
 * @return  void
 * @note    This function will set `gp_ws28128b_strip` array and write it to the strip(s).
 */
void led_animate_turn_all_pixels_off(void)
{
	led_color_t led_color;
	led_color.color_hex = LED_COLOR_HEX_BLACK;
	led_animate_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, &led_color);
}


void led_animate_turn_all_pixels_off_in_strip(const strip_mask_t mask)
{
	led_color_t led_color;
	led_color.color_hex = LED_COLOR_HEX_BLACK;
	led_animate_set_all_pixels((strip_mask_t)mask, &led_color);
}


static void led_animate_wheel(uint8_t wheel_pos, led_color_t* p_led_color)
{
	// TODO consider not modifying the passed parameter from the caller.
    // red, green, blue (3 primary colors)
    // 8 bit colors..  Max value is 255
    // make a wheel, split it into 3 primary colors (85 positions per section)
    // increment wheel position.  After 85 steps passed then move to next primary color
    // this creates a rainbow effect. Reset wheel position to the section.
    if (wheel_pos < 85)
    {
    	p_led_color->color_rgb.red = wheel_pos * 3;
    	p_led_color->color_rgb.green = UINT8_MAX - (wheel_pos * 3);
    	p_led_color->color_rgb.blue = 0;
    }
    else if(wheel_pos < 170)
    {
        wheel_pos -= 85;
        p_led_color->color_rgb.red = UINT8_MAX - (wheel_pos * 3);
        p_led_color->color_rgb.green = 0;
        p_led_color->color_rgb.blue = wheel_pos * 3;
    }
    else
    {
        wheel_pos -= 170;
        p_led_color->color_rgb.red = 0;
        p_led_color->color_rgb.green = wheel_pos * 3;
        p_led_color->color_rgb.blue = UINT8_MAX - (wheel_pos * 3);
    }
}


void led_animate_solid_custom_color(const strip_mask_t mask, const led_color_hex_code_e color)
{
    led_color_t led_color;
    led_color.color_hex = color; //led_color_to_hex_code(color);
//    led_color_t led_color.color_hex = color;
    if (task_button_press_interrupt_occurred())
	{
		if (task_button_press_check_interrupts(mask))
		{
			return;
		}
//		else if (g_task_notification_value.stimulus_bits.color)
//		{
//			led_color.color_hex = led_color_to_hex_code(*p_color);
//		}
	}
    led_animate_set_all_pixels(mask, &led_color);
	//led_animate_show_strip(mask);
}

void led_animate_only_spell_word(const strip_mask_t mask, const led_color_e* p_color,
                                 uint16_t* p_delay_ms)
{
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);
	uint32_t time_start = xTaskGetTickCount();
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    led_color_t led_color;
    led_color.color_hex = led_color_to_hex_code(*p_color);
	for (int iii = 0; iii < strip_size; iii++)
	{
        if (task_button_press_interrupt_occurred())
        {
			if (task_button_press_check_interrupts(mask))
            {
                return;
            }
			else if (g_task_notification_value.stimulus_bits.color)
			{
				led_color.color_hex = led_color_to_hex_code(*p_color);
			}
        	else if (led_animate_need_to_adjust_speed())
			{
        		delay_copy = task_led_state_inner_animation_delay_ms(mask, LED_STATE_RAINBOW_CYCLE);
				led_animate_clear_adjust_speed();
			}
        }
        led_animate_set_pixel(mask, iii, &led_color);
        led_animate_show_strip(mask);
 		led_ctrl_delay(delay_copy);
	}
	g_time_differences[LED_STATE_SPELL] = xTaskGetTickCount() - time_start;
}


void led_animate_fade_in_fade_out(const strip_mask_t mask, const led_color_e* p_color,
								  uint16_t* p_delay_ms)
{
	uint32_t time_start = xTaskGetTickCount();
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);

	float fade_factor = 0.0f;
    led_color_t led_color;
    led_color_t temp_led_color;

    led_color.color_hex = led_color_to_hex_code(*p_color);
    for (int iii = 0; iii < 256; iii += 2)
    {
    	fade_factor = (float)iii / 256.0f;
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(mask))
            {
                return;
            }
			else if (g_task_notification_value.stimulus_bits.color)
			{
				led_color.color_hex = led_color_to_hex_code(*p_color);
			}
        	else if (led_animate_need_to_adjust_speed())
			{
        		delay_copy = task_led_state_inner_animation_delay_ms(mask, LED_STATE_RAINBOW_CYCLE);
				led_animate_clear_adjust_speed();
			}
        }
        temp_led_color.color_rgb.red = led_color.color_rgb.red * fade_factor;
        temp_led_color.color_rgb.green = led_color.color_rgb.green * fade_factor;
        temp_led_color.color_rgb.blue = led_color.color_rgb.blue * fade_factor;
        led_animate_set_all_pixels(mask, &temp_led_color);
 		led_ctrl_delay(delay_copy);
    }
    for (int iii = 255; iii >= 0; iii -= 2)
    {
    	fade_factor = (float)iii / 256.0f;
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(mask))
            {
                return;
            }
			else if (g_task_notification_value.stimulus_bits.color)
			{
				led_color.color_hex = led_color_to_hex_code(*p_color);
			}
        	else if (led_animate_need_to_adjust_speed())
			{
        		delay_copy = task_led_state_inner_animation_delay_ms(mask, LED_STATE_RAINBOW_CYCLE);
				led_animate_clear_adjust_speed();
			}
        }
        temp_led_color.color_rgb.red = led_color.color_rgb.red * fade_factor;
        temp_led_color.color_rgb.green = led_color.color_rgb.green * fade_factor;
        temp_led_color.color_rgb.blue = led_color.color_rgb.blue * fade_factor;
        led_animate_set_all_pixels(mask, &temp_led_color);
 		led_ctrl_delay(delay_copy);
    }
	g_time_differences[LED_STATE_FADE_IN_AND_OUT] = xTaskGetTickCount() - time_start;

}


void led_animate_strobe(const strip_mask_t mask, const led_color_e* p_color,
                        const uint16_t led_animate_strobe_count, const uint16_t flash_delay, const uint16_t end_pause)
{

    led_color_t led_color;
    led_color.color_hex = led_color_to_hex_code(*p_color);
    for (int iii = 0; iii < led_animate_strobe_count; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(mask))
            {
                return;
            }
			else if (g_task_notification_value.stimulus_bits.color)
			{
				led_color.color_hex = led_color_to_hex_code(*p_color);
			}
        }
        led_color.color_hex = led_color_to_hex_code(*p_color);
        led_animate_set_all_pixels(mask, &led_color);
//        led_animate_show_strip(mask);
        led_ctrl_delay(flash_delay);
        led_color.color_hex = LED_COLOR_HEX_BLACK;
        led_animate_set_all_pixels(mask, &led_color);
//        led_animate_show_strip(mask);
        led_ctrl_delay(flash_delay);
    }
    led_ctrl_delay(end_pause);

}


void led_animate_twinkle(const strip_mask_t mask, const led_color_e* p_color, const uint16_t count,
                         uint16_t* p_delay_ms, const bool only_one)
{
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);
	uint32_t time_start = xTaskGetTickCount();
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    led_color_t led_color;
    led_color.color_hex = led_color_to_hex_code(*p_color);
    for (int iii = 0; iii < count; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(mask))
            {
                return;
            }
			else if (g_task_notification_value.stimulus_bits.color)
			{
				led_color.color_hex = led_color_to_hex_code(*p_color);
			}
        	else if (led_animate_need_to_adjust_speed())
			{
        		delay_copy = task_led_state_inner_animation_delay_ms(mask, LED_STATE_RAINBOW_CYCLE);
				led_animate_clear_adjust_speed();
			}
        }
        led_animate_set_pixel(mask, random_num(0, strip_size), &led_color);
        led_animate_show_strip(mask);
//        led_ctrl_delay(5);
        led_ctrl_delay(delay_copy);
        if (only_one)
		{
        	led_color.color_hex = LED_COLOR_HEX_BLACK;
        	led_animate_set_all_pixels(mask, &led_color);
		}
    }
	g_time_differences[LED_STATE_TWINKLE] = xTaskGetTickCount() - time_start;

    //led_ctrl_delay(speed_delay);
}


void led_animate_twinkle_random(const strip_mask_t mask, const uint16_t count,
                                const uint16_t* p_delay_ms, const bool only_one)
{
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);
	led_color_t led_color;
	led_color.color_hex = LED_COLOR_BLACK;
    led_animate_set_all_pixels(mask, &led_color);
     // not used but not worth creating a unique function IMO
    for (int iii = 0; iii < count; iii++)
    {
        if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(mask)) return;
        led_color.color_hex = random_num(0, UINT24_MAX);
        led_animate_set_pixel(mask, random_num(0, g_max_strip_length), &led_color);
        led_animate_show_strip(mask);
        led_ctrl_delay(delay_copy);
        if (only_one)
		{
        	led_color.color_hex = LED_COLOR_HEX_BLACK;
        	led_animate_set_all_pixels(mask, &led_color);
		}
    }
}


uint32_t g_start_time = 0; // * configTICK_RATE_HZ;
uint32_t g_stop_time = 0;
void led_animate_sparkle_only_random_color(const strip_mask_t mask, const bool fill,
                                           const uint16_t* p_delay_ms)
{
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);

	led_color_t led_color;
	float percent_to_fill = 0.7;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
	uint16_t num_active_leds = ws2812_get_num_active_animation_leds(mask);
     // not used but not worth creating a unique function IMO
	for (uint16_t iii = 0; iii < (percent_to_fill * (float)num_active_leds); iii++)
	{
	    if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(mask)) return;
		int pix = random_num(0, strip_size);
		led_color.color_hex = random_num(0, UINT24_MAX);
		led_animate_set_pixel(mask, pix, &led_color);
		led_animate_show_strip(mask);
		led_ctrl_delay(0);
		if (!fill)
		{
			led_color.color_hex = LED_COLOR_HEX_BLACK;
			led_animate_set_all_pixels(mask, &led_color);
			led_ctrl_delay(20);
		}
        led_ctrl_delay(delay_copy);
	}
}


void led_animate_sparkle_random_color(const strip_mask_t mask, const bool fill,
                                      const uint16_t* p_delay_ms)
{
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);

	led_color_t led_color;
	led_color.color_hex = random_num(0, UINT24_MAX);
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    int pix = random_num(0, strip_size);
    led_animate_set_pixel(mask, pix, &led_color);
    led_animate_show_strip(mask);
    led_ctrl_delay(delay_copy);
    if (!fill)
	{
    	led_color.color_hex = LED_COLOR_HEX_BLACK;
    	led_animate_set_pixel(mask, pix, &led_color);
	}
}


void led_animate_sparkle(const strip_mask_t mask, const led_color_e* p_color,
                         const uint16_t* p_delay_ms)
{
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);

	led_color_t led_color;
	led_color.color_hex = led_color_to_hex_code(*p_color);
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint16_t pix = random_num(0, strip_size);
    led_animate_set_pixel(mask, pix, &led_color);
    led_animate_show_strip(mask);
    led_ctrl_delay(delay_copy);
	led_color.color_hex = LED_COLOR_HEX_BLACK;
    led_animate_set_pixel(mask, pix, &led_color);
}


void led_animate_running_lights(const strip_mask_t mask, const led_color_e* p_color,
								const uint16_t* p_delay_ms)
{
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);

	led_color_t led_color;
	led_color.color_hex = led_color_to_hex_code(*p_color);
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint16_t pos = 0;
    for (int i = 0; i < strip_size * 2; i++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(mask))
            {
                return;
            }
			else if (g_task_notification_value.stimulus_bits.color)
			{
				led_color.color_hex = led_color_to_hex_code(*p_color);
			}
        }
        pos++;
        for(int iii = 0; iii < strip_size; iii++)
        {
        	// changed from double to float precision
        	led_color.color_rgb.red *= ((sinf(iii + pos) * 127.0f + 128.0f) / 255.0f);
        	led_color.color_rgb.green *= ((sinf(iii + pos) * 127.0f + 128.0f) / 255.0f);
        	led_color.color_rgb.blue *= ((sinf(iii + pos) * 127.0f + 128.0f) / 255.0f);
            led_animate_set_pixel(mask, iii, &led_color);
        }
        led_animate_show_strip(mask);
        led_ctrl_delay(delay_copy); // TODO remove the magic number here!!!
    }

}


void led_animate_rainbow_cycle(const strip_mask_t mask, uint16_t* p_delay_ms)
{
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);

	led_color_t led_color;
	led_color.color_hex = LED_COLOR_HEX_BLACK;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
	//uint16_t strip_size = ws2812_get_strip_size(mask);
    for (uint16_t jjj = 256 * 5; jjj > 0; jjj--)
    {
        if (task_button_press_interrupt_occurred())
		{
//        	if (task_button_press_check_interrupts(mask) ||
//        			(LED_STATE_RAINBOW_CYCLE != task_led_current_led_state(mask)))
        	if (task_button_press_check_interrupts(mask))
			{
        		return;
			}
        	else if (led_animate_need_to_adjust_speed())
			{
        		delay_copy = task_led_state_inner_animation_delay_ms(mask, LED_STATE_RAINBOW_CYCLE);
				led_animate_clear_adjust_speed();
			}
		}
        for (uint16_t iii = 0; iii < strip_size; iii++)
        {
            if (task_button_press_interrupt_occurred())
    		{
    //        	if (task_button_press_check_interrupts(mask) ||
    //        			(LED_STATE_RAINBOW_CYCLE != task_led_current_led_state(mask)))
            	if (task_button_press_check_interrupts(mask))
    			{
            		return;
    			}
            	else if (led_animate_need_to_adjust_speed())
    			{
            		delay_copy = task_led_state_inner_animation_delay_ms(mask, LED_STATE_RAINBOW_CYCLE);
    				led_animate_clear_adjust_speed();
    			}
    		}
            led_animate_wheel(((iii * 256 / strip_size) + jjj) & 255, &led_color);
            led_animate_set_pixel(mask, iii, &led_color);
        }
        led_animate_show_strip(mask);
//        led_ctrl_delay(1);
        led_ctrl_delay(delay_copy);

//        if (LED_SPEED_1 == led_ctrl_speed(mask)) led_ctrl_delay(0);
//        else led_ctrl_delay(speed_delay);
    }
}


void led_animate_theater_chase(const strip_mask_t mask, const led_color_e* p_color,
                               uint16_t* p_delay_ms)
{
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);

	led_color_t led_color;
	led_color.color_hex = led_color_to_hex_code((led_color_e)*p_color);
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    for (int jjj = 0; jjj < 100; jjj++)
    {
        for (int qqq = 0; qqq < 3; qqq++)
        {
            if (task_button_press_interrupt_occurred())
            {
                if (task_button_press_check_interrupts(mask))
                {
                    return;
                }
    			else if (g_task_notification_value.stimulus_bits.color)
    			{
    				led_color.color_hex = led_color_to_hex_code(*p_color);
    			}
            	else if (led_animate_need_to_adjust_speed())
    			{
            		delay_copy = task_led_state_inner_animation_delay_ms(mask, LED_STATE_RAINBOW_CYCLE);
    				led_animate_clear_adjust_speed();
    			}
            }
            for (int iii = 0; iii < strip_size; iii += 3)
            {
                led_animate_set_pixel(mask, iii + qqq, &led_color);
            }
            led_animate_show_strip(mask);
//            led_ctrl_delay(1);
            led_ctrl_delay(delay_copy);
            for (int iii = 0; iii < strip_size; iii += 3)
			{
            	led_color.color_hex = LED_COLOR_HEX_BLACK;
            	led_animate_set_pixel(mask, iii + qqq, &led_color); // turn every third pixel off
			}
            led_animate_show_strip(mask);
//            led_ctrl_delay(1);
        	led_color.color_hex = led_color_to_hex_code(*p_color);
        }
    }

}


void led_animate_theater_chase_rainbow(const strip_mask_t mask, uint16_t* p_delay_ms)
{
	uint16_t delay_copy = (uint16_t)(*p_delay_ms);

	uint32_t time_start = xTaskGetTickCount();

	led_color_t led_color;
	led_color.color_hex = LED_COLOR_HEX_BLACK;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    for (int jjj = 0; jjj < 256; jjj++) // cycle all 256 colors in the led_animate_wheel
    {
        for (int qqq = 0; qqq < 3; qqq++)
        {
            if (task_button_press_interrupt_occurred())
			{
                if (task_button_press_check_interrupts(mask))
                {
                    return;
                }
            	else if (led_animate_need_to_adjust_speed())
    			{
            		delay_copy = task_led_state_inner_animation_delay_ms(mask, LED_STATE_RAINBOW_CYCLE);
    				led_animate_clear_adjust_speed();
    			}
			}
            for (int iii = 0; iii < strip_size; iii += 3)
            {
                if (task_button_press_interrupt_occurred())
    			{
                    if (task_button_press_check_interrupts(mask))
                    {
                        return;
                    }
                	else if (led_animate_need_to_adjust_speed())
        			{
                		delay_copy = task_led_state_inner_animation_delay_ms(mask, LED_STATE_RAINBOW_CYCLE);
        				led_animate_clear_adjust_speed();
        			}
    			}
                led_animate_wheel((iii + jjj) % 255, &led_color);
                led_animate_set_pixel(mask, iii + qqq, &led_color);
            }
            led_animate_show_strip(mask);
//            led_ctrl_delay(5);
            led_ctrl_delay(delay_copy);
            for (int iii = 0; iii < strip_size; iii += 3)
			{
            	led_color.color_hex = LED_COLOR_HEX_BLACK;
            	led_animate_set_pixel(mask, iii + qqq, &led_color); // turn every third pixel off
			}
            led_animate_show_strip(mask);
//            led_ctrl_delay(5);
//            led_ctrl_delay(1);
//
//            led_ctrl_delay(*p_delay_ms);
//            for (int iii = 0; iii < strip_size; iii += 3)
//			{
//            	led_color.color_hex = LED_COLOR_HEX_BLACK;
//            	led_animate_set_pixel(mask, iii + qqq, &led_color); // turn every third pixel off
//			}
        }
    }
	g_time_differences[LED_STATE_THEATER_CHASE_RAINBOW] = xTaskGetTickCount() - time_start;

}


uint16_t g_num_pixels = 0;
uint16_t g_dbg_pixel_start = 0;
uint16_t g_dbg_pixel_stop = 10;
bool g_dbg_num_flag = false;
bool g_dbg_num_pixels_turn_off_all_pixels;
bool g_dbg_num_pixels_complete = false;
void led_animate_determine_number_pixels_in_strip(const strip_mask_t mask)
{
	led_animate_turn_all_pixels_off();
	do
	{

		if (g_dbg_num_pixels_turn_off_all_pixels)
		{
			g_dbg_num_pixels_turn_off_all_pixels = false;
			led_animate_turn_all_pixels_off();
			led_ctrl_delay(5000);
		}
		else
		{
			led_animate_set_pixels_in_range(mask, g_dbg_pixel_start, g_dbg_pixel_stop, LED_COLOR_HEX_DARK_MAGENTA);
			led_ctrl_delay(2000);
		}
	} while ((!g_dbg_num_pixels_complete));
	g_dbg_num_pixels_complete = false;
}


