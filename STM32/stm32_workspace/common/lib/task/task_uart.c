// SRW
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"
#include "pkt.h"
#include "task_uart.h"


// rx from computer
void task_uart_rx(void *argument)
{
    p_pkt_t p_pkt;

    while (1)
    {
        pkt_enqueue_to_process(pkt_dequeue_from_rx());
    }
}


// tx to computer
void task_uart_tx(void *argument)
{
    p_pkt_t p_pkt;
    while (1)
    {
        p_pkt = pkt_dequeue_from_tx();
        // send it out over uart

    }
}
