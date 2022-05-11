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


#define PACKLEN  16
#define DATALEN  4
#define STATELEN 1
#define PACKCOR 0
#define PACKERR 1

typedef struct {
	int32_t yaw_data;
	int32_t pitch_data;
	int32_t dist_data;
	int32_t target_num;
	int32_t fire_cmd;
	int32_t pack_cond;
}comm_rx_info;

void Timer_Task_Func(void const * argument);
int32_t parse_pack_indv(char* pack, char* parse_data, int pos);
comm_rx_info parse_pack_string(char* pack);


#endif /* SRC_APPLICATIONS_TIMER_APP_H_ */
