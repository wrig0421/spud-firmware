// SRW
#if !defined(UART_CONFIG_SPUDGLO_V5_H)
#include "config.h"
#include "gpio_config_hal.h"
#include "stm32l4xx_hal.h"
#define GPIO_CONFIG_SPUDGLO_V5_H

#define PIN_WKUP1               PIOA_PIN_0
#define PIN_ESP8266_SCK         PIOA_PIN_1
#define PIN_WKUP4               PIOA_PIN_2

#define PIN_ESP8266_CSN         PIOA_PIN_4
#define PIN_ESP8266_GPIO0       PIOA_PIN_5
#define PIN_ESP8266_EN          PIOA_PIN_6
#define PIN_ESP8266_RST         PIOA_PIN_7
#define PIN_TIM1_CH1            PIOA_PIN_8
#define PIN_TIM1_CH2            PIOA_PIN_9
#define PIN_TIM1_CH3            PIOA_PIN_10
#define PIN_ESP8266_CIPO        PIOA_PIN_11
#define PIN_ESP8266_COPI        PIOA_PIN_12
#define PIN_PROG_SWDIO          PIOA_PIN_13
#define PIN_PROG_SWCLK          PIOA_PIN_14
#define PIN_PROG_JTDI           PIOA_PIN_15

#define PIN_PROG_JTDO           PIOB_PIN_3
#define PIN_PROG_NJTRST         PIOB_PIN_4

#define PIN_ESP8266_RXD         PIOB_PIN_6
#define PIN_ESP8266_TXD         PIOB_PIN_7

#define PIN_XR_GPIO             PIOB_PIN_12
#define PIN_VBUS_PRESENT        PIOB_PIN_13

#define PIN_XR_TX               PIOC_PIN_0
#define PIN_XR_RX               PIOC_PIN_1
#define PIN_GREEN_LED           PIOC_PIN_2
#define PIN_RED_LED             PIOC_PIN_3

#define PIN_WKUP3               PIOC_PIN_5

#define PIN_LVL_EN              PIOC_PIN_7
#define PIN_LVL_DIR             PIOC_PIN_8

#define PIN_WKUP2               PIOC_PIN_13
#define PIN_OSC32K_HI           PIOC_PIN_14
#define PIN_OSC32K_LO           PIOC_PIN_15

#define PIN_OSC48_HI            PIOH_PIN_0
#define PIN_OSC48_LO            PIOH_PIN_1
#define PIN_BOOT0               PIOH_PIN_3

#define PIN_WKUP_1_IRQ          EXTI0_IRQn
#define PIN_WKUP_2_IRQ          EXTI15_10_IRQn
#define PIN_WKUP_3_IRQ          EXTI9_5_IRQn
#define PIN_WKUP_4_IRQ          EXTI2_IRQn

#define PIN_TIM1_CH1            PIOA_PIN_8
#define PIN_TIM1_CH2            PIOA_PIN_9
#define PIN_TIM1_CH3            PIOA_PIN_10

typedef enum
{
    PUSH_BUTTON_A = 0,
    PUSH_BUTTON_B,
    PUSH_BUTTON_C,
    PUSH_BUTTON_D,
    NUM_PUSH_BUTTONS
} gpio_config_push_buttons_e;


typedef enum
{
    PUSH_BUTTON_A_PIN = PIN_WKUP4,
    PUSH_BUTTON_B_PIN = PIN_WKUP2,
    PUSH_BUTTON_C_PIN = PIN_WKUP3,
    PUSH_BUTTON_D_PIN = PIN_WKUP1
} gpio_config_push_button_pin_e;


typedef enum
{
    PUSH_BUTTON_A_IRQ = PIN_WKUP_4_IRQ,
    PUSH_BUTTON_B_IRQ = PIN_WKUP_2_IRQ,
    PUSH_BUTTON_C_IRQ = PIN_WKUP_3_IRQ,
    PUSH_BUTTON_D_IRQ = PIN_WKUP_1_IRQ
} gpio_config_push_button_irq_e;


typedef enum
{
    GPIO_CONFIG_LED_GREEN,
    GPIO_CONFIG_LED_RED,
    GPIO_CONFIG_LED_BLUE,
    GPIO_CONFIG_LED_ORANGE
} gpio_config_led_e;
bool gpio_config_led_all_off(void);
bool gpio_config_led_all_on(void);
bool gpio_config_led_on(gpio_config_led_e led);

bool gpio_config_green_led_on(void);
bool gpio_config_green_led_off(void);
bool gpio_config_red_led_on(void);
bool gpio_config_red_led_off(void);


#endif
