/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define ECHO1_Pin GPIO_PIN_0
#define ECHO1_GPIO_Port GPIOA
#define ECHO2_Pin GPIO_PIN_1
#define ECHO2_GPIO_Port GPIOA
#define motor1F_Pin GPIO_PIN_6
#define motor1F_GPIO_Port GPIOA
#define motor1B_Pin GPIO_PIN_7
#define motor1B_GPIO_Port GPIOA
#define motor2F_Pin GPIO_PIN_0
#define motor2F_GPIO_Port GPIOB
#define motor2B_Pin GPIO_PIN_1
#define motor2B_GPIO_Port GPIOB
#define ECHO3_Pin GPIO_PIN_10
#define ECHO3_GPIO_Port GPIOB
#define TRIG_Pin GPIO_PIN_11
#define TRIG_GPIO_Port GPIOA
#define motor3F_Pin GPIO_PIN_6
#define motor3F_GPIO_Port GPIOB
#define motor3B_Pin GPIO_PIN_7
#define motor3B_GPIO_Port GPIOB
#define motor4F_Pin GPIO_PIN_8
#define motor4F_GPIO_Port GPIOB
#define motor4B_Pin GPIO_PIN_9
#define motor4B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
