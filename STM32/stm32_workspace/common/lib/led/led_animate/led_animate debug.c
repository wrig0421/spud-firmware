// move all of the debug functions here.  Perhaps even the specific LED driving functions move here also?


#if 0

bool g_clear_and_show_all_pixels = false;
bool g_show_all_pixels = false;
uint32_t g_start_pixel = 0;
uint32_t g_stop_pixel = 0;
void led_animate_srw_debug(void)
{
    uint32_t random_color = 0;
    strip_mask_t mask = STRIP_BIT_1;

//  while (1)
//  {
//      if (g_clear_and_show_all_pixels)
//      {
//          g_clear_and_show_all_pixels = false;
//          led_ctrl_time_delay(mask, 250);
//          led_animate_turn_all_pixels_off();
//      }
//      if (g_show_all_pixels)
//      {
//          g_show_all_pixels = false;
//          led_animate_turn_all_pixels_off();
//          led_ctrl_time_delay(mask, 250);
//          led_animate_set_pixels_in_range(mask, g_start_pixel, g_stop_pixel, LED_COLOR_HEX_BLUE);
//      }
//      led_ctrl_time_delay(mask, 100);
//  }




    // pumpkin_base start = 293
    // pumpkin_base stop = 404
    led_animate_set_pixels_in_range(mask, 0, 292, LED_COLOR_HEX_ORANGE);
    led_animate_set_pixels_in_range(mask, 293, 404, LED_COLOR_HEX_ORANGE_RED);
    // pumpkin stem start = 405
    // pumpkin stem stop = 427
    led_animate_set_pixels_in_range(mask, 405, 427, LED_COLOR_HEX_GREEN);
    // coffee cup base start = 428
    // coffee cup base stop = 458
    led_animate_set_pixels_in_range(mask, 428, 458, LED_COLOR_HEX_WHITE);
    // coffee cup sleeve start = 459
    // coffee cup sleeve stop = 475
    led_animate_set_pixels_in_range(mask, 459, 475, LED_COLOR_HEX_SPRING_GREEN);
    // coffee cup top start = 476
    // coffee cup top stop = 516
    led_animate_set_pixels_in_range(mask, 476, 516, LED_COLOR_HEX_CHARCOAL);
    // leaf stem start = 517
    // leaf stem stop = 529
    led_animate_set_pixels_in_range(mask, 517, 529, LED_COLOR_HEX_RED_BROWN);
    led_animate_set_pixels_in_range(mask, 530, 579, LED_COLOR_HEX_RED);

    // leaf part start = 530
    // leaf part stop = 579
    while (1)
    {
        random_color = random_num(0, UINT24_MAX);
        led_animate_set_pixels_in_range_uint32(mask, 0, 65, random_color);
        random_color = random_num(0, UINT24_MAX);
        led_animate_set_pixels_in_range_uint32(mask, 66, 141, random_color);
        random_color = random_num(0, UINT24_MAX);
        led_animate_set_pixels_in_range_uint32(mask, 142, 292, random_color);
        random_color = random_num(0, UINT24_MAX);
        led_animate_set_pixels_in_range_uint32(mask, 293, 404, random_color);
        random_color = random_num(0, UINT24_MAX);
        led_animate_set_pixels_in_range_uint32(mask, 405, 427, random_color);
        random_color = random_num(0, UINT24_MAX);
        led_animate_set_pixels_in_range_uint32(mask, 428, 458, random_color);
        random_color = random_num(0, UINT24_MAX);
        led_animate_set_pixels_in_range_uint32(mask, 459, 475, random_color);
        random_color = random_num(0, UINT24_MAX);
        led_animate_set_pixels_in_range_uint32(mask, 476, 516, random_color);
        random_color = random_num(0, UINT24_MAX);
        led_animate_set_pixels_in_range_uint32(mask, 517, 529, random_color);
        random_color = random_num(0, UINT24_MAX);
        led_animate_set_pixels_in_range_uint32(mask, 530, 579, random_color);
        led_ctrl_time_delay(mask, 1500);

//      random_color = random_num(0, UINT24_MAX);
//      led_animate_set_pixels_in_range_uint32(mask, 0, 292, random_color);
//      led_animate_set_pixels_in_range(mask, 530, 579, LED_COLOR_HEX_RED);
//      led_animate_set_pixels_in_range(mask, 428, 458, LED_COLOR_HEX_WHITE);
//      led_animate_set_pixels_in_range(mask, 459, 475, LED_COLOR_HEX_SPRING_GREEN);
//      led_animate_set_pixels_in_range(mask, 476, 516, LED_COLOR_HEX_SPRING_GREEN);
//      led_animate_set_pixels_in_range(mask, 530, 579, LED_COLOR_HEX_LAWN_GREEN);
//      led_ctrl_time_delay(mask, 3000);
//      random_color = random_num(0, UINT24_MAX);
//      led_animate_set_pixels_in_range_uint32(mask, 0, 292, random_color);
//      led_animate_set_pixels_in_range(mask, 428, 458, LED_COLOR_HEX_CHARCOAL);
//      led_animate_set_pixels_in_range(mask, 459, 475, LED_COLOR_HEX_WHITE);
//      led_animate_set_pixels_in_range(mask, 476, 516, LED_COLOR_HEX_SPRING_GREEN);
//      led_animate_set_pixels_in_range(mask, 530, 579, LED_COLOR_HEX_LAWN_GREEN);
//      led_ctrl_time_delay(mask, 3000);
//      random_color = random_num(0, UINT24_MAX);
//      led_animate_set_pixels_in_range_uint32(mask, 0, 292, random_color);
//      led_animate_set_pixels_in_range(mask, 428, 458, LED_COLOR_HEX_SPRING_GREEN);
//      led_animate_set_pixels_in_range(mask, 459, 475, LED_COLOR_HEX_CHARCOAL);
//      led_animate_set_pixels_in_range(mask, 476, 516, LED_COLOR_HEX_WHITE);
//      led_animate_set_pixels_in_range(mask, 530, 579, LED_COLOR_HEX_YELLOW);
//      led_ctrl_time_delay(mask, 3000);
    }

    // a function to determine start/stop of LEDs



}



uint32_t diff_time = 0;
void led_animate_starburst_zabinski(const strip_mask_t mask,
                                    const led_color_e* p_color,
                                    uint16_t* p_delay_ms,
                                    led_animate_starburst_mode_e mode,
                                    bool b_two_random_color)
{
    uint16_t yyy = 0;
    led_color_t led_color;
    led_color_t led_color_1;
    led_color_t led_color_2;

    led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
    uint16_t delay_copy = (uint16_t)(*p_delay_ms);

    uint16_t short_leg = 0;
    uint16_t long_leg = 0;

    uint16_t strip_size = ws2812_led_get_max_strip_size_in_mask(mask);

    uint16_t strip_half = 0;

#if defined(ENABLE_ZABINSKI_TABLE_BOTTOM)
    short_leg = LED_ANIMATE_BOTTOM_STARTBURT_SHORT_SIDE_NUM_LEDS;
    long_leg = LED_ANIMATE_BOTTOM_STARTBURT_LONG_SIDE_NUM_LEDS;
#elif defined(ENABLE_ZABINSKI_TABLE_TOP)
    short_leg = LED_ANIMATE_TOP_STARTBURT_SHORT_SIDE_NUM_LEDS;
    long_leg = LED_ANIMATE_TOP_STARTBURT_LONG_SIDE_NUM_LEDS;
#endif
    strip_half = short_leg + long_leg;
//  diff_time = ((xTaskGetTickCount() - time_start) / configTICK_RATE_HZ);
    while (diff_time < 8)
    {
        if (b_two_random_color)
        {
            led_color_1.color_hex = random_num(0, UINT24_MAX);
            led_color_2.color_hex = random_num(0, UINT24_MAX);
        }
//      diff_time = ((xTaskGetTickCount() - time_start) / configTICK_RATE_HZ);
        if (LED_ANIMATE_STARBURTS_MODE_1 == mode)
        {
            for (yyy=0; yyy < short_leg; yyy++)
            {
                if (led_animate_interrupt_occurred(mask))
                {
                    if (led_animate_check_interrupts(mask))
                    {
                        return;
                    }
                    else if (g_task_notification_value.stimulus_bits.color)
                    {
                        led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
                    }
                    else if (led_animate_need_to_adjust_speed())
                    {
                        delay_copy = led_ctrl_read_time_delay_inner_loop(mask,
                                                                             LED_STATE_RAINBOW_CYCLE);
                        led_animate_clear_adjust_speed();
                    }
                }
                if (b_two_random_color)
                {
                    led_animate_set_pixel(mask, yyy, &led_color_1);
                    led_animate_set_pixel(mask, strip_size - 1 - yyy,
                                          &led_color_2);
                }
                else
                {
                    led_animate_set_pixel(mask, yyy, &led_color);
                    led_animate_set_pixel(mask, strip_size - 1 - yyy,
                                          &led_color);
                }
                led_animate_show_strip(mask);
                led_ctrl_time_delay(mask, delay_copy);
            }
            for (uint16_t iii = short_leg; iii < short_leg + long_leg; iii++)
            {
                if (led_animate_interrupt_occurred(mask))
                {
                    if (led_animate_check_interrupts(mask))
                    {
                        return;
                    }
                    else if (g_task_notification_value.stimulus_bits.color)
                    {
                        led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
                    }
                    else if (led_animate_need_to_adjust_speed())
                    {
                        delay_copy = led_ctrl_read_time_delay_inner_loop(mask,
                                                                             LED_STATE_RAINBOW_CYCLE);
                        led_animate_clear_adjust_speed();
                    }
                }
                if (b_two_random_color)
                {
                    led_animate_set_pixel(mask, iii, &led_color_1);
                    led_animate_set_pixel(mask, strip_size - 1 - iii,
                                          &led_color_2);
                }
                else
                {
                    led_animate_set_pixel(mask, iii, &led_color);
                    led_animate_set_pixel(mask, strip_size - 1 - iii,
                                          &led_color);
                }
                led_animate_show_strip(mask);
                led_ctrl_time_delay(mask, delay_copy);
            }
        }
        else if (LED_ANIMATE_STARBURTS_MODE_2 == mode)
        {
            for (uint16_t iii = 0; iii < short_leg; iii++)
            {
                if (led_animate_interrupt_occurred(mask))
                {
                    if (led_animate_check_interrupts(mask))
                    {
                        return;
                    }
                    else if (g_task_notification_value.stimulus_bits.color)
                    {
                        led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
                    }
                    else if (led_animate_need_to_adjust_speed())
                    {
                        delay_copy = led_ctrl_read_time_delay_inner_loop(mask,
                                                                             LED_STATE_RAINBOW_CYCLE);
                        led_animate_clear_adjust_speed();
                    }
                }
                if (b_two_random_color)
                {
                    led_animate_set_pixel(mask, iii, &led_color_1);
                    led_animate_set_pixel(mask, strip_size - 1 - iii,
                                          &led_color_1);
                    led_animate_set_pixel(mask, strip_half + iii, &led_color_2);
                    led_animate_set_pixel(mask, strip_half - 1 - iii,
                                          &led_color_2);
                }
                else
                {
                    led_animate_set_pixel(mask, iii, &led_color);
                    led_animate_set_pixel(mask, strip_size - 1 - iii,
                                          &led_color);
                    led_animate_set_pixel(mask, strip_half + iii, &led_color);
                    led_animate_set_pixel(mask, strip_half - 1 - iii,
                                          &led_color);
                }
                led_animate_show_strip(mask);
                led_ctrl_time_delay(mask, delay_copy);
            }
            for (uint16_t iii = short_leg; iii < long_leg; iii++)
            {
                if (led_animate_interrupt_occurred(mask))
                {
                    if (led_animate_check_interrupts(mask))
                    {
                        return;
                    }
                    else if (g_task_notification_value.stimulus_bits.color)
                    {
                        led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
                    }
                    else if (led_animate_need_to_adjust_speed())
                    {
                        delay_copy = led_ctrl_read_time_delay_inner_loop(mask,
                                                                             LED_STATE_RAINBOW_CYCLE);
                        led_animate_clear_adjust_speed();
                    }
                }
                if (b_two_random_color)
                {
                    led_animate_set_pixel(mask, strip_size - 1 - iii,
                                          &led_color_1);
                    led_animate_set_pixel(mask, strip_half - 1 - iii,
                                          &led_color_2);
                }
                else
                {
                    led_animate_set_pixel(mask, strip_size - 1 - iii,
                                          &led_color);
                    led_animate_set_pixel(mask, strip_half - 1 - iii,
                                          &led_color);
                }
                led_animate_show_strip(mask);
                led_ctrl_time_delay(mask, delay_copy);
            }
        }
    }
}



uint16_t g_num_pixels = 0;
uint16_t g_dbg_pixel_start = 0;
uint16_t g_dbg_pixel_stop = 10;
bool g_dbg_num_flag = false;
bool g_dbg_num_pixels_turn_off_all_pixels;
bool g_dbg_num_pixels_complete = false;
void led_animate_determine_number_pixels_in_strip(const strip_mask_t mask)
{
    // morinville bike
    // rear tire                78 -> 99
    // rear brake               100 -> 112
    // seat                     113 -> 125  BROWN
    // rear fender              126 -> 133
    // gas tank                 134 -> 150
    // light                    151 -> 154
    // front fender             155 -> 163
    // front tire               164 -> 191
    // front brake              192 -> 208

    led_animate_turn_all_pixels_off();

    while(1);

    do
    {
        // strip 1 is motorcycle

        if (g_dbg_num_pixels_turn_off_all_pixels)
        {
            g_dbg_num_pixels_turn_off_all_pixels = false;
            led_animate_turn_all_pixels_off();
            led_ctrl_time_delay(mask, 5000);
        }
        else
        {
            led_animate_set_pixels_in_range_and_show(mask,
                                                     g_dbg_pixel_start,
                                                     g_dbg_pixel_stop,
                                                     LED_COLOR_HEX_DARK_MAGENTA);
            led_ctrl_time_delay(mask, 2000);
        }
    } while ((!g_dbg_num_pixels_complete));
    g_dbg_num_pixels_complete = false;
}



void led_animate_starburst(const strip_mask_t mask,
                           const led_color_e* p_color,
                            uint16_t* p_delay_ms,
                            led_animate_starburst_mode_e mode,
                            bool b_two_random_color)
{
    uint16_t yyy = 0;
    led_color_t led_color;
    led_color_t led_color_1;
    led_color_t led_color_2;
    if (b_two_random_color)
    {
        led_color_1.color_hex = random_num(0, UINT24_MAX);
        led_color_2.color_hex = random_num(0, UINT24_MAX);
    }

    led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
    uint16_t delay_copy = (uint16_t)(*p_delay_ms);

    uint16_t short_leg = 0;
    uint16_t long_leg = 0;

    uint16_t strip_size = ws2812_led_get_max_strip_size_in_mask(mask);

    uint16_t strip_half = 0;

#if defined(ENABLE_ZABINSKI_TABLE_BOTTOM)
    short_leg = LED_ANIMATE_BOTTOM_STARTBURT_SHORT_SIDE_NUM_LEDS;
    long_leg = LED_ANIMATE_BOTTOM_STARTBURT_LONG_SIDE_NUM_LEDS;
#elif defined(ENABLE_ZABINSKI_TABLE_TOP)
    short_leg = LED_ANIMATE_TOP_STARTBURT_SHORT_SIDE_NUM_LEDS;
    long_leg = LED_ANIMATE_TOP_STARTBURT_LONG_SIDE_NUM_LEDS;
#endif
    strip_half = short_leg + long_leg;

    if (LED_ANIMATE_STARBURTS_MODE_1 == mode)
    {
        for (yyy=0; yyy < short_leg; yyy++)
        {
            if (led_animate_interrupt_occurred(mask))
            {
                if (led_animate_check_interrupts(mask))
                {
                    return;
                }
                else if (g_task_notification_value.stimulus_bits.color)
                {
                    led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
                }
                else if (led_animate_need_to_adjust_speed())
                {
                    delay_copy = led_ctrl_read_time_delay_inner_loop(mask,
                                                                         LED_STATE_RAINBOW_CYCLE);
                    led_animate_clear_adjust_speed();
                }
            }
            if (b_two_random_color)
            {
                led_animate_set_pixel(mask, yyy, &led_color_1);
                led_animate_set_pixel(mask, strip_size - 1 - yyy, &led_color_2);
            }
            else
            {
                led_animate_set_pixel(mask, yyy, &led_color);
                led_animate_set_pixel(mask, strip_size - 1 - yyy, &led_color);
            }
            led_animate_show_strip(mask);
            led_ctrl_time_delay(mask, delay_copy);
        }
        for (uint16_t iii = short_leg; iii < short_leg + long_leg; iii++)
        {
            if (led_animate_interrupt_occurred(mask))
            {
                if (led_animate_check_interrupts(mask))
                {
                    return;
                }
                else if (g_task_notification_value.stimulus_bits.color)
                {
                    led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
                }
                else if (led_animate_need_to_adjust_speed())
                {
                    delay_copy = led_ctrl_read_time_delay_inner_loop(mask,
                                                                         LED_STATE_RAINBOW_CYCLE);
                    led_animate_clear_adjust_speed();
                }
            }
            if (b_two_random_color)
            {
                led_animate_set_pixel(mask, iii, &led_color_1);
                led_animate_set_pixel(mask, strip_size - 1 - iii, &led_color_2);
            }
            else
            {
                led_animate_set_pixel(mask, iii, &led_color);
                led_animate_set_pixel(mask, strip_size - 1 - iii, &led_color);
            }
            led_animate_show_strip(mask);
            led_ctrl_time_delay(mask, delay_copy);
        }
    }
    else if (LED_ANIMATE_STARBURTS_MODE_2 == mode)
    {
        for (uint16_t iii = 0; iii < short_leg; iii++)
        {
            if (led_animate_interrupt_occurred(mask))
            {
                if (led_animate_check_interrupts(mask))
                {
                    return;
                }
                else if (g_task_notification_value.stimulus_bits.color)
                {
                    led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
                }
                else if (led_animate_need_to_adjust_speed())
                {
                    delay_copy = led_ctrl_read_time_delay_inner_loop(mask,
                                                                         LED_STATE_RAINBOW_CYCLE);
                    led_animate_clear_adjust_speed();
                }
            }
            if (b_two_random_color)
            {
                led_animate_set_pixel(mask, iii, &led_color_1);
                led_animate_set_pixel(mask, strip_size - 1 - iii, &led_color_1);
                led_animate_set_pixel(mask, strip_half + iii, &led_color_2);
                led_animate_set_pixel(mask, strip_half - 1 - iii, &led_color_2);
            }
            else
            {
                led_animate_set_pixel(mask, iii, &led_color);
                led_animate_set_pixel(mask, strip_size - 1 - iii, &led_color);
                led_animate_set_pixel(mask, strip_half + iii, &led_color);
                led_animate_set_pixel(mask, strip_half - 1 - iii, &led_color);
            }
            led_animate_show_strip(mask);
            led_ctrl_time_delay(mask, delay_copy);
        }
        for (uint16_t iii = short_leg; iii < long_leg; iii++)
        {
            if (led_animate_interrupt_occurred(mask))
            {
                if (led_animate_check_interrupts(mask))
                {
                    return;
                }
                else if (g_task_notification_value.stimulus_bits.color)
                {
                    led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
                }
                else if (led_animate_need_to_adjust_speed())
                {
                    delay_copy = led_ctrl_read_time_delay_inner_loop(mask,
                                                                         LED_STATE_RAINBOW_CYCLE);
                    led_animate_clear_adjust_speed();
                }
            }
            if (b_two_random_color)
            {
                led_animate_set_pixel(mask, strip_size - 1 - iii, &led_color_1);
                led_animate_set_pixel(mask, strip_half - 1 - iii, &led_color_2);
            }
            else
            {
                led_animate_set_pixel(mask, strip_size - 1 - iii, &led_color);
                led_animate_set_pixel(mask, strip_half - 1 - iii, &led_color);
            }
            led_animate_show_strip(mask);
            led_ctrl_time_delay(mask, delay_copy);
        }
    }
}



void led_animate_static_harley_color(const strip_mask_t mask,
                                     const led_color_e* p_color)
{
    led_color_t led_color;
//  led_color_e led_color_dummy = LED_COLOR_NONE;
    led_color.led_color_hex_code = led_ctrl_color_enum_to_hex(*p_color);
//  if (led_animate_check_for_animation_exit_stimulus(mask, &led_color, &led_color_dummy)) return;
    // handle bar + forks
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 0, 16,
                                                         LED_COLOR_HEX_WHITE);
    // bottom frame
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 17, 36,
                                                         led_color.led_color_hex_code);
    // shifter?
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 37, 40,
                                                         LED_COLOR_HEX_WHITE);
    // pipes
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 41, 69,
                                                         LED_COLOR_HEX_WHITE);
    // near seat frame
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 70, 77,
                                                         led_color.led_color_hex_code);
    // rear tire
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 78, 99,
                                                         LED_COLOR_HEX_DEBUG);
    // rear brake
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 100, 112,
                                                         LED_COLOR_HEX_DEBUG);
    // seat
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 113, 119,
                                                         LED_COLOR_HEX_SADDLE_BROWN);
    // rear fender
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 120, 133,
                                                         led_color.led_color_hex_code);
    // gas tank
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 134, 150,
                                                         led_color.led_color_hex_code);
    // light
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 151, 154,
                                                         LED_COLOR_HEX_YELLOW);
    // front fender
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 155, 163,
                                                         led_color.led_color_hex_code);
    // front tire
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 164, 191,
                                                         LED_COLOR_HEX_DEBUG);
    // front brake
    led_animate_set_pixels_in_range_skip_interrupt_check(mask, 192, 208,
                                                         LED_COLOR_HEX_DEBUG);
    led_animate_show_strip(mask);
}










#endif













