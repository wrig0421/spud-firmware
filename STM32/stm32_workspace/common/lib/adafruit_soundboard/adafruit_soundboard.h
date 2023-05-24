#if !defined(ADAFRUIT_SOUNDBOARD_H)
#define ADAFRUIT_SOUNDBOARD_H

#include "config.h"

#   if defined(BOARD_MN_WILD_SOUND)


typedef enum
{
    ADAFRUIT_SOUNDBOARD_TRIG_0 = 0,
    ADAFRUIT_SOUNDBOARD_TRIG_1,
    ADAFRUIT_SOUNDBOARD_TRIG_2,
    ADAFRUIT_SOUNDBOARD_TRIG_3,
    ADAFRUIT_SOUNDBOARD_TRIG_4,
    ADAFRUIT_SOUNDBOARD_TRIG_5,
    ADAFRUIT_SOUNDBOARD_TRIG_6,
    ADAFRUIT_SOUNDBOARD_TRIG_7,
    ADAFRUIT_SOUNDBOARD_TRIG_8,
    ADAFRUIT_SOUNDBOARD_TRIG_9,
    ADAFRUIT_SOUNDBOARD_TRIG_10,
    NUM_ADAFRUIT_SOUNDBOARD_TRIG
} adafruit_soundboard_trig_e;


typedef enum
{
    ADAFRUIT_SOUNDBOARD_TRIG_ENABLE = 0,
    ADAFRUIT_SOUNDBOARD_TRIG_DISABLE
} adafruit_soundboard_trig_enable_disable_e;


typedef enum
{
    ADAFRUIT_SOUNDBOARD_UART_MODE = 0,
    ADAFRUIT_SOUNDBOARD_GPIO_MODE
} adafruit_soundboard_mode_e;


typedef enum
{
    ADAFRUIT_SOUNDBOARD_RESET_ENABLE = 0,
    ADAFRUIT_SOUNDBOARD_RESET_DISABLE
} adafruit_soundboard_reset_e;


typedef enum
{
    ADAFRUIT_SOUNDBOARD_VOLUME_UP = 0,
    ADAFRUIT_SOUNDBOARD_VOLUME_DOWN,
    ADAFRUIT_SOUNDBOARD_VOLUME_RELEASE
} adafruit_soundboard_volume_e;


typedef enum
{
    ADAFRUIT_SOUNDBOARD_POWER_ENABLE = 0,
    ADAFRUIT_SOUNDBOARD_POWER_DISABLE
} adafruit_soundboard_power_enable_disable_e;


typedef enum
{
    ADAFRUIT_SOUNDBOARD_RELAY_LIGHT_CTRL = 0,
    ADAFRUIT_SOUNDBOARD_RELAY_SOUND_CTRL
} adafruit_soundboard_relay_e;


typedef enum
{
    ADAFRUIT_SOUNDBOARD_RELAY_ENABLE = 0,
    ADAFRUIT_SOUNDBOARD_RELAY_DISABLE
} adafruit_soundboard_relay_enable_disable_e;


void adafruit_soundboard_init(void);
void adafruit_soundboard_power_enable(void);
void adafruit_soundboard_power_disable(void);
void adafruit_soundboard_trigger_enable(adafruit_soundboard_trig_e trigger);
void adafruit_soundboard_trigger_disable(adafruit_soundboard_trig_e trigger);
void adafruit_soundboard_reset_enable(void);
void adafruit_soundboard_reset_disable(void);
bool adafruit_soundboard_is_playing_audio(void);
void adafruit_soundboard_enable_uart_mode(void);
void adafruit_soundboard_enable_gpio_mode(void);
void adafruit_soundboard_adjust_volume_down(void);
void adafruit_soundboard_adjust_volume_up(void);
void adafruit_soundboard_set_volume_max(void);
void adafruit_soundboard_set_volume_min(void);
void adafruit_soundboard_enable_relay(adafruit_soundboard_relay_e relay);
void adafruit_soundboard_disable_relay(adafruit_soundboard_relay_e relay);

    #endif

#endif


