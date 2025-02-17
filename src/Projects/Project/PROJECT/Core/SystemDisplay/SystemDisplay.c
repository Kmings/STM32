//Request
//系统显示功能。oled同时显示当前电机转速、最大转速、最小转速、平均转速、误差百分比和当前PWM波的占空比、稳定时间等信息。

//include
#include "SystemDisplay.h"
#include <math.h>

//function
void OLED_Display_PWM_COMPARE(int COMPARE)
{
	uint8_t PWM_COMPARE[] = "PWMComp";
	OLED_ShowString(1, 10, PWM_COMPARE, 8, 1);
	OLED_ShowNum(80, 10, COMPARE, 3, 8, 1);
	OLED_ShowChar(100, 10, '%', 8, 1);
}
void OLED_Display_Motor_RV(int ReTVelocity, int AveVelocity, int MaxVelocity, int MinVelocity)
{
	//RealTimeRotationVelocity
	uint8_t Motor_ReTRV[] = "ReT";
	uint8_t rps[] = "rpm";
	OLED_ShowString(1, 19, Motor_ReTRV, 8, 1);
	OLED_ShowNum(20, 19, ReTVelocity, 3, 8, 1);
	OLED_ShowString(40, 19, rps, 8, 1);
	//AverageRotationVelocity
	uint8_t Motor_AveRV[] = "Ave";
	OLED_ShowString(61, 19, Motor_AveRV, 8, 1);
	OLED_ShowNum(80, 19, AveVelocity, 3, 8, 1);
	OLED_ShowString(100, 19, rps, 8, 1);
	//MaxRotationVelocity
	uint8_t Motor_MaxRV[] = "Max";
	OLED_ShowString(1, 28, Motor_MaxRV, 8, 1);
	OLED_ShowNum(20, 28, MaxVelocity, 3, 8, 1);
	OLED_ShowString(40, 28, rps, 8, 1);
	//MinRotationVelocity
	uint8_t Motor_MinRV[] = "Min";
	OLED_ShowString(61, 28, Motor_MinRV, 8, 1);
	OLED_ShowNum(80, 28, MinVelocity, 3, 8, 1);
	OLED_ShowString(100, 28, rps, 8, 1);
}
void OLED_Display_Motor_RotationDirection(int Direction)
{
	uint8_t Motor_RotationDirection[] = "Motor_RoDir";
	OLED_ShowString(1, 37, Motor_RotationDirection, 8, 1);
	if(Direction==PosDir)
	{
		uint8_t RotationDirection[] = "PosDir";
		OLED_ShowString(80, 37, RotationDirection, 8, 1);
	}
	else if(Direction==NegDir)
	{
		uint8_t RotationDirection[] = "NegDir";
		OLED_ShowString(80, 37, RotationDirection, 8, 1);
	}
	else
	{
		uint8_t RotationDirection[] = "Undete";
		OLED_ShowString(80, 37, RotationDirection, 8, 1);
	}
}
void OLED_Display_Motor_PercentageError(int SetVal, int ReaVal)
{
	uint8_t PercentageError = abs((SetVal-ReaVal)*100/SetVal);
	uint8_t Motor_PercentageError[] = "MotPerEr";
	OLED_ShowString(1, 46, Motor_PercentageError, 8, 1);
	OLED_ShowNum(80, 46, PercentageError, 3, 8, 1);
	OLED_ShowChar(100, 46, '%', 8, 1);
}
void OLED_Display_Motor_SettlingTime(int SettTime)
{
	uint8_t SettilingTime[] = "SettTime";
	uint8_t ms[] = "ms";
	OLED_ShowString(1, 55, SettilingTime, 8, 1);
	OLED_ShowNum(56, 55, SettTime, 7, 8, 1);
	OLED_ShowString(100, 55, ms, 8, 1);
}

void OLED_Display_SystemDetail(int COMPARE, int ReTVelocity, int AveVelocity, int MaxVelocity, int MinVelocity, int SetVal, int ReaVal, int SettTime, int Direction)
{
	uint8_t SystemDetail[] = "SystemData";
	OLED_ShowString(30, 1, SystemDetail, 8, 1);
	
	OLED_Display_PWM_COMPARE(COMPARE);
	OLED_Display_Motor_RV(ReTVelocity, AveVelocity, MaxVelocity, MinVelocity);
	OLED_Display_Motor_PercentageError(SetVal, ReaVal);
	OLED_Display_Motor_SettlingTime(SettTime);
	OLED_Display_Motor_RotationDirection(Direction);
}

