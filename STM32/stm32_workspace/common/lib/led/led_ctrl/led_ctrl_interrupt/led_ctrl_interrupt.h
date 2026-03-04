// SRW
#if !defined(LED_CTRL_INTERRUPT_H)
#define LED_CTRL_INTERRUPT_H


#pragma pack(1)
typedef struct
{
    union
    {
        struct
        {
            uint8_t state               : 1;
            uint8_t color               : 1;
            uint8_t speed               : 1;
            uint8_t pause_brightness    : 1;
            uint8_t rsvd                : 4;
        } bits;
        uint8_t flat_interrupt_status;
    };
} led_ctrl_interrupt_status_t;


typedef struct
{
    union
    {
        led_ctrl_interrupt_status_t     interrupt_status;
        uint8_t                         interrupt_status_flat;
    } minor;
    bool minor_interrupt_flag;
    union
    {
        led_ctrl_interrupt_status_t     interrupt_status;
        uint8_t                         interrupt_status_flat;
    } major;
    bool major_interrupt_flag;
    bool major_interrupt_transition_cmplt_flag;
} led_ctrl_interrupt_info_t;
#pragma pack()

typedef led_ctrl_interrupt_status_t* p_led_ctrl_interrupt_status_t;


led_ctrl_interrupt_info_t* led_ctrl_interrupt_read_interrupt_info(const strip_mask_t mask);
led_ctrl_interrupt_status_t led_ctrl_interrupt_read_minor_interrupt_status(const strip_mask_t mask);
bool led_ctrl_interrupt_read_minor_interrupt_flag(const strip_mask_t mask);
led_ctrl_interrupt_status_t led_ctrl_interrupt_read_major_interrupt_status(const strip_mask_t mask);
bool led_ctrl_interrupt_read_major_interrupt_flag(const strip_mask_t mask);

#endif
