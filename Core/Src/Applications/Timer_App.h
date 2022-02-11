/*
 * Timer_App.h
 *
 *  Created on: Mar 4, 2021
 *      Author: AzureRin
 */

#ifndef SRC_APPLICATIONS_TIMER_APP_H_
#define SRC_APPLICATIONS_TIMER_APP_H_

#include "main.h"
#include "cmsis_os.h"
#include "../buzzer.h"
#include "can.h"
#include "../Device/Motor.h"

typedef struct {
	int32_t yaw_data;
	int32_t pitch_data;
	int32_t dist_data;
	int32_t fire_cmd;
}comm_rx_info;

comm_rx_info comm_pack;
void Timer_Task_Func(void const * argument);
int32_t parse_pack(char* pack, char* parse_data, int pos);

#endif /* SRC_APPLICATIONS_TIMER_APP_H_ */
