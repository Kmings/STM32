//include
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "oled.h"

//function
void OLED_Display_PWM_COMPARE(int);
void OLED_Display_Motor_RV(int ReTVelocity,int AveVelocity, int MaxVelocity, int MinVelocity);
void OLED_Display_Motor_PercentageError(int SetVal, int ReaVal);
void OLED_Display_Motor_SettlingTime(int SettilingTime);
void OLED_Display_Motor_RotationDirection(int Direction);
void OLED_Display_SystemDetail(int COMPARE, int ReTVelocity, int AveVelocity, int MaxVelocity, int MinVelocity, int SetVal, int ReaVal, int SettTime, int Direction);

	
//define
#define PosDir 1
#define NegDir 2
