/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/
#include <stdint.h>
#include <math.h>
#include "numbers.h"
#include "task_led_ctrl.h"
#include "led_animate.h"
#include "task_button_press.h"


extern uint32_t g_max_strip_length;
extern uint16_t g_all_strip_mask;
extern task_notification_value_format_t g_task_notification_value;


/**
 * @brief   Write data stored in `gp_ws28128b_strip` array to the strip
 * @param   strip_mask - the strip to write to
 * @return  void
 */
void led_animate_show_strip(const strip_mask_t strip_mask)
{
    if (STRIP_BIT_1 & strip_mask)
    {
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


void led_animate_set_pixel(const strip_mask_t mask, const uint16_t pixel, const uint8_t red, const uint8_t green,
                           const uint8_t blue)
{
    if (STRIP_BIT_1 & mask)
    {
		if (ws2812_pixel_is_in_strip_range(STRIP_BIT_1, pixel))
		{
			 ws2812b_set_led(STRIP_BIT_1, pixel, red, green, blue);
		}
    }
    if (STRIP_BIT_2 & mask)
    {
		if (ws2812_pixel_is_in_strip_range(STRIP_BIT_2, pixel))
		{
			 ws2812b_set_led(STRIP_BIT_2, pixel, red, green, blue);
		}
    }
    if (STRIP_BIT_3 & mask)
    {
		if (ws2812_pixel_is_in_strip_range(STRIP_BIT_3, pixel))
		{
			 ws2812b_set_led(STRIP_BIT_3, pixel, red, green, blue);
		}
    }
}


void led_animate_set_all_pixels(const strip_mask_t mask, const uint8_t red, const uint8_t green, const uint8_t blue)
{
    uint16_t strip_size = 0;

    if (STRIP_BIT_1 & mask)
    {
		strip_size = ws2812_get_strip_size(STRIP_BIT_1);
		for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(STRIP_BIT_1, yyy, red, green, blue);
    }
    if (STRIP_BIT_2 & mask)
    {
		strip_size = ws2812_get_strip_size(STRIP_BIT_2);
		for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(STRIP_BIT_2, yyy, red, green, blue);
    }
    if (STRIP_BIT_3 & mask)
    {
		strip_size = ws2812_get_strip_size(STRIP_BIT_3);
		for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(STRIP_BIT_3, yyy, red, green, blue);
    }
    led_animate_show_strip(mask);
}


void led_animate_set_pixels_in_range(uint16_t start, uint16_t stop, const color_hex_code_e color)
{
    uint8_t dummy_red, dummy_green, dummy_blue; // not used but not worth creating a unique function IMO

    led_color_t led_color = color;
    if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
	for (uint16_t yyy = start; yyy <= stop; yyy++) ws2812b_set_led(STRIP_BIT_1, yyy, led_color.color_rgb.red, led_color.color_rgb.green, led_color.color_rgb.blue);
	led_animate_show_strip(STRIP_BIT_1);
}


/**
 * @brief   Set all pixels to black and show the strips
 * @param   void
 * @return  void
 * @note    This function will set `gp_ws28128b_strip` array and write it to the strip(s).
 */
void led_animate_turn_all_pixels_off(void)
{
	led_animate_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
}


uint8_t* led_animate_wheel(uint8_t wheel_pos)
{
    static uint8_t c[3];
    // red, green, blue (3 primary colors)
    // 8 bit colors..  Max value is 255
    // make a wheel, split it into 3 primary colors (85 positions per section)
    // increment wheel position.  After 85 steps passed then move to next primary color
    // this creates a rainbow effect. Reset wheel position to the section.
    if (wheel_pos < 85)
    {
        c[0] = wheel_pos * 3;
        c[1] = UINT8_MAX - (wheel_pos * 3);
        c[2] = 0;
    }
    else if(wheel_pos < 170)
    {
        wheel_pos -= 85;
        c[0] = UINT8_MAX - (wheel_pos * 3);
        c[1] = 0;
        c[2] = wheel_pos * 3;
    }
    else
    {
        wheel_pos -= 170;
        c[0] = 0;
        c[1] = wheel_pos * 3;
        c[2] = UINT8_MAX - (wheel_pos * 3);
    }
    return c;
}


void led_animate_solid_custom_color(const strip_mask_t mask, const color_hex_code_e color)
{
    uint8_t dummy_red, dummy_green, dummy_blue; // not used but not worth creating a unique function IMO
    led_color_t led_color = color;
//    led_color_t led_color.color_hex = color;
    if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
    led_animate_set_all_pixels(mask, color.color_rgb.red, color.color_rgb.green, color.color_rgb.blue);
    led_animate_show_strip(mask);
}


void led_animate_only_spell_word(const strip_mask_t mask, const color_hex_code_e color,
                                 const uint16_t time_ms)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    led_color_t led_color = color;
	for (int iii = 0; iii < strip_size; iii++)
	{
        if (task_button_press_interrupt_occurred() && (mask & g_task_notification_value.flat_entity))
        {
			if (task_button_press_check_interrupts())
            {
                return;
            }
			else if (g_task_notification_value.flat_stimulus.color)
			{
				led_color_strip_color(strip_bit_to_strip_num((strip_bit_e)mask, &led_color));
			}
        }
        led_animate_set_pixel(mask, iii, led_color.color_rgb.red, led_color.color_rgb.green,
							  led_color.color_rgb.blue);
        led_animate_show_strip(mask);
 		task_led_ctrl_delay(time_ms / task_speed_ctrl());
	}
}


void led_animate_fade_in_fade_out(const strip_mask_t mask, const color_hex_code_e color)
{
    float r, g, b;
    led_color_t led_color = color;
    for (int iii = 0; iii < 256; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&led_color.color_rgb.red,
            		&led_color.color_rgb.green,
					&led_color.color_rgb.blue))
            {
                return;
            }
        }
        r = (iii / 256.0) * led_color.color_rgb.red;
        g = (iii / 256.0) * led_color.color_rgb.green;
        b = (iii / 256.0) * led_color.color_rgb.blue;
        led_animate_set_all_pixels(mask, r, g, b);
    }
    for (int iii = 255; iii >= 0; iii = iii-2)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&led_color.color_rgb.red,
            		&led_color.color_rgb.green,
					&led_color.color_rgb.blue))
            {
                return;
            }
        }
        r = (iii / 256.0) * led_color.color_rgb.red;
        g = (iii / 256.0) * led_color.color_rgb.green;
        b = (iii / 256.0) * led_color.color_rgb.blue;
        led_animate_set_all_pixels(mask, r, g, b);
    }
}


void led_animate_strobe(const strip_mask_t mask, const color_hex_code_e color,
                        const uint16_t led_animate_strobe_count, const uint16_t flash_delay, const uint16_t end_pause)
{
    led_color_t led_color = color;
    for (int iii = 0; iii < led_animate_strobe_count; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&led_color.color_rgb.red, &led_color.color_rgb.green, &led_color.color_rgb.blue))
            {
                return;
            }
        }
        led_animate_set_all_pixels(mask, led_color.color_rgb.red,
        						   led_color.color_rgb.green,
                                   led_color.color_rgb.blue);
        led_animate_show_strip(mask);
        task_led_ctrl_delay(flash_delay);
        led_animate_set_all_pixels(mask, 0, 0, 0);
        led_animate_show_strip(mask);
        task_led_ctrl_delay(flash_delay);
    }
    task_led_ctrl_delay(end_pause);
}


void led_animate_twinkle(const strip_mask_t mask, const color_hex_code_e color, const uint16_t count,
                         const uint16_t speed_delay, const bool only_one)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    led_color_t led_color = color;
    for (int iii = 0; iii < count; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&led_color.color_rgb.red,
            		&led_color.color_rgb.green,
					&led_color.color_rgb.blue))
            {
                return;
            }
        }
        led_animate_set_pixel(mask, random_num(0, strip_size),
                              led_color.color_rgb.red,
                              led_color.color_rgb.green,
                              led_color.color_rgb.blue);
        led_animate_show_strip(mask);
        task_led_ctrl_delay(speed_delay / task_speed_ctrl());
        if (only_one) led_animate_set_all_pixels(mask, 0, 0, 0);
    }

    //task_led_ctrl_delay(speed_delay / task_speed_ctrl());
}


void led_animate_twinkle_random(const strip_mask_t mask, const uint16_t count,
                                const uint16_t speed_delay, const bool only_one)
{
    led_animate_set_all_pixels(mask, 0, 0, 0);
    uint8_t dummy_red, dummy_green, dummy_blue; // not used but not worth creating a unique function IMO
    for (int iii = 0; iii < count; iii++)
    {
        if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
        led_animate_set_pixel(mask, random_num(0, g_max_strip_length),
                              random_num(0, 255), random_num(0, 255), random_num(0, 255));
        led_animate_show_strip(mask);
        task_led_ctrl_delay((float_t)speed_delay / task_speed_ctrl());
        if (only_one) led_animate_set_all_pixels(mask, 0, 0, 0);
    }
}


void led_animate_sparkle_only_random_color(const strip_mask_t mask, const bool fill,
                                           const uint16_t speed_delay)
{
	float percent_to_fill = 0.7;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
	uint16_t num_active_leds = ws2812_get_num_active_animation_leds(mask);
    uint8_t dummy_red, dummy_green, dummy_blue; // not used but not worth creating a unique function IMO
	for (uint16_t iii = 0; iii < (percent_to_fill * (float)num_active_leds); iii++)
	{
	    if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
		int pix = random_num(0, strip_size);
		led_animate_set_pixel(mask, pix, random_num(0, 255), random_num(0, 255), random_num(0, 255));
		led_animate_show_strip(mask);
        task_led_ctrl_delay((float_t)speed_delay / task_speed_ctrl());
		if (!fill) led_animate_set_pixel(mask, pix, 0, 0, 0);
	}
}


void led_animate_sparkle_random_color(const strip_mask_t mask, const bool fill,
                                      const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    int pix = random_num(0, strip_size);
    led_animate_set_pixel(mask, pix, random_num(0, 255), random_num(0, 255), random_num(0, 255));
    led_animate_show_strip(mask);
    task_led_ctrl_delay((float_t)speed_delay / task_speed_ctrl());
    if (!fill) led_animate_set_pixel(mask, pix, 0, 0, 0);
}


void led_animate_sparkle(const strip_mask_t mask, const color_hex_code_e color,
                         const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t color_sparkle_rgb[sizeof(ws2812b_led_t)] = {0};
    led_color_hex_to_rgb(color, color_sparkle_rgb);
    uint16_t pix = random_num(0, strip_size);
    led_animate_set_pixel(mask, pix,
                          (color_sparkle_rgb[offsetof(ws2812b_led_t, red)]),
                          (color_sparkle_rgb[offsetof(ws2812b_led_t, green)]),
                          (color_sparkle_rgb[offsetof(ws2812b_led_t, blue)]));
    led_animate_show_strip(mask);
    task_led_ctrl_delay((float_t)speed_delay / task_speed_ctrl());
    led_animate_set_pixel(mask, pix, 0, 0, 0);
}


void led_animate_running_lights(const strip_mask_t mask, const color_hex_code_e color)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t color_running_lights_rgb[sizeof(ws2812b_led_t)] = {0};
    led_color_hex_to_rgb(mask, color_running_lights_rgb);
    uint16_t pos = 0;
    for (int i = 0; i < strip_size * 2; i++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_running_lights_rgb[offsetof(ws2812b_led_t, red)], &color_running_lights_rgb[offsetof(ws2812b_led_t, green)], &color_running_lights_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        pos++;
        for(int iii = 0; iii < strip_size; iii++)
        {
            led_animate_set_pixel(mask, iii,
                                  ((sin(iii + pos) * 127 + 128) / 255) * (color_running_lights_rgb[offsetof(ws2812b_led_t, red)]),
                                  ((sin(iii + pos) * 127 + 128) / 255) * (color_running_lights_rgb[offsetof(ws2812b_led_t, green)]),
                                  ((sin(iii + pos) * 127 + 128) / 255) * (color_running_lights_rgb[offsetof(ws2812b_led_t, blue)]));
        }
        led_animate_show_strip(mask);
        task_led_ctrl_delay(100 / task_speed_ctrl()); // TODO remove the magic number here!!!
    }
}


void led_animate_rainbow_cycle(const strip_mask_t mask, const uint16_t speed_delay)
{
	uint8_t dummy_red, dummy_green, dummy_blue;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t *c;
    uint16_t iii, jjj;
    for (jjj = 256 * 5; jjj > 0; jjj--)
    {
        if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
        for (iii = 0; iii < strip_size; iii++)
        {
            if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
            c = led_animate_wheel(((iii * 256 / strip_size) + jjj) & 255);
            led_animate_set_pixel(mask, iii, *c, *(c + 1), *(c + 2));
        }
        led_animate_show_strip(mask);
//        if (LED_SPEED_10X == task_speed_ctrl()) task_led_ctrl_delay(0);
//        else task_led_ctrl_delay((float_t)speed_delay / task_speed_ctrl());
    }
}


void led_animate_theater_chase(const strip_mask_t mask, const color_hex_code_e color,
                               const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t color_theater_chase_rgb[sizeof(ws2812b_led_t)] = {0};
    led_color_hex_to_rgb(color, color_theater_chase_rgb);
    for (int jjj = 0; jjj < 10; jjj++)
    {
        for (int qqq = 0; qqq < 3; qqq++)
        {
            if (task_button_press_interrupt_occurred())
            {
                if (task_button_press_check_interrupts(&color_theater_chase_rgb[offsetof(ws2812b_led_t, red)], &color_theater_chase_rgb[offsetof(ws2812b_led_t, green)], &color_theater_chase_rgb[offsetof(ws2812b_led_t, blue)]))
                {
                    return;
                }
            }
            for (int iii = 0; iii < strip_size; iii += 3)
            {
                led_animate_set_pixel(mask, iii + qqq,
                                      (color_theater_chase_rgb[offsetof(ws2812b_led_t, red)]),
                                      (color_theater_chase_rgb[offsetof(ws2812b_led_t, green)]),
                                      (color_theater_chase_rgb[offsetof(ws2812b_led_t, blue)]));
            }
            led_animate_show_strip(mask);
            if (task_button_press_interrupt_occurred())
            {
                if (task_button_press_check_interrupts(&color_theater_chase_rgb[offsetof(ws2812b_led_t, red)], &color_theater_chase_rgb[offsetof(ws2812b_led_t, green)], &color_theater_chase_rgb[offsetof(ws2812b_led_t, blue)]))
                {
                    return;
                }
            }
            task_led_ctrl_delay((float_t)speed_delay / task_speed_ctrl());
            for (int iii = 0; iii < strip_size; iii += 3) led_animate_set_pixel(mask, iii + qqq, 0, 0, 0); // turn every third pixel off
        }
    }
}


void led_animate_theater_chase_rainbow(const strip_mask_t mask, const uint16_t speed_delay)
{
	uint8_t dummy_red, dummy_green, dummy_blue;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t *c;
    for (int jjj = 0; jjj < 256; jjj++) // cycel all 256 colors in the led_animate_wheel
    {
        for (int qqq = 0; qqq < 3; qqq++)
        {
            if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
            for (int iii = 0; iii < strip_size; iii += 3)
            {
                if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
                c = led_animate_wheel((iii + jjj) % 255);
                led_animate_set_pixel(mask, iii + qqq, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            led_animate_show_strip(mask);
            task_led_ctrl_delay((float_t)speed_delay / task_speed_ctrl());
            for (int iii = 0; iii < strip_size; iii += 3) led_animate_set_pixel(mask, iii + qqq, 0, 0, 0); // turn every third pixel off
        }
    }
}


