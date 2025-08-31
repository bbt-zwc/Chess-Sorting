#include "Headfile.h"                  // Device header

uint8_t flag = 0,CountEnable = 0;
uint32_t Spd = 0;
void Motor_Init(void)
{	
	GPIOx_Init(PA,PP,3);
	GPIOx_Init(PA,PP,4);
	GPIOx_Init(PA,PP,6);
	GPIOx_Init(PA,PP,7);
	GPIOx_Init(PA,PP,11);
	GPIOx_Init(PA,PP,12);

}
//DIR方向，1正向0反向，Round圈数；speed脉冲高低电平时间
void Motor1(uint32_t DIR,uint32_t Round,uint32_t Speed)
{
	if (DIR) //左
	{
		PA_H(4);
	}
	if (DIR == 0) //右
	{
		PA_L(4);
	}
	for(uint32_t i = 0;i <= (Round*100);i ++)//3200脉冲
	{
		Delay_us(Speed);
		GPIOA->ODR ^= GPIO_Pin_3; 
	}
}
void Motor2(uint32_t DIR,uint32_t Round,uint32_t Speed)
{
	if (DIR) //下
	{
		PA_L(7);
	}
	if (DIR == 0) //上
	{
		PA_H(7);
	}
	for(uint32_t i = 0;i <= (Round*100);i ++)//3200脉冲
	{
		Delay_us(Speed);
    	GPIOA->ODR ^= GPIO_Pin_6;  		//翻转输出电平
	}
}
void Motor3(uint32_t DIR,uint32_t Round,uint32_t Speed)
{
	if (DIR) //上
	{
		PA_H(12);
	}
	if (DIR == 0) //下
	{
		PA_L(12);
	}
	for(uint32_t i = 0;i <= (Round*100);i ++)//3200脉冲
	{
		Delay_us(Speed);
    	GPIOA->ODR ^= GPIO_Pin_11;  		//翻转输出电平
	}
}








