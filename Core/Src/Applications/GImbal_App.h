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

void Gimbal_Task_Function(void const * argument);
void CAN_Send_Gimbal(int16_t yaw_raw, int16_t pitch_raw);
int32_t parse_pack(char* pack, char* yaw_data);

#endif /* SRC_APPLICATIONS_GIMBAL_APP_H_ */
