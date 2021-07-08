/*
 * Gimbal_App.c
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */

#include "Gimbal_App.h"
#include "Timer_App.h"



static uint8_t chassis_can_send_data[8];
static CAN_TxHeaderTypeDef  chassis_tx_message;

extern CAN_HandleTypeDef hcan1;
extern UART_HandleTypeDef huart7;
extern TIM_HandleTypeDef htim14;

int16_t current_angle;
//Velocity, from -30000 to 30000
int16_t velocity;

void Gimbal_Task_Function(void const * argument)
{


  /* USER CODE BEGIN Gimbal_Task_Function */
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
	  HAL_GPIO_TogglePin(LD_C_GPIO_Port, LD_C_Pin);

	  Motor_set_raw_value(&motor_data[4],15000);

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
