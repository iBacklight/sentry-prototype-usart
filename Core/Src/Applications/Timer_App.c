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

	char *pdata; // temp data packet buffer from computer
	char *yaw;
	yaw = malloc (4);
	pdata = malloc(PACKLEN+1);

	for (;;){
		// UART catcher

		 // Fix here: may add a switch or what to determine what data needed
		 int pos = 6; // yaw pos
		 // packet total size, referring to comm protocol

		 if (HAL_UART_Receive(&huart7, (char*)pdata, (PACKLEN+1), HAL_MAX_DELAY) == HAL_OK){
			  HAL_GPIO_TogglePin(GPIOG, LD_H_Pin);
			  //comm_pack.yaw_data = parse_pack_indv(pdata, yaw, pos);
			  comm_pack = parse_pack_string(pdata);
			  if (comm_pack.pack_cond == PACKCOR) //&& comm_pack.pitch_data == 5678 && comm_pack.fire_cmd == 0){
			  		 HAL_GPIO_WritePin(GPIOG, LD_C_Pin, RESET);
		 }
		 if (comm_pack.yaw_data == 1234) //&& comm_pack.pitch_data == 5678 && comm_pack.fire_cmd == 0){
			 HAL_GPIO_WritePin(GPIOG, LD_B_Pin, RESET);
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

/*
 * @ Func name: parse_pack_indv
 * @ Use: parse the packages sent from computer and output the motor data based on data pos
 * @ Parameter:  pack: the package received from UART
 * 			     parse_data: corresponding data variable, could be yaw, pitch, etc
 * 			     pos: The position of the last byte of the currently extracted data
 * @ Return:
 * @ Author: Haoran Qi, Created on: Jan, 2022
 */
int32_t parse_pack_indv(char* pack, char* parse_data, int pos){

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

/*
 * @ Func name: parse_pack_string
 * @ Use: parse the packages sent from computer and output the motor data based on pcak data itself.
 * @ Parameter:
 * 		pack: the package received from UART
 *
 * @ Return:
 * @ Author: Wei, Shitang, Haoran, Created on: Feb, 2022
 */
comm_rx_info parse_pack_string(char* pack)
{
	comm_rx_info Sentry_Pack;
    Sentry_Pack.yaw_data = 0;
    Sentry_Pack.pitch_data = 0;
    Sentry_Pack.dist_data = 0;
    Sentry_Pack.fire_cmd = 0;
    Sentry_Pack.target_num = 0;

    int position = 6;
    unsigned char data;
    int power;

    if (strlen(pack) == PACKLEN)
    {
        if (pack[0] == 0x41)
        {
            for (int i = 2; i< PACKLEN-1; i++)
            {
                if(pack[i]>='0' && pack[i] <= '9')
                {
                    Sentry_Pack.pack_cond = PACKCOR;
                }
                else
                {
                    Sentry_Pack.pack_cond = PACKERR;
                    HAL_GPIO_WritePin(GPIOG, LD_D_Pin, RESET);
                    break;
                }
            }
                if(pack[PACKLEN-1]=='0' || pack[PACKLEN-1] == '1') {
                    Sentry_Pack.pack_cond = PACKCOR;
                }
                else
                {
                    Sentry_Pack.pack_cond = PACKERR;
                    HAL_GPIO_WritePin(GPIOG, LD_E_Pin, RESET);
                }
            if(Sentry_Pack.pack_cond == PACKCOR)
            {
                for(int i=0;i<DATALEN;i++)
                {
                    data = pack[position-i-1] - '0';
                    power = ((int)data)*(pow(10,i));
                    Sentry_Pack.yaw_data += ((int)data)*(pow(10,i));
                }
                position = position + DATALEN;

                for(int i=0;i<DATALEN;i++)
                {
                    data = pack[position-i-1] - '0';
                    Sentry_Pack.pitch_data += ((int)data)*(pow(10,i));
                }
                position = position + DATALEN;

                for(int i=0;i<DATALEN;i++)
                {
                    data = pack[position-i-1] - '0';
                    Sentry_Pack.dist_data += ((int)data)*(pow(10,i));
                }
                position = position + STATELEN;

                data = pack[position - 1] - '0';
                Sentry_Pack.target_num = ((int) data);

                position = position + STATELEN;

                data = pack[position - 1] - '0';
                Sentry_Pack.fire_cmd = ((int) data);
            }
        }
        else
        {
            Sentry_Pack.pack_cond = PACKERR;
            HAL_GPIO_WritePin(GPIOG, LD_F_Pin, RESET);
        }
    }
    else
    {
        Sentry_Pack.pack_cond = PACKERR;
        HAL_GPIO_WritePin(GPIOG, LD_G_Pin, RESET);
    }
    return Sentry_Pack;
}
