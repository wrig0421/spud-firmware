// SRW

#if !defined(TASK_NOTIFY_H)

#define TASK_NOTIFY_H


typedef enum
{
	TASK_NOTIFICATION_STIMULUS_STATE				= (1 << 0),
	TASK_NOTIFICATION_STIMULUS_COLOR				= (1 << 1),
	TASK_NOTIFICATION_STIMULUS_SPEED				= (1 << 2),
	TASK_NOTIFICATION_STIMULUS_PAUSE				= (1 << 3),
	TASK_NOTIFICATION_STIMULUS_CUSTOM_STATE			= (1 << 4),
	TASK_NOTIFICATION_STIMULUS_BRIGHTNESS			= (1 << 5),
	TASK_NOTIFICATION_STIMULUS_STRIP_1_DMA_CMPLT 	= (1 << 6),
	TASK_NOTIFICATION_STIMULUS_STRIP_2_DMA_CMPLT 	= (1 << 7),
	TASK_NOTIFICATION_STIMULUS_STRIP_3_DMA_CMPLT 	= (1 << 8),
	TASK_NOTIFICATION_HOST_UART_PKT_RECEIVED		= (1 << 9)

} task_notification_stimulus_e;


typedef enum
{
	TASK_NOTIFICATION_ENTITY_STRIP_1			= (1 << 0),
	TASK_NOTIFICATION_ENTITY_STRIP_2			= (1 << 1),
	TASK_NOTIFICATION_ENTITY_STRIP_3			= (1 << 2),
	TASK_NOTIFICATION_ENTITY_STRIP_SYNC			= (1 << 3)
} task_notification_entity_e;


typedef union
{
	struct
	{
		union
		{
			struct
			{
				uint8_t state 				: 1;
				uint8_t color 				: 1;
				uint8_t speed 				: 1;
				uint8_t pause 				: 1;
				uint8_t custom_state 		: 1;
				uint8_t brightness 			: 1;
				uint8_t dma_cmplt			: 1;
				uint8_t rsvd				: 1;

				uint8_t rsvd_2				: 8;
			} stimulus_bits;
			uint16_t flat_stimulus;
		};
		union
		{
			struct
			{
				uint8_t strip_1 		: 1;
				uint8_t strip_2 		: 1;
				uint8_t strip_3 		: 1;
				uint8_t strip_sync 		: 1;
				uint8_t rsvd			: 4;
				uint8_t rsvd_2;
			} entity_bits;
			uint16_t flat_entity;
		};
	};
	uint32_t value;
} task_notification_value_format_t;

bool task_notify_entity_is_strip_1(void);
bool task_notify_entity_is_strip_2(void);
bool task_notify_entity_is_strip_3(void);
bool task_notify_entity_is_strip_sync(void);
bool task_notify_state_is_set(void);
bool task_notify_color_is_set(void);
bool task_notify_speed_is_set(void);
bool task_notify_pause_is_set(void);
bool task_notify_custom_state_is_set(void);
bool task_notify_brightness_is_set(void);
bool task_notify_strip_1_is_set(void);
bool task_notify_strip_2_is_set(void);
bool task_notify_strip_3_is_set(void);
bool task_notify_strip_sync_is_set(void);



#endif


