/*
 * gt_521fx_driver.c
 *
 *  Created on: Aug 4, 2020
 *      Author: spud
 */
#include "stm32l4xx_hal.h"
#include "stdbool.h"
#include "packet_queue.h"
#include "gt_521fx_driver.h"
#include "ssd1351_driver.h"

extern UART_HandleTypeDef huart1;

#define DEFAULT_DEV_ID  		0x0001
#define ACK     				0x30
#define NACK    				0x31
#define LED_ON                  0x01
#define LED_OFF                 0x00


bool g_nack_flag = false;
bool g_finger_is_pressed = false;
bool g_gt521fx_initialized = false;
uint8_t g_security_lvl = 0;
uint16_t g_identified_id = 0;
uint16_t g_enrolled_fingerprint_count = 0;
uint16_t gt521fx_identified_id(void);
pkt_t gt521fx_tx_pkt;
gt_521fx_error_e g_nack_state = GT521FX_NO_ERROR_ACK;


uint16_t gt521fx_enrolled_fingerprint_count(void);


void gt521fx_nack_flag_set(bool flag)
{
	g_nack_flag = flag;
}


void gt521fx_nack_state_set(gt_521fx_error_e err)
{
	g_nack_state = err;
}


bool gt521fx_nack_flag(void)
{
	return g_nack_flag;
}


uint16_t gt521fx_enrolled_fingerprint_count(void)
{
	return g_enrolled_fingerprint_count;
}


void gt521fx_enrolled_fingerprint_count_set(uint16_t count)
{
	g_enrolled_fingerprint_count = count;
}


bool gt521fx_initialized(void)
{
	return g_gt521fx_initialized;
}


void gt521fx_finger_is_pressed_clear(void)
{
	g_finger_is_pressed = false;
}


void gt521fx_finger_is_pressed_set(bool flag)
{
	g_finger_is_pressed = flag;
}


bool gt521fx_finger_is_pressed_flag(void)
{
	return g_finger_is_pressed;
}


void gt521fx_security_lvl_set(uint8_t lvl)
{
	g_security_lvl = lvl;
}


void gt521fx_identified_id_set(uint16_t id)
{
	g_identified_id = id;
}


uint16_t gt521fx_identified_id(void)
{
	return g_identified_id;
}


void gt521fx_led_on(void)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_CMOS_LED, LED_ON);
}


void gt521fx_led_off(void)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_CMOS_LED, LED_OFF);
}


void gt521fx_open(void)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_OPEN, 0);
}


void gt521fx_change_baud_rate(uint16_t baud_rate)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_CHANGE_BAUD_RATE, baud_rate);
}


bool gt521fx_check_enrollment_status(uint16_t id)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_CHECK_ENROLLED, id);
	while(!pkt_received());
	clear_pkt_received_flag();
	if (gt521fx_nack_flag()) return false;
	else return true;
}


void gt521fx_start_enrollment(uint16_t id)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_ENROLL_START, id);
}


void gt521fx_enrollment(gt_521fx_enrollment_stage_e stage)
{
	gt_521fx_cmd_e cmd_stage = GT521FX_CMD_ENROLL_1;
	switch (stage)
	{
		case GT521FX_ENROLLMENT_STAGE_FIRST: // intentionally fall through
			cmd_stage = GT521FX_CMD_ENROLL_1;
		break;
		case GT521FX_ENROLLMENT_STAGE_SECOND: // intentionally fall through
			cmd_stage = GT521FX_CMD_ENROLL_2;
		break;
		case GT521FX_ENROLLMENT_STAGE_THIRD: // intentionally fall through
			cmd_stage = GT521FX_CMD_ENROLL_3;
		break;
		default:
			while(1);
		break;
	}
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, cmd_stage, 0);
}


void gt521fx_finger_is_pressed(void)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_IS_PRESS_FINGER, 0);
}


void gt521fx_delete_all_fingerprints(void)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_DELETE_ALL, 0);
}


void gt521fx_delete_fingerprint(uint16_t id)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_DELETE_ID, id);
}


bool gt521fx_fingerprint_verified(uint16_t id)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_VERIFY, 0);
	while(!pkt_received());
	clear_pkt_received_flag();
	if (gt521fx_nack_flag()) return false;
	else return true;
}


bool gt521fx_fingerprint_identify(void)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_IDENTIFY, 0);
	while(!pkt_received());
	clear_pkt_received_flag();
	if (gt521fx_nack_flag()) return false;
	else return true;
}


void gt521fx_capture_finger(void)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_CAPTURE_FINGER, 0);
}


void gt521fx_set_security_level(gt_521fx_security_lvl_e security_lvl)
{
	packet_create_cmd_and_send((p_packet_handle_t)&gt521fx_tx_pkt, GT521FX_CMD_SET_SECURITY_LEVEL, 0);
}


