#include "Headfile.h"

void LED_Init(void)
{
	GPIOx_Init(PB,PP,6);
	GPIOx_Init(PB,PP,7);
	GPIOx_Init(PB,PP,8);
	GPIOx_Init(PB,PP,9);
	GPIOx_Init(PC,PP,13);
	PB_H(6);PB_H(7);PB_H(8);PB_H(9);PC_H(13);
}
void LED_ON(char LEDx)
{
	if(LEDx == 1){ PB_L(6); }
	if(LEDx == 2){ PB_L(7); }
	if(LEDx == 3){ PB_L(8); }
	if(LEDx == 4){ PB_L(9); }
	if(LEDx == 5){ PC_L(13); }
	
}

void LED_OFF(char LEDx)
{
	if(LEDx == 1){ PB_H(6); }
	if(LEDx == 2){ PB_H(7); }
	if(LEDx == 3){ PB_H(8); }
	if(LEDx == 4){ PB_H(9); }
	if(LEDx == 5){ PC_H(13); }
}
