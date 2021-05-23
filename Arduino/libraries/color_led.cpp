#include "color_led_.h"

color_hex_code_e g_color_hex_codes[NUM_COLORS] = {0};


all_colors_e g_led_color = COLORS_RED;






void color_led_init(void)
{
	// initialize color arrays
    g_color_hex_codes[DISP_COLOR_RED] = COLOR_HEX_RED;
    g_color_hex_codes[DISP_COLOR_LIME] = COLOR_HEX_LIME;
    g_color_hex_codes[DISP_COLOR_BLUE] = COLOR_HEX_BLUE;
    g_color_hex_codes[DISP_COLOR_YELLOW] = COLOR_HEX_YELLOW;
    g_color_hex_codes[DISP_COLOR_CYAN] = COLOR_HEX_CYAN;
    g_color_hex_codes[DISP_COLOR_MAGENTA] = COLOR_HEX_MAGENTA;
    g_color_hex_codes[DISP_COLOR_GREEN] = COLOR_HEX_GREEN;
    g_color_hex_codes[DISP_COLOR_PURPLE] = COLOR_HEX_PURPLE;
    g_color_hex_codes[DISP_COLOR_TEAL] = COLOR_HEX_TEAL;
    g_color_hex_codes[DISP_COLOR_NAVY] = COLOR_HEX_NAVY;
    /*
    g_colors[COLORS_BLACK] = COLOR_HEX_BLACK;
    g_colors[COLORS_WHITE] = COLOR_HEX_WHITE;
    g_colors[COLORS_RED] = COLOR_HEX_RED;
    g_colors[COLORS_LIME] = COLOR_HEX_LIME;
    g_colors[COLORS_BLUE] = COLOR_HEX_BLUE;
    g_colors[COLORS_YELLOW] = COLOR_HEX_YELLOW;
    g_colors[COLORS_CYAN] = COLOR_HEX_CYAN;
    g_colors[COLORS_MAGENTA] = COLOR_HEX_MAGENTA;
    g_colors[COLORS_SILVER] = COLOR_HEX_SILVER;
    g_colors[COLORS_GRAY] = COLOR_HEX_GRAY;
    g_colors[COLORS_MAROON] = COLOR_HEX_MAROON;
    g_colors[COLORS_OLIVE] = COLOR_HEX_OLIVE;
    g_colors[COLORS_GREEN] = COLOR_HEX_GREEN;
    g_colors[COLORS_PURPLE] = COLOR_HEX_PURPLE;
    g_colors[COLORS_TEAL] = COLOR_HEX_TEAL;
    g_colors[COLORS_NAVY] = COLOR_HEX_NAVY;
	*/
}


void color_led_adjust_color(void)
{
	if (COLORS_LAST == g_led_color) g_led_color = COLORS_FIRST;
	else g_led_color = (all_colors_e) (g_led_color + 1);
}


color_hex_e color_led_cur_color_hex(void)
{
	return g_color_hex_codes[g_led_color];
}


color_hex_code_e color_led_hex(all_colors_e color)
{
	return g_color_hex_codes[color];
}

void color_led_randomize(void)
{
	all_colors_e color = (all_colors_e)(random(NUM_COLORS));
	if (g_led_color == color)
    {
        if ((NUM_COLORS - 1) == color) g_led_color = (all_colors_e)(color - 1);
        else g_led_color = (all_colors_e)(color + 1);
    }
}

/*
color_hex_code_e color_led_random(all_colors_e cur_color)
{
    all_colors_e color = (all_colors_e)(random(COLORS_NAVY));
    if (cur_color == color)
    {
        if ((NUM_COLORS - 1) == color) color = (all_colors_e)(color - 1);
        {
            
        }
        else color = (all_colors_e)(color + 1);
    }
	return g_color_hex_codes[color];
}
*/
