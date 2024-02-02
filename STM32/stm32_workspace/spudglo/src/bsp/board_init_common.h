// SRW

#if !defined(BOARD_INIT_COMMON_H)
#define BOARD_INIT_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include "board_common.h"
#include "board_specific.h"

typedef enum
{
    PUSH_BUTTON_A = 0,
    PUSH_BUTTON_B,
    PUSH_BUTTON_C,
    PUSH_BUTTON_D,
    NUM_PUSH_BUTTONS
} board_init_push_buttons_e;


// A EXTI2
// B EXTI15_10
// C EXTI 9_5
// D EXTI 0

typedef enum
{
	// this needs to be IRQ or something but at COMPILE TIME :(
    PUSH_BUTTON_A_PIN = GPIO_PIN_2,//PIN_WKUP_4, // PA2
    PUSH_BUTTON_B_PIN = GPIO_PIN_13,// PIN_WKUP_2, // PC13
    PUSH_BUTTON_C_PIN = GPIO_PIN_5, //PIN_WKUP_3, // PC5
    PUSH_BUTTON_D_PIN = GPIO_PIN_0 //PIN_WKUP_1 // PA0
} board_init_push_button_pin_e;


typedef enum
{
#if defined(BOARD_SPUDGLO_V5)
    PUSH_BUTTON_A_IRQ = EXTI9_5_IRQn, //PIN_WKUP_4_IRQ, // EXTI2_IRQn
    PUSH_BUTTON_B_IRQ = EXTI15_10_IRQn, //PIN_WKUP_2_IRQ, // EXTI15_10_IRQn
    PUSH_BUTTON_C_IRQ = EXTI0_IRQn, //PIN_WKUP_3_IRQ, // EXTI9_5_IRQn
    PUSH_BUTTON_D_IRQ = EXTI2_IRQn //PIN_WKUP_1_IRQ // EXTI0_IRQn
#else
    PUSH_BUTTON_A_IRQ = EXTI2_IRQn, //PIN_WKUP_4_IRQ, // EXTI2_IRQn
    PUSH_BUTTON_B_IRQ = EXTI15_10_IRQn, //PIN_WKUP_2_IRQ, // EXTI15_10_IRQn
    PUSH_BUTTON_C_IRQ = EXTI9_5_IRQn, //PIN_WKUP_3_IRQ, // EXTI9_5_IRQn
    PUSH_BUTTON_D_IRQ = EXTI0_IRQn //PIN_WKUP_1_IRQ // EXTI0_IRQn
#endif
} board_init_push_button_irq_e;


void board_init_common_board_init(void);
void board_init_common_button_pressed(const board_init_push_buttons_e button);
void board_init_common_stop_timer(void);

void board_init_red_led_on(void);
void board_init_red_led_off(void);
void board_init_green_led_on(void);
void board_init_green_led_off(void);

#endif
