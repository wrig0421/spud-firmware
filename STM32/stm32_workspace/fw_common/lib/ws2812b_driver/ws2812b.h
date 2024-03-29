#if !defined(WS2812B_H)
#define WS2812B_H


#define STRIP_1_LENGTH    210
//#define STRIP_2_LENGTH    7
//#define STRIP_3_LENGTH    7
//#define STRIP_4_LENGTH    7
#define NUM_LEDS STRIP_1_LENGTH

#if !defined(STRIP_1_LENGTH) && (defined(STRIP_2_LENGTH) || defined(STRIP_3_LENGTH) || defined(STRIP_4_LENGTH))
#error "Please assign strip 0 as the first strip"
#endif
#if defined(STRIP_1_LENGTH) && (defined(STRIP_2_LENGTH) || defined(STRIP_3_LENGTH) || defined(STRIP_4_LENGTH))
#define MULTIPLE_STRIPS
#endif


typedef enum
{
#if defined(STRIP_1_LENGTH)
	STRIP_NUM_1 = 0,
#endif
#if defined(STRIP_2_LENGTH)
	STRIP_NUM_2,
#endif
#if defined(STRIP_3_LENGTH)
	STRIP_NUM_3,
#endif
#if defined(STRIP_4_LENGTH)
	STRIP_NUM_4,
#endif
#if defined(STRIP_5_LENGTH)
	STRIP_NUM_5,
#endif
#if defined(STRIP_6_LENGTH)
	STRIP_NUM_6,
#endif
#if defined(STRIP_7_LENGTH)
	STRIP_NUM_7,
#endif
#if defined(STRIP_8_LENGTH)
	STRIP_NUM_8,
#endif
#if defined(STRIP_9_LENGTH)
	STRIP_NUM_9,
#endif
	NUM_STRIPS,
    ALL_STRIPS = NUM_STRIPS
} strip_num_e;


// I want to add support for case of say strip 1 & 3 on all others off.
// Want to pass something like STRIP_1 | STRIP_3 turn on both!
typedef enum
{
	STRIP_BIT_NONE_SET = 0,
#if defined(STRIP_1_LENGTH)
	STRIP_BIT_1 = 1,
#endif
#if defined(STRIP_2_LENGTH)
	STRIP_BIT_2 = (1 << 1),
#endif
#if defined(STRIP_3_LENGTH)
	STRIP_BIT_3 = (1 << 2),
#endif
#if defined(STRIP_4_LENGTH)
	STRIP_BIT_4 = (1 << 3),
#endif
#if defined(STRIP_5_LENGTH)
	STRIP_BIT_5 = (1 << 4),
#endif
#if defined(STRIP_6_LENGTH)
	STRIP_BIT_6 = (1 << 5),
#endif
#if defined(STRIP_7_LENGTH)
	STRIP_BIT_7 = (1 << 6),
#endif
#if defined(STRIP_8_LENGTH)
	STRIP_BIT_8 = (1 << 7),
#endif
#if defined(STRIP_9_LENGTH)
	STRIP_BIT_9 = (1 << 8),
#endif
	STRIP_BIT_NUM_STRIPS = NUM_STRIPS,
	STRIP_BIT_NO_MORE_SET, 
	// brute force assignment below 
#if defined(STRIP_9_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4 | STRIP_BIT_5 | STRIP_BIT_6 | STRIP_BIT_7 | STRIP_BIT_8 | STRIP_BIT_9
#elif defined(STRIP_8_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4 | STRIP_BIT_5 | STRIP_BIT_6 | STRIP_BIT_7 | STRIP_BIT_8
#elif defined(STRIP_7_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4 | STRIP_BIT_5 | STRIP_BIT_6 | STRIP_BIT_7
#elif defined(STRIP_6_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4 | STRIP_BIT_5 | STRIP_BIT_6			
#elif defined(STRIP_5_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4 | STRIP_BIT_5
#elif defined(STRIP_4_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3 | STRIP_BIT_4
#elif defined(STRIP_3_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2 | STRIP_BIT_3
#elif defined(STRIP_2_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1 | STRIP_BIT_2
#elif defined(STRIP_1_LENGTH)
	STRIP_BIT_ALL_SET = STRIP_BIT_1
#else
    #error "No strips defined?  What are you trying to do?"
#endif
} strip_bit_e;


typedef uint8_t color_t;
typedef uint16_t strip_mask_t; // 16 strips max..


typedef struct
{
    color_t red;
    color_t green; 
    color_t blue;
} ws2812b_led_t;

typedef ws2812b_led_t* p_ws2812b_led_t;
typedef uint16_t* p_pwm_data_t;

bool ws2812_pixel_is_in_strip_range(strip_bit_e strip_bit, uint16_t pixel);
uint16_t ws2812_led_get_max_strip_size(const strip_mask_t strip_mask);
strip_bit_e ws2812_get_next_active_strip(const strip_mask_t strip_mask, const strip_bit_e prev_strip_bit);
uint16_t ws2812_get_num_active_animation_leds(const strip_mask_t strip_mask);
uint16_t ws2812_get_strip_size(const strip_bit_e strip_bit);
void ws2812b_reset(void);
void ws2812b_init(void);
void ws2812b_show(const strip_mask_t strip_mask);
void ws2812b_fill_pwm_buffer(const strip_bit_e strip_bit);
void ws2812b_set_led(const strip_bit_e strip_bit, uint16_t led_num, color_t red, color_t green, color_t blue);
void reset_ws2812b(void);

#endif

