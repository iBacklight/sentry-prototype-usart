/*
 * Shoot_App.c
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */
#include "Shoot_App.h"




//Internal Functions
void shoot_init(void);
void cmd_execute_shoot(double magazine_speed, double fric_speed);

void Shoot_Task_Func(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  shoot_init();
  double fric_wheel_speed_percent=50;
  double mag_load_speed_percent=10;
  for(;;)
  {
	  if(comm_pack.target_num ==1){
		  buzzer_play_c1(100);
		  cmd_execute_shoot(mag_load_speed_percent,fric_wheel_speed_percent);
	  }

	  //Shoot motor on half speed
	//__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,1700);
	//__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,1500);

	//fric_wheel_set_speed(fric_wheel_speed);
	//HAL_GPIO_TogglePin(LD_A_GPIO_Port,LD_A_Pin);
    //osDelay(500);


	  //Motor_set_raw_value(&motor_data[0],1000);
	  //Motor_set_raw_value(&motor_data[3],1000);

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
	osDelay(1500);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,MIN_PWM_ON_TIME);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,MIN_PWM_ON_TIME);
	osDelay(1750);

}

void fric_wheel_set_speed(double percent){
	//MAX pulse width: 2000
	//MIN Pulse Width: 1000

	double input=MIN_PWM_ON_TIME+percent/100*(MAX_PWM_ON_TIME-MIN_PWM_ON_TIME);

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,input);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,input);
}

//Shoot function, will spin magazine as well as friction wheels, the inputs represents speed in percent - 100 means 100% speed, 50 means 50% speed
//We'll tune speed at the end to optimize for performance
void cmd_execute_shoot(double magazine_speed, double fric_speed){

	double raw_input=magazine_speed/100*MAG_MOTOR_MAX_SPEED;

	Motor_set_raw_value(&motor_data[3],raw_input);
	//osdelay(1000);
	//fric_wheel_set_speed(fric_speed);

}
