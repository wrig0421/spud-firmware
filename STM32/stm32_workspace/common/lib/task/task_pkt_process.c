// SRW
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"
#include "pkt.h"
#include "task_pkt_process.h"


// rx from computer
void task_pkt_process(void *argument)
{
    p_pkt_t p_pkt;
    while (1)
    {
        p_pkt = pkt_dequeue_from_process();
        switch (p_pkt->pkt.header.tag)
        {
            case PKT_TAG_CMD:
                switch (p_pkt->pkt.header.var)
                {
                    case PKT_VAR_WRITE:
                        // write dependent on adrs
                    break;
                    case PKT_VAR_READ:
                        // read dependent on adrs
                    break;
                    case PKT_VAR_RESET:
                        // reset device NVIC_SystemReset
                    break;
                    default:
                        while (1);
                    break;
                }
            break;
            default:
                while (1);
            break;
        }
        p_pkt->pkt.header.src = PKT_SRC_PCB;
        //p_pkt->pkt.header.status = PKT_STATUS_CMPLT; // need to set status based on successful read or write
        pkt_enqueue_to_tx(p_pkt); // send response to host
    }
}

