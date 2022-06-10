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
//  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,1050);
//  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,1050);
//  osDelay(3000);
//  buzzer_play_o_canada(300);
//	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);

  //__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,1050);
  //__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,1050);
  double fric_wheel_speed_percent=5;
  double mag_load_speed_percent=10;
  int16_t input=500;
  //buzzer_play_o_canada(300);


  for(;;)
  {

//		input++;
//
//		if(input==1000){
//			input=500;
//		}
	  cmd_execute_shoot(mag_load_speed_percent,fric_wheel_speed_percent);
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
	osDelay(100);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	//osDelay(2000);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,MAX_PWM_ON_TIME);
	osDelay(100);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,MAX_PWM_ON_TIME);

	osDelay(2000);

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,MIN_PWM_ON_TIME);
	osDelay(100);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,MIN_PWM_ON_TIME);
	osDelay(6000);

//	HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);



}

void fric_wheel_set_speed(double percent){
	//MAX pulse width: 2000
	//MIN Pulse Width: 1000

	double input=MIN_PWM_ON_TIME+percent/100*(MAX_PWM_ON_TIME-MIN_PWM_ON_TIME);

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,input);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,input);
}

//Shoot function, will spin magazine as well as friction wheels, the inputs represents speed in percent - 100 means 100% speed, 50 means 50% speed
//We'll tune speed at the end to optimize for performance
void cmd_execute_shoot(double magazine_speed, double fric_speed){

	double raw_input=magazine_speed/100*MAG_MOTOR_MAX_SPEED;

	Motor_set_raw_value(&motor_data[3],raw_input);
	//osdelay(1000);
	fric_wheel_set_speed(fric_speed);

}
