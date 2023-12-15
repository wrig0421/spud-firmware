// SRW

#include "stm32l4xx_hal.h"
#include "spi_access_hal.h"


void spi_access_setup(void)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    GPIO_InitTypeDef  GPIO_InitStruct;

    GPIO_InitStruct.Pin         = PIN_SPI1_SCK | PIN_SPI1_CIPO | PIN_SPI1_COPI;
    GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull        = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate   = GPIO_AF5_SPI1;

    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
    __HAL_RCC_SPI1_CLK_ENABLE();
    if(HAL_SPI_Init(&gh_disp_spi) != HAL_OK)
    {
        /* Initialization Error */
        //Error_Handler();
    }
}


void spi_access_hal_write_byte(void);
void spi_access_hal_write_block(void);

void spi_access_hal_read_byte(void);
void spi_access_hal_read_block(void);

