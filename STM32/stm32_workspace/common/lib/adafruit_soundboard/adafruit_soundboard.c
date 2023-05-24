#include "config.h"

#if defined(BOARD_MN_WILD_SOUND)

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "numbers.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "board_init_common.h"
#include "adafruit_soundboard.h"


#define ADAFRUIT_VOLUME_MIN_MAX_ITERATIONS                  (uint8_t)(10)
#define ADAFRUIT_SOUNDBOARD_RESET_TIME_MILLISECONDS         1000
#define ADAFRUIT_SOUNDBOARD_VOLUME_DELAY_MILLISECONDS       200


static void adafruit_soundboard_power_enable_disable(adafruit_soundboard_power_enable_disable_e enable_disable)
{
    board_init_adafruit_soundboard_power_enable_disable(enable_disable);
}


static void adafruit_soundboard_trigger_enable_disable(adafruit_soundboard_trig_e trigger,
                                                       adafruit_soundboard_trig_enable_disable_e enable_disable)
{
    board_init_adafruit_soundboard_trigger(trigger, enable_disable);
}


static void adafruit_soundboard_reset_enable_disable(adafruit_soundboard_reset_e enable_disable)
{
    board_init_adafruit_reset(enable_disable);
}


static void adafruit_soundboard_mode(adafruit_soundboard_mode_e mode)
{
    board_init_adafruit_soundboard_enable_mode(mode);
    adafruit_soundboard_reset_enable();
    osDelay(ADAFRUIT_SOUNDBOARD_RESET_TIME_MILLISECONDS);
    adafruit_soundboard_reset_disable();
}


static void adafruit_soundboard_adjust_volume(adafruit_soundboard_volume_e volume)
{
    board_init_adafruit_soundboard_adjust_volume(volume);
    osDelay(ADAFRUIT_SOUNDBOARD_VOLUME_DELAY_MILLISECONDS);
    board_init_adafruit_soundboard_adjust_volume(ADAFRUIT_SOUNDBOARD_VOLUME_RELEASE);
    osDelay(ADAFRUIT_SOUNDBOARD_VOLUME_DELAY_MILLISECONDS);

}


static void adafruit_soundboard_enable_disable_relay(adafruit_soundboard_relay_e relay,
                                                     adafruit_soundboard_relay_enable_disable_e enable_disable)
{
    if (ADAFRUIT_SOUNDBOARD_RELAY_ENABLE == enable_disable)
    {
        board_init_adafruit_soundboard_enable_relay(relay);
    }
    else
    {
        board_init_adafruit_soundboard_disable_relay(relay);
    }
}


void adafruit_soundboard_init(void)
{
    adafruit_soundboard_disable_relay(ADAFRUIT_SOUNDBOARD_RELAY_SOUND_CTRL);
    adafruit_soundboard_disable_relay(ADAFRUIT_SOUNDBOARD_RELAY_LIGHT_CTRL);
    adafruit_soundboard_is_playing_audio(); // this sets up the pin as input
    adafruit_soundboard_adjust_volume(ADAFRUIT_SOUNDBOARD_VOLUME_RELEASE); // this will release both volume up and down
    adafruit_soundboard_enable_gpio_mode(); // not UART mode..
    for (adafruit_soundboard_trig_e trig = ADAFRUIT_SOUNDBOARD_TRIG_0; trig < NUM_ADAFRUIT_SOUNDBOARD_TRIG; trig = (adafruit_soundboard_trig_e)(trig + 1))
    {
        adafruit_soundboard_trigger_enable_disable(trig, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
    }
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_0, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_1, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_2, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_3, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_4, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_5, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_6, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_7, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_8, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_9, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
//    adafruit_soundboard_trigger_enable_disable(ADAFRUIT_SOUNDBOARD_TRIG_10, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
}


void adafruit_soundboard_power_enable(void)
{
    adafruit_soundboard_power_enable_disable(ADAFRUIT_SOUNDBOARD_POWER_ENABLE);
}


void adafruit_soundboard_power_disable(void)
{
    adafruit_soundboard_power_enable_disable(ADAFRUIT_SOUNDBOARD_POWER_DISABLE);
}


void adafruit_soundboard_trigger_enable(adafruit_soundboard_trig_e trigger)
{
    adafruit_soundboard_trigger_enable_disable(trigger, ADAFRUIT_SOUNDBOARD_TRIG_ENABLE);
}


void adafruit_soundboard_trigger_disable(adafruit_soundboard_trig_e trigger)
{
    adafruit_soundboard_trigger_enable_disable(trigger, ADAFRUIT_SOUNDBOARD_TRIG_DISABLE);
}


void adafruit_soundboard_reset_enable(void)
{
    adafruit_soundboard_reset_enable_disable(ADAFRUIT_SOUNDBOARD_RESET_ENABLE);
}


void adafruit_soundboard_reset_disable(void)
{
    adafruit_soundboard_reset_enable_disable(ADAFRUIT_SOUNDBOARD_RESET_DISABLE);
}


bool adafruit_soundboard_is_playing_audio(void)
{
    return board_init_adafruit_soundboard_is_playing_audio();
}


void adafruit_soundboard_enable_uart_mode(void)
{
    adafruit_soundboard_mode(ADAFRUIT_SOUNDBOARD_UART_MODE);
}


void adafruit_soundboard_enable_gpio_mode(void)
{
    adafruit_soundboard_mode(ADAFRUIT_SOUNDBOARD_GPIO_MODE);
}


void adafruit_soundboard_adjust_volume_down(void)
{
    adafruit_soundboard_adjust_volume(ADAFRUIT_SOUNDBOARD_VOLUME_DOWN);
}


void adafruit_soundboard_adjust_volume_up(void)
{
    adafruit_soundboard_adjust_volume(ADAFRUIT_SOUNDBOARD_VOLUME_UP);
}


void adafruit_soundboard_set_volume_max(void)
{
    for (uint8_t iii = 0; iii < ADAFRUIT_VOLUME_MIN_MAX_ITERATIONS; iii++)
    {
        adafruit_soundboard_adjust_volume_up();
    }
}


void adafruit_soundboard_set_volume_min(void)
{
    for (uint8_t iii = 0; iii < ADAFRUIT_VOLUME_MIN_MAX_ITERATIONS; iii++)
    {
        adafruit_soundboard_adjust_volume_down();
    }
}


void adafruit_soundboard_enable_relay(adafruit_soundboard_relay_e relay)
{
    adafruit_soundboard_enable_disable_relay(relay, ADAFRUIT_SOUNDBOARD_RELAY_ENABLE);
}


void adafruit_soundboard_disable_relay(adafruit_soundboard_relay_e relay)
{
    adafruit_soundboard_enable_disable_relay(relay, ADAFRUIT_SOUNDBOARD_RELAY_DISABLE);
}


#endif


