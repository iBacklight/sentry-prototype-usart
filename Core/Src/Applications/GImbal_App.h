/*
 * GImbal_App.h
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */

#ifndef SRC_APPLICATIONS_GIMBAL_APP_H_
#define SRC_APPLICATIONS_GIMBAL_APP_H_

#include "main.h"
#include "can.h"
#include "cmsis_os.h"
#include "../buzzer.h"
#include "../Device/Motor.h"

#define PACKLEN  16
#define DATALEN  4
#define STATELEN 1
#define PACKCOR 0
#define PACKERR 1

#define YAW_POS 6
#define PITCH_POS YAW_POS+DATALEN
#define DIST_POS PITCH_POS+DATALEN
#define TARGET_POS DIST_POS+STATELEN
#define FCMD_POS TARGET_POS+STATELEN

typedef struct {
	int32_t yaw_data;
	int32_t pitch_data;
	int32_t dist_data;
	int32_t target_num;
	int32_t fire_cmd;
	int32_t pack_cond;
}comm_rx_info;

int32_t parse_pack_indv(char* pack, int pos, int lens);
comm_rx_info parse_pack_string(char* pack);
comm_rx_info parse_all(char* pack);

double angle_preprocess(Motor* motor, int16_t recieved_angle);
comm_rx_info comm_pack;

void Gimbal_Task_Function(void const * argument);
void CAN_Send_Gimbal(int16_t yaw_raw, int16_t pitch_raw);
int32_t parse_pack(char* pack, char* yaw_data);

#endif /* SRC_APPLICATIONS_GIMBAL_APP_H_ */
