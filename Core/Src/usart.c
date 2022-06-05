/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "Applications/gimbal_app.h"

/* USER CODE BEGIN 0 */
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&husart6, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

/* USER CODE END 0 */

UART_HandleTypeDef huart7;
// NOTE: husart6 is only for test works with elder dev board.
// For RM competition and latest A type board, use huart7
UART_HandleTypeDef husart6;
//extern char *pdata[PACKLEN+1];

/* UART7 init function */
void MX_UART7_Init(void)
{

  huart7.Instance = UART7;
  huart7.Init.BaudRate = 115200;
  huart7.Init.WordLength = UART_WORDLENGTH_8B;
  huart7.Init.StopBits = UART_STOPBITS_1;
  huart7.Init.Parity = UART_PARITY_NONE;
  huart7.Init.Mode = UART_MODE_TX_RX;
  huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart7.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart7) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USART6 init function */
void MX_USART6_Init(void)
{
  husart6.Instance = USART6;
  husart6.Init.BaudRate = 115200;
  husart6.Init.WordLength = UART_WORDLENGTH_8B;
  husart6.Init.StopBits = UART_STOPBITS_1;
  husart6.Init.Parity = UART_PARITY_NONE;
  husart6.Init.Mode = UART_MODE_TX_RX;
  husart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  husart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&husart6) != HAL_OK)
  {
    Error_Handler();
  }
  else{
	HAL_UART_Receive_IT(&husart6, pdata, (PACKLEN));

	  //HAL_UART_Receive_IT(&husart6, UART6_rxBuffer_temp, 12);
	  //printf("sucessfully enabled uart6 \r\n");
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==UART7)
  {
  /* USER CODE BEGIN UART7_MspInit 0 */

  /* USER CODE END UART7_MspInit 0 */
    /* UART7 clock enable */
    __HAL_RCC_UART7_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**UART7 GPIO Configuration
    PE8     ------> UART7_TX
    PE7     ------> UART7_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART7;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  }

  if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN UART7_MspInit 0 */

  /* USER CODE END UART7_MspInit 0 */
	/* UART7 clock enable */
	__HAL_RCC_USART6_CLK_ENABLE();

	__HAL_RCC_GPIOG_CLK_ENABLE();
	/**USART6 GPIO Configuration
	  PG14     ------> USART6_TX
	  PG9     ------> USART6_RX
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* USER CODE BEGIN UART7_MspInit 1 */
	//USART6 Interrput Init
	HAL_NVIC_SetPriority(USART6_IRQn,5,0);
	HAL_NVIC_EnableIRQ(USART6_IRQn);
	printf("initialized usart 6 via the uart function");
  /* USER CODE END UART7_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  if(uartHandle->Instance==UART7)
  {
  /* USER CODE BEGIN UART7_MspDeInit 0 */

  /* USER CODE END UART7_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART7_CLK_DISABLE();

    /**UART7 GPIO Configuration
    PE8     ------> UART7_TX
    PE7     ------> UART7_RX
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_8|GPIO_PIN_7);

  /* USER CODE BEGIN UART7_MspDeInit 1 */

  /* USER CODE END UART7_MspDeInit 1 */
  }

  if(uartHandle->Instance==USART6)
  {
    /* USER CODE BEGIN USART6_MspDeInit 0 */

    /* USER CODE END USART6_MspDeInit 0 */
      /* Peripheral clock disable */
      __HAL_RCC_USART6_CLK_DISABLE();

      /**USART6 GPIO Configuration
      PG14     ------> USART6_TX
      PG9     ------> USART6_RX
      */
      HAL_GPIO_DeInit(GPIOG, GPIO_PIN_14|GPIO_PIN_9);
      HAL_NVIC_DisableIRQ(USART6_IRQn);
    }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
