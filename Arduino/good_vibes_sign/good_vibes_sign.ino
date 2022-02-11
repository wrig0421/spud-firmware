#include <color_led.h>
#include <animate_led.h>
#include <FastLED.h>

#define CYCLONE_BOUNCE_EYE_SIZE 4
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
uint32_t g_random_color_array[NUM_STRIPS];
void setup() 
{
    String msg = "";
#if defined(SERIAL_DEBUG)
    Serial.begin(115200);
#if defined(TOGETHER_SIGN)
    msg = "Together sign";
#elif defined(SCHUMACHER_SIGN)
    msg = "Schumacher sign";
#endif
    Serial.println(msg);
#endif
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

uint16_t delay_time = 5000;
int16_t animation_iterations = 0;
uint16_t g_strip_mask = 0;
led_state_e g_loop_led_state = LED_STATE_SPELL_SOLID_RANDOM_COLOR;
uint32_t random_color = 0;
// for good vibes sign... no random state changes simply advance all states and repeat

uint8_t random_true_or_false(void)
{
    return random(0, 2); // lower bound is inclusive, upper bound is exclusive
}

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
    Serial.println(g_loop_led_state, DEC);
    */
    random_color = (random(0, 255) << 16) | (random(0, 255) << 8) | (random(0, 255));
    switch(g_loop_led_state)
    {
        case LED_STATE_WHITE_COLOR:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_WHITE_COLOR");    
#endif
            animate_led_solid_custom_color((uint16_t)STRIP_BIT_1, COLOR_HEX_WHITE);
            animate_led_solid_custom_color((uint16_t)STRIP_BIT_2, COLOR_HEX_WHITE);
            delay(20000);
            g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
            animation_iterations = -1;
        break;
        case LED_STATE_FADE_IN_AND_OUT:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_FADE_IN_AND_OUT");
#endif
            animate_led_fade_in_fade_out((uint16_t)STRIP_BIT_ALL_SET, color_led_get_random_color());
            if (animation_iterations >= 5)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_FADE_IN_AND_OUT_MULTIPLE_COLORS:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_FADE_IN_AND_OUT_MULTIPLE_COLORS");
#endif
            // only works when more than one strip is defined
            for (int iii = 0; iii < animate_led_get_number_of_active_strips(STRIP_BIT_2 | STRIP_BIT_1); iii++)
            {
                g_random_color_array[iii] = color_led_get_random_color();
            }

            animate_led_fade_in_fade_out_multiple_colors(STRIP_BIT_1 | STRIP_BIT_2, g_random_color_array);
            if (animation_iterations >= 5)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_SOLID_COLOR:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_SOLID_COLOR");
#endif
            animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, color_led_get_random_color());
            if (animation_iterations >= 5)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
            delay(5000);
        break;
        case LED_STATE_MULTIPLE_SOLID_COLORS:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_MULTIPLE_SOLID_COLORS");
#endif       
            for (int iii = 0; iii < animate_led_get_number_of_active_strips(STRIP_BIT_2 | STRIP_BIT_1); iii++) g_random_color_array[iii] = color_led_get_random_color();
            animate_led_multiple_solid_custom_colors(STRIP_BIT_1 | STRIP_BIT_2, g_random_color_array);
            delay(5000);
            if (animation_iterations >= 5)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        /*
        case LED_STATE_STROBE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_STROBE");
#endif
            animate_led_strobe((uint16_t) STRIP_BIT_ALL_SET, color_led_cur_color_hex(), 1000, animate_led_delay_in_animations(), animate_led_delay_in_animations() / 2);
            if (animation_iterations >= 2)
            {
                g_loop_led_state = animate_led_state_randomize();
                animation_iterations = -1;
            }
        break;
        */
        case LED_STATE_SPELL_MULTIPLE_COLORS:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_SPELL_MULTIPLE_COLORS");
#endif
            // only works when more than one strip is defined
            for (int iii = 0; iii < animate_led_get_number_of_active_strips(STRIP_BIT_2 | STRIP_BIT_1); iii++)
            {
                g_random_color_array[iii] = color_led_get_random_color();
            }
            animate_led_spell_word_multiple_colors(STRIP_BIT_1 | STRIP_BIT_2, g_random_color_array, 0);
            if (animation_iterations >= 5)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_SPELL_SOLID_RANDOM_COLOR:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_SPELL_SOLID_RANDOM_COLOR");
#endif
            if (random_true_or_false()) animate_led_spell_and_solid_color(STRIP_BIT_1, STRIP_BIT_2, color_led_get_random_color(), 0);
            else animate_led_spell_and_solid_color(STRIP_BIT_2, STRIP_BIT_1, color_led_get_random_color(), 0);
            if (animation_iterations >= 5)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_SPELL_SPARKLE_FILL:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_SPELL_SPARKLE_FILL");
#endif
            if (random_true_or_false()) animate_led_spell_and_sparkle(STRIP_BIT_2, STRIP_BIT_1, color_led_get_random_color(), true, 0);
            else animate_led_spell_and_sparkle(STRIP_BIT_1, STRIP_BIT_2, color_led_get_random_color(), true, 0);
            if (animation_iterations >= 5)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_SPELL_SPARKLE_NO_FILL:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_SPELL_SPARKLE_NO_FILL");
#endif
            if (random_true_or_false()) animate_led_spell_and_sparkle(STRIP_BIT_2, STRIP_BIT_1, color_led_get_random_color(), true, 0);
            else animate_led_spell_and_sparkle(STRIP_BIT_1, STRIP_BIT_2, color_led_get_random_color(), true, 0);
            if (animation_iterations >= 5)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_SPELL:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_SPELL");
#endif
            animate_led_only_spell_word(STRIP_BIT_1 | STRIP_BIT_2, color_led_get_random_color(), 0);
            if (animation_iterations >= 5)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        /*
        case LED_STATE_CYCLONE_BOUNCE:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_CYCLONE_BOUNCE");
#endif
            g_strip_mask = (uint16_t) STRIP_BIT_ALL_SET;
            animate_led_cyclone_bounce(g_strip_mask, color_led_cur_color_hex(), CYCLONE_BOUNCE_E, 0, 0);
            if (animation_iterations >= 4)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        */
        case LED_STATE_SPARKLE_NO_FILL:
            // need to force all colors off before transitioning to this state
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_SPARKLE_NO_FILL");
#endif
            animate_led_turn_all_pixels_off();
            animate_led_sparkle_only_random_color(STRIP_BIT_ALL_SET, false, random(0, 50));
            if (animation_iterations >= 2)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_SPARKLE_FILL:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_SPARKLE_FILL");
#endif
            animate_led_sparkle_only_random_color(STRIP_BIT_ALL_SET, true, random(0, 50));
            if (animation_iterations >= 2)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
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
            Serial.println("LED_STATE_RAINBOW_CYCLE");
#endif
            animate_led_rainbow_cycle(STRIP_BIT_ALL_SET, 0);
            if (animation_iterations >= 2)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_RAINBOW_CYCLE_TWO_TONE:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_RAINBOW_CYCLE_TWO_TONE");
#endif
            animate_led_solid_custom_color(STRIP_BIT_2, color_led_get_random_color());
            animate_led_rainbow_cycle(STRIP_BIT_1, 0);
            if (animation_iterations >= 2)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_THEATER_CHASE:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_THEATER_CHASE");
#endif
            animate_led_theater_chase(STRIP_BIT_ALL_SET, color_led_get_random_color(), animate_led_delay_in_animations());
            if (animation_iterations >= 10)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_THEATER_CHASE_MULTIPLE_COLORS:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_THEATER_CHASE_MULTIPLE_COLORS");
#endif
            animate_led_theater_chase_multiple_colors(STRIP_BIT_1 | STRIP_BIT_2, g_random_color_array, 0);
            g_loop_led_state = LED_STATE_TWINKLE;
            if (animation_iterations >= 2)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_THEATER_CHASE_RAINBOW:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_THEATER_CHASE_RAINBOW");
#endif
            animate_led_theater_chase_rainbow(STRIP_BIT_ALL_SET, animate_led_delay_in_animations());
            g_loop_led_state = LED_STATE_TWINKLE;
            if (animation_iterations >= 2)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_TWINKLE_MULTIPLE_COLORS:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_TWINKLE_MULTIPLE_COLORS");
#endif
            for (int iii = 0; iii < animate_led_get_number_of_active_strips(STRIP_BIT_2 | STRIP_BIT_1); iii++)
            {
                g_random_color_array[iii] = color_led_get_random_color();
            }
            animate_led_twinkle_multiple_colors(STRIP_BIT_ALL_SET, g_random_color_array, NUM_LEDS - 160, animate_led_delay_in_animations(), false);
            if (animation_iterations >= 3)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        case LED_STATE_TWINKLE:
#if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_TWINKLE");
#endif
            animate_led_turn_all_pixels_off();
            animate_led_twinkle(STRIP_BIT_ALL_SET, color_led_get_random_color(), NUM_LEDS - 160, animate_led_delay_in_animations(), false);
            if (animation_iterations >= 3)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;  
        /*  
        case LED_STATE_METEOR: 
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_METEOR");
#endif
            animate_led_meteor_rain(STRIP_BIT_ALL_SET, color_led_cur_color_hex(), 20, 64, true, 5); // arbitrary selection made here
            if (animation_iterations >= 3)
            {
                g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
                animation_iterations = -1;
            }
        break;
        */
#if defined(SRW_DEBUG)
    #if defined(SERIAL_DEBUG)
            Serial.println("LED_STATE_SRW_DEBUG");
    #endif
        case LED_STATE_SRW_DEBUG:
            animate_led_solid_custom_color((uint16_t)STRIP_BIT_1, color_led_get_random_color());
            delay(4000);
        break;
#endif
        default:
#if defined(SERIAL_DEBUG)
            Serial.println("STATE_DEFAULT**************************************T");
#endif        
        break;
    }
#if defined(SERIAL_DEBUG)
    Serial.println("Animation_iteration: ");
    Serial.print(animation_iterations); 
#endif

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


//void isr_state_change(void)
//{
//    if ((millis() - isr_times[ISR_STATE]) > debounce_delay)
//    {
//        isr_times[ISR_STATE] = millis();
//        animate_led_set_interrupt_flag(ISR_STATE);
//    }
//    else return;
//#if defined(SERIAL_DEBUG)
//    Serial.println("**ISR STATE**");
//#endif
//    // if in demo mode then state will be automatically selected.  
//    // if in demo and button pressed then switch to fixed mode. 
//    // if in fixed mode and button pressed then simply adjust the state.
//    // one full cycle of states will automatically switch back to demo state
//    if (MASTER_STATE_DEMO == g_master_led_state) 
//    {
//        animate_led_reset_state();
//        g_master_led_state_change_flag = false;
//        g_master_led_state = MASTER_STATE_FIXED;
//    }
//    else if (animate_led_adjust_state())
//    {
//        g_master_led_state_change_flag = true;
//        g_master_led_state = MASTER_STATE_DEMO;
//    }
//}
//
//
//void isr_color_change(void)
//{
//    if ((millis() - isr_times[ISR_COLOR]) > debounce_delay)
//    {
//        isr_times[ISR_COLOR] = millis();
//        animate_led_set_interrupt_flag(ISR_COLOR);
//    }
//    else return;
//#if defined(SERIAL_DEBUG)
//    Serial.println("**ISR COLOR**");
//#endif
//    // if in demo mode then color will be automatically selected.  
//    // if in demo and button pressed then switch to fixed mode. 
//    // if in fixed mode and button pressed then simply adjust the color.
//    // one full cycle of colors will automatically switch back to demo colors
//    if (MASTER_COLOR_DEMO == g_master_color_state) 
//    {
//        color_led_reset_color();
//        animate_led_reset_iterations();
//        g_master_color_state_change_flag = false;
//        g_master_color_state = MASTER_COLOR_FIXED;
//    }
//    else if (color_led_adjust_color())
//    {
//        g_master_color_state_change_flag = true;
//        g_master_color_state = MASTER_COLOR_DEMO;
//        
//    }
//}
//
//
//void isr_speed_change(void)
//{
//    if ((millis() - isr_times[ISR_SPEED]) > debounce_delay)
//    {
//        isr_times[ISR_SPEED] = millis();
//        animate_led_set_interrupt_flag(ISR_SPEED);
//    }
//    else return;
//#if defined(SERIAL_DEBUG)
//    Serial.println("**ISR SPEED**");
//#endif  
//    // no demo mode for state, simply adjust the speed
//    animate_led_reset_iterations(); // if speed adjusted then reset iterations also
//    animate_led_adjust_speed();
//}
//
//
//void isr_pause(void)
//{
//    if ((millis() - isr_times[ISR_PAUSE]) > debounce_delay)
//    {
//        isr_times[ISR_PAUSE] = millis();
//        animate_led_set_interrupt_flag(ISR_PAUSE);
//    }
//    else return;
//#if defined(SERIAL_DEBUG)
//    Serial.println("PAUSE");
//#endif
//}
