// SRW
#include "rng_access.h"
#include "rng_config_hal.h"
#include "stm32l4xx_hal.h"


RNG_HandleTypeDef g_rng_handle =
{
    .Instance = RNG
};


void rng_config_hal_setup(void)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RNG;
    PeriphClkInit.RngClockSelection = RCC_RNGCLKSOURCE_HSI48;

    if (HAL_OK != HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit))
    {
        while (1);
    }

    __HAL_RCC_RNG_CLK_ENABLE();

    HAL_NVIC_SetPriority(RNG_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(RNG_IRQn);

    if (HAL_RNG_Init(&g_rng_handle) != HAL_OK)
    {
        while (1);
    }

    rng_access_generate_random_number();
}
