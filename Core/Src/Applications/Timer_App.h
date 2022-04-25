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



void Timer_Task_Func(void const * argument);

#endif /* SRC_APPLICATIONS_TIMER_APP_H_ */
