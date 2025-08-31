#include "Headfile.h"                  // Device header

void TIM1_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder)
{
	if(PWMx != 0 && Encoder != 0)
	{
		return;
	}
	/*使能时钟源*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	/*启用内部时钟源*/
	TIM_InternalClockConfig(TIM1);
	
	/*配置时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = ARR;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = PSC;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	/*PWM输出通道配置*/
	if(PWMx != 0)
	{
		TIM_CtrlPWMOutputs(TIM1,ENABLE);//允许PWM输出
		TIM_OCInitTypeDef TIM_OCInitStructure;
		TIM_OCStructInit(&TIM_OCInitStructure);
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0; 
		if(PWMx == 1)
		{
			GPIOx_Init(PA,AFPP,8);
			TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
			TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);		
		}
		if(PWMx == 2)
		{
			GPIOx_Init(PA,AFPP,9);
			TIM_OC2Init(TIM1, &TIM_OCInitStructure); 
			TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
		}
		if(PWMx == 3)
		{
			GPIOx_Init(PA,AFPP,10);
			TIM_OC3Init(TIM1, &TIM_OCInitStructure); 
			TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
		}
		if(PWMx == 4)
		{
			GPIOx_Init(PA,AFPP,11);
			TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
			TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
		}
	}	
	if(Encoder != 0)
	{
		/*配置输入捕获*/
		TIM_ICInitTypeDef TIM_ICInitStructure;
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;	//选择配置定时器通道1
		TIM_ICInitStructure.TIM_ICFilter = 0xF;				//输入滤波器参数，可以过滤信号抖动
		TIM_ICInit(TIM1, &TIM_ICInitStructure);				//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;	//选择配置定时器通道2
		TIM_ICInitStructure.TIM_ICFilter = 0xF;				//输入滤波器参数，可以过滤信号抖动
		TIM_ICInit(TIM1, &TIM_ICInitStructure);				//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
		/*初始化GPIO口*/
		GPIOx_Init(PA,IPU,8);
		GPIOx_Init(PA,IPU,9);
		
		TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);
	}
	TIM_Cmd(TIM1, ENABLE);
}
void TIM2_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder,uint8_t NVIC_Enable)
{
	if(PWMx != 0 && Encoder != 0)
	{
		return;
	}
	/*使能时钟源*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/*启用内部时钟源*/
	TIM_InternalClockConfig(TIM2);
	
	/*配置时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = ARR;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = PSC;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	/*初始化清除中断标志位*/
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
	if(PWMx != 0)
	{
		TIM_OCInitTypeDef TIM_OCInitStructure;
		TIM_OCStructInit(&TIM_OCInitStructure);
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0; 
		if(PWMx == 1)
		{
			GPIOx_Init(PA,AFPP,0);
			TIM_OC1Init(TIM2, &TIM_OCInitStructure); 		
		}
		if(PWMx == 2)
		{
			GPIOx_Init(PA,AFPP,1);
			TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
		}
		if(PWMx == 3)
		{
			GPIOx_Init(PA,AFPP,2);
			TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
		}
		if(PWMx == 4)
		{
			GPIOx_Init(PA,AFPP,3);
			TIM_OC4Init(TIM2, &TIM_OCInitStructure); 
		}
	}	
	if(Encoder != 0)
	{
		/*配置输入捕获*/
		TIM_ICInitTypeDef TIM_ICInitStructure;
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;	//选择配置定时器通道1
		TIM_ICInitStructure.TIM_ICFilter = 0xF;				//输入滤波器参数，可以过滤信号抖动
		TIM_ICInit(TIM2, &TIM_ICInitStructure);				//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;	//选择配置定时器通道2
		TIM_ICInitStructure.TIM_ICFilter = 0xF;				//输入滤波器参数，可以过滤信号抖动
		TIM_ICInit(TIM2, &TIM_ICInitStructure);				//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
		/*初始化GPIO口*/
		GPIOx_Init(PA,IPU,0);
		GPIOx_Init(PA,IPU,1);
		
		TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);
	}
	if(NVIC_Enable == Enable)
	{
		//使能中断
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//Update更新中断,使能。开启了更新中断到NVIC的通路
		//配置NVIC
		NVIC_PriorityGroupConfig(TIM2_NVIC_Group);//分到第二组
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//选择TIM2中断通道
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//开启通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM2_CPP;//响应优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM2_CSP;//抢占优先级
		/*中断初始化*/
		NVIC_Init(&NVIC_InitStructure);
	}
	TIM_Cmd(TIM2, ENABLE);
}
void TIM3_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder,uint8_t NVIC_Enable)
{
	if(PWMx != 0 && Encoder != 0)
	{
		return;
	}
	/*使能时钟源*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/*启用内部时钟源*/
	TIM_InternalClockConfig(TIM3);
	
	/*配置时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = ARR;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = PSC;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	/*初始化清除中断标志位*/
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	
	if(PWMx != 0)
	{
		TIM_OCInitTypeDef TIM_OCInitStructure;
		TIM_OCStructInit(&TIM_OCInitStructure);
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0; 
		if(PWMx == 1)
		{
			GPIOx_Init(PA,AFPP,6);
			TIM_OC1Init(TIM3, &TIM_OCInitStructure); 		
		}
		if(PWMx == 2)
		{
			GPIOx_Init(PA,AFPP,7);
			TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
		}
		if(PWMx == 3)
		{
			GPIOx_Init(PB,AFPP,0);
			TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
		}
		if(PWMx == 4)
		{
			GPIOx_Init(PB,AFPP,1);
			TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
		}
	}	
	if(Encoder != 0)
	{
		/*配置输入捕获*/
		TIM_ICInitTypeDef TIM_ICInitStructure;
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;	//选择配置定时器通道1
		TIM_ICInitStructure.TIM_ICFilter = 0xF;				//输入滤波器参数，可以过滤信号抖动
		TIM_ICInit(TIM3, &TIM_ICInitStructure);				//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;	//选择配置定时器通道2
		TIM_ICInitStructure.TIM_ICFilter = 0xF;				//输入滤波器参数，可以过滤信号抖动
		TIM_ICInit(TIM3, &TIM_ICInitStructure);				//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
		/*初始化GPIO口*/
		GPIOx_Init(PA,IPU,6);
		GPIOx_Init(PA,IPU,7);
		
		TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);
	}
	if(NVIC_Enable == Enable)
	{
		//使能中断
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//Update更新中断,使能。开启了更新中断到NVIC的通路
		//配置NVIC
		NVIC_PriorityGroupConfig(TIM3_NVIC_Group);//分到第二组
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//选择TIM2中断通道
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//开启通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM3_CPP;//响应优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM3_CSP;//抢占优先级
		/*中断初始化*/
		NVIC_Init(&NVIC_InitStructure);
	}
	TIM_Cmd(TIM3, ENABLE);
}
void TIM4_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder,uint8_t NVIC_Enable)
{
	if(PWMx != 0 && Encoder != 0)
	{
		return;
	}
	/*使能时钟源*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	/*启用内部时钟源*/
	TIM_InternalClockConfig(TIM4);
	
	/*配置时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = ARR;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = PSC;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	/*初始化清除中断标志位*/
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	
	if(PWMx != 0)
	{
		TIM_OCInitTypeDef TIM_OCInitStructure;
		TIM_OCStructInit(&TIM_OCInitStructure);
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0; 
		if(PWMx == 1)
		{
			GPIOx_Init(PB,AFPP,6);
			TIM_OC1Init(TIM4, &TIM_OCInitStructure); 		
		}
		if(PWMx == 2)
		{
			GPIOx_Init(PB,AFPP,7);
			TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
		}
		if(PWMx == 3)
		{
			GPIOx_Init(PB,AFPP,8);
			TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
		}
		if(PWMx == 4)
		{
			GPIOx_Init(PB,AFPP,9);
			TIM_OC4Init(TIM4, &TIM_OCInitStructure); 
		}
	}
	if(Encoder != 0)
	{
		/*配置输入捕获*/
		TIM_ICInitTypeDef TIM_ICInitStructure;
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;	//选择配置定时器通道1
		TIM_ICInitStructure.TIM_ICFilter = 0xF;				//输入滤波器参数，可以过滤信号抖动
		TIM_ICInit(TIM4, &TIM_ICInitStructure);				//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;	//选择配置定时器通道2
		TIM_ICInitStructure.TIM_ICFilter = 0xF;				//输入滤波器参数，可以过滤信号抖动
		TIM_ICInit(TIM4, &TIM_ICInitStructure);				//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
		/*初始化GPIO口*/
		GPIOx_Init(PB,IPU,6);
		GPIOx_Init(PB,IPU,7);
		
		TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);
	}	
	if(NVIC_Enable == Enable)
	{
		//使能中断
		TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//Update更新中断,使能。开启了更新中断到NVIC的通路
		//配置NVIC
		NVIC_PriorityGroupConfig(TIM4_NVIC_Group);//分到第二组
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//选择TIM2中断通道
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//开启通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM4_CPP;//响应优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM4_CSP;//抢占优先级
		/*中断初始化*/
		NVIC_Init(&NVIC_InitStructure);
	}
	TIM_Cmd(TIM4, ENABLE);
}
void TIM8_Init(uint32_t ARR,uint32_t PSC,uint8_t PWMx,uint8_t Encoder)
{
	if(PWMx != 0 && Encoder != 0)
	{
		return;
	}
	/*使能时钟源*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	/*启用内部时钟源*/
	TIM_InternalClockConfig(TIM8);
	
	/*配置时基单元*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = ARR;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = PSC;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure);
	/*PWM输出通道配置*/
	if(PWMx != 0)
	{
		TIM_CtrlPWMOutputs(TIM8,ENABLE);//允许PWM输出
		TIM_OCInitTypeDef TIM_OCInitStructure;
		TIM_OCStructInit(&TIM_OCInitStructure);
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0; 
		if(PWMx == 1)
		{
			GPIOx_Init(PC,AFPP,6);
			TIM_OC1Init(TIM8, &TIM_OCInitStructure); 
			TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);		
		}
		if(PWMx == 2)
		{
			GPIOx_Init(PC,AFPP,7);
			TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
			TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
		}
		if(PWMx == 3)
		{
			GPIOx_Init(PC,AFPP,8);
			TIM_OC3Init(TIM8, &TIM_OCInitStructure); 
			TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
		}
		if(PWMx == 4)
		{
			GPIOx_Init(PC,AFPP,9);
			TIM_OC4Init(TIM8, &TIM_OCInitStructure); 
			TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
		}
	}	
	if(Encoder != 0)
	{
		/*配置输入捕获*/
		TIM_ICInitTypeDef TIM_ICInitStructure;
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;	//选择配置定时器通道1
		TIM_ICInitStructure.TIM_ICFilter = 0xF;				//输入滤波器参数，可以过滤信号抖动
		TIM_ICInit(TIM8, &TIM_ICInitStructure);				//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;	//选择配置定时器通道2
		TIM_ICInitStructure.TIM_ICFilter = 0xF;				//输入滤波器参数，可以过滤信号抖动
		TIM_ICInit(TIM8, &TIM_ICInitStructure);				//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
		/*初始化GPIO口*/
		GPIOx_Init(PA,IPU,8);
		GPIOx_Init(PA,IPU,9);
		
		TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);
	}
	TIM_Cmd(TIM8, ENABLE);
}
void TIM1CH1_PWM(uint16_t Compare)
{
	TIM_SetCompare1(TIM1, Compare);
}
void TIM1CH2_PWM(uint16_t Compare)
{
	TIM_SetCompare2(TIM1, Compare);
}
void TIM1CH3_PWM(uint16_t Compare)
{
	TIM_SetCompare3(TIM1, Compare);
}
void TIM1CH4_PWM(uint16_t Compare)
{
	TIM_SetCompare4(TIM1, Compare);
}

void TIM2CH1_PWM(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);
}
void TIM2CH2_PWM(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);
}
void TIM2CH3_PWM(uint16_t Compare)
{
	TIM_SetCompare3(TIM2, Compare);
}
void TIM2CH4_PWM(uint16_t Compare)
{
	TIM_SetCompare4(TIM2, Compare);
}

void TIM3CH1_PWM(uint16_t Compare)
{
	TIM_SetCompare1(TIM3, Compare);
}
void TIM3CH2_PWM(uint16_t Compare)
{
	TIM_SetCompare2(TIM3, Compare);
}
void TIM3CH3_PWM(uint16_t Compare)
{
	TIM_SetCompare3(TIM3, Compare);
}
void TIM3CH4_PWM(uint16_t Compare)
{
	TIM_SetCompare4(TIM3, Compare);
}

void TIM4CH1_PWM(uint16_t Compare)
{
	TIM_SetCompare1(TIM4, Compare);
}
void TIM4CH2_PWM(uint16_t Compare)
{
	TIM_SetCompare2(TIM4, Compare);
}
void TIM4CH3_PWM(uint16_t Compare)
{
	TIM_SetCompare3(TIM4, Compare);
}
void TIM4CH4_PWM(uint16_t Compare)
{
	TIM_SetCompare4(TIM4, Compare);
}
void TIM5CH1_PWM(uint16_t Compare)
{
	TIM_SetCompare1(TIM5, Compare);
}
void TIM5CH2_PWM(uint16_t Compare)
{
	TIM_SetCompare2(TIM5, Compare);
}
void TIM5CH3_PWM(uint16_t Compare)
{
	TIM_SetCompare3(TIM5, Compare);
}
void TIM5CH4_PWM(uint16_t Compare)
{
	TIM_SetCompare4(TIM5, Compare);
}
void TIM8CH1_PWM(uint16_t Compare)
{
	TIM_SetCompare1(TIM8, Compare);
}
void TIM8CH2_PWM(uint16_t Compare)
{
	TIM_SetCompare2(TIM8, Compare);
}
void TIM8CH3_PWM(uint16_t Compare)
{
	TIM_SetCompare3(TIM8, Compare);
}
void TIM8CH4_PWM(uint16_t Compare)
{
	TIM_SetCompare4(TIM8, Compare);
}

int32_t TIM1_EncoderGet(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM1);
	TIM_SetCounter(TIM1, 0);
	return Temp;
}
int32_t TIM2_EncoderGet(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM2);
	TIM_SetCounter(TIM2, 0);
	return Temp;
}
int32_t TIM3_EncoderGet(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	return Temp;
}
int32_t TIM4_EncoderGet(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM4);
	TIM_SetCounter(TIM4, 0);
	return Temp;
}int32_t TIM5_EncoderGet(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM5);
	TIM_SetCounter(TIM5, 0);
	return Temp;
}
int32_t TIM8_EncoderGet(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM8);
	TIM_SetCounter(TIM8, 0);
	return Temp;
}
