/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "PWMoutput.h"
#include "oled.h"
#include "SystemDisplay.h"
#include "ENCODER.h"
#include "DAAD.h"
#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "stm32f4xx_hal.h"
#include "DIG.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
float PWM_COMPARE=0;
int v[5]={0};
int ReTVelocity=0, AveVelocity=0, *MaxVelocity=v, *MinVelocity=v;
int newCapPul=0, lastCapPul=0, newCapPul1=0, newCapPul2=0;
int SetVal=0;
int ReaVal=0;
int PercentageError=0;
int SettTime=0;
int Direcion=0;
int Position=0, Target=0;
// 定义PID参数
typedef struct
{
	float Kp;
	float Ki;
	float Kd;
} PID_Controller;
PID_Controller pid_params = {0.1, 0.1, 0.05};
//Kp=0.06,Ki=0.13,Kd=0.05 200 1209ms√
//Kp=0.07,Ki=0.14618,Kd=0.05 100
//Kp=0.07,Ki=0.149,Kd=0.05 100 1056ms√
//Kp=0.05,Ki=0.16,Kd=0.05 100

// 定义全局接收缓冲区
char rx_buffer[32];
int rx_index = 0;  // 接收缓冲区的索引
// 定义响应字符串
const uint8_t start[] = "PID参数设置启动\r\n";
const uint8_t success_response[] = "PID参数设置成功\r\n";
const uint8_t failure_response[] = "PID参数设置失败: 格式错误\r\n";
int MaxV=0, MinV=0;
int i=0;
int flag = 0;
static float Bias=0, PWM=0, Integral_Bias=0, Last_Bias=0;
int f=0;
int cnt = 0;
int times = 0;

uint32_t start_time;
uint32_t end_time;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int	TargetVelocity = 300;
int dt=1;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
float PWM_Position_PID(int Position, int Target)
	{
		Bias = Target-Position;
		Integral_Bias += Bias*dt;
		PWM = pid_params.Kp*Bias+pid_params.Ki*Integral_Bias+pid_params.Kd*(Bias-Last_Bias)/dt;
		Last_Bias = Bias;
		if(PWM_COMPARE>=100) PWM=100;
		return PWM;
	}
float outer_pid_controller(float setpoint, float input, float kp, float ki, float kd, float dt) {
    static float integral = 0;
    static float prev_error = 0;
    float error = setpoint - input;

    // 计算积分项
    integral += error * dt;

    // 计算微分项
    float derivative = (error - prev_error) / dt;

    // 计算输出
    float output = kp * error + ki * integral + kd * derivative;

    // 更新上一个误差
    prev_error = error;

    return output;
}

float inner_pid_controller(float setpoint, float input, float kp, float ki, float kd, float dt) {
    static float integral = 0;
    static float prev_error = 0;
    float error = setpoint - input;

    // 计算积分项
    integral += error * dt;

    // 计算微分项
    float derivative = (error - prev_error) / dt;

    // 计算输出
    float output = kp * error + ki * integral + kd * derivative;

    // 更新上一个误差
    prev_error = error;

    return output;
}

float double_pid_controller(float setpoint, float input, float outer_kp, float outer_ki, float outer_kd, float inner_kp, float inner_ki, float inner_kd, float dt) {
    // 计算外环控制器输出
    float outer_output = outer_pid_controller(setpoint, input, outer_kp, outer_ki, outer_kd, dt);

    // 计算内环控制器输出
    float inner_output = inner_pid_controller(outer_output, input, inner_kp, inner_ki, inner_kd, dt);

    return inner_output;
}

// 手动构建字符串并发送实时速度和目标速度
void Send_Speed_Data(UART_HandleTypeDef *huart, float current_speed, float target_speed) {
    char buffer[64];
    int len = sprintf(buffer, "%f,%f\n", current_speed, target_speed);
    HAL_UART_Transmit(huart, (uint8_t *)buffer, len, 1000);
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void PID_Start(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	//外设控制
void process(const char*buffer)
{
	if(sscanf(buffer, "Kp=%f,Ki=%f,Kd=%f", &pid_params.Kp, &pid_params.Ki, &pid_params.Kd)==3)
	{
		HAL_UART_Transmit(&huart1, (uint8_t *)success_response, sizeof(success_response) - 1, 1000);
	}
	else HAL_UART_Transmit(&huart1, (uint8_t *)failure_response, sizeof(success_response) - 1, 1000);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart1) {
      rx_buffer[rx_index++] = (char)huart1.Instance->DR;
			if(rx_buffer[rx_index-1]=='\n')
			{
				rx_buffer[rx_index-1]='\0';
				process(rx_buffer);
				rx_index = 0;
			}
    }
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&huart1.Instance->DR, 1);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	//定时器3的通道1和通道2的Encoder Mode开启使能函数
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_1 | TIM_CHANNEL_2);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM14_Init();
  MX_ADC1_Init();
  MX_DAC_Init();
  MX_SPI2_Init();
  MX_TIM5_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
	//OLED
	OLED_Init();
	
	//PWMoutput
	HAL_TIM_Base_Start(&htim14);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, PWM_COMPARE);
	
	//电机测速显示功能
	HAL_TIM_Base_Start(&htim5);
	
	//DAC给予电平
	Start_BIN1;
	Start_BIN2;
	ToggleDir1();
	
	
	//外设修改PID参数
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		/*
		int PWM_COMPARE=50;
		int AveVelocity;
		int MaxVelocity;
		int MinVelocity;
		int SetVal;
		int ReaVal;
		int SettTime;
		*/
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&huart1.Instance->DR, 1);
		//PWMoutput
		if(DETECT_KEY1()==RESET)
		{
			HAL_Delay(200);
			if(DETECT_KEY1()==RESET)
					TargetVelocity = Tv_Increase(TargetVelocity);
		}
		if(DETECT_KEY2()==RESET)
		{
			HAL_Delay(200);
			if(DETECT_KEY1()==RESET)
					TargetVelocity = Tv_Decrease(TargetVelocity);
		}
		
		//开启/关闭pid控制
		//开
		if(DETECT_KEY6()==RESET)
		{
			HAL_Delay(200);
			if(DETECT_KEY6()==RESET)
			{
				PWM_COMPARE = 0;
				flag = 1;
				start_time = HAL_GetTick();
				times++;
			}
		}
		//关
		if(DETECT_KEY5()==RESET)
		{
			HAL_Delay(200);
			if(DETECT_KEY5()==RESET)
			{
				PWM = PWM_COMPARE = 0;
				flag = 0;
				Last_Bias = 0;
				Integral_Bias = 0;
				Bias = 0;
				Position=0;
				f = 0;
				
				__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, PWM_COMPARE);
			}
		}
		
		
		//测速功能
		newCapPul1=(short)__HAL_TIM_GET_COUNTER(&htim5);
		HAL_Delay(100);
		newCapPul2=(short)__HAL_TIM_GET_COUNTER(&htim5);
		newCapPul = abs(newCapPul1-newCapPul2);
		__HAL_TIM_GET_COUNTER(&htim5)=0; 
		newCapPul=newCapPul*0.8+lastCapPul*0.2;
			
		lastCapPul=newCapPul;
		ReTVelocity=newCapPul*10*60/(13*4*30);//检测周期100ms,使用四倍频
		//
		v[i]=ReTVelocity;
		i++;
		if(i==5) i=0;
		AveVelocity = Get_AveV(v);
		//
		MaxV = Find_Max(v);
		MinV = Find_Min(v);
		
		
		//转向控制&检测
		if(DETECT_KEY3()==RESET)
		{
			HAL_Delay(200);
			if(DETECT_KEY3()==RESET)
				ToggleDir1();
		}
		else if(DETECT_KEY4()==RESET)
		{
			HAL_Delay(200);
			if(DETECT_KEY4()==RESET)
				ToggleDir2();
		}
		Direcion = 0;
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim5))
			Direcion = NegDir;
		else if(!__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim5))
			Direcion = PosDir;
		
		//pid控制
		//处理上位机数据包
		Position = ReTVelocity;
		ReaVal = Position;
		Target = TargetVelocity;//TargetVelocity 300
		SetVal = Target;
		if(flag)
		{
			PWM_COMPARE = PWM_Position_PID(Position, Target);
			__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, PWM_COMPARE);
			//上位机曲线绘制
			Send_Speed_Data(&huart1, ReTVelocity, TargetVelocity);
		}
		
		
		
		//时间检测
		PercentageError = (SetVal-ReaVal)*100/SetVal;
		if(PercentageError==0 && f==0)
		{
			cnt++;
			if(cnt==5){
				HAL_Delay(1);
				end_time = HAL_GetTick();
				SettTime = end_time - start_time;//ms
				cnt=0;
				f=1;
			}
		}
		
		//系统显示功能
		OLED_Display_SystemDetail(PWM_COMPARE, ReTVelocity, AveVelocity, MaxV, MinV, SetVal, ReaVal, SettTime, Direcion);
		
		//OLED0
		OLED_Refresh();
		
		//DIG
		Display_0();
		switch(times)
		{
			case 1:
				Display_1();
				break;
			case 2:
				Display_2();
				break;
			case 3:
				Display_3();
				break;
			case 4:
				Display_4();
				break;
			case 5:
				Display_5();
				break;
			case 6:
				Display_6();
				break;
			case 7:
				Display_7();
				break;
			case 8:
				Display_8();
				break;
		}
		
		HAL_Delay(dt);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//电机测速功能



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
