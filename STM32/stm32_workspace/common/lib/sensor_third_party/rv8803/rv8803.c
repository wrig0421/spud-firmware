/***********************************
 * @file   animate_led.c
 * @author SpudGlo LLC
 ***********************************/
#include <stdint.h>
#include <stdbool.h>
#include "i2c_access.h"
#include "rv8803.h"
#include "free_rtos_convenience.h"



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



void rv8803_write_register(rv8803_register_e reg_addr, uint8_t data)
{
	i2c_access_write_byte(I2C_ACCESS_CHIP_ID_RV_8803, (uint32_t)reg_addr, data);
}


void rv8803_read_register(rv8803_register_e reg_addr, uint8_t* data)
{
	i2c_access_read_byte(I2C_ACCESS_CHIP_ID_RV_8803, (uint32_t)reg_addr, data);
}


// reg_addr increments by one after every byte write
void rv8803_write_register_burst(rv8803_register_e reg_addr_start, uint8_t* data, uint16_t data_length)
{
	i2c_access_write_block(I2C_ACCESS_CHIP_ID_RV_8803, (uint32_t)reg_addr_start, data, data_length);
}


void rv8803_read_register_burst(rv8803_register_e reg_addr_start, uint8_t* data, uint16_t data_length)
{
	i2c_access_read_block(I2C_ACCESS_CHIP_ID_RV_8803, (uint32_t)reg_addr_start, data, data_length);
}


void rv8803_init(void)
{

}



void rv8803_read_tod(rv8803_tod_t* rv8803_tod)
{
	rv8803_read_register_burst(RV8803_REGISTER_TEN_MILLISECONDS, (uint8_t *)rv8803_tod, sizeof(rv8803_tod_t));
}


uint8_t rv8803_read_current_register(rv8803_register_e rv8803_reg)
{
	uint8_t data = 0;
	rv8803_read_register(rv8803_reg, &data);
	return data;
}


uint8_t rv8803_read_register_current_tens_of_milliseconds(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_TEN_MILLISECONDS);
}


uint8_t rv8803_read_register_current_seconds(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_SECONDS);
}


uint8_t rv8803_read_register_current_minutes(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_MINUTES);
}


uint8_t rv8803_read_register_current_hours(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_HOURS);
}


uint8_t rv8803_read_register_current_weekday(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_WEEKDAY);
}


uint8_t rv8803_read_register_current_date(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_DATE);
}


uint8_t rv8803_read_register_current_month(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_MONTH);
}


uint8_t rv8803_read_register_current_year(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_YEAR);
}


uint8_t rv8803_read_minutes_alarm(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_MINUTES_ALARM);
}


uint8_t rv8803_read_register_hours_alarm(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_HOURS_ALARM);
}


uint8_t rv8803_read_register_weekday_or_date_alarm(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_WEEKDAY_DATE_ALARM);
}


uint8_t rv8803_read_register_timer_counter_0(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_TIMER_COUNTER_0);
}


uint8_t rv8803_read_register_timer_counter_1(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_TIMER_COUNTER_1);
}


uint8_t rv8803_read_register_extension(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_EXTENSION);
}


uint8_t rv8803_read_register_flag(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_FLAG);
}


uint8_t rv8803_read_register_control(void)
{
	return rv8803_read_current_register(RV8803_REGISTER_CONTROL);
}


uint8_t rv8803_read_current_seconds(void)
{
	uint8_t data = 0;
	rv8803_read_register(RV8803_REGISTER_TEN_MILLISECONDS, &data);
	return data;
}


uint8_t numbers_hex_to_bcd(uint8_t val_hex)
{
	return (((val_hex / 10) * (1 << 4)) + (val_hex % 10));
}


uint8_t numbers_bcd_to_hex(uint8_t val_bcd)
{
	return ((val_bcd & 0xF) + (((val_bcd & 0xF0) >> 4) * 10));
}


bool g_ready_to_write_time = false;
uint8_t g_dbg_second = 0;
uint8_t g_dbg_minute = 5;
uint8_t g_dbg_hour = 11;
uint8_t g_dbg_weekday = 0;
uint8_t g_dbg_date = 27;
uint8_t g_dbg_month = 5;
uint8_t g_dbg_year = 24;
//rv8803_data_t ten_millisecond_count;
//			rv8803_data_t second;
//			rv8803_data_t minute;
//			rv8803_data_t hour;
//			rv8803_data_t weekday;
//			rv8803_data_t date;
//			rv8803_data_t month;
//			rv8803_data_t year;
uint8_t g_sec_count = 0;
void rv8803_write_current_tod(void)
{


//	while (!g_ready_to_write_time)
//	{
//        free_rtos_delay_ms(portTICK_PERIOD_MS);
//	}


	rv8803_tod_t rv8803_tod =
	{
	    // all in BCD except weekday
		.second = numbers_hex_to_bcd(g_dbg_second),
		.minute = numbers_hex_to_bcd(g_dbg_minute),
		.hour = numbers_hex_to_bcd(g_dbg_hour),
		.weekday = numbers_hex_to_bcd(g_dbg_weekday),
	    .date = numbers_hex_to_bcd(g_dbg_date),
		.month = numbers_hex_to_bcd(g_dbg_month),
		.year = numbers_hex_to_bcd(g_dbg_year)
	};

	rv8803_write_register_burst(RV8803_REGISTER_SECONDS, (uint8_t *)&rv8803_tod, sizeof(rv8803_tod_t));
	while (1)
	{
		free_rtos_delay_ms(1000);
//        g_sec_count = rv8803_tod.second;
    	rv8803_read_register(RV8803_REGISTER_SECONDS, &g_sec_count);
//        rv8803_read_register_burst(RV8803_REGISTER_SECONDS, (uint8_t *)&rv8803_tod, sizeof(rv8803_tod_t));
	}


}





