//Request
//设计单路pwm输出信号。输出占空比可设置。

//include
#include "PWMoutput.h"

//function

int Tv_Increase(int TargetVelocity)
{
	TargetVelocity+=5;
	return TargetVelocity;
}
int Tv_Decrease(int TargetVelocity)
{
	TargetVelocity-=5;
	return TargetVelocity;
}

