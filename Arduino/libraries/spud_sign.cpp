





#include "spud_sign.h"
#include <Adafruit_NeoPixel.h>

#define PIN 12


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_SIZE, PIN, NEO_GRB + NEO_KHZ800);

uint32_t full_strip_color[num_colors] = {0}; 
colors ch[20]; 

void strip_init(void)
{
	strip.setBrightness(100);
    strip.begin();
    strip.show(); 
    
    ch[black].red = 0;
    ch[black].green = 0;
    ch[black].blue = 0;
    full_strip_color[black] = strip.Color(0, 0, 0);
    ch[disp_white].red = 255;
    ch[disp_white].green = 255;
    ch[disp_white].blue = 255;
    full_strip_color[disp_white] = strip.Color(255, 255, 255);
    ch[disp_red].red = 255;
    ch[disp_red].green = 0;
    ch[disp_red].blue = 0;
    full_strip_color[disp_red] = strip.Color(255, 0, 0);
    ch[disp_blue].red = 0;
    ch[disp_blue].green = 0;
    ch[disp_blue].blue = 255;
    full_strip_color[disp_blue] = strip.Color(0, 0, 255);
    ch[disp_green].red = 0;
    ch[disp_green].green = 255;
    ch[disp_green].blue = 0;
    full_strip_color[disp_green] = strip.Color(0, 255, 0);
    ch[disp_orange].red = 255;
    ch[disp_orange].green = 165;
    ch[disp_orange].blue = 0;
    full_strip_color[disp_orange] = strip.Color(255, 165, 0);
    ch[disp_yellow].red = 255;
    ch[disp_yellow].green = 255;
    ch[disp_yellow].blue = 0;
    full_strip_color[disp_yellow] = strip.Color(255, 255, 0);
    ch[disp_indigo].red = 75;
    ch[disp_indigo].green = 0;
    ch[disp_indigo].blue = 138;
    full_strip_color[disp_indigo] = strip.Color(75, 0, 138);
    ch[disp_violet].red = 238;
    ch[disp_violet].green = 138;
    ch[disp_violet].blue = 238;
    full_strip_color[disp_violet] = strip.Color(238, 138, 238);
    ch[disp_cyan].red = 0;
    ch[disp_cyan].green = 255;
    ch[disp_cyan].blue = 255;
    full_strip_color[disp_cyan] = strip.Color(0, 255, 255);
    ch[disp_magenta].red = 255;
    ch[disp_magenta].green = 0;
    ch[disp_magenta].blue = 255;
    full_strip_color[disp_magenta] = strip.Color(255, 0, 255);
    /*
    ch[lime].red = 0;
    ch[lime].green = 255;
    ch[lime].blue = 0;
    full_strip_color[lime] = strip.Color(0, 255, 0);
    ch[maroon].red = 128;
    ch[maroon].green = 0;
    ch[maroon].blue = 0;
    full_strip_color[maroon] = strip.Color(128, 0, 0);
    ch[olive].red = 128;
    ch[olive].green = 128;
    ch[olive].blue = 0;
    full_strip_color[olive] = strip.Color(128, 128, 0);
    ch[disp_chocolate].red = 210;
    ch[disp_chocolate].green = 105;
    ch[disp_chocolate].blue = 30;
    full_strip_color[disp_chocolate] = strip.Color(210, 105, 30);
    ch[gold].red = 255;
    ch[gold].green = 215;
    ch[gold].blue = 0;
    full_strip_color[gold] = strip.Color(255, 215, 30);
    */
    for(int i = 0; i < STRIP_SIZE; i++)
    {
		strip.setPixelColor(i, ch[black].red, ch[black].green, ch[black].blue);
    }
}


void strip_turn_off_pixel(uint16_t pixel)
{
	strip.setPixelColor(pixel, ch[black].red, ch[black].green, ch[black].blue);
	strip.show();
}


void strip_turn_on_pixel(uint16_t pixel, display_colors_e color)
{
	strip.setPixelColor(pixel, ch[color].red, ch[color].green, ch[color].blue);
	strip.show();
}


void show_strip(void)
{
	strip.show();
}


void strip_clear(uint16_t strip_size)
{
	for(int i = 0; i < strip_size; i++)
    {
        strip.setPixelColor(i, ch[black].red, ch[black].green, ch[black].blue);
	}
	strip.show();
}


void strip_set_brightness(uint8_t brightness)
{
	strip.setBrightness(brightness);
	strip.begin();
}


letters_in_sign_t draw_letter(letters_in_sign_t letter, display_colors_e color)
{
    uint16_t lower_bound = 0;
    uint16_t upper_bound = 0;
    switch(letter)
    {
        case S_LETTER:
            lower_bound = S_PIXEL_NUM_START;
            upper_bound = S_PIXEL_NUM_STOP;
        break;
        case P_LETTER:
            lower_bound = P_PIXEL_NUM_START;
            upper_bound = P_PIXEL_NUM_STOP;
        break;
        case U_LETTER:
            lower_bound = U_PIXEL_NUM_START;
            upper_bound = U_PIXEL_NUM_STOP;
        break;
        case D_LETTER:
            lower_bound = D_PIXEL_NUM_START;
            upper_bound = D_PIXEL_NUM_STOP;
        break;
        default:
            return;
        break;
    }
    for(int i = lower_bound; i <= upper_bound; i++)
    {
        strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    }
    strip.show();
    return letter;
}


void draw_letters(display_colors_e color, uint16_t delay_time)
{
	letters_in_sign_t letter = S_LETTER;
    while(D_LETTER != draw_letter(letter, color))
    {
        letter = (uint8_t)letter + 1;
        delay(delay_time);
    }
}


void draw_word(display_colors_e color, uint16_t strip_size, bool spell, float speed_factor)
{
	if(!spell) strip.clear();
    for(int i = 0; i < strip_size; i++)
    {
        strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
        if(spell) 
		{
			strip.show();
			// min speed should be 100 ms.  
			// max should be 1 ms or 0. 
			delay(100 * speed_factor);
		}
    }
    strip.show();
}


void blink_word(display_colors_e color, uint16_t strip_size, uint16_t delay_time)
{
	strip.fill(full_strip_color[color], 0, strip_size);
	strip.show();
	delay(delay_time);
	strip.clear();
	strip.show();
	delay(delay_time);
}


void fade_letter_l_to_r(letters_in_sign_t letter, display_colors_e color, uint16_t delay_time)
{
    switch(letter)
    {
    	case S_LETTER:
			for(int i = 0; i <= S_LEFT_PIXEL_NUM - S_PIXEL_NUM_START; i++)
			{
				delay(delay_time);
				strip.setPixelColor(S_LEFT_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(S_LEFT_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(S_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
			}
			strip.show();
    	break;
    	
    	case P_LETTER:
			for(int i = P_PIXEL_NUM_START; i <= P_POST_PIXEL_NUM_STOP; i++)
    		{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
			strip.show();
			for(int i = 0; i <= P_MIDPOINT_PIXEL_NUM - P_PIXEL_NUM_START; i++)
			{
				delay(delay_time);
				strip.setPixelColor(P_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(P_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
    	break;
    	
    	case U_LETTER:
			// unique doesn't follow above
			for(int i = U_PIXEL_NUM_START; i <= U_PIXEL_NUM_STOP; i++)
			{
				delay(delay_time);
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
    	break;
    	
    	case D_LETTER:
			for(int i = D_PIXEL_NUM_START; i <= D_POST_PIXEL_NUM_STOP; i++)
			{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
			}
			strip.show();
			for(int i = 0; i <= D_RIGHT_PIXEL_NUM - D_TOP_CURVE_PIXEL_NUM_START; i++)
			{
				delay(delay_time);
				strip.setPixelColor(D_TOP_CURVE_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(D_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
    	break;
		
    	default:
    	break;
    }
}


void fade_letter_r_to_l(letters_in_sign_t letter, display_colors_e color, uint16_t delay_time)
{
    switch(letter)
    {
		// right to left fade!  
		case S_LETTER:
			for(int i = 0; i <= S_PIXEL_NUM_STOP - S_RIGHT_PIXEL_NUM; i++)
			{
				delay(delay_time);
				strip.setPixelColor(S_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(S_RIGHT_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(S_RIGHT_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
		break;
		
		case P_LETTER:
			for(int i = 0; i <= P_RIGHT_PIXEL_NUM - P_TOP_CURVE_PIXEL_NUM_START; i++)
			{
				delay(delay_time);
				strip.setPixelColor(P_RIGHT_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(P_RIGHT_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
			for(int i = P_PIXEL_NUM_START; i <= P_POST_PIXEL_NUM_STOP; i++)
    		{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
			strip.show();
		break;
		
		case U_LETTER:
			// unique doesn't follow above
			for(int i = U_PIXEL_NUM_STOP; i >= U_PIXEL_NUM_START; i--)
			{
				delay(delay_time);
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
    	break;
		
		case D_LETTER:
			for(int i = 0; i <= D_RIGHT_PIXEL_NUM - D_TOP_CURVE_PIXEL_NUM_START; i++)
			{
				delay(delay_time);
				strip.setPixelColor(D_RIGHT_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(D_RIGHT_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
			for(int i = D_PIXEL_NUM_START; i <= D_POST_PIXEL_NUM_STOP; i++)
			{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
			}
			strip.show();
    	break;
    	default:
    	break;
    }
}


void fade_word_bottom_to_top(display_colors_e color, uint16_t delay_time)
{
	// bottom to top
	uint8_t s_tail_count = 0;
	uint8_t s_back_count = 0;
	uint8_t p_back_count = 0;
	uint8_t d_back_count = 0;
	for(int i = 0; i <= VERTICAL_POST_NUM_PIXELS; i++)
	{
		strip.setPixelColor(S_BOTTOM_PIXEL_NUM - s_back_count++, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(S_BOTTOM_PIXEL_NUM - s_back_count++, ch[color].red, ch[color].green, ch[color].blue);

		strip.setPixelColor(P_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(P_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(P_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue); // I assume two to speed up but not checked on sign

		strip.setPixelColor(U_BOTTOM_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue); 
		strip.setPixelColor(U_BOTTOM_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue); 
		
		strip.setPixelColor(D_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue); 
		strip.setPixelColor(D_PIXEL_NUM_STOP - d_back_count++, ch[color].red, ch[color].green, ch[color].blue); 
		strip.setPixelColor(D_PIXEL_NUM_STOP - d_back_count++, ch[color].red, ch[color].green, ch[color].blue); 
		if(i < 3)
		{
			strip.setPixelColor(S_BOTTOM_PIXEL_NUM + s_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
			strip.setPixelColor(S_BOTTOM_PIXEL_NUM + s_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
		}
		if(i > 5) // midpoint of P vertical section needed
		{
			strip.setPixelColor(P_PIXEL_NUM_STOP - p_back_count++, ch[color].red, ch[color].green, ch[color].blue);
			strip.setPixelColor(P_PIXEL_NUM_STOP - p_back_count++, ch[color].red, ch[color].green, ch[color].blue);
		}
	}
}


void fade_word_top_to_bottom(display_colors_e color, uint16_t delay_time)
{
	// top to bottom
	uint8_t s_tail_count = 0;
	uint8_t s_forward_count = 0;
	uint8_t p_forward_count = 0;
	uint8_t d_forward_count = 0;
	for(int i = 0; i <= VERTICAL_POST_NUM_PIXELS; i++)
	{
		delay(delay_time);
		strip.setPixelColor(S_TOP_PIXEL_NUM + s_forward_count++, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(S_TOP_PIXEL_NUM + s_forward_count++, ch[color].red, ch[color].green, ch[color].blue);

		strip.setPixelColor(P_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
		
		strip.setPixelColor(U_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue); 
		strip.setPixelColor(U_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue); 
		
		strip.setPixelColor(D_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue); 
		strip.setPixelColor(D_TOP_CURVE_PIXEL_NUM_START + d_forward_count++, ch[color].red, ch[color].green, ch[color].blue); 
		strip.setPixelColor(D_TOP_CURVE_PIXEL_NUM_START - d_forward_count++, ch[color].red, ch[color].green, ch[color].blue); 
		if(i < 3)
		{
			strip.setPixelColor(S_TOP_PIXEL_NUM - s_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
			strip.setPixelColor(S_TOP_PIXEL_NUM - s_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
		}
		if(i < 5) // midpoint of P vertical section needed
		{
			strip.setPixelColor(P_TOP_CURVE_PIXEL_NUM_START + p_forward_count++, ch[color].red, ch[color].green, ch[color].blue);
			strip.setPixelColor(P_TOP_CURVE_PIXEL_NUM_START + p_forward_count++, ch[color].red, ch[color].green, ch[color].blue); // I assume two to speed up but not checked on sign
		}
		strip.show(); 
	}
}


void fade_word(display_colors_e color, uint16_t delay_time, bool l_to_r)
{
    if(l_to_r)
    {
        fade_letter_l_to_r(S_LETTER, color, delay_time);
        fade_letter_l_to_r(P_LETTER, color, delay_time);
        fade_letter_l_to_r(U_LETTER, color, delay_time);
        fade_letter_l_to_r(D_LETTER, color, delay_time);
    }
    else
    {
        fade_letter_r_to_l(S_LETTER, color, delay_time);
        fade_letter_r_to_l(P_LETTER, color, delay_time);
        fade_letter_r_to_l(U_LETTER, color, delay_time);
        fade_letter_r_to_l(D_LETTER, color, delay_time);
    }
}
















// old functions, new code for SPUD sign below....



/*
#include "nohbz_sign.h"
#include <Adafruit_NeoPixel.h>

#define PIN 12 // SRW changed to test SPUD sign!


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_SIZE, PIN, NEO_GRB + NEO_KHZ800);

uint32_t full_strip_color[num_colors] = {0}; 
colors ch[20]; 

void strip_init(void)
{
	strip.setBrightness(100);
    strip.begin();
    strip.show(); 
    
    ch[black].red = 0;
    ch[black].green = 0;
    ch[black].blue = 0;
    full_strip_color[black] = strip.Color(0, 0, 0);
    ch[white].red = 255;
    ch[white].green = 255;
    ch[white].blue = 255;
    full_strip_color[white] = strip.Color(255, 255, 255);
    ch[red].red = 255;
    ch[red].green = 0;
    ch[red].blue = 0;
    full_strip_color[red] = strip.Color(255, 0, 0);
    ch[blue].red = 0;
    ch[blue].green = 0;
    ch[blue].blue = 255;
    full_strip_color[blue] = strip.Color(0, 0, 255);
    ch[green].red = 0;
    ch[green].green = 255;
    ch[green].blue = 0;
    full_strip_color[green] = strip.Color(0, 255, 0);
    ch[orange].red = 255;
    ch[orange].green = 165;
    ch[orange].blue = 0;++++++
    full_strip_color[orange] = strip.Color(255, 165, 0);
    ch[yellow].red = 255;
    ch[yellow].green = 255;
    ch[yellow].blue = 0;
    full_strip_color[yellow] = strip.Color(255, 255, 0);
    ch[indigo].red = 75;
    ch[indigo].green = 0;
    ch[indigo].blue = 138;
    full_strip_color[indigo] = strip.Color(75, 0, 138);
    ch[violet].red = 238;
    ch[violet].green = 138;
    ch[violet].blue = 238;
    full_strip_color[violet] = strip.Color(238, 138, 238);
    ch[cyan].red = 0;
    ch[cyan].green = 255;
    ch[cyan].blue = 255;
    full_strip_color[cyan] = strip.Color(0, 255, 255);
    ch[magenta].red = 255;
    ch[magenta].green = 0;
    ch[magenta].blue = 255;
    full_strip_color[magenta] = strip.Color(255, 0, 255);
    ch[lime].red = 0;
    ch[lime].green = 255;
    ch[lime].blue = 0;
    full_strip_color[lime] = strip.Color(0, 255, 0);
    ch[maroon].red = 128;
    ch[maroon].green = 0;
    ch[maroon].blue = 0;
    full_strip_color[maroon] = strip.Color(128, 0, 0);
    ch[olive].red = 128;
    ch[olive].green = 128;
    ch[olive].blue = 0;
    full_strip_color[olive] = strip.Color(128, 128, 0);
    ch[chocolate].red = 210;
    ch[chocolate].green = 105;
    ch[chocolate].blue = 30;
    full_strip_color[chocolate] = strip.Color(210, 105, 30);
    ch[gold].red = 255;
    ch[gold].green = 215;
    ch[gold].blue = 0;
    full_strip_color[gold] = strip.Color(255, 215, 30);
    for(int i = 0; i < STRIP_SIZE; i++)
    {
		strip.setPixelColor(i, ch[black].red, ch[black].green, ch[black].blue);
    }
}


void strip_turn_off_pixel(uint16_t pixel)
{
	strip.setPixelColor(pixel, ch[black].red, ch[black].green, ch[black].blue);
	strip.show();
}


void strip_turn_on_pixel(uint16_t pixel, display_colors_e color)
{
	strip.setPixelColor(pixel, ch[color].red, ch[color].green, ch[color].blue);
	strip.show();
}


void show_strip(void)
{
	strip.show();
}


void strip_set_brightness(uint8_t brightness)
{
	strip.setBrightness(brightness);
	strip.begin();
}


letters_in_sign_t draw_letter(letters_in_sign_t letter, color_list_e color)
{
    uint16_t lower_bound = 0;
    uint16_t upper_bound = 0;
    switch(letter)
    {
        case S_LETTER:
            lower_bound = S_PIXEL_NUM_START;
            upper_bound = S_PIXEL_NUM_STOP;
        break;
        case P_LETTER:
            lower_bound = P_PIXEL_NUM_START;
            upper_bound = P_PIXEL_NUM_STOP;
        break;
        case U_LETTER:
            lower_bound = U_PIXEL_NUM_START;
            upper_bound = U_PIXEL_NUM_STOP;
        break;
        case D_LETTER:
            lower_bound = D_PIXEL_NUM_START;
            upper_bound = D_PIXEL_NUM_STOP;
        break;
        default:
            return;
        break;
    }
    for(int i = lower_bound; i <= upper_bound; i++)
    {
        strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    }
    strip.show();
    return letter;
}


void draw_letters(color_list_e color, uint16_t delay_time)
{
    letters_in_sign_t letter = N_LETTER;
    while(D_LETTER != draw_letter(letter, color))
    {
        letter = (uint8_t)letter + 1;
        delay(delay_time);
    }
}


void draw_word(display_colors_e color, uint16_t strip_size, bool spell)
{
	if(!spell) strip.clear();
    for(int i = 0; i < strip_size; i++)
    {
        strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
        if(spell) 
		{
			strip.show();
		}
    }
    strip.show();
}


void blink_word(color_list_e color, uint16_t strip_size, uint16_t delay_time)
{
	strip.fill(full_strip_color[color], 0, strip_size);
	strip.show();
	delay(delay_time);
	strip.clear();
	strip.show();
	delay(delay_time);
}


void fade_letter_l_to_r(letters_in_sign_t letter, color_list_e color, uint16_t delay_time)
{
    switch(letter)
    {
    	case S_LETTER:
			for(int i = 0; i <= S_LEFT_PIXEL_NUM - S_PIXEL_NUM_START; i++)
			{
				delay(delay_time);
				strip.setPixelColor(S_LEFT_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(S_LEFT_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(S_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
			}
			strip.show();
    	break;
    	
    	case P_LETTER:
			for(int i = P_PIXEL_NUM_START; i <= P_POST_PIXEL_NUM_STOP; i++)
    		{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
			strip.show();
			for(int i = 0; i <= P_MIDPOINT_PIXEL_NUM - P_PIXEL_NUM_START; i++)
			{
				delay(delay_time);
				strip.setPixelColor(P_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(P_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
    	break;
    	
    	case U_LETTER:
			// unique doesn't follow above
			for(int i = U_PIXEL_NUM_START; i <= U_PIXEL_NUM_STOP; i++)
			{
				delay(delay_time);
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
    	break;
    	
    	case D_LETTER:
			for(int i = D_PIXEL_NUM_START; i <= D_POST_PIXEL_NUM_STOP; i++)
			{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
			}
			strip.show();
			for(int i = 0; i <= D_RIGHT_PIXEL_NUM - D_TOP_CURVE_PIXEL_NUM_START; i++)
			{
				delay(delay_time);
				strip.setPixelColor(D_TOP_CURVE_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(D_TOP_CURVE_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
    	break;
		
    	default:
    	break;
    }
}


void fade_letter_r_to_l(letters_in_sign_t letter, color_list_e color, uint16_t delay_time)
{
    switch(letter)
    {
		// right to left fade!  
		case S_LETTER:
			for(int i = 0; i <= S_PIXEL_NUM_STOP - S_RIGHT_PIXEL_NUM; i++)
			{
				delay(delay_time);
				strip.setPixelColor(S_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(S_RIGHT_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(S_RIGHT_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
		break;
		
		case P_LETTER:
			for(int i = 0; i <= P_RIGHT_PIXEL_NUM - P_TOP_CURVE_PIXEL_NUM_START; i++)
			{
				delay(delay_time);
				strip.setPixelColor(P_RIGHT_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(P_RIGHT_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
			for(int i = P_PIXEL_NUM_START; i <= P_POST_PIXEL_NUM_STOP; i++)
    		{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
			strip.show();
		break;
		
		case U_LETTER:
			// unique doesn't follow above
			for(int i = U_PIXEL_NUM_STOP; i >= U_PIXEL_NUM_START; i--)
			{
				delay(delay_time);
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
    	break;
		
		case D_LETTER:
			for(int i = 0; i <= D_RIGHT_PIXEL_NUM - D_TOP_CURVE_PIXEL_NUM_START; i++)
			{
				delay(delay_time);
				strip.setPixelColor(D_RIGHT_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(D_RIGHT_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.show();
			}
			for(int i = D_PIXEL_NUM_START; i <= D_POST_PIXEL_NUM_STOP; i++)
			{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
			}
			strip.show();
    	break;
    	default:
    	break;
    }
}


void fade_word_bottom_to_top(color_list_e color, uint16_t delay_time)
{
	// bottom to top.. 
	uint8_t h_tail_count = 0;
	uint8_t b_tail_count = 0;
	uint8_t o_tail_count = 0;
	uint8_t z_tail_count = 0;
	uint8_t n_tail_count = 0;

	for(int i = 0; i <= VERTICAL_POST_NUM_PIXELS; i++)
	{
		delay(delay_time);
		
		if(i < 2)
		{
			
		}
		strip.setPixelColor(S_BOTTOM_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(S_BOTTOM_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue);

		strip.setPixelColor(P_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(P_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(P_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue); // I assume two to speed up but not checked on sign

		strip.setPixelColor(U_BOTTOM_PIXEL_NUM - i, ch[color].red, ch[color].green, ch[color].blue); // I assume two to speed up but not checked on sign
		strip.setPixelColor(U_BOTTOM_PIXEL_NUM + i, ch[color].red, ch[color].green, ch[color].blue); // I assume two to speed up but not checked on sign
		
		strip.setPixelColor(D_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue); // I assume two to speed up but not checked on sign
		strip.setPixelColor(D_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue); // I assume two to speed up but not checked on sign
		
		if(0 == i)
    	{
    		strip.setPixelColor(N_MID_POST_PIXEL_NUM_STOP - n_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		for(int i = 0; i <= Z_POST_LENGTH; i++)
    		{
    			if(i < 5)
    			{
					strip.setPixelColor(B_MID_PIXEL_NUM_STOP - b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
				}
				strip.setPixelColor(Z_BOTTOM_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
    		} 
    		strip.setPixelColor(O_PIXEL_NUM_BOTTOM_LEFT - o_tail_count, ch[color].red, ch[color].green, ch[color].blue);    		
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_RIGHT + o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
    	}
    	else if(i <= 4)
    	{
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_LEFT - o_tail_count, ch[color].red, ch[color].green, ch[color].blue);    		
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_RIGHT + o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_LEFT - o_tail_count, ch[color].red, ch[color].green, ch[color].blue);    		
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_RIGHT + o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
			
			strip.setPixelColor(Z_MID_POST_PIXEL_NUM_STOP - z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
			strip.setPixelColor(Z_MID_POST_PIXEL_NUM_STOP - z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
			strip.setPixelColor(B_MID_PIXEL_NUM_STOP - b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
			strip.setPixelColor(B_MID_PIXEL_NUM_STOP - b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		if(4 == i)
    		{
    			strip.setPixelColor(N_MID_POST_PIXEL_NUM_STOP - n_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(Z_MID_POST_PIXEL_NUM_STOP - z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(Z_MID_POST_PIXEL_NUM_STOP - z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    			for(int i = Z_TOP_POST_PIXEL_NUM_STOP; i >= Z_TOP_POST_PIXEL_NUM_START; i--)
    			{
					strip.setPixelColor(B_MID_PIXEL_NUM_STOP - b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
					strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
					strip.setPixelColor(H_MID_PIXEL_NUM_STOP - h_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    			}
    		}
    	}
    	else if(5 == i)
    	{
    		strip.setPixelColor(O_PIXEL_NUM_BOTTOM_LEFT - o_tail_count, ch[color].red, ch[color].green, ch[color].blue);    		
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_RIGHT + o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
    			
    	}
		else if(VERTICAL_POST_NUM_PIXELS - 1 == i)
		{
    		strip.setPixelColor(N_MID_POST_PIXEL_NUM_STOP - n_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
		}
		
    	strip.show(); 
	}
}


void fade_word_top_to_bottom(color_list_e color, uint16_t delay_time)
{
	// top to bottom..
	uint8_t h_tail_count = 0;
	uint8_t b_tail_count = 0;
	uint8_t o_tail_count = 0;
	uint8_t z_tail_count = 0;
	uint8_t n_tail_count = 0;
	for(int i = 0; i <= VERTICAL_POST_NUM_PIXELS; i++)
	{
		delay(delay_time);
		strip.setPixelColor(N_LEFT_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(N_RIGHT_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
    	strip.setPixelColor(H_LEFT_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(B_LEFT_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(N_MID_POST_PIXEL_NUM_START + n_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
    	if(VERTICAL_POST_NUM_PIXELS == i)
    	{
    		for(int i = Z_BOTTOM_POST_PIXEL_NUM_START; i <= Z_BOTTOM_POST_PIXEL_NUM_STOP; i++)
    		{
    			strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
    		for(int i = B_MID_PIXEL_NUM_START + b_tail_count; i <= B_MID_PIXEL_NUM_STOP; i++)
    		{
    			strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
			strip.setPixelColor(O_PIXEL_NUM_START + o_tail_count, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(O_PIXEL_NUM_STOP - o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(O_PIXEL_NUM_START + o_tail_count, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(O_PIXEL_NUM_STOP - o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		strip.show();
    	}
    	if(i >= TOP_TO_TAIL_NUM_PIXELS)
    	{
    		strip.setPixelColor(H_MID_PIXEL_NUM_START + h_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(B_MID_PIXEL_NUM_START + b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(O_PIXEL_NUM_START + o_tail_count, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(O_PIXEL_NUM_STOP - o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		if(TOP_TO_TAIL_NUM_PIXELS == i)
    		{
				strip.setPixelColor(O_PIXEL_NUM_START + o_tail_count, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(O_PIXEL_NUM_STOP - o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    			for(int i = Z_TOP_POST_PIXEL_NUM_START; i <= Z_TOP_POST_PIXEL_NUM_STOP; i++)
    			{
    				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
				}
				for(int i = B_MID_PIXEL_NUM_START; i <= B_MID_PIXEL_NUM_START + 4; i++)
				{
    				strip.setPixelColor(B_MID_PIXEL_NUM_START + b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
				}
				for(int i = H_MID_PIXEL_NUM_START; i <= H_MID_PIXEL_NUM_START + 4; i++)
				{
    				strip.setPixelColor(H_MID_PIXEL_NUM_START + h_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
				}
			}
			else
			{
				strip.setPixelColor(N_MID_POST_PIXEL_NUM_START + n_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
				strip.setPixelColor(Z_MID_POST_PIXEL_NUM_START + z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(Z_MID_POST_PIXEL_NUM_START + z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
			}
    	}
    	strip.show(); 
	}
}


void fade_word(color_list_e color, uint16_t delay_time, bool l_to_r)
{
    if(l_to_r)
    {
        fade_letter_l_to_r(N_LETTER, color, delay_time);
        fade_letter_l_to_r(O_LETTER, color, delay_time);
        fade_letter_l_to_r(H_LETTER, color, delay_time);
        fade_letter_l_to_r(B_LETTER, color, delay_time);
        fade_letter_l_to_r(Z_LETTER, color, delay_time);
    }
    else
    {
        fade_letter_r_to_l(Z_LETTER, color, delay_time);
        fade_letter_r_to_l(B_LETTER, color, delay_time);
        fade_letter_r_to_l(H_LETTER, color, delay_time);
        fade_letter_r_to_l(O_LETTER, color, delay_time);
        fade_letter_r_to_l(N_LETTER, color, delay_time);
    }
}

*/

