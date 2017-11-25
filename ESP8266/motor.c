#include "motor.h"
//
void Motor_Init(void) 
{ 
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
  //GPIOF9,F10,F8��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 |GPIO_Pin_8;//LED2��LED3��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIO
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
	delay_ms(1000);
	EN =1; 
}

