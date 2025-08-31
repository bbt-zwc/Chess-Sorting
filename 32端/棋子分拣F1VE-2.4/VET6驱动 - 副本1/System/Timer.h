#ifndef __TIMER_H
#define __TIMER_H

#define TIM2_NVIC_Group		NVIC_PriorityGroup_1
#define TIM2_CPP	1
#define TIM2_CSP	1

#define TIM3_NVIC_Group		NVIC_PriorityGroup_2
#define TIM3_CPP	2
#define TIM3_CSP	0

#define TIM4_NVIC_Group		NVIC_PriorityGroup_2
#define TIM4_CPP	2
#define TIM4_CSP	1

#define TIM5_NVIC_Group		NVIC_PriorityGroup_2
#define TIM5_CPP	2
#define TIM5_CSP	2

#define TIM6_NVIC_Group		NVIC_PriorityGroup_3
#define TIM6_CPP	3
#define TIM6_CSP	0

#define TIM7_NVIC_Group		NVIC_PriorityGroup_3
#define TIM7_CPP	3
#define TIM7_CSP	1
/*PWM通道入口写法*/
#define CH1	1
#define CH2	2
#define CH3	3
#define CH4	4
/*初始化入口参数说明：*/
//ARR:     0~65535
//PSC:     0~65535
//PWMx:	   CHx（x=1~4） / Disable
//Encoder：Enable / Disable
//NVIC_Enable：Enable / Disable
/*函数使用说明：
ARR和PSC使用时需要减1后填入；
PWM输出和输入捕获IC，两种模式仅且只能选择其一使用，否则失效；
此处编码器的Enable的意思是本定时器的输入捕获功能被使能！！！
相同的定时器多次调用时需要确保ARR和PSC一致，否则默认最后一次初始化的数值。
*/
void TIM1_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder);
void TIM2_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder,uint8_t NVIC_Enable);
void TIM3_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder,uint8_t NVIC_Enable);
void TIM4_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder,uint8_t NVIC_Enable);
void TIM5_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder,uint8_t NVIC_Enable);
void TIM6_Init(uint32_t ARR,uint32_t PSC,uint8_t NVIC_Enable);
void TIM7_Init(uint32_t ARR,uint32_t PSC,uint8_t NVIC_Enable);
void TIM8_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder);
/*设置PWM占空比*/
void TIM1CH1_PWM(uint16_t Compare);
void TIM1CH2_PWM(uint16_t Compare);
void TIM1CH3_PWM(uint16_t Compare);
void TIM1CH4_PWM(uint16_t Compare);

void TIM2CH1_PWM(uint16_t Compare);
void TIM2CH2_PWM(uint16_t Compare);
void TIM2CH3_PWM(uint16_t Compare);
void TIM2CH4_PWM(uint16_t Compare);

void TIM3CH1_PWM(uint16_t Compare);
void TIM3CH2_PWM(uint16_t Compare);
void TIM3CH3_PWM(uint16_t Compare);
void TIM3CH4_PWM(uint16_t Compare);

void TIM4CH1_PWM(uint16_t Compare);
void TIM4CH2_PWM(uint16_t Compare);
void TIM4CH3_PWM(uint16_t Compare);
void TIM4CH4_PWM(uint16_t Compare);

void TIM5CH1_PWM(uint16_t Compare);
void TIM5CH2_PWM(uint16_t Compare);
void TIM5CH3_PWM(uint16_t Compare);
void TIM5CH4_PWM(uint16_t Compare);

void TIM8CH1_PWM(uint16_t Compare);
void TIM8CH2_PWM(uint16_t Compare);
void TIM8CH3_PWM(uint16_t Compare);
void TIM8CH4_PWM(uint16_t Compare);

int32_t TIM1_EncoderGet(void);
int32_t TIM2_EncoderGet(void);
int32_t TIM3_EncoderGet(void);
int32_t TIM4_EncoderGet(void);
int32_t TIM5_EncoderGet(void);
int32_t TIM8_EncoderGet(void);
	
#endif
/*中断示例：*/
/*
void TIM2_IRQHandler (void)
{
	//检测中断标志位
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{	
		//要执行的操作
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
void TIM3_IRQHandler (void)
{
	//检测中断标志位
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{	
		//要执行的操作
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}
void TIM4_IRQHandler (void)
{
	//检测中断标志位
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)
	{	
		//要执行的操作
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}
void TIM5_IRQHandler (void)
{
	//检测中断标志位
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) == SET)
	{	
		//要执行的操作
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
	}
}
*/
