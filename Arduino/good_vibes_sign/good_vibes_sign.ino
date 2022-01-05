#include <animate_led.h>
#include <color_led.h>
#include <FastLED.h>

// static definitions
//#define SERIAL_DEBUG // define to print debug messages

//#if !defined(TOGETHER_SIGN) && !defined(SCHUMACHER_SIGN)
//#pragma error("no sign defined");
//#endif


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
#endif 
} interrupt_button_e;


// local function prototypes
void handle_count_and_color(void);
void isr_state_change(void);
void isr_color_change(void);
void isr_speed_change(void);
void isr_pause(void);


// global variables
master_led_state_e g_master_led_state = MASTER_STATE_DEMO; // start solid white for reception
master_color_state_e g_master_color_state = MASTER_COLOR_DEMO;
unsigned long isr_times[NUM_ISR] = {0};
unsigned long debounce_delay = 2000; // ms
bool g_state_flag = false;
bool g_master_color_state_change_flag = false;
bool g_master_led_state_change_flag = false;
bool g_state_short_circuit_flag = false;
bool g_start_demo_flag = false;

void setup() 
{
    String msg = "";
#if defined(SERIAL_DEBUG)
    Serial.begin(9600);
#if defined(TOGETHER_SIGN)
    msg = "Together sign";
#elif defined(SCHUMACHER_SIGN)
    msg = "Schumacher sign";
#endif
    Serial.println(msg);
#endif
    delay(2000);
    color_led_init();
    animate_led_init();

    pinMode(A1, INPUT);
    randomSeed(analogRead(A1));
    //pinMode((byte)INT_BTN_SPEED, INPUT);
    //pinMode((byte)INT_BTN_STATE, INPUT);
    //pinMode((byte)INT_BTN_COLOR, INPUT);
    //pinMode((byte)INT_BTN_PAUSE, INPUT); 
    //attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_SPEED), isr_speed_change, RISING); 
    //attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_STATE), isr_state_change, RISING); 
    //attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_COLOR), isr_color_change, RISING);  
    //attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_PAUSE), isr_pause, RISING); 
}

uint16_t delay_time = 2000;
int val = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
uint16_t eye_size = 4;
int16_t animation_iterations = 0;
led_state_e g_loop_led_state = LED_STATE_SPELL_SOLID_WHITE_COLOR;

// for good vibes sign... no random state changes simply advance all states and repeat

void loop() 
{
    /*
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
    */
    Serial.println(g_loop_led_state, DEC);
    switch(g_loop_led_state)
    {
        /*
        case LED_STATE_WHITE_COLOR:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_SOLID_WHITE_COLOR");    
#endif
            // the color change doesn't matter for solid white.. 
            animate_led_set_solid_white_color();
            delay(animate_led_delay_between_animations());
        break;
        */ 
        case LED_STATE_TWO_TONE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_TWO_TONE");
#endif
            animate_led_two_tone(COLOR_HEX_RED, COLOR_HEX_WHITE);
            delay(delay_time);
            animate_led_two_tone(COLOR_HEX_WHITE, COLOR_HEX_RED);
            delay(delay_time);
            animate_led_two_tone(COLOR_HEX_BLUE, COLOR_HEX_WHITE);
            delay(delay_time);
            animate_led_two_tone(COLOR_HEX_WHITE, COLOR_HEX_BLUE);
            delay(delay_time);
            animate_led_two_tone(COLOR_HEX_PURPLE, COLOR_HEX_WHITE);
            delay(delay_time);
            animate_led_two_tone(COLOR_HEX_WHITE, COLOR_HEX_PURPLE);
            delay(delay_time);
            animate_led_two_tone(COLOR_HEX_PURPLE, COLOR_HEX_YELLOW);
            delay(delay_time);
            animate_led_two_tone(COLOR_HEX_YELLOW, COLOR_HEX_PURPLE);
            delay(delay_time);
            animate_led_two_tone(COLOR_HEX_RED, COLOR_HEX_BLUE);
            delay(delay_time);
            animate_led_two_tone(COLOR_HEX_BLUE, COLOR_HEX_RED);
            delay(delay_time);
            g_loop_led_state = LED_STATE_FADE_IN_AND_OUT;
            animation_iterations = -1;    
        break;
        case LED_STATE_FADE_IN_AND_OUT:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_FADE");
#endif
            animate_led_fade_in_fade_out(ALL_STRIPS);
            if (animation_iterations >= 4)
            {
                g_loop_led_state = LED_STATE_STROBE;
                animation_iterations = -1;
            }
           
        break;
        /*
        case LED_STATE_SOLID_COLOR:
            if (MASTER_STATE_FIXED == g_master_led_state)
            {
#if defined(SERIAL_DEBUG)
                Serial.println("STATE_SOLID_COLOR");
#endif
                animate_led_solid_color();
                delay(animate_led_delay_between_animations());
            }
        break;
        */
        case LED_STATE_STROBE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_STROBE");
#endif
            animate_led_strobe(ALL_STRIPS, 10, animate_led_delay_in_animations(), animate_led_delay_in_animations() / 2);
            if (animation_iterations >= 10)
            {
                g_loop_led_state = LED_STATE_SPELL;
                animation_iterations = -1;
            }
        break;
        
        case LED_STATE_SPELL:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_SPELL");
#endif
            animate_led_spell_word(STRIP_NUM_2, 0);
            if (animation_iterations >= 10)
            {
                g_loop_led_state = LED_STATE_CYCLONE_BOUNCE;
                animation_iterations = -1;
            }
            //animate_led_solid_custom_color(STRIP_NUM_1, 255, 255, 255);
            //animate_led_solid_custom_color(STRIP_NUM_1, 255, 255, 255);
            //animate_led_spell_word(STRIP_NUM_2, animate_led_delay_in_animations());
            //delay(animate_led_delay_between_animations());
            
        break;

        case LED_STATE_SPELL_SOLID_RANDOM_COLOR:
            animate_led_solid_custom_color(STRIP_NUM_1, random(0, 255), random(0, 255), random(0, 255));
            animate_led_spell_word(STRIP_NUM_2, 0);
            if (animation_iterations >= 10)
            {
                g_loop_led_state = LED_STATE_CYCLONE_BOUNCE;
                animation_iterations = -1;
            }
        break;
        
        case LED_STATE_SPELL_SOLID_WHITE_COLOR:
            animate_led_solid_custom_color(STRIP_NUM_1, 255, 255, 255);
            animate_led_spell_word(STRIP_NUM_2, 0);
            if (animation_iterations >= 10)
            {
                g_loop_led_state = LED_STATE_CYCLONE_BOUNCE;
                animation_iterations = -1;
            }
        break;
        
        case LED_STATE_SPELL_SPARKLE_FILL:
            animate_led_spell_and_sparkle(STRIP_NUM_2, STRIP_NUM_1, true, 0);
            color_led_randomize();
            animate_led_spell_and_sparkle(STRIP_NUM_2, STRIP_NUM_1, true, 0);
            color_led_randomize();
            animate_led_spell_and_sparkle(STRIP_NUM_1, STRIP_NUM_2, true, 0);
            color_led_randomize();
            animate_led_spell_and_sparkle(STRIP_NUM_1, STRIP_NUM_2, true, 0);
            if (animation_iterations >= 2)
            {
                g_loop_led_state = LED_STATE_CYCLONE_BOUNCE;
                animation_iterations = -1;
            }
        break;

        case LED_STATE_SPELL_SPARKLE_NO_FILL:
            animate_led_spell_and_sparkle(STRIP_NUM_2, STRIP_NUM_1, false, 0);
            color_led_randomize();
            animate_led_spell_and_sparkle(STRIP_NUM_2, STRIP_NUM_1, false, 0);
            color_led_randomize();
            animate_led_spell_and_sparkle(STRIP_NUM_1, STRIP_NUM_2, false, 0);
            color_led_randomize();
            animate_led_spell_and_sparkle(STRIP_NUM_1, STRIP_NUM_2, false, 0);
            if (animation_iterations >= 2)
            {
                g_loop_led_state = LED_STATE_CYCLONE_BOUNCE;
                animation_iterations = -1;
            }
        break;
        
        
        case LED_STATE_CYCLONE_BOUNCE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_CYCLONE_BOUNCE");
#endif
            animate_led_cyclone_bounce(ALL_STRIPS, eye_size, 0, 0);
            if (animation_iterations >= 4)
            {
                g_loop_led_state = LED_STATE_SPARKLE_FILL;
                animation_iterations = -1;
            }
        break;

        case LED_STATE_SPARKLE_NO_FILL:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_SPARKLE");
#endif
            Serial.println("TEST");
            animate_led_sparkle_random_color(ALL_STRIPS, false, 100);
        break;

        case LED_STATE_SPARKLE_FILL:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_SPARKLE");
#endif
            Serial.println("TEST");
            animate_led_sparkle_random_color(ALL_STRIPS, true, 0);
        break;
        /*
        case LED_STATE_RUNNING_LIGHTS:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_RUNNING_LIGHTS");
#endif
            g_state_short_circuit_flag = true;
            animate_led_running_lights();
            if (animation_iterations >= 10)
            {
                g_loop_led_state = LED_STATE_RAINBOW_CYCLE;
                animation_iterations = -1;
            }
        break;
        */
        case LED_STATE_RAINBOW_CYCLE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_RAINBOW_CYCLE");
#endif
            //g_state_short_circuit_flag = true;
            animate_led_solid_custom_color(STRIP_NUM_2, 255, 0, 0);
            animate_led_rainbow_cycle(STRIP_NUM_1, 0);//animate_led_delay_in_animations());
            g_loop_led_state = LED_STATE_THEATER_CHASE;
            /*
            if (animation_iterations >= 10)
            {
                g_loop_led_state = LED_STATE_THEATER_CHASE;
                animation_iterations = -1;
            }
            */
        break;

        case LED_STATE_THEATER_CHASE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_THEATER_CHASE");
#endif
            animate_led_theater_chase(ALL_STRIPS, animate_led_delay_in_animations());
            if (animation_iterations >= 10)
            {
                g_loop_led_state = LED_STATE_THEATER_CHASE_RAINBOW;
                animation_iterations = -1;
            }
        break;
        
        case LED_STATE_THEATER_CHASE_RAINBOW:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_RAINBOW");
#endif
            g_state_short_circuit_flag = true;
            animate_led_theater_chase_rainbow(ALL_STRIPS, animate_led_delay_in_animations());
            g_loop_led_state = LED_STATE_TWINKLE;
            /*
            if (animation_iterations >= 10)
            {
                g_loop_led_state = LED_STATE_TWINKLE;
                animation_iterations = -1;
            }
            */
        break;
        
        case LED_STATE_TWINKLE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_TWINKLE");
#endif
            animate_led_twinkle(ALL_STRIPS, NUM_LEDS - 100, animate_led_delay_in_animations(), false);
            delay(animate_led_delay_between_animations());
            if (animation_iterations >= 4)
            {
                g_loop_led_state = LED_STATE_METEOR;
                animation_iterations = -1;
            }
        break;    
          
        case LED_STATE_METEOR: 
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_METEOR");
#endif
            animate_led_meteor_rain(ALL_STRIPS, 20, 64, true, 5); // arbitrary selection made here
            if (animation_iterations >= 4)
            {
                g_loop_led_state = LED_STATE_TWO_TONE;
                animation_iterations = -1;
            }
        break;
        
        default:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_DEFAULT");
#endif        
        break;
    }
    color_led_randomize();
    animation_iterations++;
}


void master_led_state_change(void)
{
    for (int i = 0; i < 5; i++)
    {
        animate_led_set_all_pixels(ALL_STRIPS,0,0,0);
        delay(250);
        animate_led_set_all_pixels(ALL_STRIPS,0,255,0);
        delay(250);
    }
}


void master_led_color_state_change(void)
{
    for (int i = 0; i < 5; i++)
    {
        animate_led_set_all_pixels(ALL_STRIPS, 0,0,0);
        delay(250);
        animate_led_set_all_pixels(ALL_STRIPS, 255,0,0);
        delay(250);
    }
}


void handle_count_and_color(void)
{
    uint8_t modulus = 10;
    if (LED_STATE_CYCLONE_BOUNCE == animate_led_state())
    {
        modulus = 5;
    }
    else
    {
        modulus = 10;
    }
    animate_led_increment_iterations();
    if (MASTER_STATE_DEMO == g_master_led_state)
    {
        color_led_randomize(); // randomize the colors for the demo LED state
        if ((!(animate_led_iterations() % modulus)) || g_state_short_circuit_flag) \
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


void isr_speed_change(void)
{
    if ((millis() - isr_times[ISR_SPEED]) > debounce_delay)
    {
        isr_times[ISR_SPEED] = millis();
        animate_led_set_interrupt_flag(ISR_SPEED);
    }
    else return;
#if defined(SERIAL_DEBUG)
    Serial.println("**ISR SPEED**");
#endif  
    // no demo mode for state, simply adjust the speed
    animate_led_reset_iterations(); // if speed adjusted then reset iterations also
    animate_led_adjust_speed();
}


/*
void isr_pause(void)
{
    if ((millis() - isr_times[ISR_PAUSE]) > debounce_delay)
    {
        isr_times[ISR_PAUSE] = millis();
        animate_led_set_interrupt_flag(ISR_PAUSE);
    }
    else return;
#if defined(SERIAL_DEBUG)
    Serial.println("PAUSE");
#endif
}
*/
