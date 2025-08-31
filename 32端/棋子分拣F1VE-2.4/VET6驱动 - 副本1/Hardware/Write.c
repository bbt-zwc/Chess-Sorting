#include "Headfile.h"
/*
每100个num对应50mm
2个num对应1mm

则移动27mm（每一格），以54个num！

x/y轴方向300mm上限移动距离，共计600个num

O --------------150------------->y轴
|
|
|
|
|
|
|
150
|
|
|
|
|
|
V
x轴
*/

#define YMAX 600
#define XMAX 600

// 全局二维数组，用于记录位置状态
int X_Location[XMAX] = {0};
int Y_Location[YMAX] = {0};

// 当前位置
int xcur,ycur,zcur;
int current_x = 0;
int current_y = 0;

// 使能位
char X_ENABLE = 1;
char X_putnum = 0;
char Y_ENABLE = 1;
char Y_putnum = 0;

void xy_init()
{
	X_ENABLE = 1;
	Y_ENABLE = 1;
	x_move(0,current_x,30);
	y_move(0,current_y,30);
}
void x_move(uint32_t dir,uint32_t num,uint32_t speed)
{
	// 更新全局位置
    if (dir == 1) // 正方向
    {
        xcur += num;
    }
    else // 反方向
    {
        xcur -= num;
    }
	// 边界限幅
	if(xcur < 0 || xcur > 600)
	{
		xcur = current_x;
		X_ENABLE = 0;
	}
	else
	{
		current_x = xcur;
		X_ENABLE = 1;
	}
    // 更新位置状态
    X_Location[current_x] = 1;
	
	
	if(dir==1)//x+
	{
		PA_L(4);
		PA_L(7);
	}
	if(dir==0)//x-
	{
		PA_H(7);
		PA_H(4);
	}
	if(X_ENABLE)
	{
		for(uint32_t i = 0;i <= (num*100);i ++)//3200脉冲
		{
			Delay_us(speed);
			GPIOA->ODR ^= GPIO_Pin_3;  		//翻转输出电平
			GPIOA->ODR ^= GPIO_Pin_6;  		//翻转输出电平
		}
//		X_ENABLE = 0;
	}
	
}

void y_move(uint32_t dir,uint32_t num,uint32_t speed)
{
	// 更新全局位置
    if (dir == 1) // 正方向
    {
        ycur += num;
    }
    else // 反方向
    {
        ycur -= num;
    }
	// 边界限幅
	if(ycur < 0 || ycur > 604)
	{
		ycur = current_y;
		Y_ENABLE = 0;
	}
	else
	{
		current_y = ycur;
		Y_ENABLE = 1;
	}
    // 更新位置状态
    Y_Location[current_y] = 1;
	
	
	if(dir==1)//y+
	{
		PA_L(7);
		PA_H(4);
	}
	
	if(dir==0)//y-
	{
		PA_H(7);
		PA_L(4);
	}
	if(Y_ENABLE)
	{
		for(uint32_t i = 0;i <= (num*100);i ++)//3200脉冲
		{
			Delay_us(speed);
			GPIOA->ODR ^= GPIO_Pin_3;  		//翻转输出电平
			GPIOA->ODR ^= GPIO_Pin_6;  		//翻转输出电平
		}
//		Y_ENABLE = 0;
	}
}


void z_move(uint32_t dir,uint32_t num,uint32_t speed)
{

	if(dir==0)//z-
	{
		PA_L(12);
	}
	
	if(dir==1)//z+
	{
		PA_H(12);
	}
	for(uint32_t i = 0;i <= (num*100);i ++)//3200脉冲
	{
		Delay_us(speed);
		GPIOA->ODR ^= GPIO_Pin_11;  		//翻转输出电平
	}
}


