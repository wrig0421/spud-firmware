/***********************************
 * @file   rv8803.c
 * @author SpudGlo LLC
 ***********************************/
#include <stdint.h>
#include <stdbool.h>
#include "i2c_access.h"
#include "rv8803.h"
#include "free_rtos_convenience.h"


// reg_addr increments by one after every byte write

// `g_rv8803_tod` will keep track of the read time any
// time that a read is performed.
rv8803_tod_t g_rv8803_tod =
{
	.second 		= 0,
	.minute 		= 0,
	.hour 			= 0,
	.weekday 		= 0,
	.date 			= 0,
	.month 			= 0,
	.year 			= 0
};


typedef enum
{
	RV8803_REGISTER_TEN_MILLISECOND 	= 0x10,
	RV8803_REGISTER_SECOND 				= 0x11,
	RV8803_REGISTER_MINUTE 				= 0x12,
	RV8803_REGISTER_HOUR 				= 0x13,
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

typedef struct
{
	uint8_t minutes_alarm 				: 7;
	uint8_t minutes_alarm_enable 		: 1;
} rv8803_minutes_alarm_register_t;


typedef struct
{
	uint8_t hours_alarm 				: 6;
	uint8_t hours_gp0					: 1;
	uint8_t hours_alarm_enable 			: 1;
} rv8803_hours_alarm_register_t;


typedef struct
{
	uint8_t weekday_date_alarm 			: 7;
	uint8_t weekday_date_alarm_enable 	: 1;
} rv8803_weekday_date_alarm_register_t;


typedef struct
{
	uint8_t weekday_alarm 				: 7;
	uint8_t weekday_alarm_enable 		: 1;
} rv8803_weekday_alarm_register_t;


typedef struct
{
	uint8_t date_alarm 					: 6;
	uint8_t date_gp1					: 1;
	uint8_t date_alarm_enable 			: 1;
} rv8803_date_alarm_register_t;



//static void rv8803_write_register(rv8803_register_e reg_addr, uint8_t data)
//{
//	i2c_access_write_byte(I2C_ACCESS_CHIP_ID_RV_8803, (uint32_t)reg_addr, data);
//}
//
//
//static void rv8803_read_register(rv8803_register_e reg_addr, uint8_t* data)
//{
//	i2c_access_read_byte(I2C_ACCESS_CHIP_ID_RV_8803, (uint32_t)reg_addr, data);
//}
//
//
//static void rv8803_write_register_burst(rv8803_register_e reg_addr_start, uint8_t* data, uint16_t data_length)
//{
//	i2c_access_write_block(I2C_ACCESS_CHIP_ID_RV_8803, (uint32_t)reg_addr_start, data, data_length);
//}
//
//
//static void rv8803_read_register_burst(rv8803_register_e reg_addr_start, uint8_t* data, uint16_t data_length)
//{
//	i2c_access_read_block(I2C_ACCESS_CHIP_ID_RV_8803, (uint32_t)reg_addr_start, data, data_length);
//}
//
//
//void rv8803_init(void)
//{
//	// perform any initialization here..
//}

//
//uint8_t rv8803_current_seconds(void)
//{
////	rv8803_data_t rv8803_data = 0;
////	rv8803_read_register(RV8803_REGISTER_SECOND, &rv8803_data.second);
////	return rv8803_data.second;
//}
//
//
//uint8_t rv8803_current_minutes(void)
//{
////	rv8803_data_t rv8803_data = 0;
////	rv8803_read_register(RV8803_REGISTER_MINUTE, &rv8803_data.minute);
////	return rv8803_data.minute;
////}
//
//
//uint8_t rv8803_current_hours(void)
//{
////	rv8803_data_t rv8803_data = 0;
////	rv8803_read_register(RV8803_REGISTER_HOUR, &rv8803_data.hour);
////	return rv8803_data.hour;
//}
//
//
//uint8_t rv8803_current_weekday(void)
//{
////	rv8803_data_t rv8803_data = 0;
////	rv8803_read_register(RV8803_REGISTER_WEEKDAY, &rv8803_data.weekday);
////	return rv8803_data.weekday;
//}
//
//
//uint8_t rv8803_current_date(void)
//{
////	rv8803_data_t rv8803_data = 0;
////	rv8803_read_register(RV8803_REGISTER_DATE, &rv8803_data.date);
////	return rv8803_data.date;
//}
//
//
//uint8_t rv8803_current_month(void)
//{
////	rv8803_data_t rv8803_data = 0;
////	rv8803_read_register(RV8803_REGISTER_MONTH, &rv8803_data.month);
////	return rv8803_data.month;
//}
//
//
//uint8_t rv8803_current_year(void)
//{
////	rv8803_data_t rv8803_data = 0;
////	rv8803_read_register(RV8803_REGISTER_YEAR, &rv8803_data.year);
////	return rv8803_data.year;
//}
//
//
//uint8_t rv8803_read_minutes_alarm(void)
//{
//	return rv8803_read_current_register(RV8803_REGISTER_MINUTES_ALARM);
//}
//
//
//uint8_t rv8803_read_register_hours_alarm(void)
//{
//	return rv8803_read_current_register(RV8803_REGISTER_HOURS_ALARM);
//}
//
//
//uint8_t rv8803_read_register_weekday_or_date_alarm(void)
//{
//	return rv8803_read_current_register(RV8803_REGISTER_WEEKDAY_DATE_ALARM);
//}
//
//
//uint8_t rv8803_read_register_timer_counter_0(void)
//{
//	return rv8803_read_current_register(RV8803_REGISTER_TIMER_COUNTER_0);
//}
//
//
//uint8_t rv8803_read_register_timer_counter_1(void)
//{
//	return rv8803_read_current_register(RV8803_REGISTER_TIMER_COUNTER_1);
//}
//
//
//uint8_t rv8803_read_register_extension(void)
//{
//	return rv8803_read_current_register(RV8803_REGISTER_EXTENSION);
//}
//
//
//uint8_t rv8803_read_register_flag(void)
//{
//	return rv8803_read_current_register(RV8803_REGISTER_FLAG);
//}
//
//
//uint8_t rv8803_read_register_control(void)
//{
//	return rv8803_read_current_register(RV8803_REGISTER_CONTROL);
//}
//
//
//uint8_t rv8803_read_current_seconds(void)
//{
////	uint8_t data = 0;
////	rv8803_read_register(RV8803_REGISTER_TEN_MILLISECONDS, &data);
////	return data;
//}
//
//
//uint8_t numbers_hex_to_bcd(uint8_t val_hex)
//{
//	return (((val_hex / 10) * (1 << 4)) + (val_hex % 10));
//}
//
//
//uint8_t numbers_bcd_to_hex(uint8_t val_bcd)
//{
//	return ((val_bcd & 0xF) + (((val_bcd & 0xF0) >> 4) * 10));
//}
//
//
//bool g_ready_to_write_time = false;
//uint8_t g_dbg_second = 0;
//uint8_t g_dbg_minute = 5;
//uint8_t g_dbg_hour = 11;
//uint8_t g_dbg_weekday = 0;
//uint8_t g_dbg_date = 27;
//uint8_t g_dbg_month = 5;
//uint8_t g_dbg_year = 24;
//
//uint8_t g_sec_count = 0;
//void rv8803_write_current_tod(void)
//{
//	// need to get the current time from the debugger and write it down
//	// through debugger..
//	rv8803_tod_t rv8803_tod =
//	{
//	    // all in BCD except weekday
//		.second = numbers_hex_to_bcd(g_dbg_second),
//		.minute = numbers_hex_to_bcd(g_dbg_minute),
//		.hour = numbers_hex_to_bcd(g_dbg_hour),
//		.weekday = numbers_hex_to_bcd(g_dbg_weekday),
//	    .date = numbers_hex_to_bcd(g_dbg_date),
//		.month = numbers_hex_to_bcd(g_dbg_month),
//		.year = numbers_hex_to_bcd(g_dbg_year)
//	};
//
////	rv8803_write_register_burst(RV8803_REGISTER_SECONDS, (uint8_t *)&rv8803_tod, sizeof(rv8803_tod_t));
////	while (1)
////	{
////		free_rtos_delay_ms(1000);
//////        g_sec_count = rv8803_tod.second;
////    	rv8803_read_register(RV8803_REGISTER_SECONDS, &g_sec_count);
//////        rv8803_read_register_burst(RV8803_REGISTER_SECONDS, (uint8_t *)&rv8803_tod, sizeof(rv8803_tod_t));
////	}
//
//
//}
//
//
////void rv8803_read_current_tod(rv8803_tod_t* rv8803_tod)
////{
//////	rv8803_read_register_burst(RV8803_REGISTER_TEN_MILLISECOND, &rv8803_tod, sizeof(rv8803_tod_t));
//////	memcpy(&g_rv8803_tod, rv8803_tod, sizeof(rv8803_tod_t));
////}
//
//
//
//
//
