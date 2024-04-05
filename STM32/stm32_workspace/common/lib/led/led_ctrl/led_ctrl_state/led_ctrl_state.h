// SRW
#if !defined(LED_CTRL_STATE_H)
#define LED_CTRL_STATE_H

#include <stdint.h>

typedef enum
{
    LED_CTRL_STATE_MASTER_DEMO,
    LED_CTRL_STATE_MASTER_FIXED
} led_ctrl_state_master_e;


typedef struct
{
    // byte 0
    uint8_t spell : 1;
    uint8_t white : 1;
    uint8_t solid : 1;
    uint8_t sparkle : 1;
    uint8_t sparkle_no_fill : 1;
    uint8_t rainbow : 1;
    uint8_t chase : 1;
    uint8_t chase_rainbow : 1;

    // byte 1
    uint8_t fade : 1;
    uint8_t twinkle : 1;
    uint8_t rsvd0 : 6;

    // byte 2
    uint8_t rsvd1;

    // byte 3
    uint8_t rsvd2;

    // these can be applied to each strip..
} led_animate_state_t;

typedef enum
{
	LED_STATE_FIRST = 0,
	LED_STATE_SPELL = LED_STATE_FIRST,
	//LED_STATE_MINT_NOHBZ,
	LED_STATE_WHITE_COLOR,
	LED_STATE_SOLID_COLOR,
	LED_STATE_SPARKLE_NO_FILL,
    LED_STATE_SPARKLE_FILL,
    LED_STATE_RAINBOW_CYCLE,
    LED_STATE_THEATER_CHASE,
    LED_STATE_THEATER_CHASE_RAINBOW,
    LED_STATE_FADE_IN_AND_OUT,
    LED_STATE_TWINKLE,
	LED_STATE_TWO_COLOR,
	LED_STATE_LAST = LED_STATE_TWO_COLOR,
#if (NUM_ACTIVE_STRIPS > 2)
	LED_STATE_SPELL_AND_SPARKLE,
	LED_STATE_SPELL_AND_RAINBOW
#endif
    NUM_LED_STATES,
    LED_STATE_SRW_DEBUG,
	// future states below
	//LED_STATE_FADE_IN_AND_OUT_RANDOM,
    //LED_STATE_METEOR,
    //LED_STATE_STROBE,
    //LED_STATE_SPELL_SOLID_WHITE_COLOR,
    //LED_STATE_KITT,
    //LED_STATE_CYCLONE_BOUNCE,
    //LED_STATE_RANDOM,
    //LED_STATE_RUNNING_LIGHTS,
    //LED_STATE_FIRE,
    //LED_STATE_BOUNCING_BALLS,
    //LED_STATE_BOUNCING_BALLS_RANDOM,
} led_state_e;


typedef struct
{
	led_ctrl_state_master_e		led_state_master;
	led_state_e					led_state;
	uint16_t					led_state_current_iteration;
} led_ctrl_state_info_t;


typedef struct
{
	uint16_t				led_state_max_iteration;
	uint16_t				led_state_iteration_delay_ms;
} led_ctrl_state_iterations_t;




#endif
