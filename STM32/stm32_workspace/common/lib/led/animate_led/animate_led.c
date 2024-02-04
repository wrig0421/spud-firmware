/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/
#include <stdint.h>
#include <math.h>
#include "projdefs.h"
#include "numbers.h"
#include "task_led_ctrl.h"
#include "animate_led.h"
#include "task_button_press.h"


extern uint32_t g_max_strip_length;
extern uint16_t g_all_strip_mask;


const animate_led_ctrl_t g_animate_led_ctrl[NUM_LED_STATES] =
{
	[LED_STATE_SPELL] =
	{
		.animation_loop_iterations = 10,
		.animation_delay_ms = 0
	},
	[LED_STATE_WHITE_COLOR] =
	{
		.animation_loop_iterations = 1,
		.animation_delay_ms = 5000
	},
	[LED_STATE_SOLID_COLOR] =
	{
		.animation_loop_iterations = 5,
		.animation_delay_ms = 5000
	},
	[LED_STATE_SPARKLE_NO_FILL] =
	{
		.animation_loop_iterations = 5,
		.animation_delay_ms = 0
	},
	[LED_STATE_SPARKLE_FILL] =
	{
		.animation_loop_iterations = 10,
		.animation_delay_ms = 0
	},
	[LED_STATE_RAINBOW_CYCLE] =
	{
		.animation_loop_iterations = 5,
		.animation_delay_ms = 0
	},
	[LED_STATE_THEATER_CHASE] =
	{
		.animation_loop_iterations = 10,
		.animation_delay_ms = 0
	},
	[LED_STATE_THEATER_CHASE_RAINBOW] =
	{
		.animation_loop_iterations = 2,
		.animation_delay_ms = 0
	},
	[LED_STATE_FADE_IN_AND_OUT] =
	{
		.animation_loop_iterations = 10,
		.animation_delay_ms = 0
	},
	[LED_STATE_TWINKLE] =
	{
		.animation_loop_iterations = 5,
		.animation_delay_ms = 0
	}
};


void animate_led_master_state_to_demo(animate_led_state_e* p_master_led_state, uint16_t* p_led_state_iteration)
{
	*p_master_led_state = MASTER_LED_STATE_DEMO;
	*p_led_state_iteration = 0;
}


void animate_led_master_state_to_fixed(animate_led_state_e* p_master_led_state, led_state_e* p_led_state, uint16_t* p_led_state_iteration)
{
    *p_master_led_state = MASTER_LED_STATE_FIXED;
    *p_led_state = LED_STATE_FIRST; // set first state
    *p_led_state_iteration = 0;
}


void animate_led_random_state(led_state_e* p_led_state)
{
	led_state_e rand_state = (led_state_e)(random_num(0, NUM_LED_STATES));

    if (*p_led_state == rand_state)
    {
        if (LED_STATE_LAST == *p_led_state) rand_state = (led_state_e)(rand_state - 1);
        else *p_led_state = (led_state_e)(rand_state + 1);
    }
}

void animate_led_adjust_state(led_state_e* p_led_state)
{
    if (LED_STATE_LAST == *p_led_state)
    {
        *p_led_state = LED_STATE_FIRST;
    }
    else
	{
    	*p_led_state = *p_led_state + 1;
	}
}


void animate_led_reset_state(led_state_e* p_led_state)
{
	*p_led_state = LED_STATE_FIRST;
}


uint8_t* animate_led_wheel(uint8_t wheel_pos)
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


/**
 * @brief   Write data stored in `gp_ws28128b_strip` array to the strip
 * @param   strip_mask - the strip to write to
 * @return  void
 */
void animate_led_show_strip(const strip_mask_t strip_mask)
{
    if (STRIP_NUM_1 & strip_mask)
    {
        ws2812b_show_strip_one();
    }
    if (STRIP_NUM_2 & strip_mask)
    {
        ws2812b_show_strip_two();
    }
    if (STRIP_NUM_3 & strip_mask)
    {
        ws2812b_show_strip_three();
    }
}


void animate_led_set_pixel(const strip_mask_t mask, const uint16_t pixel, const uint8_t red, const uint8_t green,
                           const uint8_t blue)
{
    if (STRIP_NUM_1 & mask)
    {
		if (ws2812_pixel_is_in_strip_range(STRIP_NUM_1, pixel))
		{
			 ws2812b_set_led(STRIP_NUM_1, pixel, red, green, blue);
		}
    }
    if (STRIP_NUM_2 & mask)
    {
		if (ws2812_pixel_is_in_strip_range(STRIP_NUM_2, pixel))
		{
			 ws2812b_set_led(STRIP_NUM_2, pixel, red, green, blue);
		}
    }
    if (STRIP_NUM_3 & mask)
    {
		if (ws2812_pixel_is_in_strip_range(STRIP_NUM_3, pixel))
		{
			 ws2812b_set_led(STRIP_NUM_3, pixel, red, green, blue);
		}
    }
}


void animate_led_set_all_pixels(const strip_mask_t mask, const uint8_t red, const uint8_t green, const uint8_t blue)
{
    uint16_t strip_size = 0;

    if (STRIP_NUM_1 & mask)
    {
		strip_size = ws2812_get_strip_size(STRIP_NUM_1);
		for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(STRIP_NUM_1, yyy, red, green, blue);
    }
    if (STRIP_NUM_2 & mask)
    {
		strip_size = ws2812_get_strip_size(STRIP_NUM_2);
		for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(STRIP_NUM_2, yyy, red, green, blue);
    }
    if (STRIP_NUM_3 & mask)
    {
		strip_size = ws2812_get_strip_size(STRIP_NUM_3);
		for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(STRIP_NUM_3, yyy, red, green, blue);
    }
    animate_led_show_strip(mask);
}


void animate_led_solid_custom_color(const strip_mask_t mask, const color_hex_code_e color)
{
    uint8_t color_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color, color_rgb);
    animate_led_set_all_pixels(mask, color_rgb[offsetof(ws2812b_led_t, red)], \
    		color_rgb[offsetof(ws2812b_led_t, green)],
			color_rgb[offsetof(ws2812b_led_t, blue)]);
    animate_led_show_strip(mask);
}


/**
 * @brief   Set all pixels to black and show the strips
 * @param   void
 * @return  void
 * @note    This function will set `gp_ws28128b_strip` array and write it to the strip(s).
 */
void animate_led_turn_all_pixels_off(void)
{
	animate_led_set_all_pixels((strip_mask_t)STRIP_ALL_SET, 0, 0, 0);
}


void animate_led_only_spell_word(const strip_mask_t mask, const color_hex_code_e color,
                                 const uint16_t time_ms)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t color_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color, color_rgb);
	for (int iii = 0; iii < strip_size; iii++)
	{
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_rgb[offsetof(ws2812b_led_t, red)],
            		&color_rgb[offsetof(ws2812b_led_t, green)],
					&color_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        animate_led_set_pixel(mask, iii,
        		color_rgb[offsetof(ws2812b_led_t, red)],
				color_rgb[offsetof(ws2812b_led_t, green)],
				color_rgb[offsetof(ws2812b_led_t, blue)]);
        animate_led_show_strip(mask);
 		pdMS_TO_TICKS(time_ms / task_led_ctrl_speed());
	}
}


void animate_led_fade_in_fade_out(const strip_mask_t mask, const color_hex_code_e color)
{
    float r, g, b;
    uint8_t color_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color, color_rgb);
    for (int iii = 0; iii < 256; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_rgb[offsetof(ws2812b_led_t, red)],
            		&color_rgb[offsetof(ws2812b_led_t, green)],
					&color_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        r = (iii / 256.0) * color_rgb[offsetof(ws2812b_led_t, red)];
        g = (iii / 256.0) * color_rgb[offsetof(ws2812b_led_t, green)];
        b = (iii / 256.0) * color_rgb[offsetof(ws2812b_led_t, blue)];
        animate_led_set_all_pixels(mask, r, g, b);
    }
    for (int iii = 255; iii >= 0; iii = iii-2)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_rgb[offsetof(ws2812b_led_t, red)],
            		&color_rgb[offsetof(ws2812b_led_t, green)],
					&color_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        r = (iii / 256.0) * color_rgb[offsetof(ws2812b_led_t, red)];
        g = (iii / 256.0) * color_rgb[offsetof(ws2812b_led_t, green)];
        b = (iii / 256.0) * color_rgb[offsetof(ws2812b_led_t, blue)];
        animate_led_set_all_pixels(mask, r, g, b);
    }
}


void animate_led_strobe(const strip_mask_t mask, const color_hex_code_e color,
                        const uint16_t animate_led_strobe_count, const uint16_t flash_delay, const uint16_t end_pause)
{
    uint8_t color_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color, color_rgb);
    for (int iii = 0; iii < animate_led_strobe_count; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_rgb[offsetof(ws2812b_led_t, red)], &color_rgb[offsetof(ws2812b_led_t, green)], &color_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        animate_led_set_all_pixels(mask, (color_rgb[offsetof(ws2812b_led_t, red)]),
                                   (color_rgb[offsetof(ws2812b_led_t, green)]),
                                   (color_rgb[offsetof(ws2812b_led_t, blue)]));
        animate_led_show_strip(mask);
        pdMS_TO_TICKS(flash_delay);
        animate_led_set_all_pixels(mask, 0, 0, 0);
        animate_led_show_strip(mask);
        pdMS_TO_TICKS(flash_delay);
    }
    pdMS_TO_TICKS(end_pause);
}


void animate_led_twinkle(const strip_mask_t mask, const color_hex_code_e color, const uint16_t count,
                         const uint16_t speed_delay, const bool only_one)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t color_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color, color_rgb);
    for (int iii = 0; iii < count; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_rgb[offsetof(ws2812b_led_t, red)],
            		&color_rgb[offsetof(ws2812b_led_t, green)],
					&color_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        animate_led_set_pixel(mask, random_num(0, strip_size),
                              (color_rgb[offsetof(ws2812b_led_t, red)]),
                              (color_rgb[offsetof(ws2812b_led_t, green)]),
                              (color_rgb[offsetof(ws2812b_led_t, blue)]));
        animate_led_show_strip(mask);
        pdMS_TO_TICKS(speed_delay / task_led_ctrl_speed());
        if (only_one) animate_led_set_all_pixels(mask, 0, 0, 0);
    }

    //pdMS_TO_TICKS(speed_delay / task_led_ctrl_speed());
}


void animate_led_twinkle_random(const strip_mask_t mask, const uint16_t count,
                                const uint16_t speed_delay, const bool only_one)
{
    animate_led_set_all_pixels(mask, 0, 0, 0);
    uint8_t dummy_red, dummy_green, dummy_blue; // not used but not worth creating a unique function IMO
    for (int iii = 0; iii < count; iii++)
    {
        if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
        animate_led_set_pixel(mask, random_num(0, g_max_strip_length),
                              random_num(0, 255), random_num(0, 255), random_num(0, 255));
        animate_led_show_strip(mask);
        pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
        if (only_one) animate_led_set_all_pixels(mask, 0, 0, 0);
    }
}


void animate_led_sparkle_only_random_color(const strip_mask_t mask, const bool fill,
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
		animate_led_set_pixel(mask, pix, random_num(0, 255), random_num(0, 255), random_num(0, 255));
		animate_led_show_strip(mask);
        pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
		if (!fill) animate_led_set_pixel(mask, pix, 0, 0, 0);
	}
}


void animate_led_sparkle_random_color(const strip_mask_t mask, const bool fill,
                                      const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    int pix = random_num(0, strip_size);
    animate_led_set_pixel(mask, pix, random_num(0, 255), random_num(0, 255), random_num(0, 255));
    animate_led_show_strip(mask);
    pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
    if (!fill) animate_led_set_pixel(mask, pix, 0, 0, 0);
}


void animate_led_sparkle(const strip_mask_t mask, const color_hex_code_e color,
                         const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t color_sparkle_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color, color_sparkle_rgb);
    uint16_t pix = random_num(0, strip_size);
    animate_led_set_pixel(mask, pix,
                          (color_sparkle_rgb[offsetof(ws2812b_led_t, red)]),
                          (color_sparkle_rgb[offsetof(ws2812b_led_t, green)]),
                          (color_sparkle_rgb[offsetof(ws2812b_led_t, blue)]));
    animate_led_show_strip(mask);
    pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
    animate_led_set_pixel(mask, pix, 0, 0, 0);
}


void animate_led_running_lights(const strip_mask_t mask, const color_hex_code_e color)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t color_running_lights_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(mask, color_running_lights_rgb);
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
            animate_led_set_pixel(mask, iii,
                                  ((sin(iii + pos) * 127 + 128) / 255) * (color_running_lights_rgb[offsetof(ws2812b_led_t, red)]),
                                  ((sin(iii + pos) * 127 + 128) / 255) * (color_running_lights_rgb[offsetof(ws2812b_led_t, green)]),
                                  ((sin(iii + pos) * 127 + 128) / 255) * (color_running_lights_rgb[offsetof(ws2812b_led_t, blue)]));
        }
        animate_led_show_strip(mask);
        pdMS_TO_TICKS(100 / task_led_ctrl_speed()); // TODO remove the magic number here!!!
    }
}


void animate_led_rainbow_cycle(const strip_mask_t mask, const uint16_t speed_delay)
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
            c = animate_led_wheel(((iii * 256 / strip_size) + jjj) & 255);
            animate_led_set_pixel(mask, iii, *c, *(c + 1), *(c + 2));
        }
        animate_led_show_strip(mask);
        if (LED_SPEED_10X == task_led_ctrl_speed()) pdMS_TO_TICKS(0);
        else pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
    }
}


void animate_led_theater_chase(const strip_mask_t mask, const color_hex_code_e color,
                               const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t color_theater_chase_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color, color_theater_chase_rgb);
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
                animate_led_set_pixel(mask, iii + qqq,
                                      (color_theater_chase_rgb[offsetof(ws2812b_led_t, red)]),
                                      (color_theater_chase_rgb[offsetof(ws2812b_led_t, green)]),
                                      (color_theater_chase_rgb[offsetof(ws2812b_led_t, blue)]));
            }
            animate_led_show_strip(mask);
            if (task_button_press_interrupt_occurred())
            {
                if (task_button_press_check_interrupts(&color_theater_chase_rgb[offsetof(ws2812b_led_t, red)], &color_theater_chase_rgb[offsetof(ws2812b_led_t, green)], &color_theater_chase_rgb[offsetof(ws2812b_led_t, blue)]))
                {
                    return;
                }
            }
            pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
            for (int iii = 0; iii < strip_size; iii += 3) animate_led_set_pixel(mask, iii + qqq, 0, 0, 0); // turn every third pixel off
        }
    }
}


void animate_led_theater_chase_rainbow(const strip_mask_t mask, const uint16_t speed_delay)
{
	uint8_t dummy_red, dummy_green, dummy_blue;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
    uint8_t *c;
    for (int jjj = 0; jjj < 256; jjj++) // cycel all 256 colors in the animate_led_wheel
    {
        for (int qqq = 0; qqq < 3; qqq++)
        {
            if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
            for (int iii = 0; iii < strip_size; iii += 3)
            {
                if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
                c = animate_led_wheel((iii + jjj) % 255);
                animate_led_set_pixel(mask, iii + qqq, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            animate_led_show_strip(mask);
            pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
            for (int iii = 0; iii < strip_size; iii += 3) animate_led_set_pixel(mask, iii + qqq, 0, 0, 0); // turn every third pixel off
        }
    }
}


//void animate_led_twinkle_multiple_colors(const strip_mask_t mask_twinkle, const uint32_t* color_array,
//                                         const uint16_t count, const uint16_t speed_delay, const bool only_one)
//{
//	strip_num_e active_strip = STRIP_NUM_1;
//	strip_num_e pre_strip = STRIP_NUM_1;
//	uint8_t num_active_strips = 0;
//	strip_num_e active_strip_array[NUM_STRIPS] = {STRIP_NONE};
//    uint8_t color_twinkle_rgb[sizeof(ws2812b_led_t)] = {0};
//    // for the multiple color case.  Drive the LEDs based on the most amount of pixels
//    // on a given strip.
//
//	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
//	{
//		active_strip = ws2812_get_next_active_strip(mask_twinkle, pre_strip);
//		if ((active_strip != STRIP_BIT_NO_MORE_SET) && (active_strip != (1 << (NUM_STRIPS - 1))))
//		{
//			pre_strip = active_strip + 1;
//		}
//		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
//		num_active_strips++;
//		active_strip_array[iii] = active_strip;
//	}
//	for (int iii = 0; iii < count; iii++)
//    {
//	    if (task_button_press_interrupt_occurred())
//        {
//            if (task_button_press_check_interrupts(&color_twinkle_rgb[offsetof(ws2812b_led_t, red)], &color_twinkle_rgb[offsetof(ws2812b_led_t, green)], &color_twinkle_rgb[offsetof(ws2812b_led_t, blue)]))
//            {
//                return;
//            }
//        }
//	    for (int yyy = 0; yyy < num_active_strips; yyy++)
//		{
//            color_led_hex_to_rgb(color_array[yyy], color_twinkle_rgb);
//			animate_led_set_pixel(active_strip_array[yyy], random_num(0,
//			                ws2812_get_strip_size(active_strip_array[yyy])),
//			                (color_twinkle_rgb[offsetof(ws2812b_led_t, red)]),
//			                (color_twinkle_rgb[offsetof(ws2812b_led_t, green)]),
//			                (color_twinkle_rgb[offsetof(ws2812b_led_t, blue)]));
//			animate_led_show_strip(mask_twinkle);
//		}
//        if (only_one) animate_led_set_all_pixels(mask_twinkle, 0, 0, 0);
//    }
//	pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
//}
//
//
///**
// * @brief   Execute spell animation on `mask_spell` strip(s).  Execute sparkle animationn on `mask_sparkle` strip(s).
// * @param   mask_spell strip(s) to show spell animation
// * @param   mask_sparkle strip(s) to show sparkle animation
// * @param   color color to display on spell animation strip(s)
// * @param   fill if true every pixel remains lit after set in mask_sparkle strip(s) else pixel off after turned on
// * @param   speed_delay speed to delay between each pixel turn on
// * @return  void
// */
//void animate_led_spell_and_sparkle(const strip_mask_t mask_spell, const strip_mask_t mask_sparkle,
//                                   const color_hex_code_e color_spell, const bool fill, const uint16_t speed_delay)
//{
//	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_spell); // this makes more sense... SRW
//    uint8_t color_spell_rgb[sizeof(ws2812b_led_t)] = {0};
//    color_led_hex_to_rgb(color_spell, color_spell_rgb);
//	if (!fill) animate_led_set_all_pixels(mask_sparkle, 0, 0, 0);
//	for (int iii = 0; iii < strip_size; iii++)
//	{
//        if (task_button_press_interrupt_occurred())
//        {
//            if (task_button_press_check_interrupts(&color_spell_rgb[offsetof(ws2812b_led_t, red)], &color_spell_rgb[offsetof(ws2812b_led_t, green)], &color_spell_rgb[offsetof(ws2812b_led_t, blue)]))
//            {
//                return;
//            }
//        }
//        animate_led_sparkle_random_color(mask_sparkle, fill, 0);
//        animate_led_set_pixel(mask_spell, iii,
//                              color_spell_rgb[offsetof(ws2812b_led_t, red)],
//                              color_spell_rgb[offsetof(ws2812b_led_t, green)],
//                              color_spell_rgb[offsetof(ws2812b_led_t, blue)]);
//		animate_led_show_strip(mask_sparkle | mask_spell);
//		pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
//	}
//}
//
//
///**
// * @brief   Execute spell animation on `mask_spell` strip(s).  Execute solid animationn on `mask_solid_color` strip(s).
// * @param   mask_spell strip(s) to show spell animation
// * @param   mask_sparkle strip(s) to show solid color animation
// * @param   color color to display on spell animation strip(s)
// * @param   fill if true every pixel remains lit after set in mask_sparkle strip(s) else pixel off after turned on
// * @param   speed_delay speed to delay between each pixel turn on
// * @return  void
// */
//void animate_led_spell_and_solid_color(const strip_mask_t mask_spell, const strip_mask_t mask_solid,
//                                       const color_hex_code_e color_spell, const color_hex_code_e color_solid,
//                                       const uint16_t speed_delay)
//{
//	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_spell); // this makes more sense... SRW
//	uint8_t color_spell_rgb[sizeof(ws2812b_led_t)] = {0};
//    color_led_hex_to_rgb(color_spell, color_spell_rgb);
//	//task_led_ctrl_color_random();
//	animate_led_solid_custom_color(mask_solid, color_solid);
//	for (int iii = 0; iii < strip_size; iii++)
//	{
//        if (task_button_press_interrupt_occurred())
//        {
//            if (task_button_press_check_interrupts(&color_spell_rgb[offsetof(ws2812b_led_t, red)], &color_spell_rgb[offsetof(ws2812b_led_t, green)], &color_spell_rgb[offsetof(ws2812b_led_t, blue)]))
//            {
//                return;
//            }
//        }
//        animate_led_set_pixel(mask_spell, iii,
//                              color_spell_rgb[offsetof(ws2812b_led_t, red)],
//                              color_spell_rgb[offsetof(ws2812b_led_t, green)],
//                              color_spell_rgb[offsetof(ws2812b_led_t, blue)]);
//		animate_led_show_strip(mask_spell | mask_solid);
//		pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
//	}
//}
//
//
//void animate_led_spell_word_multiple_colors(const strip_mask_t mask_spell, const color_hex_code_e* color_array,
//                                            const uint16_t speed_delay)
//{
//	strip_bit_e active_strip = STRIP_NUM_1;
//	strip_bit_e pre_strip = STRIP_NUM_1;
//	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_spell);
//	uint8_t num_active_strips = 0;
//	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
//    uint8_t color_spell_rgb[sizeof(ws2812b_led_t)] = {0};
//	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
//	{
//		active_strip = ws2812_get_next_active_strip(mask_spell, pre_strip);
//		if ((active_strip != STRIP_BIT_NO_MORE_SET) && (active_strip != (1 << (NUM_STRIPS - 1))))
//		{
//			pre_strip = active_strip + 1;
//		}
//		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
//		num_active_strips++;
//		active_strip_array[iii] = active_strip;
//	}
//	for (int iii = 0; iii < strip_size; iii++)
//	{
//		for (int yyy = 0; yyy < num_active_strips; yyy++)
//		{
//		    color_led_hex_to_rgb(color_array[yyy], color_spell_rgb);
//	        animate_led_set_pixel(active_strip_array[yyy], iii,
//	                              color_spell_rgb[offsetof(ws2812b_led_t, red)],
//	                              color_spell_rgb[offsetof(ws2812b_led_t, green)],
//	                              color_spell_rgb[offsetof(ws2812b_led_t, blue)]);
//		}
//		animate_led_show_strip(mask_spell);
//		pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
//	}
//}
//
//
//void animate_led_fade_in_fade_out_multiple_colors(const strip_mask_t strip_mask, const uint32_t* color_array)
//{
//    // interrupts not handled yet!
//	strip_bit_e active_strip = STRIP_NUM_1;
//	strip_bit_e pre_strip = STRIP_NUM_1;
//	uint8_t num_active_strips = 0;
//	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
//    uint8_t color_rgb[sizeof(ws2812b_led_t)] = {0};
//	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
//	{
//		active_strip = ws2812_get_next_active_strip(strip_mask, pre_strip);
//		if ((active_strip != STRIP_BIT_NO_MORE_SET) && (active_strip != (1 << (NUM_STRIPS - 1))))
//		{
//			pre_strip = active_strip + 1;
//		}
//		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
//		num_active_strips++;
//		active_strip_array[iii] = active_strip;
//	}
//    for (int i = 0; i < 256; i+=5)
//    {
//    	for (int yyy = 0; yyy < num_active_strips; yyy++)
//		{
//            color_led_hex_to_rgb(color_array[yyy], color_rgb);
//            animate_led_set_all_pixels(active_strip_array[yyy],
//                                       (color_rgb[offsetof(ws2812b_led_t, red)]) * (i / 256.0),
//                                       (color_rgb[offsetof(ws2812b_led_t, green)]) * (i / 256.0),
//                                       (color_rgb[offsetof(ws2812b_led_t, blue)]) * (i / 256.0));
//		}
//        if (task_button_press_interrupt_occurred())
//        {
//            if (task_button_press_check_interrupts(&color_rgb[offsetof(ws2812b_led_t, red)], &color_rgb[offsetof(ws2812b_led_t, green)], &color_rgb[offsetof(ws2812b_led_t, blue)]))
//            {
//                return;
//            }
//        }
//    }
//    for (int i = 255; i >= 0; i -= 5)
//    {
//    	for (int yyy = 0; yyy < num_active_strips; yyy++)
//		{
//            color_led_hex_to_rgb(color_array[yyy], color_rgb);
//            animate_led_set_all_pixels(active_strip_array[yyy],
//                                       (color_rgb[offsetof(ws2812b_led_t, red)]) * (i / 256.0),
//                                       (color_rgb[offsetof(ws2812b_led_t, green)]) * (i / 256.0),
//                                       (color_rgb[offsetof(ws2812b_led_t, blue)]) * (i / 256.0));
//		}
//        if (task_button_press_interrupt_occurred())
//        {
//            if (task_button_press_check_interrupts(&color_rgb[offsetof(ws2812b_led_t, red)], &color_rgb[offsetof(ws2812b_led_t, green)], &color_rgb[offsetof(ws2812b_led_t, blue)]))
//            {
//                return;
//            }
//        }
//    }
//}
//
//
///**
// * @brief   Write solid color data to the strip(s)
// * @param   strip_mask - the strip to write to
// * @param   color_array - the color to write to the strip
// * @return  void
// * @note    The least significant bit set in strip_mask will be set to the color defined
// *          at the first entry in `color_array`.
// */
//void animate_led_multiple_solid_custom_colors(const strip_mask_t mask_solid, const uint32_t* color_array)
//{
//    // not checking for interrupts in this function the solid color is too fast.  No way a user
//    // would be able to tell if caught or not.
//	strip_bit_e active_strip = STRIP_NUM_1;
//	strip_bit_e pre_strip = STRIP_NUM_1;
//	uint8_t num_active_strips = 0;
//	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
//    uint8_t color_solid_rgb[sizeof(ws2812b_led_t)] = {0};
//	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
//	{
//		active_strip = ws2812_get_next_active_strip(mask_solid, pre_strip);
//		if ((active_strip != STRIP_BIT_NO_MORE_SET) && (active_strip != (1 << (NUM_STRIPS - 1))))
//		{
//			pre_strip = active_strip + 1;
//		}
//		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
//		num_active_strips++;
//		active_strip_array[iii] = active_strip;
//	}
//	for (int yyy = 0; yyy < num_active_strips; yyy++)
//	{
//        color_led_hex_to_rgb(color_array[yyy], color_solid_rgb);
//		animate_led_set_all_pixels(active_strip_array[yyy],
//		                           (color_solid_rgb[offsetof(ws2812b_led_t, red)]),
//		                           (color_solid_rgb[offsetof(ws2812b_led_t, green)]),
//		                           (color_solid_rgb[offsetof(ws2812b_led_t, blue)]));
//	}
//}
//
//
//void animate_led_theater_chase_multiple_colors(const strip_mask_t mask, const uint32_t* color_array,
//                                               const uint16_t speed_delay)
//{
//	uint8_t red, green, blue;
//	strip_bit_e active_strip = STRIP_NUM_1;
//	strip_bit_e pre_strip = STRIP_NUM_1;
//	uint16_t strip_size = ws2812_led_get_max_strip_size(mask);
//	uint8_t num_active_strips = 0;
//	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
//    uint8_t color_theater_chase_rgb[sizeof(ws2812b_led_t)] = {0};
//	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
//	{
//		active_strip = ws2812_get_next_active_strip(mask, pre_strip);
//		if ((active_strip != STRIP_BIT_NO_MORE_SET) && (active_strip != (1 << (NUM_STRIPS - 1))))
//		{
//			pre_strip = active_strip + 1;
//		}
//		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
//		num_active_strips++;
//		active_strip_array[iii] = active_strip;
//	}
//	for (int jjj = 0; jjj < 100; jjj++)
//    {
//        for (int qqq = 0; qqq < 3; qqq++)
//        {
//            if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&red, &green, &blue)) return;
//            for (int iii = 0; iii < strip_size; iii += 3)
//            {
//            	for (int yyy = 0; yyy < num_active_strips; yyy++)
//				{
//                    color_led_hex_to_rgb(color_array[yyy], color_theater_chase_rgb);
//            	    animate_led_set_pixel(active_strip_array[yyy], iii + qqq,
//            	                          (color_theater_chase_rgb[offsetof(ws2812b_led_t, red)]),
//            	                          (color_theater_chase_rgb[offsetof(ws2812b_led_t, green)]),
//            	                          (color_theater_chase_rgb[offsetof(ws2812b_led_t, blue)]));
//				}
//            }
//            animate_led_show_strip(mask);
//            if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&red, &green, &blue)) return;
//            pdMS_TO_TICKS((float_t)speed_delay / task_led_ctrl_speed());
//            for (int iii = 0; iii < strip_size; iii += 3)
//            {
//            	for (int yyy = 0; yyy < num_active_strips; yyy++)
//				{
//					animate_led_set_pixel(active_strip_array[yyy], iii + qqq, 0, 0, 0);
//				}
//       		}
//        }
//    }
//}
