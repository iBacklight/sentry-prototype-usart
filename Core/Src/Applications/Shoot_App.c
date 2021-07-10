/*
 * Shoot_App.c
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */
#include "Shoot_App.h"




void shoot_init(void);

void Shoot_Task_Func(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  shoot_init();
  double fric_wheel_speed=0;
  for(;;)
  {
	  //Shoot motor on half speed
	//__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,1500);
	//__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,1500);

	fric_wheel_set_speed(fric_wheel_speed);
	HAL_GPIO_TogglePin(LD_A_GPIO_Port,LD_A_Pin);
    osDelay(500);
    osDelay(1);
  }
  /* USER CODE END 5 */
}

void shoot_init(void){
	//Corresponds to pin H and pin F on the PWM board - need to change manually if we change the pins
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,MAX_PWM_ON_TIME);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,MAX_PWM_ON_TIME);
	osDelay(2000);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,MIN_PWM_ON_TIME);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,MIN_PWM_ON_TIME);
	osDelay(1750);

}

void fric_wheel_set_speed(double percent){
	//MAX pulse width: 2000
	//MIN Pulse Width: 1000

	double input=1000+percent/100*1000;

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,input);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,input);

}
