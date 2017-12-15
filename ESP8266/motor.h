#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "sys.h"
#include "delay.h"

#define EN PFout(13)	
#define STEP PFout(11)
#define DIR PFout(10)	

void Motor_Init(void);
void Step_Control(u8 dir,u16 period,u32 steps);
#endif
