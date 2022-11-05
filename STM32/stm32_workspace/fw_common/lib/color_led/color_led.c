#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "numbers.h"
#include "task_led_ctrl.h"

color_hex_code_e g_color_hex_codes[NUM_COLORS];


void color_led_init(void)
{
    // initialize color arrays
    g_color_hex_codes[COLORS_RED] = COLOR_HEX_RED;
    g_color_hex_codes[COLORS_LIME] = COLOR_HEX_LIME;
    g_color_hex_codes[COLORS_BLUE] = COLOR_HEX_BLUE;
    g_color_hex_codes[COLORS_YELLOW] = COLOR_HEX_YELLOW;
    g_color_hex_codes[COLORS_CYAN] = COLOR_HEX_CYAN;
    g_color_hex_codes[COLORS_MAGENTA] = COLOR_HEX_MAGENTA;
    g_color_hex_codes[COLORS_GREEN] = COLOR_HEX_GREEN;
    g_color_hex_codes[COLORS_PURPLE] = COLOR_HEX_PURPLE;
    g_color_hex_codes[COLORS_TEAL] = COLOR_HEX_TEAL;
    g_color_hex_codes[COLORS_NAVY] = COLOR_HEX_NAVY;
    g_color_hex_codes[COLORS_ORANGE_RED] = COLOR_HEX_ORANGE_RED;
    g_color_hex_codes[COLORS_ORANGE] = COLOR_HEX_ORANGE;
    g_color_hex_codes[COLORS_KHAKI] = COLOR_HEX_KHAKI;
    g_color_hex_codes[COLORS_LAWN_GREEN] = COLOR_HEX_LAWN_GREEN;
    g_color_hex_codes[COLORS_SPRING_GREEN] = COLOR_HEX_SPRING_GREEN;
    g_color_hex_codes[COLORS_MIDNIGHT_BLUE] = COLOR_HEX_MIDNIGHT_BLUE;
    g_color_hex_codes[COLORS_BLUE_VIOLET] = COLOR_HEX_BLUE_VIOLET;
    g_color_hex_codes[COLORS_DARK_MAGENTA] = COLOR_HEX_DARK_MAGENTA;
    g_color_hex_codes[COLORS_HOT_PINK] = COLOR_HEX_HOT_PINK;
    g_color_hex_codes[COLORS_MINT] = COLOR_HEX_MINT;
    //g_color_hex_codes[COLORS_GRAY] = COLOR_HEX_GRAY;
    g_color_hex_codes[COLORS_BROWN] = COLOR_HEX_BROWN;
}


void color_led_hex_to_rgb(color_hex_code_e color, uint8_t *color_array)
{
    uint8_t red, green, blue;
    color_array[offsetof(ws2812b_led_t, red)] = ((color & 0xFF0000) >> (BITS_PER_BYTE * (2 - offsetof(ws2812b_led_t, red))));
    color_array[offsetof(ws2812b_led_t, green)] = ((color & 0xFF0000) >> (BITS_PER_BYTE * (2 - offsetof(ws2812b_led_t, green))));
    color_array[offsetof(ws2812b_led_t, blue)] = ((color & 0xFF0000) >> (BITS_PER_BYTE * (2 - offsetof(ws2812b_led_t, blue))));
}

