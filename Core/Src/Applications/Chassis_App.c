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


  int32_t direction = CLOCKWISE; // direction of motor
  double vel = 1000; //Velocity of motor
  uint32_t cycles_s=5; //Time period is 1 seconds per cycle, 5=5 cycles=5s, the timer is controlled by TIM13

  /* Infinite loop */
  //uint32_t t=0;
  //double distance = -1.0;
  //double i=0;
  //double vmax=16000;
  //double max_angle=4096;
  //double velocity_3508=500;

  for(;;)
  {

	 // Forever loop
	  motor_move_period(cycles_s, vel, direction);

	/* Ultra Sound Sensor test started here */
	// trigger the sensor to launch ultraSound wave
	//  distance = UltraSoundFindDistance();
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

/*
 * @ Func name: motor_move_period
 * @ Use: set up a period cycle and movement and apply to sentry chassis
 * @ Parameter:
 * 		cycles: cycle of a interrupt time unit, current unit : second
 * 		vel: The velocity of the each motor, note: NOT the rpm
 * 		direction:
 *
 * @ Return: Null
 * @ Author: Haoran, Adan
 */
void motor_move_period(uint32_t cycles, double vel, int32_t direction){
	//TIMEBASE = (APBxTIMCLK / (Prescaler + 1)) / (Period + 1) (Hertz)
	//currently set 1 Hz, if want 0.1s, set Prescaler of TIM13 to 839 (10 Hz)
	if(direction == CLOCKWISE){
		// Clockwise Direction
		// give time counter here
		if (period_counter >= cycles) {
			period_counter = 0;
			direction = COUNTER_CLOCKWISE;
		}
	}

	if(direction == COUNTER_CLOCKWISE){
		// Counter Clockwise Direction
		if (period_counter >= cycles){
			period_counter = 0;
			direction = CLOCKWISE;
		}
	}

	//Calculate velocity via direction * speed
	vel = direction*vel;

	//Send velocity to motor
	//and function should be written to control the RPM rather than just setting raw value
	Motor_set_raw_value(&motor_data[0], vel);
	Motor_set_raw_value(&motor_data[1], -vel);
	osDelay(1);
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
