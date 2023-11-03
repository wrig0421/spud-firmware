// SRW
#include "stm32l4xx_hal.h"
#include "board_specific.h"
#include "spi_access_hal.h"


SPI_HandleTypeDef       gh_disp_spi =
{
    .Instance               = SPI1,
    .Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256,
    .Init.Direction         = SPI_DIRECTION_2LINES,
    .Init.CLKPhase          = SPI_PHASE_1EDGE,
    .Init.CLKPolarity       = SPI_POLARITY_LOW,
    .Init.DataSize          = SPI_DATASIZE_8BIT,
    .Init.FirstBit          = SPI_FIRSTBIT_MSB,
    .Init.TIMode            = SPI_TIMODE_DISABLE,
    .Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE,
    .Init.CRCPolynomial     = 7,
    .Init.CRCLength         = SPI_CRC_LENGTH_8BIT,
    .Init.NSS               = SPI_NSS_SOFT,
    .Init.NSSPMode          = SPI_NSS_PULSE_DISABLE,
    .Init.Mode              = SPI_MODE_MASTER
};


void spi_access_setup(void)
{
    //RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    GPIO_InitTypeDef  GPIO_InitStruct;

    GPIO_InitStruct.Pin         = PIN_ESP8266_SCK | PIN_ESP8266_CIPO | PIN_ESP8266_COPI;
    GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull        = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate   = GPIO_AF5_SPI1;

    HAL_GPIO_Init(PIN_PORT_A, &GPIO_InitStruct);
    __HAL_RCC_SPI1_CLK_ENABLE();
    if(HAL_SPI_Init(&gh_disp_spi) != HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }
}


void spi_access_write_and_read(uint8_t *tx_data, uint8_t *rx_data, uint16_t size)
{
    HAL_SPI_TransmitReceive(&gh_disp_spi, tx_data, rx_data, size, 5000);
}


