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
	HAL_GPIO_TogglePin(LD_B_GPIO_Port,LD_B_Pin);
  /* USER CODE BEGIN Chassis_Task_Func */
  /* Infinite loop */
  for(;;)
  {

    osDelay(500);
    osDelay(1);
  }
  /* USER CODE END Chassis_Task_Func */
}
