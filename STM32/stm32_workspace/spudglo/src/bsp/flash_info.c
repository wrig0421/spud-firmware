#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include "stm32l4xx_hal.h"
#include "version.h"
#include "led_animate.h"
#include "flash_info.h"
#include "flash_access.h"
#include "led_ctrl_speed.h"
#include "led_ctrl_brightness.h"
#include "pkt.h"
#include "free_rtos_convenience.h"


flash_info_block_t  g_flash_info_block;

p_flash_info_block_t flash_info_block_handle(void)
{
	return &g_flash_info_block;
}


bool flash_info_color_enabled_on_strip(strip_bit_e strip_bit, led_color_e color)
{
    bool return_val = false;
    flash_info_color_select_t strip_color_mask;
    switch (strip_bit)
    {
#if defined(STRIP_1_LENGTH)
        case STRIP_BIT_1:
            strip_color_mask = g_flash_info_block.flash_info_config.strip_info.strip_1_color;
        break;
#endif
#if defined(STRIP_2_LENGTH)
        case STRIP_BIT_2:
            strip_color_mask = g_flash_info_block.flash_info_config.strip_info.strip_2_color;
        break;
#endif
#if defined(STRIP_3_LENGTH)
        case STRIP_BIT_3:
            strip_color_mask = g_flash_info_block.flash_info_config.strip_info.strip_3_color;
        break;
#endif
        default:
            while(1); // HW limited to 3 strips
        break;
    }
    switch (color)
    {
        case LED_COLOR_RED:
            if (strip_color_mask.red) return_val = true;
        break;
        case LED_COLOR_DARK_RED:
            if (strip_color_mask.dark_red) return_val = true;
        break;
        case LED_COLOR_MAROON:
            if (strip_color_mask.maroon) return_val = true;
        break;
        case LED_COLOR_SALMON:
            if (strip_color_mask.salmon) return_val = true;
        break;
        case LED_COLOR_ORANGE_RED:
            if (strip_color_mask.orange_red) return_val = true;
        break;
        case LED_COLOR_ORANGE:
            if (strip_color_mask.orange) return_val = true;
        break;
        case LED_COLOR_GOLD:
            if (strip_color_mask.gold) return_val = true;
        break;
        case LED_COLOR_YELLOW:
            if (strip_color_mask.yellow) return_val = true;
        break;
        case LED_COLOR_GREEN:
            if (strip_color_mask.green) return_val = true;
        break;
        case LED_COLOR_SPRING_GREEN:
            if (strip_color_mask.spring_green) return_val = true;
        break;
        case LED_COLOR_FOREST_GREEN:
            if (strip_color_mask.forest_green) return_val = true;
        break;
        case LED_COLOR_TEAL:
            if (strip_color_mask.teal) return_val = true;
        break;
        case LED_COLOR_CYAN:
            if (strip_color_mask.cyan) return_val = true;
        break;
        case LED_COLOR_AQUA_MARINE:
            if (strip_color_mask.aqua_marine) return_val = true;
        break;
        case LED_COLOR_BLUE:
            if (strip_color_mask.blue) return_val = true;
        break;
        case LED_COLOR_NAVY:
            if (strip_color_mask.navy) return_val = true;
        break;
        case LED_COLOR_DARK_BLUE:
            if (strip_color_mask.dark_blue) return_val = true;
        break;
        case LED_COLOR_PURPLE:
            if (strip_color_mask.purple) return_val = true;
        break;
        case LED_COLOR_VIOLET:
            if (strip_color_mask.violet) return_val = true;
        break;
        case LED_COLOR_INDIGO:
            if (strip_color_mask.indigo) return_val = true;
        break;
        case LED_COLOR_PLUM:
            if (strip_color_mask.plum) return_val = true;
        break;
        case LED_COLOR_PINK:
            if (strip_color_mask.pink) return_val = true;
        break;
        case LED_COLOR_HOT_PINK:
            if (strip_color_mask.hot_pink) return_val = true;
        break;
        case LED_COLOR_DEEP_PINK:
            if (strip_color_mask.deep_pink) return_val = true;
        break;
        case LED_COLOR_BROWN:
            if (strip_color_mask.brown) return_val = true;
        break;
        case LED_COLOR_CHOCOLATE:
            if (strip_color_mask.chocolate) return_val = true;
        break;
        case LED_COLOR_WHITE:
            if (strip_color_mask.white) return_val = true;
        break;
        case LED_COLOR_GRAY:
            if (strip_color_mask.gray) return_val = true;
        break;
        case LED_COLOR_SILVER:
            if (strip_color_mask.silver) return_val = true;
        break;
        case LED_COLOR_BLACK:
            if (strip_color_mask.black) return_val = true;
        break;
        default:
            while(1);
        break;
    }
    return return_val;
}


// function to return the brightness enabled on a particular strip!
led_brightness_e flash_info_brightness_enabled_on_strip(strip_bit_e strip_bit)
{
    //led_brightness_e strip_brightness = LED_BRIGHTNESS_INVALID;
	led_brightness_e led_brightness = LED_BRIGHTNESS_100_PERCENT;
    flash_info_brightness_select_t strip_brightness_mask;
    bool brightness_setting_valid = false;

    switch (strip_bit)
    {
#		if defined(STRIP_1_LENGTH)
			case STRIP_BIT_1:
				strip_brightness_mask = g_flash_info_block.flash_info_config.strip_info.strip_1_brightness;
			break;
#		endif
#		if defined(STRIP_2_LENGTH)
			case STRIP_BIT_2:
				strip_brightness_mask = g_flash_info_block.flash_info_config.strip_info.strip_2_brightness;
			break;
#		endif
#		if defined(STRIP_3_LENGTH)
			case STRIP_BIT_3:
				strip_brightness_mask = g_flash_info_block.flash_info_config.strip_info.strip_3_brightness;
			break;
#		endif
        // future strip num support goes here!
        default:
        	UNUSED(strip_brightness_mask);
            while(1);
        break;
    }

    switch (strip_brightness_mask.flat_brightness)
    {
    	case 1 << 0:
    	case 1 << 1:
    	case 1 << 2:
    	case 1 << 3:
    	case 1 << 4:
    	case 1 << 5:
			brightness_setting_valid = true;
    	break;
    	default:
			brightness_setting_valid = false;
    		while (1); // should never have more than one set!
    	break;
    }

    if (brightness_setting_valid)
    {
    	if (strip_brightness_mask.brightness_100p)
		{
			led_brightness = LED_BRIGHTNESS_100_PERCENT;
		}
//		else if (strip_brightness_mask.brightness_75p)
//		{
//			led_brightness = LED_BRIGHTNESS_75_PERCENT;
//		}
		else if (strip_brightness_mask.brightness_50p)
		{
			led_brightness = LED_BRIGHTNESS_50_PERCENT;
		}
		else if (strip_brightness_mask.brightness_25p)
		{
			led_brightness = LED_BRIGHTNESS_25_PERCENT;
		}
		else if (strip_brightness_mask.brightness_1p)
		{
			led_brightness = LED_BRIGHTNESS_10_PERCENT;
		}
		else
		{
			while (1);
		}
    }
    return led_brightness;
}


// function to return the speed enabled on a particular strip!
led_speed_e flash_info_speed_enabled_on_strip(strip_bit_e strip_bit)
{
    led_speed_e strip_speed = LED_SPEED_INVALID;
    flash_info_speed_select_t strip_speed_mask;
    switch (strip_bit)
    {
#if defined(STRIP_1_LENGTH)
        case STRIP_BIT_1:
            strip_speed_mask = g_flash_info_block.flash_info_config.strip_info.strip_1_speed;
        break;
#endif
#if defined(STRIP_2_LENGTH)
        case STRIP_BIT_2:
            strip_speed_mask = g_flash_info_block.flash_info_config.strip_info.strip_2_speed;
        break;
#endif
#if defined(STRIP_3_LENGTH)
        case STRIP_BIT_3:
            strip_speed_mask = g_flash_info_block.flash_info_config.strip_info.strip_3_speed;
        break;
#endif
        // future strip num support goes here!
        default:
            while(1); // HW limited to 3 strips
        break;
    }
    if (strip_speed_mask.speed_1000p)
    {
    	strip_speed = LED_SPEED_FAST; // LED_SPEED_1000P
    }
    else if (strip_speed_mask.speed_500p)
	{
    	strip_speed = LED_SPEED_500P; // LED_SPEED_1000P
	}
    else if (strip_speed_mask.speed_100p)
	{
    	strip_speed = LED_SPEED_100P; // LED_SPEED_1000P
	}
    else if (strip_speed_mask.speed_50p)
	{
    	strip_speed = LED_SPEED_50P; // LED_SPEED_1000P
	}
    else if (strip_speed_mask.speed_25p)
	{
    	strip_speed = LED_SPEED_25P; // LED_SPEED_1000P
	}
    return strip_speed;
}


void flash_info_block_init(void)
{
	// strip_config
    g_flash_info_block.flash_info_config.strip_info.strip_config.num_strips = 1;
    g_flash_info_block.flash_info_config.strip_info.strip_config.strip_enable.strip_1_enabled = true;
    g_flash_info_block.flash_info_config.strip_info.strip_config.strip_enable.strip_2_enabled = false;
    g_flash_info_block.flash_info_config.strip_info.strip_config.strip_enable.strip_3_enabled = false;
    g_flash_info_block.flash_info_config.strip_info.strip_config.rsvd1 = 0;
    g_flash_info_block.flash_info_config.strip_info.strip_config.rsvd2 = 0;
    g_flash_info_block.flash_info_config.strip_info.strip_config.strip_1_length = 10;
    g_flash_info_block.flash_info_config.strip_info.strip_config.strip_2_length = 10;
    g_flash_info_block.flash_info_config.strip_info.strip_config.strip_3_length = 10;

    // strip_color
    memset(&g_flash_info_block.flash_info_config.strip_info.strip_1_color, 0xFF, sizeof(flash_info_color_select_t));
    memset(&g_flash_info_block.flash_info_config.strip_info.strip_2_color, 0xFF, sizeof(flash_info_color_select_t));
    memset(&g_flash_info_block.flash_info_config.strip_info.strip_3_color, 0xFF, sizeof(flash_info_color_select_t));

    // strip animation
	g_flash_info_block.flash_info_config.strip_info.strip_1_animation.flat_animation_1 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_1_animation.flat_animation_2 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_1_animation.flat_animation_3 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_1_animation.flat_animation_4 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_1_animation.flat_animation_5 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_1_animation.flat_animation_6 = 0;

	g_flash_info_block.flash_info_config.strip_info.strip_2_animation.flat_animation_1 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_2_animation.flat_animation_2 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_2_animation.flat_animation_3 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_2_animation.flat_animation_4 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_2_animation.flat_animation_5 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_2_animation.flat_animation_6 = 0;

	g_flash_info_block.flash_info_config.strip_info.strip_3_animation.flat_animation_1 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_3_animation.flat_animation_2 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_3_animation.flat_animation_3 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_3_animation.flat_animation_4 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_3_animation.flat_animation_5 = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_3_animation.flat_animation_6 = 0;

	// strip brightness
	g_flash_info_block.flash_info_config.strip_info.strip_1_brightness.flat_brightness = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_2_brightness.flat_brightness = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_3_brightness.flat_brightness = 0;

	// strip speed
	g_flash_info_block.flash_info_config.strip_info.strip_1_speed.flat_speed = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_2_speed.flat_speed = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_3_speed.flat_speed = 0;
	g_flash_info_block.flash_info_config.strip_info.strip_1_speed.speed_100p = 1;
	g_flash_info_block.flash_info_config.strip_info.strip_2_speed.speed_100p = 1;
	g_flash_info_block.flash_info_config.strip_info.strip_3_speed.speed_100p = 1;

	// rand seed
	g_flash_info_block.flash_info_config.strip_info.rand_seed = rand();

	// uid
	g_flash_info_block.flash_info_config.device_info.uid.uid0 = HAL_GetUIDw0();
	g_flash_info_block.flash_info_config.device_info.uid.uid1 = HAL_GetUIDw1();
	g_flash_info_block.flash_info_config.device_info.uid.uid2 = HAL_GetUIDw2();

	g_flash_info_block.flash_info_config.device_info.hw_rev = FLASH_INFO_HW_REV_SPUDGLO_BABY_DINOSAUR_V1P0;
	g_flash_info_block.flash_info_config.device_info.pcb_serial_number = 1;
}


void flash_info_read_data(void *p_data, uint16_t address, uint16_t num_bytes)
{
    uint32_t flash_address = FLASH_START_ADDRESS + FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET + address;
    flash_access_read_flash((void *)p_data, (void *)flash_address, num_bytes);

//    switch (address)
//    {
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_config):
//            flash_access_read_flash(p_data, )
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_1_color):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_2_color):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_3_color):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_1_animation):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_2_animation):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_3_animation):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_1_brightness):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_2_brightness):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_3_brightness):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_1_speed):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_2_speed):
//        break;
//        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_3_speed):
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
    uint32_t flash_address = FLASH_START_ADDRESS + FLASH_SUB_BLOCK_CONFIG_ADDRESS_OFFSET + address;
    switch (address)
    {
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_config):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_config, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_1_color):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_1_color, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_2_color):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_2_color, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_3_color):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_3_color, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_1_animation):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_1_animation, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_2_animation):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_2_animation, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_3_animation):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_3_animation, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_1_brightness):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_1_brightness, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_2_brightness):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_2_brightness, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_3_brightness):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_3_brightness, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_1_speed):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_1_speed, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_2_speed):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_2_speed, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.strip_3_speed):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.strip_3_speed, \
                            num_bytes))
            {
                write_to_flash = true;
            }
        break;
        case offsetof(flash_info_block_t, flash_info_config.strip_info.rand_seed):
            if (!memcmp((uint8_t *)p_data, (uint8_t *) &g_flash_info_block.flash_info_config.strip_info.rand_seed, \
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
        flash_access_write_to_flash((void *)p_data, flash_address, num_bytes);
    }
}


static void flash_info_rand_re_seed(void)
{
    g_flash_info_block.flash_info_config.strip_info.rand_seed = rand();
    // update flash value in separate part of code.
}


void flash_info_init(void)
{
    uint32_t uid_0 = HAL_GetUIDw0();
    uint32_t uid_1 = HAL_GetUIDw1();
    uint32_t uid_2 = HAL_GetUIDw2();

    flash_access_read_sector(&g_flash_info_block.flat_data_uint8, FLASH_INFO_SUB_BLOCK_CONFIG);

    // check if UUID is set in flash block.  If not then init RAM struct and store to FLASH.
    if ((uid_0 != g_flash_info_block.flash_info_config.device_info.uid.uid0) && \
    	(uid_1 != g_flash_info_block.flash_info_config.device_info.uid.uid1) && \
        (uid_2 != g_flash_info_block.flash_info_config.device_info.uid.uid2))
    {
        flash_info_block_init();
    }

    // store rand_seed sourced from the incremented flash value
    srand(g_flash_info_block.flash_info_config.strip_info.rand_seed);

    flash_info_rand_re_seed();
    flash_access_write_sector(g_flash_info_block.flat_data_uint64, FLASH_INFO_SUB_BLOCK_CONFIG);
}


void flash_info_led_color_is_enabled(const strip_mask_t strip_mask, led_color_e color, bool *ret_val)
{
	flash_info_color_select_t *p_strip_n_color_generic = NULL;
	flash_info_color_select_t *p_strip_1_color_select = NULL;
	flash_info_color_select_t *p_strip_2_color_select = NULL;
	flash_info_color_select_t *p_strip_3_color_select = NULL;

	if (flash_info_strip_1_is_enabled() && (STRIP_BIT_1 & strip_mask))
	{
		if (STRIP_BIT_1 & strip_mask)
		{
			p_strip_1_color_select = &g_flash_info_block.flash_info_config.strip_info.strip_1_color;
		}
	}
	if (flash_info_strip_2_is_enabled() && (STRIP_BIT_2 & strip_mask))
	{
		if (STRIP_BIT_2 & strip_mask)
		{
			p_strip_2_color_select = &g_flash_info_block.flash_info_config.strip_info.strip_2_color;
		}
	}
	if (flash_info_strip_3_is_enabled() && (STRIP_BIT_3 & strip_mask))
	{
		if (STRIP_BIT_3 & strip_mask)
		{
			p_strip_3_color_select = &g_flash_info_block.flash_info_config.strip_info.strip_3_color;
		}
	}
	for (uint8_t iii = 0; iii < NUM_ACTIVE_STRIPS; iii++)
	{
		if (!(strip_mask & (1 << iii)))
		{
			ret_val[iii] = false;
			continue;
		}
		switch (iii)
		{
			case STRIP_NUM_1: p_strip_n_color_generic = p_strip_1_color_select; break;
			case STRIP_NUM_2: p_strip_n_color_generic = p_strip_2_color_select; break;
			case STRIP_NUM_3: p_strip_n_color_generic = p_strip_3_color_select; break;
			default: while (1); break;
		}

		switch (color)
		{
			case LED_COLOR_WHITE: 			ret_val[iii] = p_strip_n_color_generic->white; 			break;
			case LED_COLOR_RED: 			ret_val[iii] = p_strip_n_color_generic->red; 				break;
			case LED_COLOR_DARK_RED: 		ret_val[iii] = p_strip_n_color_generic->dark_red; 		break;
			case LED_COLOR_MAROON: 			ret_val[iii] = p_strip_n_color_generic->maroon; 			break;
			case LED_COLOR_SALMON: 			ret_val[iii] = p_strip_n_color_generic->salmon; 			break;
			case LED_COLOR_ORANGE_RED: 		ret_val[iii] = p_strip_n_color_generic->orange_red; 		break;
			case LED_COLOR_ORANGE: 			ret_val[iii] = p_strip_n_color_generic->orange; 			break;
			case LED_COLOR_GOLD: 			ret_val[iii] = p_strip_n_color_generic->gold; 			break;

			case LED_COLOR_GREEN: 			ret_val[iii] = p_strip_n_color_generic->green; 			break;
			case LED_COLOR_MINT: 			ret_val[iii] = p_strip_n_color_generic->mint; 			break;
			case LED_COLOR_FOREST_GREEN: 	ret_val[iii] = p_strip_n_color_generic->forest_green; 	break;
			case LED_COLOR_TEAL: 			ret_val[iii] = p_strip_n_color_generic->teal; 			break;
			case LED_COLOR_CYAN: 			ret_val[iii] = p_strip_n_color_generic->cyan;		 		break;
			case LED_COLOR_AQUA_MARINE: 	ret_val[iii] = p_strip_n_color_generic->aqua_marine; 		break;
			case LED_COLOR_BLUE: 			ret_val[iii] = p_strip_n_color_generic->blue; 			break;
			case LED_COLOR_NAVY: 			ret_val[iii] = p_strip_n_color_generic->navy; 			break;

			case LED_COLOR_DARK_BLUE: 		ret_val[iii] = p_strip_n_color_generic->dark_blue; 		break;
			case LED_COLOR_PURPLE: 			ret_val[iii] = p_strip_n_color_generic->purple; 			break;
			case LED_COLOR_VIOLET: 			ret_val[iii] = p_strip_n_color_generic->violet; 			break;
			case LED_COLOR_INDIGO: 			ret_val[iii] = p_strip_n_color_generic->indigo; 			break;
			case LED_COLOR_PLUM: 			ret_val[iii] = p_strip_n_color_generic->plum; 			break;
			case LED_COLOR_PINK: 			ret_val[iii] = p_strip_n_color_generic->pink; 			break;
			case LED_COLOR_HOT_PINK: 		ret_val[iii] = p_strip_n_color_generic->hot_pink; 		break;
			case LED_COLOR_DEEP_PINK: 		ret_val[iii] = p_strip_n_color_generic->deep_pink; 		break;

			case LED_COLOR_BROWN: 			ret_val[iii] = p_strip_n_color_generic->brown; 			break;
			case LED_COLOR_CHOCOLATE: 		ret_val[iii] = p_strip_n_color_generic->chocolate; 		break;
			case LED_COLOR_YELLOW: 			ret_val[iii] = p_strip_n_color_generic->yellow; 			break;
			case LED_COLOR_GRAY: 			ret_val[iii] = p_strip_n_color_generic->gray; 			break;
			case LED_COLOR_SILVER: 			ret_val[iii] = p_strip_n_color_generic->silver;		 	break;
			case LED_COLOR_BLACK: 			ret_val[iii] = p_strip_n_color_generic->black; 			break;
			case LED_COLOR_LIME: 			ret_val[iii] = p_strip_n_color_generic->lime; 			break;
			case LED_COLOR_MAGENTA: 		ret_val[iii] = p_strip_n_color_generic->magenta; 			break;

			case LED_COLOR_OLIVE: 			ret_val[iii] = p_strip_n_color_generic->olive; 			break;
			case LED_COLOR_KHAKI: 			ret_val[iii] = p_strip_n_color_generic->khaki; 			break;
			case LED_COLOR_LAWN_GREEN: 		ret_val[iii] = p_strip_n_color_generic->lawn_green; 		break;
			case LED_COLOR_SPRING_GREEN: 	ret_val[iii] = p_strip_n_color_generic->spring_green; 	break;
			case LED_COLOR_MIDNIGHT_BLUE: 	ret_val[iii] = p_strip_n_color_generic->midnight_blue; 	break;
			case LED_COLOR_BLUE_VIOLET: 	ret_val[iii] = p_strip_n_color_generic->blue_violet; 		break;
			case LED_COLOR_DARK_MAGENTA: 	ret_val[iii] = p_strip_n_color_generic->dark_magenta; 	break;
			case LED_COLOR_TAN: 			ret_val[iii] = p_strip_n_color_generic->tan; 				break;

			default: while (1); break;
		}
	}
}



void flash_info_led_state_is_enabled(const strip_mask_t strip_mask, led_state_e state, bool *ret_val)
{
	flash_info_animation_select_t *p_strip_n_state_generic = NULL;
	flash_info_animation_select_t *p_strip_1_state = NULL;
	flash_info_animation_select_t *p_strip_2_state = NULL;
	flash_info_animation_select_t *p_strip_3_state = NULL;

	if (flash_info_strip_1_is_enabled() && (STRIP_BIT_1 & strip_mask))
	{
		p_strip_1_state = &g_flash_info_block.flash_info_config.strip_info.strip_1_animation;
	}
	if (flash_info_strip_2_is_enabled() && (STRIP_BIT_2 & strip_mask))
	{
		p_strip_2_state = &g_flash_info_block.flash_info_config.strip_info.strip_2_animation;
	}
	if (flash_info_strip_3_is_enabled() && (STRIP_BIT_3 & strip_mask))
	{
		p_strip_3_state = &g_flash_info_block.flash_info_config.strip_info.strip_3_animation;
	}
	for (uint8_t iii = 0; iii < NUM_ACTIVE_STRIPS; iii++)
	{
		if (!(strip_mask & (1 << iii)))
		{
			ret_val[iii] = false;
			continue;
		}
		switch (iii)
		{
			case STRIP_NUM_1: p_strip_n_state_generic = p_strip_1_state; break;
			case STRIP_NUM_2: p_strip_n_state_generic = p_strip_2_state; break;
			case STRIP_NUM_3: p_strip_n_state_generic = p_strip_3_state; break;
			default: while(1); break;
		}
		switch (state)
		{
			case LED_STATE_SPELL: 						ret_val[iii] = p_strip_n_state_generic->spell; 					break;
			case LED_STATE_WHITE_COLOR: 				ret_val[iii] = p_strip_n_state_generic->solid_white; 			break;
			case LED_STATE_SOLID_COLOR: 				ret_val[iii] = p_strip_n_state_generic->solid_color; 			break;
			case LED_STATE_SPARKLE_NO_FILL: 			ret_val[iii] = p_strip_n_state_generic->sparkle_no_fill; 		break;
			case LED_STATE_SPARKLE_FILL: 				ret_val[iii] = p_strip_n_state_generic->sparkle_fill; 			break;
			case LED_STATE_RAINBOW_CYCLE: 				ret_val[iii] = p_strip_n_state_generic->rainbow; 				break;
			case LED_STATE_THEATER_CHASE: 				ret_val[iii] = p_strip_n_state_generic->chase; 					break;
			case LED_STATE_THEATER_CHASE_RAINBOW: 		ret_val[iii] = p_strip_n_state_generic->chase_rainbow; 			break;

			case LED_STATE_FADE_IN_AND_OUT: 			ret_val[iii] = p_strip_n_state_generic->fade; 					break;
//			case LED_STATE_TWINKLE: 					ret_val[iii] = p_strip_n_state_generic->twinkle; 				break;
//			case LED_STATE_RUNNING_LIGHTS: 				ret_val[iii] = p_strip_n_state_generic->running_lights; 		break;
//			case LED_STATE_FIRE: 						ret_val[iii] = p_strip_n_state_generic->fire; 					break;
//			case LED_STATE_METEOR: 						ret_val[iii] = p_strip_n_state_generic->meteor;		 			break;
//			case LED_STATE_STROBE: 						ret_val[iii] = p_strip_n_state_generic->strobe; 				break;
//			case LED_STATE_FADE_IN_AND_OUT_RANDOM: 		ret_val[iii] = p_strip_n_state_generic->fade; 					break;
			default: while (1); break;
		}
	}
}


void flash_info_brightness_level_is_enabled(const strip_mask_t strip_mask, led_brightness_e *led_brightness_enabled)
{
	// policy here.... the highest brightness is returned first!
	flash_info_brightness_select_t *p_strip_n_brightness_generic = NULL;
	flash_info_brightness_select_t *p_strip_1_brightness = NULL;
	flash_info_brightness_select_t *p_strip_2_brightness = NULL;
	flash_info_brightness_select_t *p_strip_3_brightness = NULL;

	if (flash_info_strip_1_is_enabled() && (STRIP_BIT_1 & strip_mask))
	{
		p_strip_1_brightness = &g_flash_info_block.flash_info_config.strip_info.strip_1_brightness;
	}
	if (flash_info_strip_2_is_enabled() && (STRIP_BIT_2 & strip_mask))
	{
		p_strip_2_brightness = &g_flash_info_block.flash_info_config.strip_info.strip_2_brightness;
	}
	if (flash_info_strip_3_is_enabled() && (STRIP_BIT_3 & strip_mask))
	{
		p_strip_3_brightness = &g_flash_info_block.flash_info_config.strip_info.strip_3_brightness;
	}
	for (uint8_t iii = 0; iii < NUM_ACTIVE_STRIPS; iii++)
	{
		if (!(strip_mask & (1 << iii)))
		{
			led_brightness_enabled[iii] = LED_BRIGHTNESS_INVALID;
			continue;
		}
		switch (iii)
		{
			case STRIP_NUM_1: p_strip_n_brightness_generic = p_strip_1_brightness; break;
			case STRIP_NUM_2: p_strip_n_brightness_generic = p_strip_2_brightness; break;
			case STRIP_NUM_3: p_strip_n_brightness_generic = p_strip_3_brightness; break;
			default:	while(1); break;
		}
		if (p_strip_n_brightness_generic->brightness_100p)
		{
			led_brightness_enabled[iii] = LED_BRIGHTNESS_100_PERCENT;
		}
//		else if (p_strip_n_brightness_generic->brightness_75p)
//		{
//			led_brightness_enabled[iii] = LED_BRIGHTNESS_75_PERCENT;
//		}
		else if (p_strip_n_brightness_generic->brightness_50p)
		{
			led_brightness_enabled[iii] = LED_BRIGHTNESS_50_PERCENT;
		}
		else if (p_strip_n_brightness_generic->brightness_25p)
		{
			led_brightness_enabled[iii] = LED_BRIGHTNESS_25_PERCENT;
		}
		else if (p_strip_n_brightness_generic->brightness_1p)
		{
			led_brightness_enabled[iii] = LED_BRIGHTNESS_10_PERCENT;
		}
		else if(p_strip_n_brightness_generic->rsvd0)
		{
			while (1);
		}
	}
}


void flash_info_speed_is_enabled(const strip_mask_t strip_mask, led_speed_e *led_speed)
{
	// policy here.... the highest brightness is returned first!
	flash_info_speed_select_t *p_strip_n_speed_generic = NULL;
	flash_info_speed_select_t *p_strip_1_speed = NULL;
	flash_info_speed_select_t *p_strip_2_speed = NULL;
	flash_info_speed_select_t *p_strip_3_speed = NULL;

	if (flash_info_strip_1_is_enabled() && (STRIP_BIT_1 & strip_mask))
	{
		p_strip_1_speed = &g_flash_info_block.flash_info_config.strip_info.strip_1_speed;
	}
	if (flash_info_strip_2_is_enabled() && (STRIP_BIT_2 & strip_mask))
	{
		p_strip_2_speed = &g_flash_info_block.flash_info_config.strip_info.strip_2_speed;
	}
	if (flash_info_strip_3_is_enabled() && (STRIP_BIT_3 & strip_mask))
	{
		p_strip_3_speed = &g_flash_info_block.flash_info_config.strip_info.strip_3_speed;
	}
	for (uint8_t iii = 0; iii < flash_info_num_strips(); iii++)
	{
		if (!(strip_mask & (1 << iii)))
		{
			led_speed[iii] = LED_SPEED_INVALID;
			continue;
		}
		switch (iii)
		{
			case STRIP_NUM_1: p_strip_n_speed_generic = p_strip_1_speed; break;
			case STRIP_NUM_2: p_strip_n_speed_generic = p_strip_2_speed; break;
			case STRIP_NUM_3: p_strip_n_speed_generic = p_strip_3_speed; break;
			default: while (1); break;
		}
		if (p_strip_n_speed_generic->speed_1000p)
		{
			led_speed[iii] = LED_SPEED_1000P;
		}
		else if (p_strip_n_speed_generic->speed_500p)
		{
			led_speed[iii] = LED_SPEED_500P;
		}
		else if (p_strip_n_speed_generic->speed_100p)
		{
			led_speed[iii] = LED_SPEED_100P;
		}
		else if (p_strip_n_speed_generic->speed_50p)
		{
			led_speed[iii] = LED_SPEED_50P;
		}
		else if (p_strip_n_speed_generic->speed_25p)
		{
			led_speed[iii] = LED_SPEED_25P;
		}
		else if(p_strip_n_speed_generic->rsvd0)
		{
			while (1);
		}
	}
}


uint8_t flash_info_num_strips(void)
{
	return g_flash_info_block.flash_info_config.strip_info.strip_config.num_strips;
}


uint8_t flash_info_num_enabled_strips(void)
{
	return (flash_info_strip_1_is_enabled() + flash_info_strip_2_is_enabled() + flash_info_strip_3_is_enabled());
}


bool flash_info_strip_1_is_enabled(void)
{
	return (bool)(g_flash_info_block.flash_info_config.strip_info.strip_config.strip_enable.strip_1_enabled);
}


bool flash_info_strip_2_is_enabled(void)
{
	return (bool)(g_flash_info_block.flash_info_config.strip_info.strip_config.strip_enable.strip_2_enabled);
}


bool flash_info_strip_3_is_enabled(void)
{
	return (bool)(g_flash_info_block.flash_info_config.strip_info.strip_config.strip_enable.strip_3_enabled);
}


void flash_info_strip_length(const strip_mask_t mask, uint8_t *strip_length)
{
	for (uint8_t iii = 0; iii < NUM_ACTIVE_STRIPS; iii++)
	{
		if (!(mask & (1 << iii)))
		{
			strip_length[iii] = 0;
			continue;
		}
		switch (iii)
		{
			case STRIP_NUM_1:
				strip_length[iii] = g_flash_info_block.flash_info_config.strip_info.strip_config.strip_1_length;
			break;

			case STRIP_NUM_2:
				strip_length[iii] = g_flash_info_block.flash_info_config.strip_info.strip_config.strip_2_length;
			break;

			case STRIP_NUM_3:
				strip_length[iii] = g_flash_info_block.flash_info_config.strip_info.strip_config.strip_3_length;
			break;
		}
	}
}


uint16_t flash_info_strip_1_length(void)
{
	uint16_t length = 0;
	if (flash_info_strip_1_is_enabled())
	{
		length = g_flash_info_block.flash_info_config.strip_info.strip_config.strip_1_length;
	}
	return length;
}


uint16_t flash_info_strip_2_length(void)
{
	uint16_t length = 0;
	if (flash_info_strip_2_is_enabled())
	{
		length = g_flash_info_block.flash_info_config.strip_info.strip_config.strip_2_length;
	}
	return length;
}


uint16_t flash_info_strip_3_length(void)
{
	uint16_t length = 0;
	if (flash_info_strip_3_is_enabled())
	{
		length = g_flash_info_block.flash_info_config.strip_info.strip_config.strip_3_length;
	}
	return length;
}


flash_info_hw_rev_e flash_info_read_hw_rev(void)
{
	return g_flash_info_block.flash_info_config.device_info.hw_rev;
}


uint16_t flash_info_read_serial_number(void)
{
	return g_flash_info_block.flash_info_config.device_info.pcb_serial_number;
}


void flash_info_read_uid(uint32_t* p_uid)
{
	p_uid[0] = g_flash_info_block.flash_info_config.device_info.uid.uid0;
	p_uid[1] = g_flash_info_block.flash_info_config.device_info.uid.uid1;
	p_uid[2] = g_flash_info_block.flash_info_config.device_info.uid.uid2;
}


void flash_info_firmware_version(void)
{
    version_date_and_time_t version_date_time =
    {
        .year = BUILD_DATE_YEAR,
        .month = BUILD_DATE_MONTH,
        .day = BUILD_DATE_DAY,
        .hour = BUILD_TIME_HOUR,
        .minutes = BUILD_TIME_MINUTE,
        .seconds = BUILD_TIME_SECOND,
        .fill = 0xFF
    };

    // TODO use version_date_time
    UNUSED(version_date_time);

}


