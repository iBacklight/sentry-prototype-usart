/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/**
  ******************************************************************************
  * Please write all peripherals initialized manually here
  * ENSURE ALL MANUAL INITIALIZATION CODES ARE BETWEEN USER CODE BEGIN AND USER CODE END
  ******************************************************************************
  * Peripheral name:
  * Peripheral GPIO Pins:
  * Files modified:
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define UltraSound_Trig_Pin GPIO_PIN_5
#define UltraSound_Trig_GPIO_Port GPIOE
#define LD_A_Pin GPIO_PIN_8
#define LD_A_GPIO_Port GPIOG
#define LD_B_Pin GPIO_PIN_7
#define LD_B_GPIO_Port GPIOG
#define LD_C_Pin GPIO_PIN_6
#define LD_C_GPIO_Port GPIOG
#define LD_D_Pin GPIO_PIN_5
#define LD_D_GPIO_Port GPIOG
#define LD_E_Pin GPIO_PIN_4
#define LD_E_GPIO_Port GPIOG
#define LD_F_Pin GPIO_PIN_3
#define LD_F_GPIO_Port GPIOG
#define UltraSound_Echo_Pin GPIO_PIN_10
#define UltraSound_Echo_GPIO_Port GPIOF
#define LD_G_Pin GPIO_PIN_2
#define LD_G_GPIO_Port GPIOG
#define Button_Pin GPIO_PIN_2
#define Button_GPIO_Port GPIOB
#define Button_EXTI_IRQn EXTI2_IRQn
#define LD_H_Pin GPIO_PIN_1
#define LD_H_GPIO_Port GPIOG
#define LED_Red_Pin GPIO_PIN_11
#define LED_Red_GPIO_Port GPIOE
#define LED_Green_Pin GPIO_PIN_14
#define LED_Green_GPIO_Port GPIOF
/* USER CODE BEGIN Private defines */

TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim12;

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
