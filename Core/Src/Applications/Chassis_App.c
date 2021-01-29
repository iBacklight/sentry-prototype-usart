/* USER CODE BEGIN Header_Chassis_Task_Func */
#include "Chassis_App.h"


/**
* @brief Function implementing the Chassis_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Chassis_Task_Func */
void Chassis_Task_Func(void const * argument)
{

  /* USER CODE BEGIN Chassis_Task_Func */
	//buzzer_play_mario(200);
  /* Infinite loop */
  for(;;)
  {
	printf("\nWelcome to RM-EE\n");
    osDelay(500);
    osDelay(1);
  }
  /* USER CODE END Chassis_Task_Func */
}
