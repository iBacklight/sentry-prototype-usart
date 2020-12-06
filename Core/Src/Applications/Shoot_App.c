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
  for(;;)
  {
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,1500);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,1500);
	HAL_GPIO_TogglePin(LD_A_GPIO_Port,LD_A_Pin);
    osDelay(500);
    osDelay(1);
  }
  /* USER CODE END 5 */
}

void shoot_init(void){
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,2000);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,2000);
	osDelay(2000);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,1000);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,1000);
	osDelay(1750);

}
