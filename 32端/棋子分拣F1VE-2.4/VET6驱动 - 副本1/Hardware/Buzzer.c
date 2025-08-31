#include "Headfile.h"

uint16_t Buz_Delay = 0;
uint8_t Buz_Num = 0;
void Buzzer_Init(void)
{
    GPIOx_Init(PE,PP,14);
    PE_L(14);
}

void Buzzer_ON(void)
{
    PE_H(14);
}
void Buzzer_OFF(void)
{
    PE_L(14);
}
void Buzzer_Toggle(uint16_t Time_ms,uint8_t Num)
{
    Buz_Delay = Time_ms;
    Buz_Num = Num;
}
