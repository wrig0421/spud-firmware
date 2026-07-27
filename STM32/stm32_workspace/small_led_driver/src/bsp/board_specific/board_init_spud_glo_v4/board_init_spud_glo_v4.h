// SRW

#if !defined(BOARD_INIT_SPUD_GLO_V4_H)
#define BOARD_INIT_SPUD_GLO_V4_H

// PORT A pins 
#define PIN_PORT_A              GPIOA
#define PIN_SPI1_SCK            GPIO_PIN_1

#define PIN_SPI1_NSS            GPIO_PIN_4 //
#define PIN_DISP_BACKLIGHT      GPIO_PIN_5
#define PIN_DISP_DC             GPIO_PIN_6
#define PIN_DISP_RST            GPIO_PIN_7

#define PIN_SPI1_CIPO           GPIO_PIN_11
#define PIN_SPI1_COPI           GPIO_PIN_12

#define SWDIO                   GPIO_PIN_13
#define SWCLK                   GPIO_PIN_14
#define JTDI                    GPIO_PIN_15

// PORT B pins  
#define PIN_PORT_B              GPIOB
#define PIN_INT_LVL_EN          GPIO_PIN_0

#define JTDO                    GPIO_PIN_3
#define NJTRST                  GPIO_PIN_4

#define PIN_XR_RX               GPIO_PIN_1 //
#define PIN_XR_TX               GPIO_PIN_0 //

#define PIN_XR_GPIO             GPIO_PIN_12
#define PIN_VBUS_PRESENT        GPIO_PIN_13

// PORT C pins 
#define PIN_PORT_C              GPIOC

#define PIN_LVL_DIR             GPIO_PIN_8


void board_init_specific(void);
void board_init_specific_power_cycle_level_shifter(void);


#endif
