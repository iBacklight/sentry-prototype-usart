/*
 * Timer_App.c
 *	This function is invoked every 1s to read data from CAN
 *  Created on: Mar 4, 2021
 *      Author: AzureRin
 */

#include "Timer_App.h"



void Timer_Task_Func(void const * argument){

uint32_t tick;
	for (;;){
		Motor_Data_Read();
		Motor_Data_Sent();
		printf("Current Angle: %d \n", motor_data[0].motor_feedback.rx_angle);

		//Timer task

		//Write code here to put stuffs from rx buffer into structures
		//Each motor shall have the structure motorstatus representing its status, see definition in timer_app.h
		//All motors should follow an array of structures
		//First start filter
		//Then memcpy from can_rx_buffer to a secondary buffer?
		//Use that something else to assign value to each motor via a function, void fill_in_stuffs_rx_buffer?
		//Then stop filter
		//Read data complete complete

		//Grab send data from other applications
		//Send data

		osDelay(1);

	}


}
