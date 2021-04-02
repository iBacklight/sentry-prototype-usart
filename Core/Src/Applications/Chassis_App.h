/*
 * Chassis_App.h
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */

#ifndef SRC_APPLICATIONS_CHASSIS_APP_H_
#define SRC_APPLICATIONS_CHASSIS_APP_H_

#include "main.h"
#include "cmsis_os.h"
#include "../buzzer.h"
#include "../Device/Motor.h"

void Chassis_Task_Func(void const * argument);


#endif /* SRC_APPLICATIONS_CHASSIS_APP_H_ */
