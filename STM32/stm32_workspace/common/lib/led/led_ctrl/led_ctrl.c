// SRW

#include "FreeRTOS.h"
#include "timers.h"
#include "portmacro.h"
#include "numbers.h"

#include "led_ctrl.h"
#include "task_button_press.h"
#include "free_rtos_convenience.h"
#include "ws2812b.h"
#include "led_ctrl_speed.h"
#include "task_button_press.h"
#include "led_ctrl_brightness.h"
#include "led_ctrl.h"
#include "led_color.h"

extern TimerHandle_t g_led_ctrl_timer_handle;

// global arrays guaranteed to be 0 filled... Only filling in parameters below
// if they are non zero!


led_ctrl_t g_led_ctrl[NUM_SUPPORTED_STRIP_COMBOS] =
{
    [STRIP_NUM_1] =
    {
        .led_ctrl_brightness                = LED_BRIGHTNESS_100_PERCENT,
        .led_ctrl_color_info                =
        {
            .led_color_master               = LED_COLOR_MASTER_STATE_DEMO,
            .led_color                      = LED_COLOR_MINT
            // hex color code set at init!
        },
        .led_ctrl_interrupt_info            =
        {
            .minor.interrupt_status_flat    = 0,
            .minor_interrupt_flag           = false,
            .major.interrupt_status_flat    = 0,
            .major_interrupt_flag           = false,
        },
        .led_ctrl_pause_state               = LED_CTRL_PAUSE_STATE_NOT_ACTIVE,
        .led_ctrl_power_factor              = 0,
        .led_ctrl_speed                     = LED_SPEED_NORMAL,
        .led_ctrl_state_info                =
        {
            .led_state_master               = LED_CTRL_STATE_MASTER_DEMO,
            .led_state                      = LED_STATE_RAINBOW_CYCLE,
            .led_state_current_iteration    = 0
        },
    },
    [STRIP_NUM_2] =
    {
        .led_ctrl_brightness                = LED_BRIGHTNESS_100_PERCENT,
        .led_ctrl_color_info                =
        {
            .led_color_master               = LED_COLOR_MASTER_STATE_DEMO,
            .led_color                      = LED_COLOR_MINT
            // hex color code set at init!

        },
        .led_ctrl_interrupt_info            =
        {
            .minor.interrupt_status_flat    = 0,
            .minor_interrupt_flag           = false,
            .major.interrupt_status_flat    = 0,
            .major_interrupt_flag           = false,
        },
        .led_ctrl_pause_state               = LED_CTRL_PAUSE_STATE_NOT_ACTIVE,
        .led_ctrl_power_factor              = 0,
        .led_ctrl_speed                     = LED_SPEED_NORMAL,
        .led_ctrl_state_info                =
        {
            .led_state_master               = LED_CTRL_STATE_MASTER_DEMO,
            .led_state                      = LED_STATE_RAINBOW_CYCLE,
            .led_state_current_iteration    = 0
        },
    },
    [STRIP_NUM_3] =
    {
        .led_ctrl_brightness                = LED_BRIGHTNESS_100_PERCENT,
        .led_ctrl_color_info                =
        {
            .led_color_master               = LED_COLOR_MASTER_STATE_DEMO,
            .led_color                      = LED_COLOR_MINT
            // hex color code set at init!

        },
        .led_ctrl_interrupt_info            =
        {
            .minor.interrupt_status_flat    = 0,
            .minor_interrupt_flag           = false,
            .major.interrupt_status_flat    = 0,
            .major_interrupt_flag           = false,
        },
        .led_ctrl_pause_state               = LED_CTRL_PAUSE_STATE_NOT_ACTIVE,
        .led_ctrl_power_factor              = 0,
        .led_ctrl_speed                     = LED_SPEED_NORMAL,
        .led_ctrl_state_info                =
        {
            .led_state_master               = LED_CTRL_STATE_MASTER_DEMO,
            .led_state                      = LED_STATE_RAINBOW_CYCLE,
            .led_state_current_iteration    = 0
        },
    },
    [STRIP_NUM_ALL_SET] =
    {
        .led_ctrl_brightness                = LED_BRIGHTNESS_100_PERCENT,
        .led_ctrl_color_info                =
        {
            .led_color_master               = LED_COLOR_MASTER_STATE_DEMO,
            .led_color                      = LED_COLOR_MINT
            // hex color code set at init!

        },
        .led_ctrl_interrupt_info            =
        {
            .minor.interrupt_status_flat    = 0,
            .minor_interrupt_flag           = false,
            .major.interrupt_status_flat    = 0,
            .major_interrupt_flag           = false,
        },
        .led_ctrl_pause_state               = LED_CTRL_PAUSE_STATE_NOT_ACTIVE,
        .led_ctrl_power_factor              = 0,
        .led_ctrl_speed                     = LED_SPEED_NORMAL,
        .led_ctrl_state_info                =
        {
            .led_state_master               = LED_CTRL_STATE_MASTER_DEMO,
            .led_state                      = LED_STATE_RAINBOW_CYCLE,
            .led_state_current_iteration    = 0
        },
    }
// multiple strips that ARE NOT ALL are not supported at this time...
};


led_ctrl_state_master_e led_ctrl_read_master_state(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_state_info.led_state_master;
}


void led_ctrl_write_master_state(const strip_mask_t mask,
                                 led_ctrl_state_master_e master_state)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    g_led_ctrl[strip_num].led_ctrl_state_info.led_state_master = master_state;
}


led_state_e led_ctrl_read_active_state(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_state_info.led_state;
}


void led_ctrl_write_active_state(const strip_mask_t mask,
                                 led_state_e state)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    g_led_ctrl[strip_num].led_ctrl_state_info.led_state = state;
}


uint16_t led_ctrl_read_state_current_iteration(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_state_info.led_state_current_iteration;
}


void led_ctrl_write_state_current_iteration(const strip_mask_t mask,
                                            uint16_t value)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    g_led_ctrl[strip_num].led_ctrl_state_info.led_state_current_iteration = value;
}


led_speed_e led_ctrl_read_speed(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_speed;
}


void led_ctrl_write_speed(const strip_mask_t mask, led_speed_e led_speed)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    g_led_ctrl[strip_num].led_ctrl_speed = led_speed;
}


led_ctrl_pause_state_e led_ctrl_read_pause_state(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_pause_state;
}


void led_ctrl_write_pause_state(const strip_mask_t mask, bool pause_enable)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    g_led_ctrl[strip_num].led_ctrl_pause_state = pause_enable;
}


led_ctrl_interrupt_info_t* led_ctrl_read_interrupt_info(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return &g_led_ctrl[strip_num].led_ctrl_interrupt_info;
}


led_ctrl_interrupt_status_t led_ctrl_read_minor_interrupt_status(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_interrupt_info.minor.interrupt_status;
}


bool led_ctrl_read_minor_interrupt_flag(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_interrupt_info.minor_interrupt_flag;
}


led_ctrl_interrupt_status_t led_ctrl_read_major_interrupt_status(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_interrupt_info.major.interrupt_status;
}


bool led_ctrl_read_major_interrupt_flag(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_interrupt_info.major_interrupt_flag;
}


led_color_master_state_e led_ctrl_read_color_master_state(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_color_info.led_color_master;
}


void led_ctrl_write_color_master_state(const strip_mask_t mask,
                                       led_color_master_state_e master_state)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    g_led_ctrl[strip_num].led_ctrl_color_info.led_color_master = master_state;
}


led_color_e led_ctrl_read_active_color(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_color_info.led_color.led_color;
}


void led_ctrl_write_active_color(const strip_mask_t mask, led_color_e led_color)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    g_led_ctrl[strip_num].led_ctrl_color_info.led_color.led_color = led_color;
}


led_color_hex_code_e led_ctrl_read_active_color_hex(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_color_info.led_color.led_color_hex_code;
}


void led_ctrl_write_active_color_hex(const strip_mask_t mask,
                                   led_color_hex_code_e led_color_hex_code)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    g_led_ctrl[strip_num].led_ctrl_color_info.led_color.led_color_hex_code = led_color_hex_code;
}


uint8_t led_ctrl_read_color_rgb_red_hex(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return ((g_led_ctrl[strip_num].led_ctrl_color_info.led_color.led_color_hex_code & 0xFF0000) \
                    >> (2 * BITS_PER_BYTE));
}


uint8_t led_ctrl_read_color_rgb_green_hex(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return ((g_led_ctrl[strip_num].led_ctrl_color_info.led_color.led_color_hex_code & 0x00FF00) \
                    >> (1 * BITS_PER_BYTE));
}


uint8_t led_ctrl_read_color_rgb_blue_hex(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return ((g_led_ctrl[strip_num].led_ctrl_color_info.led_color.led_color_hex_code & 0x0000FF) \
                    >> (0 * BITS_PER_BYTE));
}


led_brightness_e led_ctrl_read_strip_brightness(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return g_led_ctrl[strip_num].led_ctrl_brightness;
}


void led_ctrl_write_strip_brightness(const strip_mask_t mask,
                                     led_brightness_e led_brightness)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    g_led_ctrl[strip_num].led_ctrl_brightness = led_brightness;
}


led_ctrl_state_info_t* led_ctrl_read_state_info(const strip_mask_t mask)
{
    strip_num_e strip_num = ws2812_strip_bit_to_strip_num(mask);
    return &g_led_ctrl[strip_num].led_ctrl_state_info;
}


