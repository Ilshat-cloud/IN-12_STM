/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

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
#define PWM_feedback_Pin GPIO_PIN_0
#define PWM_feedback_GPIO_Port GPIOA
#define encoder1_Pin GPIO_PIN_6
#define encoder1_GPIO_Port GPIOA
#define encoder2_Pin GPIO_PIN_7
#define encoder2_GPIO_Port GPIOA
#define OUT_A0_Pin GPIO_PIN_12
#define OUT_A0_GPIO_Port GPIOB
#define OUT_A1_Pin GPIO_PIN_13
#define OUT_A1_GPIO_Port GPIOB
#define OUT_A2_Pin GPIO_PIN_14
#define OUT_A2_GPIO_Port GPIOB
#define OUT_A3_Pin GPIO_PIN_15
#define OUT_A3_GPIO_Port GPIOB
#define Digit_1_Pin GPIO_PIN_8
#define Digit_1_GPIO_Port GPIOA
#define Digit_2_Pin GPIO_PIN_9
#define Digit_2_GPIO_Port GPIOA
#define Digit_3_Pin GPIO_PIN_10
#define Digit_3_GPIO_Port GPIOA
#define Digit_4_Pin GPIO_PIN_11
#define Digit_4_GPIO_Port GPIOA
#define Dot_Pin GPIO_PIN_12
#define Dot_GPIO_Port GPIOA
#define PWM_out_Pin GPIO_PIN_15
#define PWM_out_GPIO_Port GPIOA
#define Encoder_button_Pin GPIO_PIN_6
#define Encoder_button_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define voltage 2048
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
