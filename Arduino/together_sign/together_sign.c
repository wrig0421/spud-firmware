/**************************************************************************
 *  @brief      Together sign with LED animations                         *
 *  @note       Arduino UNO used.  Code is easily portable                                *
 *  @author     Spencer Wright                                            *
 *  @copyright  Copyright (C) 2020 SRW                                    *
 *                                                                        *
 *  The code is intended to be distributed open-source with NO            *
 *  ASSOCIATED WARRANTY distributed with the code.  Use at your own       *
 *  risk.  Forward any bugs or concerns to wrig0421@umn.edu.              *
 **************************************************************************/

#include <together_sign.h>
#include <Adafruit_NeoPixel.h>

// RF receiver IC pins
#define VT          1  
#define D0          2
#define D1          3
#define D2          4
#define D3          5
#define PWR_ENABLE  6

typedef enum
{
    ST_SPELL_WORD,
    ST_DRAW_LETTERS,
    ST_L_R_FADE,
    ST_R_L_FADE,
    ST_T_B_FADE,
    ST_B_T_FADE,
    ST_DRAW_WORD,
    ST_ALTERNATE_FADE,
    ST_TWINKLE,
    ST_CRASH, 
    //ST_RAINBOW, // to cheesy..
    ST_DEV,
    ST_DEV_2,
} sign_state_t;


const byte button1 = 2;
const byte button2 = 3;

sign_state_t sign_state = ST_SPELL_WORD;
color_list_e sign_color = cyan;
color_list_e twinkle_color = red;

uint16_t delay_time = 10;

byte pixel_set_flags[STRIP_SIZE] = {0}; 
bool rand_flags[8] = {false};
int z = 0;
uint8_t st_dev_count = 0; 
uint8_t odd_count = 1;

color_list_e color_1 = red;
color_list_e color_2 = orange;
color_list_e color_3 = yellow;
color_list_e color_4 = green;
color_list_e color_5 = blue;
color_list_e color_6 = indigo;
color_list_e color_7 = violet;
color_list_e color_8 = red;
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
    attachInterrupt(digitalPinToInterrupt(button1), a_interrupt, RISING); 
    attachInterrupt(digitalPinToInterrupt(button2), b_interrupt, RISING); 
    randomSeed(analogRead(0));
    for(int i = 0; i < STRIP_SIZE; i++)
    {
        pixel_set_flags[i] = 0;
    }
    for(int i = 0; i < 8; i++)
    {
        rand_flags[i] = false;
    }
}


void switch_photo_color(void);
void switch_photo_color(void)
{
    switch(sign_color)
    {
        case red:
            sign_color = orange;
        break;
        case orange:
            sign_color = green;
        break;
        case green:
            sign_color = blue;
        break;
        case blue:
            sign_color = indigo;
        break;
        case indigo:
            sign_color = violet;
        break;
        case violet:
            sign_color = white;
        break;
        case white:
            sign_color = cyan;
        break;
        case cyan:
            sign_color = magenta;
        break;
        case magenta:
            sign_color = lime;
        break;
        case lime:
            sign_color = olive;
        break;
        case olive:
            sign_color = chocolate;
        break;
        case chocolate:
            sign_color = gold;
        break;
        case gold:
            sign_color = red;
        break;
        
    }
}


void switch_twinkle_color(void);
void switch_twinkle_color(void)
{
    switch(twinkle_color)
    {
        case white:
            twinkle_color = yellow;
        break;
        case yellow:
            twinkle_color = cyan;
        break;
        case cyan:
            twinkle_color = indigo;
        break;
        case indigo:
            twinkle_color = white;
        break;
        default:
            // reset color to white
            twinkle_color = white;
        break;
    }
}


void switch_color(void);
void switch_color(void)
{
    switch(sign_color)
    {
        case white:
            sign_color = yellow;
        break;
        case yellow:
            sign_color = cyan;
        break;
        case cyan:
            sign_color = indigo;
        break;
        case indigo:
            sign_color = white;
        break;
        default:
            // reset color to white
            sign_color = white;
        break;
    }
}


void a_interrupt()
{
    sign_state = (uint8_t)sign_state + 1;
    if(ST_DEV == sign_state)
    {
        sign_state = ST_SPELL_WORD;
    }
}

void b_interrupt()
{
    switch_photo_color();
}



uint16_t twinkle_spot(uint16_t minimum, uint16_t maximum, color_list_e color);
uint16_t twinkle_spot(uint16_t minimum, uint16_t maximum, color_list_e color)
{
    uint8_t start_pixel = 0;
    uint8_t stop_pixel = 0;
    uint8_t count = 0;
    // T
    // random number algorithm.  SRW
        // generate random number
        // if random number is not used then use it and return
        // else
            // search in range min to random number
                // check for first 0 occurrence 
    uint16_t rand_pixel = 0;
    rand_pixel = random(minimum, maximum);
    
    if(!pixel_set_flags[rand_pixel])
    {
        pixel_set_flags[rand_pixel] = 1;
        strip_turn_on_pixel(rand_pixel, color);
        return 0;
    }
    else
    {
        while(pixel_set_flags[minimum + start_pixel] && (((minimum + start_pixel) < rand_pixel) && ((minimum + start_pixel) < maximum)))
        {
            start_pixel++;
        }
        start_pixel = stop_pixel;
        while(!pixel_set_flags[minimum + stop_pixel] && (((minimum + start_pixel) < rand_pixel) && ((minimum + start_pixel) < maximum)))
        {
            stop_pixel++;
        }
        if(!start_pixel && !stop_pixel)
        {
            while(pixel_set_flags[rand_pixel + start_pixel] && ((rand_pixel + start_pixel) < maximum))
            {
                start_pixel++;
            }
            stop_pixel = start_pixel;
            while(!pixel_set_flags[rand_pixel + stop_pixel] && ((minimum + stop_pixel) < maximum))
            {
                stop_pixel++;
            }
            if(start_pixel == stop_pixel)
            {
                if(stop_pixel != maximum)
                {
                    stop_pixel = start_pixel + 1;
                }
            }
            if((rand_pixel + stop_pixel) > maximum)
            {
                return;
            }
            return (twinkle_spot(rand_pixel + start_pixel, rand_pixel + stop_pixel, color));
        }
        else
        {
            if(start_pixel == stop_pixel)
            {
                if(stop_pixel != maximum)
                {
                    stop_pixel = start_pixel + 1;
                }
            }
            if((minimum + stop_pixel) > maximum)
            {
                return;
            }
            return (twinkle_spot(minimum + start_pixel, minimum + stop_pixel, color));
        }
    }
}


void reset_rand_flags(void);
void reset_rand_flags(void)
{
    for(int i = 0; i < 8; i++)
    {
        rand_flags[i] = false;
    }
    for(int i = 0; i < STRIP_SIZE; i++)
    {
        pixel_set_flags[i] = 0;
    }
}


color_list_e swap_rainbow_color(color_list_e color);
color_list_e swap_rainbow_color(color_list_e color)
{
    switch(color)
    {
        case red:
            return violet;
        case orange:
            return red;
        case yellow:
            return orange;
        case green:
            return yellow;
        case blue:
            return green;
        case indigo:
            return blue;
        case violet:
            return indigo;
        default:
            return red;
    }
}


void loop() 
{
    switch(sign_state)
    {
        case ST_SPELL_WORD:
            draw_word(sign_color, STRIP_SIZE, delay_time, true);
         break;
         case ST_DRAW_LETTERS:
            draw_letters(sign_color, 500);
         break;
         case ST_L_R_FADE:
            fade_word(sign_color, delay_time, true);
         break;
         case ST_R_L_FADE:
            fade_word(sign_color, delay_time, false);
         break;
         case ST_T_B_FADE:
            fade_word_top_to_bottom(sign_color, delay_time);
         break;
         case ST_B_T_FADE:
            fade_word_bottom_to_top(sign_color, delay_time);
         break;
         case ST_DRAW_WORD:
            draw_word(sign_color, STRIP_SIZE, delay_time, false);
         break;
         case ST_ALTERNATE_FADE:
            fade_word(sign_color, delay_time, true);
            switch_color();
            fade_word(sign_color, delay_time, false);
         break;
         case ST_TWINKLE:
            if(odd_count)
            {
                for(z = T_FIRST_PIXEL_NUM_START; z < T_FIRST_PIXEL_NUM_STOP; z++) if(!pixel_set_flags[z]) break;
                if(z == T_FIRST_PIXEL_NUM_STOP) rand_flags[0] = true;
                else twinkle_spot(T_FIRST_PIXEL_NUM_START, T_FIRST_PIXEL_NUM_STOP, twinkle_color);
            }
            
            for(z = O_PIXEL_NUM_START; z < O_PIXEL_NUM_STOP; z++) if(!pixel_set_flags[z]) break;
            if(z == 60) rand_flags[1] = true;  
            else twinkle_spot(22, 60, twinkle_color);
            
            for(z = G_PIXEL_NUM_START; z < G_PIXEL_NUM_STOP; z++) if(!pixel_set_flags[z]) break;
            if(z == G_PIXEL_NUM_STOP) rand_flags[2] = true; 
            else twinkle_spot(G_PIXEL_NUM_START, G_PIXEL_NUM_STOP, twinkle_color);

            for(z = E_FIRST_PIXEL_NUM_START; z < E_FIRST_PIXEL_NUM_STOP; z++) if(!pixel_set_flags[z]) break;
            if(z == E_FIRST_PIXEL_NUM_STOP) rand_flags[3] = true; 
            else twinkle_spot(E_FIRST_PIXEL_NUM_START, E_FIRST_PIXEL_NUM_STOP, twinkle_color);
            
            if(odd_count)
            {
                for(z = T_LAST_PIXEL_NUM_START; z < T_LAST_PIXEL_NUM_STOP; z++) if(!pixel_set_flags[z]) break;
                if(z == T_LAST_PIXEL_NUM_STOP) rand_flags[4] = true;
                else twinkle_spot(T_LAST_PIXEL_NUM_START, T_LAST_PIXEL_NUM_STOP, twinkle_color);
            }
            
            for(z = H_PIXEL_NUM_START; z < H_PIXEL_NUM_STOP; z++) if(!pixel_set_flags[z]) break;
            if(z == H_PIXEL_NUM_STOP) rand_flags[5] = true; 
            else twinkle_spot(H_PIXEL_NUM_START, H_PIXEL_NUM_STOP, twinkle_color);

            for(z = E_LAST_PIXEL_NUM_START; z < E_LAST_PIXEL_NUM_STOP; z++) if(!pixel_set_flags[z]) break;
            if(z == E_LAST_PIXEL_NUM_STOP) rand_flags[6] = true; 
            else twinkle_spot(E_LAST_PIXEL_NUM_START, E_LAST_PIXEL_NUM_STOP, twinkle_color);

            for(z = R_PIXEL_NUM_START; z < R_PIXEL_NUM_STOP; z++) if(!pixel_set_flags[z]) break;
            if(z == R_PIXEL_NUM_STOP) rand_flags[7] = true; 
            else twinkle_spot(R_PIXEL_NUM_START, R_PIXEL_NUM_STOP, twinkle_color);

            if((rand_flags[T_LETTER_FIRST] && rand_flags[O_LETTER]) && (rand_flags[G_LETTER] && rand_flags[E_LETTER_FIRST]))
            {
                if((rand_flags[T_LETTER_LAST] && rand_flags[H_LETTER]) && (rand_flags[E_LETTER_LAST] && rand_flags[R_LETTER]))
                {
                    reset_rand_flags();
                    st_dev_count = 0;
                    sign_color = twinkle_color;
                    switch_twinkle_color();
                    draw_word(sign_color, STRIP_SIZE, 1000, false);
                }
            }
            if(st_dev_count++ > 45) // 45 random pixel fills before we force entire word on
            {
                reset_rand_flags();
                st_dev_count = 0;
                sign_color = twinkle_color;
                switch_twinkle_color();
                draw_word(sign_color, STRIP_SIZE, 1000, false);
            }
            odd_count ^= 1;
         break;
         case ST_CRASH:
            crash(red, blue, indigo, 10);
         break;
         case ST_DEV:
            fade_word_top_to_bottom(sign_color, 100);
            switch_color();
         break;
         default:
         break;
    }
    if(ST_DRAW_WORD != sign_state && ST_DEV != sign_state)
    {
        switch_color();
    }
}