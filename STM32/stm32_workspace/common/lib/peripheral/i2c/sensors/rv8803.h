///***********************************
// * @file   animate_led.h
// * @author SpudGlo LLC
// ***********************************/
#if !defined(RV8803_H)
#define RV8803_H
#include <stdint.h>


typedef enum
{
	RV8803_REGISTER_TEN_MILLISECONDS 	= 0x10,
	RV8803_REGISTER_SECONDS 			= 0x11,
	RV8803_REGISTER_MINUTES 			= 0x12,
	RV8803_REGISTER_HOURS 				= 0x13,
	RV8803_REGISTER_WEEKDAY 			= 0x14,
	RV8803_REGISTER_DATE 				= 0x15,
	RV8803_REGISTER_MONTH 				= 0x16,
	RV8803_REGISTER_YEAR 				= 0x17,
	RV8803_REGISTER_MINUTES_ALARM 		= 0x18,
	RV8803_REGISTER_HOURS_ALARM 		= 0x19,
	RV8803_REGISTER_WEEKDAY_DATE_ALARM 	= 0x1A,
	RV8803_REGISTER_TIMER_COUNTER_0 	= 0x1B,
	RV8803_REGISTER_TIMER_COUNTER_1 	= 0x1C,
	RV8803_REGISTER_EXTENSION 			= 0x1D,
	RV8803_REGISTER_FLAG 				= 0x1E,
	RV8803_REGISTER_CONTROL 			= 0x1F
} rv8803_register_e;


typedef uint8_t rv8803_data_t;

typedef struct
{
	//rv8803_data_t ten_millisecond_count;
	rv8803_data_t second;
	rv8803_data_t minute;
	rv8803_data_t hour;
	rv8803_data_t weekday;
	rv8803_data_t date;
	rv8803_data_t month;
	rv8803_data_t year;
} rv8803_tod_t;


typedef union
{
	rv8803_tod_t rv8803_time;
	uint8_t flat_data_uint8[sizeof(rv8803_tod_t)];
} rv8803_tod_union_t;

void rv8803_write_register(rv8803_register_e reg_addr, uint8_t data);
void rv8803_read_register(rv8803_register_e reg_addr, uint8_t* data);
void rv8803_write_register_burst(rv8803_register_e reg_addr_start, uint8_t* data, uint16_t data_length);
void rv8803_read_register_burst(rv8803_register_e reg_addr_start, uint8_t* data, uint16_t data_length);
void rv8803_read_tod(rv8803_tod_t* rv8803_tod);
uint8_t numbers_hex_to_bcd(uint8_t val_hex);
void rv8803_write_current_tod(void);




#endif
