#include "Headfile.h"
/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void ADCx_Init(uint8_t ADC_Channel)
{
	//开启ADC时钟
	RCC_APB2PeriphClockCmd(ADC_CLK, ENABLE);
	
	//ADC进行6分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//配置GPIO口
	switch(ADC_Channel)
	{
		case CH0:GPIOx_Init(PA,AIN,0);break;
		case CH1:GPIOx_Init(PA,AIN,1);break;
		case CH2:GPIOx_Init(PA,AIN,2);break;
		case CH3:GPIOx_Init(PA,AIN,3);break;
		case CH4:GPIOx_Init(PA,AIN,4);break;
		case CH5:GPIOx_Init(PA,AIN,5);break;
		case CH6:GPIOx_Init(PA,AIN,6);break;
		case CH7:GPIOx_Init(PA,AIN,7);break;
		case CH8:GPIOx_Init(PB,AIN,0);break;
		case CH9:GPIOx_Init(PB,AIN,1);break;
		case CH10:GPIOx_Init(PC,AIN,0);break;
		case CH11:GPIOx_Init(PC,AIN,1);break;
		case CH12:GPIOx_Init(PC,AIN,2);break;
		case CH13:GPIOx_Init(PC,AIN,3);break;
		case CH14:GPIOx_Init(PC,AIN,4);break;
		case CH15:GPIOx_Init(PC,AIN,5);break;
		default:break;
	}
	
	//配置ADC
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	    			//独立模式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//软件触发
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					//单次转换
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						//非扫描模式
	ADC_InitStructure.ADC_NbrOfChannel = 1;								//总通道数
	ADC_Init(ADCx, &ADC_InitStructure);									//初始化ADC
	
	//使能ADC
	ADC_Cmd(ADCx, ENABLE);
	
	//ADC校验
	ADC_ResetCalibration(ADCx);
	while(ADC_GetResetCalibrationStatus(ADCx) == SET);
	ADC_StartCalibration(ADCx);
	while(ADC_GetCalibrationStatus(ADCx) == SET);	
}

/**
  * @brief  获取ADC转换后的数据
  * @param  ADC_Channel 	选择需要采集的ADC通道
  * @param  ADC_SampleTime  选择采样时间
  * @retval 转换后的模拟信号数值
  */
u16 ADC_GetValue(uint8_t ADC_Channel)
{
	//配置ADC通道
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	
	ADC_SoftwareStartConvCmd(ADCx, ENABLE); 			   //软件触发ADC	
	while(ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET); //转换完成标志位
	return ADC_GetConversionValue(ADCx);
}
