// SRW
#include "stm32l4xx_hal.h"
#include "config.h"
#if defined(ENABLE_BUTTON)

#include "button_config_hal.h"

extern const button_config_t g_button_config[NUM_BUTTONS];


void button_config_hal_setup(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    for (button_e btn = BUTTON_FIRST; btn < NUM_BUTTONS; btn++)
    {
    	GPIO_InitStruct.Pin 		= g_button_config[btn].pin;
    	GPIO_InitStruct.Pull 		= g_button_config[btn].pull;
		GPIO_InitStruct.Mode      	= g_button_config[btn].mode;

		__HAL_GPIO_EXTI_CLEAR_IT(g_button_config[btn].irqn);
	    HAL_NVIC_SetPriority(g_button_config[btn].irqn, 24, 0);
	    HAL_NVIC_EnableIRQ(g_button_config[btn].irqn);
	    __HAL_GPIO_EXTI_CLEAR_IT(g_button_config[btn].irqn);

	    HAL_GPIO_Init(g_button_config[btn].port, &GPIO_InitStruct);
    }
}


void button_config_clear_interrupt(button_e btn)
{
	__HAL_GPIO_EXTI_CLEAR_IT(g_button_config[btn].irqn);
}


void button_config_disable_interrupt(button_e btn)
{
	HAL_NVIC_DisableIRQ(g_button_config[btn].irqn);
}


void button_config_enable_interrupt(button_e btn)
{
    HAL_NVIC_SetPriority(g_button_config[btn].irqn, 24, 0);
    HAL_NVIC_EnableIRQ(g_button_config[btn].irqn);
}

void button_config_irq_handler(void)
{
//	HAL_GPIO_EXTI_IRQHandler(g_button_config[btn].irqn);
}

#endif
