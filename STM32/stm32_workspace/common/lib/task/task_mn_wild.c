// SRW

#if 0

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32l4xx_hal.h"
#include "board_common.h"
#include "board_init_common.h"
#include "board_specific.h"
#include "cmsis_os.h"
#include "adafruit_soundboard.h"
#include "task_mn_wild.h"


task_mn_wild_state_e g_task_mn_wild_state = TASK_MN_WILD_STATE_IDLE;


static void task_mn_wild_init(void)
{
    board_init_green_led_on();
    adafruit_soundboard_power_enable();
    osDelay(500);
    adafruit_soundboard_reset_enable();
    osDelay(100);
    adafruit_soundboard_reset_disable();
    osDelay(100);
    adafruit_soundboard_init();
    board_init_green_led_off();
    adafruit_soundboard_enable_relay(ADAFRUIT_SOUNDBOARD_RELAY_SOUND_CTRL);
}


task_mn_wild_state_e task_mn_wild_state(void)
{
    return g_task_mn_wild_state;
}


void task_mn_wild_enter_idle(void)
{
    g_task_mn_wild_state = TASK_MN_WILD_STATE_IDLE;
}


static void task_mn_wild_play_sound(void)
{
    adafruit_soundboard_trigger_enable(ADAFRUIT_SOUNDBOARD_TRIG_1);
    osDelay(250);
    adafruit_soundboard_trigger_disable(ADAFRUIT_SOUNDBOARD_TRIG_1);
    adafruit_soundboard_enable_relay(ADAFRUIT_SOUNDBOARD_RELAY_LIGHT_CTRL);
}


void task_mn_wild(void *argument)
{
    uint32_t button_pressed_bit = 0;
    task_mn_wild_init();

    while (1)
    {
        // TODO add debounce for the switch!
        xTaskNotifyWait(0, button_pressed_bit, &button_pressed_bit, portMAX_DELAY);
        g_task_mn_wild_state = TASK_MN_WILD_STATE_ACTIVE;
        task_mn_wild_play_sound();
        while (adafruit_soundboard_is_playing_audio() && (TASK_MN_WILD_STATE_ACTIVE == g_task_mn_wild_state))
        {
            osDelay(100);
        }
        if (TASK_MN_WILD_STATE_IDLE == g_task_mn_wild_state)
        {
            adafruit_soundboard_reset_enable();
            adafruit_soundboard_disable_relay(ADAFRUIT_SOUNDBOARD_RELAY_LIGHT_CTRL);
            adafruit_soundboard_disable_relay(ADAFRUIT_SOUNDBOARD_RELAY_SOUND_CTRL);
            osDelay(1000);
            adafruit_soundboard_reset_disable();
            adafruit_soundboard_enable_relay(ADAFRUIT_SOUNDBOARD_RELAY_SOUND_CTRL); // leave sound enabled
        }
        else
        {
            g_task_mn_wild_state = TASK_MN_WILD_STATE_IDLE;
        }
        adafruit_soundboard_disable_relay(ADAFRUIT_SOUNDBOARD_RELAY_LIGHT_CTRL); // leave sound enabled
    }
}



#endif