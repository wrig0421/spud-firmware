// SRW
#include <stdbool.h>
#include "stm32l4xx_hal.h"

#include "task_notify.h"


task_notification_value_format_t g_task_notification_value =
{
	.value = 0 // force clear
};


bool task_notify_entity_is_strip_1(void)
{
	return g_task_notification_value.entity_bits.strip_1;
}


bool task_notify_entity_is_strip_2(void)
{
	return g_task_notification_value.entity_bits.strip_2;
}


bool task_notify_entity_is_strip_3(void)
{
	return g_task_notification_value.entity_bits.strip_3;
}


bool task_notify_entity_is_strip_sync(void)
{
	return g_task_notification_value.entity_bits.strip_sync;
}


bool task_notify_state_is_set(void)
{
	return g_task_notification_value.stimulus_bits.state;
}


bool task_notify_color_is_set(void)
{
	return g_task_notification_value.stimulus_bits.color;
}


bool task_notify_speed_is_set(void)
{
	return g_task_notification_value.stimulus_bits.speed;
}


bool task_notify_pause_is_set(void)
{
	return g_task_notification_value.stimulus_bits.speed;
}


bool task_notify_custom_state_is_set(void)
{
	return g_task_notification_value.stimulus_bits.speed;
}


bool task_notify_brightness_is_set(void)
{
	return g_task_notification_value.stimulus_bits.speed;
}


bool task_notify_strip_1_is_set(void)
{
	return g_task_notification_value.entity_bits.strip_1;
}


bool task_notify_strip_2_is_set(void)
{
	return g_task_notification_value.entity_bits.strip_2;
}


bool task_notify_strip_3_is_set(void)
{
	return g_task_notification_value.entity_bits.strip_3;
}


bool task_notify_strip_sync_is_set(void)
{
	return g_task_notification_value.entity_bits.strip_sync;
}


