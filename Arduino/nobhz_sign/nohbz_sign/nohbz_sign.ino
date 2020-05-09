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
} sign_state_master_t; 


typedef enum
{
    ANIMATION_DELAY_MS_1 = 1, // sizzling
    ANIMATION_DELAY_MS_100 = 100,
    ANIMATION_DELAY_MS_500 = 500,
    ANIMATION_DELAY_MS_1000 = 1000,
    ANIMATION_DELAY_MS_1500 = 1500,
    ANIMATION_DELAY_MS_2000 = 2000,
    LAST_ANIMATION_DELAY,
} animation_delay_ms_t;

uint8_t z = 0;
const byte button1 = 2;
const byte button2 = 3;
byte pixel_set_flags[STRIP_SIZE] = {0};
bool rand_flags[8] = {false};
uint8_t st_dev_count = 0;
//sign_state_master_t master_sign_state = ST_MASTER_DEMO_FIXED_TIME;
sign_state_master_t master_sign_state = ST_MASTER_DEMO_FIXED_TIME;
animation_delay_ms_t animation_delay = ANIMATION_DELAY_MS_1000;
color_list_e random_sign_color = num_colors; // set to invalid color initially..
sign_state_t sign_state = ST_SPELL_WORD;
color_list_e sign_color = cyan;
color_list_e twinkle_color = red;
color_list_e random_twinkle_color = num_colors;
void mode_switch_isr(void);
void animation_speed_isr(void);
uint32_t loop_count = 0;

void switch_twinkle_color(void);
sign_state_t select_random_state(void);
void switch_sign_color(void);
uint16_t twinkle_spot(uint16_t minimum, uint16_t maximum, color_list_e color);
void reset_rand_flags(void);
bool twinkle_animation(void);
void check_loop_count(void);
bool state_used_flag[NUM_SIGN_STATES] = {false};
sign_state_t random_state = NUM_SIGN_STATES; // set to an invalid state initially....
uint8_t state_spot_checker = 0;

void setup(void)
{
    pinMode(VT, INPUT); // input
    pinMode(D3, INPUT);
    pinMode(D2, INPUT);
    pinMode(D1, INPUT);
    pinMode(D0, INPUT);
    pinMode(PWR_ENABLE, OUTPUT); // output
    digitalWrite(PWR_ENABLE, HIGH);
    pinMode(LED_BUILTIN, OUTPUT);
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
    random_twinkle_color = (color_list_e) random(red, num_colors);
    if(random_twinkle_color == twinkle_color)
    {
        if(gold != twinkle_color) twinkle_color = (color_list_e)twinkle_color + 1;
        else twinkle_color = (color_list_e)twinkle_color - 1;
    }
    else twinkle_color = random_twinkle_color;
}


void switch_sign_color(void)
{
    static bool first_pass = true;
    if(!first_pass)
    {
        sign_color = red;
        first_pass = false;
    }
    else
    {
        random_sign_color = (color_list_e) random(red, num_colors);
        if(random_sign_color == sign_color)
        {
            if(sign_color != gold) sign_color = (color_list_e)sign_color + 1;
            else sign_color = (color_list_e)sign_color - 1;
        }
        else sign_color = random_sign_color;
    }
}


unsigned long animation_last_time = 0;
unsigned long mode_switch_last_time = 0;
unsigned long debounceDelay = 50; // ms

bool state_transition_flag_g = false;

void mode_switch_isr()
{
    if ((millis() - mode_switch_last_time) > debounceDelay)
    {
        mode_switch_last_time = millis();
    }
    else return;
    loop_count = 0;
    switch(master_sign_state)
    {
        case ST_MASTER_DEMO_FIXED_TIME:
            master_sign_state = ST_MASTER_DEMO_VARIABLE_TIME;
            animation_delay = ANIMATION_DELAY_MS_1000;
            state_transition_flag_g = true;
        break;
        case ST_MASTER_DEMO_VARIABLE_TIME:
            master_sign_state = ST_RUN;
            sign_state = ST_SPELL_WORD;
            state_transition_flag_g = true;
        break;
        case ST_RUN:
            sign_state = (sign_state_t)(sign_state + 1);
            if(NUM_SIGN_STATES == sign_state) 
            {
                master_sign_state = ST_MASTER_DEMO_FIXED_TIME;
                state_transition_flag_g = true;
            }
        break;
    }
}

uint8_t animation_speed_flag = 0;
void animation_speed_isr()
{ 
    if ((millis() - animation_last_time) > debounceDelay)
    {
        animation_last_time = millis();
    }
    else return;
    loop_count = 0;
    animation_delay = (animation_delay_ms_t)animation_delay + 1;
    if(LAST_ANIMATION_DELAY == animation_delay) animation_delay = ANIMATION_DELAY_MS_1;
    loop_count = 0;
}


uint16_t twinkle_spot(uint16_t minimum, uint16_t maximum, color_list_e color)
{
    uint8_t start_pixel = 0;
    uint8_t stop_pixel = 0;
    // generate random number SRW
    // if random number is not used then use it and return
    // else
    // search in range min to random number
    // check for first 0 occurrence
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
    if ((rand_flags[N_LETTER] && rand_flags[O_LETTER]) && (rand_flags[H_LETTER] && rand_flags[B_LETTER]))
    {
        if (rand_flags[Z_LETTER])
        {
            reset_rand_flags();
            st_dev_count = 0;
            sign_color = twinkle_color;
            switch_twinkle_color();
            draw_word(sign_color, STRIP_SIZE, false);
        }
    }
    if (st_dev_count++ > 25) // 45 random pixel fills before we force entire word on
    {
        reset_rand_flags();
        st_dev_count = 0;
        sign_color = twinkle_color;
        switch_twinkle_color();
        draw_word(sign_color, STRIP_SIZE, false);
        return true;
    }
     return false;
}


// 10 seconds display time per animation in demo mode
#define DEMO_ANIMATION_TIME_MS 10000
bool demo_get_faster_flag = true;
void check_loop_count(void)
{
    Serial.println(loop_count, DEC);
    if(ST_MASTER_DEMO_VARIABLE_TIME == master_sign_state)
    {
        if(loop_count > (DEMO_ANIMATION_TIME_MS / animation_delay))
        {
            loop_count = 0;
            switch(animation_delay)
            {
                case ANIMATION_DELAY_MS_1:
                    if(demo_get_faster_flag) animation_delay = ANIMATION_DELAY_MS_100;
                    else 
                    {
                        animation_delay = ANIMATION_DELAY_MS_2000;
                        select_random_state();
                    }
                case ANIMATION_DELAY_MS_100:
                    if(demo_get_faster_flag) animation_delay = ANIMATION_DELAY_MS_500;
                    else animation_delay = ANIMATION_DELAY_MS_1;
                case ANIMATION_DELAY_MS_500:
                    if(demo_get_faster_flag) animation_delay = ANIMATION_DELAY_MS_1000;
                    else animation_delay = ANIMATION_DELAY_MS_100;
                case ANIMATION_DELAY_MS_1000:
                    if(demo_get_faster_flag) animation_delay = ANIMATION_DELAY_MS_2000;
                    else animation_delay = ANIMATION_DELAY_MS_500;
                case ANIMATION_DELAY_MS_2000:
                    if(demo_get_faster_flag) 
                    {
                        animation_delay = ANIMATION_DELAY_MS_1;
                        select_random_state();
                    }
                    else animation_delay = ANIMATION_DELAY_MS_1000;
                break;
            }
        }
    }
    if(loop_count >= ((uint32_t)DEMO_ANIMATION_TIME_MS / (uint32_t)animation_delay)) 
    {
        Serial.println("hi");
        loop_count = 0;
        sign_state = select_random_state();
    }
    loop_count++; 
}


sign_state_t select_random_state(void)
{
    static bool first_pass = true;
    if(!first_pass)
    {
        for(sign_state_t i = sign_state; i < NUM_SIGN_STATES; i = (sign_state_t)i + 1)
        {
            if(!state_used_flag[i])
            {
                state_spot_checker = i;
                while(state_used_flag[state_spot_checker])
                {
                    if((NUM_SIGN_STATES - 1) == state_spot_checker)
                    {
                        random_state = random(i, NUM_SIGN_STATES);
                        sign_state = random_state;
                        state_used_flag[sign_state] = true;
                        return sign_state;
                    }
                    state_spot_checker++;
                }
                if(state_spot_checker == i) // all states above i have been used already.. 
                {
                    // state_spot_checker is already equal to 'i' to get to this point
                    while(state_used_flag[state_spot_checker]);
                    {
                        // leaving out demo state here.  Sounds like a headache of circularly referenced messiness
                        if(ST_SPELL_WORD == state_spot_checker)
                        {
                            random_state = random(ST_SPELL_WORD, i+1);
                            sign_state = random_state;
                            state_used_flag[sign_state] = true;
                            return sign_state;
                        }
                        state_spot_checker--;
                    }
                    if(state_spot_checker != i)
                    {
                        random_state = random(state_spot_checker, i + 1);
                        sign_state = random_state;
                        state_used_flag[sign_state] = true;
                        return sign_state;
                    }
                }
                else
                {
                    random_state = random(i, state_spot_checker + 1);
                    sign_state = random_state;
                    state_used_flag[sign_state] = true;
                    return sign_state;
                }
                if(state_spot_checker == i) // state above & below are both used already.  
                {
                    random_state = i;
                    sign_state = random_state;
                    state_used_flag[sign_state] = true;
                    return sign_state;
                }
            }
        }
        // if we reach this point in code then all states have been used already.. 
        // clear all the state flags
        for(int i = 0; i < NUM_SIGN_STATES; i++)
        {
            state_used_flag[i] = false;
        }
        random_state = random(ST_SPELL_WORD, NUM_SIGN_STATES);
        sign_state = (sign_state_t)random_state;
        state_used_flag[sign_state] = true;
        return(sign_state);
    }
    else
    {
        random_state = random(ST_SPELL_WORD, NUM_SIGN_STATES); // random function lower bound is inclusive, upper bound is exclusive
        sign_state = (sign_state_t)random_state;
        state_used_flag[sign_state] = true;
        first_pass = false;
        return sign_state;
    }
}


letters_in_sign_t letter = N_LETTER;  
uint8_t alternate_t_b_flag = 1;
uint8_t alternate_l_r_flag = 1;

void loop() 
{
    if(state_transition_flag_g)
    {
        // alert the user they are switch master modes.  This occurs only on master transitions 
        state_transition_flag_g = false;
        draw_word(red, STRIP_SIZE, false);
        delay(250);
    }
    //Serial.println(master_sign_state,DEC);
    if(ST_MASTER_DEMO_FIXED_TIME == master_sign_state || ST_MASTER_DEMO_VARIABLE_TIME == master_sign_state)
    {
        check_loop_count();
    }
    switch (sign_state)
    {
        case ST_SPELL_WORD:
            draw_word(sign_color, STRIP_SIZE, true);
            delay(animation_delay);
        break;
        case ST_DRAW_LETTERS:
            while(letter != NUM_LETTERS)
            {
                draw_letter((letters_in_sign_t)letter, sign_color);
                letter = (letters_in_sign_t)(letter + 1);
                delay(animation_delay/NUM_LETTERS);
            }
        break;
        case ST_L_R_FADE:
            fade_word(sign_color, 10, true);
            delay(animation_delay);
        break;
        case ST_R_L_FADE:
            fade_word(sign_color, 10, false);
            delay(animation_delay);
        break;
        case ST_ALTERNATE_L_R_FADE:
            if(alternate_l_r_flag) fade_word(sign_color, 25, false);
            else  fade_word(sign_color, 25, true);
            alternate_l_r_flag ^= 1;
            delay(animation_delay);
        break;
        case ST_T_B_FADE:
            fade_word_top_to_bottom(sign_color, 25);
            delay(animation_delay);
        break;
        case ST_B_T_FADE:
            fade_word_bottom_to_top(sign_color, 25);
            delay(animation_delay);
        break;
        case ST_ALTERNATE_T_B_FADE:
            if(alternate_t_b_flag) fade_word_top_to_bottom(sign_color, 25);
            else fade_word_bottom_to_top(sign_color, 25);
            alternate_t_b_flag ^= 1;
            delay(animation_delay);
        break;
        case ST_DRAW_WORD:
            draw_word(sign_color, STRIP_SIZE, false);
            delay(animation_delay);
        break;
        case ST_TWINKLE:
           while(!twinkle_animation());
           delay(animation_delay);
        break;
        default:
        break;
    }
    
    switch_sign_color(); // for all cases switch sign color
}
