// SRW
#include "config.h"
#if !defined(BOARD_INIT_SPUD_GLO_V4_H)
#define BOARD_INIT_SPUD_GLO_V4_H

// PORT A pins 

// PORT C pins

//#if defined(BOARD_SPUDGLO_V4P1)
//
//#define PIN_INT_LVL_EN          PIOB_PIN_0
//
//#define PIN_LVL_EN              PIOC_PIN_7
//#define PIN_LVL_DIR             PIOC_PIN_8
//
//
//#elif defined(BOARD_SPUDGLO_V4P2) || defined(BOARD_SPUDGLO_V4P3)
//
//#define PIN_SPI1_SCK            PIOA_PIN_1
//#define PIN_SPI1_NSS            PIOA_PIN_4
//#define PIN_DISP_BACKLIGHT      PIOA_PIN_5
//#define PIN_DISP_DC             PIOA_PIN_6
//#define PIN_DISP_RST            PIOA_PIN_7
//#define PIN_SPI1_CIPO           PIOA_PIN_11
//#define PIN_SPI1_COPI           PIOA_PIN_12
//
//#define PIN_INT_LVL_EN          PIOB_PIN_0
//#define PIN_XR_GPIO             PIOB_PIN_12
//#define PIN_VBUS_PRESENT        PIOB_PIN_13
//
//#define PIN_XR_TX               PIOC_PIN_0
//#define PIN_XR_RX               PIOC_PIN_1
//#define PIN_LVL_EN              PIOC_PIN_7
//#define PIN_LVL_DIR             PIOC_PIN_8
//
//#endif
//
//#if defined(BOARD_SPUDGLO_V4P3)
//
//#define PIN_BLUE_LED            PIOB_PIN_8
//#define PIN_ORANGE_LED          PIOB_PIN_9
//#define PIN_GREEN_LED           PIOC_PIN_2
//#define PIN_RED_LED             PIOC_PIN_3
//
//#endif

void board_init_specific(void);
void board_init_specific_power_cycle_level_shifter(void);


#endif
