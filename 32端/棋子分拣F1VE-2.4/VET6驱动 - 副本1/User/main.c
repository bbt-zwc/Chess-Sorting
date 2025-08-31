#include "Headfile.h"

int key;

int main(void)
{	
	TIM2_Init(999,71,Disable,Disable,Enable);
	Serial_Init();		//串口初始化
	LED_Init();
	Key_Init();
	OLED_Init();
	Motor_Init();
	GPIOx_Init(PA, PP, 0);
	OLED_ShowString(1,1,"fuck");
	Calculate_coordinates();
	Elm_open(0);
	z_move(1,40,50);
	x_move(1,158,50);
	y_move(1,590,50);
	
	while (1)
	{
		key = Key_GetNum();	
		if(key == 1)
		{
			Elm_open(0);
			Serial_TxPacket[0] = 1;
			Serial_SendPacket();
//			
//			x_move(1,20,100);
//		Serial_Printf("(%d,%d) \r\n",current_x,current_y);
		}
		else if(key == 2)
		{
			Elm_open(1);
			Serial_TxPacket[0] = 2;
			Serial_SendPacket();
//			y_move(1,20,100);
//		Serial_Printf("(%d,%d) \r\n",current_x,current_y);
		}
		else if(key == 3)
		{
			Serial_TxPacket[0] = 3;
			Serial_SendPacket();
//			y_move(0,20,100);
//		Serial_Printf("(%d,%d) \r\n",current_x,current_y);
		}
		else if(key == 4)
		{
			Serial_TxPacket[0] = 4;
			Serial_SendPacket();
//			gogogo(14,118);
//			gogogo(44,119);
//			for(int i=0;i<=119;i++)
//			{
//				gogogo(i,118);
//			}
		}
		if (Serial_GetRxFlag() == 1)	
		{
			OLED_ShowString(1,1,"???? fuck !!!!");
			uint8_t i,j,k;
			
			Serial_Printf("get:");
			for(i=0;i<117;i++)
			{
				k=Serial_RxPacket[i];
				Serial_Printf("%d ",k);
				j = 1+i;
				if(k==2)//黑
				{
					OLED_ShowString(2,1,"black:");
					OLED_ShowNum(2, 7, j, 2);
					gogogo(j,118);
					j++;
				}
				else if(k==1)//白
				{
					OLED_ShowString(2,1,"white:");
					OLED_ShowNum(2, 7, j, 2);
					gogogo(j,119);
					j++;
				}
				else if(k==0)//啥也没有
				{
					OLED_ShowString(2,1,"empty:");
					OLED_ShowNum(2, 7, j, 2);
					j++;
				}
			}
			Delay_s(1);
			Serial_TxPacket[0] = 3;
			Serial_SendPacket();
		}
	}
		
}

void TIM2_IRQHandler (void)//10ms
{
	//检测中断标志位
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Key_Tick();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}


