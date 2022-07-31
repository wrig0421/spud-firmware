// SRW
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "cmsis_os.h"
#include "numbers.h"
#include "color_led.h"
#include "ws2812b.h"
#include "board_init.h"
#include "animate_led.h"

//#define PIN_STRIP_1 8
////#define PIN_STRIP_1 12
//
//#if defined(MULTIPLE_STRIPS)
////#define PIN_STRIP_2 8
//#define PIN_STRIP_2 12
////#define PIN_STRIP_3
////#define PIN_STRIP_5
////#define PIN_STRIP_6
////#define PIN_STRIP_7
////#define PIN_STRIP_8
////#define PIN_STRIP_9
//#endif





typedef enum
{
    ANIMATION_LOOP_ITERATIONS_0 = 0,
    ANIMATION_LOOP_ITERATIONS_1,
    ANIMATION_LOOP_ITERATIONS_2,
    ANIMATION_LOOP_ITERATIONS_3,
    ANIMATION_LOOP_ITERATIONS_4,
    ANIMATION_LOOP_ITERATIONS_5,
    ANIMATION_LOOP_ITERATIONS_6,
    ANIMATION_LOOP_ITERATIONS_7,
    ANIMATION_LOOP_ITERATIONS_8,
    ANIMATION_LOOP_ITERATIONS_9,
    ANIMATION_LOOP_ITERATIONS_10,
    ANIMATION_LOOP_ITERATIONS_50 = 50,
    ANIMATION_LOOP_ITERATIONS_100 = 100
} animation_loop_iterations_e;


typedef enum
{
    ANIMATION_DELAY_MS_0 = 0,
    ANIMATION_DELAY_MS_1000 = 1000,
    ANIMATION_DELAY_MS_2000 = 2000,
    ANIMATION_DELAY_MS_3000 = 3000,
    ANIMATION_DELAY_MS_4000 = 4000,
    ANIMATION_DELAY_MS_5000 = 5000,
    ANIMATION_DELAY_MS_10000 = 10000,
    ANIMATION_DELAY_MS_15000 = 15000,
    ANIMATION_DELAY_MS_20000 = 20000
} animation_delay_ms_e;


// global variables
master_led_state_e g_master_led_state = MASTER_LED_STATE_DEMO;
extern master_color_state_e g_master_color_state;
extern bool g_color_led_demo_state_exit_flag;
extern bool g_color_led_demo_state_enter_flag;

uint8_t g_animation_iterations = 0;
led_state_e g_led_state = LED_STATE_SPELL;

unsigned long g_isr_times[NUM_ISR] = {0};
unsigned long g_debounce_delay = 2000; // ms
bool g_master_color_state_change_flag = false;
bool g_master_led_state_change_flag = false;
uint32_t g_random_color_array[NUM_STRIPS];


// if strip is not in use then offset is 0 

bool g_interrupt_flag[NUM_ISR] = {false};
extern uint32_t g_max_strip_length;

uint16_t g_strip_offset[NUM_STRIPS] = {0};

led_speed_e g_led_speed = LED_SPEED_5X;
//led_speed_e g_led_speed = LED_SPEED_1X;
//led_state_e g_led_state = LED_STATE_FIRST;
//led_state_e g_led_state = LED_STATE_TWO_TONE;

uint16_t g_delay_between_animations_ms = 1000;
uint16_t g_delay_in_animation_ms = 100; // where applicable of course
uint32_t g_iterations = 0; 
extern uint16_t g_all_strip_mask;

bool g_master_led_demo_state_exit_flag = false;
bool g_master_led_demo_state_enter_flag = false;
bool g_animate_led_pause_flag = false;
bool g_animate_led_interrupt = false;

void animate_led_interrupt(void)
{
    g_animate_led_interrupt = true;
}


void animate_led_reset_animate_iteration_count(void)
{
    g_animation_iterations = 0;
}


void animate_led_pause(void)
{
    static uint8_t flip_or_flop = 1;
    if (flip_or_flop) g_animate_led_pause_flag = true;
    else g_animate_led_pause_flag = false;
    flip_or_flop ^= 1;
}


void animate_led_enter_demo_state(void)
{
    g_master_led_demo_state_enter_flag = true;
    g_master_led_state = MASTER_LED_STATE_DEMO;
    g_animation_iterations = 0;
}


void animate_led_exit_demo_state(void)
{
    g_master_led_demo_state_exit_flag = true;
    g_master_led_state = MASTER_LED_STATE_FIXED;
    g_led_state = LED_STATE_FIRST; // set first state
    g_animation_iterations = 0;
}


master_led_state_e animate_led_master_state(void)
{
    return g_master_led_state;
}


static uint32_t millis(void)
{
    return 0; // TODO FIX THIS!
}


static void delay(uint32_t time)
{
    uint32_t count = 0;
    while (!animate_led_interrupt_occurred() && ((count * 10) < time))
    {
        osDelay(time / 100);
        count++;
    }
}


//uint32_t random_num(uint32_t min, uint32_t max)
//{
//   return min + rand() % (max + 1 - min);
//}


void animate_led_reset_state(void)
{
	g_led_state = LED_STATE_FIRST;
}




void animate_led_set_interrupt_flag(isr_e src)
{
    g_animate_led_interrupt = true; // global indicator that intterupt occured
    g_interrupt_flag[src] = true;
}


bool animate_led_interrupt_occurred(void)
{
//    bool return_val = false;
//    if (g_animate_led_interrupt)
//    {
//        return_val = true;
//        g_animate_led_interrupt = false;
//    }
//    return return_val;
    return g_animate_led_interrupt;
}


bool animate_led_interrupt_flag(isr_e src)
{
	bool return_val = g_interrupt_flag[src];
	if (return_val) g_interrupt_flag[src] = false; // auto clear
	return return_val;
}


bool animate_led_interrupt_flag_speed(void)
{
	return (animate_led_interrupt_flag(ISR_SPEED));
}


bool animate_led_interrupt_flag_state(void)
{
	return (animate_led_interrupt_flag(ISR_STATE));
}


bool animate_led_interrupt_flag_color(void)
{
	return (animate_led_interrupt_flag(ISR_COLOR));
}


float animate_led_speed_factor(void);
float animate_led_speed_factor(void)
{
	float speed_factor = 0.0;
	switch(g_led_speed)
	{
		
		case LED_SPEED_10X:
			speed_factor = 10;
		break;
		case LED_SPEED_5X:
			speed_factor = 5;
		break;
		case LED_SPEED_2X:
			speed_factor = 2;
		break;
		case LED_SPEED_1X:	
			speed_factor = 1;
		break;
		case LED_SPEED_0P5X:
			speed_factor = 0.5;
		break;
		case LED_SPEED_0P25X:
			speed_factor = 0.25;
		break;
		default:
		break;
		/*
		case LED_SPEED_0P1X:
			speed_factor = 0.1;
		break;
		*/
	}
	return speed_factor;
}

uint16_t animate_led_delay_between_animations(void)
{
	return ((float)g_delay_between_animations_ms / animate_led_speed_factor());
}


float animate_led_delay_in_animations(void)
{
	return ((float)g_delay_in_animation_ms / animate_led_speed_factor());
}


void animate_led_adjust_speed(void)
{
	if (LED_SPEED_LAST == g_led_speed) g_led_speed = LED_SPEED_FIRST;
	else g_led_speed = (led_speed_e) (g_led_speed + 1);
}


bool animate_led_adjust_state(void)
{
	bool return_val = false;
	if (LED_STATE_LAST == g_led_state)
	{
		g_led_state = LED_STATE_FIRST;
		return_val = true;
	}
	else g_led_state = (led_state_e) (g_led_state + 1);
	return return_val;
}


void animate_led_init(void)
{

}


//static void animate_led_internal_set_led_color(CRGB *buf, uint16_t led, uint8_t red, uint8_t green, uint8_t blue)
//{
//	buf[led].red = red;
//	buf[led].green = green;
//	buf[led].blue = blue;
//}


// animate led will have the following interrupts
// A - speed
// B - state
// C - color
// D - pause
static bool animate_led_check_interrupts(uint8_t *red, uint8_t *green, uint8_t *blue)
{
	bool return_val = false;
	g_animate_led_interrupt = false; // this is only called after interrupt has occurred... so flag gets reset here
	if (animate_led_interrupt_flag(ISR_STATE))
    {
        return_val = true;
	    animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
        //osDelay(500); // some dormant time?
    }
	else if (animate_led_interrupt_flag(ISR_PAUSE))
	{
	    while (g_animate_led_pause_flag)
	    {
	        osDelay(10);
	    }
	}
	else if (animate_led_interrupt_flag(ISR_COLOR))
	{
	    // interrupt modifies the current color... apply it to the animation!
	    *red = color_led_cur_color_red_hex();
        *green = color_led_cur_color_green_hex();
        *blue = color_led_cur_color_blue_hex();
	}
	return return_val;
}


void animate_led_reset_iterations(void)
{
	g_iterations = 0;
}


void animate_led_increment_iterations(void)
{
	g_iterations++;
}


uint32_t animate_led_iterations(void)
{
	return g_iterations; 
}


led_state_e animate_led_state(void)
{
	return g_led_state;
}


void animate_led_show_strip(const strip_mask_t strip_mask)
{
	ws2812b_show(strip_mask);
}


led_state_e animate_led_state_randomize(led_state_e cur_state)
{
	led_state_e state = (led_state_e)(random_num(LED_STATE_FIRST, NUM_LED_STATES));
    if (cur_state == state)
    {
        if (LED_STATE_LAST == cur_state) state = (led_state_e)(state - 1);
        else state = (led_state_e)(state + 1);
    }
	return state;
}


/*
void animate_led_state_randomize(void)
{
    led_state_e state = (led_state_e)(random_num(LED_STATE_FIRST, NUM_LED_STATES));
    if (g_led_state == state)
    {
        if (LED_STATE_LAST == g_led_state) g_led_state = (led_state_e)(state - 1);
        else g_led_state = (led_state_e)(state + 1);
    }
	else
	{
		g_led_state = state;
	}
}
*/


void animate_led_multiple_solid_custom_colors(strip_mask_t strip_mask, uint32_t* color_array)
{
    // not checking for interrupts in this function the solid color is too fast.  No way a user
    // would be able to tell if caught or not.
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};

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
	for (int yyy = 0; yyy < num_active_strips; yyy++)
	{
		animate_led_set_all_pixels(active_strip_array[yyy], ((color_array[yyy] & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR, ((color_array[yyy] & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR, (color_array[yyy] & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR);
	}
}


void animate_led_solid_custom_color(const strip_mask_t strip_mask, color_hex_code_e color)
{
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
	animate_led_set_all_pixels(strip_mask, red, green, blue);
	animate_led_show_strip(strip_mask);
}


void animate_led_turn_all_pixels_off(void)
{
	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
}


void animate_led_spell_and_sparkle(const strip_mask_t spell_mask, const strip_mask_t sparkle_mask, color_hex_code_e color, bool fill, uint16_t speed_delay)
{
	//uint16_t strip_size = ws2812_led_get_max_strip_size(spell_mask | sparkle_mask);
	uint16_t strip_size = ws2812_led_get_max_strip_size(spell_mask); // this makes more sense... SRW
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
	if (!fill) animate_led_set_all_pixels(sparkle_mask, 0, 0, 0);
	for (int i = 0; i < strip_size; i++)
	{
	    if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
        animate_led_sparkle_random_color(sparkle_mask, fill, 0);
        animate_led_set_pixel(spell_mask, i, red, green, blue);
		animate_led_show_strip(sparkle_mask|spell_mask);
        delay((float_t)speed_delay / animate_led_speed_factor());
	}	
}


void animate_led_spell_and_solid_color(const strip_mask_t spell_mask, const strip_mask_t solid_color_mask, color_hex_code_e color, uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(spell_mask); // this makes more sense... SRW
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
	animate_led_solid_custom_color(solid_color_mask, color_led_get_random_color());
	for (int i = 0; i < strip_size; i++)
	{
	    if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
        animate_led_set_pixel(spell_mask, i, red, green, blue);
		animate_led_show_strip(spell_mask | solid_color_mask);
		delay((float_t)speed_delay / animate_led_speed_factor());
	}	
}


void animate_led_spell_word_multiple_colors(strip_mask_t strip_mask, uint32_t* color_array, uint16_t speed_delay)
{
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};

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
	for (int i = 0; i < strip_size; i++)
	{
		for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
		    //if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
			animate_led_set_pixel(active_strip_array[yyy], i, ((color_array[yyy] & 0xFF0000) >> 16), ((color_array[yyy] & 0x00FF00) >> 8), (color_array[yyy] & 0x0000FF));
		}
		animate_led_show_strip(strip_mask);
		delay((float_t)speed_delay / animate_led_speed_factor());
	}
}


void animate_led_only_spell_word(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
	for (int i = 0; i < strip_size; i++)
	{
	    if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
		animate_led_set_pixel(strip_mask, i, red, green, blue);
		animate_led_show_strip(strip_mask);
		delay((float_t)speed_delay / animate_led_speed_factor());
	}
}


void animate_led_fade_in_fade_out_multiple_colors(strip_mask_t strip_mask, uint32_t* color_array)
{
    // interrupts not handled yet!
	uint8_t red, green, blue; 
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
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
			animate_led_set_all_pixels(active_strip_array[yyy], (((color_array[yyy] & 0xFF0000) >> 16)) * (i / 256.0), (((color_array[yyy] & 0x00FF00) >> 8)) * (i / 256.0), ((color_array[yyy] & 0x0000FF)) * (i / 256.0));
		}
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
    }
    for (int i = 255; i >= 0; i -= 5)
    {
    	for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
			animate_led_set_all_pixels(active_strip_array[yyy], (((color_array[yyy] & 0xFF0000) >> 16)) * (i / 256.0), (((color_array[yyy] & 0x00FF00) >> 8)) * (i / 256.0), ((color_array[yyy] & 0x0000FF)) * (i / 256.0));
		}
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
    }
}


void animate_led_fade_in_fade_out(strip_mask_t strip_mask, color_hex_code_e color)
{
    float r, g, b;
    uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    for (int i = 0; i < 256; i++)
    {
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
        r = (i / 256.0) * red;
        g = (i / 256.0) * green;
        b = (i / 256.0) * blue;
        animate_led_set_all_pixels(strip_mask, r, g, b);
    }
    for (int i = 255; i >= 0; i = i-2)
    {
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
        r = (i / 256.0) * red;
        g = (i / 256.0) * green;
        b = (i / 256.0) * blue;
        animate_led_set_all_pixels(strip_mask, r, g, b);
    }
}


void animate_led_strobe(strip_mask_t strip_mask, color_hex_code_e color, uint16_t animate_led_strobe_count, uint16_t flash_delay, uint16_t end_pause)
{
    // speed is not handled here currently
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    for (int i = 0; i < animate_led_strobe_count; i++)
    {
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
        animate_led_set_all_pixels(strip_mask, red, green, blue);
        animate_led_show_strip(strip_mask);
        delay(flash_delay);
        animate_led_set_all_pixels(strip_mask, 0, 0, 0);
        animate_led_show_strip(strip_mask);
        delay(flash_delay);
    }
    delay(end_pause);
}


void animate_led_cyclone_bounce(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint8_t red, green, blue; 
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    for (int i = 0; i < strip_size - eye_size - 2; i++) // "-2" is CYA
    {
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
        animate_led_set_all_pixels(strip_mask, 0, 0, 0);
        animate_led_set_pixel(strip_mask, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip_mask,(i + j), red, green, blue);
        }
        animate_led_set_pixel(strip_mask, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip(strip_mask);
        delay(speed_delay);
    }
    delay(return_delay);
    for (int i = strip_size - eye_size - 2; i > 0; i--)
    {
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
        animate_led_set_all_pixels(strip_mask, 0, 0, 0); 
        animate_led_set_pixel(strip_mask, i , red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip_mask, i + j, red, green, blue);
        }
        animate_led_set_pixel(strip_mask, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip(strip_mask);
        delay(speed_delay);
    }
    delay(return_delay);
	animate_led_set_all_pixels(strip_mask, 0, 0, 0);
}


void animate_led_center_to_outside(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    // interrupts not handled yet!
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
    uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    for (int i = ((strip_size - eye_size) / 2); i >= 0; i--)
    {
        animate_led_set_all_pixels(strip_mask, 0,0,0);
        animate_led_set_pixel(strip_mask, i, red/10, green/10, blue/10);
        for (int j = 1; j<= eye_size; j++)
        {
            animate_led_set_pixel(strip_mask, i + j, red, green, blue);
        }
        animate_led_set_pixel(strip_mask, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_set_pixel(strip_mask, strip_size - i, red/10, green/10, blue/10);
        for (int j = 1; j<= eye_size; j++)
        {
            animate_led_set_pixel(strip_mask, strip_size - i - j, red, green, blue);
        }
        animate_led_set_pixel(strip_mask, strip_size - i - eye_size - 1, red/10, green/10, blue/10);
        animate_led_show_strip(strip_mask);
        delay((float_t)speed_delay / animate_led_speed_factor());
    }
    delay(return_delay);
}


void animate_led_outside_to_center(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    // interrupts not handled yet!
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
    uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    for (int i = 0; i <= ((strip_size - eye_size) / 2 ); i++)
    {
        animate_led_set_all_pixels(strip_mask, 0, 0, 0);
        animate_led_set_pixel(strip_mask, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip_mask, i+j, red, green, blue);
        }
        animate_led_set_pixel(strip_mask, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_set_pixel(strip_mask, strip_size - i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip_mask, strip_size - i - j, red, green, blue);
        }
        animate_led_set_pixel(strip_mask, strip_size - i - eye_size - 1, red/10, green/10, blue/10);
        animate_led_show_strip(strip_mask);
        delay((float_t)speed_delay / animate_led_speed_factor());
    }
    delay(return_delay);
}


void animate_led_left_to_right(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    // interrupts not handled yet!
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
    uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    for (int i = 0; i < strip_size - eye_size - 2; i++)
    {
        animate_led_set_all_pixels(strip_mask, 0, 0, 0);
        animate_led_set_pixel(strip_mask, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++) animate_led_set_pixel(strip_mask, i + j, red, green, blue);
        animate_led_set_pixel(strip_mask, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip(strip_mask);
        delay((float_t)speed_delay / animate_led_speed_factor());
    }
    delay(return_delay);
}


void animate_led_right_to_left(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    // interrupts not handled yet!
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
    uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    for (int i = strip_size - eye_size - 2; i > 0; i--)
    {
        animate_led_set_all_pixels(strip_mask, 0, 0, 0);
        animate_led_set_pixel(strip_mask, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++) animate_led_set_pixel(strip_mask, i + j, red, green, blue);
        animate_led_show_strip(strip_mask);
        delay((float_t)speed_delay / animate_led_speed_factor());
    }
    delay(return_delay);
}


void animate_led_new_kitt(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    // interrupts not handled yet!
    animate_led_right_to_left((uint16_t)STRIP_BIT_ALL_SET, color_led_cur_color_hex(), eye_size, speed_delay, return_delay);
    animate_led_left_to_right((uint16_t)STRIP_BIT_ALL_SET, color_led_cur_color_hex(), eye_size, speed_delay, return_delay);
    animate_led_outside_to_center((uint16_t)STRIP_BIT_ALL_SET, color_led_cur_color_hex(), eye_size, speed_delay, return_delay);
    animate_led_center_to_outside((uint16_t)STRIP_BIT_ALL_SET, color_led_cur_color_hex(), eye_size, speed_delay, return_delay);
    animate_led_left_to_right((uint16_t)STRIP_BIT_ALL_SET, color_led_cur_color_hex(), eye_size, speed_delay, return_delay);
    animate_led_right_to_left((uint16_t)STRIP_BIT_ALL_SET, color_led_cur_color_hex(), eye_size, speed_delay, return_delay);
    animate_led_outside_to_center((uint16_t)STRIP_BIT_ALL_SET, color_led_cur_color_hex(), eye_size, speed_delay, return_delay);
    animate_led_center_to_outside((uint16_t)STRIP_BIT_ALL_SET, color_led_cur_color_hex(), eye_size, speed_delay, return_delay);
}


void animate_led_twinkle_multiple_colors(strip_mask_t strip_mask, uint32_t* color_array, uint16_t count, uint16_t speed_delay, bool only_one)
{
	uint8_t red, green, blue; 
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
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
	for (int i = 0; i < count; i++)
    {
	    if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
        for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
			animate_led_set_pixel(active_strip_array[yyy], random_num(0, ws2812_get_strip_size(active_strip_array[yyy])), (((color_array[yyy] & 0xFF0000) >> 16)), (((color_array[yyy] & 0x00FF00) >> 8)), ((color_array[yyy] & 0x0000FF)));
			animate_led_show_strip(strip_mask);
		}
        if (only_one) animate_led_set_all_pixels(strip_mask, 0, 0, 0);
    }
	delay((float_t)speed_delay / animate_led_speed_factor());
}


void animate_led_twinkle(strip_mask_t strip_mask, color_hex_code_e color, uint16_t count, uint16_t speed_delay, bool only_one)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    //animate_led_set_all_pixels(ALL_STRIPS, 0, 0, 0);
    for (int i = 0; i < count; i++)
    {
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
        animate_led_set_pixel(strip_mask, random_num(0, strip_size), red, green, blue);
        animate_led_show_strip(strip_mask);
        delay(speed_delay);
        if (only_one) animate_led_set_all_pixels(strip_mask, 0, 0, 0);
    }
    delay((float_t)speed_delay / animate_led_speed_factor());
}


void animate_led_twinkle_random(strip_mask_t strip_mask, uint16_t count, uint16_t speed_delay, bool only_one)
{
    animate_led_set_all_pixels(strip_mask, 0, 0, 0);
    uint8_t dummy_red, dummy_green, dummy_blue; // not used but not worth creating a unique function IMO
    for (int i = 0; i < count; i++)
    {
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
        animate_led_set_pixel(strip_mask, random_num(0, g_max_strip_length), random_num(0, 255), random_num(0, 255), random_num(0, 255));
        animate_led_show_strip(strip_mask);
        delay(speed_delay);
        if (only_one) animate_led_set_all_pixels(strip_mask, 0, 0, 0);
    }
    delay((float_t)speed_delay / animate_led_speed_factor());
}


void animate_led_sparkle_only_random_color(strip_mask_t strip_mask, bool fill, uint16_t speed_delay)
{
	float percent_to_fill = 0.7;
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	uint16_t num_active_leds = ws2812_get_num_active_animation_leds(strip_mask);
    uint8_t dummy_red, dummy_green, dummy_blue; // not used but not worth creating a unique function IMO
	for (uint16_t iii = 0; iii < (percent_to_fill * (float)num_active_leds); iii++)
	{
	    if (g_animate_led_interrupt) if (animate_led_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
		int pix = random_num(0, strip_size);
		animate_led_set_pixel(strip_mask, pix, random_num(0, 255), random_num(0, 255), random_num(0, 255));
		animate_led_show_strip(strip_mask);
		delay(speed_delay);
		if (!fill) animate_led_set_pixel(strip_mask, pix, 0, 0, 0);
	}
}


void animate_led_sparkle_random_color(strip_mask_t strip_mask, bool fill, uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	//for (uint16_t iii = 0; iii < (percent_to_fill * (float)ws2812_get_num_active_animation_leds(strip_mask)); iii++)
	///{
		int pix = random_num(0, strip_size);
		animate_led_set_pixel(strip_mask, pix, random_num(0, 255), random_num(0, 255), random_num(0, 255));
		animate_led_show_strip(strip_mask);
		delay(speed_delay);
		if (!fill) animate_led_set_pixel(strip_mask, pix, 0, 0, 0);
	//}
}


void animate_led_sparkle(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    int pix = random_num(0, strip_size);
    animate_led_set_pixel(strip_mask, pix, red, green, blue);
    animate_led_show_strip(strip_mask);
    delay((float_t)speed_delay / animate_led_speed_factor());
    animate_led_set_pixel(strip_mask, pix, 0, 0, 0);
}


void animate_led_running_lights(strip_mask_t strip_mask, color_hex_code_e color)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    uint16_t pos = 0;
    for (int i = 0; i < strip_size * 2; i++)
    {
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
        pos++;
        for(int i = 0; i < strip_size; i++)
        {
            animate_led_set_pixel(strip_mask, i, ((sin(i + pos) * 127 + 128) / 255) * red, ((sin(i + pos) * 127 + 128) / 255) * green, ((sin(i + pos) * 127 + 128) / 255) * blue); 
        }
        animate_led_show_strip(strip_mask);
		delay(100 / animate_led_speed_factor()); // TODO remove the magic number here!!!
    }
}


void animate_led_color_wipe(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    for (uint16_t i = 0; i < strip_size; i++)
    {
        animate_led_set_pixel(strip_mask, i, red, green, blue);
        animate_led_show_strip(strip_mask);
        delay((float_t)speed_delay / animate_led_speed_factor());
    }
    for (uint16_t i = 0; i < g_max_strip_length; i++)
    {
        animate_led_set_pixel(strip_mask, i, 0, 0, 0);
        animate_led_show_strip(strip_mask);
        delay((float_t)speed_delay / animate_led_speed_factor());
    }
}


void animate_led_rainbow_cycle(strip_mask_t strip_mask, uint16_t speed_delay)
{
	uint8_t dummy_red, dummy_green, dummy_blue;
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
    uint8_t *c;
    uint16_t i, j;
    //for (j = 0; j < 256 * 5; j++)
    for (j = 0; j < 256 * 5; j++)
    {
        if (g_animate_led_interrupt) if (animate_led_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
        for (i = 0; i < strip_size; i++)
        {
            if (g_animate_led_interrupt) if (animate_led_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
            c = animate_led_wheel(((i * 256 / strip_size) + j) & 255);
            animate_led_set_pixel(strip_mask, i, *c, *(c + 1), *(c + 2));
        }
        animate_led_show_strip(strip_mask);
        delay((float_t)speed_delay / animate_led_speed_factor());
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

    
void animate_led_theater_chase_multiple_colors(strip_mask_t strip_mask, uint32_t* color_array, uint16_t speed_delay)
{
	uint8_t red, green, blue; 
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
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
	for (int j = 0; j < 100; j++)
    {
        for (int q = 0; q < 3; q++)
        {
            if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
            for (int i = 0; i < strip_size; i += 3) 
            {
            	for (int yyy = 0; yyy < num_active_strips; yyy++)
				{
					animate_led_set_pixel(active_strip_array[yyy], i + 	q, (((color_array[yyy] & 0xFF0000) >> 16)), (((color_array[yyy] & 0x00FF00) >> 8)), ((color_array[yyy] & 0x0000FF)));
				}
            }
            animate_led_show_strip(strip_mask);
            if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
            delay((float_t)speed_delay / animate_led_speed_factor());
            for (int i = 0; i < strip_size; i += 3) 
            {
            	for (int yyy = 0; yyy < num_active_strips; yyy++)
				{
					animate_led_set_pixel(active_strip_array[yyy], i + q, 0, 0, 0); 
				}
       		}
        }
    }
}


void animate_led_theater_chase(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    for (int j = 0; j < 10; j++)
    {
        for (int q = 0; q < 3; q++)
        {
            if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
            for (int i = 0; i < strip_size; i += 3) animate_led_set_pixel(strip_mask, i + q, red, green, blue); // turn every third pixel on
            animate_led_show_strip(strip_mask);
            if (g_animate_led_interrupt) if (animate_led_check_interrupts(&red, &green, &blue)) return;
            delay((float_t)speed_delay / animate_led_speed_factor());
            for (int i = 0; i < strip_size; i += 3) animate_led_set_pixel(strip_mask, i + q, 0, 0, 0); // turn everty third pixel off
        }
    }
}


void animate_led_theater_chase_rainbow(strip_mask_t strip_mask, uint16_t speed_delay)
{
	uint8_t dummy_red, dummy_green, dummy_blue;
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
    uint8_t *c;
    for (int j = 0; j < 256; j++) // cycel all 256 colors in the animate_led_wheel
    {
        for (int q = 0; q < 3; q++)
        {
            if (g_animate_led_interrupt) if (animate_led_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
            for (int i = 0; i < strip_size; i = i + 3)
            {
                if (g_animate_led_interrupt) if (animate_led_check_interrupts(&dummy_red, &dummy_green, &dummy_blue)) return;
                c = animate_led_wheel((i + j) % 255);
                animate_led_set_pixel(strip_mask, i + q, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            animate_led_show_strip(strip_mask);
            delay((float_t)speed_delay / animate_led_speed_factor());
            for (int i = 0; i < strip_size; i = i + 3) animate_led_set_pixel(strip_mask, i + q, 0, 0, 0); // turn every third pixel off
        }
    }
}


void animate_led_bouncing_balls(strip_mask_t strip_mask, color_hex_code_e color, int ball_count)
{
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
    float gravity = -9.81;
    int start_height = 1;
    float height[ball_count];
    float impact_velocity_start = sqrt(-2 * gravity * start_height);
    float impact_velocity[ball_count];
    float time_since_last_bounce[ball_count];
    int pos[ball_count];
    long clock_time_since_last_bounce[ball_count];
    float dampening[ball_count];
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    for (int i = 0; i < ball_count; i++)
    {
        clock_time_since_last_bounce[i] = millis();
        height[i] = start_height;
        pos[i] = 0;
        impact_velocity[i] = impact_velocity_start;
        time_since_last_bounce[i] = 0;
        dampening[i] = 0.90 - (float)i / pow(ball_count, 2);
    }

	for (int i = 0; i < ball_count; i++)
	{
		time_since_last_bounce[i] = millis() - clock_time_since_last_bounce[i];
		height[i] = 0.5 * gravity * pow(time_since_last_bounce[i] / 1000, 2.0) + impact_velocity[i] * time_since_last_bounce[i] / 1000;
		if (height[i] < 0)
		{
			height[i] = 0;
			impact_velocity[i] = dampening[i] * impact_velocity[i];
			clock_time_since_last_bounce[i] = millis();
			if (impact_velocity[i] < 0.01)
			{
				impact_velocity[i] = impact_velocity_start;
			}
		}
		pos[i] = round(height[i] * (strip_size - 1) / start_height);
	}
	for (int i = 0; i < ball_count; i++)
	{
		animate_led_set_pixel(strip_mask, pos[i], red, green, blue);
	}
	animate_led_show_strip(strip_mask);
	animate_led_set_all_pixels(strip_mask, 0, 0, 0);
}


void animate_led_meteor_rain(strip_mask_t strip_mask, color_hex_code_e color, uint8_t meteor_size, uint8_t meteor_trail_decay, bool meteor_random_decay, int speed_delay)
{
    // interrupts not handled yet!
	//uint16_t offset = 0;
	uint16_t strip_size = ws2812_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16);
	green = ((color & 0x00FF00) >> 8);
	blue = (color & 0x0000FF);
    animate_led_set_all_pixels(strip_mask, 0, 0, 0);
    for(int i = 0; i < strip_size + 50; i++) // 50 arbitrarily chosen SRW
    {
        for (int j = 0; j < strip_size; j++)
        {
            if ((!meteor_random_decay) || (random_num(0, 10) > 5))
            {
            	if (strip_mask == g_all_strip_mask)
				{
					for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
					{
						//offset = animate_led_get_strip_offset(strip_bit);
						if (ws2812_pixel_is_in_strip_range(strip_bit, j)) ;//animate_led_fade_to_black(strip_mask, j, meteor_trail_decay);
					}
				}
				else
				{
					for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = strip_bit + 1)
					{
						if (strip_mask & strip_bit)
						{
							//offset = animate_led_get_strip_offset(strip_bit);
							if (ws2812_pixel_is_in_strip_range(strip_bit, j)) animate_led_fade_to_black(strip_mask, j, meteor_trail_decay);
						}
					}
				}
            }
        }
        for (int j = 0; j < meteor_size; j++)
        {
            if ((i - j < strip_size) && (i - j >= 0))
            {
            	if (strip_mask == g_all_strip_mask)
				{
					for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
					{
						//offset = animate_led_get_strip_offset(strip_bit);
						if (ws2812_pixel_is_in_strip_range(strip_bit, i - j)) animate_led_set_pixel(strip_mask, i - j, red, green, blue);
					}
				}
				else
				{
					for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = strip_bit + 1)
					{
						if (strip_mask & strip_bit)
						{
							//offset = animate_led_get_strip_offset(strip_bit);
							if (ws2812_pixel_is_in_strip_range(strip_bit, i - j)) animate_led_set_pixel(strip_mask, i - j, red, green, blue);
						}
					}
				}
            }
        }
//        if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
//        {
//        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
//			return;
//        }
        animate_led_show_strip(strip_mask);
        delay((float_t)speed_delay / animate_led_speed_factor());
    }
}


void animate_led_fade_to_black(strip_mask_t strip_mask, uint16_t pixel, uint8_t fade_value)
{
    // wtf?  update?
	if (STRIP_BIT_ALL_SET == strip_mask)
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
		{
			//offset = animate_led_get_strip_offset(strip_bit);
			//if (ws2812_pixel_is_in_strip_range(strip_bit, pixel)) led_strip[pixel + offset].fadeToBlackBy(fade_value);
		}
	}	
	else
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = strip_bit + 1)
		{
			if (strip_mask & strip_bit)
			{
				//offset = animate_led_get_strip_offset(strip_bit);
				//if (ws2812_pixel_is_in_strip_range(strip_bit, pixel)) led_strip[pixel + offset].fadeToBlackBy(fade_value);
			}
		}		
	}
}


void animate_led_set_pixel(strip_mask_t strip_mask, uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t adj_red = red / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	uint8_t adj_green = green / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	uint8_t adj_blue = blue / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	if (STRIP_BIT_ALL_SET == strip_mask)
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
		{
			//offset = animate_led_get_strip_offset(strip_bit);
			if (ws2812_pixel_is_in_strip_range(strip_bit, pixel)) ws2812b_set_led(strip_bit, pixel, adj_red, adj_green, adj_blue);
		}
	}
	else
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
		{
			if (strip_mask & strip_bit)
			{
				//offset = animate_led_get_strip_offset(strip_bit);
				if (ws2812_pixel_is_in_strip_range(strip_bit, pixel)) ws2812b_set_led(strip_bit, pixel, adj_red, adj_green, adj_blue);
			}
		}
	}
	//animate_led_show_strip();
}


void animate_led_set_all_pixels(strip_mask_t strip_mask, uint8_t red, uint8_t green, uint8_t blue)
{		
	uint16_t strip_size = 0;
	uint8_t adj_red = red / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	uint8_t adj_green = green / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	uint8_t adj_blue = blue / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	if (strip_mask == g_all_strip_mask)
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
		{
		    strip_size = ws2812_get_strip_size(strip_bit);
			//offset = animate_led_get_strip_offset(strip_bit);
			for (uint16_t iii = 0; iii < strip_size; iii++) ws2812b_set_led(strip_bit, iii, adj_red, adj_green, adj_blue);
		}
	}
	else
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
		{
			if (strip_mask & strip_bit)
			{
				//offset = animate_led_get_strip_offset(strip_bit);
				strip_size = ws2812_get_strip_size(strip_bit);
				for (uint16_t yyy = 0; yyy < strip_size; yyy++) ws2812b_set_led(strip_bit, yyy, adj_red, adj_green, adj_blue);
			}
		}
	}
    animate_led_show_strip(strip_mask);
}


#define TEST_MODE
static void handle_count_color_delay(const animation_loop_iterations_e max_iterations, const animation_delay_ms_e animation_delay_ms)
{
    if (ANIMATION_DELAY_MS_0 != animation_delay_ms) delay(animation_delay_ms);
    g_animation_iterations++;
    if (MASTER_LED_STATE_DEMO == g_master_led_state)
    {
        if (max_iterations == g_animation_iterations)
        {
#if defined(TEST_MODE)
            g_led_state = (led_state_e) (g_led_state + 1);
            if (NUM_LED_STATES == g_led_state) g_led_state = LED_STATE_FIRST;
#else
            g_led_state = animate_led_state_randomize(g_led_state);
#endif
            g_animation_iterations = 0;
        }
    }
    if (MASTER_COLOR_STATE_DEMO == g_master_color_state) color_led_randomize();
    //else color_led_adjust_color();
    // if not demo state then stay in current LED state forever until switched by user
}



void task_animate_led(void *argument)
{
    uint32_t button_pressed_count = 0;
	board_init_stop_timer();
    animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
    osDelay(1000);
    bool button_press_b_detected = false;
    bool button_press_c_detected = false;
	while (1)
	{

	    if (!button_press_c_detected && board_init_button_is_pressed(PUSH_BUTTON_C))
	    {
	        button_press_c_detected = true;
	    }
	    else if (button_press_c_detected && board_init_button_is_pressed(PUSH_BUTTON_C))
	    {
	        button_press_c_detected = false;
	        while (board_init_button_is_pressed(PUSH_BUTTON_C))
            {
                if ((board_init_button_on_count(PUSH_BUTTON_C) > button_pressed_count) && \
                                board_init_button_on_count(PUSH_BUTTON_C) > 50)
                {
                    // the button is being held down!
                    color_led_enter_demo_state();
                    while(board_init_button_is_pressed(PUSH_BUTTON_C)); // wait for release
                    // clear the counts..
                    board_init_button_on_count_clear(PUSH_BUTTON_C);
                    for (uint8_t iii = 0; iii < 3; iii++)
                    {
                        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLUE);
                        osDelay(100);
                        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
                        osDelay(100);
                    }
                    osDelay(500);
                    break;
                }
                else if (!board_init_button_on_count(PUSH_BUTTON_C))
                {
                    break;
                }
            }
	    }
        if (!button_press_b_detected && board_init_button_is_pressed(PUSH_BUTTON_B))
        {
            button_press_b_detected = true;
        }
        else if (button_press_c_detected && board_init_button_is_pressed(PUSH_BUTTON_C))
        {
            button_press_b_detected = false;
            while (board_init_button_is_pressed(PUSH_BUTTON_B))
            {
                if ((board_init_button_on_count(PUSH_BUTTON_B) > button_pressed_count) && \
                                board_init_button_on_count(PUSH_BUTTON_B) > 50)
                {
                    // the button is being held down!
                    animate_led_enter_demo_state();
                    while(board_init_button_is_pressed(PUSH_BUTTON_B)); // wait for release
                    // clear the counts..
                    board_init_button_on_count_clear(PUSH_BUTTON_B);
                    for (uint8_t iii = 0; iii < 3; iii++)
                    {
                        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLUE);
                        osDelay(100);
                        animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
                        osDelay(100);
                    }
                    osDelay(500);
                    break;
                }
                else if (!board_init_button_on_count(PUSH_BUTTON_B))
                {
                    break;
                }
            }
	    }
//	    if (g_master_led_demo_state_exit_flag || g_color_led_demo_state_exit_flag)
//	    {
//	        g_color_led_demo_state_exit_flag = false;
//	        g_master_led_demo_state_exit_flag = false;
//	        for (uint8_t iii = 0; iii < 3; iii++)
//	        {
//                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_RED);
//                osDelay(100);
//                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
//                osDelay(100);
//	        }
//	        osDelay(500); // ehh needed?
//	    }
//	    else if (g_master_led_demo_state_enter_flag)
//	    {
//	        g_master_led_demo_state_enter_flag = false;
//	        for (uint8_t iii = 0; iii < 3; iii++)
//            {
//                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_GREEN);
//                osDelay(100);
//                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
//                osDelay(100);
//            }
//	        osDelay(500); // ehh needed?
//	    }
//	    else if (g_color_led_demo_state_enter_flag)
//        {
//	        g_color_led_demo_state_enter_flag = false;
//            for (uint8_t iii = 0; iii < 3; iii++)
//            {
//                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLUE);
//                osDelay(100);
//                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_BLACK);
//                osDelay(100);
//            }
//            osDelay(500); // ehh needed?
//        }
	    switch(g_led_state)
        {
            case LED_STATE_WHITE_COLOR:
                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, COLOR_HEX_WHITE);
                handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_1, ANIMATION_DELAY_MS_5000);
            break;
            case LED_STATE_SOLID_COLOR:
                animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, color_led_cur_color_hex());
                handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_5000);
            break;
            case LED_STATE_SPARKLE_NO_FILL:
                // SRW OK!!!
                // need to force all colors off before transitioning to this state
                animate_led_turn_all_pixels_off();
                animate_led_sparkle_only_random_color(STRIP_BIT_ALL_SET, false, random_num(20,80));//random(0, 50));
                handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
            break;
            case LED_STATE_SPARKLE_FILL:
                // SRW ok!!!
                animate_led_sparkle_only_random_color(STRIP_BIT_ALL_SET, true, random_num(20,80));
                handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_10, ANIMATION_DELAY_MS_0);
            break;
            case LED_STATE_RAINBOW_CYCLE:
                // SRW OK!!!
                animate_led_rainbow_cycle(STRIP_BIT_ALL_SET, 0);
                handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
            break;
            case LED_STATE_THEATER_CHASE:
                // SRW ok !!!
                animate_led_theater_chase(STRIP_BIT_ALL_SET, color_led_cur_color_hex(), animate_led_delay_in_animations());
                handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_10, ANIMATION_DELAY_MS_0);
            break;
            case LED_STATE_THEATER_CHASE_RAINBOW:
                // SRW ok!!!!
                animate_led_theater_chase_rainbow(STRIP_BIT_ALL_SET, animate_led_delay_in_animations());
                g_led_state = LED_STATE_TWINKLE;
                handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_2, ANIMATION_DELAY_MS_0);
            break;
            case LED_STATE_FADE_IN_AND_OUT:
                // SRW ok!!!
                animate_led_fade_in_fade_out((uint16_t)STRIP_BIT_ALL_SET, color_led_cur_color_hex());
                handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_10, ANIMATION_DELAY_MS_0);
            break;
            case LED_STATE_TWINKLE:
                // SRW ok!!!
                animate_led_turn_all_pixels_off();
                animate_led_twinkle(STRIP_BIT_ALL_SET, color_led_cur_color_hex(), (uint32_t)((float)NUM_LEDS * (float)0.9), animate_led_delay_in_animations(), false);
                handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
            break;
            case LED_STATE_SPELL:
                // SRW ok!!!
                animate_led_only_spell_word(STRIP_BIT_ALL_SET, color_led_cur_color_hex(), 30);
                handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_10, ANIMATION_DELAY_MS_0);
            break;
            default:
            break;
        }

	        //osDelay(1000);

//	    if (gb_a_flag)
//	    {
//	        gb_a_flag = false;
//	        color = COLOR_HEX_MAROON;
//	    }
//	    else if (gb_b_flag)
//	    {
//	        gb_b_flag = false;
//	        color = COLOR_HEX_NAVY;
//	    }
//	    else if (gb_c_flag)
//        {
//	        gb_c_flag = false;
//	        color = COLOR_HEX_PURPLE;
//        }
//	    else if (gb_d_flag)
//        {
//	        gb_d_flag = false;
//	        color = COLOR_HEX_GREEN;
//        }
//        animate_led_only_spell_word(STRIP_BIT_1, color, 10);
//        ws2812b_show(1);
//        osDelay(100);
//        while(!datasentflag) osDelay(10);
//        datasentflag = 0;
//
//        animate_led_only_spell_word(STRIP_BIT_1, COLOR_HEX_BLACK, 10);
//        ws2812b_show(1);
//        osDelay(100);
//        while(!datasentflag) osDelay(10);
//        datasentflag = 0;
//		color = COLOR_HEX_MAROON;
//		animate_led_only_spell_word(STRIP_BIT_1, color, 10);
//		ws2812b_show(1);
//		osDelay(50);
//		while(!datasentflag) osDelay(10);
//		datasentflag = 0;
//
//		color = COLOR_HEX_PURPLE;
//		animate_led_only_spell_word(STRIP_BIT_1, color, 10);
//		ws2812b_show(1);
//		osDelay(50);
//		while(!datasentflag) osDelay(10);
//		datasentflag = 0;
//
//		color = COLOR_HEX_NAVY;
//		animate_led_only_spell_word(STRIP_BIT_1, color, 10);
//		ws2812b_show(1);
//		osDelay(50);
//		while(!datasentflag) osDelay(10);
//		datasentflag = 0;
	}
}


// kind of lame..  I don't plan on using
/*
void animate_led_fire(uint16_t cooling, uint16_t sparking, uint16_t speed_delay)
{
    static uint8_t heat[NUM_LEDS];
    uint16_t cooldown;
    for (int i = 0; i < NUM_LEDS; i++)
    {
        cooldown = random_num(0, ((cooling * 10) / NUM_LEDS) + 2);
        if (cooldown > heat[i])
        {
            heat[i] = 0;
        }
        else
        {
            heat[i] = heat[i] - cooldown;
        }
    }
    for (int k = NUM_LEDS - 1; k >= 2; k--)
    {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }
    if (random_num(255) < sparking)
    {
        uint16_t y = random_num(7);
        heat[y] = heat[y] + random_num(160, 255);
    }
    for (int j = 0; j < NUM_LEDS; j++)
    {
        animate_led_set_pixel_heat_color(j, heat[j]);
    }
    animate_led_show_strip();
    delay(speed_delay);
}


void animate_led_set_pixel_heat_color(int pix, uint8_t temp)
{
    uint8_t t192 = round((temp / 255.0) *191);
    uint8_t heatramp = t192 & 0x3F;
    heatramp <<= 2;

    if(t192 > 0x80)
    {
        animate_led_set_pixel(ALL_STRIPS, pix, 255, 255, heatramp); // hottest
    }
    else if (t192 > 0x40)
    {
        animate_led_set_pixel(ALL_STRIPS, pix, 255, heatramp, 0); // medium
    }
    else
    {
        animate_led_set_pixel(ALL_STRIPS, pix, heatramp, 0, 0); // coolest
    }
    
}
*/

