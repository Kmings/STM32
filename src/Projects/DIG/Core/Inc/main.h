/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define KEY2_Pin GPIO_PIN_2
#define KEY2_GPIO_Port GPIOE
#define KEY2_EXTI_IRQn EXTI2_IRQn
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY1_EXTI_IRQn EXTI3_IRQn
#define DIG5_Pin GPIO_PIN_4
#define DIG5_GPIO_Port GPIOE
#define C_Pin GPIO_PIN_5
#define C_GPIO_Port GPIOE
#define DIG4_Pin GPIO_PIN_14
#define DIG4_GPIO_Port GPIOC
#define DIG2_Pin GPIO_PIN_15
#define DIG2_GPIO_Port GPIOC
#define DIG3_Pin GPIO_PIN_0
#define DIG3_GPIO_Port GPIOF
#define D_Pin GPIO_PIN_1
#define D_GPIO_Port GPIOF
#define DP_Pin GPIO_PIN_2
#define DP_GPIO_Port GPIOF
#define DIG6_Pin GPIO_PIN_2
#define DIG6_GPIO_Port GPIOG
#define A_Pin GPIO_PIN_3
#define A_GPIO_Port GPIOG
#define B_Pin GPIO_PIN_4
#define B_GPIO_Port GPIOG
#define E_Pin GPIO_PIN_5
#define E_GPIO_Port GPIOG
#define F_Pin GPIO_PIN_6
#define F_GPIO_Port GPIOG
#define G_Pin GPIO_PIN_7
#define G_GPIO_Port GPIOG
#define DIG1_Pin GPIO_PIN_8
#define DIG1_GPIO_Port GPIOG
#define KEY6_Pin GPIO_PIN_13
#define KEY6_GPIO_Port GPIOG
#define KEY6_EXTI_IRQn EXTI15_10_IRQn
#define KEY5_Pin GPIO_PIN_15
#define KEY5_GPIO_Port GPIOG
#define KEY5_EXTI_IRQn EXTI15_10_IRQn
#define KEY4_Pin GPIO_PIN_0
#define KEY4_GPIO_Port GPIOE
#define KEY4_EXTI_IRQn EXTI0_IRQn
#define KEY3_Pin GPIO_PIN_1
#define KEY3_GPIO_Port GPIOE
#define KEY3_EXTI_IRQn EXTI1_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
