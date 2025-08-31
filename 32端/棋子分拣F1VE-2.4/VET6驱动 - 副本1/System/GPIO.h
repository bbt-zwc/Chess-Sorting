// GPIO.h
#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

// GPIO端口定义
#define PA 1
#define PB 2
#define PC 3
#define PD 4
#define PE 5

// 工作模式定义
#define PP  1    // 推挽输出
#define AIN 2    // 模拟输入
#define IPU 3    // 上拉输入
#define AFPP 4    // 复用推挽输出

//定义宏函数
#define PA_L(Px)		GPIO_ResetBits(GPIOA,1<<Px)
#define PB_L(Px)		GPIO_ResetBits(GPIOB,1<<Px)
#define PC_L(Px)		GPIO_ResetBits(GPIOC,1<<Px)
#define PD_L(Px)		GPIO_ResetBits(GPIOD,1<<Px)
#define PE_L(Px)		GPIO_ResetBits(GPIOE,1<<Px)

#define PA_H(Px)		GPIO_SetBits(GPIOA,1<<Px)
#define PB_H(Px)		GPIO_SetBits(GPIOB,1<<Px)
#define PC_H(Px)		GPIO_SetBits(GPIOC,1<<Px)
#define PD_H(Px)		GPIO_SetBits(GPIOD,1<<Px)
#define PE_H(Px)		GPIO_SetBits(GPIOE,1<<Px)

#define PA_R(Px)		GPIO_ReadInputDataBit(GPIOA,1<<Px)
#define PB_R(Px)		GPIO_ReadInputDataBit(GPIOB,1<<Px)
#define PC_R(Px)		GPIO_ReadInputDataBit(GPIOC,1<<Px)
#define PD_R(Px)		GPIO_ReadInputDataBit(GPIOD,1<<Px)
#define PE_R(Px)		GPIO_ReadInputDataBit(GPIOE,1<<Px)

void GPIOx_Init(uint8_t GPIOx, uint8_t GPIOxMode, uint8_t Px_num);

#endif

