// SRW

#if !defined(BOARD_INIT_SPUD_GLO_V3_H)
#define BOARD_INIT_SPUD_GLO_V3_H

// PORT A pins
#define PIN_ADC_IN              PIOA_PIN_1
#define PIN_SPI3_NSS            PIOA_PIN_4

// PORT B pins
#define PIN_GPIO0               PIOB_PIN_5
#define PIN_GPIO1               PIOB_PIN_6
#define PIN_GPIO2               PIOB_PIN_7
#define PIN_GPIO3               PIOB_PIN_8
#define PIN_I2C2_SCL            PIOB_PIN_10
#define PIN_I2C2_SDA            PIOB_PIN_11
#define PIN_TIM15_CH1           PIOB_PIN_14

// PORT C pins 
#define PIN_LPUART1_RX          PIOC_PIN_0
#define PIN_LPUART1_TX          PIOC_PIN_1
#define PIN_LED_OUT_1           PIOC_PIN_2
#define PIN_LED_OUT_2           PIOC_PIN_3
#define RED_LED                 PIN_LED_OUT_1
#define GREEN_LED               PIN_LED_OUT_2
#define PIN_LVL_EN              PIOC_PIN_7
#define PIN_LVL_DIR             PIOC_PIN_8
#define PIN_SPI3_SCK            PIOC_PIN_10
#define PIN_SPI3_MISO           PIOC_PIN_11
#define PIN_SPI3_MOSI           PIOC_PIN_12


void board_init_specific(void);
void board_init_specific_power_cycle_level_shifter(void);


#endif
