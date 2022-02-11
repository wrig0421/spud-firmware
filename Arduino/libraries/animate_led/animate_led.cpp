// SRW
#include <stdint.h>
#include <stdbool.h>
#include "FastLED.h"
#include "color_led.h"
//#include <FastLED>
#include "animate_led.h"

#define PIN_STRIP_1 8
//#define PIN_STRIP_1 12

#if defined(MULTIPLE_STRIPS)
//#define PIN_STRIP_2 8 
#define PIN_STRIP_2 12
//#define PIN_STRIP_3 
//#define PIN_STRIP_5 
//#define PIN_STRIP_6 
//#define PIN_STRIP_7 
//#define PIN_STRIP_8  
//#define PIN_STRIP_9 
#endif

// if strip is not in use then offset is 0 

bool g_interrupt_flag[NUM_ISR] = {false};
uint32_t g_max_strip_length = 0;

uint16_t g_strip_offset[NUM_STRIPS] = {0};

//CLEDController *controllers[2];
CLEDController *controller[NUM_STRIPS];
//CRGB led_strip[NUM_LEDS];

CRGB *led_strip;

led_speed_e g_led_speed = LED_SPEED_5X;
//led_speed_e g_led_speed = LED_SPEED_1X;
//led_state_e g_led_state = LED_STATE_FIRST;
//led_state_e g_led_state = LED_STATE_TWO_TONE;
led_state_e g_led_state = LED_STATE_WHITE_COLOR;

uint16_t g_delay_between_animations_ms = 1000;
uint16_t g_delay_in_animation_ms = 100; // where applicable of course
uint32_t g_iterations = 0; 
uint16_t g_num_leds = 0;
uint16_t g_all_strip_mask = 0;

uint16_t animate_led_get_number_of_active_strips(const strip_mask_t strip_mask)
{
	uint16_t num_active_strips = 0;
	for (strip_bit_e iii = STRIP_BIT_1; iii < STRIP_BIT_NUM_STRIPS; iii = (strip_bit_e)(iii + 1))
	{
		if (iii & strip_mask) num_active_strips++;
	}
	return num_active_strips;
}

// if STRIP_BIT_NO_MORE_SET returned then all bits have been encountered 
static strip_bit_e animate_led_get_next_active_strip(const strip_mask_t strip_mask, const strip_bit_e prev_strip_bit)
{
	// STRIP_BIT_ALL_SET is not a valid option!  
	for (strip_bit_e iii = prev_strip_bit; iii < STRIP_BIT_NUM_STRIPS; iii = (strip_bit_e)(iii + 1))
	{
#if defined(STRIP_1_LENGTH)
		if (iii & strip_mask) return iii;
#endif
#if defined(STRIP_2_LENGTH)
		if (iii & strip_mask) return iii;
#endif
#if defined(STRIP_3_LENGTH)
		if (iii & strip_mask) return iii;
#endif
#if defined(STRIP_4_LENGTH)
		if (iii & strip_mask) return iii;
#endif
#if defined(STRIP_5_LENGTH)
		if (iii & strip_mask) return iii;
#endif
#if defined(STRIP_6_LENGTH)
		if (iii & strip_mask) return iii;
#endif
#if defined(STRIP_7_LENGTH)
		if (iii & strip_mask) return iii;
#endif
#if defined(STRIP_8_LENGTH)
		if (iii & strip_mask) return iii;
#endif
#if defined(STRIP_9_LENGTH)
		if (iii & strip_mask) return iii;
#endif	
	}
	return STRIP_BIT_NO_MORE_SET;  // if this is returned 
}


static uint16_t animate_led_get_num_active_animation_leds(const strip_mask_t strip_mask)
{
	uint16_t strip_size = 0;
	if (STRIP_BIT_ALL_SET == strip_mask) strip_size = g_num_leds;
	else
	{
#if defined(STRIP_1_LENGTH)
		if (STRIP_BIT_1 & strip_mask) strip_size += STRIP_1_LENGTH;
#endif
#if defined(STRIP_2_LENGTH)
		if (STRIP_BIT_2 & strip_mask) strip_size += STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
		if (STRIP_BIT_3 & strip_mask) strip_size += STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
		if (STRIP_BIT_4 & strip_mask) strip_size += STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
		if (STRIP_BIT_5 & strip_mask) strip_size += STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
		if (STRIP_BIT_6 & strip_mask) strip_size += STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
		if (STRIP_BIT_7 & strip_mask) strip_size += STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
		if (STRIP_BIT_8 & strip_mask) strip_size += STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
		if (STRIP_BIT_9 & strip_mask) strip_size += STRIP_9_LENGTH;
#endif
	}
	return strip_size;
}


static uint16_t animate_led_get_max_strip_size(const strip_mask_t strip_mask)
{
	uint16_t strip_size = 0;
	if (STRIP_BIT_ALL_SET == strip_mask) strip_size = g_max_strip_length;
	else 
	{
#if defined(STRIP_1_LENGTH)
		if ((STRIP_BIT_1 & strip_mask) && (strip_size < STRIP_1_LENGTH)) strip_size = STRIP_1_LENGTH;
#endif
#if defined(STRIP_2_LENGTH)
		if ((STRIP_BIT_2 & strip_mask) && (strip_size < STRIP_2_LENGTH)) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
		if ((STRIP_BIT_3 & strip_mask) && (strip_size < STRIP_3_LENGTH)) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
		if ((STRIP_BIT_4 & strip_mask) && (strip_size < STRIP_4_LENGTH)) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
		if ((STRIP_BIT_5 & strip_mask) && (strip_size < STRIP_5_LENGTH)) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
		if ((STRIP_BIT_6 & strip_mask) && (strip_size < STRIP_6_LENGTH)) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
		if ((STRIP_BIT_7 & strip_mask) && (strip_size < STRIP_7_LENGTH)) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
		if ((STRIP_BIT_8 & strip_mask) && (strip_size < STRIP_8_LENGTH)) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
		if ((STRIP_BIT_9 & strip_mask) && (strip_size < STRIP_9_LENGTH)) strip_size = STRIP_9_LENGTH;
#endif
	}
	return strip_size;
}


static uint16_t animate_led_get_strip_size(const strip_bit_e strip_bit)
{
	uint16_t strip_size = 0;
	if (STRIP_BIT_ALL_SET == strip_bit) strip_size = g_max_strip_length;
	else 
	{
#if defined(STRIP_1_LENGTH)
		if (STRIP_BIT_1 == strip_bit) strip_size = STRIP_1_LENGTH;
#endif
#if defined(STRIP_2_LENGTH)
		else if (STRIP_BIT_2 == strip_bit) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
		else if (STRIP_BIT_3 == strip_bit) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
		else if (STRIP_BIT_4 == strip_bit) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
		else if (STRIP_BIT_5 == strip_bit) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
		else if (STRIP_BIT_6 == strip_bit) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
		else if (STRIP_BIT_7 == strip_bit) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
		else if (STRIP_BIT_8 == strip_bit) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
		else if (STRIP_BIT_9 == strip_bit) strip_size = STRIP_9_LENGTH;
#endif
	}
	return strip_size;
}


static bool animate_led_pixel_is_in_strip_range(strip_bit_e strip_bit, uint16_t pixel)
{
	bool return_val = false;
#if defined(STRIP_1_LENGTH)
	if ((STRIP_BIT_1 == strip_bit) && (pixel < STRIP_1_LENGTH)) return_val = true;
#endif
#if defined(STRIP_2_LENGTH)
	else if ((STRIP_BIT_2 == strip_bit) && (pixel < STRIP_2_LENGTH)) return_val = true;
#endif
#if defined(STRIP_3_LENGTH)
	else if ((STRIP_BIT_3 == strip_bit) && (pixel < STRIP_3_LENGTH)) return_val = true;
#endif
#if defined(STRIP_4_LENGTH)
	else if ((STRIP_BIT_4 == strip_bit) && (pixel < STRIP_4_LENGTH)) return_val = true;
#endif
#if defined(STRIP_5_LENGTH)
	else if ((STRIP_BIT_5 == strip_bit) && (pixel < STRIP_5_LENGTH)) return_val = true;
#endif
#if defined(STRIP_6_LENGTH)
	else if ((STRIP_BIT_6 == strip_bit) && (pixel < STRIP_6_LENGTH)) return_val = true;
#endif
#if defined(STRIP_7_LENGTH) 
	else if ((STRIP_BIT_7 == strip_bit) && (pixel < STRIP_7_LENGTH)) return_val = true;
#endif
#if defined(STRIP_8_LENGTH)
	else if ((STRIP_BIT_8 == strip_bit) && (pixel < STRIP_8_LENGTH)) return_val = true;
#endif
#if defined(STRIP_9_LENGTH)
	else if ((STRIP_BIT_9 == strip_bit) && (pixel < STRIP_9_LENGTH)) return_val = true;
#endif
	return return_val;
}


static uint16_t animate_led_get_strip_offset(const strip_bit_e strip_bit)
{
	uint16_t offset = 0;
#if defined(STRIP_1_LENGTH)
	if (STRIP_BIT_1 == strip_bit) offset = g_strip_offset[STRIP_NUM_1];
#endif
#if defined(STRIP_2_LENGTH)
	else if (STRIP_BIT_2 == strip_bit) offset = g_strip_offset[STRIP_NUM_2];
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_BIT_3 == strip_bit) offset = g_strip_offset[STRIP_NUM_3];
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_BIT_4 == strip_bit) offset = g_strip_offset[STRIP_NUM_4];
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_BIT_5 == strip_bit) offset = g_strip_offset[STRIP_NUM_5];
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_BIT_6 == strip_bit) offset = g_strip_offset[STRIP_NUM_6];
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_BIT_7 == strip_bit) offset = g_strip_offset[STRIP_NUM_7];
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_BIT_8 == strip_bit) offset = g_strip_offset[STRIP_NUM_8];
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_BIT_9 == strip_bit) offset = g_strip_offset[STRIP_NUM_9];
#endif
	return offset;
}


void animate_led_reset_state(void)
{
	g_led_state = LED_STATE_FIRST;
}


void animate_led_set_interrupt_flag(isr_e src)
{
	g_interrupt_flag[src] = true;
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
	uint8_t num_strips = NUM_STRIPS;
	g_all_strip_mask = 0;
	for (int iii = 0; iii < NUM_STRIPS; iii++)
	{
		g_all_strip_mask |= 1 << iii;
	}
	
	switch (num_strips)
	{
#if defined(STRIP_9_LENGTH)
		case 9:
			g_num_leds += STRIP_9_LENGTH;
			g_max_strip_length = STRIP_9_LENGTH;
			g_strip_offset[STRIP_NUM_9] = STRIP_8_LENGTH;
			//g_strip_offset[STRIP_NUM_9] = STRIP_9_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
		case 8:
			g_num_leds += STRIP_8_LENGTH;
			if (STRIP_8_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_8_LENGTH;
			g_strip_offset[STRIP_NUM_8] = STRIP_7_LENGTH;
			//g_strip_offset[STRIP_NUM_8] = STRIP_8_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
		case 7:
			g_num_leds += STRIP_7_LENGTH;
			if (STRIP_7_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_7_LENGTH;
			g_strip_offset[STRIP_NUM_7] = STRIP_6_LENGTH;
			//g_strip_offset[STRIP_NUM_7] = STRIP_7_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
		case 6:
			g_num_leds += STRIP_6_LENGTH;
			if (STRIP_6_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_6_LENGTH;
			g_strip_offset[STRIP_NUM_6] = STRIP_5_LENGTH;
			//g_strip_offset[STRIP_NUM_6] = STRIP_6_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
		case 5:
			g_num_leds += STRIP_5_LENGTH;
			if (STRIP_5_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_5_LENGTH;
			g_strip_offset[STRIP_NUM_5] = STRIP_4_LENGTH;
			//g_strip_offset[STRIP_NUM_5] = STRIP_5_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
		case 4:
			g_num_leds += STRIP_4_LENGTH;
			if (STRIP_4_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_4_LENGTH;
			g_strip_offset[STRIP_NUM_4] = STRIP_3_LENGTH;
			//g_strip_offset[STRIP_NUM_4] = STRIP_4_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
		case 3:
			g_num_leds += STRIP_3_LENGTH;
			if (STRIP_3_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_3_LENGTH;
			g_strip_offset[STRIP_NUM_3] = STRIP_2_LENGTH;
			//g_strip_offset[STRIP_NUM_3] = STRIP_3_LENGTH;
#endif
#if defined(STRIP_2_LENGTH)
		case 2:
			g_num_leds += STRIP_2_LENGTH;
			if (STRIP_2_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_2_LENGTH;
			g_strip_offset[STRIP_NUM_2] = STRIP_1_LENGTH;
			//g_strip_offset[STRIP_NUM_2] = STRIP_2_LENGTH;
#endif
		case 1:
			g_num_leds += STRIP_1_LENGTH;
			if (STRIP_1_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_1_LENGTH;
			g_strip_offset[STRIP_NUM_1] = 0;
			//g_strip_offset[STRIP_NUM_1] = STRIP_1_LENGTH;
		break;
	}
	led_strip = malloc(sizeof(led_strip) * g_num_leds);
	
	// PIN2 is strip1
	// PIN1 is strip2
#if defined(STRIP_1_LENGTH)
	controller[STRIP_NUM_1] = &FastLED.addLeds<WS2812, PIN_STRIP_1, GRB>(led_strip, 0, STRIP_1_LENGTH);
#endif
#if defined(STRIP_2_LENGTH)
	controller[STRIP_NUM_2] = &FastLED.addLeds<WS2812, PIN_STRIP_2, GRB>(led_strip + STRIP_1_LENGTH, 0, STRIP_2_LENGTH);
#endif
#if defined(STRIP_3_LENGTH)
	controller[STRIP_NUM_3] = &FastLED.addLeds<WS2812, PIN_STRIP_3, GRB>(led_strip + STRIP_2_LENGTH, 0, STRIP_3_LENGTH);
#endif
#if defined(STRIP_4_LENGTH)
	controller[STRIP_NUM_4] = &FastLED.addLeds<WS2812, PIN_STRIP_4, GRB>(led_strip + STRIP_3_LENGTH, 0, STRIP_4_LENGTH);
#endif
#if defined(STRIP_5_LENGTH)
	controller[STRIP_NUM_5] = &FastLED.addLeds<WS2812, PIN_STRIP_5, GRB>(led_strip + STRIP_4_LENGTH, 0, STRIP_5_LENGTH);
#endif
#if defined(STRIP_6_LENGTH)
	controller[STRIP_NUM_6] = &FastLED.addLeds<WS2812, PIN_STRIP_6, GRB>(led_strip + STRIP_5_LENGTH, 0, STRIP_6_LENGTH);
#endif
#if defined(STRIP_7_LENGTH)
	controller[STRIP_NUM_7] = &FastLED.addLeds<WS2812, PIN_STRIP_7, GRB>(led_strip + STRIP_6_LENGTH, 0, STRIP_7_LENGTH);
#endif
#if defined(STRIP_8_LENGTH)
	controller[STRIP_NUM_8] = &FastLED.addLeds<WS2812, PIN_STRIP_8, GRB>(led_strip + STRIP_7_LENGTH, 0, STRIP_8_LENGTH);
#endif
#if defined(STRIP_9_LENGTH)
	controller[STRIP_NUM_9] = &FastLED.addLeds<WS2812, PIN_STRIP_9, GRB>(led_strip + STRIP_8_LENGTH, 0, STRIP_9_LENGTH);
#endif
}


static void animate_led_internal_set_led_color(CRGB *buf, uint16_t led, uint8_t red, uint8_t green, uint8_t blue)
{
	buf[led].red = red;
	buf[led].green = green;
	buf[led].blue = blue;
}


static bool animate_led_check_interrupts(uint16_t *speed_delay, uint8_t *red, uint8_t *green, uint8_t *blue)
{
	bool return_val = false;
	if(animate_led_interrupt_flag_speed())
	{
		*speed_delay = animate_led_delay_in_animations();
	}
	else if(animate_led_interrupt_flag_color())
	{
		*red = color_led_cur_color_red_hex();
		*green = color_led_cur_color_green_hex();
		*blue = color_led_cur_color_blue_hex();
	}
	else if (animate_led_interrupt_flag_state())
	{
		return_val = true;
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


void animate_led_show_strip(void)
{
    FastLED.show();
}


led_state_e animate_led_state_randomize(led_state_e cur_state)
{
	led_state_e state = (led_state_e)(random(LED_STATE_FIRST, NUM_LED_STATES));
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
    led_state_e state = (led_state_e)(random(LED_STATE_FIRST, NUM_LED_STATES));
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
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};

	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
	{
		active_strip = animate_led_get_next_active_strip(strip_mask, pre_strip);
		pre_strip = active_strip;
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
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	animate_led_set_all_pixels(strip_mask, red, green, blue);
}


void animate_led_turn_all_pixels_off(void)
{
	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
}


void animate_led_spell_and_sparkle(const strip_mask_t spell_mask, const strip_mask_t sparkle_mask, color_hex_code_e color, bool fill, uint16_t speed_delay)
{
	//uint16_t strip_size = animate_led_get_max_strip_size(spell_mask | sparkle_mask);
	uint16_t strip_size = animate_led_get_max_strip_size(spell_mask); // this makes more sense... SRW
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	if (!fill) animate_led_set_all_pixels(sparkle_mask, 0, 0, 0);
	for (int i = 0; i < strip_size; i++)
	{
		/*
		if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        */
        animate_led_sparkle_random_color(sparkle_mask, fill, 0);
        animate_led_set_pixel(spell_mask, i, red, green, blue);
		animate_led_show_strip();
        delay(speed_delay);
	}	
}


void animate_led_spell_and_solid_color(const strip_mask_t spell_mask, const strip_mask_t solid_color_mask, color_hex_code_e color, uint16_t speed_delay)
{
	uint16_t strip_size = animate_led_get_max_strip_size(spell_mask); // this makes more sense... SRW
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	animate_led_solid_custom_color(solid_color_mask, color_led_get_random_color());
	for (int i = 0; i < strip_size; i++)
	{
		/*
		if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        */
        animate_led_set_pixel(spell_mask, i, red, green, blue);
		animate_led_show_strip();
        delay(speed_delay);
	}	
}


void animate_led_spell_word_multiple_colors(strip_mask_t strip_mask, uint32_t* color_array, uint16_t speed_delay)
{
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};

	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
	{
		active_strip = animate_led_get_next_active_strip(strip_mask, pre_strip);
		pre_strip = active_strip;
		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
		num_active_strips++;
		active_strip_array[iii] = active_strip;
	}
	for (int i = 0; i < strip_size; i++)
	{
		for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
			animate_led_set_pixel(active_strip_array[yyy], i, ((color_array[yyy] & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR, ((color_array[yyy] & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR, (color_array[yyy] & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR);
		}
		animate_led_show_strip();
        delay(speed_delay);
	}
}


void animate_led_only_spell_word(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay)
{
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	for (int i = 0; i < strip_size; i++)
	{
		/*
		if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        */
		animate_led_set_pixel(strip_mask, i, red, green, blue);
		animate_led_show_strip();
        delay(speed_delay);
	}
}


void animate_led_fade_in_fade_out_multiple_colors(strip_mask_t strip_mask, uint32_t* color_array)
{
	uint8_t red, green, blue; 
	uint16_t dummy_speed;
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
	{
		active_strip = animate_led_get_next_active_strip(strip_mask, pre_strip);
		pre_strip = active_strip;
		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
		num_active_strips++;
		active_strip_array[iii] = active_strip;
	}
    for (int i = 0; i < 256; i++)
    {
    	for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
			animate_led_set_all_pixels(active_strip_array[yyy], (((color_array[yyy] & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0), (((color_array[yyy] & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0), ((color_array[yyy] & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0));
		}
		if (animate_led_check_interrupts(&dummy_speed, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
    }
    for (int i = 255; i >= 0; i = i-2)
    {
    	for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
			animate_led_set_all_pixels(active_strip_array[yyy], (((color_array[yyy] & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0), (((color_array[yyy] & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0), ((color_array[yyy] & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0));
		}
		if (animate_led_check_interrupts(&dummy_speed, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
    }
}


void animate_led_fade_in_fade_out(strip_mask_t strip_mask, color_hex_code_e color)
{
	uint16_t dummy_speed;
    float r, g, b;
    uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    for (int i = 0; i < 256; i++)
    {
		if (animate_led_check_interrupts(&dummy_speed, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        r = (i / 256.0) * red;
        g = (i / 256.0) * green;
        b = (i / 256.0) * blue;
        animate_led_set_all_pixels(strip_mask, r, g, b);
    }
    for (int i = 255; i >= 0; i = i-2)
    {
		if (animate_led_check_interrupts(&dummy_speed, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        r = (i / 256.0) * red;
        g = (i / 256.0) * green;
        b = (i / 256.0) * blue;
        animate_led_set_all_pixels(strip_mask, r, g, b);
    }
}


void animate_led_strobe(strip_mask_t strip_mask, color_hex_code_e color, uint16_t animate_led_strobe_count, uint16_t flash_delay, uint16_t end_pause)
{
	uint8_t red, green, blue; 
	uint16_t dummy_speed;
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    for (int i = 0; i < animate_led_strobe_count; i++)
    {
		if (animate_led_check_interrupts(&dummy_speed, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        animate_led_set_all_pixels(strip_mask, red, green, blue);
        animate_led_show_strip();
        delay(flash_delay);
        animate_led_set_all_pixels(strip_mask, 0, 0, 0);
        animate_led_show_strip();
        delay(flash_delay);
    }
    delay(end_pause);
}


void animate_led_cyclone_bounce(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint8_t red, green, blue; 
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint16_t dummy_speed;
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    for (int i = 0; i < strip_size - eye_size - 2; i++) // "-2" is CYA
    {
		if (animate_led_check_interrupts(&dummy_speed, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        animate_led_set_all_pixels(strip_mask, 0, 0, 0);
        animate_led_set_pixel(strip_mask, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip_mask,(i + j), red, green, blue);
        }
        animate_led_set_pixel(strip_mask, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
    for (int i = strip_size - eye_size - 2; i > 0; i--)
    {
		if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        animate_led_set_all_pixels(strip_mask, 0, 0, 0); 
        animate_led_set_pixel(strip_mask, i , red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip_mask, i + j, red, green, blue);
        }
        animate_led_set_pixel(strip_mask, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
	animate_led_set_all_pixels(strip_mask, 0, 0, 0);
}


void animate_led_center_to_outside(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
    uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
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
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_outside_to_center(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
    uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
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
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_left_to_right(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
    uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    for (int i = 0; i < strip_size - eye_size - 2; i++)
    {
        animate_led_set_all_pixels(strip_mask, 0, 0, 0);
        animate_led_set_pixel(strip_mask, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++) animate_led_set_pixel(strip_mask, i + j, red, green, blue);
        animate_led_set_pixel(strip_mask, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_right_to_left(strip_mask_t strip_mask, color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
    uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    for (int i = strip_size - eye_size - 2; i > 0; i--)
    {
        animate_led_set_all_pixels(strip_mask, 0, 0, 0);
        animate_led_set_pixel(strip_mask, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++) animate_led_set_pixel(strip_mask, i + j, red, green, blue);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_new_kitt(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
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
	uint16_t dummy_speed;
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
	{
		active_strip = animate_led_get_next_active_strip(strip_mask, pre_strip);
		pre_strip = active_strip;
		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
		num_active_strips++;
		active_strip_array[iii] = active_strip;
	}
	for (int i = 0; i < count; i++)
    {
		if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        for (int yyy = 0; yyy < num_active_strips; yyy++)
		{
			animate_led_set_pixel(active_strip_array[yyy], random(animate_led_get_strip_size(active_strip_array[yyy])), (((color_array[yyy] & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0), (((color_array[yyy] & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0), ((color_array[yyy] & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0));
			animate_led_show_strip();
		}
        if (only_one) animate_led_set_all_pixels(strip_mask, 0, 0, 0);
    }
	delay(speed_delay);
}


void animate_led_twinkle(strip_mask_t strip_mask, color_hex_code_e color, uint16_t count, uint16_t speed_delay, bool only_one)
{
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    //animate_led_set_all_pixels(ALL_STRIPS, 0, 0, 0);
    for (int i = 0; i < count; i++)
    {
		if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        animate_led_set_pixel(strip_mask, random(strip_size), red, green, blue);
        animate_led_show_strip();
        delay(speed_delay);
        if (only_one) animate_led_set_all_pixels(strip_mask, 0, 0, 0);
    }
    delay(speed_delay);
}


void animate_led_twinkle_random(strip_mask_t strip_mask, uint16_t count, uint16_t speed_delay, bool only_one)
{
    animate_led_set_all_pixels(strip_mask, 0, 0, 0);
    uint8_t dummy_red, dummy_green, dummy_blue;
    for (int i = 0; i < count; i++)
    {
		if (animate_led_check_interrupts(&speed_delay, &dummy_red, &dummy_green, &dummy_blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        animate_led_set_pixel(strip_mask, random(g_max_strip_length), random(0, 255), random(0, 255), random(0, 255));
        animate_led_show_strip();
        delay(speed_delay);
        if (only_one) animate_led_set_all_pixels(strip_mask, 0, 0, 0);
    }
    delay(speed_delay);
}


void animate_led_sparkle_only_random_color(strip_mask_t strip_mask, bool fill, uint16_t speed_delay)
{
	float percent_to_fill = 0.7;
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	for (uint16_t iii = 0; iii < (percent_to_fill * (float)animate_led_get_num_active_animation_leds(strip_mask)); iii++)
	{
		int pix = random(strip_size);
		animate_led_set_pixel(strip_mask, pix, random(0, 255), random(0, 255), random(0, 255));
		animate_led_show_strip();
		delay(speed_delay);
		if (!fill) animate_led_set_pixel(strip_mask, pix, 0, 0, 0);
	}
}


void animate_led_sparkle_random_color(strip_mask_t strip_mask, bool fill, uint16_t speed_delay)
{
	float percent_to_fill = 0.7;
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	//for (uint16_t iii = 0; iii < (percent_to_fill * (float)animate_led_get_num_active_animation_leds(strip_mask)); iii++)
	///{
		int pix = random(strip_size);
		animate_led_set_pixel(strip_mask, pix, random(0, 255), random(0, 255), random(0, 255));
		animate_led_show_strip();
		delay(speed_delay);
		if (!fill) animate_led_set_pixel(strip_mask, pix, 0, 0, 0);
	//}
}


void animate_led_sparkle(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay)
{
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    int pix = random(strip_size);
    animate_led_set_pixel(strip_mask, pix, red, green, blue);
    animate_led_show_strip();
    delay(speed_delay);
    animate_led_set_pixel(strip_mask, pix, 0, 0, 0);
}


void animate_led_running_lights(strip_mask_t strip_mask, color_hex_code_e color)
{
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint16_t dummy_delay;
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    uint16_t pos = 0;
    for (int i = 0; i < strip_size * 2; i++)
    {
		if (animate_led_check_interrupts(&dummy_delay, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        pos++;
        for(int i = 0; i < strip_size; i++)
        {
            animate_led_set_pixel(strip_mask, i, ((sin(i + pos) * 127 + 128) / 255) * red, ((sin(i + pos) * 127 + 128) / 255) * green, ((sin(i + pos) * 127 + 128) / 255) * blue); 
        }
        animate_led_show_strip();
		delay(100 /animate_led_speed_factor());
    }
}


void animate_led_color_wipe(strip_mask_t strip_mask, color_hex_code_e color, uint16_t speed_delay)
{
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    for (uint16_t i = 0; i < strip_size; i++)
    {
        animate_led_set_pixel(strip_mask, i, red, green, blue);
        animate_led_show_strip();
        delay(speed_delay);
    }
    for (uint16_t i = 0; i < g_max_strip_length; i++)
    {
        animate_led_set_pixel(strip_mask, i, 0, 0, 0);
        animate_led_show_strip();
        delay(speed_delay);
    }
}


void animate_led_rainbow_cycle(strip_mask_t strip_mask, uint16_t speed_delay)
{
	uint8_t dummy_red, dummy_green, dummy_blue;
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
    byte *c;
    uint16_t i, j;
    //for (j = 0; j < 256 * 5; j++)
    for (j = 0; j < 256 * 5; j++)
    {
		if (animate_led_check_interrupts(&speed_delay, &dummy_red, &dummy_green, &dummy_blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        for (i = 0; i < strip_size; i++)
        {
            c = animate_led_wheel(((i * 256 / strip_size) + j) & 255);
            animate_led_set_pixel(strip_mask, i, *c, *(c + 1), *(c + 2));
        }
        animate_led_show_strip();
        delay(speed_delay);
    }
}


byte* animate_led_wheel(byte wheel_pos)
{
    static byte c[3];
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
	uint16_t dummy_speed;
	strip_bit_e active_strip = STRIP_BIT_1; 
	strip_bit_e pre_strip = STRIP_BIT_1;
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t num_active_strips = 0;
	strip_bit_e active_strip_array[NUM_STRIPS] = {STRIP_BIT_NONE_SET};
	for (uint8_t iii = 0; iii < NUM_STRIPS; iii++)
	{
		active_strip = animate_led_get_next_active_strip(strip_mask, pre_strip);
		pre_strip = active_strip;
		if (STRIP_BIT_NO_MORE_SET == active_strip) break;
		num_active_strips++;
		active_strip_array[iii] = active_strip;
	}
	
	for (int j = 0; j < 10; j++)
    {
        for (int q = 0; q < 3; q++)
        {
        	if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
        	{
        		animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
        		return;
        	}
            for (int i = 0; i < strip_size; i += 3) 
            {
            	for (int yyy = 0; yyy < num_active_strips; yyy++)
				{
					animate_led_set_pixel(active_strip_array[yyy], i + 	q, (((color_array[yyy] & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0), (((color_array[yyy] & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0), ((color_array[yyy] & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR) * (i / 256.0));
				}
            }
            animate_led_show_strip();
			if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
			{
        		animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
				return;
			}
            delay(speed_delay);
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
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    for (int j = 0; j < 10; j++)
    {
        for (int q = 0; q < 3; q++)
        {
        	if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
        	{
        		animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
        		return;
        	}
            for (int i = 0; i < strip_size; i += 3) animate_led_set_pixel(strip_mask, i + q, red, green, blue); // turn every third pixel on
            animate_led_show_strip();
			if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
			{
        		animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
				return;
			}
            delay(speed_delay);
            for (int i = 0; i < strip_size; i += 3) animate_led_set_pixel(strip_mask, i + q, 0, 0, 0); // turn everty third pixel off
        }
    }
}


void animate_led_theater_chase_rainbow(strip_mask_t strip_mask, uint16_t speed_delay)
{
	uint8_t dummy_red, dummy_green, dummy_blue;
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
    byte *c;
    for (int j = 0; j < 256; j++) // cycel all 256 colors in the animate_led_wheel
    {
        for (int q = 0; q < 3; q++)
        {
			if (animate_led_check_interrupts(&speed_delay, &dummy_red, &dummy_green, &dummy_blue))
			{
				animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
				return;
			}
            for (int i = 0; i < strip_size; i = i + 3)
            {
                c = animate_led_wheel((i + j) % 255);
                animate_led_set_pixel(strip_mask, i + q, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            animate_led_show_strip();
            delay(speed_delay);
            for (int i = 0; i < strip_size; i = i + 3) animate_led_set_pixel(strip_mask, i + q, 0, 0, 0); // turn every third pixel off
        }
    }
}


void animate_led_bouncing_balls(strip_mask_t strip_mask, color_hex_code_e color, int ball_count)
{
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
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
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    for (int i = 0; i < ball_count; i++)
    {
        clock_time_since_last_bounce[i] = millis();
        height[i] = start_height;
        pos[i] = 0;
        impact_velocity[i] = impact_velocity_start;
        time_since_last_bounce[i] = 0;
        dampening[i] = 0.90 - float(i) / pow(ball_count, 2);
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
	animate_led_show_strip();
	animate_led_set_all_pixels(strip_mask, 0, 0, 0);
}


void animate_led_meteor_rain(strip_mask_t strip_mask, color_hex_code_e color, byte meteor_size, byte meteor_trail_decay, bool meteor_random_decay, int speed_delay)
{
	uint16_t offset = 0;
	uint16_t strip_size = animate_led_get_max_strip_size(strip_mask);
	uint8_t red, green, blue; 
	red = ((color & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	green = ((color & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
	blue = (color & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR;
    animate_led_set_all_pixels(strip_mask, 0, 0, 0);
    for(int i = 0; i < strip_size + 50; i++) // 50 arbitrarily chosen SRW
    {
        for (int j = 0; j < strip_size; j++)
        {
            if ((!meteor_random_decay) || (random(10) > 5))
            {
            	if (strip_mask == g_all_strip_mask)
				{
					for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
					{
						offset = animate_led_get_strip_offset(strip_bit);
						if (animate_led_pixel_is_in_strip_range(strip_bit, j)) animate_led_fade_to_black(strip_mask, j, meteor_trail_decay);		
					}
				}
				else
				{
					for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; (strip_bit_e)(strip_bit + 1))
					{
						if (strip_mask & strip_bit)
						{
							offset = animate_led_get_strip_offset(strip_bit);
							if (animate_led_pixel_is_in_strip_range(strip_bit, j)) animate_led_fade_to_black(strip_mask, j, meteor_trail_decay);		
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
						offset = animate_led_get_strip_offset(strip_bit);
						if (animate_led_pixel_is_in_strip_range(strip_bit, i - j)) animate_led_set_pixel(strip_mask, i - j, red, green, blue);	
					}
				}
				else
				{
					for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; (strip_bit_e)(strip_bit + 1))
					{
						if (strip_mask & strip_bit)
						{
							offset = animate_led_get_strip_offset(strip_bit);
							if (animate_led_pixel_is_in_strip_range(strip_bit, i - j)) animate_led_set_pixel(strip_mask, i - j, red, green, blue);			
						}
					}
				}
            }
        }
        if (animate_led_check_interrupts(&speed_delay, &red, &green, &blue))
        {
        	animate_led_set_all_pixels((strip_mask_t)STRIP_BIT_ALL_SET, 0, 0, 0);
			return;
        }
        animate_led_show_strip();
        delay(speed_delay);
    }
}


void animate_led_fade_to_black(strip_mask_t strip_mask, uint16_t pixel, byte fade_value)
{
	uint16_t offset = 0;
	if (STRIP_BIT_ALL_SET == strip_mask)
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
		{
			offset = animate_led_get_strip_offset(strip_bit);
			if (animate_led_pixel_is_in_strip_range(strip_bit, pixel)) led_strip[pixel + offset].fadeToBlackBy(fade_value);
		}
	}	
	else
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit < STRIP_BIT_NUM_STRIPS; (strip_bit_e)(strip_bit + 1))
		{
			if (strip_mask & strip_bit)
			{
				offset = animate_led_get_strip_offset(strip_bit);
				if (animate_led_pixel_is_in_strip_range(strip_bit, pixel)) led_strip[pixel + offset].fadeToBlackBy(fade_value);
			}
		}		
	}
}


void animate_led_set_pixel(strip_mask_t strip_mask, uint16_t pixel, byte red, byte green, byte blue)
{
	uint16_t offset = 0;
	if (STRIP_BIT_ALL_SET == strip_mask)
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
		{
			offset = animate_led_get_strip_offset(strip_bit);
			if (animate_led_pixel_is_in_strip_range(strip_bit, pixel)) animate_led_internal_set_led_color(led_strip + offset, pixel, red, green, blue);		
		}
	}
	else
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
		{
			if (strip_mask & strip_bit)
			{
				offset = animate_led_get_strip_offset(strip_bit);
				if (animate_led_pixel_is_in_strip_range(strip_bit, pixel)) animate_led_internal_set_led_color(led_strip + offset, pixel, red, green, blue);
			}
		}
	}
	//animate_led_show_strip();
}


void animate_led_set_all_pixels(strip_mask_t strip_mask, byte red, byte green, byte blue) 
{		
	uint16_t offset = 0;
	uint16_t strip_size = 0;
	if (strip_mask == g_all_strip_mask)
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
		{
			offset = animate_led_get_strip_offset(strip_bit);
			strip_size = animate_led_get_strip_size(strip_bit);
			for (uint16_t iii = 0; iii < strip_size; iii++) animate_led_internal_set_led_color(led_strip + offset, iii, red, green, blue);
		}
	}
	else
	{
		for (strip_bit_e strip_bit = STRIP_BIT_1; strip_bit <= STRIP_BIT_NUM_STRIPS; strip_bit = (strip_bit_e)(strip_bit + 1))
		{
			if (strip_mask & strip_bit)
			{
				offset = animate_led_get_strip_offset(strip_bit);
				strip_size = animate_led_get_strip_size(strip_bit);
				for (uint16_t yyy = 0; yyy < strip_size; yyy++) animate_led_internal_set_led_color(led_strip + offset, yyy, red, green, blue);
			}
		}
	}
    animate_led_show_strip();
}


// kind of lame..  I don't plan on using
/*
void animate_led_fire(uint16_t cooling, uint16_t sparking, uint16_t speed_delay)
{
    static byte heat[NUM_LEDS];
    uint16_t cooldown;
    for (int i = 0; i < NUM_LEDS; i++)
    {
        cooldown = random(0, ((cooling * 10) / NUM_LEDS) + 2);
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
    if (random(255) < sparking)
    {
        uint16_t y = random(7);
        heat[y] = heat[y] + random(160, 255);
    }
    for (int j = 0; j < NUM_LEDS; j++)
    {
        animate_led_set_pixel_heat_color(j, heat[j]);
    }
    animate_led_show_strip();
    delay(speed_delay);
}


void animate_led_set_pixel_heat_color(int pix, byte temp)
{
    byte t192 = round((temp / 255.0) *191);
    byte heatramp = t192 & 0x3F;
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

