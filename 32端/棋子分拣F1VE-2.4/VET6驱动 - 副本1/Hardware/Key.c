#include "Headfile.h"

uint8_t Key_Num;

void Key_Init(void)
{
	GPIOx_Init(PB,IPU,12);
	GPIOx_Init(PB,IPU,13);
	GPIOx_Init(PB,IPU,14);
	GPIOx_Init(PB,IPU,15);
}

uint8_t Key_GetNum(void)
{
	uint8_t Temp;
	if (Key_Num)
	{
		Temp = Key_Num;
		Key_Num = 0;
		return Temp;
	}
	return 0;
}

uint8_t Key_GetState(void)
{
	if (PB_R(12) == 0){ return 1; }
	if (PB_R(13) == 0){ return 2; }
	if (PB_R(14) == 0){ return 3; }
	if (PB_R(15) == 0){ return 4; }
	return 0;
}

void Key_Tick(void)
{
	static uint8_t Count;
	static uint8_t CurrState, PrevState;
	
	Count ++;
	if (Count >= 20)
	{
		Count = 0;
		
		PrevState = CurrState;
		CurrState = Key_GetState();
		
		if (CurrState == 0 && PrevState != 0)
		{
			Key_Num = PrevState;
		}
	}
}
