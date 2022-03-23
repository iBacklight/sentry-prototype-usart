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

#define CLOCKWISE 1
#define COUNTER_CLOCKWISE -1

extern uint32_t period_counter;

void Chassis_Task_Func(void const * argument);
double UltraSoundFindDistance(void);
void delay_us(uint32_t delay_us);
void motor_move_period(uint32_t cycles, double vel, int32_t direction);

#endif /* SRC_APPLICATIONS_CHASSIS_APP_H_ */
