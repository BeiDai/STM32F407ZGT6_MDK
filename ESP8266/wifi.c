#include "wifi.h"
#include "led.h"

////WIFI AP�˿ںţ�WiFi����wifi����

const unsigned int portnum=8086;		 

const u8* wifiap_ssid="ESP8266";			//����SSID��

const u8* wifiap_password="123456789"; 		//�������� 


//���յ���ATָ��Ӧ�����ݷ��ظ����Դ���
//mode:0,������USART3_RX_STA;
//     1,����USART3_RX_STA;
void atk_8266_at_response(u8 mode)
{
	if(USART3_RX_STA&0X8000)		//���յ�һ��������
	{
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//��ӽ�����
		printf("%s",USART3_RX_BUF);	//���͵�����
		if(mode)USART3_RX_STA=0;
	}
}

//ATK-ESP8266���������,�����յ���Ӧ��
//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//    ����,�ڴ�Ӧ������λ��(str��λ��)
u8* atk_8266_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART3_RX_STA&0X8000)		//���յ�һ��������
	{
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//��ӽ�����
		strx=strstr((const char*)USART3_RX_BUF,(const char*)str);
	}
	return (u8*)strx;
}
//��ATK-ESP8266��������
//cmd:���͵������ַ���
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0;
	USART3_RX_STA=0;
	u3_printf("%s\r\n",cmd);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(atk_8266_check_cmd(ack))
				{
					printf("ack:%s\r\n",(u8*)ack);
					break;//�õ���Ч����
				}
					USART3_RX_STA=0;
			}
		}
		if(waittime==0)res=1;
	}
	return res;
}

//��ATK-ESP8266����ָ������
//data:���͵�����(����Ҫ��ӻس���)
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
u8 atk_8266_send_data(u8 *data,u8 *ack,u16 waittime)
{
	u8 res=0;
	USART3_RX_STA=0;
	u3_printf("%s",data);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(atk_8266_check_cmd(ack))break;//�õ���Ч����
				USART3_RX_STA=0;
			}
		}
		if(waittime==0)res=1;
	}
	return res;
}

//��ȡATK-ESP8266ģ�������״̬
//����ֵ:0,δ����;1,���ӳɹ�.
u8 atk_8266_consta_check(void)
{
	u8 *p;
	u8 res;
	if(atk_8266_quit_trans())return 0;			//�˳�͸��
	atk_8266_send_cmd("AT+CIPSTATUS",":",50);	//����AT+CIPSTATUSָ��,��ѯ����״̬
	p=atk_8266_check_cmd("+CIPSTATUS:");
	res=*p;									//�õ�����״̬
	return res;
}

//ATK-ESP8266�˳�͸��ģʽ
//����ֵ:0,�˳��ɹ�;
//       1,�˳�ʧ��
u8 atk_8266_quit_trans(void)
{
	while((USART3->SR&0X40)==0);	//�ȴ����Ϳ�
	USART3->DR='+';
	delay_ms(15);					//���ڴ�����֡ʱ��(10ms)
	while((USART3->SR&0X40)==0);	//�ȴ����Ϳ�
	USART3->DR='+';
	delay_ms(15);					//���ڴ�����֡ʱ��(10ms)
	while((USART3->SR&0X40)==0);	//�ȴ����Ϳ�
	USART3->DR='+';
	delay_ms(500);					//�ȴ�500ms
	return atk_8266_send_cmd("AT","OK",20);//�˳�͸���ж�.
}

//ATK-ESP8266ģ�����������
void atk_8266_test(void)
{
	// u8 timex;
	printf("ATK-ESP8266 WIFIģ�����");
	while(atk_8266_send_cmd("AT","OK",20))//���WIFIģ���Ƿ�����
	{
//		atk_8266_quit_trans();//�˳�͸��
//			atk_8266_send_cmd("AT+CIPMODE=0","OK",200);  //�ر�͸��ģʽ	
		printf("δ��⵽ģ��!!!");
		delay_ms(800);
		printf("��������ģ��...");
	}
		while(atk_8266_send_cmd("ATE0","OK",20));//�رջ���
		delay_ms(10);
		atk_8266_config();
		printf("\n\rwifi�������\n");
}

void  atk_8266_config(void)
{
		u8 *p;
		while(atk_8266_send_cmd("AT","OK",20))//���WIFIģ���Ƿ�����
		{
			LED2=!LED2;
			delay_ms(500);
		}
		while(atk_8266_send_cmd("ATE0","OK",20));//�رջ���
		delay_ms(100);
		atk_8266_send_cmd("AT+CWMODE=2","OK",20);
		atk_8266_send_cmd("AT+RST","OK",1000);
		sprintf((char*)p,"AT+CWSAP=\"%s\",\"%s\",1,4",wifiap_ssid,wifiap_password);
		atk_8266_send_cmd(p,"OK",1000);			
//	atk_8266_send_cmd("AT+CWSAP=\"ESP8266\",\"123456789\",1,4","OK",1000);
		atk_8266_send_cmd("AT+CIPMUX=1","OK",20);
//	printf("\n\r������ģʽ");
//		sprintf((char*)p,"AT+CIPSERVER=1,%d",portnum);    //����Ŀ��TCP������
//		atk_8266_send_cmd(p,"OK",200);
	atk_8266_send_cmd("AT+CIPSERVER=1,8086","OK",20);
//	printf("\n\r����TCP����ģʽ");
}
