#include "keyled.h"

KEYS ScanPressedKey(uint32_t timeout)
{
		uint32_t tickstart = HAL_GetTick();
		const uint32_t btnDelay = 20;
		while(1)
		{
#ifdef KEY0_Pin
			if(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET)
			{
					HAL_Delay(btnDelay);
					if(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET)
							return KEY_0;
			}
#endif
#ifdef KEY1_Pin
			if(HAL_GPIO_ReadPin(KEY1_GPIO_Port ,KEY1_Pin) == GPIO_PIN_RESET)
			{
					HAL_Delay(btnDelay);
					if(HAL_GPIO_ReadPin(KEY1_GPIO_Port ,KEY1_Pin) == GPIO_PIN_RESET)
							return KEY_1;
			}
#endif
#ifdef KEY2_Pin
			if(HAL_GPIO_ReadPin(KEY2_GPIO_Port ,KEY2_Pin) == GPIO_PIN_RESET)
			{
					HAL_Delay(btnDelay);
					if(HAL_GPIO_ReadPin(KEY2_GPIO_Port ,KEY2_Pin) == GPIO_PIN_RESET)
							return KEY_2;
			}
#endif
			if(timeout != KEY_WAIT_ALWAYS){
					if((HAL_GetTick() - tickstart) > timeout)
							break;
			}
		}
		return KEY_NONE;
}