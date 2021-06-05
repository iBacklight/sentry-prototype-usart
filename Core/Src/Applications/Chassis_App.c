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
  //double i=0;
  double velocity=-3000;
  double velocity_3508=500;
  for(;;)
  {
	//printf("\nWelcome to RM-EE\n");

	Motor temp_motor_buffer;
	Motor temp_motor_buffer_3508;

	get_Motor_buffer(&motor_data[4],&temp_motor_buffer);
	get_Motor_buffer(&motor_data[0],&temp_motor_buffer_3508);

	temp_motor_buffer.tx_data=velocity;
	temp_motor_buffer_3508.tx_data=velocity_3508;

	set_Motor_buffer(&temp_motor_buffer,&motor_data[4]);
	set_Motor_buffer(&temp_motor_buffer_3508,&motor_data[0]);

	//printf("Hello, the current time is %.2F",i);
	//i+=0.1;
    //osDelay(500);
    osDelay(1);
  }
  /* USER CODE END Chassis_Task_Func */
}
