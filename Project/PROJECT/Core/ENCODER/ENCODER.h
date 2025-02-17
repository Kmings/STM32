//include
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"


//define
#define __TIMER_H	

//function
//void Encoder_Init_TIM4(u16 arr,u16 psc);
int Find_Max(int *v);
int Find_Min(int *v);
int Get_AveV(int *v);
