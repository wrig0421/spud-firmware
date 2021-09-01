#include <stdint.h>
#include <stdbool.h>
#include "FastLED.h"
#include "color_led.h"
//#include <FastLED>
#include "animate_led.h"

#define PIN 12

bool g_interrupt_flag[NUM_ISR] = {false};
CRGB leds[NUM_LEDS];
led_speed_e g_led_speed = LED_SPEED_1X;
//led_state_e g_led_state = LED_STATE_FIRST;
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
	//return g_delay_between_animations_ms;
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
	FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
	/*
	g_led_speeds[LED_SPEED_10X] = g_led_delay_ms / 10;
	g_led_speeds[LED_SPEED_5X] = g_led_delay_ms / 5;
	g_led_speeds[LED_SPEED_2X] = g_led_delay_ms / 2;
	g_led_speeds[LED_SPEED_1X] = g_led_delay_ms / 1;
	g_led_speeds[LED_SPEED_0P5X] = g_led_delay_ms / 0.5f;
	g_led_speeds[LED_SPEED_0P25X] = g_led_delay_ms / 0.25f;
	g_led_speeds[LED_SPEED_0P1X] = g_led_delay_ms / 0.1f;
	*/
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


void animate_led_set_pixel(int Pixel, byte red, byte green, byte blue)
{
    leds[Pixel].r = red;
    leds[Pixel].g = green;
    leds[Pixel].b = blue;
}


void animate_led_set_all_pixels(byte red, byte green, byte blue) 
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        animate_led_set_pixel(i, red, green, blue);
    }
    animate_led_show_strip();
}


void animate_led_state_randomize(void)
{
    led_state_e state = (led_state_e)(random(NUM_LED_STATES));
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


void animate_led_solid_color(void)
{
	animate_led_set_all_pixels(color_led_cur_color_red_hex(), color_led_cur_color_green_hex(), color_led_cur_color_blue_hex());
}


void animate_led_spell_word(uint16_t speed_delay)
{
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
	for (int i = 0; i < NUM_LEDS; i++)
	{
		if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(0, 0, 0);
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
		animate_led_set_pixel(i, red, green, blue);
		animate_led_show_strip();
        delay(speed_delay);
	}
}


void animate_led_fade_in_fade_out(void)
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
			animate_led_set_all_pixels(0, 0, 0);
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
        animate_led_set_all_pixels(r, g, b);
        //delay(10 / animate_led_speed_factor());
    }
    //for (int i = 255; i >= 0; i = i - 2)
    for (int i = 255; i >= 0; i = i-2)
    {
		if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(0, 0, 0);
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
        animate_led_set_all_pixels(r, g, b);
        //delay(10 / animate_led_speed_factor());
    }
}


void animate_led_strobe(uint16_t animate_led_strobe_count, uint16_t flash_delay, uint16_t end_pause)
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
			animate_led_set_all_pixels(0, 0, 0);
			return;
		}
        animate_led_set_all_pixels(red, green, blue);
        animate_led_show_strip();
        delay(flash_delay);
        animate_led_set_all_pixels(0, 0, 0);
        animate_led_show_strip();
        delay(flash_delay);
    }
    delay(end_pause);
}


void animate_led_cyclone_bounce(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = 0; i < NUM_LEDS - eye_size - 2; i++) // I think the -2 is CYA if someone says eye_size is 0
    {
		if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(0, 0, 0);
			return;
		}
        animate_led_set_all_pixels(0, 0, 0);
        animate_led_set_pixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(i + j, red, green, blue);
        }
        animate_led_set_pixel(i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
    for (int i = NUM_LEDS - eye_size - 2; i > 0; i--)
    {
		if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(0, 0, 0);
			return;
		}
        animate_led_set_all_pixels(0, 0, 0); 
        animate_led_set_pixel(i , red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(i + j, red, green, blue);
        }
        animate_led_set_pixel(i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
	animate_led_set_all_pixels(0, 0, 0);
}


void animate_led_center_to_outside(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = ((NUM_LEDS - eye_size) / 2); i >= 0; i--)
    {
        animate_led_set_all_pixels(0,0,0);
        animate_led_set_pixel(i, red/10, green/10, blue/10);
        for (int j = 1; j<= eye_size; j++)
        {
            animate_led_set_pixel(i + j, red, green, blue);
        }
        animate_led_set_pixel(i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_set_pixel(NUM_LEDS - i, red/10, green/10, blue/10);
        for (int j = 1; j<= eye_size; j++)
        {
            animate_led_set_pixel(NUM_LEDS - i - j, red, green, blue);
        }
        animate_led_set_pixel(NUM_LEDS - i - eye_size - 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_outside_to_center(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = 0; i <= ((NUM_LEDS - eye_size) / 2 ); i++)
    {
        animate_led_set_all_pixels(0, 0, 0);
        animate_led_set_pixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(i+j, red, green, blue);
        }
        animate_led_set_pixel(i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_set_pixel(NUM_LEDS - i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(NUM_LEDS - i - j, red, green, blue);
        }
        animate_led_set_pixel(NUM_LEDS - i - eye_size - 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_left_to_right(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = 0; i < NUM_LEDS - eye_size - 2; i++)
    {
        animate_led_set_all_pixels(0, 0, 0);
        animate_led_set_pixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(i + j, red, green, blue);
        }
        animate_led_set_pixel(i + eye_size + 1, red/10, green/10, blue/10);
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_right_to_left(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (int i = NUM_LEDS - eye_size - 2; i > 0; i--)
    {
        animate_led_set_all_pixels(0, 0, 0);
        animate_led_set_pixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            animate_led_set_pixel(i + j, red, green, blue);
        }
        animate_led_show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void animate_led_new_kitt(uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    animate_led_right_to_left(eye_size, speed_delay, return_delay);
    animate_led_left_to_right(eye_size, speed_delay, return_delay);
    animate_led_outside_to_center(eye_size, speed_delay, return_delay);
    animate_led_center_to_outside(eye_size, speed_delay, return_delay);
    animate_led_left_to_right(eye_size, speed_delay, return_delay);
    animate_led_right_to_left(eye_size, speed_delay, return_delay);
    animate_led_outside_to_center(eye_size, speed_delay, return_delay);
    animate_led_center_to_outside(eye_size, speed_delay, return_delay);
}


void animate_led_twinkle(uint16_t count, uint16_t speed_delay, bool only_one)
{
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    animate_led_set_all_pixels(0, 0, 0);
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
			animate_led_set_all_pixels(0, 0, 0);
			return;
		}
        animate_led_set_pixel(random(NUM_LEDS), red, green, blue);
        animate_led_show_strip();
        delay(speed_delay);
        if (only_one)
        {
            animate_led_set_all_pixels(0, 0, 0);
        }
    }
    delay(speed_delay);
}


void animate_led_twinkle_random(uint16_t count, uint16_t speed_delay, bool only_one)
{
    animate_led_set_all_pixels(0, 0, 0);
    for (int i = 0; i < count; i++)
    {
		if(animate_led_interrupt_flag_speed())
		{
			speed_delay = animate_led_delay_in_animations();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(0, 0, 0);
			return;
		}
        animate_led_set_pixel(random(NUM_LEDS), random(0, 255), random(0, 255), random(0, 255));
        animate_led_show_strip();
        delay(speed_delay);
        if (only_one)
        {
            animate_led_set_all_pixels(0, 0, 0);
        }
    }
    delay(speed_delay);
}


void animate_led_sparkle(uint16_t speed_delay)
{
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    int pix = random(NUM_LEDS);
	// should this be wrapped in for loop for NUM_LEDS
    animate_led_set_pixel(pix, red, green, blue);
    animate_led_show_strip();
    delay(speed_delay);
    animate_led_set_pixel(pix, 0, 0, 0);
}


void animate_led_running_lights()
{
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    uint16_t pos = 0;
    for (int i = 0; i < NUM_LEDS * 2; i++)
    {
		if(animate_led_interrupt_flag_color())
		{
			red = color_led_cur_color_red_hex();
			green = color_led_cur_color_green_hex();
			blue = color_led_cur_color_blue_hex();
		}
		else if (animate_led_interrupt_flag_state())
		{
			animate_led_set_all_pixels(0, 0, 0);
			return;
		}
        pos++;
        for(int i = 0; i < NUM_LEDS; i++)
        {
            animate_led_set_pixel(i, ((sin(i + pos) * 127 + 128) / 255) * red, ((sin(i + pos) * 127 + 128) / 255) * green, ((sin(i + pos) * 127 + 128) / 255) * blue); 
        }
        animate_led_show_strip();
		delay(100 /animate_led_speed_factor());
    }
}


void animate_led_color_wipe(uint16_t speed_delay)
{
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    for (uint16_t i = 0; i < NUM_LEDS; i++)
    {
        animate_led_set_pixel(i, red, green, blue);
        animate_led_show_strip();
        delay(speed_delay);
    }
    for (uint16_t i = 0; i < NUM_LEDS; i++)
    {
        animate_led_set_pixel(i, 0, 0, 0);
        animate_led_show_strip();
        delay(speed_delay);
    }
}


void animate_led_rainbow_cycle(uint16_t speed_delay)
{
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
			animate_led_set_all_pixels(0, 0, 0);
			return;
		}
        for (i = 0; i < NUM_LEDS; i++)
        {
            c = animate_led_wheel(((i * 256 / NUM_LEDS) + j) & 255);
            animate_led_set_pixel(i, *c, *(c + 1), *(c + 2));
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


void animate_led_theater_chase(uint16_t speed_delay)
{
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
				animate_led_set_all_pixels(0, 0, 0);
				return;
			}
            for (int i = 0; i < NUM_LEDS; i += 3)
            {
                animate_led_set_pixel(i + q, red, green, blue); // turn every third pixel on
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
            for (int i = 0; i < NUM_LEDS; i += 3)
            {
                animate_led_set_pixel(i + q, 0, 0, 0); // turn everty third pixel off
            }
        }
    }
}


void animate_led_theater_chase_rainbow(uint16_t speed_delay)
{
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
				animate_led_set_all_pixels(0, 0, 0);
				return;
			}
            for (int i = 0; i < NUM_LEDS; i = i + 3)
            {
                c = animate_led_wheel((i + j) % 255);
                animate_led_set_pixel(i + q, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            animate_led_show_strip();
			
            delay(speed_delay);
            for (int i = 0; i < NUM_LEDS; i = i + 3)
            {
                animate_led_set_pixel(i + q, 0, 0, 0); // turn every third pixel off
            }
        }
    }
}


void animate_led_bouncing_balls(int ball_count)
{
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
            pos[i] = round(height[i] * (NUM_LEDS - 1) / start_height);
        }
        for (int i = 0; i < ball_count; i++)
        {
            animate_led_set_pixel(pos[i], red, green, blue);
        }
        animate_led_show_strip();
        animate_led_set_all_pixels(0, 0, 0);
    //}
}


void animate_led_meteor_rain(byte meteor_size, byte meteor_trail_decay, bool meteor_random_decay, int speed_delay)
{
	uint8_t red, green, blue; 
	red = color_led_cur_color_red_hex();
	green = color_led_cur_color_green_hex();
	blue = color_led_cur_color_blue_hex();
    animate_led_set_all_pixels(0, 0, 0);
    for(int i = 0; i < NUM_LEDS + 50; i++) // 50 arbitrarily chosen SRW
    {
        for (int j = 0; j < NUM_LEDS; j++)
        {
            if ((!meteor_random_decay) || (random(10) > 5))
            {
                animate_led_fade_to_black(j, meteor_trail_decay);
            }
        }
        for (int j = 0; j < meteor_size; j++)
        {
            if ((i - j < NUM_LEDS) && (i - j >= 0))
            {
                animate_led_set_pixel(i - j, red, green, blue);
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
			animate_led_set_all_pixels(0, 0, 0);
			return;
		}
		// don't allow speed change!
        animate_led_show_strip();
        delay(speed_delay);
    }
}


void animate_led_fade_to_black(int led_no, byte fade_value)
{
    leds[led_no].fadeToBlackBy(fade_value);
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
        animate_led_set_pixel(pix, 255, 255, heatramp); // hottest
    }
    else if (t192 > 0x40)
    {
        animate_led_set_pixel(pix, 255, heatramp, 0); // medium
    }
    else
    {
        animate_led_set_pixel(pix, heatramp, 0, 0); // coolest
    }
    
}
*/

