
#include "main.h"
#include "keypad.h"


#define KEYPAD_UNITS	1
#define KEYPAD_ROWS		4
#define KEYPAD_COLS		3
#define KEYS			12

#define KEY_PRESSED		1
#define KEY_RELEASED	0


#define KEYPAD_ROW_ONE_PIN		GPIO_PIN_5
#define KEYPAD_ROW_TWO_PIN		GPIO_PIN_8
#define KEYPAD_ROW_THREE_PIN	GPIO_PIN_9
#define KEYPAD_ROW_FOUR_PIN		GPIO_PIN_12

#define KEYPAD_COL_ONE_PIN		GPIO_PIN_2
#define KEYPAD_COL_TWO_PIN		GPIO_PIN_2
#define KEYPAD_COL_THREE_PIN	GPIO_PIN_3


// pin definitions
// PB5  -> R1
// PB8  -> R2
// PB9  -> R3
// PB12 -> R4
// PA2  -> C1
// PB2  -> C2
// PA3  -> C3

uint8_t g_keys[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS];
uint8_t g_password[KEYPAD_PASSWORD_LENGTH] = {4, 4, 2, 6, 6, 1, 3, 3};
uint8_t g_last_button_pressed = 0;

void keypad_init(void)
{
	// '*' = 10, '0' = 11, '#' = 12
	uint8_t setting = 1;
	for (keypad_row_e row = KEYPAD_ROW_FIRST; row < KEYPAD_NUM_ROWS; row++)
	{
		for (keypad_col_e col = KEYPAD_COL_FIRST; col < KEYPAD_NUM_COLS; col++)
		{
			g_keys[row][col] = setting++;
		}
	}
}


bool keypad_password_check(uint8_t *user_input)
{
	for(int i = 0; i < KEYPAD_PASSWORD_LENGTH; i++)
	{
		if (g_password[i] != user_input[i]) return false;
	}
	return true;
}


uint8_t keypad_lookup(keypad_row_e row, keypad_col_e col)
{
	return (g_keys[row][col]); // '*' = 10, '0' = 11, '#' = 12
}


uint8_t keypad_button_pressed(void)
{
	return g_last_button_pressed;
}

keypad_col_e col_index = KEYPAD_COL_ONE;
keypad_row_e row_index = KEYPAD_ROW_ONE;

bool keypad_scan(void)
{
	bool ret_val = false;
	uint16_t row_pin = 0;
	uint16_t col_pin = 0;
	GPIO_TypeDef *col_port = 0;
	//static keypad_col_e col_index = KEYPAD_COL_ONE;
	//static keypad_row_e row_index = KEYPAD_ROW_ONE;
	switch(row_index)
	{
		case KEYPAD_ROW_ONE: row_pin = KEYPAD_ROW_ONE_PIN; break;
		case KEYPAD_ROW_TWO: row_pin = KEYPAD_ROW_TWO_PIN; break;
		case KEYPAD_ROW_THREE: row_pin = KEYPAD_ROW_THREE_PIN; break;
		case KEYPAD_ROW_FOUR: row_pin = KEYPAD_ROW_FOUR_PIN; break;
		default: while(1); break;
	}
	switch(col_index)
	{
		case KEYPAD_COL_ONE:
			col_pin = KEYPAD_COL_ONE_PIN;
			col_port = GPIOA;
		break;
		case KEYPAD_COL_TWO:
			col_pin = KEYPAD_COL_TWO_PIN;
			col_port = GPIOB;
		break;
		case KEYPAD_COL_THREE:
			col_pin = KEYPAD_COL_THREE_PIN;
			col_port = GPIOA;
		break;
		default: while(1); break;
	}
	HAL_GPIO_WritePin(col_port, col_pin, GPIO_PIN_SET);
	if (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, row_pin))
	{
		while (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, row_pin));
		ret_val = true;
	}
	HAL_GPIO_WritePin(col_port, col_pin, GPIO_PIN_RESET);
	if (ret_val)
	{
		g_last_button_pressed = keypad_lookup(row_index, col_index);
		row_index = KEYPAD_ROW_ONE;
		col_index = KEYPAD_COL_ONE;
	}
	else if (KEYPAD_ROW_FOUR == row_index++)
	{
		if (KEYPAD_COL_THREE == col_index)
		{
			row_index = KEYPAD_ROW_ONE;
			col_index = KEYPAD_COL_ONE;
		}
		else
		{
			row_index = KEYPAD_ROW_ONE;
			col_index++;
		}
	}
	//else row_index++;
	return ret_val;
	/*
	for (keypad_row_e key_row = KEYPAD_ROW_FIRST; key_row < KEYPAD_NUM_ROWS; key_row++)
	{
		switch(row)
		{
			case KEYPAD_ROW_ONE: row_pin = KEYPAD_ROW_ONE_PIN; break;
			case KEYPAD_ROW_TWO: row_pin = KEYPAD_ROW_TWO_PIN; break;
			case KEYPAD_ROW_THREE: row_pin = KEYPAD_ROW_THREE_PIN; break;
			case KEYPAD_ROW_FOUR: row_pin = KEYPAD_ROW_FOUR_PIN; break;
		}
		if (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, row_pin))
		{
			return key_row;
		}
	}
	*/
}
