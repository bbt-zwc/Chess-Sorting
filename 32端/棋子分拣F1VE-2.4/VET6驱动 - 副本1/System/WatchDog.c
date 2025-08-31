#include "Headfile.h"

void WatchDog_Init(uint16_t Time)
{
	uint32_t LoadTime;
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)//通过RCC时钟中的标志位函数选择看门狗的标志位
	{
		RCC_ClearFlag();
	}
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);//需要计算超时时间，来选择PSC
	LoadTime = (Time/640) - 1;
	IWDG_SetReload(LoadTime);//1000（目标计时）/0.025（固定的）/16（预分频系数） - 1
	IWDG_ReloadCounter();	//先喂一次狗（CNT清零）					//重装计数器，喂狗
	IWDG_Enable();
}
