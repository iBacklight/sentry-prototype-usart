/* USER CODE BEGIN Header_Chassis_Task_Func */
#include "Chassis_App.h"
#include "tim.h"
#include <stdio.h>

/**
* @brief Function implementing the Chassis_Task thread.
* @param argument: Not used
* @retval None
*/
void Chassis_Task_Func(void const * argument)
{

  /* USER CODE BEGIN Chassis_Task_Func */
	//buzzer_play_mario(200);

  double vel=1000; // velocity applied to motor
  int direction = CLOCKWISE; // direction of motor
  uint32_t t=0;
  double distance = -1.0;

  /* Infinite loop */
  for(;;)
  {
	if(direction == CLOCKWISE){
		/* Clockwise Direction */
		// give time counter here
		if (period_counter >= 10) {
			period_counter = 0;
			direction = COUNTER_CLOCKWISE;
		}
		else {
			vel=-1000;
		}
		Motor_set_raw_value(&motor_data[0], vel);

//		if(direction == CLOCKWISE){
//			// give time counter here
//			t++;
//			if(t>=500)
//				period_counter = 0;
//				direction = COUNTER_CLOCKWISE;
//			}
//			else if(t>=400)
//				vel += 1;
//			else
//				vel=-1000;
//			Motor_set_raw_value(&motor_data[0], vel);
//			osDelay(1);
	}
	else{
		/* Counter Clockwise Direction */
		if (period_counter >= 10){
			period_counter = 0;
			direction = CLOCKWISE;
		}
		else{
			vel=1000;
		}
		Motor_set_raw_value(&motor_data[0], vel);

//		t--;
//		if(t<=0){
//			period_counter = 0;
//			direction = CLOCKWISE;
//		}
//		else if(t<=100)
//			vel -= 10;
//		else
//			vel=1000;
//		Motor_set_raw_value(&motor_data[0], vel);
//		osDelay(1);
	}


	/*Ultra Sound Sensor test started here*/
	// trigger the sensor to launch ultraSound wave


//    distance = UltraSoundFindDistance();
//	//printf("distance: %d\n", distance);
//	if(distance > 0 && distance < 150 ){
//		HAL_GPIO_WritePin(LD_A_GPIO_Port,LD_A_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(LD_B_GPIO_Port,LD_B_Pin, GPIO_PIN_SET);
//	}
//	else{
//		HAL_GPIO_WritePin(LD_B_GPIO_Port,LD_B_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(LD_A_GPIO_Port,LD_A_Pin, GPIO_PIN_SET);
//	}
    //osDelay(10);
  }

}

/* USER CODE END Chassis_Task_Func */
double UltraSoundFindDistance(void){
	    // Timer 13 set to pre-scalar as 100us per cnt
		HAL_GPIO_TogglePin(LED_Red_GPIO_Port,LED_Red_Pin);

	    double dis = -1.0;
		uint32_t val = 0;
		GPIO_PinState echo;

		HAL_GPIO_WritePin(UltraSound_Trig_Port, UltraSound_Trig, GPIO_PIN_SET);
		delay_us(10);
		HAL_GPIO_WritePin(UltraSound_Trig_Port, UltraSound_Trig, GPIO_PIN_RESET);
		//TIM13->CNT = 0;

		// Wait for response
		while((echo = HAL_GPIO_ReadPin(UltraSound_Echo_Port, UltraSound_Echo)) == GPIO_PIN_RESET);
		//if( HAL_TIM_Base_Start(&htim13) == HAL_OK){
			val = __HAL_TIM_GET_COUNTER(&htim13); //ideally equal to 0 here
			//Getting response
			while( (echo = HAL_GPIO_ReadPin(UltraSound_Echo_Port, UltraSound_Echo)) == GPIO_PIN_SET);
			//togglePin LD / buzzer
			//if(HAL_TIM_Base_Stop(&htim13) == HAL_OK){
				val = __HAL_TIM_GET_COUNTER(&htim13) - val;
				//Calculate distance
				dis = val * 0.1 * (0.34 * 0.5) * 10;//unit: cm
			//}
		//}
		return dis;
}

void delay_us(uint32_t delay_us)
{
  volatile unsigned int num;
  volatile unsigned int t;

  for (num = 0; num < delay_us; num++)
  {
    t = 11;
    while (t != 0)
    {
      t--;
    }
  }
}
