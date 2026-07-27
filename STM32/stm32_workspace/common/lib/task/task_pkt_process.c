// SRW
#include <stdbool.h>
#include "stm32l4xx_hal.h"

#include "pkt_queue.h"
#include "task_create.h"
#include "task_pkt_process.h"

TaskHandle_t 	g_task_pkt_process_handle;
StaticTask_t 	g_task_pkt_process_buffer;
StackType_t 	g_task_pkt_process_stack[TASK_CREATE_STACK_SIZE_STANDARD];


void task_pkt_process(void *argument);

void task_pkt_process_create(void)
{
	g_task_pkt_process_handle = xTaskCreateStatic(task_pkt_process,
			"task_pkt_process", TASK_CREATE_STACK_SIZE_STANDARD,
			NULL, tskIDLE_PRIORITY, g_task_pkt_process_stack,
			&g_task_pkt_process_buffer);
}


// rx from computer
void task_pkt_process(void *argument)
{
    p_pkt_t p_pkt = NULL;
    while (1)
    {
    	pkt_queue_dequeue_pkt_from_process(p_pkt); // blocking

        switch (p_pkt->pkt.header.tag)
        {
            case PKT_TAG_CMD:
                switch (p_pkt->pkt.header.var)
                {
                    case PKT_VAR_WRITE:
//                    	switch (p_pkt->pkt.header.adrs):
//						{
//                    		case offsetof()
//							break;
//                    		default:
//                    		break;
//						}
                    	// need to write to flash..
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
        pkt_queue_enqueue_pkt_to_host_tx(p_pkt); // send response to host
    }
}

