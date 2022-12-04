// SRW
#include <stdint.h>
#include <math.h>
#include "numbers.h"
#include "task_led_ctrl.h"
#include "animate_led.h"
#include "task_button_press.h"


extern uint32_t g_max_strip_length;
extern uint16_t g_all_strip_mask;


/**
 * @brief   Write data stored in `gp_ws28128b_strip` array to the strip
 * @param   strip_mask - the strip to write to
 * @return  void
 */
void animate_led_show_strip(const strip_mask_t strip_mask)
{
    ws2812b_show(strip_mask);
}


void animate_led_set_pixel(const strip_mask_t mask, const uint16_t pixel, const uint8_t red, const uint8_t green,
                           const uint8_t blue)
{
    if (STRIP_BIT_ALL_SET == mask)
    {
        for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
        {
            //offset = animate_led_get_strip_offset(strip_bit);
            if (ws2812_pixel_is_in_strip_range(strip_bit, pixel)) ws2812b_set_led(strip_bit, pixel, red, green, blue);
        }
    }
    else
    {
        for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
        {
            if (mask & strip_bit)
            {
                //offset = animate_led_get_strip_offset(strip_bit);
                if (ws2812_pixel_is_in_strip_range(strip_bit, pixel)) ws2812b_set_led(strip_bit, pixel, red, green, blue);
            }
        }
    }
    //animate_led_show_strip();
}


void animate_led_set_all_pixels(const strip_mask_t mask, const uint8_t red, const uint8_t green, const uint8_t blue)
{
    uint16_t strip_size = 0;
    if (mask == g_all_strip_mask)
    {
        for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
        {
            strip_size = ws2812_get_strip_size(strip_bit);
            //offset = animate_led_get_strip_offset(strip_bit);
            for (uint16_t iii = 0; iii < strip_size; iii++) ws2812b_set_led(strip_bit, iii, red, green, blue);
        }
    }
    else
    {
        for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
        {
            if (mask & strip_bit)
            {
                strip_size = ws2812_get_strip_size(strip_bit);
                for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(strip_bit, yyy, red, green, blue);
            }
        }
    }
    animate_led_show_strip(mask);
}


/**
 * @brief   Write solid color data to the strip(s)
 * @param   strip_mask - the strip to write to
 * @param   color_array - the color to write to the strip
 * @return  void
 * @note    The least significant bit set in strip_mask will be set to the color defined
 *          at the first entry in `color_array`.
 */
void animate_led_multiple_solid_custom_colors(const strip_mask_t mask_solid, const uint32_t* color_array)
{
    // not checking for interrupts in this function the solid color is too fast.  No way a user
    // would be able to tell if caught or not.
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
    uint8_t color_solid_rgb[sizeof(ws2812b_led_t)] = {0};
	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
	{
		active_strip = ws2812_get_next_active_strip(mask_solid, pre_strip);
		if ((active_strip != STRIP_BIT_NO_MORE_SET) && (active_strip != (1 << (NUM_STRIPS - 1))))
		{
			pre_strip = active_strip + 1;
		}
		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
		num_active_strips++;
		active_strip_array[iii] = active_strip;
	}
	for (int yyy = 0; yyy < num_active_strips; yyy++)
	{
        color_led_hex_to_rgb(color_array[yyy], color_solid_rgb);
		animate_led_set_all_pixels(active_strip_array[yyy],
		                           (color_solid_rgb[offsetof(ws2812b_led_t, red)]),
		                           (color_solid_rgb[offsetof(ws2812b_led_t, green)]),
		                           (color_solid_rgb[offsetof(ws2812b_led_t, blue)]));
	}
}


void animate_led_solid_custom_color(const strip_mask_t mask_solid, const color_hex_code_e color_spell)
{
    uint8_t color_solid_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color_spell, color_solid_rgb);
    animate_led_set_all_pixels(mask_solid, color_solid_rgb[offsetof(ws2812b_led_t, red)],
                               color_solid_rgb[offsetof(ws2812b_led_t, green)],
                               color_solid_rgb[offsetof(ws2812b_led_t, blue)]);
    animate_led_show_strip(mask_solid);
}


/**
 * @brief   Set all pixels to black and show the strips
 * @param   void
 * @return  void
 * @note    This function will set `gp_ws28128b_strip` array and write it to the strip(s).
 */
void animate_led_turn_all_pixels_off(void)
{
	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
}


/**
 * @brief   Execute spell animation on `mask_spell` strip(s).  Execute sparkle animationn on `mask_sparkle` strip(s).
 * @param   mask_spell strip(s) to show spell animation
 * @param   mask_sparkle strip(s) to show sparkle animation
 * @param   color color to display on spell animation strip(s)
 * @param   fill if true every pixel remains lit after set in mask_sparkle strip(s) else pixel off after turned on
 * @param   speed_delay speed to delay between each pixel turn on
 * @return  void
 */
void animate_led_spell_and_sparkle(const strip_mask_t mask_spell, const strip_mask_t mask_sparkle,
                                   const color_hex_code_e color_spell, const bool fill, const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_spell); // this makes more sense... SRW
    uint8_t color_spell_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color_spell, color_spell_rgb);
	if (!fill) animate_led_set_all_pixels(mask_sparkle, 0, 0, 0);
	for (int iii = 0; iii < strip_size; iii++)
	{
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_spell_rgb[offsetof(ws2812b_led_t, red)], &color_spell_rgb[offsetof(ws2812b_led_t, green)], &color_spell_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        animate_led_sparkle_random_color(mask_sparkle, fill, 0);
        animate_led_set_pixel(mask_spell, iii,
                              color_spell_rgb[offsetof(ws2812b_led_t, red)],
                              color_spell_rgb[offsetof(ws2812b_led_t, green)],
                              color_spell_rgb[offsetof(ws2812b_led_t, blue)]);
		animate_led_show_strip(mask_sparkle | mask_spell);
		task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
	}	
}


/**
 * @brief   Execute spell animation on `mask_spell` strip(s).  Execute solid animationn on `mask_solid_color` strip(s).
 * @param   mask_spell strip(s) to show spell animation
 * @param   mask_sparkle strip(s) to show solid color animation
 * @param   color color to display on spell animation strip(s)
 * @param   fill if true every pixel remains lit after set in mask_sparkle strip(s) else pixel off after turned on
 * @param   speed_delay speed to delay between each pixel turn on
 * @return  void
 */
void animate_led_spell_and_solid_color(const strip_mask_t mask_spell, const strip_mask_t mask_solid,
                                       const color_hex_code_e color_spell, const color_hex_code_e color_solid,
                                       const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_spell); // this makes more sense... SRW
	uint8_t color_spell_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color_spell, color_spell_rgb);
	//task_led_ctrl_color_random();
	animate_led_solid_custom_color(mask_solid, color_solid);
	for (int iii = 0; iii < strip_size; iii++)
	{
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_spell_rgb[offsetof(ws2812b_led_t, red)], &color_spell_rgb[offsetof(ws2812b_led_t, green)], &color_spell_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        animate_led_set_pixel(mask_spell, iii,
                              color_spell_rgb[offsetof(ws2812b_led_t, red)],
                              color_spell_rgb[offsetof(ws2812b_led_t, green)],
                              color_spell_rgb[offsetof(ws2812b_led_t, blue)]);
		animate_led_show_strip(mask_spell | mask_solid);
		task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
	}	
}


void animate_led_spell_word_multiple_colors(const strip_mask_t mask_spell, const color_hex_code_e* color_array,
                                            const uint16_t speed_delay)
{
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_spell);
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
    uint8_t color_spell_rgb[sizeof(ws2812b_led_t)] = {0};
	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
	{
		active_strip = ws2812_get_next_active_strip(mask_spell, pre_strip);
		if ((active_strip != STRIP_BIT_NO_MORE_SET) && (active_strip != (1 << (NUM_STRIPS - 1))))
		{
			pre_strip = active_strip + 1;
		}
		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
		num_active_strips++;
		active_strip_array[iii] = active_strip;
	}
	for (int iii = 0; iii < strip_size; iii++)
	{
		for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
		    color_led_hex_to_rgb(color_array[yyy], color_spell_rgb);
	        animate_led_set_pixel(active_strip_array[yyy], iii,
	                              color_spell_rgb[offsetof(ws2812b_led_t, red)],
	                              color_spell_rgb[offsetof(ws2812b_led_t, green)],
	                              color_spell_rgb[offsetof(ws2812b_led_t, blue)]);
		}
		animate_led_show_strip(mask_spell);
		task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
	}
}


void animate_led_only_spell_word(const strip_mask_t mask_spell, const color_hex_code_e color_spell,
                                 const uint16_t time_ms)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_spell);
    uint8_t color_spell_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color_spell, color_spell_rgb);
	for (int i = 0; i < strip_size; i++)
	{
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_spell_rgb[offsetof(ws2812b_led_t, red)], &color_spell_rgb[offsetof(ws2812b_led_t, green)], &color_spell_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        animate_led_set_pixel(mask_spell, i,
                              color_spell_rgb[offsetof(ws2812b_led_t, red)],
                              color_spell_rgb[offsetof(ws2812b_led_t, green)],
                              color_spell_rgb[offsetof(ws2812b_led_t, blue)]);
        animate_led_show_strip(mask_spell);
		task_led_ctrl_delay(time_ms / task_led_ctrl_speed());
	}
}


void animate_led_fade_in_fade_out_multiple_colors(const strip_mask_t strip_mask, const uint32_t* color_array)
{
    // interrupts not handled yet!
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
    uint8_t color_rgb[sizeof(ws2812b_led_t)] = {0};
	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
	{
		active_strip = ws2812_get_next_active_strip(strip_mask, pre_strip);
		if ((active_strip != STRIP_BIT_NO_MORE_SET) && (active_strip != (1 << (NUM_STRIPS - 1))))
		{
			pre_strip = active_strip + 1;
		}
		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
		num_active_strips++;
		active_strip_array[iii] = active_strip;
	}
    for (int i = 0; i < 256; i+=5)
    {
    	for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
            color_led_hex_to_rgb(color_array[yyy], color_rgb);
            animate_led_set_all_pixels(active_strip_array[yyy],
                                       (color_rgb[offsetof(ws2812b_led_t, red)]) * (i / 256.0),
                                       (color_rgb[offsetof(ws2812b_led_t, green)]) * (i / 256.0),
                                       (color_rgb[offsetof(ws2812b_led_t, blue)]) * (i / 256.0));
		}
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_rgb[offsetof(ws2812b_led_t, red)], &color_rgb[offsetof(ws2812b_led_t, green)], &color_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
    }
    for (int i = 255; i >= 0; i -= 5)
    {
    	for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
            color_led_hex_to_rgb(color_array[yyy], color_rgb);
            animate_led_set_all_pixels(active_strip_array[yyy],
                                       (color_rgb[offsetof(ws2812b_led_t, red)]) * (i / 256.0),
                                       (color_rgb[offsetof(ws2812b_led_t, green)]) * (i / 256.0),
                                       (color_rgb[offsetof(ws2812b_led_t, blue)]) * (i / 256.0));
		}
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_rgb[offsetof(ws2812b_led_t, red)], &color_rgb[offsetof(ws2812b_led_t, green)], &color_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
    }
}


void animate_led_fade_in_fade_out(const strip_mask_t mask_fade, const color_hex_code_e color_fade)
{
    float r, g, b;
    uint8_t color_fade_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color_fade, color_fade_rgb);
    for (int iii = 0; iii < 256; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_fade_rgb[offsetof(ws2812b_led_t, red)], &color_fade_rgb[offsetof(ws2812b_led_t, green)], &color_fade_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        r = (iii / 256.0) * color_fade_rgb[offsetof(ws2812b_led_t, red)];
        g = (iii / 256.0) * color_fade_rgb[offsetof(ws2812b_led_t, green)];
        b = (iii / 256.0) * color_fade_rgb[offsetof(ws2812b_led_t, blue)];
        animate_led_set_all_pixels(mask_fade, r, g, b);
    }
    for (int iii = 255; iii >= 0; iii = iii-2)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_fade_rgb[offsetof(ws2812b_led_t, red)], &color_fade_rgb[offsetof(ws2812b_led_t, green)], &color_fade_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        r = (iii / 256.0) * color_fade_rgb[offsetof(ws2812b_led_t, red)];
        g = (iii / 256.0) * color_fade_rgb[offsetof(ws2812b_led_t, green)];
        b = (iii / 256.0) * color_fade_rgb[offsetof(ws2812b_led_t, blue)];
        animate_led_set_all_pixels(mask_fade, r, g, b);
    }
}


void animate_led_strobe(const strip_mask_t mask_strobe, const color_hex_code_e color_strobe,
                        const uint16_t animate_led_strobe_count, const uint16_t flash_delay, const uint16_t end_pause)
{
    uint8_t color_strobe_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color_strobe, color_strobe_rgb);
    for (int iii = 0; iii < animate_led_strobe_count; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_strobe_rgb[offsetof(ws2812b_led_t, red)], &color_strobe_rgb[offsetof(ws2812b_led_t, green)], &color_strobe_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        animate_led_set_all_pixels(mask_strobe,
                                   (color_strobe_rgb[offsetof(ws2812b_led_t, red)]),
                                   (color_strobe_rgb[offsetof(ws2812b_led_t, green)]),
                                   (color_strobe_rgb[offsetof(ws2812b_led_t, blue)]));
        animate_led_show_strip(mask_strobe);
        task_led_ctrl_delay(flash_delay);
        animate_led_set_all_pixels(mask_strobe, 0, 0, 0);
        animate_led_show_strip(mask_strobe);
        task_led_ctrl_delay(flash_delay);
    }
    task_led_ctrl_delay(end_pause);
}


void animate_led_twinkle_multiple_colors(const strip_mask_t mask_twinkle, const uint32_t* color_array,
                                         const uint16_t count, const uint16_t speed_delay, const bool only_one)
{
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
    uint8_t color_twinkle_rgb[sizeof(ws2812b_led_t)] = {0};
	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
	{
		active_strip = ws2812_get_next_active_strip(mask_twinkle, pre_strip);
		if ((active_strip != STRIP_BIT_NO_MORE_SET) && (active_strip != (1 << (NUM_STRIPS - 1))))
		{
			pre_strip = active_strip + 1;
		}
		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
		num_active_strips++;
		active_strip_array[iii] = active_strip;
	}
	for (int iii = 0; iii < count; iii++)
    {
	    if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_twinkle_rgb[offsetof(ws2812b_led_t, red)], &color_twinkle_rgb[offsetof(ws2812b_led_t, green)], &color_twinkle_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
	    for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
            color_led_hex_to_rgb(color_array[yyy], color_twinkle_rgb);
			animate_led_set_pixel(active_strip_array[yyy], random_num(0,
			                ws2812_get_strip_size(active_strip_array[yyy])),
			                (color_twinkle_rgb[offsetof(ws2812b_led_t, red)]),
			                (color_twinkle_rgb[offsetof(ws2812b_led_t, green)]),
			                (color_twinkle_rgb[offsetof(ws2812b_led_t, blue)]));
			animate_led_show_strip(mask_twinkle);
		}
        if (only_one) animate_led_set_all_pixels(mask_twinkle, 0, 0, 0);
    }
	task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
}


void animate_led_twinkle(const strip_mask_t twinkle_mask, const color_hex_code_e color_twinkle, const uint16_t count,
                         const uint16_t speed_delay, const bool only_one)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(twinkle_mask);
    uint8_t color_twinkle_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color_twinkle, color_twinkle_rgb);
    for (int iii = 0; iii < count; iii++)
    {
        if (task_button_press_interrupt_occurred())
        {
            if (task_button_press_check_interrupts(&color_twinkle_rgb[offsetof(ws2812b_led_t, red)], &color_twinkle_rgb[offsetof(ws2812b_led_t, green)], &color_twinkle_rgb[offsetof(ws2812b_led_t, blue)]))
            {
                return;
            }
        }
        animate_led_set_pixel(twinkle_mask, random_num(0, strip_size),
                              (color_twinkle_rgb[offsetof(ws2812b_led_t, red)]),
                              (color_twinkle_rgb[offsetof(ws2812b_led_t, green)]),
                              (color_twinkle_rgb[offsetof(ws2812b_led_t, blue)]));
        animate_led_show_strip(twinkle_mask);
        task_led_ctrl_delay(speed_delay / task_led_ctrl_speed());
        if (only_one) animate_led_set_all_pixels(twinkle_mask, 0, 0, 0);
    }

    //task_led_ctrl_delay(speed_delay / task_led_ctrl_speed());
}


void animate_led_twinkle_random(const strip_mask_t mask_twinkle_random, const uint16_t count,
                                const uint16_t speed_delay, const bool only_one)
{
    animate_led_set_all_pixels(mask_twinkle_random, 0, 0, 0);
    uint8_t dummy_red, dummy_green, dummy_blue; // not used but not worth creating a unique function IMO
    for (int iii = 0; iii < count; iii++)
    {
        if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
        animate_led_set_pixel(mask_twinkle_random, random_num(0, g_max_strip_length),
                              random_num(0, 255), random_num(0, 255), random_num(0, 255));
        animate_led_show_strip(mask_twinkle_random);
        task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
        if (only_one) animate_led_set_all_pixels(mask_twinkle_random, 0, 0, 0);
    }
}


void animate_led_sparkle_only_random_color(const strip_mask_t mask_sparkle_random, const bool fill,
                                           const uint16_t speed_delay)
{
	float percent_to_fill = 0.7;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_sparkle_random);
	uint16_t num_active_leds = ws2812_get_num_active_animation_leds(mask_sparkle_random);
    uint8_t dummy_red, dummy_green, dummy_blue; // not used but not worth creating a unique function IMO
	for (uint16_t iii = 0; iii < (percent_to_fill * (float)num_active_leds); iii++)
	{
	    if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
		int pix = random_num(0, strip_size);
		animate_led_set_pixel(mask_sparkle_random, pix, random_num(0, 255), random_num(0, 255), random_num(0, 255));
		animate_led_show_strip(mask_sparkle_random);
        task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
		if (!fill) animate_led_set_pixel(mask_sparkle_random, pix, 0, 0, 0);
	}
}


void animate_led_sparkle_random_color(const strip_mask_t mask_sparkle_random, const bool fill,
                                      const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_sparkle_random);
    int pix = random_num(0, strip_size);
    animate_led_set_pixel(mask_sparkle_random, pix, random_num(0, 255), random_num(0, 255), random_num(0, 255));
    animate_led_show_strip(mask_sparkle_random);
    task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
    if (!fill) animate_led_set_pixel(mask_sparkle_random, pix, 0, 0, 0);
}


void animate_led_sparkle(const strip_mask_t mask_sparkle, const color_hex_code_e color_sparkle,
                         const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_sparkle);
    uint8_t color_sparkle_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color_sparkle, color_sparkle_rgb);
    uint16_t pix = random_num(0, strip_size);
    animate_led_set_pixel(mask_sparkle, pix,
                          (color_sparkle_rgb[offsetof(ws2812b_led_t, red)]),
                          (color_sparkle_rgb[offsetof(ws2812b_led_t, green)]),
                          (color_sparkle_rgb[offsetof(ws2812b_led_t, blue)]));
    animate_led_show_strip(mask_sparkle);
    task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
    animate_led_set_pixel(mask_sparkle, pix, 0, 0, 0);
}


void animate_led_running_lights(const strip_mask_t mask_running_lights, const color_hex_code_e color_running_lights)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_running_lights);
    uint8_t color_running_lights_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color_running_lights, color_running_lights_rgb);
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
            animate_led_set_pixel(mask_running_lights, iii,
                                  ((sin(iii + pos) * 127 + 128) / 255) * (color_running_lights_rgb[offsetof(ws2812b_led_t, red)]),
                                  ((sin(iii + pos) * 127 + 128) / 255) * (color_running_lights_rgb[offsetof(ws2812b_led_t, green)]),
                                  ((sin(iii + pos) * 127 + 128) / 255) * (color_running_lights_rgb[offsetof(ws2812b_led_t, blue)]));
        }
        animate_led_show_strip(mask_running_lights);
        task_led_ctrl_delay(100 / task_led_ctrl_speed()); // TODO remove the magic number here!!!
    }
}


void animate_led_rainbow_cycle(const strip_mask_t mask_rainbow_cycle, const uint16_t speed_delay)
{
	uint8_t dummy_red, dummy_green, dummy_blue;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_rainbow_cycle);
    uint8_t *c;
    uint16_t iii, jjj;
    for (jjj = 0; jjj < 256 * 5; jjj++)
    {
        if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
        for (iii = 0; iii < strip_size; iii++)
        {
            if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
            c = animate_led_wheel(((iii * 256 / strip_size) + jjj) & 255);
            animate_led_set_pixel(mask_rainbow_cycle, iii, *c, *(c + 1), *(c + 2));
        }
        animate_led_show_strip(mask_rainbow_cycle);
        if (LED_SPEED_10X == task_led_ctrl_speed()) task_led_ctrl_delay(0);
        else task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
    }
}


uint8_t* animate_led_wheel(uint8_t wheel_pos)
{
    static uint8_t c[3];
    if (wheel_pos < 85)
    {
        c[0] = wheel_pos * 3;
        c[1] = 255 - wheel_pos * 3; 
        c[2] = 0;
    }
    else if(wheel_pos < 170)
    {
        wheel_pos -= 85;
        c[0] = 255 - wheel_pos * 3;
        c[1] = 0;
        c[2] = wheel_pos * 3;
    }
    else
    {
        wheel_pos -= 170;
        c[0] = 0;
        c[1] = wheel_pos * 3; 
        c[2] = 255 - wheel_pos * 3;
    }
    return c;
}

    
void animate_led_theater_chase_multiple_colors(const strip_mask_t mask_theater_chase, const uint32_t* color_array,
                                               const uint16_t speed_delay)
{
	uint8_t red, green, blue; 
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_theater_chase);
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
    uint8_t color_theater_chase_rgb[sizeof(ws2812b_led_t)] = {0};
	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
	{
		active_strip = ws2812_get_next_active_strip(mask_theater_chase, pre_strip);
		if ((active_strip != STRIP_BIT_NO_MORE_SET) && (active_strip != (1 << (NUM_STRIPS - 1))))
		{
			pre_strip = active_strip + 1;
		}
		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
		num_active_strips++;
		active_strip_array[iii] = active_strip;
	}
	for (int jjj = 0; jjj < 100; jjj++)
    {
        for (int qqq = 0; qqq < 3; qqq++)
        {
            if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&red, &green, &blue)) return;
            for (int iii = 0; iii < strip_size; iii += 3)
            {
            	for (int yyy = 0; yyy < num_active_strips; yyy++)
				{
                    color_led_hex_to_rgb(color_array[yyy], color_theater_chase_rgb);
            	    animate_led_set_pixel(active_strip_array[yyy], iii + qqq,
            	                          (color_theater_chase_rgb[offsetof(ws2812b_led_t, red)]),
            	                          (color_theater_chase_rgb[offsetof(ws2812b_led_t, green)]),
            	                          (color_theater_chase_rgb[offsetof(ws2812b_led_t, blue)]));
				}
            }
            animate_led_show_strip(mask_theater_chase);
            if (task_button_press_interrupt_occurred()) if (task_button_press_check_interrupts(&red, &green, &blue)) return;
            task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
            for (int iii = 0; iii < strip_size; iii += 3)
            {
            	for (int yyy = 0; yyy < num_active_strips; yyy++)
				{
					animate_led_set_pixel(active_strip_array[yyy], iii + qqq, 0, 0, 0);
				}
       		}
        }
    }
}


void animate_led_theater_chase(const strip_mask_t mask_theater_chase, const color_hex_code_e color_theater_chase,
                               const uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_theater_chase);
    uint8_t color_theater_chase_rgb[sizeof(ws2812b_led_t)] = {0};
    color_led_hex_to_rgb(color_theater_chase, color_theater_chase_rgb);
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
                animate_led_set_pixel(mask_theater_chase, iii,
                                      (color_theater_chase_rgb[offsetof(ws2812b_led_t, red)]),
                                      (color_theater_chase_rgb[offsetof(ws2812b_led_t, green)]),
                                      (color_theater_chase_rgb[offsetof(ws2812b_led_t, blue)]));
            }
            animate_led_show_strip(mask_theater_chase);
            if (task_button_press_interrupt_occurred())
            {
                if (task_button_press_check_interrupts(&color_theater_chase_rgb[offsetof(ws2812b_led_t, red)], &color_theater_chase_rgb[offsetof(ws2812b_led_t, green)], &color_theater_chase_rgb[offsetof(ws2812b_led_t, blue)]))
                {
                    return;
                }
            }
            task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
            for (int iii = 0; iii < strip_size; iii += 3) animate_led_set_pixel(mask_theater_chase, iii + qqq, 0, 0, 0); // turn everty third pixel off
        }
    }
}


void animate_led_theater_chase_rainbow(const strip_mask_t mask_theater_chase, const uint16_t speed_delay)
{
	uint8_t dummy_red, dummy_green, dummy_blue;
	uint16_t strip_size = ws2812_led_get_max_strip_size(mask_theater_chase);
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
                animate_led_set_pixel(mask_theater_chase, iii + qqq, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            animate_led_show_strip(mask_theater_chase);
            task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
            for (int iii = 0; iii < strip_size; iii += 3) animate_led_set_pixel(mask_theater_chase, iii + qqq, 0, 0, 0); // turn every third pixel off
        }
    }
}


// future
//void animate_led_bouncing_balls(strip_mask_t strip_mask, color_hex_code_e color, int ball_count)
//{
//    uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
//    float gravity = -9.81;
//    int start_height = 1;
//    float height[ball_count];
//    float impact_velocity_start = sqrt(-2 * gravity * start_height);
//    float impact_velocity[ball_count];
//    float time_since_last_bounce[ball_count];
//    int pos[ball_count];
//    long clock_time_since_last_bounce[ball_count];
//    float dampening[ball_count];
//    uint8_t red, green, blue;
//    red = ((color & 0xFF0000) >> 16);
//    green = ((color & 0x00FF00) >> 8);
//    blue = (color & 0x0000FF);
//    for (int i = 0; i < ball_count; i++)
//    {
//        clock_time_since_last_bounce[i] = millis();
//        height[i] = start_height;
//        pos[i] = 0;
//        impact_velocity[i] = impact_velocity_start;
//        time_since_last_bounce[i] = 0;
//        dampening[i] = 0.90 - (float)i / pow(ball_count, 2);
//    }
//
//    for (int i = 0; i < ball_count; i++)
//    {
//        time_since_last_bounce[i] = millis() - clock_time_since_last_bounce[i];
//        height[i] = 0.5 * gravity * pow(time_since_last_bounce[i] / 1000, 2.0) + impact_velocity[i] * time_since_last_bounce[i] / 1000;
//        if (height[i] < 0)
//        {
//            height[i] = 0;
//            impact_velocity[i] = dampening[i] * impact_velocity[i];
//            clock_time_since_last_bounce[i] = millis();
//            if (impact_velocity[i] < 0.01)
//            {
//                impact_velocity[i] = impact_velocity_start;
//            }
//        }
//        pos[i] = round(height[i] * (strip_size - 1) / start_height);
//    }
//    for (int i = 0; i < ball_count; i++)
//    {
//        animate_led_set_pixel(strip_mask, pos[i], red, green, blue);
//    }
//    animate_led_show_strip(strip_mask);
//    animate_led_set_all_pixels(strip_mask, 0, 0, 0);
//}
//
//
//void animate_led_meteor_rain(strip_mask_t strip_mask, color_hex_code_e color, uint8_t meteor_size, uint8_t meteor_trail_decay, bool meteor_random_decay, int speed_delay)
//{
//    // interrupts not handled yet!
//    //uint16_t offset = 0;
//    uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
//    uint8_t red, green, blue;
//    red = ((color & 0xFF0000) >> 16);
//    green = ((color & 0x00FF00) >> 8);
//    blue = (color & 0x0000FF);
//    animate_led_set_all_pixels(strip_mask, 0, 0, 0);
//    for(int i = 0; i < strip_size + 50; i++) // 50 arbitrarily chosen SRW
//    {
//        for (int j = 0; j < strip_size; j++)
//        {
//            if ((!meteor_random_decay) || (random_num(0, 10) > 5))
//            {
//                if (strip_mask == g_all_strip_mask)
//                {
//                    for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
//                    {
//                        //offset = animate_led_get_strip_offset(strip_bit);
//                        if (ws2812_pixel_is_in_strip_range(strip_bit, j)) ;//animate_led_fade_to_black(strip_mask, j, meteor_trail_decay);
//                    }
//                }
//                else
//                {
//                    for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = strip_bit + 1)
//                    {
//                        if (strip_mask & strip_bit)
//                        {
//                            //offset = animate_led_get_strip_offset(strip_bit);
//                            if (ws2812_pixel_is_in_strip_range(strip_bit, j)) animate_led_fade_to_black(strip_mask, j, meteor_trail_decay);
//                        }
//                    }
//                }
//            }
//        }
//        for (int j = 0; j < meteor_size; j++)
//        {
//            if ((i - j < strip_size) && (i - j >= 0))
//            {
//                if (strip_mask == g_all_strip_mask)
//                {
//                    for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
//                    {
//                        //offset = animate_led_get_strip_offset(strip_bit);
//                        if (ws2812_pixel_is_in_strip_range(strip_bit, i - j)) animate_led_set_pixel(strip_mask, i - j, red, green, blue);
//                    }
//                }
//                else
//                {
//                    for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = strip_bit + 1)
//                    {
//                        if (strip_mask & strip_bit)
//                        {
//                            //offset = animate_led_get_strip_offset(strip_bit);
//                            if (ws2812_pixel_is_in_strip_range(strip_bit, i - j)) animate_led_set_pixel(strip_mask, i - j, red, green, blue);
//                        }
//                    }
//                }
//            }
//        }
////        if (task_button_press_check_interrupts(&speed_delay, &red, &green, &blue))
////        {
////          animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
////          return;
////        }
//        animate_led_show_strip(strip_mask);
//        task_led_ctrl_delay((float_t)speed_delay / task_led_ctrl_speed());
//    }
//}
//
//
//void animate_led_fade_to_black(strip_mask_t strip_mask, uint16_t pixel, uint8_t fade_value)
//{
//    if (STRIP_BIT_ALL_SET == strip_mask)
//    {
//        for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
//        {
//            //offset = animate_led_get_strip_offset(strip_bit);
//            //if (ws2812_pixel_is_in_strip_range(strip_bit, pixel)) led_strip[pixel + offset].fadeToBlackBy(fade_value);
//        }
//    }
//    else
//    {
//        for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = strip_bit + 1)
//        {
//            if (strip_mask & strip_bit)
//            {
//                //offset = animate_led_get_strip_offset(strip_bit);
//                //if (ws2812_pixel_is_in_strip_range(strip_bit, pixel)) led_strip[pixel + offset].fadeToBlackBy(fade_value);
//            }
//        }
//    }
//}
