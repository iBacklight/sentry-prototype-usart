/*
 * Timer_App.c
 *	This function is invoked every 1s to read data from CAN
 *  Created on: Mar 4, 2021
 *      Author: AzureRin
 */
#include <string.h>
#include <math.h>
#include "Timer_App.h"

extern UART_HandleTypeDef huart7;

void Timer_Task_Func(void const * argument){

uint32_t tick;
	for (;;){
		// UART catcher
		 char *pdata; // temp data packet buffer from computer
		 char *yaw;
		 // Fix here: may add a switch or what to determine what data needed
		 int pos = 6; // yaw pos
		 yaw = malloc (4);
		 pdata = malloc(7); // packet total size, referring to comm protocol

		 if (HAL_UART_Receive(&huart7, (char*)pdata, 7, HAL_MAX_DELAY) == HAL_OK){
			  HAL_GPIO_TogglePin(GPIOG, LD_H_Pin);
			  comm_pack.yaw_data = parse_pack(pdata, yaw, pos);
		 }
		 if (comm_pack.yaw_data == 1234){
		 		HAL_GPIO_TogglePin(GPIOG, LD_B_Pin);
		  }

		 // HAL_GPIO_WritePin(GPIOG, LD_B_Pin, GPIO_PIN_RESET);
		 Motor_Data_Read();
		 Motor_Data_Sent();
		 Motor temp_buffer;
		 Motor temp_buffer_3508;
		 get_Motor_buffer(&motor_data[4], &temp_buffer);
		 get_Motor_buffer(&motor_data[0], &temp_buffer_3508);

		//printf("Current angle (6020): %d \n", temp_buffer.motor_feedback.rx_angle);
		//printf("Current RPM (3508): %d \n", temp_buffer_3508.motor_feedback.rx_rpm);

		  free(yaw);
		  free(pdata);
		  /* USER CODE END Gimbal_Task_Function */

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

/*
 * Func name: parse_pack
 * Use: parse the packages sent from computer and output the motor data
 * Parameter: @ pack: the package received from UART
 * 			  @ parse_data: corresponding data variable, could be yaw, pitch, etc
 * 			  @ pos: The position of the last byte of the currently extracted data
 * Return:
 * Author: Haoran Qi, Created on: Jan, 2022
 */
int32_t parse_pack(char* pack, char* parse_data, int pos){

    char pdata[(strlen(pack)+1)]; //pack content size + '\0'
    int32_t data = 0;
    strcpy(pdata, pack);

    if (pdata[0] == 0x41){ //check received correct pack head frame， modify here to 0xAA in real world test
    	HAL_GPIO_WritePin(GPIOG, LD_A_Pin, GPIO_PIN_RESET); // if correct, turn 1st led on
    	// FIXME: if the data is no longer 4 bytes, e.g. fire cmd only have 1 bytes, there should be an additional Conditional Statements.
		for(int i=0;i<4;i++){
			parse_data[i] = pdata[pos-i-1] - '0'; // decoding, referring to the vision code.
            data += (int32_t)((parse_data[i])*pow(10,i));
		}
    }
	else{
		parse_data[0] = NULL;
		osDelay(1);
	}


    //data++; // plus 1 to ensure the correct output
    return data;
}
