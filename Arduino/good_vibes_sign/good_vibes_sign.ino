#include <color_led.h>
#include <animate_led.h>
#include <FastLED.h>

// static definitions
//#define SERIAL_DEBUG // define to print debug messages
//#define ENABLE_EXT_INTERRUPTS

// typedefs, structs, enums
typedef enum
{
    MASTER_LED_STATE_DEMO,
    MASTER_LED_STATE_FIXED
} master_led_state_e;


typedef enum
{
    MASTER_COLOR_STATE_DEMO,
    MASTER_COLOR_STATE_FIXED
} master_color_state_e;


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
    ANIMATION_LOOP_ITERATIONS_10
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


// local function prototypes
void handle_count_color_delay(void);
void isr_state_change(void);
void isr_color_change(void);
void isr_speed_change(void);
void isr_pause(void);

// global variables
master_led_state_e g_master_led_state = MASTER_LED_STATE_DEMO; 
master_color_state_e g_master_color_state = MASTER_COLOR_STATE_DEMO;
uint8_t g_animation_iterations = 0;
led_state_e g_loop_led_state = LED_STATE_SPELL_SOLID_RANDOM_COLOR;

unsigned long g_isr_times[NUM_ISR] = {0};
unsigned long g_debounce_delay = 2000; // ms
bool g_master_color_state_change_flag = false;
bool g_master_led_state_change_flag = false;
uint32_t g_random_color_array[NUM_STRIPS];


#if defined(ENABLE_EXT_INTERRUPTS)
typedef enum
{
    // No RF control on Good Vibes Sign. Ext switches on back of sign
    INT_BTN_PAUSE = 19, 
    INT_BTN_STATE = 18,
    INT_BTN_SPEED = 20,
    INT_BTN_COLOR = 21,
} ext_interrupt_pin_e;


void ext_interrupt_init(void)
{
    pinMode((byte)INT_BTN_SPEED, INPUT);
    pinMode((byte)INT_BTN_STATE, INPUT);
    pinMode((byte)INT_BTN_COLOR, INPUT);
    pinMode((byte)INT_BTN_PAUSE, INPUT); 
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_SPEED), isr_speed_change, RISING); 
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_STATE), isr_state_change, RISING); 
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_COLOR), isr_color_change, RISING);  
    attachInterrupt(digitalPinToInterrupt((byte)INT_BTN_PAUSE), isr_pause, RISING); 
}
#endif


uint8_t random_true_or_false(void)
{
    return random(0, 2); // lower bound is inclusive, upper bound is exclusive
}


void dbg_serial_print(void)
{
    if (MASTER_LED_STATE_FIXED == g_master_led_state) Serial.println("MASTER LED STATE FIXED");
    else Serial.println("MASTER LED STATE DEMO");
    if (MASTER_COLOR_STATE_FIXED == g_master_color_state) Serial.println("MASTER LED COLOR STATE FIXED");
    else Serial.println("MASTER LED COLOR DEMO");
    Serial.println("Animation_iteration: ");
    Serial.println(animate_led_iterations(), DEC); // print iteration count
    switch (g_loop_led_state)
    {
        case LED_STATE_WHITE_COLOR:
            Serial.println("LED_STATE_WHITE_COLOR");    
        break;
        case LED_STATE_FADE_IN_AND_OUT:
            Serial.println("LED_STATE_FADE_IN_AND_OUT");    
        break;
        case LED_STATE_SOLID_COLOR:
            Serial.println("LED_STATE_SOLID_COLOR");
        break;
        case LED_STATE_SPELL_MULTIPLE_COLORS:
            Serial.println("LED_STATE_SPELL_MULTIPLE_COLORS");
        break;
        case LED_STATE_SPELL_SOLID_RANDOM_COLOR:
            Serial.println("LED_STATE_SPELL_SOLID_RANDOM_COLOR");
        break;
        case LED_STATE_SPELL_SPARKLE_FILL:
            Serial.println("LED_STATE_SPELL_SPARKLE_FILL");
        break;
        case LED_STATE_SPELL_SPARKLE_NO_FILL:
            Serial.println("LED_STATE_SPELL_SPARKLE_NO_FILL");
        break;
        case LED_STATE_SPELL:
            Serial.println("LED_STATE_SPELL");
        break;
        case LED_STATE_SPARKLE_NO_FILL:
            Serial.println("LED_STATE_SPARKLE_NO_FILL");
        break;
        case LED_STATE_SPARKLE_FILL:
            Serial.println("LED_STATE_SPARKLE_FILL");
        break;
        case LED_STATE_RAINBOW_CYCLE:
            Serial.println("LED_STATE_RAINBOW_CYCLE");
        break;
        case LED_STATE_RAINBOW_CYCLE_TWO_TONE:
            Serial.println("LED_STATE_RAINBOW_CYCLE_TWO_TONE");
        break;
        case LED_STATE_THEATER_CHASE:
            Serial.println("LED_STATE_THEATER_CHASE");
        break;
        case LED_STATE_THEATER_CHASE_MULTIPLE_COLORS:
            Serial.println("LED_STATE_THEATER_CHASE_MULTIPLE_COLORS");
        break;
        case LED_STATE_THEATER_CHASE_RAINBOW:
            Serial.println("LED_STATE_THEATER_CHASE_RAINBOW");
        break;
        case LED_STATE_MULTIPLE_COLORS:
            Serial.println("LED_STATE_MULTIPLE_SOLID_COLORS");
        break;
        case LED_STATE_FADE_IN_AND_OUT_MULTIPLE_COLORS:
            Serial.println("LED_STATE_FADE_IN_AND_OUT_MULTIPLE_COLORS");
        break;
        case LED_STATE_TWINKLE:
            Serial.println("LED_STATE_TWINKLE");
        break;
        default:
            Serial.println("LED_STATE_FDEFAULT **BAD**");
        break;
    }
}


void handle_count_color_delay(const animation_loop_iterations_e max_iterations, const animation_delay_ms_e animation_delay_ms)
{
    if (ANIMATION_DELAY_MS_0 != animation_delay_ms) delay(animation_delay_ms);
    g_animation_iterations++;
    if (MASTER_LED_STATE_DEMO == g_master_led_state)
    {
        if (max_iterations == g_animation_iterations)
        {
            g_loop_led_state = animate_led_state_randomize(g_loop_led_state);
            g_animation_iterations = 0;
        }
    }
}


void setup(void) 
{
    String msg = "";
#if defined(SERIAL_DEBUG)
    Serial.begin(115200);
    Serial.println("Good Vibes Sign");
    Serial.println("Author: Spencer Wright");
#endif
    pinMode(A1, INPUT);
    randomSeed(analogRead(A1)); // Nothing connected to A1.  Get random noise on input for seed
#if defined(ENABLE_EXT_INTERRUPTS)
    ext_interrupt_init();
#endif
    color_led_init();
    animate_led_init();
}


void loop(void) 
{
#if defined(SERIAL_DEBUG)
    dbg_serial_print();
#endif
    /*
    
    if (g_master_led_state_change_flag)
    {
        animate_led_reset_iterations();
        master_led_state_change();
        g_master_led_state_change_flag = false;
    }
    */
    switch(g_loop_led_state)
    {
        case LED_STATE_WHITE_COLOR:
            animate_led_solid_custom_color((uint16_t)STRIP_BIT_1, COLOR_HEX_WHITE);
            animate_led_solid_custom_color((uint16_t)STRIP_BIT_2, COLOR_HEX_WHITE);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_1, ANIMATION_DELAY_MS_20000);
        break;
        case LED_STATE_SOLID_COLOR:
            animate_led_solid_custom_color((uint16_t)STRIP_BIT_ALL_SET, color_led_get_random_color());
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_5000);
        break;
        case LED_STATE_SPARKLE_NO_FILL:
            // need to force all colors off before transitioning to this state
            animate_led_turn_all_pixels_off();
            animate_led_sparkle_only_random_color(STRIP_BIT_ALL_SET, false, random(0, 50));
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_2, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_SPARKLE_FILL:
            animate_led_sparkle_only_random_color(STRIP_BIT_ALL_SET, true, random(0, 50));
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_2, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_RAINBOW_CYCLE:
            animate_led_rainbow_cycle(STRIP_BIT_ALL_SET, 0);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_2, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_THEATER_CHASE:
            animate_led_theater_chase(STRIP_BIT_ALL_SET, color_led_get_random_color(), animate_led_delay_in_animations());
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_10, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_THEATER_CHASE_RAINBOW:
            animate_led_theater_chase_rainbow(STRIP_BIT_ALL_SET, animate_led_delay_in_animations());
            g_loop_led_state = LED_STATE_TWINKLE;
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_2, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_FADE_IN_AND_OUT:
            animate_led_fade_in_fade_out((uint16_t)STRIP_BIT_ALL_SET, color_led_get_random_color());
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_TWINKLE:
            animate_led_turn_all_pixels_off();
            animate_led_twinkle(STRIP_BIT_ALL_SET, color_led_get_random_color(), NUM_LEDS - 160, animate_led_delay_in_animations(), false);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_3, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_SPELL:
            animate_led_only_spell_word(STRIP_BIT_1 | STRIP_BIT_2, color_led_get_random_color(), 0);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
        break;
#if defined(SRW_DEBUG)
        case LED_STATE_SRW_DEBUG:
            // a state strictlty for debugging new animations also there's no state change here...
            animate_led_solid_custom_color((uint16_t)STRIP_BIT_1, color_led_get_random_color());
        break;
#endif
#if defined(MULTIPLE_STRIPS)
        case LED_STATE_FADE_IN_AND_OUT_MULTIPLE_COLORS:
            // only works when more than one strip is defined
            for (int iii = 0; iii < animate_led_get_number_of_active_strips(STRIP_BIT_2 | STRIP_BIT_1); iii++)
            {
                g_random_color_array[iii] = color_led_get_random_color();
            }
            animate_led_fade_in_fade_out_multiple_colors(STRIP_BIT_1 | STRIP_BIT_2, g_random_color_array);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_MULTIPLE_COLORS:  
            for (int iii = 0; iii < animate_led_get_number_of_active_strips(STRIP_BIT_2 | STRIP_BIT_1); iii++) g_random_color_array[iii] = color_led_get_random_color();
            animate_led_multiple_solid_custom_colors(STRIP_BIT_1 | STRIP_BIT_2, g_random_color_array);
            delay(5000);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_RAINBOW_CYCLE_TWO_TONE:
            animate_led_solid_custom_color(STRIP_BIT_2, color_led_get_random_color());
            animate_led_rainbow_cycle(STRIP_BIT_1, 0);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_2, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_THEATER_CHASE_MULTIPLE_COLORS:
            animate_led_theater_chase_multiple_colors(STRIP_BIT_1 | STRIP_BIT_2, g_random_color_array, 0);
            g_loop_led_state = LED_STATE_TWINKLE;
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_2, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_TWINKLE_MULTIPLE_COLORS:
            for (int iii = 0; iii < animate_led_get_number_of_active_strips(STRIP_BIT_2 | STRIP_BIT_1); iii++)
            {
                g_random_color_array[iii] = color_led_get_random_color();
            }
            animate_led_twinkle_multiple_colors(STRIP_BIT_ALL_SET, g_random_color_array, NUM_LEDS - 160, animate_led_delay_in_animations(), false);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_3, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_SPELL_MULTIPLE_COLORS:
            // only works when more than one strip is defined
            for (int iii = 0; iii < animate_led_get_number_of_active_strips(STRIP_BIT_2 | STRIP_BIT_1); iii++)
            {
                g_random_color_array[iii] = color_led_get_random_color();
            }
            animate_led_spell_word_multiple_colors(STRIP_BIT_1 | STRIP_BIT_2, g_random_color_array, 0);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_SPELL_SOLID_RANDOM_COLOR:
            if (random_true_or_false()) animate_led_spell_and_solid_color(STRIP_BIT_1, STRIP_BIT_2, color_led_get_random_color(), 0);
            else animate_led_spell_and_solid_color(STRIP_BIT_2, STRIP_BIT_1, color_led_get_random_color(), 0);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_SPELL_SPARKLE_FILL:
            if (random_true_or_false()) animate_led_spell_and_sparkle(STRIP_BIT_2, STRIP_BIT_1, color_led_get_random_color(), true, 0);
            else animate_led_spell_and_sparkle(STRIP_BIT_1, STRIP_BIT_2, color_led_get_random_color(), true, 0);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
        break;
        case LED_STATE_SPELL_SPARKLE_NO_FILL:
            if (random_true_or_false()) animate_led_spell_and_sparkle(STRIP_BIT_2, STRIP_BIT_1, color_led_get_random_color(), true, 0);
            else animate_led_spell_and_sparkle(STRIP_BIT_1, STRIP_BIT_2, color_led_get_random_color(), true, 0);
            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_5, ANIMATION_DELAY_MS_0);
        break;
#endif
//        case LED_STATE_STROBE:
//#if defined(SERIAL_DEBUG)
//            Serial.println("STATE_STROBE");
//#endif
//            animate_led_strobe((uint16_t) STRIP_BIT_ALL_SET, color_led_cur_color_hex(), 1000, animate_led_delay_in_animations(), animate_led_delay_in_animations() / 2);
//            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_2, ANIMATION_DELAY_MS_0);
//        break;
//        case LED_STATE_METEOR: 
//#if defined(SERIAL_DEBUG)
//            Serial.println("STATE_METEOR");
//#endif
//            animate_led_meteor_rain(STRIP_BIT_ALL_SET, color_led_cur_color_hex(), 20, 64, true, 5); // arbitrary selection made here
//            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_3, ANIMATION_DELAY_MS_0);
//        break;
//        case LED_STATE_RUNNING_LIGHTS:
//#if defined(SERIAL_DEBUG)
//            Serial.println("STATE_RUNNING_LIGHTS");
//#endif
//            animate_led_running_lights();
//            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_10, ANIMATION_DELAY_MS_0);
//        break;
//        case LED_STATE_CYCLONE_BOUNCE:
//#if defined(SERIAL_DEBUG)
//            Serial.println("STATE_CYCLONE_BOUNCE");
//#endif
//            animate_led_cyclone_bounce(STRIP_BIT_ALL_SET, color_led_cur_color_hex(), CYCLONE_BOUNCE_E, 0, 0);
//            handle_count_color_delay(ANIMATION_LOOP_ITERATIONS_4, ANIMATION_DELAY_MS_0);
//        break;
        default:      
        break;
    }
    //color_led_randomize();
}


#if defined(ENABLE_EXT_INTERRUPTS)
void master_led_state_change(void)
{
    for (int i = 0; i < 5; i++)
    {
        animate_led_set_all_pixels(STRIP_BIT_ALL_SET, 0, 0, 0);
        delay(250);
        animate_led_set_all_pixels(STRIP_BIT_ALL_SET, 0, 255, 0);
        delay(250);
    }
}


void master_led_color_state_change(void)
{
    for (int i = 0; i < 5; i++)
    {
        animate_led_set_all_pixels(STRIP_BIT_ALL_SET, 0, 0, 0);
        delay(250);
        animate_led_set_all_pixels(STRIP_BIT_ALL_SET, 0, 0, 0);
        delay(250);
    }
}


void isr_state_change(void)
{
    if ((millis() - g_isr_times[ISR_STATE]) > g_debounce_delay)
    {
        g_isr_times[ISR_STATE] = millis();
        animate_led_set_interrupt_flag(ISR_STATE);
    }
    else return;
#if defined(SERIAL_DEBUG)
    Serial.println("**EXTERNAL INTERRUPT - ISR STATE**");
#endif
    // if in demo mode then state will be automatically selected.  
    // if in demo and button pressed then switch to fixed mode. 
    // if in fixed mode and button pressed then simply adjust the state.
    // one full cycle of states will automatically switch back to demo state
    if (MASTER_LED_STATE_DEMO == g_master_led_state) 
    {
        animate_led_reset_state();
        g_master_led_state_change_flag = false;
        g_master_led_state = MASTER_LED_STATE_FIXED;
    }
    else if (animate_led_adjust_state())
    {
        g_master_led_state_change_flag = true;
        g_master_led_state = MASTER_LED_STATE_DEMO;
    }
}


void isr_color_change(void)
{
    if ((millis() - g_isr_times[ISR_COLOR]) > g_debounce_delay)
    {
        g_isr_times[ISR_COLOR] = millis();
        animate_led_set_interrupt_flag(ISR_COLOR);
    }
    else return;
#if defined(SERIAL_DEBUG)
    Serial.println("**EXTERNAL INTERRUPT - ISR COLOR**");
#endif
    // if in demo mode then color will be automatically selected.  
    // if in demo and button pressed then switch to fixed mode. 
    // if in fixed mode and button pressed then simply adjust the color.
    // one full cycle of colors will automatically switch back to demo colors
    if (MASTER_COLOR_STATE_DEMO == g_master_color_state) 
    {
        color_led_reset_color();
        animate_led_reset_iterations();
        g_master_color_state_change_flag = false;
        g_master_color_state = MASTER_COLOR_STATE_FIXED;
    }
    else if (color_led_adjust_color())
    {
        g_master_color_state_change_flag = true;
        g_master_color_state = MASTER_COLOR_STATE_DEMO;
        
    }
}


void isr_speed_change(void)
{
    if ((millis() - g_isr_times[ISR_SPEED]) > g_debounce_delay)
    {
        g_isr_times[ISR_SPEED] = millis();
        animate_led_set_interrupt_flag(ISR_SPEED);
    }
    else return;
#if defined(SERIAL_DEBUG)
    Serial.println("**EXTERNAL INTERRUPT - ISR SPEED**");
#endif  
    // no demo mode for state, simply adjust the speed
    animate_led_reset_iterations(); // if speed adjusted then reset iterations also
    animate_led_adjust_speed();
}


void isr_pause(void)
{
    if ((millis() - g_isr_times[ISR_PAUSE]) > g_debounce_delay)
    {
        g_isr_times[ISR_PAUSE] = millis();
        animate_led_set_interrupt_flag(ISR_PAUSE);
    }
    else return;
#if defined(SERIAL_DEBUG)
    Serial.println("**EXTERNAL INTERRUPT - PAUSE STATE**");
#endif
}


#endif
