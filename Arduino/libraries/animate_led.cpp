#include <stdint.h>
#include <stdbool.h>
#include "animate_led.h"


typedef enum
{
	LED_STATE_FIRST,
    LED_STATE_FADE_IN_AND_OUT = LED_STATE_FIRST,
    //LED_STATE_FADE_IN_AND_OUT_RANDOM,
    LED_STATE_STROBE,
    //LED_STATE_KITT,
    LED_STATE_TWINKLE,
    LED_STATE_CYCLONE_BOUNCE,
    //LED_STATE_TWINKLE_RANDOM,
    LED_STATE_SPARKLE,
    LED_STATE_RUNNING_LIGHTS,
    LED_STATE_RAINBOW_CYCLE,
    LED_STATE_THEATER_CHASE,
    LED_STATE_THEATER_CHASE_RAINBOW,
    //LED_STATE_FIRE,
    //LED_STATE_BOUNCING_BALLS,
    //LED_STATE_BOUNCING_BALLS_RANDOM,
    LED_STATE_METEOR,
	LED_STATE_LAST = LED_STATE_METEOR,
    NUM_LED_STATES
} led_state_e;



typedef enum
{
	LED_SPEED_FIRST,
	LED_SPEED_10X = LED_SPEED_FIRST,
	LED_SPEED_5X,
	LED_SPEED_2X,
	LED_SPEED_1X,
	LED_SPEED_0P5X,
	LED_SPEED_0P25X,
	LED_SPEED_0P1X,
	LED_SPEED_LAST = LED_SPEED_0P1X,
	NUM_SPEEDS
} led_speed_e;


//#define SERIAL_DEBUG
#define LED_SPEED_FACTOR_SLOWEST    1.0
#define LED_SPEED_FACTOR_SLOW       0.75
#define LED_SPEED_FACTOR_FAST       0.5 
#define LED_SPEED_FACTOR_FASTEST    0.25

led_speed_e g_led_speed = LED_SPEED_1X;

led_state_e g_led_state = LED_STATE_FADE_IN_AND_OUT;
uint32_t g_iterations = 0; 

void animate_led_adjust_speed(void)
{
	if (LED_SPEED_LAST == g_led_speed) g_led_speed = LED_SPEED_FIRST;
	else g_led_speed = (led_speed_e) (g_led_speed + 1);
}


void animate_led_adjust_state(void)
{
	if (LED_STATE_LAST == g_led_state) g_led_state = LED_STATE_FIRST;
	else g_led_state = (led_speed_e) (g_led_state + 1);
}


void animate_led_init(void)
{
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


void show_strip(void)
{
    FastLED.show();
}


void set_pixel(int Pixel, byte red, byte green, byte blue)
{
    leds[Pixel].r = red;
    leds[Pixel].g = green;
    leds[Pixel].b = blue;
}


void set_all_pixels(byte red, byte green, byte blue) 
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        set_pixel(i, red, green, blue);
    }
    show_strip();
}


void animate_led_state_randomize(void)
{
    led_state_e state = (led_state_e)(random(NUM_LED_STATES));
    if (g_led_state == state)
    {
        if ((led_state_e)(g_led_state + 1) == NUM_LED_STATES)
        {
            g_led_state = (led_state_e)(state - 1);
        }
        else
        {
            g_led_state = (led_state_e)(state + 1);
        }
    }
}


void fade_in_fade_out(color_hex_code_e color)
{
    float r, g, b;
    uint8_t red, green, blue; 
    red = (color & 0xFF0000) >> 16;
    green = (color & 0x00FF00) >> 8;
    blue = color & 0x0000FF;
    for (int i = 0; i < 256; i++)
    {
        r = (i / 256.0) * red;
        g = (i / 256.0) * green;
        b = (i / 256.0) * blue;
        set_all_pixels(r, g, b);
        delay(10);
    }
    //for (int i = 255; i >= 0; i = i - 2)
    for (int i = 255; i >= 0; i = i-2)
    {
        r = (i / 256.0) * red;
        g = (i / 256.0) * green;
        b = (i / 256.0) * blue;
        set_all_pixels(r, g, b);
        delay(10);
    }
}


void strobe(color_hex_code_e color, uint16_t strobe_count, uint16_t flash_delay, uint16_t end_pause)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    for (int i = 0; i < strobe_count; i++)
    {
        set_all_pixels(red, green, blue);
        show_strip();
        delay(flash_delay);
        set_all_pixels(0, 0, 0);
        show_strip();
        delay(flash_delay);
    }
    delay(end_pause);
}


void cyclone_bounce(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    for (int i = 0; i < NUM_LEDS - eye_size - 2; i++) // I think the -2 is CYA if someone says eye_size is 0
    {
        set_all_pixels(0, 0, 0);
        set_pixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            set_pixel(i + j, red, green, blue);
        }
        set_pixel(i + eye_size + 1, red/10, green/10, blue/10);
        show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
    for (int i = NUM_LEDS - eye_size - 2; i > 0; i--)
    {
        set_all_pixels(0, 0, 0); 
        set_pixel(i , red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            set_pixel(i + j, red, green, blue);
        }
        set_pixel(i + eye_size + 1, red/10, green/10, blue/10);
        show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void new_kitt(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    right_to_left(color, eye_size, speed_delay, return_delay);
    left_to_right(color, eye_size, speed_delay, return_delay);
    outside_to_center(color, eye_size, speed_delay, return_delay);
    center_to_outside(color, eye_size, speed_delay, return_delay);
    left_to_right(color, eye_size, speed_delay, return_delay);
    right_to_left(color, eye_size, speed_delay, return_delay);
    outside_to_center(color, eye_size, speed_delay, return_delay);
    center_to_outside(color, eye_size, speed_delay, return_delay);
}



void center_to_outside(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    for (int i = ((NUM_LEDS - eye_size) / 2); i >= 0; i--)
    {
        set_all_pixels(0,0,0);
        set_pixel(i, red/10, green/10, blue/10);
        for (int j = 1; j<= eye_size; j++)
        {
            set_pixel(i + j, red, green, blue);
        }
        set_pixel(i + eye_size + 1, red/10, green/10, blue/10);
        set_pixel(NUM_LEDS - i, red/10, green/10, blue/10);
        for (int j = 1; j<= eye_size; j++)
        {
            set_pixel(NUM_LEDS - i - j, red, green, blue);
        }
        set_pixel(NUM_LEDS - i - eye_size - 1, red/10, green/10, blue/10);
        show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void outside_to_center(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    for (int i = 0; i <= ((NUM_LEDS - eye_size) / 2 ); i++)
    {
        set_all_pixels(0, 0, 0);
        set_pixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            set_pixel(i+j, red, green, blue);
        }
        set_pixel(i + eye_size + 1, red/10, green/10, blue/10);
        set_pixel(NUM_LEDS - i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            set_pixel(NUM_LEDS - i - j, red, green, blue);
        }
        set_pixel(NUM_LEDS - i - eye_size - 1, red/10, green/10, blue/10);
        show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void left_to_right(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    for (int i = 0; i < NUM_LEDS - eye_size - 2; i++)
    {
        set_all_pixels(0, 0, 0);
        set_pixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            set_pixel(i + j, red, green, blue);
        }
        set_pixel(i + eye_size + 1, red/10, green/10, blue/10);
        show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void right_to_left(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    for (int i = NUM_LEDS - eye_size - 2; i > 0; i--)
    {
        set_all_pixels(0, 0, 0);
        set_pixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            set_pixel(i + j, red, green, blue);
        }
        show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
}


void twinkle(color_hex_code_e color, uint16_t count, uint16_t speed_delay, bool only_one)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    set_all_pixels(0, 0, 0);
    for (int i = 0; i < count; i++)
    {
        set_pixel(random(NUM_LEDS), red, green, blue);
        show_strip();
        delay(speed_delay);
        if (only_one)
        {
            set_all_pixels(0, 0, 0);
        }
    }
    delay(speed_delay);
}


void twinkle_random(uint16_t count, uint16_t speed_delay, bool only_one)
{
    set_all_pixels(0, 0, 0);
    for (int i = 0; i < count; i++)
    {
        set_pixel(random(NUM_LEDS), random(0, 255), random(0, 255), random(0, 255));
        show_strip();
        delay(speed_delay);
        if (only_one)
        {
            set_all_pixels(0, 0, 0);
        }
    }
    delay(speed_delay);
}


void sparkle(color_hex_code_e color, uint16_t speed_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    int pix = random(NUM_LEDS);
    set_pixel(pix, red, green, blue);
    show_strip();
    delay(speed_delay);
    set_pixel(pix, 0, 0, 0);
}


void running_lights(color_hex_code_e color, uint16_t wave_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    uint16_t pos = 0;
    for (int i = 0; i < NUM_LEDS * 2; i++)
    {
        pos++;
        for(int i = 0; i < NUM_LEDS; i++)
        {
            set_pixel(i, ((sin(i + pos) * 127 + 128) / 255) * red, ((sin(i + pos) * 127 + 128) / 255) * green, ((sin(i + pos) * 127 + 128) / 255) * blue); 
        }
        show_strip();
        delay(wave_delay);
    }
}


void color_wipe(color_hex_code_e color, uint16_t speed_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    for (uint16_t i = 0; i < NUM_LEDS; i++)
    {
        set_pixel(i, red, green, blue);
        show_strip();
        delay(speed_delay);
    }
    for (uint16_t i = 0; i < NUM_LEDS; i++)
    {
        set_pixel(i, 0, 0, 0);
        show_strip();
        delay(speed_delay);
    }
}


void rainbow_cycle(uint16_t speed_delay)
{
    byte *c;
    uint16_t i, j;
    for (j = 0; j < 256 * 5; j++)
    {
        for (i = 0; i < NUM_LEDS; i++)
        {
            c = wheel(((i * 256 / NUM_LEDS) + j) & 255);
            set_pixel(i, *c, *(c + 1), *(c + 2));
        }
        show_strip();
        delay(speed_delay);
    }
}


byte* wheel(byte wheel_pos)
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


void theater_chase(color_hex_code_e color, uint16_t speed_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    for (int j = 0; j < 10; j++)
    {
        for (int q = 0; q < 3; q++)
        {
            for (int i = 0; i < NUM_LEDS; i += 3)
            {
                set_pixel(i + q, red, green, blue); // turn every third pixel on
            }
            show_strip();
            delay(speed_delay);
            for (int i = 0; i < NUM_LEDS; i += 3)
            {
                set_pixel(i + q, 0, 0, 0); // turn everty third pixel off
            }
        }
    }
}


void theater_chase_rainbow(uint16_t speed_delay)
{
    byte *c;
    for (int j = 0; j < 256; j++) // cycel all 256 colors in the wheel
    {
        for (int q = 0; q < 3; q++)
        {
            for (int i = 0; i < NUM_LEDS; i = i + 3)
            {
                c = wheel((i + j) % 255);
                set_pixel(i + q, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            show_strip();
            delay(speed_delay);
            for (int i = 0; i < NUM_LEDS; i = i + 3)
            {
                set_pixel(i + q, 0, 0, 0); // turn every third pixel off
            }
        }
    }
}


void bouncing_balls(color_hex_code_e color, int ball_count)
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
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    
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
            set_pixel(pos[i], red, green, blue);
        }
        show_strip();
        set_all_pixels(0, 0, 0);
    //}
}


void meteor_rain(color_hex_code_e color, byte meteor_size, byte meteor_trail_decay, bool meteor_random_decay, int speed_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    set_all_pixels(0, 0, 0);
    for(int i = 0; i < NUM_LEDS + 50; i++) // 50 arbitrarily chosen SRW
    {
        for (int j = 0; j < NUM_LEDS; j++)
        {
            if ((!meteor_random_decay) || (random(10) > 5))
            {
                fade_to_black(j, meteor_trail_decay);
            }
        }
        for (int j = 0; j < meteor_size; j++)
        {
            if ((i - j < NUM_LEDS) && (i - j >= 0))
            {
                set_pixel(i - j, red, green, blue);
            }
        }
        show_strip();
        delay(speed_delay);
    }
}


void fade_to_black(int led_no, byte fade_value)
{
    leds[led_no].fadeToBlackBy(fade_value);
}


// kind of lame..  I don't plan on using
/*
void fire(uint16_t cooling, uint16_t sparking, uint16_t speed_delay)
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
        set_pixelHeatColor(j, heat[j]);
    }
    show_strip();
    delay(speed_delay);
}


void set_pixelHeatColor(int pix, byte temp)
{
    byte t192 = round((temp / 255.0) *191);
    byte heatramp = t192 & 0x3F;
    heatramp <<= 2;

    if(t192 > 0x80)
    {
        set_pixel(pix, 255, 255, heatramp); // hottest
    }
    else if (t192 > 0x40)
    {
        set_pixel(pix, 255, heatramp, 0); // medium
    }
    else
    {
        set_pixel(pix, heatramp, 0, 0); // coolest
    }
    
}
*/

