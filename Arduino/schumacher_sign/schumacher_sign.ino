#include "FastLED.h"

#define NUM_LEDS 420
CRGB leds[NUM_LEDS];
#define PIN 8


// RF receiver IC pins
#define VT          1
#define D0          2
#define D1          3
#define D2          4
#define D3          5
#define PWR_ENABLE  6


typedef enum
{
    // RGB
    COLOR_HEX_BLACK = 0x000000,
    COLOR_HEX_WHITE = 0xFFFFFF,
    COLOR_HEX_RED = 0xFF0000,
    COLOR_HEX_LIME = 0x00FF00,
    COLOR_HEX_BLUE = 0x0000FF,
    COLOR_HEX_YELLOW = 0xFFFF00,
    COLOR_HEX_CYAN = 0x00FFFF,
    COLOR_HEX_MAGENTA = 0xFF00FF,
    COLOR_HEX_SILVER = 0xC0C0C0,
    COLOR_HEX_GRAY = 0x808080,
    COLOR_HEX_MAROON = 0x800000,
    COLOR_HEX_OLIVE = 0x808000,
    COLOR_HEX_GREEN = 0x008000,
    COLOR_HEX_PURPLE = 0x800080,
    COLOR_HEX_TEAL = 0x008080,
    COLOR_HEX_NAVY = 0x000080
} color_hex_code_e;


typedef enum
{
    COLORS_BLACK = 0,
    COLORS_WHITE,
    COLORS_RED,
    COLORS_LIME,
    COLORS_BLUE,
    COLORS_YELLOW,
    COLORS_CYAN,
    COLORS_MAGENTA,
    COLORS_SILVER,
    COLORS_GRAY,
    COLORS_MAROON,
    COLORS_OLIVE,
    COLORS_GREEN,
    COLORS_PURPLE,
    COLORS_TEAL,
    COLORS_NAVY,
    NUM_COLORS
} all_colors_e;


typedef enum
{
    DISP_COLOR_RED = 0,
    DISP_COLOR_LIME,
    DISP_COLOR_BLUE,
    DISP_COLOR_YELLOW,
    DISP_COLOR_CYAN,
    DISP_COLOR_MAGENTA,
    //DISP_COLOR_MAROON,
    DISP_COLOR_GREEN,
    DISP_COLOR_PURPLE,
    DISP_COLOR_TEAL,
    DISP_COLOR_NAVY,
    NUM_DISP_COLORS
} disp_colors_e;


typedef enum
{
    LED_STATE_FADE_IN_AND_OUT = 0,
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
    NUM_LED_STATES
} led_state_e;

#define LED_SPEED_FACTOR_SLOWEST    1.0
#define LED_SPEED_FACTOR_SLOW       0.75
#define LED_SPEED_FACTOR_FAST       0.5 
#define LED_SPEED_FACTOR_FASTEST    0.25


//led_state_e g_led_state = LED_STATE_METEOR;

led_state_e g_led_state = LED_STATE_THEATER_CHASE_RAINBOW;
color_hex_code_e g_colors[NUM_COLORS] = {0};
color_hex_code_e g_disp_colors[NUM_DISP_COLORS] = {0};
color_hex_code_e g_led_hex_code = COLOR_HEX_RED; 
disp_colors_e g_disp_color = DISP_COLOR_RED;
float g_strobe_speed_factor = 1.2;
uint16_t g_bounce_size = 4;
uint8_t twinkle_toggle = 1;
uint16_t g_master_count = 0;

const byte button1 = 21;
const byte button2 = 20;

unsigned long animation_last_time = 0;
unsigned long mode_switch_last_time = 0;
unsigned long debounceDelay = 50; // ms

void mode_switch_isr(void);
void animation_speed_isr(void);

void setup() 
{
    Serial.begin(9600);
    FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

    pinMode(VT, INPUT);
    pinMode(D3, INPUT);
    pinMode(D2, INPUT);
    pinMode(D1, INPUT);
    pinMode(D0, INPUT);
    
    interrupts();
    attachInterrupt(digitalPinToInterrupt(button1), mode_switch_isr, RISING);
    attachInterrupt(digitalPinToInterrupt(button2), animation_speed_isr, RISING);       
    // initialize color arrays
    g_disp_colors[DISP_COLOR_RED] = COLOR_HEX_RED;
    g_disp_colors[DISP_COLOR_LIME] = COLOR_HEX_LIME;
    g_disp_colors[DISP_COLOR_BLUE] = COLOR_HEX_BLUE;
    g_disp_colors[DISP_COLOR_YELLOW] = COLOR_HEX_YELLOW;
    g_disp_colors[DISP_COLOR_CYAN] = COLOR_HEX_CYAN;
    g_disp_colors[DISP_COLOR_MAGENTA] = COLOR_HEX_MAGENTA;
    //g_disp_colors[DISP_COLOR_MAROON] = COLOR_HEX_MAROON;
    g_disp_colors[DISP_COLOR_GREEN] = COLOR_HEX_GREEN;
    g_disp_colors[DISP_COLOR_PURPLE] = COLOR_HEX_PURPLE;
    g_disp_colors[DISP_COLOR_TEAL] = COLOR_HEX_TEAL;
    g_disp_colors[DISP_COLOR_NAVY] = COLOR_HEX_NAVY;
    
    g_colors[COLORS_BLACK] = COLOR_HEX_BLACK;
    g_colors[COLORS_WHITE] = COLOR_HEX_WHITE;
    g_colors[COLORS_RED] = COLOR_HEX_RED;
    g_colors[COLORS_LIME] = COLOR_HEX_LIME;
    g_colors[COLORS_BLUE] = COLOR_HEX_BLUE;
    g_colors[COLORS_YELLOW] = COLOR_HEX_YELLOW;
    g_colors[COLORS_CYAN] = COLOR_HEX_CYAN;
    g_colors[COLORS_MAGENTA] = COLOR_HEX_MAGENTA;
    g_colors[COLORS_SILVER] = COLOR_HEX_SILVER;
    g_colors[COLORS_GRAY] = COLOR_HEX_GRAY;
    g_colors[COLORS_MAROON] = COLOR_HEX_MAROON;
    g_colors[COLORS_OLIVE] = COLOR_HEX_OLIVE;
    g_colors[COLORS_GREEN] = COLOR_HEX_GREEN;
    g_colors[COLORS_PURPLE] = COLOR_HEX_PURPLE;
    g_colors[COLORS_TEAL] = COLOR_HEX_TEAL;
    g_colors[COLORS_NAVY] = COLOR_HEX_NAVY;
}

bool g_mode_switch = false;
void mode_switch_isr()
{
    if ((millis() - mode_switch_last_time) > debounceDelay)
    {
        mode_switch_last_time = millis();
    }
    else return;
    g_mode_switch = true;
    Serial.println("hello! mode switch");
}



void animation_speed_isr()
{
    if ((millis() - animation_last_time) > debounceDelay)
    {
        animation_last_time = millis();
    }
    else return;
    Serial.println("hello! animation speed switch");
}


color_hex_code_e random_color(void)
{
    disp_colors_e color = (disp_colors_e)(random(NUM_DISP_COLORS));
    if (g_disp_color == color)
    {
        if (color == DISP_COLOR_NAVY)
        {
            color = (disp_colors_e)(color - 1);
        }
        else
        {
            color = (disp_colors_e)(color + 1);
        }
    }
    switch (color)
    {
        case DISP_COLOR_RED: 
            g_disp_color = DISP_COLOR_RED;
            return COLOR_HEX_RED;
        case DISP_COLOR_LIME: 
            g_disp_color = DISP_COLOR_LIME;
            return COLOR_HEX_LIME;
        case DISP_COLOR_BLUE: 
            g_disp_color = DISP_COLOR_BLUE;
            return COLOR_HEX_BLUE;
        case DISP_COLOR_YELLOW: 
            g_disp_color = DISP_COLOR_YELLOW;
            return COLOR_HEX_YELLOW;
        case DISP_COLOR_CYAN: 
            g_disp_color = DISP_COLOR_CYAN;
            return COLOR_HEX_CYAN;
        case DISP_COLOR_MAGENTA: 
            g_disp_color = DISP_COLOR_MAGENTA;
            return COLOR_HEX_MAGENTA;
        /*
        case DISP_COLOR_MAROON: 
            g_disp_color = DISP_COLOR_MAROON;
            return COLOR_HEX_MAROON;
        */
        case DISP_COLOR_GREEN: 
            g_disp_color = DISP_COLOR_GREEN;
            return COLOR_HEX_GREEN;
        case DISP_COLOR_PURPLE: 
            g_disp_color = DISP_COLOR_PURPLE;
            return COLOR_HEX_PURPLE;
        case DISP_COLOR_TEAL: 
            g_disp_color = DISP_COLOR_TEAL;
            return COLOR_HEX_TEAL;
        case DISP_COLOR_NAVY: 
            g_disp_color = DISP_COLOR_NAVY;
            return COLOR_HEX_NAVY;
        default: 
            g_disp_color = DISP_COLOR_RED;
            return COLOR_HEX_RED;
    }
}


led_state_e random_state(void)
{
    led_state_e state = (led_state_e)(random(NUM_LED_STATES));
    if (g_led_state == state)
    {
        if ((led_state_e)(g_led_state + 1) == NUM_LED_STATES)
        {
            state = (led_state_e)(state - 1);
        }
        else
        {
            state = (led_state_e)(state + 1);
        }
    }
    return state;
}


void handle_count_and_color(void)
{
    g_master_count++;
    if (!(g_master_count % 10))
    {
        if(LED_STATE_TWINKLE == g_led_state) twinkle_toggle ^=1;
        g_led_state = random_state();
    }
    g_led_hex_code = random_color();
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
            //void fade_in_fade_out(disp_colors_e color)
            fade_in_fade_out(g_led_hex_code);
            delay(1000);
        break;
        case LED_STATE_STROBE:
            //void strobe(disp_colors_e color, uint16_t strobe_count, uint16_t flash_delay, uint16_t end_pause)
            g_strobe_speed_factor -= 0.2;
            if (g_strobe_speed_factor <= 0) g_strobe_speed_factor = 1.2;
            strobe(g_led_hex_code, 10 * (1 + g_strobe_speed_factor), 100 * g_strobe_speed_factor, 500);
        break;
        case LED_STATE_CYCLONE_BOUNCE:
            //void cyclone_bounce(disp_colors_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
            g_bounce_size *= 2;
            if (g_bounce_size > NUM_LEDS) g_bounce_size = 4;            
            cyclone_bounce(g_led_hex_code, g_bounce_size, 0, 0);
        break;
        /*
        case LED_STATE_KITT:
            //void new_kitt(disp_colors_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay)
            new_kitt(g_led_hex_code, 20, 1, 1);
        break;
        */
        case LED_STATE_TWINKLE:
            //void twinkle(disp_colors_e color, uint16_t count, uint16_t speed_delay, bool only_one)
            twinkle(g_led_hex_code, NUM_LEDS/3, 100, twinkle_toggle);
            delay(1000);
        break;
        /*
        case LED_STATE_TWINKLE_RANDOM:
            //void twinkle_random(uint16_t count, uint16_t speed_delay, bool only_one)
            twinkle_random(100, 10, true);
        break;
        */
        case LED_STATE_SPARKLE:
            //void sparkle(disp_colors_e color, uint16_t speed_delay)
            sparkle(g_led_hex_code, 100);
        break;
        case LED_STATE_RUNNING_LIGHTS:
            //void running_lights(disp_colors_e color, uint16_t wave_delay)
            running_lights(g_led_hex_code, 0);
        break;
        case LED_STATE_RAINBOW_CYCLE:
            rainbow_cycle(0);
            //void rainbow_cycle(uint16_t speed_delay)
        break;
        case LED_STATE_THEATER_CHASE:
            //void theater_chase(disp_colors_e color, uint16_t speed_delay)
            theater_chase(g_led_hex_code, 100);
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
            meteor_rain(g_led_hex_code, 20, 64, true, 5);
        break;
    }
    handle_count_and_color();
   #endif
}


void show_strip()
{
    FastLED.show();
}


void setPixel(int Pixel, byte red, byte green, byte blue)
{
    leds[Pixel].r = red;
    leds[Pixel].g = green;
    leds[Pixel].b = blue;
}


void set_all(byte red, byte green, byte blue) 
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        setPixel(i, red, green, blue);
    }
    show_strip();
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
        set_all(r, g, b);
        delay(10);
    }
    //for (int i = 255; i >= 0; i = i - 2)
    for (int i = 255; i >= 0; i = i-2)
    {
        r = (i / 256.0) * red;
        g = (i / 256.0) * green;
        b = (i / 256.0) * blue;
        set_all(r, g, b);
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
        set_all(red, green, blue);
        show_strip();
        delay(flash_delay);
        set_all(0, 0, 0);
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
        set_all(0, 0, 0);
        setPixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + eye_size + 1, red/10, green/10, blue/10);
        show_strip();
        delay(speed_delay);
    }
    delay(return_delay);
    for (int i = NUM_LEDS - eye_size - 2; i > 0; i--)
    {
        set_all(0, 0, 0); 
        setPixel(i , red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + eye_size + 1, red/10, green/10, blue/10);
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
        set_all(0,0,0);
        setPixel(i, red/10, green/10, blue/10);
        for (int j = 1; j<= eye_size; j++)
        {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + eye_size + 1, red/10, green/10, blue/10);
        setPixel(NUM_LEDS - i, red/10, green/10, blue/10);
        for (int j = 1; j<= eye_size; j++)
        {
            setPixel(NUM_LEDS - i - j, red, green, blue);
        }
        setPixel(NUM_LEDS - i - eye_size - 1, red/10, green/10, blue/10);
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
        set_all(0, 0, 0);
        setPixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            setPixel(i+j, red, green, blue);
        }
        setPixel(i + eye_size + 1, red/10, green/10, blue/10);
        setPixel(NUM_LEDS - i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            setPixel(NUM_LEDS - i - j, red, green, blue);
        }
        setPixel(NUM_LEDS - i - eye_size - 1, red/10, green/10, blue/10);
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
        set_all(0, 0, 0);
        setPixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + eye_size + 1, red/10, green/10, blue/10);
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
        set_all(0, 0, 0);
        setPixel(i, red/10, green/10, blue/10);
        for (int j = 1; j <= eye_size; j++)
        {
            setPixel(i + j, red, green, blue);
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
    set_all(0, 0, 0);
    for (int i = 0; i < count; i++)
    {
        setPixel(random(NUM_LEDS), red, green, blue);
        show_strip();
        delay(speed_delay);
        if (only_one)
        {
            set_all(0, 0, 0);
        }
    }
    delay(speed_delay);
}


void twinkle_random(uint16_t count, uint16_t speed_delay, bool only_one)
{
    set_all(0, 0, 0);
    for (int i = 0; i < count; i++)
    {
        setPixel(random(NUM_LEDS), random(0, 255), random(0, 255), random(0, 255));
        show_strip();
        delay(speed_delay);
        if (only_one)
        {
            set_all(0, 0, 0);
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
    setPixel(pix, red, green, blue);
    show_strip();
    delay(speed_delay);
    setPixel(pix, 0, 0, 0);
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
            setPixel(i, ((sin(i + pos) * 127 + 128) / 255) * red, ((sin(i + pos) * 127 + 128) / 255) * green, ((sin(i + pos) * 127 + 128) / 255) * blue); 
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
        setPixel(i, red, green, blue);
        show_strip();
        delay(speed_delay);
    }
    for (uint16_t i = 0; i < NUM_LEDS; i++)
    {
        setPixel(i, 0, 0, 0);
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
            setPixel(i, *c, *(c + 1), *(c + 2));
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
                setPixel(i + q, red, green, blue); // turn every third pixel on
            }
            show_strip();
            delay(speed_delay);
            for (int i = 0; i < NUM_LEDS; i += 3)
            {
                setPixel(i + q, 0, 0, 0); // turn everty third pixel off
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
                setPixel(i + q, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            show_strip();
            delay(speed_delay);
            for (int i = 0; i < NUM_LEDS; i = i + 3)
            {
                setPixel(i + q, 0, 0, 0); // turn every third pixel off
            }
        }
    }
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
        setPixelHeatColor(j, heat[j]);
    }
    show_strip();
    delay(speed_delay);
}


void setPixelHeatColor(int pix, byte temp)
{
    byte t192 = round((temp / 255.0) *191);
    byte heatramp = t192 & 0x3F;
    heatramp <<= 2;

    if(t192 > 0x80)
    {
        setPixel(pix, 255, 255, heatramp); // hottest
    }
    else if (t192 > 0x40)
    {
        setPixel(pix, 255, heatramp, 0); // medium
    }
    else
    {
        setPixel(pix, heatramp, 0, 0); // coolest
    }
    
}
*/


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
            setPixel(pos[i], red, green, blue);
        }
        show_strip();
        set_all(0, 0, 0);
    //}
}


void meteor_rain(color_hex_code_e color, byte meteor_size, byte meteor_trail_decay, bool meteor_random_decay, int speed_delay)
{
    uint8_t red = (color & 0xFF0000) >> 16;
    uint8_t green = (color & 0x00FF00) >> 8;
    uint8_t blue = color & 0x0000FF;
    set_all(0, 0, 0);
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
                setPixel(i - j, red, green, blue);
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
