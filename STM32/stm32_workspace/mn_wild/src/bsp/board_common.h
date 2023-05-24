// SRW

#if !defined(BOARD_COMMON_H)
#define BOARD_COMMON_H


// PORTA pins
#define PIN_PORT_A                  GPIOA

#define PIN_WKUP_1                  GPIO_PIN_0
#define PIN_ADAFRUIT_RESET_N        GPIO_PIN_1
#define PIN_WKUP_4                  GPIO_PIN_2
#define PIN_ADAFRUIT_TRIG_0         GPIO_PIN_3
#define PIN_ADAFRUIT_TRIG_1         GPIO_PIN_4
#define PIN_ADAFRUIT_TRIG_2         GPIO_PIN_5
#define PIN_ADAFRUIT_TRIG_3         GPIO_PIN_6
#define PIN_ADAFRUIT_TRIG_4         GPIO_PIN_7
#define PIN_TIM1_CH1                GPIO_PIN_8
#define PIN_LVL_DIR                 GPIO_PIN_9
#define PIN_LVL_EN                  GPIO_PIN_10
#define PIN_LIGHT_CTRL              GPIO_PIN_11
#define PIN_SPEAKER_CTRL            GPIO_PIN_12


// PORTB pins
#define PIN_PORT_B                  GPIOB

#define PIN_GPIO_0                  GPIO_PIN_0
#define PIN_GPIO_1                  GPIO_PIN_1
#define PIN_GPIO_2                  GPIO_PIN_2

#define PIN_GPIO_7                  GPIO_PIN_5
#define PIN_GPIO_6                  GPIO_PIN_6
#define PIN_GPIO_5                  GPIO_PIN_7
#define PIN_GPIO_4                  GPIO_PIN_8

#define PIN_I2C2_SCL                GPIO_PIN_10
#define PIN_I2C2_SDA                GPIO_PIN_11
#define PIN_ADAFRUIT_TRIG_6         GPIO_PIN_12
#define PIN_ADAFRUIT_TRIG_7         GPIO_PIN_13
#define PIN_ADAFRUIT_TRIG_8         GPIO_PIN_14
#define PIN_ADAFRUIT_TRIG_9         GPIO_PIN_15


// PORTC pins
#define PIN_PORT_C                  GPIOC

#define PIN_LPUART1_RX              GPIO_PIN_0
#define PIN_LPUART1_TX              GPIO_PIN_1
#define PIN_LED_OUT_1               GPIO_PIN_2
#define RED_LED                     PIN_LED_OUT_1
#define PIN_LED_OUT_2               GPIO_PIN_3
#define GREEN_LED                   PIN_LED_OUT_2

#define PIN_ADAFRUIT_TRIG_5         GPIO_PIN_4
#define PIN_WKUP_3                  GPIO_PIN_5
#define PIN_ADAFRUIT_TRIG_10        GPIO_PIN_6
#define PIN_ADAFRUIT_ACT            GPIO_PIN_7
#define PIN_ADAFRUIT_PWR_EN         GPIO_PIN_8
#define PIN_GPIO_3                  GPIO_PIN_9
#define PIN_ADAFRUIT_VOL_DOWN       GPIO_PIN_10
#define PIN_ADAFRUIT_VOL_UP         GPIO_PIN_11
#define PIN_ADAFRUIT_UART_ENABLE_N  GPIO_PIN_12
#define PIN_WKUP_2                  GPIO_PIN_13
#define PIN_OSC32_HI                GPIO_PIN_14
#define PIN_OSC32_LO                GPIO_PIN_15



#endif