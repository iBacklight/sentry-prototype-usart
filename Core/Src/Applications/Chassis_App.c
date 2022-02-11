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

  int32_t speed=1000; // speed applied to motor

  int direction = CLOCKWISE; // direction of motor
  int32_t vel; //Velocity of motor

  //uint32_t t=0;
  //double distance = -1.0;

  //Time period is 1 seconds per cycle, 10=10 cycles=10s, the timer is controlled by TIM13
  uint32_t cycles_s=10;

  /* Infinite loop */

  //double i=0;
  //double vmax=16000;
  //double max_angle=4096;
  //double velocity_3508=500;

  for(;;)
  {


	//motor_move_time(cycles_2s, vel,direction);


	  //Motor movement function call, check for direction, then check for timer interrupt cycle
		if(direction == CLOCKWISE){
			// Clockwise Direction
			// give time counter here
			if (period_counter >= cycles_s) {
				period_counter = 0;
				direction = COUNTER_CLOCKWISE;
			}
		}

		if(direction == COUNTER_CLOCKWISE){
			// Counter Clockwise Direction
			if (period_counter >= cycles_s){
				period_counter = 0;
				direction = CLOCKWISE;
			}
		}

		//Calculate velocity via direction * speed
		vel=direction*speed;

		//Send velocity to motor
		//Currently only sets value to one motor, need to set to all 3, and function should be written to control the RPM rather than just setting raw value
		Motor_set_raw_value(&motor_data[0], vel);
		osDelay(1);


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

//Ultrasound sensor functions, currently not in use
double UltraSoundFindDistance(void){
	/*
	 *  Currently not used
	 */

	// Timer 13 set to pre-scalar as 100us per cnt
	HAL_GPIO_TogglePin(LED_Red_GPIO_Port,LED_Red_Pin);

	double dis = -1.0;
	uint32_t val = 0;
	GPIO_PinState echo;

	HAL_GPIO_WritePin(UltraSound_Trig_GPIO_Port, UltraSound_Trig_Pin, GPIO_PIN_SET);
	delay_us(10);
	HAL_GPIO_WritePin(UltraSound_Trig_GPIO_Port, UltraSound_Trig_Pin, GPIO_PIN_RESET);
	//TIM13->CNT = 0;

	// Wait for response
	while((echo = HAL_GPIO_ReadPin(UltraSound_Echo_GPIO_Port, UltraSound_Echo_Pin)) == GPIO_PIN_RESET);
	//if( HAL_TIM_Base_Start(&htim13) == HAL_OK){
		val = __HAL_TIM_GET_COUNTER(&htim13); //ideally equal to 0 here
		//Getting response
		while( (echo = HAL_GPIO_ReadPin(UltraSound_Echo_GPIO_Port, UltraSound_Echo_Pin)) == GPIO_PIN_SET);
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
/* USER CODE END Chassis_Task_Func */
