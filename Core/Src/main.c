/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "Led.h"
#include "uart.h"

IWDG_HandleTypeDef hiwdg;
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;
WWDG_HandleTypeDef hwwdg;
void SystemClock_Config(void);
//void MX_GPIO_Init(void);
//static void MX_DMA_Init(void);
//static void MX_IWDG_Init(void);
//static void MX_TIM2_Init(void);
void MX_USART1_UART_Init(void);
//static void MX_WWDG_Init(void);
int main(void)
{
    HAL_Init();
    SystemClock_Config();
/*  MX_GPIO_Init();
  MX_DMA_Init();
  MX_IWDG_Init();
  MX_TIM2_Init();
  MX_WWDG_Init();*/
   Led_init();
   MX_USART1_UART_Init();
   while(1)
   {
       Context_in_while_for_uart1();
   }
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
/*static void MX_IWDG_Init(void)
{

   USER CODE BEGIN IWDG_Init 0

   USER CODE END IWDG_Init 0

   USER CODE BEGIN IWDG_Init 1

   USER CODE END IWDG_Init 1
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_4;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
   USER CODE BEGIN IWDG_Init 2

   USER CODE END IWDG_Init 2

}*/
/*

*
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
*/

//static void MX_TIM2_Init(void)
//{
//
//   USER CODE BEGIN TIM2_Init 0
//
//   USER CODE END TIM2_Init 0
//
//  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
//  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
//  TIM_MasterConfigTypeDef sMasterConfig = {0};
//
//   USER CODE BEGIN TIM2_Init 1
//
//   USER CODE END TIM2_Init 1
//  htim2.Instance = TIM2;
//  htim2.Init.Prescaler = 0;
//  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim2.Init.Period = 65535;
//  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_ETRMODE2;
//  sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_NONINVERTED;
//  sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
//  sClockSourceConfig.ClockFilter = 0;
//  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_TRIGGER;
//  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
//  if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//   USER CODE BEGIN TIM2_Init 2
//
//   USER CODE END TIM2_Init 2
//
//}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None*/
/*static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

//}

*//**
  * @brief WWDG Initialization Function
  * @param None
  * @retval None*/
/*static void MX_WWDG_Init(void)
{


  hwwdg.Instance = WWDG;
  hwwdg.Init.Prescaler = WWDG_PRESCALER_1;
  hwwdg.Init.Window = 64;
  hwwdg.Init.Counter = 64;
  hwwdg.Init.EWIMode = WWDG_EWI_DISABLE;
  if (HAL_WWDG_Init(&hwwdg) != HAL_OK)
  {
    Error_Handler();
  }

}*/
/*static void MX_DMA_Init(void)
{

 DMA controller clock enable

  __HAL_RCC_DMA1_CLK_ENABLE();

 DMA interrupt init

 DMA1_Channel4_IRQn interrupt configuration

  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
 DMA1_Channel5_IRQn interrupt configuration

  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}*/

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None*//*
void MX_GPIO_Init(void)
{

   GPIO Ports Clock Enable
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}
/* @brief  This function is executed in case of error occurrence.
  * @retval None
  * */
void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
