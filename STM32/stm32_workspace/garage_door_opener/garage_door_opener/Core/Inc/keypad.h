#if !defined(KEYPAD_H)
#define KEYPAD_H

#include <stdint.h>
#include <stdbool.h>

#define KEYPAD_PASSWORD_LENGTH			8
#define KEYPAD_MAX_PASSWORD_ATTEMPTS	5

typedef struct
{
	uint8_t col_size;
	uint8_t row_size;
	uint16_t last_key;
} keypad_t;

typedef enum
{
	KEYPAD_ROW_ONE = 0,
	KEYPAD_ROW_FIRST = KEYPAD_ROW_ONE,
	KEYPAD_ROW_TWO,
	KEYPAD_ROW_THREE,
	KEYPAD_ROW_FOUR,
	KEYPAD_NUM_ROWS
} keypad_row_e;


typedef enum
{
	KEYPAD_COL_ONE = 0,
	KEYPAD_COL_FIRST = KEYPAD_COL_ONE,
	KEYPAD_COL_TWO,
	KEYPAD_COL_THREE,
	KEYPAD_NUM_COLS
} keypad_col_e;


typedef enum
{
	KEYPAD_STATE_SCAN,
	KEYPAD_STATE_BTN_PRESS,
	KEYPAD_STATE_PASSWORD_MATCH,
	KEYPAD_STATE_LOCKOUT
} keypad_state_e;


void keypad_init(void);
bool keypad_scan(void);
uint8_t keypad_button_pressed(void);
uint8_t keypad_lookup(keypad_row_e row, keypad_col_e col);
bool keypad_password_check(uint8_t *user_input);


#endif
