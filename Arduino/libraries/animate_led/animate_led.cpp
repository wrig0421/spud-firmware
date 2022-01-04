// SRW
#include <stdint.h>
#include <stdbool.h>
#include "FastLED.h"
#include "color_led.h"
//#include <FastLED>
#include "animate_led.h"

#define PIN_STRIP_1 12

#if defined(MULTIPLE_STRIPS)
#define PIN_STRIP_2 8 
//#define PIN_STRIP_3 
//#define PIN_STRIP_5 
//#define PIN_STRIP_6 
//#define PIN_STRIP_7 
//#define PIN_STRIP_8  
//#define PIN_STRIP_9 
#endif

bool g_interrupt_flag[NUM_ISR] = {false};
uint32_t g_max_strip_length = 0;

//CLEDController *controllers[2];
CLEDController *controller[2];
//CRGB led_strip[NUM_LEDS];

CRGB led_strip_1[STRIP_1_LENGTH];

#if defined(MULTIPLE_STRIPS)
CRGB led_strip_2[STRIP_2_LENGTH];
//CRGB led_strip_3[STRIP_3_LENGTH];
//CRGB led_strip_4[STRIP_4_LENGTH];
//CRGB led_strip_5[STRIP_5_LENGTH];
//CRGB led_strip_6[STRIP_6_LENGTH];
//CRGB led_strip_7[STRIP_7_LENGTH];
//CRGB led_strip_8[STRIP_8_LENGTH];
//CRGB led_strip_9[STRIP_9_LENGTH];
#endif

led_speed_e g_led_speed = LED_SPEED_5X;
//led_speed_e g_led_speed = LED_SPEED_1X;
//led_state_e g_led_state = LED_STATE_FIRST;
//led_state_e g_led_state = LED_STATE_TWO_TONE;
led_state_e g_led_state = LED_STATE_SPELL;

uint16_t g_delay_between_animations_ms = 1000;
uint16_t g_delay_in_animation_ms = 100; // where applicable of course
uint32_t g_iterations = 0; 


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
	g_max_strip_length = STRIP_1_LENGTH;
#if defined(MULTIPLE_STRIPS)
	if (STRIP_2_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_2_LENGTH;
#if defined(STRIP_3_LENGTH)
	if (STRIP_3_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	if (STRIP_4_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	if (STRIP_5_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	if (STRIP_6_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	if (STRIP_7_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	if (STRIP_8_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	if (STRIP_9_LENGTH > g_max_strip_length) g_max_strip_length = STRIP_9_LENGTH;
#endif
#endif
	// PIN2 is strip1
	// PIN1 is strip2
	controller[0] = &FastLED.addLeds<WS2812, PIN_STRIP_2, GRB>(led_strip_1, 0, STRIP_1_LENGTH);
	controller[1] = &FastLED.addLeds<WS2812, PIN_STRIP_1, GRB>(led_strip_2, 0, STRIP_2_LENGTH);
	//FastLED.addLeds<WS2812, PIN_STRIP_1, GRB>(led_strip, 0, STRIP_1_LENGTH).setCorrection( TypicalLEDStrip );
	//FastLED.addLeds<WS2812, PIN_STRIP_2, GRB>(led_strip, STRIP_1_LENGTH, STRIP_2_LENGTH).setCorrection( TypicalLEDStrip );

#if defined(MULTIPLE_STRIPS)
	//FastLED.addLeds<WS2812, PIN_STRIP_2, GRB>(led_strip_2, STRIP_2_LENGTH).setCorrection( TypicalLEDStrip );
	//FastLED.addLeds<WS2812, PIN_STRIP_3, GRB>(led_strip_3, STRIP_3_LENGTH).setCorrection( TypicalLEDStrip );
	//FastLED.addLeds<WS2812, PIN_STRIP_4, GRB>(led_strip_4, STRIP_4_LENGTH).setCorrection( TypicalLEDStrip );
	//FastLED.addLeds<WS2812, PIN_STRIP_5, GRB>(led_strip_5, STRIP_5_LENGTH).setCorrection( TypicalLEDStrip );
	//FastLED.addLeds<WS2812, PIN_STRIP_6, GRB>(led_strip_6, STRIP_6_LENGTH).setCorrection( TypicalLEDStrip );
	//FastLED.addLeds<WS2812, PIN_STRIP_7, GRB>(led_strip_7, STRIP_7_LENGTH).setCorrection( TypicalLEDStrip );
	//FastLED.addLeds<WS2812, PIN_STRIP_8, GRB>(led_strip_8, STRIP_8_LENGTH).setCorrection( TypicalLEDStrip );
	//FastLED.addLeds<WS2812, PIN_STRIP_9, GRB>(led_strip_9, STRIP_9_LENGTH).setCorrection( TypicalLEDStrip );
#endif

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


void animate_led_set_pixel(strip_num_e strip, int i, byte red, byte green, byte blue)
{
	if (ALL_STRIPS == strip)
	{
#if defined(MULTIPLE_STRIPS)
		if (i < STRIP_1_LENGTH)
		{
			led_strip_1[i].r = red;
			led_strip_1[i].g = green;
			led_strip_1[i].b = blue;
		}
		if (i  < STRIP_2_LENGTH)
		{
			led_strip_2[i].r = red;
			led_strip_2[i].g = green;
			led_strip_2[i].b = blue;
		}
#if defined(STRIP_3_LENGTH)
		if (i < STRIP_3_LENGTH)
		{
			led_strip_3[i].r = red;
			led_strip_3[i].g = green;
			led_strip_3[i].b = blue;
		}
#endif
#if defined(STRIP_4_LENGTH)
		if (i < STRIP_4_LENGTH)
		{
			led_strip_4[i].r = red;
			led_strip_4[i].g = green;
			led_strip_4[i].b = blue;
		}
#endif
#if defined(STRIP_5_LENGTH)
		if (i < STRIP_5_LENGTH)
		{
			led_strip_5[i].r = red;
			led_strip_5[i].g = green;
			led_strip_5[i].b = blue;
		}
#endif
#if defined(STRIP_6_LENGTH)
		if (i < STRIP_6_LENGTH)
		{
			led_strip_6[i].r = red;
			led_strip_6[i].g = green;
			led_strip_6[i].b = blue;
		}
#endif
#if defined(STRIP_7_LENGTH)
		if (i < STRIP_7_LENGTH)
		{
			led_strip_7[i].r = red;
			led_strip_7[i].g = green;
			led_strip_7[i].b = blue;
		}
#endif
#if defined(STRIP_8_LENGTH)
		if (i < STRIP_8_LENGTH)
		{
			led_strip_8[i].r = red;
			led_strip_8[i].g = green;
			led_strip_8[i].b = blue;
		}
#endif
#if defined(STRIP_9_LENGTH)
		if (i < STRIP_9_LENGTH)
		{
			led_strip_9[i].r = red;
			led_strip_9[i].g = green;
			led_strip_9[i].b = blue;
		}
#endif
#else
		led_strip_1[i].r = red;
		led_strip_1[i].g = green;
		led_strip_1[i].b = blue;
#endif
	}
	else
	{
		switch (strip)
		{
#if defined(STRIP_1_LENGTH)
			case STRIP_NUM_1:
				if (i < STRIP_1_LENGTH)
				{
					led_strip_1[i].r = red;
					led_strip_1[i].g = green;
					led_strip_1[i].b = blue;
				}
			break;
#endif
#if defined(STRIP_2_LENGTH)
			case STRIP_NUM_2:
				if (i < STRIP_2_LENGTH)
				{
					led_strip_2[i].r = red;
					led_strip_2[i].g = green;
					led_strip_2[i].b = blue;
				}
			break;
#endif
#if defined(STRIP_3_LENGTH)
			case STRIP_NUM_3:
				if (i < STRIP_3_LENGTH)
				{
					led_strip_3[i].r = red;
					led_strip_3[i].g = green;
					led_strip_3[i].b = blue;
				}
			break;
#endif
#if defined(STRIP_4_LENGTH)
			case STRIP_NUM_4:
				if (i < STRIP_4_LENGTH)
				{
					led_strip_4[i].r = red;
					led_strip_4[i].g = green;
					led_strip_4[i].b = blue;
				}
			break;
#endif
#if defined(STRIP_5_LENGTH)
			case STRIP_NUM_5:
				if (i < STRIP_5_LENGTH)
				{
					led_strip_5[i].r = red;
					led_strip_5[i].g = green;
					led_strip_5[i].b = blue;
				}
			break;
#endif
#if defined(STRIP_6_LENGTH)
			case STRIP_NUM_6:
				if (i < STRIP_6_LENGTH)
				{
					led_strip_6[i].r = red;
					led_strip_6[i].g = green;
					led_strip_6[i].b = blue;
				}
			break;
#endif
#if defined(STRIP_7_LENGTH)
			case STRIP_NUM_7:
				if (i < STRIP_7_LENGTH)
				{
					led_strip_7[i].r = red;
					led_strip_7[i].g = green;
					led_strip_7[i].b = blue;
				}
			break;
#endif
#if defined(STRIP_8_LENGTH)
			case STRIP_NUM_8:
				if (i < STRIP_8_LENGTH)
				{
					led_strip_8[i].r = red;
					led_strip_8[i].g = green;
					led_strip_8[i].b = blue;
				}
			break;
#endif
#if defined(STRIP_9_LENGTH)
			case STRIP_NUM_9:
				if (i < STRIP_9_LENGTH)
				{
					led_strip_9[i].r = red;
					led_strip_9[i].g = green;
					led_strip_9[i].b = blue;
				}
			break;
#endif
			default:
			break;
		}
		
	}
    //animate_led_show_strip();
}


void animate_led_set_all_pixels(strip_num_e strip, byte red, byte green, byte blue) 
{
	for (int i = 0; i < g_max_strip_length; i++)
    {
    	if (ALL_STRIPS == strip)
		{
    	//delay(1);
#if defined(MULTIPLE_STRIPS)
			if (i < STRIP_1_LENGTH)
			{
				// strip 1
				led_strip_1[i].r = red;
				led_strip_1[i].g = green;
				led_strip_1[i].b = blue;
			}
			if (i  < STRIP_2_LENGTH)
			{
				// strip 2
				led_strip_2[i].r = red;
				led_strip_2[i].g = green;
				led_strip_2[i].b = blue;
			}
#if defined(STRIP_3_LENGTH)
			if (i < STRIP_3_LENGTH)
			{
				led_strip_3[i].r = red;
				led_strip_3[i].g = green;
				led_strip_3[i].b = blue;
			}
#endif
#if defined(STRIP_4_LENGTH)
			if (i < STRIP_4_LENGTH)
			{
				led_strip_4[i].r = red;
				led_strip_4[i].g = green;
				led_strip_4[i].b = blue;
			}
#endif
#if defined(STRIP_5_LENGTH)
			if (i < STRIP_5_LENGTH)
			{
				led_strip_5[i].r = red;
				led_strip_5[i].g = green;
				led_strip_5[i].b = blue;
			}
#endif
#if defined(STRIP_6_LENGTH)
			if (i < STRIP_6_LENGTH)
			{
				led_strip_6[i].r = red;
				led_strip_6[i].g = green;
				led_strip_6[i].b = blue;
			}
#endif
#if defined(STRIP_7_LENGTH)
			if (i < STRIP_7_LENGTH)
			{
				led_strip_7[i].r = red;
				led_strip_7[i].g = green;
				led_strip_7[i].b = blue;
			}
#endif
#if defined(STRIP_8_LENGTH)
			if (i < STRIP_8_LENGTH)
			{
				led_strip_8[i].r = red;
				led_strip_8[i].g = green;
				led_strip_8[i].b = blue;
			}
#endif
#if defined(STRIP_9_LENGTH)
			if (i < STRIP_9_LENGTH)
			{
				led_strip_9[i].r = red;
				led_strip_9[i].g = green;
				led_strip_9[i].b = blue;
			}
#endif
#else
			led_strip_1[i].r = red;
			led_strip_1[i].g = green;
			led_strip_1[i].b = blue;
#endif
		}	
		else
		{
			switch (strip)
			{
#if defined(STRIP_1_LENGTH)
				case STRIP_NUM_1:
					if (i < STRIP_1_LENGTH)
					{
						led_strip_1[i].r = red;
						led_strip_1[i].g = green;
						led_strip_1[i].b = blue;
					}
				break;
#endif
#if defined(STRIP_2_LENGTH)
				case STRIP_NUM_2:
					if (i < STRIP_2_LENGTH)
					{
						led_strip_2[i].r = red;
						led_strip_2[i].g = green;
						led_strip_2[i].b = blue;
					}
				break;
#endif
#if defined(STRIP_3_LENGTH)
				case STRIP_NUM_3:
					if (i < STRIP_3_LENGTH)
					{
						led_strip_3[i].r = red;
						led_strip_3[i].g = green;
						led_strip_3[i].b = blue;
					}
				break;
#endif
#if defined(STRIP_4_LENGTH)
				case STRIP_NUM_4:
					if (i < STRIP_4_LENGTH)
					{
						led_strip_4[i].r = red;
						led_strip_4[i].g = green;
						led_strip_4[i].b = blue;
					}
				break;
#endif
#if defined(STRIP_5_LENGTH)
				case STRIP_NUM_5:
					if (i < STRIP_5_LENGTH)
					{
						led_strip_5[i].r = red;
						led_strip_5[i].g = green;
						led_strip_5[i].b = blue;
					}
				break;
#endif
#if defined(STRIP_6_LENGTH)
				case STRIP_NUM_6:
					if (i < STRIP_6_LENGTH)
					{
						led_strip_6[i].r = red;
						led_strip_6[i].g = green;
						led_strip_6[i].b = blue;
					}
				break;
#endif
#if defined(STRIP_7_LENGTH)
				case STRIP_NUM_7:
					if (i < STRIP_7_LENGTH)
					{
						led_strip_7[i].r = red;
						led_strip_7[i].g = green;
						led_strip_7[i].b = blue;
					}
				break;
#endif
#if defined(STRIP_8_LENGTH)
				case STRIP_NUM_8:
					if (i < STRIP_8_LENGTH)
					{
						led_strip_8[i].r = red;
						led_strip_8[i].g = green;
						led_strip_8[i].b = blue;
					}
				break;
#endif
#if defined(STRIP_9_LENGTH)
				case STRIP_NUM_9:
					if (i < STRIP_9_LENGTH)
					{
						led_strip_9[i].r = red;
						led_strip_9[i].g = green;
						led_strip_9[i].b = blue;
					}
				break;
#endif
				default:
				break;
			}
		
		}
    }
    animate_led_show_strip();
}


void animate_led_state_randomize(void)
{
    led_state_e state = (led_state_e)(random());
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


void animate_led_solid_custom_color(strip_num_e strip, byte red, byte green, byte blue)
{
	animate_led_set_all_pixels(strip, red, green, blue);
}


void animate_led_solid_color(strip_num_e strip)
{
	animate_led_set_all_pixels(strip, color_led_cur_color_red_hex(), color_led_cur_color_green_hex(), color_led_cur_color_blue_hex());
}


void animate_led_spell_word(strip_num_e strip, uint16_t speed_delay)
{
	uint16_t strip_size = 0;
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;

	for (int i = 0; i < strip_size; i++)
	{
		//xanimate_led_sparkle_random_color(STRIP_NUM_1, 0);
		if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(ALL_STRIPS, 0, 0, 0);
			return;
		}
		else if(animate_led_interrupt_flag_speed())
		{
			speed_delay = animate_led_delay_in_animations();
		}
		else if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		animate_led_set_pixel(strip, i, red, green, blue);
		animate_led_show_strip();
        delay(speed_delay);
	}
}


void animate_led_fade_in_fade_out(strip_num_e strip)
{
    float r, g, b;
    uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = 0; i < 256; i++)
    {
		if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(ALL_STRIPS, 0, 0, 0);
			return;
		}
		/*
		else if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		*/
        r = (i / 256.0) * red;
        g = (i / 256.0) * green;
        b = (i / 256.0) * blue;
        animate_led_set_all_pixels(strip, r, g, b);
        //delay(10 / animate_led_speed_factor());
    }
    //for (int i = 255; i >= 0; i = i - 2)
    for (int i = 255; i >= 0; i = i-2)
    {
		if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(strip, 0, 0, 0);
			return;
		}
		/*
		else if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		*/
        r = (i / 256.0) * red;
        g = (i / 256.0) * green;
        b = (i / 256.0) * blue;
        animate_led_set_all_pixels(ALL_STRIPS, r, g, b);
    }
}


void animate_led_strobe(strip_num_e strip, uint16_t animate_led_strobe_count, uint16_t flash_delay, uint16_t end_pause)
{
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = 0; i < animate_led_strobe_count; i++)
    {
		if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		else if(animate_led_interrupt_flag_speed())
		{
			flash_delay = animate_led_delay_in_animations();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(strip, 0, 0, 0);
			return;
		}
        animate_led_set_all_pixels(strip, red, green, blue);
        animate_led_show_strip();
        delay(flash_delay);
        animate_led_set_all_pixels(strip, 0, 0, 0);
        animate_led_show_strip();
        delay(flash_delay);
    }
    delay(end_pause);
}


void animate_led_cyclone_bounce(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint8_t red, green, blue; 
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = 0; i < strip_size - eye_size - 2; i++) // I think the -2 is CYA if someone says eye_size is 0
    {
		if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(strip, 0, 0, 0);
			return;
		}
        animate_led_set_all_pixels(strip, 0, 0, 0);
        animate_led_set_pixel(strip, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip,(i + j), red, green, blue);
        }
        animate_led_set_pixel(strip, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
    for (int i = g_max_strip_length - eye_size - 2; i > 0; i--)
    {
		if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(strip, 0, 0, 0);
			return;
		}
        animate_led_set_all_pixels(strip, 0, 0, 0); 
        animate_led_set_pixel(strip, i , red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip, i + j, red, green, blue);
        }
        animate_led_set_pixel(strip, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
	animate_led_set_all_pixels(strip, 0, 0, 0);
}


void animate_led_center_to_outside(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
    uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = ((strip_size - eye_size) / 2); i >= 0; i--)
    {
        animate_led_set_all_pixels(strip, 0,0,0);
        animate_led_set_pixel(strip, i, red/10, green/10, blue/10);
        for (int j = 1; j<= eye_size; j++)
        {
            animate_led_set_pixel(strip, i + j, red, green, blue);
        }
        animate_led_set_pixel(strip, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_set_pixel(strip, strip_size - i, red/10, green/10, blue/10);
        for (int j = 1; j<= eye_size; j++)
        {
            animate_led_set_pixel(strip, strip_size - i - j, red, green, blue);
        }
        animate_led_set_pixel(strip, strip_size - i - eye_size - 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_outside_to_center(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
    uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = 0; i <= ((strip_size - eye_size) / 2 ); i++)
    {
        animate_led_set_all_pixels(strip, 0, 0, 0);
        animate_led_set_pixel(strip, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip, i+j, red, green, blue);
        }
        animate_led_set_pixel(strip, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_set_pixel(strip, strip_size - i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip, strip_size - i - j, red, green, blue);
        }
        animate_led_set_pixel(strip, strip_size - i - eye_size - 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_left_to_right(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
    uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = 0; i < strip_size - eye_size - 2; i++)
    {
        animate_led_set_all_pixels(strip, 0, 0, 0);
        animate_led_set_pixel(strip, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip, i + j, red, green, blue);
        }
        animate_led_set_pixel(strip, i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_right_to_left(strip_num_e strip, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
    uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = strip_size - eye_size - 2; i > 0; i--)
    {
        animate_led_set_all_pixels(strip, 0, 0, 0);
        animate_led_set_pixel(strip, i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(strip, i + j, red, green, blue);
        }
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_new_kitt(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    animate_led_right_to_left(ALL_STRIPS, eye_size, speed_delay, return_delay);
    animate_led_left_to_right(ALL_STRIPS, eye_size, speed_delay, return_delay);
    animate_led_outside_to_center(ALL_STRIPS, eye_size, speed_delay, return_delay);
    animate_led_center_to_outside(ALL_STRIPS, eye_size, speed_delay, return_delay);
    animate_led_left_to_right(ALL_STRIPS, eye_size, speed_delay, return_delay);
    animate_led_right_to_left(ALL_STRIPS, eye_size, speed_delay, return_delay);
    animate_led_outside_to_center(ALL_STRIPS, eye_size, speed_delay, return_delay);
    animate_led_center_to_outside(ALL_STRIPS, eye_size, speed_delay, return_delay);
}


void animate_led_twinkle(strip_num_e strip, uint16_t count, uint16_t speed_delay, bool only_one)
{
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    //animate_led_set_all_pixels(ALL_STRIPS, 0, 0, 0);
    for (int i = 0; i < count; i++)
    {
		if(animate_led_interrupt_flag_speed())
		{
			speed_delay = animate_led_delay_in_animations();
		}
		else if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(strip, 0, 0, 0);
			return;
		}
        animate_led_set_pixel(strip, random(g_max_strip_length), red, green, blue);
        animate_led_show_strip();
        delay(speed_delay);
        if (only_one)
        {
            animate_led_set_all_pixels(strip, 0, 0, 0);
        }
    }
    delay(speed_delay);
}


void animate_led_twinkle_random(strip_num_e strip, uint16_t count, uint16_t speed_delay, bool only_one)
{
    animate_led_set_all_pixels(ALL_STRIPS, 0, 0, 0);
    for (int i = 0; i < count; i++)
    {
		if(animate_led_interrupt_flag_speed())
		{
			speed_delay = animate_led_delay_in_animations();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(strip, 0, 0, 0);
			return;
		}
        animate_led_set_pixel(strip, random(g_max_strip_length), random(0, 255), random(0, 255), random(0, 255));
        animate_led_show_strip();
        delay(speed_delay);
        if (only_one)
        {
            animate_led_set_all_pixels(strip, 0, 0, 0);
        }
    }
    delay(speed_delay);
}


void animate_led_sparkle_random_color(strip_num_e strip, uint16_t speed_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
	uint8_t red, green, blue; 
    int pix = random(strip_size);
	// should this be wrapped in for loop for NUM_LEDS
    animate_led_set_pixel(strip, pix, random(0, 255), random(0, 255), random(0, 255));
    animate_led_show_strip();
    delay(speed_delay);
    animate_led_set_pixel(strip, pix, 0, 0, 0);
}


void animate_led_sparkle(strip_num_e strip, uint16_t speed_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    int pix = random(strip_size);
	// should this be wrapped in for loop for NUM_LEDS
    animate_led_set_pixel(strip, pix, red, green, blue);
    animate_led_show_strip();
    delay(speed_delay);
    animate_led_set_pixel(strip, pix, 0, 0, 0);
}


void animate_led_running_lights(strip_num_e strip)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    uint16_t pos = 0;
    for (int i = 0; i < strip_size * 2; i++)
    {
		if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(strip, 0, 0, 0);
			return;
		}
        pos++;
        for(int i = 0; i < g_max_strip_length; i++)
        {
            animate_led_set_pixel(strip, i, ((sin(i + pos) * 127 + 128) / 255) * red, ((sin(i + pos) * 127 + 128) / 255) * green, ((sin(i + pos) * 127 + 128) / 255) * blue); 
        }
        animate_led_show_strip();
		delay(100 /animate_led_speed_factor());
    }
}


void animate_led_color_wipe(strip_num_e strip, uint16_t speed_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (uint16_t i = 0; i < strip_size; i++)
    {
        animate_led_set_pixel(strip, i, red, green, blue);
        animate_led_show_strip();
        delay(speed_delay);
    }
    for (uint16_t i = 0; i < g_max_strip_length; i++)
    {
        animate_led_set_pixel(strip, i, 0, 0, 0);
        animate_led_show_strip();
        delay(speed_delay);
    }
}


void animate_led_rainbow_cycle(strip_num_e strip, uint16_t speed_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
    byte *c;
    uint16_t i, j;
    for (j = 0; j < 256 * 5; j++)
    {
		if(animate_led_interrupt_flag_speed())
		{
			speed_delay = animate_led_delay_in_animations();
		}
		else if (animate_led_interrupt_flag_state())
		{
			//animate_led_set_all_pixels(strip, 0, 0, 0);
			return;
		}
        for (i = 0; i < strip_size; i++)
        {
            c = animate_led_wheel(((i * 256 / strip_size) + j) & 255);
            animate_led_set_pixel(strip, i, *c, *(c + 1), *(c + 2));
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


void animate_led_theater_chase(strip_num_e strip, uint16_t speed_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int j = 0; j < 10; j++)
    {
        for (int q = 0; q < 3; q++)
        {
			if(animate_led_interrupt_flag_speed())
			{
				speed_delay = animate_led_delay_in_animations();
			}
			else if(animate_led_interrupt_flag_color())
			{
				red = color_led_cur_color_red_hex();
				green = color_led_cur_color_green_hex();
				blue = color_led_cur_color_blue_hex();
			}
			else if (animate_led_interrupt_flag_state())
			{
				animate_led_set_all_pixels(strip, 0, 0, 0);
				return;
			}
            for (int i = 0; i < strip_size; i += 3)
            {
                animate_led_set_pixel(strip, i + q, red, green, blue); // turn every third pixel on
            }
            animate_led_show_strip();
			if(animate_led_interrupt_flag_speed())
			{
				speed_delay = animate_led_delay_in_animations();
			}
			if(animate_led_interrupt_flag_color())
			{
				red = color_led_cur_color_red_hex();
				green = color_led_cur_color_green_hex();
				blue = color_led_cur_color_blue_hex();
			}
            delay(speed_delay);
            for (int i = 0; i < strip_size; i += 3)
            {
                animate_led_set_pixel(strip, i + q, 0, 0, 0); // turn everty third pixel off
            }
        }
    }
}


void animate_led_theater_chase_rainbow(strip_num_e strip, uint16_t speed_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
    byte *c;
    for (int j = 0; j < 256; j++) // cycel all 256 colors in the animate_led_wheel
    {
        for (int q = 0; q < 3; q++)
        {
			if(animate_led_interrupt_flag_speed())
			{
				speed_delay = animate_led_delay_in_animations();
			}
			else if (animate_led_interrupt_flag_state())
			{
				animate_led_set_all_pixels(strip, 0, 0, 0);
				return;
			}
            for (int i = 0; i < strip_size; i = i + 3)
            {
                c = animate_led_wheel((i + j) % 255);
                animate_led_set_pixel(strip, i + q, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            animate_led_show_strip();
			
            delay(speed_delay);
            for (int i = 0; i < strip_size; i = i + 3)
            {
                animate_led_set_pixel(strip, i + q, 0, 0, 0); // turn every third pixel off
            }
        }
    }
}


void animate_led_bouncing_balls(strip_num_e strip, int ball_count)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
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
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = 0; i < ball_count; i++)
    {
        clock_time_since_last_bounce[i] = millis();
        height[i] = start_height;
        pos[i] = 0;
        impact_velocity[i] = impact_velocity_start;
        time_since_last_bounce[i] = 0;
        dampening[i] = 0.90 - float(i) / pow(ball_count, 2);
    }

    //while (1)
    //{
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
            animate_led_set_pixel(strip, pos[i], red, green, blue);
        }
        animate_led_show_strip();
        animate_led_set_all_pixels(strip, 0, 0, 0);
    //}
}


void animate_led_meteor_rain(strip_num_e strip, byte meteor_size, byte meteor_trail_decay, bool meteor_random_decay, int speed_delay)
{
	uint16_t strip_size = 0;
	if (STRIP_NUM_1 == strip) strip_size = STRIP_1_LENGTH;
#if defined(STRIP_2_LENGTH)
	else if (STRIP_NUM_2 == strip) strip_size = STRIP_2_LENGTH;
#endif
#if defined(STRIP_3_LENGTH)
	else if (STRIP_NUM_3 == strip) strip_size = STRIP_3_LENGTH;
#endif
#if defined(STRIP_4_LENGTH)
	else if (STRIP_NUM_4 == strip) strip_size = STRIP_4_LENGTH;
#endif
#if defined(STRIP_5_LENGTH)
	else if (STRIP_NUM_5 == strip) strip_size = STRIP_5_LENGTH;
#endif
#if defined(STRIP_6_LENGTH)
	else if (STRIP_NUM_6 == strip) strip_size = STRIP_6_LENGTH;
#endif
#if defined(STRIP_7_LENGTH)
	else if (STRIP_NUM_7 == strip) strip_size = STRIP_7_LENGTH;
#endif
#if defined(STRIP_8_LENGTH)
	else if (STRIP_NUM_8 == strip) strip_size = STRIP_8_LENGTH;
#endif
#if defined(STRIP_9_LENGTH)
	else if (STRIP_NUM_9 == strip) strip_size = STRIP_9_LENGTH;
#endif
	else if (ALL_STRIPS == strip) strip_size = g_max_strip_length;
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    animate_led_set_all_pixels(strip, 0, 0, 0);
    for(int i = 0; i < strip_size + 50; i++) // 50 arbitrarily chosen SRW
    {
        for (int j = 0; j < strip_size; j++)
        {
            if ((!meteor_random_decay) || (random(10) > 5))
            {
                animate_led_fade_to_black(strip, j, meteor_trail_decay);
            }
        }
        for (int j = 0; j < meteor_size; j++)
        {
            if ((i - j < strip_size) && (i - j >= 0))
            {
                animate_led_set_pixel(strip, i - j, red, green, blue);
            }
        }
		if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(ALL_STRIPS, 0, 0, 0);
			return;
		}
		// don't allow speed change!
        animate_led_show_strip();
        delay(speed_delay);
    }
}


void animate_led_fade_to_black(strip_num_e strip, int i, byte fade_value)
{
	if (ALL_STRIPS == strip)
	{
    	//delay(1);
#if defined(MULTIPLE_STRIPS)
		if (i < STRIP_1_LENGTH)
		{
			led_strip_1[i].fadeToBlackBy(fade_value);
    		led_strip_1[i].fadeToBlackBy(fade_value);
    		led_strip_1[i].fadeToBlackBy(fade_value);
		}
		if (i  < STRIP_2_LENGTH)
		{
			led_strip_2[i].fadeToBlackBy(fade_value);
    		led_strip_2[i].fadeToBlackBy(fade_value);
    		led_strip_2[i].fadeToBlackBy(fade_value);
		}
#if defined(STRIP_3_LENGTH)
		if (i < STRIP_3_LENGTH)
		{
			led_strip_3[i].fadeToBlackBy(fade_value);
    		led_strip_3[i].fadeToBlackBy(fade_value);
    		led_strip_3[i].fadeToBlackBy(fade_value);
		}
#endif
#if defined(STRIP_4_LENGTH)
		if (i < STRIP_4_LENGTH)
		{
			led_strip_4[i].fadeToBlackBy(fade_value);
    		led_strip_4[i].fadeToBlackBy(fade_value);
    		led_strip_4[i].fadeToBlackBy(fade_value);
		}
#endif
#if defined(STRIP_5_LENGTH)
		if (i < STRIP_5_LENGTH)
		{
			led_strip_5[i].fadeToBlackBy(fade_value);
    		led_strip_5[i].fadeToBlackBy(fade_value);
    		led_strip_5[i].fadeToBlackBy(fade_value);
		}
#endif
#if defined(STRIP_6_LENGTH)
		if (i < STRIP_6_LENGTH)
		{
			led_strip_6[i].fadeToBlackBy(fade_value);
    		led_strip_6[i].fadeToBlackBy(fade_value);
    		led_strip_6[i].fadeToBlackBy(fade_value);
		}
#endif
#if defined(STRIP_7_LENGTH)
		if (i < STRIP_7_LENGTH)
		{
			led_strip_7[i].fadeToBlackBy(fade_value);
    		led_strip_7[i].fadeToBlackBy(fade_value);
    		led_strip_7[i].fadeToBlackBy(fade_value);
		}
#endif
#if defined(STRIP_8_LENGTH)
		if (i < STRIP_8_LENGTH)
		{
			led_strip_8[i].fadeToBlackBy(fade_value);
    		led_strip_8[i].fadeToBlackBy(fade_value);
    		led_strip_8[i].fadeToBlackBy(fade_value);
		}
#endif
#if defined(STRIP_9_LENGTH)
		if (i < STRIP_9_LENGTH)
		{
			led_strip_9[i].fadeToBlackBy(fade_value);
    		led_strip_9[i].fadeToBlackBy(fade_value);
    		led_strip_9[i].fadeToBlackBy(fade_value);
		}
#endif
#else
		led_strip_1[i].fadeToBlackBy(fade_value);
		led_strip_1[i].fadeToBlackBy(fade_value);
		led_strip_1[i].fadeToBlackBy(fade_value);
#endif
	}	
	else
	{
		switch (strip)
		{
#if defined(STRIP_1_LENGTH)
			case STRIP_NUM_1:
				if (i < STRIP_1_LENGTH)
				{
					led_strip_1[i].fadeToBlackBy(fade_value);
    				led_strip_1[i].fadeToBlackBy(fade_value);
    				led_strip_1[i].fadeToBlackBy(fade_value);
				}
			break;
#endif
#if defined(STRIP_2_LENGTH)
			case STRIP_NUM_2:
				if (i < STRIP_2_LENGTH)
				{
					led_strip_2[i].fadeToBlackBy(fade_value);
    				led_strip_2[i].fadeToBlackBy(fade_value);
    				led_strip_2[i].fadeToBlackBy(fade_value);
				}
			break;
#endif
#if defined(STRIP_3_LENGTH)
			case STRIP_NUM_3:
				if (i < STRIP_3_LENGTH)
				{
					led_strip_3[i].fadeToBlackBy(fade_value);
    				led_strip_3[i].fadeToBlackBy(fade_value);
    				led_strip_3[i].fadeToBlackBy(fade_value);
				}
			break;
#endif
#if defined(STRIP_4_LENGTH)
			case STRIP_NUM_4:
				if (i < STRIP_4_LENGTH)
				{
					led_strip_4[i].fadeToBlackBy(fade_value);
    				led_strip_4[i].fadeToBlackBy(fade_value);
    				led_strip_4[i].fadeToBlackBy(fade_value);
				}
			break;
#endif
#if defined(STRIP_5_LENGTH)
			case STRIP_NUM_5:
				if (i < STRIP_5_LENGTH)
				{
					led_strip_5[i].fadeToBlackBy(fade_value);
    				led_strip_5[i].fadeToBlackBy(fade_value);
    				led_strip_5[i].fadeToBlackBy(fade_value);
				}
			break;
#endif
#if defined(STRIP_6_LENGTH)
			case STRIP_NUM_6:
				if (i < STRIP_6_LENGTH)
				{
					led_strip_6[i].fadeToBlackBy(fade_value);
    				led_strip_6[i].fadeToBlackBy(fade_value);
    				led_strip_6[i].fadeToBlackBy(fade_value);
				}
			break;
#endif
#if defined(STRIP_7_LENGTH)
			case STRIP_NUM_7:
				if (i < STRIP_7_LENGTH)
				{
					led_strip_7[i].fadeToBlackBy(fade_value);
    				led_strip_7[i].fadeToBlackBy(fade_value);
    				led_strip_7[i].fadeToBlackBy(fade_value);
				}
			break;
#endif
#if defined(STRIP_8_LENGTH)
			case STRIP_NUM_8:
				if (i < STRIP_8_LENGTH)
				{
					led_strip_8[i].fadeToBlackBy(fade_value);
    				led_strip_8[i].fadeToBlackBy(fade_value);
    				led_strip_8[i].fadeToBlackBy(fade_value);
				}
			break;
#endif
#if defined(STRIP_9_LENGTH)
			case STRIP_NUM_9:
				if (i < STRIP_9_LENGTH)
				{
					led_strip_9[i].fadeToBlackBy(fade_value);
    				led_strip_9[i].fadeToBlackBy(fade_value);
    				led_strip_9[i].fadeToBlackBy(fade_value);
				}
			break;
#endif
			default:
			break;
		}
	}
}

void animate_led_two_tone(uint32_t color_strip_1, uint32_t color_strip_2)
{
	uint8_t red_1, green_1, blue_1; 
	uint8_t red_2, green_2, blue_2;
	red_1 = (color_strip_1 & 0xFF0000) >> 16;
	green_1 = (color_strip_1 & 0x00FF00) >> 8;
	blue_1 = (color_strip_1 & 0x0000FF);
	red_2 = (color_strip_2 & 0xFF0000) >> 16;
	green_2 = (color_strip_2 & 0x00FF00) >> 8;
	blue_2 = (color_strip_2 & 0x0000FF);
    //animate_led_set_all_pixels(ALL_STRIPS, 0, 0, 0);
#if defined(MULTIPLE_STRIPS)
	for (int i = 0; i < g_max_strip_length; i++)
    {
    	//delay(1);
		if (i < STRIP_1_LENGTH)
		{
			// strip 1
    		led_strip_1[i].r = red_1;
    		led_strip_1[i].g = green_1;
    		led_strip_1[i].b = blue_1;
    	}
    	if (i  < STRIP_2_LENGTH)
    	{
    		// strip 2
    		led_strip_2[i].r = red_2;
    		led_strip_2[i].g = green_2;
    		led_strip_2[i].b = blue_2;
		}
	}
#endif
	animate_led_show_strip();
	// no support for single strip case
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

