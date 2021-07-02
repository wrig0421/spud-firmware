/*
 * gt_521fx_driver.h
 *
 *  Created on: Aug 4, 2020
 *      Author: spud
 */

#ifndef INC_GT_521FX_DRIVER_H_
#define INC_GT_521FX_DRIVER_H_

#include <stdbool.h>


#define GT521FX_CAPTURE_FINGER_FAST		0
#define GT521FX_CAPTURE_FINGER_SLOW		1


typedef enum
{
    GT521FX_CMD_OPEN                  	= 0x01,
    GT521FX_CMD_CLOSE                   = 0x02,
    GT521FX_CMD_USB_INTERNAL_CHECK      = 0x03,
    GT521FX_CMD_CHANGE_BAUD_RATE        = 0x04,
    GT521FX_CMD_CMOS_LED                = 0x12,
    GT521FX_CMD_GET_ENROLL_COUNT        = 0x20,
    GT521FX_CMD_CHECK_ENROLLED         	= 0x21,
    GT521FX_CMD_ENROLL_START            = 0x22,
    GT521FX_CMD_ENROLL_1              	= 0x23,
    GT521FX_CMD_ENROLL_2             	= 0x24,
    GT521FX_CMD_ENROLL_3             	= 0x25,
    GT521FX_CMD_IS_PRESS_FINGER         = 0x26,
    GT521FX_CMD_DELETE_ID               = 0x40,
    GT521FX_CMD_DELETE_ALL             	= 0x41,
    GT521FX_CMD_VERIFY                  = 0x50,
    GT521FX_CMD_IDENTIFY                = 0x51,
    GT521FX_CMD_VERIFY_TEMPLATE         = 0x52,
    GT521FX_CMD_IDENTIFY_TEMPLATE       = 0x53,
    GT521FX_CMD_CAPTURE_FINGER         	= 0x60,
    GT521FX_CMD_MAKE_TEMPLATE           = 0x61,
    GT521FX_CMD_GET_IMAGE               = 0x62,
    GT521FX_CMD_GET_RAW_IMAGE           = 0x63,
    GT521FX_CMD_GET_TEMPLATE            = 0x70,
    GT521FX_CMD_SET_TEMPLATE            = 0x71,
    GT521FX_CMD_GET_DATABASE_START      = 0x72,
    GT521FX_CMD_GET_DATABASE_END        = 0x73,
    GT521FX_CMD_SET_SECURITY_LEVEL      = 0xF0,
    GT521FX_CMD_GET_SECURITY_LEVEL      = 0xF1,
    GT521FX_CMD_IDENFITY_TEMPLATE_2     = 0xF4,
    GT521FX_CMD_ENTER_STANDBY           = 0xF9,
    GT521FX_CMD_ACK                     = 0x30,
    GT521FX_CMD_NACK                    = 0x31,
} gt_521fx_cmd_e;


typedef enum
{
	GT521FX_ENROLLMENT_STAGE_FIRST,
	GT521FX_ENROLLMENT_STAGE_SECOND,
	GT521FX_ENROLLMENT_STAGE_THIRD,
} gt_521fx_enrollment_stage_e;


typedef enum
{
	GT521FX_NO_ERROR                       = 0x0000,
	GT521FX_ERROR_DUPLICATE_ID			   = 0x0001,
	GT521FX_ERROR_TIMEOUT                  = 0x1001,
	GT521FX_ERROR_INVALID_BAUDRATE         = 0x1002,
	GT521FX_ERROR_INVALID_POS              = 0x1003,
	GT521FX_ERROR_IS_NOT_USED              = 0x1004,
	GT521FX_ERROR_IS_ALREADY_USED          = 0x1005,
	GT521FX_ERROR_COMM_ERR                 = 0x1006,
	GT521FX_ERROR_VERIFY_FAILED            = 0x1007,
	GT521FX_ERROR_IDENTIFY_FAILED          = 0x1008,
	GT521FX_ERROR_DB_IS_FULL               = 0x1009,
	GT521FX_ERROR_DB_IS_EMPTY              = 0x100A,
	GT521FX_ERROR_TURN_ERR                 = 0x100B,
	GT521FX_ERROR_BAD_FINGER               = 0x100C,
	GT521FX_ERROR_ENROLL_FAILED            = 0x100D,
	GT521FX_ERROR_IS_NOT_SUPPORTED         = 0x100E,
	GT521FX_ERROR_DEV_ERR                  = 0x100F,
	GT521FX_ERROR_CAPTURE_CANCELLED        = 0x1010,
	GT521FX_ERROR_INVALID_PARAM            = 0x1011,
	GT521FX_ERROR_FINGER_IS_NOT_PRESSED    = 0x1012,
	GT521FX_ERROR_SRW_ENROLL_FAILURE	   = 0x2000,
	// duplicate ID error is [0,2999] I believe this is because there can be 3000 fingerprints saved
	GT521FX_NO_ERROR_ACK				   = 0xFFFF,
} gt_521fx_error_e;


typedef enum
{
	GT521FX_SECURITY_LVL_0	= 0,
	GT521FX_SECURITY_LVL_1	= 1,
	GT521FX_SECURITY_LVL_2	= 2,
	GT521FX_SECURITY_LVL_3	= 3,
	GT521FX_SECURITY_LVL_4	= 4,
	GT521FX_SECURITY_LVL_5	= 5
} gt_521fx_security_lvl_e;


void gt521fx_fingerprint_init(void);
void gt521fx_open(void);
void gt521fx_led_off(void);
void gt521fx_led_on(void);
void gt521fx_delete_all(void);
void gt521fx_change_baud_rate(uint16_t baud_rate);
void gt521fx_start_enrollment(uint16_t id);
void gt521fx_enrollment(gt_521fx_enrollment_stage_e stage);
void gt521fx_capture_finger(bool enroll_stage);
void gt521fx_finger_is_pressed(void);
void gt521fx_delete_all_fingerprints(void);
void gt521fx_delete_fingerprint(uint16_t id);
void gt521fx_nack_state_set(gt_521fx_error_e err);
void gt521fx_nack_flag_set(bool flag);
void gt521fx_finger_is_pressed_set(bool flag);
void gt521fx_security_lvl_set(uint8_t lvl);
void gt521fx_identified_id_set(uint16_t id);
void gt521fx_enrolled_fingerprint_count_set(uint16_t count);
void identified_id_set(uint16_t id);
void security_lvl_set(uint8_t lvl);
void finger_is_pressed_set(bool flag);
void enrolled_fingerprint_count_set(uint16_t count);
void nack_state_set(gt_521fx_error_e err);
void nack_flag_set(bool flag);
void gt521fx_finger_is_pressed_clear(void);

bool gt521fx_initialized(void);
bool gt521fx_nack_flag(void);
bool gt521fx_finger_is_pressed_flag(void);
bool gt521fx_fingerprint_identify(void);

uint16_t flash_access_gt521fx_enroll_count(void);
uint16_t flash_access_gt521fx_cur_id(void);

gt_521fx_error_e gt521fx_enroll_finger(uint16_t id);

#endif /* INC_GT_521FX_DRIVER_H_ */
