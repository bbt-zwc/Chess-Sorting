#ifndef _ADC_H_
#define _ADC_H_
#include "Headfile.h"                  // Device header

// ADC编号选择（可以不改）
// 可以是 ADC1/2/3
#define    ADCx        ADC1
#define    ADC_CLK     RCC_APB2Periph_ADC1
/*ADC通道选择*/
#define CH0		0	
#define CH1		1	
#define CH2		2	
#define CH3		3	
#define CH4		4	
#define CH5		5	
#define CH6		6	
#define CH7		7	
#define CH8		8	
#define CH9		9	
#define CH10	10
#define CH11	11
#define CH12	12
#define CH13	13
#define CH14	14
#define CH15	15
/*函数使用说明：
入口参数：CH0~CH15；
ADC初始化部分放在main中whlie前初始化；
要读取ADC数值只需要用int型变量存储 获取ADC值函数 即可。
*/
void ADCx_Init(uint8_t ADC_Channel);
u16 ADC_GetValue(uint8_t ADC_Channel);

#endif
