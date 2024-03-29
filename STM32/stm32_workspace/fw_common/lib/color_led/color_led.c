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
}


