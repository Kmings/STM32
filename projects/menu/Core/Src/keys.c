/* Includes ------------------------------------------------------------------*/
#include "keys.h"

//functions
int detect_key1(void)
{
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)==RESET)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)==RESET) return 1;
	}
	return 0;
}
int detect_key2(void)
{
	if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)==RESET)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)==RESET) return 1;
	}
	return 0;
}
int detect_key3(void)
{
	if(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)==RESET)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)==RESET) return 1;
	}
	return 0;
}
int detect_key4(void)
{
	if(HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin)==RESET)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin)==RESET) return 1;
	}
	return 0;
}
int detect_key5(void)
{
	if(HAL_GPIO_ReadPin(KEY5_GPIO_Port, KEY5_Pin)==RESET)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY5_GPIO_Port, KEY5_Pin)==RESET) return 1;
	}
	return 0;
}
int detect_key6(void)
{
	if(HAL_GPIO_ReadPin(KEY6_GPIO_Port, KEY6_Pin)==RESET)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY6_GPIO_Port, KEY6_Pin)==RESET) return 1;
	}
	return 0;
}

int keys_detect(void)
{
	if(detect_key1()) return 1;
	if(detect_key2()) return 2;
	if(detect_key3()) return 3;
	if(detect_key4()) return 4;
	if(detect_key5()) return 5;
	if(detect_key6()) return 6;
	return 0;
}
