/*
 * task_pin_level_count.c
 *
 *  Created on: Jul 31, 2022
 *      Author: splat
 */
#include "cmsis_os.h"
#include "board_init.h"
#include "task_pin_level_count.h"


void task_pin_level_count(void *argument)
{
    while (1)
    {
        if (board_init_button_is_pressed(PUSH_BUTTON_A)) board_init_button_on_count_increment(PUSH_BUTTON_A);
        else if (board_init_button_is_pressed(PUSH_BUTTON_B)) board_init_button_on_count_increment(PUSH_BUTTON_B);
        else if (board_init_button_is_pressed(PUSH_BUTTON_C)) board_init_button_on_count_increment(PUSH_BUTTON_C);
        else if (board_init_button_is_pressed(PUSH_BUTTON_D)) board_init_button_on_count_increment(PUSH_BUTTON_D);
        osDelay(100);
    }

}
