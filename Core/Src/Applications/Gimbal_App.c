/*
 * Gimbal_App.c
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */

#include "Gimbal_App.h"


void Gimbal_Task_Function(void const * argument)
{

  /* USER CODE BEGIN Gimbal_Task_Function */
  /* Infinite loop */
	buzzer_play_chromatic(100);
	buzzer_play_o_canada(100);

  for(;;)
  {
	  HAL_GPIO_TogglePin(LD_C_GPIO_Port, LD_C_Pin);
	  osDelay(1000);
	  osDelay(1);
  }
  /* USER CODE END Gimbal_Task_Function */
}

