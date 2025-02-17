//include
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "oled.h"

//function
void DETECT_KEY1(void);
void DETECT_KEY2(void);
int Tv_Increase(int TargetVelocity);
int Tv_Decrease(int TargetVelocity);


//define
#define DETECT_KEY1() HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)
#define DETECT_KEY2() HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)

//
