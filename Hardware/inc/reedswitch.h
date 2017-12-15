#ifndef _REEDSWITCH_H
#define _REEDSWITCH_H
#include "sys.h"

#define ReedSwitch  PEin(5)

void ReedSwitchInit(void);

//干簧管感应到磁场时输出低电平，加一个中断控制。

#endif
