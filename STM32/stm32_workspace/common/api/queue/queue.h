
#if !defined(QUEUE_H)

#define QUEUE_H

typedef struct
{
	QueueHandle_t		queue
	uint32_t 			*p_cur_item;
	uint32_t 			queue_index;
} queue_item_t;





typedef enum
{
	QUEUE_FREE,
	QUEUE_RX,
	QUEUE_TX,
	NUM_QUEUES
} queue_e;

#endif
