#include "motor.h"
#include "ReedSwitch.h"
#include "oled.h"

u8 positionReceive = 0;
u8 position1 = 0;
u8 positionNow = 0;

void Motor_Init(void) 
{ 
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
  //GPIOF9,F10,F8初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 |GPIO_Pin_13;//LED2和LED3对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO
} 
	//	Step_Control(0,1300,2000);  
void Step_Control(u8 dir,u16 period,u32 steps) //1300--700
{ 
	u32 i; 
	EN =0;   //
	DIR = dir; 
	for(i=0; i <= steps;i++) 
	{  
	STEP = 1; 
	delay_us(2); 
	STEP = 0; 
	delay_us(period); 
	} 
	delay_ms(10);
	EN =1; 
}
// 药盒位置初始化，通过干簧管确定1号药盒的位置
void  boxPosition_Init(u8 dir,u16 period,u32 steps) //1300--700
{ 
	u32 i; 
	EN =0;   //
	DIR = dir; 
	for(i=0; i <= steps;i++) 
	{  
	STEP = 1; 
	delay_us(2); 
	STEP = 0; 
	delay_us(period); 
	if(ReedSwitch == 0)
	{
		break;
	}
	} 
	delay_ms(10);
	EN =1; 
	OLED_ShowString(24,40,"ReedSwitch !  ",12);
	OLED_Refresh_Gram();
	positionNow = 1;
}

//药盒控制函数，输入药盒的位置
//所需药盒位置 - 现在药盒所在位置  =  电机控制 M
//大于0，反转控制转动，转 45 * M 度
//小于0，正转控制转动，转 45 * M 度

void boxPosition(u8 num)
{
	s8 temp;
	temp = num - positionNow;
	if(temp > 0)
	{
		Step_Control(0,350,800*temp);
	}
	else if(temp < 0)
	{
		temp = -temp;
		Step_Control(1,350,800*temp);
	}
}


