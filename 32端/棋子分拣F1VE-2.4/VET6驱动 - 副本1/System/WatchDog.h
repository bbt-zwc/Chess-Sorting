#ifndef __WATCHDOG__H
#define __WATCHDOG__H

//初始化
void WatchDog_Init(uint16_t Time);	//单位ms

//把以下内容放到主函数While中，即成功启用独立看门狗  ：
//IWDG_ReloadCounter();

#endif
