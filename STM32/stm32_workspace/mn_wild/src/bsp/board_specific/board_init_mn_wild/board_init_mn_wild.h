// SRW

#if !defined(BOARD_INIT_MN_WILD_H)
#define BOARD_INIT_MN_WILD_H

//// PORT A pins
//#define PIN_PORT_A              GPIOA
//#define PIN_ANALOG_IN           GPIO_PIN_1 //
//
//#define PIN_SPI3_NSS            GPIO_PIN_4 //
//
//#define SWDIO                   GPIO_PIN_13
//#define SWCLK                   GPIO_PIN_14
//#define JTDI                    GPIO_PIN_15
//
//// PORT B pins
//#define PIN_PORT_B              GPIOB
//#define JTDO                    GPIO_PIN_3
//#define NJTRST                  GPIO_PIN_4
//#define PIN_GPIO0               GPIO_PIN_5 //
//#define PIN_GPIO1               GPIO_PIN_6 //
//#define PIN_GPIO3               GPIO_PIN_7 //
//
//#define PIN_I2C2_SCL            GPIO_PIN_10
//#define PIN_I2C2_SDA            GPIO_PIN_11
//
//// PORT C pins
//#define PIN_PORT_C              GPIOC
//#define PIN_LPUART1_RX          GPIO_PIN_0
//#define PIN_LPUART1_TX          GPIO_PIN_1
//
//#define PIN_LVL_DIR             GPIO_PIN_8 //
//
//#define PIN_SPI3_SCK            GPIO_PIN_10
//#define PIN_SPI3_MISO           GPIO_PIN_11
//#define PIN_SPI3_MOSI           GPIO_PIN_12


void board_init_specific(void);


#endif