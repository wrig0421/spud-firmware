/**************************************************************************
 *  -|-|-|-|-|-|-|-|-|-|-|-|-|Nohbz Sign-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|- *                                    *
 *                                                                        *
 *  @brief      Nohbz LED Strip Sign Code                                 *
 *  @note       Flashed to Arduino Uno                                    *
 *  @author     Spencer Wright                                            *
 *  @copyright  Copyright (C) 2020 Spencer Wright                         *
 *                                                                        *
 *  All code was written for a good buddy.  Feel free to disribute.       *                             
 *  Forward any bugs to wrig0421@umn.edu                                  *           
 **************************************************************************/

#include "Adafruit_NeoPixel.h"
#include <nohbz_sign.h>

#include "stdint.h"
#include "stdbool.h"

// RF receiver IC pins
#define VT          1
#define D0          2
#define D1          3
#define D2          4
#define D3          5
#define PWR_ENABLE  6

#define ANIMATION_SPEED_UP_FACTOR_0_5X          (float)0.5
#define ANIMATION_SPEED_UP_FACTOR_0_25X         (float)0.25
#define ANIMATION_SPEED_UP_FACTOR_0_1X          (float)0.1
#define ANIMATION_SPEED_UP_FACTOR_0X            0
#define DEFAULT_DELAY_TIME_MS                   1000

typedef enum
{
    ST_SPELL_WORD = 0,
    ST_DRAW_LETTERS,
    ST_L_R_FADE,
    ST_R_L_FADE,
    ST_ALTERNATE_L_R_FADE,
    ST_T_B_FADE,
    ST_B_T_FADE,
    ST_ALTERNATE_T_B_FADE,
    ST_DRAW_WORD,
    ST_TWINKLE,
    NUM_SIGN_STATES, 
} sign_state_t;


typedef enum
{
    ST_MASTER_DEMO_FIXED_TIME = 0,
    ST_MASTER_DEMO_VARIABLE_TIME,
    ST_RUN,
    ST_SOLID_COLOR,
} sign_state_master_t; 


typedef enum
{
    DEMO_VARIABLE_0_5X_COUNT = 6,
    DEMO_VARIABLE_0_25X_COUNT = 8,
    DEMO_VARIABLE_0_1X_COUNT = 10,
    DEMO_VARIABLE_0X_COUNT = 12,
} demo_variable_time_count_t;

sign_state_master_t master_sign_state = ST_MASTER_DEMO_FIXED_TIME;
sign_state_t sign_state = ST_SPELL_WORD;
sign_state_t random_state = NUM_SIGN_STATES; // set to an invalid state initially....
sign_state_t state_checker = sign_state;

letters_in_sign_t letter = N_LETTER;  

demo_variable_time_count_t demo_variable_time_count = DEMO_VARIABLE_0_5X_COUNT;

display_colors_e sign_color = disp_red;
display_colors_e random_sign_color = disp_num_colors_disp; // set to invalid color initially..
display_colors_e twinkle_color = disp_red;
display_colors_e random_twinkle_color = disp_num_colors_disp;

bool rand_flags[8] = {false}; // used in twinkle function..
bool down_flag = true; // used for demo modes
byte pixel_set_flags[STRIP_SIZE] = {0}; // used in twinkle function..

const byte button1 = 2;
const byte button2 = 3;

uint32_t loop_count = 0;
uint8_t z = 0; // use in twinkle function.. 
uint8_t st_dev_count = 0; // used in twinkle function.. 
uint8_t state_spot_checker = 0;
uint8_t alternate_t_b_flag = 1;
uint8_t alternate_l_r_flag = 1;
uint8_t state_transition_num_blinks = 0;
uint8_t animation_speed_num_blinks = 0;
float animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0X;

// variables used in ISR
unsigned long animation_last_time = 0;
unsigned long mode_switch_last_time = 0;
unsigned long debounceDelay = 50; // ms

bool state_transition_flag_g = false;
bool run_state_transition_flag_g = false;
bool animation_speed_change_flag_g = false;

// local function defs
void mode_switch_isr(void);
void animation_speed_isr(void);
void switch_twinkle_color(void);
void clear_random_state_flags(void);
void switch_sign_color_in_order(void);
void switch_sign_color(void);
void reset_rand_flags(void);
void check_loop_count(void);

bool state_used_flag[NUM_SIGN_STATES] = {false};
bool twinkle_animation(void);

sign_state_t select_random_state(void);

uint16_t twinkle_spot(uint16_t minimum, uint16_t maximum, display_colors_e color);

void setup(void)
{
    pinMode(VT, INPUT); 
    pinMode(D3, INPUT);
    pinMode(D2, INPUT);
    pinMode(D1, INPUT);
    pinMode(D0, INPUT);
    Serial.begin(9600);
    strip_init();
    interrupts();
    attachInterrupt(digitalPinToInterrupt(button1), mode_switch_isr, RISING);
    attachInterrupt(digitalPinToInterrupt(button2), animation_speed_isr, RISING);
    randomSeed(analogRead(0));
    for (int i = 0; i < STRIP_SIZE; i++) pixel_set_flags[i] = 0;
    for (int i = 0; i < 8; i++) rand_flags[i] = false;
}


void switch_twinkle_color(void)
{
    random_twinkle_color = (display_colors_e) random(disp_red, disp_num_colors_disp);
    if(random_twinkle_color == twinkle_color)
    {
        if(disp_magenta != twinkle_color) twinkle_color = (display_colors_e)twinkle_color + 1;
        else twinkle_color = (display_colors_e)twinkle_color - 1;
    }
    else twinkle_color = random_twinkle_color;
}


void switch_sign_color_in_order(void)
{
    sign_color = (display_colors_e) sign_color + 1;
    if(disp_num_colors_disp == sign_color) sign_color = disp_red;
}


void switch_sign_color(void)
{
    static bool first_pass = true;
    if(!first_pass)
    {
        sign_color = disp_red;
        first_pass = false;
    }
    else
    {
        random_sign_color = (display_colors_e) random(disp_red, disp_num_colors_disp);
        if(random_sign_color == sign_color)
        {
            if(disp_magenta != sign_color) sign_color = (display_colors_e)sign_color + 1;
            else sign_color = (display_colors_e)sign_color - 1;
        }
        else sign_color = random_sign_color;
    }
}


void mode_switch_isr()
{
    if ((millis() - mode_switch_last_time) > debounceDelay)
    {
        mode_switch_last_time = millis();
    }
    else return;
    loop_count = 0;
    clear_random_state_flags(); // best option just to clear flags for random states on mode switch
    switch(master_sign_state)
    {
        case ST_MASTER_DEMO_FIXED_TIME:
            master_sign_state = ST_MASTER_DEMO_VARIABLE_TIME;
            sign_state = ST_SPELL_WORD;
            state_transition_flag_g = true;
        break;
        case ST_MASTER_DEMO_VARIABLE_TIME:
            master_sign_state = ST_SOLID_COLOR;
            sign_state = ST_DRAW_WORD;
            state_transition_flag_g = true;
        break;
        case ST_SOLID_COLOR:
            sign_state = ST_SPELL_WORD;
            master_sign_state = ST_RUN;
            state_transition_flag_g = true;
        break;
        case ST_RUN:
            sign_state = (sign_state_t)(sign_state + 1);
            if(NUM_SIGN_STATES == sign_state) 
            {
                sign_state = ST_SPELL_WORD;
                master_sign_state = ST_MASTER_DEMO_FIXED_TIME;
                state_transition_flag_g = true;
            }
            else run_state_transition_flag_g = true;   
        break;
    }
}


void animation_speed_isr()
{ 
    if ((millis() - animation_last_time) > debounceDelay)
    {
        animation_last_time = millis();
    }
    else return;
    loop_count = 0;
    if(ST_SOLID_COLOR == master_sign_state)
    {
        switch_sign_color_in_order();
        animation_speed_change_flag_g = false;
    }
    else
    {
        animation_speed_change_flag_g = true;
        if(ANIMATION_SPEED_UP_FACTOR_0_5X == animation_speed_factor)
        {
            animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0_25X;
        }
        else if(ANIMATION_SPEED_UP_FACTOR_0_25X == animation_speed_factor)
        {
            animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0_1X;
        }
        else if(ANIMATION_SPEED_UP_FACTOR_0_1X == animation_speed_factor)
        {
            animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0X;
        }
        else if(ANIMATION_SPEED_UP_FACTOR_0X == animation_speed_factor)
        {
            animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0_5X;
        }
    }
}


uint16_t twinkle_spot(uint16_t minimum, uint16_t maximum, display_colors_e color)
{
    uint8_t start_pixel = 0;
    uint8_t stop_pixel = 0;
    uint16_t rand_pixel = 0;
    
    rand_pixel = random(minimum, maximum);
    
    if (!pixel_set_flags[rand_pixel])
    {
        pixel_set_flags[rand_pixel] = 1;
        strip_turn_on_pixel(rand_pixel, color);
        return 0;
    }
    else
    {
        while (pixel_set_flags[minimum + start_pixel] && (((minimum + start_pixel) < rand_pixel) && ((minimum + start_pixel) < maximum))) start_pixel++;
        start_pixel = stop_pixel;
        while (!pixel_set_flags[minimum + stop_pixel] && (((minimum + start_pixel) < rand_pixel) && ((minimum + start_pixel) < maximum))) stop_pixel++;
        if (!start_pixel && !stop_pixel)
        {
            while (pixel_set_flags[rand_pixel + start_pixel] && ((rand_pixel + start_pixel) < maximum)) start_pixel++;
            stop_pixel = start_pixel;
            while (!pixel_set_flags[rand_pixel + stop_pixel] && ((minimum + stop_pixel) < maximum)) stop_pixel++;
            if (start_pixel == stop_pixel)
            {
                if (stop_pixel != maximum) stop_pixel = start_pixel + 1;
            }
            if ((rand_pixel + stop_pixel) > maximum) return;
            return (twinkle_spot(rand_pixel + start_pixel, rand_pixel + stop_pixel, color));
        }
        else
        {
            if (start_pixel == stop_pixel)
            {
                if (stop_pixel != maximum) stop_pixel = start_pixel + 1;
            }
            if ((minimum + stop_pixel) > maximum) return;
            return (twinkle_spot(minimum + start_pixel, minimum + stop_pixel, color));
        }
    }
}


void reset_rand_flags(void)
{
    for (int i = 0; i < 8; i++) rand_flags[i] = false;
    for (int i = 0; i < STRIP_SIZE; i++) pixel_set_flags[i] = 0;
}


bool twinkle_animation(void)
{
    for (z = N_LEFT_POST_PIXEL_NUM_START; z < N_RIGHT_POST_PIXEL_NUM_STOP; z++) if (!pixel_set_flags[z]) break;
    if (z == N_RIGHT_POST_PIXEL_NUM_STOP) rand_flags[N_LETTER] = true;
    else twinkle_spot(N_LEFT_POST_PIXEL_NUM_START, N_RIGHT_POST_PIXEL_NUM_STOP, twinkle_color);
    for (z = O_PIXEL_NUM_START; z < O_PIXEL_NUM_STOP; z++) if (!pixel_set_flags[z]) break;
    if (z == 60) rand_flags[O_LETTER] = true;
    else twinkle_spot(O_PIXEL_NUM_START, O_PIXEL_NUM_STOP, twinkle_color);
    for (z = H_LEFT_POST_PIXEL_NUM_START; z < H_MID_PIXEL_NUM_STOP; z++) if (!pixel_set_flags[z]) break;
    if (z == H_MID_PIXEL_NUM_STOP) rand_flags[H_LETTER] = true;
    else twinkle_spot(H_LEFT_POST_PIXEL_NUM_START, H_MID_PIXEL_NUM_STOP, twinkle_color);
    for (z = B_LEFT_POST_PIXEL_NUM_START; z < B_MID_PIXEL_NUM_STOP; z++) if (!pixel_set_flags[z]) break;
    if (z == B_MID_PIXEL_NUM_STOP) rand_flags[B_LETTER] = true;
    else twinkle_spot(B_LEFT_POST_PIXEL_NUM_START, B_MID_PIXEL_NUM_STOP, twinkle_color);
    for (z = Z_TOP_POST_PIXEL_NUM_START; z < Z_BOTTOM_POST_PIXEL_NUM_STOP; z++) if (!pixel_set_flags[z]) break;
    if (z == Z_BOTTOM_POST_PIXEL_NUM_STOP) rand_flags[Z_LETTER] = true;
    else twinkle_spot(Z_TOP_POST_PIXEL_NUM_START, Z_BOTTOM_POST_PIXEL_NUM_STOP, twinkle_color);
    delay(250 * animation_speed_factor + 10);
    if ((rand_flags[N_LETTER] && rand_flags[O_LETTER]) && (rand_flags[H_LETTER] && rand_flags[B_LETTER]))
    {
        if (rand_flags[Z_LETTER])
        {
            reset_rand_flags();
            st_dev_count = 0;
            sign_color = twinkle_color;
            switch_twinkle_color();
            draw_word(sign_color, STRIP_SIZE, false, animation_speed_factor);
        }
        
    }
    if (st_dev_count++ > 28) // force word fill if not found by this point
    {
        reset_rand_flags();
        st_dev_count = 0;
        sign_color = twinkle_color;
        switch_twinkle_color();
        draw_word(sign_color, STRIP_SIZE, false, animation_speed_factor);
        return true;
    }
    return false;
}


void check_loop_count(void)
{
    if(ST_MASTER_DEMO_VARIABLE_TIME == master_sign_state)
    {
        switch(demo_variable_time_count)
        {
            case DEMO_VARIABLE_0_5X_COUNT:
                if(loop_count >= DEMO_VARIABLE_0_5X_COUNT)
                {
                    if(!down_flag) 
                    {
                        down_flag = true;
                        select_random_state();
                    }
                    loop_count = 0;
                    demo_variable_time_count = DEMO_VARIABLE_0_25X_COUNT;
                    animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0_25X;
                }
            break;
            case DEMO_VARIABLE_0_25X_COUNT:
                if(loop_count >= DEMO_VARIABLE_0_25X_COUNT)
                {
                    loop_count = 0;
                    if(down_flag)
                    {
                        demo_variable_time_count = DEMO_VARIABLE_0_1X_COUNT;
                        animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0_1X;
                    }
                    else
                    {
                        demo_variable_time_count = DEMO_VARIABLE_0_5X_COUNT;
                        animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0_5X;
                    }
                }
            break;
            case DEMO_VARIABLE_0_1X_COUNT:
                if(loop_count >= DEMO_VARIABLE_0_1X_COUNT)
                {
                    loop_count = 0;
                    if(down_flag)
                    {
                        demo_variable_time_count = DEMO_VARIABLE_0X_COUNT;
                        animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0X;
                    }
                    else
                    {
                        demo_variable_time_count = DEMO_VARIABLE_0_25X_COUNT;
                        animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0_25X;
                    }
                }
            break;
            case DEMO_VARIABLE_0X_COUNT:
                if(loop_count >= DEMO_VARIABLE_0X_COUNT)
                {
                    loop_count = 0;
                    if(down_flag) 
                    {
                        down_flag = false;
                        select_random_state();
                    }
                    demo_variable_time_count = DEMO_VARIABLE_0_1X_COUNT;
                    animation_speed_factor = ANIMATION_SPEED_UP_FACTOR_0_1X;
                }
            break;
            default:
            break;
        }
    }
    else if(ST_MASTER_DEMO_FIXED_TIME == master_sign_state)
    {
        if(ANIMATION_SPEED_UP_FACTOR_0X == animation_speed_factor)
        {
            if(loop_count > DEMO_VARIABLE_0X_COUNT)
            {
                loop_count = 0;
                select_random_state();
            }
        }
        else if(ANIMATION_SPEED_UP_FACTOR_0_1X == animation_speed_factor)
        {
            if(loop_count > DEMO_VARIABLE_0_1X_COUNT)
            {
                loop_count = 0;
                select_random_state();
            }
        }
        else if(ANIMATION_SPEED_UP_FACTOR_0_25X == animation_speed_factor)
        {
            if(loop_count > DEMO_VARIABLE_0_25X_COUNT)
            {
                loop_count = 0;
                select_random_state();
            }
        }
        else if(ANIMATION_SPEED_UP_FACTOR_0_5X == animation_speed_factor)
        {
            if(loop_count > DEMO_VARIABLE_0_5X_COUNT)
            {
                loop_count = 0;
                select_random_state();
            }
        }
    }
    loop_count++; 
}



void clear_random_state_flags(void)
{
    for(sign_state_t i = ST_SPELL_WORD; i < NUM_SIGN_STATES;)
    {
        state_used_flag[i] = false;
        i = (sign_state_t)i + 1;
    }
}


sign_state_t select_random_state(void)
{
    if(sign_state != ST_TWINKLE)
    {
        random_state = (sign_state_t)random(sign_state, NUM_SIGN_STATES);
    }
    else
    {
        random_state = (sign_state_t)random(ST_SPELL_WORD, sign_state);
    }
    Serial.println("Trying to change state");
    if(state_used_flag[random_state])
    {
        if(random_state != ST_TWINKLE)
        {
            random_state = (sign_state_t)random_state + 1;
            state_checker = random_state;
        }
        else
        {
            random_state = (sign_state_t)random_state - 1;
            state_checker = random_state;
        }
        while(state_used_flag[state_checker]) // try to find first unused state.. 
        {
            state_checker = (sign_state_t)state_checker + 1;
            if(NUM_SIGN_STATES == state_checker)
            {
                state_checker = random_state;
                while(state_used_flag[state_checker])
                {
                    if(ST_SPELL_WORD == state_checker)
                    {
                        for(sign_state_t i = ST_SPELL_WORD; i < NUM_SIGN_STATES;)
                        {
                            state_used_flag[i] = false;
                            i = (sign_state_t)i + 1;
                        }
                        random_state = random(ST_SPELL_WORD, NUM_SIGN_STATES);
                        sign_state = (sign_state_t)random_state;
                        state_used_flag[sign_state] = true;
                        return sign_state;
                    }
                    state_checker = (sign_state_t)state_checker - 1;
                }
            }
        }
        random_state = state_checker;
        state_checker = ST_SPELL_WORD;
        while(state_used_flag[state_checker])
        {
            if(state_checker == ST_TWINKLE)
            {
                for(sign_state_t i = ST_SPELL_WORD; i < NUM_SIGN_STATES;)
                {
                    state_used_flag[i] = false;
                    i = (sign_state_t)i + 1;
                }
                random_state = random(ST_SPELL_WORD, NUM_SIGN_STATES);
                sign_state = (sign_state_t)random_state;
                state_used_flag[sign_state] = true;
                return sign_state;
            }
            state_checker = (sign_state_t)state_checker + 1;
        }
        sign_state = random_state;
        state_used_flag[sign_state] = true;
        return sign_state;
    }
    else
    {
        state_checker = ST_SPELL_WORD;
        while(state_used_flag[state_checker])
        {
            if(state_checker == ST_TWINKLE)
            {
                for(sign_state_t i = ST_SPELL_WORD; i < NUM_SIGN_STATES;)
                {
                    state_used_flag[i] = false;
                    i = (sign_state_t)i + 1;
                }
                random_state = random(ST_SPELL_WORD, NUM_SIGN_STATES);
                sign_state = (sign_state_t)random_state;
                state_used_flag[sign_state] = true;
                return sign_state;
            }
            state_checker = (sign_state_t)state_checker + 1;
        }
        sign_state = random_state;
        state_used_flag[sign_state] = true;
        return sign_state;
    }
}


void loop() 
{
    if(state_transition_flag_g)
    {
        // alert the user they are switch master modes.  This occurs only on master transitions 
        state_transition_flag_g = false;
        if(ST_MASTER_DEMO_FIXED_TIME == master_sign_state) state_transition_num_blinks = 1;
        else if(ST_MASTER_DEMO_VARIABLE_TIME == master_sign_state) state_transition_num_blinks = 2;
        else if(ST_SOLID_COLOR == master_sign_state) state_transition_num_blinks = 3;
        else state_transition_num_blinks = 4;
        for(uint8_t i = 0; i < state_transition_num_blinks; i++)
        {
            strip_clear(STRIP_SIZE);
            delay(500);
            draw_word(disp_red, STRIP_SIZE, false, animation_speed_factor);
            delay(250);
        }
        strip_clear(STRIP_SIZE);
        delay(500);
    }
    else if(run_state_transition_flag_g)
    {
        run_state_transition_flag_g = false;
        strip_clear(STRIP_SIZE);
        delay(500);
        draw_word(disp_blue, STRIP_SIZE, false, animation_speed_factor);
        delay(250);
        strip_clear(STRIP_SIZE);
        delay(500);
    }
    else if(animation_speed_change_flag_g)
    {
        animation_speed_change_flag_g = false;
        if(ANIMATION_SPEED_UP_FACTOR_0_5X == animation_speed_factor)
        {
            animation_speed_num_blinks = 1;
        }
        else if(ANIMATION_SPEED_UP_FACTOR_0_25X == animation_speed_factor)
        {
            animation_speed_num_blinks = 2;
        }
        else if(ANIMATION_SPEED_UP_FACTOR_0_1X == animation_speed_factor)
        {
            animation_speed_num_blinks = 3;
        }
        else 
        {
            animation_speed_num_blinks = 4;
        }
        for(uint8_t i = 0; i < animation_speed_num_blinks; i++)
        {
            strip_clear(STRIP_SIZE);
            delay(500);
            draw_word(disp_green, STRIP_SIZE, false, animation_speed_factor);
            delay(250);
        }
        strip_clear(STRIP_SIZE);
        delay(500);
        draw_word(sign_color, STRIP_SIZE, false, animation_speed_factor);
    }
    if(master_sign_state != ST_SOLID_COLOR)
    {
        switch_sign_color();
    }
    if(ST_MASTER_DEMO_FIXED_TIME == master_sign_state || ST_MASTER_DEMO_VARIABLE_TIME == master_sign_state)
    {
        check_loop_count();
    }
    switch (sign_state)
    {
        case ST_SPELL_WORD:
            draw_word(sign_color, STRIP_SIZE, true, animation_speed_factor);
            delay(DEFAULT_DELAY_TIME_MS * animation_speed_factor);
        break;
        case ST_DRAW_LETTERS:
            while(NUM_LETTERS != draw_letter(letter, sign_color))
            {
                letter = (uint8_t)letter + 1;
                delay(2000 * animation_speed_factor + 50);
            }
            letter = N_LETTER;
        break;
        case ST_L_R_FADE:
            fade_word(sign_color, 250*animation_speed_factor + 10, true);
            delay(DEFAULT_DELAY_TIME_MS * animation_speed_factor);
        break;
        case ST_R_L_FADE:
            fade_word(sign_color, 250*animation_speed_factor + 10, false);
            delay(DEFAULT_DELAY_TIME_MS * animation_speed_factor);
        break;
        case ST_ALTERNATE_L_R_FADE:
            if(alternate_l_r_flag) fade_word(sign_color, 250*animation_speed_factor + 10, false);
            else  fade_word(sign_color, 250*animation_speed_factor + 10, true);
            alternate_l_r_flag ^= 1;
            delay(DEFAULT_DELAY_TIME_MS * animation_speed_factor + 10);
        break;
        case ST_T_B_FADE:
            fade_word_top_to_bottom(sign_color, 250*animation_speed_factor + 10);
            delay(DEFAULT_DELAY_TIME_MS * animation_speed_factor);
        break;
        case ST_B_T_FADE:
            fade_word_bottom_to_top(sign_color, 250*animation_speed_factor + 10);
            delay(DEFAULT_DELAY_TIME_MS * animation_speed_factor);
        break;
        case ST_ALTERNATE_T_B_FADE:
            if(alternate_t_b_flag) fade_word_top_to_bottom(sign_color, 250*animation_speed_factor + 10);
            else fade_word_bottom_to_top(sign_color, 250*animation_speed_factor + 10);
            alternate_t_b_flag ^= 1;
            delay(DEFAULT_DELAY_TIME_MS * animation_speed_factor);
        break;
        case ST_DRAW_WORD:
            draw_word(sign_color, STRIP_SIZE, false, animation_speed_factor);
            delay(DEFAULT_DELAY_TIME_MS * animation_speed_factor + 100);
        break;
        case ST_TWINKLE:
           while(!twinkle_animation());
           delay(DEFAULT_DELAY_TIME_MS * animation_speed_factor + 100);
        break;
        default:
        break;
    }
}