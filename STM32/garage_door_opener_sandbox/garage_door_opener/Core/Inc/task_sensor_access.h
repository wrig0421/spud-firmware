

#if !defined(TASK_SENSOR_ACCESS_H)
#define TASK_SENSOR_ACCESS_H

#include <stdint.h>
typedef enum
{
	GT521FX_STATE_ADMIN,
	GT521FX_STATE_ENROLL, // must match key 1
	GT521FX_STATE_DELETE, // must match key 2
	GT521FX_STATE_DELETE_ALL, // must match key 3
	GT521FX_STATE_IDENTIFY,
	GT521FX_STATE_VERIFY,
	GT521FX_STATE_OPEN_DOOR,
	GT521FX_STATE_ERROR,
	GT521FX_STATE_NOTHING_TO_DO,
} gt521fx_state_e;


void task_sensor_access_entry(void *argument);
gt521fx_state_e gt521fx_current_state(void);
void gt521fx_set_state(uint16_t key);

#endif
