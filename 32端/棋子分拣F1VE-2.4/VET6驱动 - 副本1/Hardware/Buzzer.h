#ifndef __BUZZER_H
#define __BUZZER_H

#include "Headfile.h"

void Buzzer_Init(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);
void Buzzer_Toggle(uint16_t Time_ms,uint8_t Num);

#endif
