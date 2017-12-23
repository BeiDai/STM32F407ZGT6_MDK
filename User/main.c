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
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
//	delay_init(168);  
//	ReedSwitchInit();
//	LED_Init();
//	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
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
////	if(USART3_RX_STA&0X8000)		//���յ�һ��������
////	{ 
////		rlen=USART3_RX_STA&0X7FFF;	//�õ����ν��յ������ݳ���
////		USART3_RX_BUF[rlen]=0;		//��ӽ����� 
////		printf("%s",USART3_RX_BUF);	//���͵�����   
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

int main(void) 
{ 
	u16 rlen=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  
	ReedSwitchInit();
	LED_Init();
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
	usart3_init(115200); 
	Motor_Init();
	OLED_Init();				
	atk_8266_config();
	USART3_RX_STA=0;
	EN = 1;
	OLED_ShowString(0,0," STM32F407ZGTGT6 2.4'",12); 
	OLED_Refresh_Gram();
	while(1)
	{
		if(USART3_RX_STA&0X8000)		//���յ�һ��������
		{ 
			rlen=USART3_RX_STA&0X7FFF;	//�õ����ν��յ������ݳ���
			USART3_RX_BUF[rlen]=0;		//��ӽ����� 
			OLED_Clear();
			delay_ms(200);
			OLED_ShowString(0,50,USART3_RX_BUF,12);
			OLED_ShowChar(60,0,USART3_RX_BUF[rlen-1],12,1);
			OLED_ShowNum(60,20,USART3_RX_BUF[rlen-1]-'0',1,12);
			OLED_ShowChar(70,0,USART3_RX_BUF[rlen-2],12,1);
			OLED_ShowNum(70,20,USART3_RX_BUF[rlen-2]-'0',1,12);
			OLED_ShowChar(76,0,USART3_RX_BUF[rlen-3],12,1);
			OLED_ShowNum(80,20,USART3_RX_BUF[rlen-3]-'0',1,12);
//			
//			atk_8266_send_cmd("AT+CIPSEND=0,11","OK",20);
//			u3_printf("�ɹ����ӣ��뷢�����");
//	
			OLED_Refresh_Gram();
			USART3_RX_STA = 0;
		}
	}    
}

