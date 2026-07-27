
#if !defined(FLASH_INFO_H)
#define FLASH_INFO_H
#include <limits.h>
#include <stdint.h>
#include "led_ctrl_state.h"
#include "led_animate.h"
#include "led_ctrl_color.h"
#include "led_ctrl_brightness.h"
#include "version.h"

//#define FLASH_BASE            (0x08000000UL) /*!< FLASH(up to 256 KB) base address */
//#define FLASH_END             (0x0803FFFFUL) /*!< FLASH END address                */
//#define FLASH_BANK1_END       (0x0803FFFFUL) /*!< FLASH END address of bank1       */

//#define FLASH_BANK_SIZE                    (FLASH_SIZE)
//#define FLASH_PAGE_SIZE                    ((uint32_t)0x800)

#define FLASH_INFO_SUB_BLOCK_SECTOR_SIZE_BYTES      (2048)

#define FLASH_START_ADDRESS                         ((uint32_t)0x08000000)
#define FLASH_STOP_ADDRESS                         	((uint32_t)0x08020000)

#define FLASH_NUM_FLASH_PAGES						(FLASH_BANK1_END - FLASH_BASE) / FLASH_INFO_SUB_BLOCK_SECTOR_SIZE_BYTES
#define FLASH_MAX_PAGE_NUMBER


#define FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET       ((uint32_t)(FLASH_NUM_FLASH_PAGES - 3) * FLASH_INFO_SECTOR_SIZE)
#define FLASH_SUB_BLOCK_STATUS_ADDRESS_OFFSET   	((uint32_t)(FLASH_NUM_FLASH_PAGES - 2) * FLASH_INFO_SECTOR_SIZE)
#define FLASH_SUB_BLOCK_IMAGE_ADDRESS_OFFSET    (	(uint32_t)(FLASH_NUM_FLASH_PAGES - 2) * FLASH_INFO_SECTOR_SIZE)

#define FLASH_SUB_BLOCK_CONFIG_PAGE_START			(FLASH_NUM_FLASH_PAGES - 3)
#define FLASH_SUB_BLOCK_STATUS_PAGE_START			(FLASH_NUM_FLASH_PAGES - 2)
#define FLASH_SUB_BLOCK_IMAGE_PAGE_START			(FLASH_NUM_FLASH_PAGES - 1)

#define FLASH_INFO_DEFAULT_IMAGE_SLOT   FLASH_INFO_IMAGE_SLOT_1
#define FLASH_INFO_MINI_MAIN_SLOT       FLASH_INFO_MINI_MAIN_SLOT
#define FLASH_INFO_SUB_BLOCK_SIZE       256
#define FLASH_INFO_SECTOR_SIZE          (8 * FLASH_INFO_SUB_BLOCK_SIZE) // 2 kB


typedef enum
{
    FLASH_INFO_IMAGE_SLOT_0 = 0,
    FLASH_INFO_MINI_MAIN_SLOT = FLASH_INFO_IMAGE_SLOT_0,
    FLASH_INFO_IMAGE_SLOT_1,
    FLASH_INFO_IMAGE_SLOT_2,
    NUM_FLASH_INFO_IMAGE_SLOT
} flash_info_image_slot_t;


typedef enum
{
    FLASH_INFO_SUB_BLOCK_CONFIG,
    FLASH_INFO_SUB_BLOCK_STATUS,
    FLASH_INFO_SUB_BLOCK_IMAGE,
    NUM_FLASH_INFO_SUB_BLOCKS
} flash_info_sub_block_t;

typedef enum
{
	FLASH_INFO_HW_REV_SPUDGLO_BABY_DINOSAUR_V1P0,
	FLASH_INFO_HW_REV_SPUDGLO_BUSINESS_CARD_V1P0,
	FLASH_INFO_HW_REV_SPUDGLO_BUSINESS_CARD_V2P0,
	FLASH_INFO_HW_REV_SPUDGLO_DRIVER_V3P1,
	FLASH_INFO_HW_REV_SPUDGLO_DRIVER_V4P1,
	FLASH_INFO_HW_REV_SPUDGLO_DRIVER_V4P2,
	FLASH_INFO_HW_REV_SPUDGLO_DRIVER_V4P3,
	FLASH_INFO_HW_REV_SPUDGLO_DRIVER_V4P4,
	FLASH_INFO_HW_REV_SPUDGLO_DRIVER_V5P0,
	FLASH_INFO_HW_REV_SPUDGLO_DRIVER_V6P0,
	FLASH_INFO_HW_REV_SPUDGLO_DRIVER_V7P0,
	FLASH_INFO_HW_REV_SPUDGLO_DRIVER_V8P0,

	FLASH_INFO_HW_REV_LAST_ENTRY = UINT16_MAX - 1 // force UINT16 maximum!
} flash_info_hw_rev_e;

typedef version_date_and_time_t flash_info_fw_version_t;	// 8 B total


#pragma pack(1)
typedef struct
{
	uint8_t strip_1_enabled	: 1;
	uint8_t strip_2_enabled	: 1;
	uint8_t strip_3_enabled	: 1;
	uint8_t	rsvd			: 5;
} flash_info_strip_enable_t;



typedef struct
{
	union
	{
		uint8_t flat_color_1;
		struct
		{
			uint8_t white           : 1;
			uint8_t red             : 1;
			uint8_t dark_red        : 1;
			uint8_t maroon          : 1;
			uint8_t salmon          : 1;
			uint8_t orange_red      : 1;
			uint8_t orange          : 1;
			uint8_t gold            : 1;
		};
	};
	union
	{
		uint8_t flat_color_2;
		struct
		{
			uint8_t green           : 1;
			uint8_t mint            : 1;
			uint8_t forest_green    : 1;
			uint8_t teal            : 1;
			uint8_t cyan            : 1;
			uint8_t aqua_marine     : 1;
			uint8_t blue            : 1;
			uint8_t navy            : 1;
		};
	};
	union
	{
		uint8_t flat_color_3;
		struct
		{
			uint8_t dark_blue       : 1;
			uint8_t purple          : 1;
			uint8_t violet          : 1;
			uint8_t indigo          : 1;
			uint8_t plum            : 1;
			uint8_t pink            : 1;
			uint8_t hot_pink        : 1;
			uint8_t deep_pink       : 1;
		};
	};
	union
	{
		uint8_t flat_color_4;
		struct
		{
			uint8_t brown           : 1;
			uint8_t chocolate       : 1;
			uint8_t yellow          : 1;
			uint8_t gray            : 1;
			uint8_t silver          : 1;
			uint8_t black           : 1;
			uint8_t lime            : 1;
			uint8_t magenta         : 1;
		};
	};
	union
	{
		uint8_t flat_color_5;
		struct
		{

			uint8_t olive           : 1;
			uint8_t khaki           : 1;
			uint8_t lawn_green      : 1;
			uint8_t spring_green    : 1;
			uint8_t midnight_blue   : 1;
			uint8_t blue_violet     : 1;
			uint8_t dark_magenta    : 1;
			uint8_t tan            	: 1;
		};
	};
	uint8_t flat_color_6;					// 1 B
	uint8_t flat_color_7;					// 1 B
	uint8_t flat_color_8;					// 1 B
} flash_info_color_select_t;				// 8 B total


typedef struct
{
	union
	{
		uint8_t flat_animation_1;
		struct
		{
			uint8_t spell           : 1;
			uint8_t solid_white     : 1;
			uint8_t solid_color     : 1;
			uint8_t sparkle_no_fill : 1;
			uint8_t sparkle_fill    : 1;
			uint8_t rainbow         : 1;
			uint8_t chase           : 1;
			uint8_t chase_rainbow   : 1;
		};
	};
	union
	{
		uint8_t flat_animation_2;
		struct
		{
			uint8_t fade            : 1;
			uint8_t twinkle         : 1;
			uint8_t running_lights	: 1;
			uint8_t fire			: 1;
			uint8_t meteor			: 1;
			uint8_t strobe			: 1;
			uint8_t rsvd			: 2;
		};
	};
	uint8_t flat_animation_3;			// 1 B
	uint8_t flat_animation_4;			// 1 B
	uint8_t flat_animation_5;			// 1 B
	uint8_t flat_animation_6;			// 1 B
    uint8_t	flat_animation_7;			// 1 B
    uint8_t flat_animation_8;			// 1 B
} flash_info_animation_select_t;		// 8 B total


typedef union
{
	struct
	{
		uint8_t 				brightness_100p : 1;
//		uint8_t 				brightness_75p  : 1;
		uint8_t 				brightness_50p  : 1;
		uint8_t 				brightness_25p  : 1;
		uint8_t 				brightness_1p   : 1;
		uint8_t 				rsvd0           : 3;
	};
	uint8_t 					flat_brightness;		// 1 B
} flash_info_brightness_select_t;						// 1 B total


typedef union
{
	struct
	{
		uint8_t 				speed_1000p     : 1;
		uint8_t 				speed_500p      : 1;
		uint8_t 				speed_100p      : 1;
		uint8_t 				speed_50p       : 1;
		uint8_t 				speed_25p       : 1;
		uint8_t 				rsvd0           : 3;
	};
	uint8_t 					flat_speed;				// 1 B
} flash_info_speed_select_t;							// 1 B total


typedef struct
{
	uint8_t     				num_strips;				// 1 B 		0x00
	flash_info_strip_enable_t   strip_enable;					// 1 B		0x01
	uint8_t     				rsvd1;					// 1 B		0x02
	uint8_t     				rsvd2;					// 1 B	    0x03

	uint16_t    				strip_1_length;			// 2 B		0x04
	uint16_t    				strip_2_length;			// 2 B		0x06
	uint16_t    				strip_3_length;			// 2 B		0x08

	uint16_t    				rsvd4[4];					// 2 B		0x0A
} flash_info_strip_config_t; 							// 24 B total


typedef struct
{
	// future sub blocks go here
	uint32_t                    uid0;					// 4 B
	uint32_t                    uid1;					// 4 B
	uint32_t                    uid2;					// 4 B
} flash_info_uid_t;										// 12 B total


typedef struct
{
	flash_info_uid_t			uid; 					// 12 B		0x00
	flash_info_hw_rev_e			hw_rev;					// 1 B		0x0C
	uint16_t 					pcb_serial_number; 		// 1 B		0x0D
	uint8_t 					rsvd[22]; 				// 20 B		0x12
} flash_info_device_info_t;								// 36 B total


typedef struct
{
    flash_info_strip_config_t       strip_config;           // 24 B 	0x0000

    flash_info_color_select_t       strip_1_color;          // 8 B 		0x0018
    flash_info_color_select_t       strip_2_color;          // 8 B 		0x0020
    flash_info_color_select_t       strip_3_color;          // 8 B 		0x0028

    flash_info_animation_select_t   strip_1_animation;      // 8 B 		0x0030
    flash_info_animation_select_t   strip_2_animation;      // 8 B 		0x0038
    flash_info_animation_select_t   strip_3_animation;      // 8 B 		0x0040

    flash_info_brightness_select_t  strip_1_brightness;     // 1 B 		0x0041
    flash_info_brightness_select_t  strip_2_brightness;     // 1 B 		0x0042
    flash_info_brightness_select_t  strip_3_brightness;     // 1 B 		0x0043

    flash_info_speed_select_t       strip_1_speed;          // 1 B 		0x0044
    flash_info_speed_select_t       strip_2_speed;          // 1 B 		0x0045
    flash_info_speed_select_t       strip_3_speed;          // 1 B 		0x0046

    int                        		rand_seed;				// 4 B		0x0050

    // future items go here!

    // future additions go here
} flash_info_strip_info_t;


typedef struct
{
	flash_info_strip_info_t			strip_info;			// 	[0x0000, 0x0050)
    flash_info_device_info_t		device_info;
	flash_info_uid_t				uid;				//  [0x0050, 0x005C)
	flash_info_fw_version_t			fw_version;			//  [0x005C, 0x0066)
	// may need to pad this out...  technically packing is 1 byte alignment.  Be careful though..
} flash_info_config_t;


typedef union
{
    struct
    {
    	flash_info_config_t    	flash_info_config;
        uint8_t                 rsvd[FLASH_INFO_SECTOR_SIZE - sizeof(flash_info_config_t)];
    };
    uint8_t                     flat_data_uint8[FLASH_INFO_SECTOR_SIZE];
    uint16_t                    flat_data_uint16[FLASH_INFO_SECTOR_SIZE / sizeof(uint16_t)];
    uint32_t                    flat_data_uint32[FLASH_INFO_SECTOR_SIZE / sizeof(uint32_t)];
    uint64_t                    flat_data_uint64[FLASH_INFO_SECTOR_SIZE / sizeof(uint64_t)];
} flash_info_block_t;

#pragma pack(0)

typedef flash_info_block_t* p_flash_info_block_t;


p_flash_info_block_t flash_info_block_handle(void);
bool flash_info_color_enabled_on_strip(strip_bit_e strip_bit, led_color_e color);
led_brightness_e flash_info_brightness_enabled_on_strip(strip_bit_e strip_bit);
led_speed_e flash_info_speed_enabled_on_strip(strip_bit_e strip_bit);

void flash_info_block_init(void);
void flash_info_write_data(void *p_data, uint16_t address, uint16_t num_bytes);
void flash_info_init(void);
void flash_info_led_color_is_enabled(const strip_mask_t strip_mask, led_color_e color, bool *ret_val);
void flash_info_led_state_is_enabled(const strip_mask_t strip_mask, led_state_e state, bool *ret_val);
void flash_info_brightness_level_is_enabled(const strip_mask_t strip_mask, led_brightness_e *led_brightness_enabled);
void flash_info_speed_is_enabled(const strip_mask_t strip_mask, led_speed_e *led_speed);
uint8_t flash_info_num_strips(void);
uint8_t flash_info_num_enabled_strips(void);
bool flash_info_strip_1_is_enabled(void);
bool flash_info_strip_2_is_enabled(void);
bool flash_info_strip_3_is_enabled(void);
void flash_info_strip_length(const strip_mask_t mask, uint8_t *strip_length);
uint16_t flash_info_strip_1_length(void);
uint16_t flash_info_strip_2_length(void);
uint16_t flash_info_strip_3_length(void);
flash_info_hw_rev_e flash_info_read_hw_rev(void);
uint16_t flash_info_read_serial_number(void);
void flash_info_read_uid(uint32_t* p_uid);
void flash_info_firmware_version(void);




#endif
