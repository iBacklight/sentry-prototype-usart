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
extern UART_HandleTypeDef huart7;

void Gimbal_Task_Function(void const * argument)
{


  /* USER CODE BEGIN Gimbal_Task_Function */
  /* Infinite loop */
	//buzzer_play_chromatic(100);

	//buzzer_play_mario(200);
	//int16_t message=7500;


	can_filter_enable(&hcan1);

  for(;;)
  {
	  HAL_GPIO_TogglePin(LD_C_GPIO_Port, LD_C_Pin);
	  CAN_Send_Gimbal(7500,0);



	  //osDelay(500);
	  osDelay(3);
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

//This function activates whenever the RxFifo receives a message persumably? But it doesnt seem to work right now
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	HAL_GPIO_TogglePin(LED_Red_GPIO_Port,LED_Red_Pin);
	HAL_Delay(1000);
}

void can_filter_enable(CAN_HandleTypeDef* hcan){
	CAN_FilterTypeDef CAN_FilterConfigStructure;

	CAN_FilterConfigStructure.FilterIdHigh = 0x0000;
	CAN_FilterConfigStructure.FilterIdLow = 0x0000;
	CAN_FilterConfigStructure.FilterMaskIdHigh = 0x0000;
	CAN_FilterConfigStructure.FilterMaskIdLow = 0x0000;
	CAN_FilterConfigStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	CAN_FilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
	CAN_FilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
	CAN_FilterConfigStructure.FilterActivation = ENABLE;
	CAN_FilterConfigStructure.SlaveStartFilterBank = 27;

	CAN_FilterConfigStructure.FilterBank = 0;

	HAL_CAN_ConfigFilter(hcan, &CAN_FilterConfigStructure);
}

void can_filter_disable(CAN_HandleTypeDef* hcan){
	CAN_FilterTypeDef CAN_FilterConfigStructure;

	CAN_FilterConfigStructure.FilterIdHigh = 0x0000;
	CAN_FilterConfigStructure.FilterIdLow = 0x0000;
	CAN_FilterConfigStructure.FilterMaskIdHigh = 0x0000;
	CAN_FilterConfigStructure.FilterMaskIdLow = 0x0000;
	CAN_FilterConfigStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	CAN_FilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
	CAN_FilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
	CAN_FilterConfigStructure.FilterActivation = DISABLE;
	CAN_FilterConfigStructure.SlaveStartFilterBank = 27;

	CAN_FilterConfigStructure.FilterBank = 0;

	HAL_CAN_ConfigFilter(hcan, &CAN_FilterConfigStructure);
}

//This function occurs whenever an EXTI line is called, the EXTI needs to be setup in the ioc file, and button pin is setup as interrupt (EXTI2) right now, and hence, whenver the white button is pressed, this function below is activated
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == Button_Pin){
		//can_filter_enable(&hcan1);


		printf("\n======== 6020 DATA REPORT ========\r\n"
	             "ID           %d\r\n"
	             "Angle        %d\r\n"
	             "Current      %d\r\n"
	             "Speed        %d\r\n"
	             "Temperature  %u\r\n"
	             "=================================\r\n\r\n",1,1,1,1,1);

		//Adding HAL_Delay would stop the entire code!
		//HAL_Delay(5000);

		//can_filter_disable(&hcan1);


	}
}
