// SRW

#include "stm32l4xx_hal.h"
#include "board_specific.h"
#include "gpio_config_hal.h"


extern gpio_config_t gpio_config[GPIO_CONFIG_NUM_PINS];

void gpio_config_init(void)
{
    for (gpio_config_pin_e pin = GPIO_CONFIG_PIN_FIRST;
                    pin < GPIO_CONFIG_NUM_PINS;
                    pin = (gpio_config_pin_e)(pin + 1))
    {
        GPIO_PinState output_lvl = GPIO_PIN_RESET;
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = gpio_config[pin].pin;
        switch (gpio_config[pin].pin_mode)
        {
            case GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL:
                GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
                GPIO_InitStruct.Pull = GPIO_NOPULL;
            break;
            case GPIO_CONFIG_PIN_MODE_OUTPUT_OPEN_DRAIN:
                GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
                GPIO_InitStruct.Pull = GPIO_PULLUP;
            break;
            case GPIO_CONFIG_PIN_MODE_INPUT_FLOAT:
                GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
                GPIO_InitStruct.Pull = GPIO_NOPULL;
            break;
            case GPIO_CONFIG_PIN_MODE_INPUT_PULLUP:
                if (GPIO_CONFIG_PIN_INTERRUPT_ENABLE == gpio_config[pin].interrupt)
                {
                    switch (gpio_config[pin].pin_mode)
                    {
                        case GPIO_CONFIG_PIN_MODE_INPUT_PULLUP:
                            GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
                            GPIO_InitStruct.Pull = GPIO_PULLUP;
                        break;
                        case GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN:
                            GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
                            GPIO_InitStruct.Pull = GPIO_PULLDOWN;
                        break;
                        default:
                        break;
                    }
                }
                else
                {
                    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
                    GPIO_InitStruct.Pull = GPIO_PULLUP;
                }
            break;
            case GPIO_CONFIG_PIN_MODE_INPUT_PULLDOWN:
                GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
                GPIO_InitStruct.Pull = GPIO_PULLDOWN;
            break;
            case GPIO_CONFIG_PIN_MODE_ALTERNATE_FUNCTION: // fall through
            case GPIO_CONFIG_PIN_MODE_NO_SETUP: // fall through
            default:
            break;
        }
        HAL_GPIO_Init(gpio_config[pin].port, &GPIO_InitStruct);
        switch (gpio_config[pin].pin_mode)
        {
            case GPIO_CONFIG_PIN_MODE_OUTPUT_PUSH_PULL:
            case GPIO_CONFIG_PIN_MODE_OUTPUT_OPEN_DRAIN:
                output_lvl = ((gpio_config[pin].output_lvl == GPIO_CONFIG_OUTPUT_LVL_HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET);
                HAL_GPIO_WritePin(gpio_config[pin].port, gpio_config[pin].pin, output_lvl);
            break;
            default:
            break;
        }
        if (GPIO_CONFIG_PIN_INTERRUPT_ENABLE == gpio_config[pin].interrupt)
        {
            __HAL_GPIO_EXTI_CLEAR_IT(gpio_config[pin].interrupt_type);
            HAL_NVIC_SetPriority(gpio_config[pin].interrupt_type, 24, 0);
            HAL_NVIC_EnableIRQ(gpio_config[pin].interrupt_type);
            __HAL_GPIO_EXTI_CLEAR_IT(gpio_config[pin].interrupt_type);
        }
    }
}




