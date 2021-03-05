/*
 * Shoot_App.h
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */

#ifndef SRC_APPLICATIONS_SHOOT_APP_H_
#define SRC_APPLICATIONS_SHOOT_APP_H_


#include "main.h"
#include "cmsis_os.h"
#include "../buzzer.h"

//Max and min PWM on time - motors require it to be between 1000us and 2000us
#define MAX_PWM_ON_TIME 2000
#define MIN_PWM_ON_TIME 1000


void Shoot_Task_Func(void const * argument);



#endif /* SRC_APPLICATIONS_SHOOT_APP_H_ */
