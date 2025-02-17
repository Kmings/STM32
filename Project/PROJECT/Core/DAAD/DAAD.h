//include
#include "main.h"
#include "dac.h"

//define
#define Start_BIN1 HAL_DAC_Start(&hdac, DAC_CHANNEL_1)
#define Start_BIN2 HAL_DAC_Start(&hdac, DAC_CHANNEL_2)
#define High_Lev 4095
#define Low_Lev 0
#define DETECT_KEY3() HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)
#define DETECT_KEY4() HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin)

//function
void ToggleDir1(void);
void ToggleDir2(void);
