// SRW

#include "main.h"
#include "stm32l4xx_hal.h"
#include <time.h>
#include "animate_led.h"
#include "board_common.h"
#include "board_specific.h"
#include <stdlib.h>
#include "board_init_common.h"
#include "packet_queue.h"
#include "serial_com.h"


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
USART_HandleTypeDef     gh_host_usart =
{
    .Instance           = USART1,
    .Init.BaudRate      = 9600,
    .Init.WordLength    = USART_WORDLENGTH_8B,
    .Init.StopBits      = USART_STOPBITS_1,
    .Init.Parity        = USART_PARITY_NONE,
    .Init.Mode          = USART_MODE_TX_RX
};


void serial_com_init_spi(void)
{
    __HAL_RCC_SPI1_CLK_ENABLE();
    if(HAL_SPI_Init(&gh_disp_spi) != HAL_OK)
    {
        /* Initialization Error */
        //Error_Handler();
    }
}


void serial_com_init_usart(void)
{
    __HAL_RCC_USART1_CLK_ENABLE();
    if(HAL_USART_DeInit(&gh_host_usart) != HAL_OK)
    {
        //Error_Handler();
    }
    if(HAL_USART_Init(&gh_host_usart) != HAL_OK)
    {
        //Error_Handler();
    }
}


void serial_com_init_iic(void)
{

}


void serial_com_init_all(void)
{
    serial_com_init_usart();
    serial_com_init_spi();
    serial_com_init_iic();
}

pkt_t g_rx_pkt;
pkt_t g_tx_pkt;


void task_serial_com_usart_rx(void)
{
    packet_dequeue_from_host_rx(&g_rx_pkt);
    packet_parse(&g_rx_pkt);
    //packet_dequeue_from_host_rx
    // enqueue to process
}


void task_serial_com_usart_tx(void)
{
    packet_dequeue_from_host_tx(&g_tx_pkt);
    //packet_dequeue_from_host_tx
    // block on a queue, transmit when pkt added
}






