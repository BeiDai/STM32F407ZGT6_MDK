#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "pwm.h"
#include "usart3.h"
#include "wifi.h"

#define STEP PFout(9)
#define DIR PFout(10)	
//int main(void)
//{   
//  DIR=0;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
//	delay_init(168);  //初始化延时函数
//	uart_init(115200);//初始化串口波特率为115200
// 	TIM14_PWM_Init(8000-1,10-1);	//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.     
//   while(1) 
//	{
//		TIM_SetCompare1(TIM14,10);	//修改比较值，修改占空比
//	}
//}
void Motor_Init(void) 
{ 
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//LED2和LED3对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO
} 
void Step_Control(u8 dir,u16 period,u32 steps) 
{ 
	u32 i; 
	DIR = dir; 
	for(i=0; i <= steps;i++) 
	{  
	STEP = 1; 
	delay_us(1); 
	STEP = 0; 
	delay_us(period); 
	} 
}
int main(void) 
{ 
	u16 rlen=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  
	uart_init(115200);//初始化串口波特率为115200
	usart3_init(115200); 
	Motor_Init();
	atk_8266_test();
	USART3_RX_STA=0;
	while(1)
	{
//		Step_Control(0,900,500);
//		delay_ms(10000);
//		Step_Control(1,900,200);
//		delay_ms(10000);
//		delay_ms(5);
	if(USART3_RX_STA&0X8000)		//接收到一次数据了
	{ 
		rlen=USART3_RX_STA&0X7FFF;	//得到本次接收到的数据长度
		USART3_RX_BUF[rlen]=0;		//添加结束符 
		printf("%s",USART3_RX_BUF);	//发送到串口   
		USART3_RX_STA=0;
	}
		atk_8266_at_response(1);
	}    
}

