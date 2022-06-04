/*
 * Gimbal_App.c
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */

#include <string.h>
#include "Gimbal_App.h"
#include "Timer_App.h"
#include "stdio.h"


static uint8_t chassis_can_send_data[8];
static CAN_TxHeaderTypeDef  chassis_tx_message;

extern CAN_HandleTypeDef hcan1;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef husart6;
extern TIM_HandleTypeDef htim14;

int16_t current_angle;
//Velocity, from -30000 to 30000
int16_t velocity;

void Gimbal_Task_Function(void const * argument)
{

  /* USER CODE BEGIN Gimbal_Task_Function */
  double vmax=30000;
  double max_angle=4096;
  int16_t init_complete=-3000; //For the first init_complete*osDelay [ms], initialize gimbal state
  uint16_t pitch_change_counter=0;

  int16_t patrol_dir=1;

  //Init comm pack
  comm_pack.yaw_data = 0;
  comm_pack.pitch_data = 0;
  comm_pack.dist_data = 0;
  comm_pack.fire_cmd = 0;
  comm_pack.target_num = 0;
  Motor temp_motor_buffer;


  /* Infinite loop */
	//buzzer_play_chromatic(100);
	//buzzer_play_mario(200);
	//int16_t message=7500;

	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

	//HAL_UART_Receive_IT(&husart6, pdata, (PACKLEN+1));
	printf("Gimbal App is on! \r\n");
	velocity=3000;
	abs_pitch=0;
	abs_yaw=0;

	//can_filter_enable(&hcan1);

	//Variables for a part that doesn't work yet
/*
	uint16_t counter=0;*/

	//End of variables that doesn't work

  for (int i=0;i<3000;++i){
			Motor_pid_set_angle(&motor_data[4], INIT_YAW, vmax/max_angle,0,0);
			Motor_pid_set_angle(&motor_data[5], INIT_PITCH, vmax/max_angle,0,0);
			osDelay(1);
			//continue; //Keep initializing until its done
  }

  for(;;)
  {
	  //Initialize the gimbal states
	  //Maybe put it outside of for loop


	  //comm_pack=parse_all(pdata);
	  //printf("Yaw: %d;\t Pitch: %d; \t%s\r\n", comm_pack.yaw_data, comm_pack.pitch_data, pdata);
	  //osDelay(1000);
//	  	  comm_pack.pack_cond=PACKERR;
	  	  /*
	  	   * @Note: Parse process(as well as re-transmit and buzzer process) may be placed in interrupt callback (HAL_UART_RxCpltCallback) too
	  	   * 		based on the accuracy of debugging.
	  	   *
	  	   * 		Besides, we may also need to put the func Motor_pid_set_angle in the interrupt (at least before next enable of uart interrupt)
	  	   * 		since we do not know the freq of pack coming, doing this ensures every pack can be set to motor,
	  	   * 		rather than directly entering next uart interrupt.
	  	   *
	  	   * 		SweepAndPatrol may be put in for loop here, as the target num varible will be the quit signal of sweep mode.
	  	   */
	  	  if(comm_pack.target_num == 0){
	  		  pitch_change_counter++;
	  		  if (pitch_change_counter>MAX_PITCH_CHANGE_TIME*1000){
	  			  patrol_dir=patrol_dir*-1;
	  			  pitch_change_counter=0;
	  		  }

	  		  if (patrol_dir==-1){
	  			  Motor_pid_set_angle(&motor_data[5],FRONT_ANGLE,vmax/max_angle,0,0);
	  			  HAL_GPIO_WritePin(GPIOG, LD_C_Pin, RESET);
	  			  HAL_GPIO_WritePin(GPIOG, LD_D_Pin, SET);
	  		  }
	  		  else{
	  			  Motor_pid_set_angle(&motor_data[5],BACK_ANGLE,vmax/max_angle,0,0);
	  			  HAL_GPIO_WritePin(GPIOG, LD_D_Pin, RESET);
	  			  HAL_GPIO_WritePin(GPIOG, LD_C_Pin, SET);
	  		  }

//	  		HAL_GPIO_WritePin(GPIOG, LD_C_Pin, RESET);
//
//	  		  //Get Current angle
//	  		  get_Motor_buffer(&motor_data[4], &temp_motor_buffer);
//	  		  yaw_rx_angle=temp_motor_buffer.motor_feedback.rx_angle; //in 0-8192
//
//	  		  get_Motor_buffer(&motor_data[5], &temp_motor_buffer);
//	  		  pitch_rx_angle=temp_motor_buffer.motor_feedback.rx_angle; //in 0-8192
//
//	  		  if (yaw_rx_angle>((INIT_YAW+YAW_MAX_HALF_DELTA+8192)%8192) && (yaw_rx_angle)<((INIT_YAW-YAW_MAX_HALF_DELTA+8192)%8192)){
//	  			  patrol_dir=patrol_dir*-1;
//	  		  }
//
//	  		  yaw_rx_angle+=patrol_dir*20;
//
//	  		 Motor_pid_set_angle(&motor_data[4], (double)yaw_rx_angle*360/8192, vmax/max_angle,0,0);

	  		  // Activate Sweep&Patrol mode
	  		  //SweepAndPatrol();

	  	  }
	  	  else{
	  		 pitch_change_counter=0; //If there is a target, restart pitch counter
	//		  char* temp_pdata, temp;
	//	  	  strcpy(temp_pdata, pdata);
	//		  comm_pack=parse_all(temp_pdata);
	//		  HAL_UART_Transmit(&husart6, (char*)pdata, (PACKLEN+1),50);
	//		  HAL_UART_Transmit(&husart6, (char*)temp, 17,50);

			  if (comm_pack.pack_cond==PACKCOR){
				  //buzzer_play_c1(500);
				  //printf("InsideTask -> Yaw: %d;\t Pitch: %d; \t%s\r\n", (int16_t)angle_preprocess(&motor_data[4], comm_pack.yaw_data), (int16_t)angle_preprocess(&motor_data[5], comm_pack.pitch_data), pdata);
				  // Guess the following function should be called only if the pack is correct?
				  Motor_pid_set_angle(&motor_data[4], abs_yaw, vmax/max_angle,0,0);
				  Motor_pid_set_angle(&motor_data[5], abs_pitch, vmax/max_angle,0,0);
			  }
			  else if (comm_pack.pack_cond==PACKERR){
				  //buzzer_play_mario(120);
			  }

			  //Motor_pid_set_angle	(&motor_data[4], 0, vmax/max_angle,0,0);
			  //Motor_set_raw_value(&motor_data[4],-3000);
			  //osDelay(1);
	  	  }
		  //Motor_pid_set_angle(&motor_data[4], abs_yaw, vmax/max_angle,0,0);
		  //Motor_pid_set_angle(&motor_data[5], abs_pitch, vmax/max_angle,0,0);
		  osDelay(1);
  }

  /* USER CODE END Gimbal_Task_Function */
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	 // When enter this callback function, the variable pdata has been filled with the received data.
	 // Thus parse it directly.
	  //HAL_UART_Transmit(&husart6, 'Inter',5,0xFFFF);
	  HAL_GPIO_TogglePin(GPIOG, LD_H_Pin);
	  comm_pack=parse_all(pdata);
	  abs_yaw=angle_preprocess(&motor_data[4], comm_pack.yaw_data);
	  abs_pitch=angle_preprocess(&motor_data[5], comm_pack.pitch_data);
	  //Motor_pid_set_angle(&motor_data[4], angle_preprocess(&motor_data[4], comm_pack.yaw_data), vmax/max_angle,0,0);
	  //Motor_pid_set_angle(&motor_data[5], angle_preprocess(&motor_data[5], comm_pack.pitch_data), vmax/max_angle,0,0);
	  //
//	  printf("%s \r\n", pdata);
//	  if(comm_pack.pack_cond == PACKCOR)
//		  printf("Yaw: %d;\t Pitch: %d; \t%s\r\n", (int16_t)angle_preprocess(&motor_data[4], comm_pack.yaw_data), (int16_t)angle_preprocess(&motor_data[5], comm_pack.pitch_data), pdata);
//	  // Enable the uart interrupt again
	  HAL_UART_Receive_IT(&husart6, (char*)pdata, (PACKLEN));
}


double angle_preprocess(Motor* motor, int16_t recieved_angle){
	Motor temp_motor_buffer;
	int16_t rx_angle;
	int16_t input_angle;
	int16_t target_angle;
	input_angle=round(recieved_angle*8192/360);

	get_Motor_buffer(motor, &temp_motor_buffer);
	rx_angle=temp_motor_buffer.motor_feedback.rx_angle;

	target_angle=input_angle + rx_angle;
	target_angle=(8192+target_angle) % 8192;

	return (double)(target_angle*360/8192);
}

void SweepAndPatrol(void){

	Motor temp_motor_buffer;
	int16_t rx_angle, i;
	double vmax_patrol=20000;
	double max_angle_patrol=4096;

	// Enter while loop to sweep the gimbal
	while(1){
		// Obtain the current angle
		get_Motor_buffer(&motor_data[4], &temp_motor_buffer);
		rx_angle=temp_motor_buffer.motor_feedback.rx_angle;

		for(i= rx_angle;i<2048;i++){ //Go to 180
			if(comm_pack.target_num > 0)
				return;
			Motor_pid_set_angle(&motor_data[4],i/8192*360,vmax_patrol/max_angle_patrol,0,0);
		}

		for(i= 2048; i>0; i--){ //Go back to 0
			if(comm_pack.target_num > 0)
				return;
			Motor_pid_set_angle(&motor_data[4],i/8192*360,vmax_patrol/max_angle_patrol,0,0);
		}

		for(i= 8192; i>(8192-2048); i--){ //Go to -180
			if(comm_pack.target_num > 0)
				return;
			Motor_pid_set_angle(&motor_data[4],i/8192*360,vmax_patrol/max_angle_patrol,0,0);
		}

	}
}

/*
 * @ Func name: parse_pack_indv
 * @ Use: parse the packages sent from computer and output the motor data based on data pos
 * @ Parameter:  pack: the package received from UART.
 * 			     pos: The position of the last byte of the currently extracted data, e.g. yaw.
 * 			     lens: the length of current data, e.g. yaw.
 * @ Return:
 * @ Author: Haoran Qi, Created on: Jan, 2022
 */
int32_t parse_pack_indv(char* pack, int pos, int lens){
	char pdata_temp[PACKLEN]; //pack content size + '\0'
	    int32_t data = 0;
	    memcpy(pdata_temp, pack, PACKLEN);

	    if (pdata_temp[0] == 0x41){ //check received correct pack head frame， modify here to 0xAA in real world test
			for(int i=0; i<lens; i++){
	            data += (int32_t)((pdata_temp[pos-i-1] - '0')*pow(10,i)); // decoding, referring to the vision code.
			}
	    }
		else{
			data = -1;
		}
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

/*
 * @ Func name: parse_all
 * @ Use: parse the packages sent from computer using defined parse indv function
 * @ Parameter:
 *   pack: the package received from UART
 *
 * @ Return: Parsed pack
 * @ Author: Wenyuan, Wei Created on: May, 2022
 */
comm_rx_info parse_all(char* pack)
{
	comm_rx_info Sentry_Pack;
	Sentry_Pack.yaw_data = 0;
	Sentry_Pack.pitch_data = 0;
	Sentry_Pack.dist_data = 0;
	Sentry_Pack.fire_cmd = 0;
	Sentry_Pack.target_num = 0;
	Sentry_Pack.pack_cond=PACKERR;

	//int position = 6;
	//unsigned char data;
	//int power;

//	if (strlen(pack) == PACKLEN)
//	{
		if (pack[0] == 0x41) //start with 'A'
		{
			for (int i = 2; i< PACKLEN-1; i++)
			{
				if(pack[i]>='0' && pack[i] <= '9') // make sure each number is 0~9
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

			if(pack[PACKLEN-1]=='0' || pack[PACKLEN-1] == '1') {// fire command is '0' or '1'
				Sentry_Pack.pack_cond = PACKCOR;
			}
			else
			{
				Sentry_Pack.pack_cond = PACKERR;
				HAL_GPIO_WritePin(GPIOG, LD_E_Pin, RESET);
			}
			//only when the format is correct, parse the packet
			if(Sentry_Pack.pack_cond == PACKCOR)
			{
				Sentry_Pack.yaw_data=parse_pack_indv(pack,YAW_POS, DATALEN);
				Sentry_Pack.pitch_data=parse_pack_indv(pack,PITCH_POS,DATALEN);
				Sentry_Pack.dist_data=parse_pack_indv(pack,DIST_POS,DATALEN);
				Sentry_Pack.target_num=parse_pack_indv(pack,TARGET_POS,STATELEN);
				Sentry_Pack.fire_cmd=parse_pack_indv(pack,FCMD_POS,STATELEN);
			}
		}
		else
		{
			Sentry_Pack.pack_cond = PACKERR;
			HAL_GPIO_WritePin(GPIOG, LD_F_Pin, RESET);
		}
//	}
//	else
//	{
//		Sentry_Pack.pack_cond = PACKERR;
//		HAL_GPIO_WritePin(GPIOG, LD_G_Pin, RESET);
//	}
	return Sentry_Pack;

}
    
void CAN_Send_Gimbal(int16_t yaw_raw, int16_t pitch_raw)
{
    uint32_t send_mail_box;
    //chassis_tx_message.StdId = 0x200;  // 3508
	chassis_tx_message.StdId = 0x1FF;  // gimbal
    chassis_tx_message.IDE = CAN_ID_STD;
    chassis_tx_message.RTR = CAN_RTR_DATA;
    chassis_tx_message.DLC = 0x08;
    chassis_can_send_data[0] = yaw_raw >> 8;
    chassis_can_send_data[1] = yaw_raw;
    chassis_can_send_data[2] = pitch_raw >> 8;
    chassis_can_send_data[3] = pitch_raw;
    chassis_can_send_data[4] = 0;
    chassis_can_send_data[5] = 0;
    chassis_can_send_data[6] = 0;
    chassis_can_send_data[7] = 0;

    HAL_CAN_AddTxMessage(&hcan1, &chassis_tx_message, chassis_can_send_data, &send_mail_box);

//    if (check==HAL_OK){
//    	buzzer_play_f1(1000);
//    }
//    else if (check==HAL_ERROR){
//    	buzzer_play_c1(100);
//    	buzzer_play_c1(100);
//    }
//    else{
//    	buzzer_play_c1(100);
//    	buzzer_play_d1(100);
//    	buzzer_play_e1(100);
//    }
}

// UART interrupt callback function

