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


typedef struct {

	//ID Used to send stuffs

	uint32_t stdid;
	//rx data
	int16_t rx_angle;
	int16_t rx_rpm;
	int16_t rx_current;
	int16_t rx_temp;
	//tx data
	int32_t tx_data;

	//Maybe PID data in here too

} motorstat;

void Timer_Task_Func(void const * argument);
uint8_t can_rx_buffer[8];

#endif /* SRC_APPLICATIONS_TIMER_APP_H_ */
