#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "pwm.h"
#include "usart3.h"
#include "wifi.h"
#include "motor.h"
#include "reedswitch.h"
#include "oled.h"

//int main(void) 
//{ 
////	u16 rlen=0;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
//	delay_init(168);  
//	ReedSwitchInit();
//	LED_Init();
//	uart_init(115200);//初始化串口波特率为115200
//	usart3_init(115200); 
//	Motor_Init();
//	OLED_Init();				
//	atk_8266_config();
//	USART3_RX_STA=0;
//	EN = 1;
//	OLED_ShowString(0,0," STM32F407ZGTGT6 2.4'",12); 
//	OLED_Refresh_Gram();
//	while(1)
//	{
////	if(USART3_RX_STA&0X8000)		//接收到一次数据了
////	{ 
////		rlen=USART3_RX_STA&0X7FFF;	//得到本次接收到的数据长度
////		USART3_RX_BUF[rlen]=0;		//添加结束符 
////		printf("%s",USART3_RX_BUF);	//发送到串口   
////		if(USART3_RX_BUF[rlen-1]==48)
////			Step_Control(0,350,6400); 
////		else if(USART3_RX_BUF[rlen-1]==49)
////			Step_Control(1,350,6400);
////		USART3_RX_STA=0; 
////	}
//		atk_8266_at_response(1);
//		Step_Control(1,350,6400);
//		if(ReedSwitch==1)
//		{
//			OLED_ShowString(0,30,"     STOP! 10S",16); 
//			OLED_Refresh_Gram();
//			delay_ms(10000);
//			LED2=!LED2;
//			OLED_ShowString(0,30,"   ReedSwitch !    ",16); 
//			OLED_Refresh_Gram();
//		}
//	}    
//}

//int main(void) 
//{ 
//		u16 rlen=0;
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
//		delay_init(168);  
//		ReedSwitchInit();
//		LED_Init();
//		uart_init(115200);//初始化串口波特率为115200
//		usart3_init(115200); 
//		Motor_Init();
//		OLED_Init();	
//		OLED_ShowChinese(0+30,0,0,12,1); //智
//		OLED_ShowChinese(14+30,0,1,12,1); //能
//		OLED_ShowChinese(28+30,0,2,12,1);//云
//		OLED_ShowChinese(42+30,0,3,12,1);//药
//		OLED_ShowChinese(56+30,0,4,12,1);//盒	
//	  
//		OLED_ShowChinese(0+30-12,0+16,6,12,1); //请
//		OLED_ShowChinese(14+30-12,0+16,7,12,1); //取
//		OLED_ShowChinese(28+30-12,0+16,8,12,1);//药
//		OLED_ShowChinese(42+30-12,0+16,9,12,1);//：
//		OLED_ShowChinese(56+30-12+12,0+16,10,12,1);//盒
//		OLED_ShowChinese(70+30-12+12,0+16,11,12,1);//号
//	
//		OLED_Refresh_Gram();
////	OLED_ShowChinese(68+30,0,5,12,1);//wifi
//		atk_8266_config();
//	
//		USART3_RX_STA=0; //允许接收数据
//		EN = 1; //开启接收中断

//	while(1)
//	{
//		if(USART3_RX_STA&0X8000)	
//		{
//			rlen=USART3_RX_STA&0X7FFF;	//得到本次接收到的数据长度
//			USART3_RX_BUF[rlen]=0;		//添加结束符 
//			positionReceive = USART3_RX_BUF[rlen-1] - '0'; //把字符转为整形
//			position1 = USART3_RX_BUF[rlen-2] - '0';
//			switch(positionReceive)
//			{
//				case 1: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
//								Step_Control(1,350,6400);positionReceive=0; break;
//				
//				case 2: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
//								Step_Control(1,350,6400*2);positionReceive=0; break;
//				
//				case 3: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
//								Step_Control(1,350,6400*3);positionReceive=0; break;
//				
//				case 4: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
//								Step_Control(1,350,6400*4);positionReceive=0; break;
//				
//				case 5: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
//								Step_Control(1,350,6400*5);positionReceive=0;	break;
//				
//				case 6: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
//								Step_Control(1,350,6400*6);positionReceive=0; break;
//				
//				case 7: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
//								Step_Control(1,350,6400*7);positionReceive=0; break;
//				
//				case 8: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
//								Step_Control(1,350,6400*8);positionReceive=0; break;
//				defaule: break;
//			}
//			USART3_RX_STA=0;
//		}
//	}
//}

int main(void) 
{ 
		u16 rlen=0;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
		delay_init(168);  
		ReedSwitchInit();
		LED_Init();
		uart_init(115200);//初始化串口波特率为115200
		usart3_init(115200); 
		Motor_Init();
		EN = 1; //关闭电机电源
		OLED_Init();	
		OLED_ShowChinese(0+30,0,0,12,1); //智
		OLED_ShowChinese(14+30,0,1,12,1); //能
		OLED_ShowChinese(28+30,0,2,12,1);//云
		OLED_ShowChinese(42+30,0,3,12,1);//药
		OLED_ShowChinese(56+30,0,4,12,1);//盒	
	  
		OLED_ShowChinese(0+30-12,0+16,6,12,1); //请
		OLED_ShowChinese(14+30-12,0+16,7,12,1); //取
		OLED_ShowChinese(28+30-12,0+16,8,12,1);//药
		OLED_ShowChinese(42+30-12,0+16,9,12,1);//：
		OLED_ShowChinese(56+30-12+12,0+16,10,12,1);//盒
		OLED_ShowChinese(70+30-12+12,0+16,11,12,1);//号
	
		OLED_Refresh_Gram();
//	OLED_ShowChinese(68+30,0,5,12,1);//wifi
		atk_8266_config();
	
		USART3_RX_STA=0; //允许接收数据
		
		boxPosition_Init(1,350,6400*1000);
		
		positionNow = 1;

	while(1)
	{
		if(USART3_RX_STA&0X8000)	
		{
			rlen=USART3_RX_STA&0X7FFF;	//得到本次接收到的数据长度
			USART3_RX_BUF[rlen]=0;		//添加结束符 
			positionReceive = USART3_RX_BUF[rlen-1] - '0'; //把字符转为整形
			position1 = USART3_RX_BUF[rlen-2] - '0';
			switch(positionReceive)
			{
				case 1: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
								boxPosition(positionReceive);positionReceive=0,positionNow=1; break;
				
				case 2: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
								boxPosition(positionReceive);positionReceive=0,positionNow=2; break;
				
				case 3: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
								boxPosition(positionReceive);positionReceive=0,positionNow=3; break;
				
				case 4: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
								boxPosition(positionReceive);positionReceive=0,positionNow=4; break;
				
				case 5: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
								boxPosition(positionReceive);positionReceive=0,positionNow=5;	break;
				
				case 6: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
								boxPosition(positionReceive);positionReceive=0,positionNow=6; break;
				
				case 7: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
								boxPosition(positionReceive);positionReceive=0,positionNow=7; break;
				
				case 8: OLED_ShowNum(74,17,positionReceive,1,12),OLED_Refresh_Gram(),
								boxPosition(positionReceive);positionReceive=0,positionNow=8; break;
			}
			USART3_RX_STA=0;
		}
	}
}
