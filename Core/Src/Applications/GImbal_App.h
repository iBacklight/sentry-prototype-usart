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

//These are ABSOLUTE ANGLES, calibrate manually.
#define INIT_YAW 0
#define INIT_PITCH 0
#define YAW_MAX_HALF_DELTA 2048
#define YAW_MAX_PITCH_DELTA 2048
#define MAX_PITCH_CHANGE_TIME 10
#define FRONT_ANGLE 80 //Hard set front and back angles
#define BACK_ANGLE 280

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
double abs_pitch;
double abs_yaw;
void SweepAndPatrol(void);
comm_rx_info comm_pack;
char *pdata[PACKLEN]; // data packet from computer //Make sure to define a size, else the interrupt will not work!
int16_t yaw_rx_angle;
int16_t pitch_rx_angle;

void Gimbal_Task_Function(void const * argument);
void CAN_Send_Gimbal(int16_t yaw_raw, int16_t pitch_raw);
int32_t parse_pack(char* pack, char* yaw_data);
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* SRC_APPLICATIONS_GIMBAL_APP_H_ */
