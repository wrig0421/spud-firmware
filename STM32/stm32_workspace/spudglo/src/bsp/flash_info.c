#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include "stm32l4xx_hal.h"
#include "version.h"
#include "animate_led.h"
#include "flash_info.h"
#include "flash_access.h"
#include "pkt.h"

#define FLASH_INFO_DEFAULT_IMAGE_SLOT   FLASH_INFO_IMAGE_SLOT_1
#define FLASH_INFO_MINI_MAIN_SLOT       FLASH_INFO_MINI_MAIN_SLOT
#define FLASH_INFO_SUB_BLOCK_SIZE       256
#define FLASH_INFO_SECTOR_SIZE          (8 * FLASH_INFO_SUB_BLOCK_SIZE) // 2 kB
#define MAX_NUM_STRIPS  3


#pragma pack(1)
typedef union
{
    uint32_t data[3];
} uint96_t;


typedef union
{
    version_date_and_time_t     fw_version_date;
    uint8_t                     flat_data_uint8[sizeof(version_date_and_time_t)];
} flash_info_fw_version_t;


typedef struct
{
    flash_info_strip_config_t       strip_config;           // 0x0000

    flash_info_color_select_t       strip_1_color;          // 0x000A
    flash_info_color_select_t       strip_2_color;          // 0x000E
    flash_info_color_select_t       strip_3_color;          // 0x0013

    flash_info_animation_select_t   strip_1_animation;      // 0x0015
    flash_info_animation_select_t   strip_2_animation;      // 0x0017
    flash_info_animation_select_t   strip_3_animation;      // 0x0019

    flash_info_brightness_select_t  strip_1_brightness;     // 0x001A
    flash_info_brightness_select_t  strip_2_brightness;     // 0x001B
    flash_info_brightness_select_t  strip_3_brightness;     // 0x001C

    flash_info_speed_select_t       strip_1_speed;          // 0x001D
    flash_info_speed_select_t       strip_2_speed;          // 0x001E
    flash_info_speed_select_t       strip_3_speed;          // 0x001F

    uint32_t                        rand_seed;

    all_colors_e                    strip_current_color;

    led_state_e                     strip_current_animation;

    // future additions go here
} flash_info_strip_info_t;


typedef struct
{
    flash_info_strip_info_t     strip_info;                                         // 0x00
    uint8_t                     strip_info_fill[FLASH_INFO_SUB_BLOCK_SIZE - sizeof(flash_info_strip_info_t)];

    // future sub blocks go here
    uint32_t                    uuid0;
    uint32_t                    uuid1;
    uint32_t                    uuid2;
} flash_info_data_t;

typedef union
{
    struct
    {
        flash_info_data_t       flash_info_data;
        uint8_t                 rsvd[FLASH_INFO_SECTOR_SIZE - sizeof(flash_info_data_t)];
    };
    uint8_t                     flat_data_uint8[FLASH_INFO_SECTOR_SIZE];
    uint16_t                    flat_data_uint16[FLASH_INFO_SECTOR_SIZE / sizeof(uint16_t)];
    uint32_t                    flat_data_uint32[FLASH_INFO_SECTOR_SIZE / sizeof(uint32_t)];
    uint64_t                    flat_data_uint64[FLASH_INFO_SECTOR_SIZE / sizeof(uint64_t)];
} flash_info_block_t;
#pragma pack(0)

flash_info_block_t  g_flash_info_block;


bool flash_info_color_enabled(strip_num_e strip_num,
                              all_colors_e color)
{
    bool return_val = false;
    flash_info_color_select_t strip_color_mask;
    switch (strip_num)
    {
#if defined(STRIP_1_LENGTH)
        case STRIP_NUM_1:
            strip_color_mask = g_flash_info_block.flash_info_data.strip_info.strip_1_color;
        break;
#endif
#if defined(STRIP_2_LENGTH)
        case STRIP_NUM_2:
            strip_color_mask = g_flash_info_block.flash_info_data.strip_info.strip_2_color;
        break;
#endif
#if defined(STRIP_3_LENGTH)
        case STRIP_NUM_3:
            strip_color_mask = g_flash_info_block.flash_info_data.strip_info.strip_3_color;
        break;
#endif
        // future strip num support goes here!
        default:
            while(1); // HW limited to 3 strips
        break;
    }
//    switch (color)
//    {
//        case COLORS_RED:
//            if (strip_color_mask.red) return_val = true;
//        break;
//        case COLORS_DARK_RED:
//            if (strip_color_mask.dark_red) return_val = true;
//        break;
//        case COLORS_MAROON:
//            if (strip_color_mask.maroon) return_val = true;
//        break;
//        case COLORS_SALMON:
//            if (strip_color_mask.salmon) return_val = true;
//        break;
//        case COLORS_ORANGE_RED:
//            if (strip_color_mask.orange_red) return_val = true;
//        break;
//        case COLORS_ORANGE:
//            if (strip_color_mask.orange) return_val = true;
//        break;
//        case COLORS_GOLD:
//            if (strip_color_mask.gold) return_val = true;
//        break;
//        case COLORS_YELLOW:
//            if (strip_color_mask.yellow) return_val = true;
//        break;
//        case COLORS_GREEN:
//            if (strip_color_mask.green) return_val = true;
//        break;
//        case COLORS_SPRING_GREEN:
//            if (strip_color_mask.spring_green) return_val = true;
//        break;
//        case COLORS_FOREST_GREEN:
//            if (strip_color_mask.forest_green) return_val = true;
//        break;
//        case COLORS_TEAL:
//            if (strip_color_mask.teal) return_val = true;
//        break;
//        case COLORS_CYAN:
//            if (strip_color_mask.cyan) return_val = true;
//        break;
//        case COLORS_AQUA_MARINE:
//            if (strip_color_mask.aqua_marine) return_val = true;
//        break;
//        case COLORS_BLUE:
//            if (strip_color_mask.blue) return_val = true;
//        break;
//        case COLORS_NAVY:
//            if (strip_color_mask.navy) return_val = true;
//        break;
//        case COLORS_DARK_BLUE:
//            if (strip_color_mask.dark_blue) return_val = true;
//        break;
//        case COLORS_PURPLE:
//            if (strip_color_mask.purple) return_val = true;
//        break;
//        case COLORS_VIOLET:
//            if (strip_color_mask.violet) return_val = true;
//        break;
//        case COLORS_INDIGO:
//            if (strip_color_mask.indigo) return_val = true;
//        break;
//        case COLORS_PLUM:
//            if (strip_color_mask.plum) return_val = true;
//        break;
//        case COLORS_PINK:
//            if (strip_color_mask.pink) return_val = true;
//        break;
//        case COLORS_HOT_PINK:
//            if (strip_color_mask.hot_pink) return_val = true;
//        break;
//        case COLORS_DEEP_PINK:
//            if (strip_color_mask.deep_pink) return_val = true;
//        break;
//        case COLORS_BROWN:
//            if (strip_color_mask.brown) return_val = true;
//        break;
//        case COLORS_CHOCOLATE:
//            if (strip_color_mask.chocolate) return_val = true;
//        break;
//        case COLORS_WHITE:
//            if (strip_color_mask.white) return_val = true;
//        break;
//        case COLORS_GRAY:
//            if (strip_color_mask.gray) return_val = true;
//        break;
//        case COLORS_SILVER:
//            if (strip_color_mask.silver) return_val = true;
//        break;
//        case COLORS_BLACK:
//            if (strip_color_mask.black) return_val = true;
//        break;
//        default:
//            while(1);
//        break;
//    }
    return return_val;
}


bool flash_info_animation_enabled(strip_num_e strip_num,
                                  led_state_e animation)
{
    bool return_val = false;
    flash_info_animation_select_t strip_animation_mask;
    switch (strip_num)
    {
#if defined(STRIP_1_LENGTH)
        case STRIP_NUM_1:
            strip_animation_mask = g_flash_info_block.flash_info_data.strip_info.strip_1_animation;
        break;
#endif
#if defined(STRIP_2_LENGTH)
        case STRIP_NUM_2:
            strip_animation_mask = g_flash_info_block.flash_info_data.strip_info.strip_2_animation;
        break;
#endif
#if defined(STRIP_3_LENGTH)
        case STRIP_NUM_3:
            strip_animation_mask = g_flash_info_block.flash_info_data.strip_info.strip_3_animation;
        break;
#endif
        // future strip num support goes here!
        default:
            while(1); // HW limited to 3 strips
        break;
    }
    switch (animation)
    {
        case LED_STATE_SPELL:
            if (strip_animation_mask.spell) return_val = true;
        break;
        case LED_STATE_WHITE_COLOR:
            if (strip_animation_mask.solid_white) return_val = true;
        break;
        case LED_STATE_SOLID_COLOR:
            if (strip_animation_mask.solid_color) return_val = true;
        break;
        case LED_STATE_SPARKLE_NO_FILL:
            if (strip_animation_mask.sparkle_no_fill) return_val = true;
        break;
        case LED_STATE_SPARKLE_FILL:
            if (strip_animation_mask.sparkle_fill) return_val = true;
        break;
        case LED_STATE_RAINBOW_CYCLE:
            if (strip_animation_mask.rainbow) return_val = true;
        break;
        case LED_STATE_THEATER_CHASE:
            if (strip_animation_mask.chase) return_val = true;
        break;
        case LED_STATE_THEATER_CHASE_RAINBOW:
            if (strip_animation_mask.chase_rainbow) return_val = true;
        break;
        case LED_STATE_FADE_IN_AND_OUT:
            if (strip_animation_mask.fade) return_val = true;
        break;
        case LED_STATE_TWINKLE:
            if (strip_animation_mask.twinkle) return_val = true;
        break;
        case LED_STATE_SRW_DEBUG:
            if (strip_animation_mask.solid_white) return_val = true;
        break;
        default:
        break;
    }
    return return_val;
}


// function to return the brightness enabled on a particular strip!
led_brightness_e flash_info_strip_brightness(strip_num_e strip_num)
{
    //led_brightness_e strip_brightness = LED_BRIGHTNESS_INVALID;
    flash_info_brightness_select_t strip_brightness_mask;
    switch (strip_num)
    {
#if defined(STRIP_1_LENGTH)
        case STRIP_NUM_1:
            strip_brightness_mask = g_flash_info_block.flash_info_data.strip_info.strip_1_brightness;
        break;
#endif
#if defined(STRIP_2_LENGTH)
        case STRIP_NUM_2:
            strip_brightness_mask = g_flash_info_block.flash_info_data.strip_info.strip_2_brightness;
        break;
#endif
#if defined(STRIP_3_LENGTH)
        case STRIP_NUM_3:
            strip_brightness_mask = g_flash_info_block.flash_info_data.strip_info.strip_3_brightness;
        break;
#endif
        // future strip num support goes here!
        default:
            while(1); // HW limited to 3 strips
        break;
    }
//    if (strip_brightness_mask.brightness_100p) strip_brightness = LED_BRIGHTNESS_100_PERCENT;
//    else if (strip_brightness_mask.brightness_75p) strip_brightness = LED_BRIGHTNESS_75_PERCENT;
//    else if (strip_brightness_mask.brightness_50p) strip_brightness = LED_BRIGHTNESS_50_PERCENT;
//    else if (strip_brightness_mask.brightness_25p) strip_brightness = LED_BRIGHTNESS_25_PERCENT;
//    else if (strip_brightness_mask.brightness_1p) strip_brightness = LED_BRIGHTNESS_1_PERCENT;
//    else
//    {
//        strip_brightness = LED_BRIGHTNESS_INVALID;
//        while(1); // hang for debug..  Shouldn't be encountering an invalid brightness
//    }
    //return strip_brightness;
}


// function to return the speed enabled on a particular strip!
led_speed_e flash_info_strip_speed(strip_num_e strip_num)
{
    //led_speed_e strip_speed = LED_SPEED_INVALID;
    flash_info_speed_select_t strip_speed_mask;
    switch (strip_num)
    {
#if defined(STRIP_1_LENGTH)
        case STRIP_NUM_1:
            strip_speed_mask = g_flash_info_block.flash_info_data.strip_info.strip_1_speed;
        break;
#endif
#if defined(STRIP_2_LENGTH)
        case STRIP_NUM_2:
            strip_speed_mask = g_flash_info_block.flash_info_data.strip_info.strip_2_speed;
        break;
#endif
#if defined(STRIP_3_LENGTH)
        case STRIP_NUM_3:
            strip_speed_mask = g_flash_info_block.flash_info_data.strip_info.strip_3_speed;
        break;
#endif
        // future strip num support goes here!
        default:
            while(1); // HW limited to 3 strips
        break;
    }
//    if (strip_speed_mask.speed_1000p) strip_speed = LED_SPEED_10X;
//    else if (strip_speed_mask.speed_500p) strip_speed = LED_SPEED_5X;
//    else if (strip_speed_mask.speed_100p) strip_speed = LED_SPEED_1X;
//    else if (strip_speed_mask.speed_50p) strip_speed = LED_SPEED_0P5X;
//    else if (strip_speed_mask.speed_25p) strip_speed = LED_SPEED_0P25X;
//    else while(1); // hang for debug..  Shouldn't be encountering an invalid speed
//    return strip_speed;
}


void flash_info_block_init(void)
{
    g_flash_info_block.flash_info_data.uuid0 = HAL_GetUIDw0();
    g_flash_info_block.flash_info_data.uuid1 = HAL_GetUIDw1();
    g_flash_info_block.flash_info_data.uuid2 = HAL_GetUIDw2();

    // strip_config setup.  Strip 1 enabled with length of 10.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_config, 0xA5, sizeof(flash_info_strip_config_t));
    //g_flash_info_block.flash_info_data.strip_info.strip_config.num_strips = 1;
    //g_flash_info_block.flash_info_data.strip_info.strip_config.strip_1_length = 10; // want to notice on sign if default is set

    // strip 1 animation setup.  ALl animations enabled by default.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_1_animation, UINT8_MAX, sizeof(flash_info_animation_select_t));
    g_flash_info_block.flash_info_data.strip_info.strip_1_animation.rsvd0 = 0;

    // strip 1 brightness setup.  100 percent brightness enabled by default.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_1_brightness, 0, sizeof(flash_info_brightness_select_t));
    g_flash_info_block.flash_info_data.strip_info.strip_1_brightness.brightness_100p = 1;

    // strip 1 color setup.  All colors enabled by default.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_1_color, UINT8_MAX, sizeof(flash_info_color_select_t));
    g_flash_info_block.flash_info_data.strip_info.strip_1_color.rsvd = 0;

    // strip 1 speed setup.  100 percent speed enabled by default.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_1_brightness, 0, sizeof(flash_info_speed_select_t));
    g_flash_info_block.flash_info_data.strip_info.strip_1_speed.speed_100p = 1;

    // strip 2 animation setup.  ALl animations DISABLED by default.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_2_animation, 0, sizeof(flash_info_animation_select_t));

    // strip 2 brightness setup.  No brightness enabled.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_2_brightness, 0, sizeof(flash_info_brightness_select_t));

    // strip 2 color setup.  All colors DISABLED by default.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_2_color, 0, sizeof(flash_info_color_select_t));

    // strip 2 speed setup.  No speed enabled.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_2_brightness, 0, sizeof(flash_info_speed_select_t));

    // strip 3 animation setup.  ALl animations DISABLED by default.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_3_animation, 0, sizeof(flash_info_animation_select_t));

    // strip 3 brightness setup.  No brightness enabled.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_3_brightness, 0, sizeof(flash_info_brightness_select_t));

    // strip 3 color setup.  All colors DISABLED by default.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_3_color, 0, sizeof(flash_info_color_select_t));

    // strip 3 speed setup.  No speed enabled.
    memset(&g_flash_info_block.flash_info_data.strip_info.strip_3_brightness, 0, sizeof(flash_info_speed_select_t));

    g_flash_info_block.flash_info_data.strip_info.rand_seed = 0;

    flash_access_write_sector(g_flash_info_block.flat_data_uint64, FLASH_INFO_SUB_BLOCK_CONFIG);
}


void flash_info_read_data(void *p_data, uint16_t address, uint16_t num_bytes)
{
    uint64_t flash_address = FLASH_START_ADDRESS + FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET + address;
    flash_access_read_flash(p_data, (void *)flash_address, num_bytes);
//    switch (address)
//    {
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_config):
//            flash_access_read_flash(p_data, )
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_1_color):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_2_color):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_3_color):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_1_animation):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_2_animation):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_3_animation):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_1_brightness):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_2_brightness):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_3_brightness):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_1_speed):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_2_speed):
//        break;
//        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_3_speed):
//        break;
//        default:
//            while(1); // error.  Hang for breakpoint
//        break;
//    }
}


uint8_t g_flash_read_buffer[100] = {0};
void flash_info_write_data(void *p_data, uint16_t address, uint16_t num_bytes)
{
    bool write_to_flash = false;
    uint64_t flash_address = FLASH_START_ADDRESS + FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET + address;
    switch (address)
    {
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_config):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_config, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_1_color):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_1_color, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_2_color):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_2_color, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_3_color):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_3_color, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_1_animation):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_1_animation, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_2_animation):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_2_animation, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_3_animation):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_3_animation, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_1_brightness):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_1_brightness, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_2_brightness):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_2_brightness, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_3_brightness):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_3_brightness, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_1_speed):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_1_speed, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_2_speed):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_2_speed, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.strip_3_speed):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.strip_3_speed, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_data.strip_info.rand_seed):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_data.strip_info.rand_seed, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        default:
            while(1); // error.  Hang for breakpoint
        break;
    }
    if (write_to_flash)
    {
        flash_access_write_to_flash((void *)p_data, (void *)flash_address, num_bytes);
    }
}


static void flash_info_rand_seed_increment(void)
{
    g_flash_info_block.flash_info_data.strip_info.rand_seed += 1;
    flash_access_write_sector(g_flash_info_block.flat_data_uint64, FLASH_INFO_SUB_BLOCK_CONFIG);
}


void flash_info_init(void)
{
    uint32_t rand_color = 0;
    uint32_t rand_animation = 0;
    uint32_t uid_0 = HAL_GetUIDw0();
    uint32_t uid_1 = HAL_GetUIDw1();
    uint32_t uid_2 = HAL_GetUIDw2();
    flash_access_read_sector(&g_flash_info_block.flat_data_uint8, FLASH_INFO_SUB_BLOCK_CONFIG);
    // check if UUID is set in flash block.  If not then init RAM struct and store to FLASH.
    if ((uid_0 != g_flash_info_block.flash_info_data.uuid0) && \
                    (uid_1 != g_flash_info_block.flash_info_data.uuid1) && \
                    (uid_2 != g_flash_info_block.flash_info_data.uuid2))
    {
        flash_info_block_init();
    }
    flash_info_rand_seed_increment();
    srand(g_flash_info_block.flash_info_data.strip_info.rand_seed);
    rand_color = (uint32_t)((double)rand() / ((double)RAND_MAX + 1) * (NUM_COLORS - 1));
    g_flash_info_block.flash_info_data.strip_info.strip_current_color = (all_colors_e)rand_color;
    //if (COLORS_BLACK == g_flash_info_block.flash_info_data.strip_info.strip_current_color) g_flash_info_block.flash_info_data.strip_info.strip_current_color = COLORS_LIME;
    rand_animation = (uint32_t)((double)rand() / ((double)RAND_MAX + 1) * (NUM_LED_STATES - 1));
    g_flash_info_block.flash_info_data.strip_info.strip_current_animation = rand_animation;
}


void flash_info_write_led_color_current(all_colors_e color)
{
    g_flash_info_block.flash_info_data.strip_info.strip_current_color = color;
}


all_colors_e flash_info_read_led_color_current(void)
{
    return g_flash_info_block.flash_info_data.strip_info.strip_current_color;
}


void flash_info_write_led_animation_current(led_state_e state)
{
    g_flash_info_block.flash_info_data.strip_info.strip_current_animation = state;
}


led_state_e flash_info_read_led_animation_current(void)
{
    return g_flash_info_block.flash_info_data.strip_info.strip_current_animation;
}


void flash_info_firmware_version(void)
{
    version_date_and_time_t version_date_time = \
    {
        .year = BUILD_DATE_YEAR,
        .month = BUILD_DATE_MONTH,
        .day = BUILD_DATE_DAY,
        .hour = BUILD_TIME_HOUR,
        .minutes = BUILD_TIME_MINUTE,
        .seconds = BUILD_TIME_SECOND,
        .fill = 0xFF
    };
//    if (0 != memcmp((void *)&version_date_time,
//                    (void *)(&g_flash_info_block.flash_info_data.image_info.active_image_fw_version),
//                    sizeof(version_date_and_time_t)))
//    {
//        memcpy((void *)(&g_flash_info_block.flash_info_data.image_info.active_image_fw_version),
//                        (void *)&version_date_time,
//                        sizeof(version_date_and_time_t));
//        // NEED TO WRITE THIS TO FLASH
//    }

}

