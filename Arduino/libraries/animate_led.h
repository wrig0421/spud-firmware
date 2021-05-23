#include <stdint.h>
#include <stdbool.h>


void animate_led_adjust_speed(void);
void animate_led_adjust_state(void);
void animate_led_increment_iterations(void);
uint32_t animate_led_iterations(void);
led_state_e animate_led_state(void);
void show_strip(void);
void set_pixel(int Pixel, byte red, byte green, byte blue);
void set_all_pixels(byte red, byte green, byte blue);
void animate_led_state_randomize(void);
void fade_in_fade_out(color_hex_code_e color);
void strobe(color_hex_code_e color, uint16_t strobe_count, uint16_t flash_delay, uint16_t end_pause);
void cyclone_bounce(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void new_kitt(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void center_to_outside(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void outside_to_center(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void left_to_right(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void right_to_left(color_hex_code_e color, uint16_t eye_size, uint16_t speed_delay, uint16_t return_delay);
void twinkle(color_hex_code_e color, uint16_t count, uint16_t speed_delay, bool only_one);
void twinkle_random(uint16_t count, uint16_t speed_delay, bool only_one);
void sparkle(color_hex_code_e color, uint16_t speed_delay);
void running_lights(color_hex_code_e color, uint16_t wave_delay);
void color_wipe(color_hex_code_e color, uint16_t speed_delay);
void rainbow_cycle(uint16_t speed_delay);
byte* wheel(byte wheel_pos);
void theater_chase(color_hex_code_e color, uint16_t speed_delay);
void theater_chase_rainbow(uint16_t speed_delay);
void bouncing_balls(color_hex_code_e color, int ball_count);
void meteor_rain(color_hex_code_e color, byte meteor_size, byte meteor_trail_decay, bool meteor_random_decay, int speed_delay);
void fade_to_black(int led_no, byte fade_value);
