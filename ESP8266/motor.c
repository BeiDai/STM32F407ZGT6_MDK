#include "motor.h"
#include "ReedSwitch.h"
#include "oled.h"

u8 positionReceive = 0;
u8 position1 = 0;
u8 positionNow = 0;

void Motor_Init(void) 
{ 
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
  //GPIOF9,F10,F8��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 |GPIO_Pin_13;//LED2��LED3��ӦIO��
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
	delay_ms(10);
	EN =1; 
}
// ҩ��λ�ó�ʼ����ͨ���ɻɹ�ȷ��1��ҩ�е�λ��
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

//ҩ�п��ƺ���������ҩ�е�λ��
//����ҩ��λ�� - ����ҩ������λ��  =  ������� M
//����0����ת����ת����ת 45 * M ��
//С��0����ת����ת����ת 45 * M ��

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


