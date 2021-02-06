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
  double i=0;
  for(;;)
  {
	printf("\nWelcome to RM-EE\n");
	printf("Hello, the current time is %.2F",i);
	i+=0.1;
    osDelay(500);
    osDelay(1);
  }
  /* USER CODE END Chassis_Task_Func */
}
