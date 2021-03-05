/*
 * Timer_App.c
 *	This function is invoked every 1s to read data from CAN
 *  Created on: Mar 4, 2021
 *      Author: AzureRin
 */

#include "Timer_App.h"

uint8_t can_rx_buffer[8];

void Timer_Task_Func(void const * argument){

uint32_t tick;
	for (;;){

		tick=HAL_GetTick();
		//buzzer_play_g0(100);
		//printf("CurrentTime \n");
		printf("CurrentTime: %d \n",(uint32_t)tick);

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

//This function activates whenever the RxFifo receives a message persumably? But it doesnt seem to work right now
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	CAN_RxHeaderTypeDef rx_header;
	rx_header.StdId = (CAN_RI0R_STID & hcan->Instance->sFIFOMailBox[CAN_RX_FIFO0].RIR) >> CAN_TI0R_STID_Pos;
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, can_rx_buffer);
	//HAL_GPIO_TogglePin(LED_Red_GPIO_Port,LED_Red_Pin);
	//HAL_Delay(1000);
}
