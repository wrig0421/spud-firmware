#include "FastLED.h"
#include <animate_led.h>
#include <color_led.h>

#define NUM_LEDS 420
CRGB leds[NUM_LEDS];
#define PIN 8

/*
// RF receiver IC pins
#define VT          1
#define D0          2
#define D1          3
#define D2          4
#define D3          5
#define PWR_ENABLE  6
*/

//#define SERIAL_DEBUG
#define LED_SPEED_FACTOR_SLOWEST    1.0
#define LED_SPEED_FACTOR_SLOW       0.75
#define LED_SPEED_FACTOR_FAST       0.5 
#define LED_SPEED_FACTOR_FASTEST    0.25


//led_state_e g_led_state = LED_STATE_METEOR;
all_colors_e g_color = COLORS_RED;


led_state_e g_led_state = LED_STATE_THEATER_CHASE_RAINBOW;
color_hex_code_e g_colors[NUM_COLORS] = {0};
color_hex_code_e g_led_hex_code = COLOR_HEX_RED; 
disp_colors_e g_disp_color = DISP_COLOR_RED;
float g_strobe_speed_factor = 1.2;
uint16_t g_bounce_size = 4;
uint8_t twinkle_toggle = 1;
uint16_t g_master_count = 0;


typedef enum
{
    ISR_SPEED = 0,
    ISR_STATE,
    ISR_COLOR,
    ISR_PAUSE,
    NUM_ISR
} isr_e;

typedef enum
{
    INT_BTN_SPEED = 21,
    INT_BTN_STATE = 20,
    INT_BTN_COLOR = 19,
    INT_BTN_PAUSE = 18,
} interrupt_button_e;

unsigned long isr_times[NUM_ISR] = {0};
unsigned long debounceDelay = 50; // ms

void handle_count_and_color(void);

void isr_state_change(void);
void isr_color_change(void);
void isr_speed_change(void);
void isr_pause(void);


void setup() 
{
#if defined(SERIAL_DEBUG)
    Serial.begin(9600);
#endif
    FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    interrupts();
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_SPEED), isr_speed_change, RISING);
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_STATE), isr_state_change, RISING);       
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_COLOR), isr_color_change, RISING);
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_PAUSE), isr_pause, RISING);       
}


void handle_count_and_color(void)
{
    led_state_increment_iterations();
    if (!(animate_led_iterations() % 10))
    {
        //if(LED_STATE_TWINKLE == g_led_state) twinkle_toggle ^=1;
        animate_led_state_randomize();
    }
    color_led_randomize();
}


void isr_state_change(void)
{
    if ((millis() - isr_times[ISR_STATE]) > debounceDelay)
    {
        isr_times[ISR_STATE] = millis();
    }
    else return;
    animate_led_adjust_state();
}


void isr_color_change(void)
{
    if ((millis() - isr_times[ISR_COLOR]) > debounceDelay)
    {
        isr_times[ISR_COLOR] = millis();
    }
    else return;
    color_led_adjust_color();
}


void isr_speed_change(void)
{
    if ((millis() - isr_times[ISR_SPEED]) > debounceDelay)
    {
        isr_times[ISR_SPEED] = millis();
    }
    else return;
    animate_led_adjust_speed();
}


void isr_pause(void)
{
    if ((millis() - isr_times[ISR_PAUSE]) > debounceDelay)
    {
        isr_times[ISR_PAUSE] = millis();
    }
    else return;
}


void loop() 
{
    /*
    if (g_mode_switch)
    {
        Serial.println("hello! mode switch");
    }
    */
    #if 0
    switch(g_led_state)
    {
        /*
        case LED_STATE_FADE_IN_AND_OUT: 
        break;
        */
        case LED_STATE_FADE_IN_AND_OUT:
            fade_in_fade_out(color_led_cur_color_hex());
            //delay(1000);
        break;
        case LED_STATE_STROBE:
            g_strobe_speed_factor -= 0.2;
            if (g_strobe_speed_factor <= 0) g_strobe_speed_factor = 1.2;
            strobe(g_led_hex_code, 10 * (1 + g_strobe_speed_factor), 100 * g_strobe_speed_factor, 500);
        break;
        case LED_STATE_CYCLONE_BOUNCE:
            g_bounce_size *= 2;
            if (g_bounce_size > NUM_LEDS) g_bounce_size = 4;            
            cyclone_bounce(color_led_cur_color_hex(), g_bounce_size, 0, 0);
        break;
        /*
        case LED_STATE_KITT:
            //void new_kitt(disp_colors_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
            new_kitt(g_led_hex_code, 20, 1, 1);
        break;
        */
        case LED_STATE_TWINKLE:
            twinkle();
            //delay(1000);
        break;
        /*
        case LED_STATE_TWINKLE_RANDOM:
            //void twinkle_random(uint16_t count, uint16_t speed_delay, bool only_one)
            twinkle_random(100, 10, true);
        break;
        */
        case LED_STATE_SPARKLE:
            //void sparkle(disp_colors_e color, uint16_t speed_delay)
            sparkle(color_led_cur_color_hex(), 100);
        break;
        case LED_STATE_RUNNING_LIGHTS:
            //void running_lights(disp_colors_e color, uint16_t wave_delay)
            running_lights(color_led_cur_color_hex(), 0);
        break;
        case LED_STATE_RAINBOW_CYCLE:
            rainbow_cycle(0);
            //void rainbow_cycle(uint16_t speed_delay)
        break;
        case LED_STATE_THEATER_CHASE:
            //void theater_chase(disp_colors_e color, uint16_t speed_delay)
            theater_chase(color_led_cur_color_hex(), 100);
        break;
        case LED_STATE_THEATER_CHASE_RAINBOW:
            //void theater_chase_rainbow(uint16_t speed_delay)
            theater_chase_rainbow(100);
        break;
        /*
        case LED_STATE_FIRE:
        break;
        case LED_STATE_BOUNCING_BALLS:
            //void bouncing_balls(disp_colors_e color, int ball_count)
            bouncing_balls(g_led_hex_code, 10);
        break;
        case LED_STATE_BOUNCING_BALLS_RANDOM:
        break;
        */
        case LED_STATE_METEOR:
            //void meteor_rain(disp_colors_e color, byte meteor_size, byte meteor_trail_decay, bool meteor_random_decay, int speed_delay)
            meteor_rain(color_led_cur_color_hex(), 20, 64, true, 5);
        break;
    }
    handle_count_and_color();
   #endif
}
