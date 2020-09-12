#include <Adafruit_NeoPixel.h>

#define PIN 7
#define NEW_PIN 13            
#define STRIP_SIZE  31  // 31 pixels per strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_SIZE, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(STRIP_SIZE, NEW_PIN, NEO_GRB + NEO_KHZ800);


struct colors {

  uint8_t red;
  uint8_t green;
  uint8_t blue;
};


typedef enum
{
    STATE_RAINBOW,
} sign_state_t;


typedef enum
{
    black = 0,
    white,
    red,
    blue,
    green,
    orange,
    yellow,
    indigo,
    violet,
    cyan,
    magenta,
    lime,
    maroon,
    olive,
    chocolate,
    gold,
} color_list_e;


colors ch[20];
sign_state_t sign_state = STATE_RAINBOW; 
color_list_e c1 = blue;
color_list_e c2 = red;
color_list_e c3 = green;
color_list_e c4 = indigo;
uint8_t i = 0;

void set_all_pixels(color_list_e color);


void init_colors(void) {
    // black
    ch[0].red = 0;
    ch[0].green = 0;
    ch[0].blue = 0;
    // white  
    ch[1].red = 255;
    ch[1].green = 255;
    ch[1].blue = 255;
    // red
    ch[2].red = 255;
    ch[2].green = 0;
    ch[2].blue = 0;
    // blue
    ch[3].red = 0;
    ch[3].green = 0;
    ch[3].blue = 255;
    // green
    ch[4].red = 0;
    ch[4].green = 255;
    ch[4].blue = 0;
    // orange
    ch[5].red = 255;
    ch[5].green = 165;
    ch[5].blue = 0;
    // yellow
    ch[6].red = 255;
    ch[6].green = 255;
    ch[6].blue = 0;
    // indigo
    ch[7].red = 75;
    ch[7].green = 0;
    ch[7].blue = 138;
    // violet
    ch[8].red = 238;
    ch[8].green = 138;
    ch[8].blue = 238;
    // cyan
    ch[9].red = 0;
    ch[9].green = 255;
    ch[9].blue = 255;
    // magenta
    ch[10].red = 255;
    ch[10].green = 0;
    ch[10].blue = 255;
    // lime
    ch[11].red = 0;
    ch[11].green = 255;
    ch[11].blue = 0;
    // maroon
    ch[12].red = 128;
    ch[12].green = 0;
    ch[12].blue = 0;
    // olive
    ch[13].red = 128;
    ch[13].green = 128;
    ch[13].blue = 0;
    // chocolate
    ch[14].red = 210;
    ch[14].green = 105;
    ch[14].blue = 30;
    // gold
    ch[15].red = 255;
    ch[15].green = 215;
    ch[15].blue = 0;
    for(int i = 0; i < STRIP_SIZE; i++)
    {
        strip.setPixelColor(i, ch[black].red, ch[black].green, ch[black].blue);
        strip_2.setPixelColor(i, ch[black].red, ch[black].green, ch[black].blue);
    }
}


void set_all_pixels(color_list_e color)
{
    for(int i = 0; i < 144; i++)
    {
        strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
        strip_2.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    }
}


void setup(void) 
{
    strip.setBrightness(100);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    strip_2.setBrightness(100);
    strip_2.begin();
    strip_2.show();
    init_colors();
}


void loop(void) 
{
    switch(sign_state)
    {
        case STATE_RAINBOW:
                if (i < (STRIP_SIZE / 4))
                {
                    strip.setPixelColor(i, ch[c1].red, ch[c1].green, ch[c1].blue);
                    strip_2.setPixelColor(i, ch[c1].red, ch[c1].green, ch[c1].blue);
                    strip.setPixelColor(i + (STRIP_SIZE / 4), ch[c2].red, ch[c2].green, ch[c2].blue);
                    strip_2.setPixelColor(i + (STRIP_SIZE / 4), ch[c2].red, ch[c2].green, ch[c2].blue);
                    strip.setPixelColor(i + 2*(STRIP_SIZE / 4), ch[c3].red, ch[c3].green, ch[c3].blue);
                    strip_2.setPixelColor(i + 2*(STRIP_SIZE / 4), ch[c3].red, ch[c3].green, ch[c3].blue);
                    strip.setPixelColor(i + 3*(STRIP_SIZE / 4), ch[c4].red, ch[c4].green, ch[c4].blue);
                    strip_2.setPixelColor(i + 3*(STRIP_SIZE / 4), ch[c4].red, ch[c4].green, ch[c4].blue);
                }
                else if ((i >= (STRIP_SIZE / 4)) && (i < 2*(STRIP_SIZE / 4)))
                {
                    strip.setPixelColor(i - (STRIP_SIZE / 4), ch[c4].red, ch[c4].green, ch[c4].blue);
                    strip_2.setPixelColor(i - (STRIP_SIZE / 4), ch[c4].red, ch[c4].green, ch[c4].blue);
                    strip.setPixelColor(i, ch[c1].red, ch[c1].green, ch[c1].blue);
                    strip_2.setPixelColor(i, ch[c1].red, ch[c1].green, ch[c1].blue);
                    strip.setPixelColor(i + (STRIP_SIZE / 4), ch[c2].red, ch[c2].green, ch[c2].blue);
                    strip_2.setPixelColor(i + (STRIP_SIZE / 4), ch[c2].red, ch[c2].green, ch[c2].blue);
                    strip.setPixelColor(i + 2*(STRIP_SIZE / 4), ch[c3].red, ch[c3].green, ch[c3].blue);
                    strip_2.setPixelColor(i + 2*(STRIP_SIZE / 4), ch[c3].red, ch[c3].green, ch[c3].blue);
                }
                else if ((i >= 2*(STRIP_SIZE / 4)) && (i < 3*(STRIP_SIZE / 4)))
                {
                    strip.setPixelColor(i - 2*(STRIP_SIZE / 4), ch[c3].red, ch[c3].green, ch[c3].blue);
                    strip_2.setPixelColor(i - 2*(STRIP_SIZE / 4), ch[c3].red, ch[c3].green, ch[c3].blue);
                    strip.setPixelColor(i - (STRIP_SIZE / 4), ch[c4].red, ch[c4].green, ch[c4].blue);
                    strip_2.setPixelColor(i - (STRIP_SIZE / 4), ch[c4].red, ch[c4].green, ch[c4].blue);
                    strip.setPixelColor(i, ch[c1].red, ch[c1].green, ch[c1].blue);
                    strip_2.setPixelColor(i, ch[c1].red, ch[c1].green, ch[c1].blue);
                    strip.setPixelColor(i + (STRIP_SIZE / 4), ch[c2].red, ch[c2].green, ch[c2].blue);
                    strip_2.setPixelColor(i + (STRIP_SIZE / 4), ch[c2].red, ch[c2].green, ch[c2].blue);
                }
                else
                {
                    strip.setPixelColor(i - 3*(STRIP_SIZE / 4), ch[c2].red, ch[c2].green, ch[c2].blue);
                    strip_2.setPixelColor(i - 3*(STRIP_SIZE / 4), ch[c2].red, ch[c2].green, ch[c2].blue);
                    strip.setPixelColor(i - 2*(STRIP_SIZE / 4), ch[c3].red, ch[c3].green, ch[c3].blue);
                    strip_2.setPixelColor(i - 2*(STRIP_SIZE / 4), ch[c3].red, ch[c3].green, ch[c3].blue);
                    strip.setPixelColor(i - (STRIP_SIZE / 4), ch[c4].red, ch[c4].green, ch[c4].blue);
                    strip_2.setPixelColor(i - (STRIP_SIZE / 4), ch[c4].red, ch[c4].green, ch[c4].blue);
                    strip.setPixelColor(i, ch[c1].red, ch[c1].green, ch[c1].blue);
                    strip_2.setPixelColor(i, ch[c1].red, ch[c1].green, ch[c1].blue);
                }
                strip.show();
                strip_2.show();
                delay(50);
                i++;
                if (i > STRIP_SIZE) i = 3;
        break;
        default:
        break;
    }
}