// SRW

#if !defined(BOARD_INIT_COMMON_H)
#define BOARD_INIT_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32l4xx_hal.h"

#include "adafruit_soundboard.h"

typedef enum
{
    PUSH_BUTTON_A = 0,
    PUSH_BUTTON_B,
    PUSH_BUTTON_C,
    PUSH_BUTTON_D,
    NUM_PUSH_BUTTONS,
} board_init_push_buttons_e;


void board_init_adafruit_soundboard_enable_relay(adafruit_soundboard_relay_e relay);
void board_init_adafruit_soundboard_disable_relay(adafruit_soundboard_relay_e relay);

void board_init_adafruit_reset(adafruit_soundboard_reset_e reset);
bool board_init_adafruit_soundboard_is_playing_audio(void);
void board_init_adafruit_soundboard_adjust_volume(adafruit_soundboard_volume_e volume);
void board_init_adafruit_soundboard_power_enable_disable(adafruit_soundboard_power_enable_disable_e enable_disable);
void board_init_adafruit_soundboard_enable_mode(adafruit_soundboard_mode_e mode);
void board_init_adafruit_soundboard_trigger(adafruit_soundboard_trig_e trigger,
                                            adafruit_soundboard_trig_enable_disable_e enable_disable);

void board_init_common_board_init(void);
void board_init_common_button_pressed(const board_init_push_buttons_e button);
void board_init_common_stop_timer(void);

void board_init_red_led_on(void);
void board_init_red_led_off(void);
void board_init_green_led_on(void);
void board_init_green_led_off(void);

void board_init_adafruit_soundboard_trigger(adafruit_soundboard_trig_e trigger,
                                            adafruit_soundboard_trig_enable_disable_e enable_disable);
void board_init_setup_gpio_input_no_pull(GPIO_TypeDef* port, uint16_t pin);

#endif