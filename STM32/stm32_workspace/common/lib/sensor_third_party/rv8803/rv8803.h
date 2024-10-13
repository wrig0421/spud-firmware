///***********************************
// * @file   animate_led.h
// * @author SpudGlo LLC
// ***********************************/
#if !defined(RV8803_H)
#define RV8803_H
#include <stdint.h>

typedef uint8_t rv8803_data_t;


typedef enum
{
	RV8803_TIME_FIELD_TENS_OF_MILLISECOND,
	RV8803_TIME_FIELD_SECOND,
	RV8803_TIME_FIELD_MINUTE,
	RV8803_TIME_FIELD_HOUR,
	RV8803_TIME_FIELD_WEEKDAY,
	RV8803_TIME_FIELD_DATE,
	RV8803_TIME_FIELD_MONTH,
	RV8803_TIME_FIELD_YEAR,
	RV8803_NUM_TIME_FIELDS
} rv8803_time_field_e;


typedef struct
{
	rv8803_data_t tens_of_millisecond;
	rv8803_data_t second;
	rv8803_data_t minute;
	rv8803_data_t hour;
	rv8803_data_t weekday;
	rv8803_data_t dates;
	rv8803_data_t months;
	rv8803_data_t years;
} rv8803_tod_t;


typedef union
{
	rv8803_tod_t rv8803_time;
	uint8_t flat_data_uint8[sizeof(rv8803_tod_t)];
} rv8803_tod_union_t;



void rv8803_read_tod(rv8803_tod_t* rv8803_tod);
uint8_t numbers_hex_to_bcd(uint8_t val_hex);
uint8_t numbers_bcd_to_hex(uint8_t val_bcd);
void rv8803_write_current_tod(void);




#endif
