/* Includes ------------------------------------------------------------------*/
#include "menu.h"
#include "main.h"

int menu1(void)
{
	while(1)
	{
		uint8_t cmenu[]="MENU";
		OLED_ShowString(24,1,cmenu,8,1);
		uint8_t cpidcontrol[]=" PIDControl             ";
		OLED_ShowString(0,9,cpidcontrol,8,1);
		uint8_t cpiddata[]=" PIDData                    ";
		OLED_ShowString(0,17,cpiddata,8,0);
		OLED_Refresh();
	}
}
