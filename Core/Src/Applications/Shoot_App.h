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
#include "../Device/Motor.h"
#include "Gimbal_App.h"

//Max and min PWM pulse width time, this differs for different motors, units in us
//The big drone motors from hobbywing, which is used to power the large friction wheels has a max pulse widthof 2000us, and min of 1000us
//The smaller snail motors from robomaster for small friction wheels have a max on-time of 2200, and min of 400us
//Consult the datasheet when in doubt, if there are none, try 2000 and 1000
#define MAX_PWM_ON_TIME 2200
#define MIN_PWM_ON_TIME 400

//Max input value (abs) for magazine motor, for p2006, it is 10000, for 3508 it is 16000, for 6020 it is 30000
#define MAG_MOTOR_MAX_SPEED 10000

void Shoot_Task_Func(void const * argument);



#endif /* SRC_APPLICATIONS_SHOOT_APP_H_ */
