#include "main.h"

typedef enum{
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_NONE,
}KEYS;

#define KEY_WAIT_ALWAYS		0

KEYS ScanPressedKey(uint32_t timeout);

#ifdef LED1_PIN
		#define LED1_Toggle()		HAL_GPIO_Toggle(GPIOF, GPIO_PIN_7)
		#define LED1_ON()				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET)
		#define LED1_OFF()			HAL_GPIO_WritePin(GPIOF, GPIG_PIN_7, GPIO_PIN_RESET)
#endif

#ifdef LED2_PIN
		#define LED2_Toggle()		HAL_GPIO_Toggle(GPIOF, GPIO_PIN_8)
		#define LED2_ON()				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET)
		#define LED2_OFF()			HAL_GPIO_WritePin(GPIOF, GPIG_PIN_8, GPIO_PIN_RESET)
#endif

#ifdef Buzzer_Pin
		#define Buzzer_Toggle()	HAL_GPIO_Toggle(Buzzer_GPIO_Port, Buzzer_Pin)
		#define Buzzer_ON()			HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET)
		#define Buzzer_OFF()		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET)
#endif