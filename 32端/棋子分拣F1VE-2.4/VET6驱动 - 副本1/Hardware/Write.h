#ifndef __WRITE_H
#define __WRITE_H

#include "Headfile.h"

void  x_move(uint32_t dir,uint32_t num,uint32_t speed);
void  y_move(uint32_t dir,uint32_t num,uint32_t speed);
void  z_move(uint32_t dir,uint32_t num,uint32_t speed);

extern int current_x;
extern int current_y;
extern char X_ENABLE;

#endif
