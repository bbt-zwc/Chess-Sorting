#include "Headfile.h"


//20个位置坐标xy,面向装置2个电机在远处，左上角为原点，向右x+，向下y+


int pxy[120][2] = {
	{0,0}, //*0号坐标,原点
};

void Calculate_coordinates(void)
{
	int topLeft_x,topLeft_y,bottomright_x,bottomright_y;
	topLeft_x = 0;
	topLeft_y = 0;
	bottomright_x = topLeft_x + 648;
	bottomright_y = topLeft_y + 432;
	int xStep, yStep;
//	int points[9][13]; 
	xStep = (bottomright_x - topLeft_x) / 12.0;  // x????
	yStep = (bottomright_y - topLeft_y) / 8.0;
	for(int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			pxy[13*i+j+1][0] = topLeft_x + j * xStep;
			pxy[13*i+j+1][1] = topLeft_y + i * yStep;
//			Serial_Printf("pxy(%d):(%d,%d) \r",13*i+j+1,pxy[13*i+j+1][0],pxy[13*i+j+1][1]);
		}
	}
	pxy[118][0] = pxy[1][0]+158;
	pxy[118][1] = pxy[1][1]+590;
	pxy[119][0] = pxy[1][0]+490;
	pxy[119][1] = pxy[1][1]+590;
//	Serial_Printf("pxy(%d):(%d,%d) \r",118,pxy[118][0],pxy[118][1]);
//	Serial_Printf("pxy(%d):(%d,%d) \r",119,pxy[119][0],pxy[119][1]);
}