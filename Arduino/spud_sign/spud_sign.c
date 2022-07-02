#include <animate_led.h>
#include <color_led.h>
#include <FastLED.h>
#include <Arduino.h>

// static definitions
#define SERIAL_DEBUG // define to print debug messages

#if !defined(TOGETHER_SIGN) && !defined(SCHUMACHER_SIGN) && !defined(SPUDS_PUB_SIGN)
#pragma error("no sign defined");
#endif


// typedefs, structs, enums
typedef enum
{
    MASTER_STATE_DEMO,
    MASTER_STATE_FIXED
} master_led_state_e;


typedef enum
{
    MASTER_COLOR_DEMO,
    MASTER_COLOR_FIXED
} master_color_state_e;


typedef enum
{
#if defined(TOGETHER_SIGN)
    INT_BTN_PAUSE = 21,
    INT_BTN_STATE = 20,  // A
    INT_BTN_SPEED = 19,  // D
    INT_BTN_COLOR = 18,  // C
#elif defined(SCHUMACHER_SIGN)
    INT_BTN_PAUSE = 19,
    INT_BTN_STATE = 18,  // A
    INT_BTN_SPEED = 20,  // D
    INT_BTN_COLOR = 21,  // B
#elif defined(SPUDS_PUB_SIGN)
    INT_BTN_SPEED = 18,
    INT_BTN_STATE = 19,  
    INT_BTN_PAUSE = 20,  
    INT_BTN_COLOR = 21,  
#endif 
} interrupt_button_e;


// local function prototypes
void handle_count_and_color(void);
void isr_state_change(void);
void isr_color_change(void);
void isr_speed_change(void);
void isr_pause(void);


// global variables
//master_led_state_e g_master_led_state = MASTER_STATE_DEMO; // start solid white for reception
master_led_state_e g_master_led_state = MASTER_STATE_FIXED;
//master_color_state_e g_master_color_state = MASTER_COLOR_DEMO;
master_color_state_e g_master_color_state = MASTER_COLOR_FIXED;

unsigned long isr_times[NUM_ISR] = {0};
unsigned long debounce_delay = 2000; // ms
bool g_state_flag = false;
bool g_master_color_state_change_flag = false;
bool g_master_led_state_change_flag = false;
bool g_state_short_circuit_flag = false;


void setup() 
{
    Serial.begin(9600);
    String msg = "";
#if defined(SERIAL_DEBUG)
#if defined(TOGETHER_SIGN)
    msg = "Together sign";
#elif defined(SCHUMACHER_SIGN)
    msg = "Schumacher sign";
#elif defined(SPUDS_PUB_SIGN)
    msg = "Spud's Pub Sign";
#endif
    Serial.println(msg);
#endif
    pinMode(LED_BUILTIN, OUTPUT);
    color_led_init();
    animate_led_init();
    delay(10000);
    pinMode((byte)INT_BTN_SPEED, INPUT);
    pinMode((byte)INT_BTN_STATE, INPUT);
    pinMode((byte)INT_BTN_COLOR, INPUT);
    pinMode((byte)INT_BTN_PAUSE, INPUT); 
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_SPEED), isr_speed_change, LOW);  // speed is 18
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_STATE), isr_state_change, LOW); 
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_COLOR), isr_color_change, LOW);  
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_PAUSE), isr_pause, LOW); 
}

uint8_t g_toggle = 1;
void loop() 
{
#if defined(SERIAL_DEBUG)
    // these print on each iteration...simply for quick debug
    if (MASTER_STATE_FIXED == g_master_led_state) Serial.println("MASTER STATE LED FIXED");
    else Serial.println("MASTER STATE LED DEMO");
    if (MASTER_COLOR_FIXED == g_master_color_state) Serial.println("MASTER COLOR LED FIXED");
    else Serial.println("MASTER COLOR LED DEMO");
    Serial.println(animate_led_iterations(), DEC); // print iteration count
#endif
    handle_count_and_color(); // select state, color based iteration count
    if (g_master_led_state_change_flag)
    {
        animate_led_reset_iterations();
        master_led_state_change();
        g_master_led_state_change_flag = false;
    }
    switch(animate_led_state())
    {
        
//        case LED_STATE_WHITE_COLOR:
//#if defined(SERIAL_DEBUG)
//            Serial.println("STATE_SOLID_WHITE_COLOR");    
//#endif
//            // the color change doesn't matter for solid white.. 
//            animate_led_set_solid_white_color();
//            delay(animate_led_delay_between_animations());
//        break;
        case LED_STATE_SOLID_COLOR:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_SOLID_COLOR");
#endif
            animate_led_solid_color();
            delay(animate_led_delay_between_animations());
        break;
        case LED_STATE_SPELL:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_SPELL");
#endif
            animate_led_spell_word(animate_led_delay_in_animations());
            delay(animate_led_delay_between_animations());
        break;
        case LED_STATE_FADE_IN_AND_OUT:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_FADE");
#endif
            animate_led_fade_in_fade_out();
        break;
        case LED_STATE_TWINKLE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_TWINKLE");
#endif
            animate_led_twinkle(NUM_LEDS - 100, animate_led_delay_in_animations(), false);
            delay(animate_led_delay_between_animations());
        break;
        case LED_STATE_SPARKLE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_SPARKLE");
#endif
            animate_led_sparkle(animate_led_delay_in_animations());
        break;
        case LED_STATE_RUNNING_LIGHTS:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_RUNNING_LIGHTS");
#endif
            g_state_short_circuit_flag = true;
            animate_led_running_lights();
        break;
        case LED_STATE_RAINBOW_CYCLE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_RAINBOW_CYCLE");
#endif
            g_state_short_circuit_flag = true;
            animate_led_rainbow_cycle(animate_led_delay_in_animations());
        break;
        case LED_STATE_THEATER_CHASE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_THEATER_CHASE");
#endif
            animate_led_theater_chase(animate_led_delay_in_animations());
        break;
        case LED_STATE_THEATER_CHASE_RAINBOW:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_RAINBOW");
#endif
            g_state_short_circuit_flag = true;
            animate_led_theater_chase_rainbow(animate_led_delay_in_animations());
        break;
        case LED_STATE_METEOR: 
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_METEOR");
#endif
            animate_led_meteor_rain(20, 64, true, 5); // arbitrary selection made here
        break;
        case LED_STATE_STROBE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_STROBE");
#endif
            animate_led_strobe(10, animate_led_delay_in_animations(), animate_led_delay_in_animations() / 2);
        break;
        case LED_STATE_CYCLONE_BOUNCE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_CYCLONE_BOUNCE");
#endif
            uint16_t eye_size = 4;
            animate_led_cyclone_bounce(eye_size, 0, 0);
        break;
        
        default:
        break;
        // unused states below
        /*
        case LED_STATE_FIRE:
        break;
        case LED_STATE_BOUNCING_BALLS:
            animate_led_bouncing_balls(10);
        break;
        case LED_STATE_BOUNCING_BALLS_RANDOM:
        break;
        case LED_STATE_TWINKLE_RANDOM:
            animate_led_twinkle_random(100, 10, true);
        break;
        case LED_STATE_KITT:
            animate_led_new_kitt(20, 1, 1);
        break;
        */
        
    }
    
}


void master_led_state_change(void)
{
    for (int i = 0; i < 5; i++)
    {
        animate_led_set_all_pixels(0,0,0);
        delay(250);
        animate_led_set_all_pixels(0,255,0);
        delay(250);
    }
}


void master_led_color_state_change(void)
{
    for (int i = 0; i < 5; i++)
    {
        animate_led_set_all_pixels(0,0,0);
        delay(250);
        animate_led_set_all_pixels(255,0,0);
        delay(250);
    }
}


void handle_count_and_color(void)
{
    animate_led_increment_iterations();
    if (MASTER_STATE_DEMO == g_master_led_state)
    {
        color_led_randomize(); // randomize the colors for the demo LED state
        if ((!(animate_led_iterations() % 10)) || g_state_short_circuit_flag) \
        {
            g_state_short_circuit_flag = false;
            //if(LED_STATE_TWINKLE == g_led_state) twinkle_toggle ^=1;
            animate_led_state_randomize();
        }
    }
    if ((MASTER_COLOR_DEMO == g_master_color_state) || (LED_STATE_SPELL == animate_led_state())) color_led_randomize();
    //else animate_led_set_all_pixels(0, 0, 0); // fixed color, clear pixels before next cycle
}


void isr_state_change(void)
{
    if ((millis() - isr_times[ISR_STATE]) > debounce_delay)
    {
        isr_times[ISR_STATE] = millis();
        animate_led_set_interrupt_flag(ISR_STATE);
    }
    else return;
//    if (g_toggle ^= 1) digitalWrite(LED_BUILTIN, HIGH);
//    else digitalWrite(LED_BUILTIN, LOW);
#if defined(SERIAL_DEBUG)
    Serial.println("**ISR STATE**");
#endif
    // if in demo mode then state will be automatically selected.  
    // if in demo and button pressed then switch to fixed mode. 
    // if in fixed mode and button pressed then simply adjust the state.
    // one full cycle of states will automatically switch back to demo state
    if (MASTER_STATE_DEMO == g_master_led_state) 
    {
        animate_led_reset_state();
        g_master_led_state_change_flag = false;
        g_master_led_state = MASTER_STATE_FIXED;
    }
    else if (animate_led_adjust_state())
    {
        g_master_led_state_change_flag = true;
        g_master_led_state = MASTER_STATE_DEMO;
    }
}


void isr_color_change(void)
{
    if ((millis() - isr_times[ISR_COLOR]) > debounce_delay)
    {
        isr_times[ISR_COLOR] = millis();
        animate_led_set_interrupt_flag(ISR_COLOR);
    }
    else return;
//    if (g_toggle ^= 1) digitalWrite(LED_BUILTIN, HIGH);
//    else digitalWrite(LED_BUILTIN, LOW);    
#if defined(SERIAL_DEBUG)
    Serial.println("**ISR COLOR**");
#endif
    // if in demo mode then color will be automatically selected.  
    // if in demo and button pressed then switch to fixed mode. 
    // if in fixed mode and button pressed then simply adjust the color.
    // one full cycle of colors will automatically switch back to demo colors
    if (MASTER_COLOR_DEMO == g_master_color_state) 
    {
        color_led_reset_color();
        animate_led_reset_iterations();
        g_master_color_state_change_flag = false;
        g_master_color_state = MASTER_COLOR_FIXED;
    }
    else if (color_led_adjust_color())
    {
        g_master_color_state_change_flag = true;
        g_master_color_state = MASTER_COLOR_DEMO;
        
    }
}

//uint8_t g_toggle = 1;
void isr_speed_change(void)
{
    if ((millis() - isr_times[ISR_SPEED]) > debounce_delay)
    {
        isr_times[ISR_SPEED] = millis();
        animate_led_set_interrupt_flag(ISR_SPEED);
    }
    else return;
//    if (g_toggle ^= 1) digitalWrite(LED_BUILTIN, HIGH);
//    else digitalWrite(LED_BUILTIN, LOW);

#if defined(SERIAL_DEBUG)
    Serial.println("**ISR SPEED**");
#endif  
    // no demo mode for state, simply adjust the speed
    animate_led_reset_iterations(); // if speed adjusted then reset iterations also
    animate_led_adjust_speed();
}



void isr_pause(void)
{
    if ((millis() - isr_times[ISR_PAUSE]) > debounce_delay)
    {
        isr_times[ISR_PAUSE] = millis();
        animate_led_set_interrupt_flag(ISR_PAUSE);
    }
    else return;
//    if (g_toggle ^= 1) digitalWrite(LED_BUILTIN, HIGH);
//    else digitalWrite(LED_BUILTIN, LOW);
#if defined(SERIAL_DEBUG)
    Serial.println("PAUSE");
#endif
}
