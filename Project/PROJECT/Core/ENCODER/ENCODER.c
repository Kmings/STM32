//include
#include "ENCODER.h"

//function
int Find_Max(int *v)
{
	int i, temp=v[0];
	for(i=1; i<5; i++)
	{
		if(temp<v[i]) temp=v[i];
	}
	return temp;
}
int Find_Min(int *v)
{
	int i, temp=v[0];
	for(i=1; i<5; i++)
	{
		if(temp>v[i]) temp=v[i];
	}
	return temp;
}
int Get_AveV(int *v)
{
	int Ave=(v[0]+v[1]+v[2]+v[3]+v[4])/5.0;
	return Ave;
}

