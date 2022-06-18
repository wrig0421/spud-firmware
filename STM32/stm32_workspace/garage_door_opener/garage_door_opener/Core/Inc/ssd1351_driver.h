/*
 * ssd1351_driver.h
 *
 *  Created on: Aug 2, 2020
 *      Author: spud
 */

#ifndef INC_SSD1351_DRIVER_H_
#define INC_SSD1351_DRIVER_H_

#include "fonts.h"

#define SSD1351_CMD_UNLOCK_BYTE		0x12
#define COLUMNS 128 // Not sure of this SRW
#define ROWS 128
#define SSD1351_PIXEL_WIDTH			128
#define SSD1351_PIXEL_HEIGHT		128
#define SSD1351_BYTES_PER_PIXEL		2
#define SSD1351_BUFFER_SIZE_8BIT	SSD1351_PIXEL_WIDTH * SSD1351_PIXEL_HEIGHT  * SSD1351_BYTES_PER_PIXEL / sizeof(uint8_t)
#define SSD1351_BUFFER_SIZE_16BIT	SSD1351_PIXEL_WIDTH * SSD1351_PIXEL_HEIGHT  * SSD1351_BYTES_PER_PIXEL / sizeof(uint16_t)
#define SSD1351_TOTAL_PIXELS		SSD1351_PIXEL_HEIGHT * SSD1351_PIXEL_WIDTH


typedef enum
{
	SSD1351_CMD_SET_COLUMN_ADDRESS					= 0x15,
	SSD1351_CMD_SET_ROW_ADDRESS						= 0x75,
	SSD1351_CMD_WRITE_RAM							= 0x5C,
	SSD1351_CMD_READ_RAM							= 0x5D,
	SSD1351_CMD_SET_REMAP_COLOR_DEPTH				= 0xA0,
	SSD1351_CMD_SET_DISP_START_LINE					= 0xA1,
	SSD1351_CMD_SET_DISP_OFFSET						= 0xA2,
	SSD1351_CMD_SET_DISP_MODE_OFF					= 0xA4,
	SSD1351_CMD_SET_DISP_MODE_ON					= 0xA5,
	SSD1351_CMD_SET_DISP_MODE_NORMAL				= 0xA6,
	SSD1351_CMD_SET_DISP_MODE_INVERSE				= 0xA7,
	SSD1351_CMD_FUNCTION_SELECTION					= 0xAB,
	SSD1351_CMD_NOP									= 0xAD,
	SSD1351_CMD_SET_SLEEP_MODE_ON					= 0xAE,
	SSD1351_CMD_SET_SLEEP_MODE_OFF					= 0xAF,
	SSD1351_CMD_SET_RESET_PRECHARGE_PERIOD			= 0xB1,
	SSD1351_CMD_DISP_ENHANCEMENT					= 0xB2,
	SSD1351_CMD_FRONT_CLOCK_DIVIDER					= 0xB3,
	SSD1351_CMD_SET_SEGMENT_LOW_VOLTAGE				= 0xB4,
	SSD1351_CMD_SET_GPIO							= 0xB5,
	SSD1351_CMD_SET_SECOND_PRECHARGE_PERIOD			= 0xB6,
	SSD1351_CMD_LUT									= 0xB8,
	SSD1351_CMD_USE_LUT								= 0xB9,
	SSD1351_CMD_SET_PRECHARGE_VOLTAGE				= 0xBB,
	SSD1351_CMD_SET_VCOMH_VOLTAGE					= 0xBE,
	SSD1351_CMD_SET_CONTRAST_CURRENT				= 0xC1,
	SSD1351_CMD_MASTER_CONTRAST_CURRENT_CTRL		= 0xC7,
	SSD1351_CMD_SET_MUX_RATIO						= 0xCA,
	SSD1351_CMD_SET_CMD_LOCK						= 0xFD,
	SSD1351_CMD_HORIZONTAL_SCROLL					= 0x96,
	SSD1351_CMD_STOP_MOVING							= 0x9E,
	SSD1351_CMD_START_MOVING						= 0x9F,
} ssd1351_cmd_e;


typedef enum
{
	COLOR_16BIT_BLACK		= 0x0,
	COLOR_16BIT_WHITE		= 0xFFFF,
	COLOR_16BIT_RED			= 0xF800,
	COLOR_16BIT_BLUE		= 0x001F,
	COLOR_16BIT_YELLOW		= 0xFFE0,
	COLOR_16BIT_GREEN		= 0x0400,
	COLOR_16BIT_PURPLE		= 0x8010,
	COLOR_16BIT_MAROON		= 0x8000,
	COLOR_16BIT_ORANGE		= 0xFD20,
	COLOR_16BIT_GOLD		= 0xFEA0,
	COLOR_16BIT_LIME		= 0x07E0,
	COLOR_16BIT_AQUA		= 0x07FF,
	COLOR_16BIT_MAGENTA		= 0xF81F,
	COLOR_16BIT_PINK		= 0xF8B2,
	COLOR_16BIT_CHOCOLATE	= 0xD343,
	COLOR_16BIT_GRAY		= 0x8410,
} color_16bit_e;


typedef struct
{
	union
	{
		uint8_t	ssd1351_disp_buffer_uint8[SSD1351_BUFFER_SIZE_8BIT];
		uint16_t ssd1351_disp_buffer_uint16[SSD1351_BUFFER_SIZE_16BIT];
	};
} ssd1351_buffer_t;


typedef struct
{
	uint8_t x;
	uint8_t y;
} ssd1351_coordinates_t;


void ssd1351_init(void);
void ssd1351_fill_screen(color_16bit_e color);
void ssd1351_fill_solid_color(color_16bit_e color);
void ssd1351_update(void);
void ssd1351_delay_ms(uint32_t delay_ms);
void ssd1351_write_cmd(ssd1351_cmd_e cmd);
void ssd1351_byte_write_data(uint8_t data);
void ssd1351_block_write_data(uint8_t *data, uint32_t len);
void ssd1351_set_pixel_address(uint8_t column, uint8_t row);
void ssd1351_draw_pixel(uint8_t x, uint8_t y, color_16bit_e color);
void ssd1351_draw_horizontal_line(uint8_t x0, uint8_t x1);
void ssd1351_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void ssd1351_write_buffer_to_display(void);
void ssd1351_clear_screen(void);
void ssd1351_reset_ram_address(void);
void ssd1351_write_int(color_16bit_e color, font_t font, int8_t n);
void ssd1351_write_string(color_16bit_e color, font_t font, char *line);
void ssd1351_write_char(color_16bit_e color, font_t font, char c);
void ssd1351_printf(char *string);
//void ssd1351_printf(color_16bit_e color, font_t font, const char *format, ...);

#endif /* INC_SSD1351_DRIVER_H_ */
