#include "Headfile.h"

int x,y,go1,go2;
int speed = 40;
extern int pxy[120][2];


void Elm_open(int a)
{
	if(a==1)
	{
		PA_H(0);
	}	
	else if(a==0)
	{
		PA_L(0);
	}	
}

void take_qi(int b)
{
	z_move(0,40,speed) ; 
	Elm_open(b);
  Delay_ms(100);//*����
	z_move(1,40,speed) ; 
}	


void gogogo(int p11,int p12)
{
	
	if(p11%13 != 0)
	{
		Elm_open(1);
		//*��ԭ�㵽p1λ��
		x = pxy[p11][0]-current_x;
		if(x>=0){go1=1;}
		else if(x<0){go1=0;x=-x;}
		y = pxy[p11][1]-current_y;
		if(y>=0){go2=1;}
		else if(y<0){go2=0;y=-y;}
		x_move(go1,x,speed);
		y_move(go2,y,speed);
//		Serial_Printf("��1��λ�ã�(%d,%d) \r\n",current_x,current_y);
		take_qi(1);
		
		//*�ٵ�p2λ��
		x = pxy[p12][0]-current_x;
		if(x>=0){go1=1;}
		else if(x<0){go1=0;x=-x;}
		y = pxy[p12][1]-current_y;
		if(y>=0){go2=1;}
		else if(y<0){go2=0;y=-y;}
		x_move(go1,x,speed);
		y_move(go2,y,speed);
//		Serial_Printf("��2��λ��:(%d,%d) \r\n",current_x,current_y);
		take_qi(0);
		
	}
	else if(p11%13 == 0)
	{
//		Serial_Printf("������Χ����ǰλ�ã� (%d,%d) \r\n",current_x,current_y);
	}
}
