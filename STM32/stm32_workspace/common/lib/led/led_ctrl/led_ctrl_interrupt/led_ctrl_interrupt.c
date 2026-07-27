// SRW

#include "led_ctrl_interrupt.h"
#include "led_ctrl.h"


led_ctrl_interrupt_info_t* led_ctrl_interrupt_read_interrupt_info(const strip_mask_t mask)
{
    return led_ctrl_read_interrupt_info(mask);
}


led_ctrl_interrupt_status_t led_ctrl_interrupt_read_minor_interrupt_status(const strip_mask_t mask)
{
    return led_ctrl_read_minor_interrupt_status(mask);
}


bool led_ctrl_interrupt_read_minor_interrupt_flag(const strip_mask_t mask)
{
    return led_ctrl_read_minor_interrupt_flag(mask);
}


led_ctrl_interrupt_status_t led_ctrl_interrupt_read_major_interrupt_status(const strip_mask_t mask)
{
    return led_ctrl_read_major_interrupt_status(mask);
}


bool led_ctrl_interrupt_read_major_interrupt_flag(const strip_mask_t mask)
{
    return led_ctrl_read_major_interrupt_flag(mask);
}


bool* led_ctrl_interrupt_read_major_interrupt_flag_ref(const strip_mask_t mask)
{
    return led_ctrl_read_major_interrupt_flag_ref(mask);
}


bool led_ctrl_interrupt_major_or_minor_flag_set(const strip_mask_t mask)
{
	return (led_ctrl_interrupt_read_minor_interrupt_flag(mask) || \
			led_ctrl_interrupt_read_major_interrupt_flag(mask));
}


bool led_ctrl_interrupt_minor_state_flag_is_set(const strip_mask_t mask)
{
    return led_ctrl_minor_interrupt_state_flag_is_set(mask);
}


bool* led_ctrl_interrupt_minor_state_flag_ref(const strip_mask_t mask)
{
    return led_ctrl_minor_interrupt_state_flag_ref(mask);
}


bool led_ctrl_interrupt_minor_color_flag_is_set(const strip_mask_t mask)
{
    return led_ctrl_minor_interrupt_color_flag_is_set(mask);
}


bool* led_ctrl_interrupt_minor_color_flag_ref(const strip_mask_t mask)
{
    return led_ctrl_minor_interrupt_color_flag_ref(mask);
}


bool led_ctrl_interrupt_minor_speed_flag_is_set(const strip_mask_t mask)
{
    return led_ctrl_minor_interrupt_speed_flag_is_set(mask);
}


bool* led_ctrl_interrupt_minor_speed_flag_ref(const strip_mask_t mask)
{
    return led_ctrl_minor_interrupt_speed_flag_ref(mask);
}


bool led_ctrl_interrupt_minor_pause_flag_is_set(const strip_mask_t mask)
{
    return led_ctrl_minor_interrupt_pause_flag_is_set(mask);
}


bool* led_ctrl_interrupt_minor_pause_flag_ref(const strip_mask_t mask)
{
    return led_ctrl_minor_interrupt_pause_flag_ref(mask);
}





