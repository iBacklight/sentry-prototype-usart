/*
 * Gimbal_App.c
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */

#include "Gimbal_App.h"

static uint8_t chassis_can_send_data[8];
static CAN_TxHeaderTypeDef  chassis_tx_message;

extern CAN_HandleTypeDef hcan1;

void Gimbal_Task_Function(void const * argument)
{


  /* USER CODE BEGIN Gimbal_Task_Function */
  /* Infinite loop */
	//buzzer_play_chromatic(100);

	//buzzer_play_mario(200);
	//int16_t message=7500;
	HAL_CAN_Start(&hcan1);



  for(;;)
  {
	  //HAL_GPIO_TogglePin(LD_C_GPIO_Port, LD_C_Pin);
	  CAN_Send_Gimbal(7500,0);

	  //osDelay(500);
	  osDelay(1);
  }
  /* USER CODE END Gimbal_Task_Function */
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
