#include "Headfile.h"                  // Device header

void RP_Init(void)
{
	ADCx_Init(CH6);
}

uint16_t RP_GetValue(uint8_t ADC_Channel)
{
	return ADC_GetValue(ADC_Channel);
}
