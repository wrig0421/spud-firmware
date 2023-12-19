// SRW
#include "config.h"
#if !defined(BOARD_INIT_SPUD_GLO_V5_H)
#define BOARD_INIT_SPUD_GLO_V5_H



//#define PIN_XR_TX               PIOC_PIN_0
//#define PIN_XR_RX               PIOC_PIN_1
#define PIN_GREEN_LED           PIOC_PIN_2
#define PIN_RED_LED             PIOC_PIN_3

#define PIN_WKUP3				PIOC_PIN_5
#define PIN_LVL_EN          	PIOC_PIN_7
#define PIN_LVL_DIR             PIOC_PIN_8

#define PIN_WKUP2				PIOC_PIN_13

#define PIN_WKUP1				PIOA_PIN_0
//#define PIN_ESP8266_SCK			PIOA_PIN_1
#define PIN_WKUP4				PIOA_PIN_2

//#define PIN_ESP8266_CSN			PIOA_PIN_4
#define PIN_ESP8266_GPIO0		PIOA_PIN_5
#define PIN_ESP8266_EN			PIOA_PIN_6
#define PIN_ESP8266_RST			PIOA_PIN_7
#define PIN_TIM1_CH1			PIOA_PIN_8
#define PIN_TIM1_CH2			PIOA_PIN_9
#define PIN_TIM1_CH3			PIOA_PIN_10
//#define PIN_ESP8266_MISO		PIOA_PIN_11
//#define PIN_ESP8266_MOSI		PIOA_PIN_12

//#define PIN_ESP8266_RXD			PIOB_PIN_6
//#define PIN_ESP8266_TXD			PIOB_PIN_7

#define PIN_XR_GPIO				PIOB_PIN_12
#define PIN_VBUS_PRESENT		PIOB_PIN_13


void board_init_specific(void);
void board_init_specific_power_cycle_level_shifter(void);


#endif
