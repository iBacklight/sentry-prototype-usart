/*
 * Gimbal_App.c
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */

#include <string.h>
#include "Gimbal_App.h"
#include "Timer_App.h"


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
  char *pdata; // data packet from computer
  double vmax=30000;
  double max_angle=4096;
  pdata = malloc(PACKLEN+1);

  /* Infinite loop */
	//buzzer_play_chromatic(100);
	//buzzer_play_mario(200);
	//int16_t message=7500;

	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	velocity=3000;
	//can_filter_enable(&hcan1);

	//Variables for a part that doesn't work yet
/*
	uint16_t counter=0;*/

	//End of variables that doesn't work

  for(;;)
  {
	 /*
	  //Motor_pid_set_angle(&motor_data[4],360,vmax/max_angle,0,0);
	 // packet total size, referring to comm protocol

	  if (HAL_UART_Receive(&husart6, (char*)pdata, (PACKLEN+1), HAL_MAX_DELAY) == HAL_OK){ // origin:huart7
		  HAL_GPIO_TogglePin(GPIOG, LD_H_Pin);
		  comm_pack.yaw_data = parse_pack_indv(pdata, YAW_POS, DATALEN);
		  // comm_pack.yaw_data = parse_pack_indv(pdata, TARGET_POS, STATELEN);
		  //comm_pack = parse_pack_string(pdata);
		  if (comm_pack.pack_cond == PACKCOR){ //&& comm_pack.pitch_data == 5678 && comm_pack.fire_cmd == 0){
				 HAL_GPIO_WritePin(GPIOG, LD_C_Pin, RESET);
		  }
		  HAL_UART_Transmit(&husart6, (char*)pdata, (PACKLEN+1),HAL_MAX_DELAY);
	 }
	 if (comm_pack.yaw_data == 1234){ //&& comm_pack.pitch_data == 5678 && comm_pack.fire_cmd == 0){
		 HAL_GPIO_WritePin(GPIOG, LD_B_Pin, RESET);
	  }

	  //HAL_GPIO_WritePin(GPIOG, LD_B_Pin, GPIO_PIN_RESET);
	  Motor_set_raw_value(&motor_data[0], comm_pack.yaw_data);*/
	  /*if (HAL_UART_Receive(&husart6, (char*)pdata, (PACKLEN+1), 1) == HAL_OK){
		  HAL_GPIO_TogglePin(GPIOG, LD_H_Pin);
		  comm_pack=parse_all(pdata);
		  HAL_UART_Transmit(&husart6, (char*)pdata, (PACKLEN+1),1);
	  }
	  if (comm_pack.pack_cond==PACKCOR){
//		  buzzer_play_c1(500);
	  }
	  else if (comm_pack.pack_cond==PACKERR){
//		  buzzer_play_mario(120);
	  }
	  double temp = angle_preprocess(4, comm_pack.yaw_data);
	  Motor_pid_set_angle(&motor_data[4], angle_preprocess(4, comm_pack.yaw_data), 1,0,0);
	  char arr[sizeof(temp)+1];
	  memcpy(arr,&temp,sizeof(temp)+1);
	  arr[sizeof(temp)] = 0x0A;
	  HAL_UART_Transmit(&husart6, (char*)arr, sizeof(temp)+1,1);*/
	  Motor_pid_set_angle(&motor_data[4], 0, vmax/max_angle,0,0);
	  //Motor_set_raw_value(&motor_data[4],-3000);
	  osDelay(1);
  }
	free(pdata);

  /* USER CODE END Gimbal_Task_Function */
}


double angle_preprocess(int16_t motor_ID, int16_t recieved_angle){
	Motor temp_motor_buffer;
	int16_t rx_angle;
	int16_t input_angle;
	int16_t target_angle;
	input_angle=round(recieved_angle/360*8192);

	get_Motor_buffer(&motor_data[motor_ID], &temp_motor_buffer);
	rx_angle=temp_motor_buffer.motor_feedback.rx_angle;

	target_angle=input_angle + rx_angle;
	target_angle=(8192+target_angle) % 8192;

	return (double)(target_angle/8192*360);
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

    char pdata[(strlen(pack)+1)]; //pack content size + '\0'
    int32_t data = 0;
    strcpy(pdata, pack);

    if (pdata[0] == 0x41){ //check received correct pack head frame， modify here to 0xAA in real world test
		for(int i=0; i<lens; i++){
            data += (int32_t)((pdata[pos-i-1] - '0')*pow(10,i)); // decoding, referring to the vision code.
		}
    }
	else{
		data = -1;
	}
    osDelay(1);
    return data;
}
//int32_t parse_pack_indv(char* pack, char* parse_data, int pos){
//
//    char pdata[(strlen(pack)+1)]; //pack content size + '\0'
//    int32_t data = 0;
//    strcpy(pdata, pack);
//
//    if (pdata[0] == 0x41){ //check received correct pack head frame， modify here to 0xAA in real world test
//    	HAL_GPIO_WritePin(GPIOG, LD_A_Pin, GPIO_PIN_RESET); // if correct, turn 1st led on
//    	// FIXME: if the data is no longer 4 bytes, e.g. fire cmd only have 1 bytes, there should be an additional Conditional Statements.
//		for(int i=0;i<4;i++){
//			parse_data[i] = pdata[pos-i-1] - '0'; // decoding, referring to the vision code.
//            data += (int32_t)((parse_data[i])*pow(10,i));
//		}
//    }
//	else{
//		parse_data[0] = NULL;
//		osDelay(1);
//	}
//
//    //data++; // plus 1 to ensure the correct output
//    return data;
//}

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

comm_rx_info parse_all(char* pack)
{
    comm_rx_info Sentry_Pack;
    Sentry_Pack.yaw_data = 0;
    Sentry_Pack.pitch_data = 0;
    Sentry_Pack.dist_data = 0;
    Sentry_Pack.fire_cmd = 0;
    Sentry_Pack.target_num = 0;
    Sentry_Pack.pack_cond=0;

    //int position = 6;
    //unsigned char data;
    //int power;

    if (strlen(pack) == PACKLEN)
    {
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
    }
    else
    {
        Sentry_Pack.pack_cond = PACKERR;
        HAL_GPIO_WritePin(GPIOG, LD_G_Pin, RESET);
    }
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
