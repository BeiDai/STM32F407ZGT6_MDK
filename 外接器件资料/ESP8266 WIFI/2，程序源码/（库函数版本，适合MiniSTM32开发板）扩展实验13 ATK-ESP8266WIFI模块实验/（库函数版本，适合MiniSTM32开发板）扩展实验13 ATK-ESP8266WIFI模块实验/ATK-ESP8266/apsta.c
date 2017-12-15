#include "common.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//ATK-ESP8266 AP+STAģʽ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/4/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 


//ATK-ESP8266 AP+STAģʽ����
//���ڲ���TCP/UDP����
//����ֵ:0,����
//    ����,�������
u8 atk_8266_apsta_test(void)
{
	u8 netpro;
	u8 key=0;
	u8 timex=0; 
	u8 ipbuf[16]; 	//IP����
	u8 *p;
	u16 t=999;		//���ٵ�һ�λ�ȡ����״̬
	u8 res=0;
	u16 rlen=0;
	u8 constate=0;	//����״̬
	p=mymalloc(32);							//����32�ֽ��ڴ�
	atk_8266_send_cmd("AT+CWMODE=3","OK",50);		//����WIFI AP+STAģʽ
//	atk_8266_send_cmd("AT+RST","OK",20);		//����ģ�� 
//	delay_ms(1000);         //��ʱ2S�ȴ������ɹ�
//	delay_ms(1000);
//	delay_ms(1000);
	//����ģ��APģʽ��WIFI��������/���ܷ�ʽ/���룬�⼸���������Լ�ϲ������
	sprintf((char*)p,"AT+CWSAP=\"%s\",\"%s\",1,4",wifiap_ssid,wifiap_password);//�������߲���:ssid,����
	atk_8266_send_cmd(p,"OK",1000);					//����APģʽ����
	//�������ӵ���WIFI��������/���ܷ�ʽ/����,�⼸��������Ҫ�������Լ���·�������ý����޸�!! 
	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);//�������߲���:ssid,����
	atk_8266_send_cmd(p,"WIFI GOT IP",1000);						//����Ŀ��·�����������IP
	while(atk_8266_send_cmd("AT+CIFSR","STAIP",20));   //����Ƿ���STA IP
	while(atk_8266_send_cmd("AT+CIFSR","APIP",20));   //����Ƿ���AP IP
//	while((atk_8266_consta_check()-'2'));   //���IP
	LCD_Clear(WHITE);
	POINT_COLOR=RED;
	Show_Str(30,30,200,16,"ATK-ESP AP+STAģʽ����",16,0); 
	atk_8266_send_cmd("AT+CIPMUX=1","OK",50);   //0�������ӣ�1��������
	delay_ms(500);
	sprintf((char*)p,"AT+CIPSERVER=1,%s",(u8*)portnum);
	atk_8266_send_cmd(p,"OK",50);     //����Serverģʽ���˿ں�Ϊ8086
	delay_ms(500);
	atk_8266_send_cmd("AT+CIPSTO=1200","OK",50);     //���÷�������ʱʱ��
	
PRESTA:
	netpro=atk_8266_netpro_sel(50,30,(u8*)ATK_ESP8266_CWMODE_TBL[0]);	//AP+STAģʽ����ģʽѡ��
	if(netpro&0X02)   //STA UDP
	{
				LCD_Clear(WHITE);
				POINT_COLOR=RED;
				Show_Str_Mid(0,30,"ATK-ESP WIFI-STA����",16,240); 
				Show_Str(30,50,200,16,"��������ATK-ESPģ��,���Ե�...",12,0);
				if(atk_8266_ip_set("WIFI-STAԶ��UDP IP����","UDPģʽ",(u8*)portnum,ipbuf))goto PRESTA;	//IP����
				sprintf((char*)p,"AT+CIPSTART=0,\"UDP\",\"%s\",%s",ipbuf,(u8*)portnum);    //����Ŀ��UDP������,��ID�ţ�STAģʽ��Ϊ0
				LCD_Clear(WHITE);
				Show_Str_Mid(0,30,"ATK-ESP WIFI-STA����",16,240); 
				Show_Str(30,50,200,16,"��������ATK-ESPģ��,���Ե�...",12,0);
				atk_8266_send_cmd(p,"OK",200);
				netpro=atk_8266_mode_cofig(netpro);     //APģʽ����ģʽ����			
	}
	else     //TCP
	{
		if(netpro&0X01)     //STA TCP Client  
		{
			LCD_Clear(WHITE);
			POINT_COLOR=RED;
			Show_Str_Mid(0,30,"ATK-ESP WIFI-STA ����",16,240); 
			Show_Str(30,50,200,16,"��������ATK-ESPģ��,���Ե�...",12,0);
			if(atk_8266_ip_set("WIFI-STA Զ��IP����",(u8*)ATK_ESP8266_WORKMODE_TBL[netpro],(u8*)portnum,ipbuf))goto PRESTA;	//IP����
			sprintf((char*)p,"AT+CIPSTART=0,\"TCP\",\"%s\",%s",ipbuf,(u8*)portnum);    //����Ŀ��TCP������,��ID�ţ�STAģʽ��Ϊ0
			while(atk_8266_send_cmd(p,"OK",200))
			{
				LCD_Clear(WHITE);
				POINT_COLOR=RED;
				Show_Str_Mid(0,40,"WK_UP:������ѡ",16,240);
				Show_Str(30,80,200,12,"ATK-ESP ����UDPʧ��",12,0); //����ʧ��	 
				key=KEY_Scan(0);
				if(key==WKUP_PRES)goto PRESTA;
			}	
			netpro=atk_8266_mode_cofig(netpro);     //APģʽ����ģʽ����	
		}
		else netpro=atk_8266_mode_cofig(netpro);     //TCP SERVER��������
	}
	
	
	
	LCD_Clear(WHITE);
	POINT_COLOR=RED;
	Show_Str_Mid(0,30,"ATK-ESP WIFI-STA+AP ����",16,240);
	Show_Str(15,50,200,16,"��������ATK-ESPģ��,���Ե�...",12,0);			
	LCD_Fill(15,50,239,50+12,WHITE);			//���֮ǰ����ʾ
	Show_Str_Mid(0,50,"WK_UP:�˳� KEY0:ID0���� KEY1:ID1����",12,240);
	LCD_Fill(15,80,239,80+12,WHITE);
	atk_8266_get_ip(15,65);//STA+APģʽ,��ȡ IP,����ʾ	
	
	
	Show_Str(15,95,200,12,"����״̬:",12,0); 		//����״̬
	Show_Str(15,110,200,12,"STAģʽ:",12,0); 		//STA����״̬
	Show_Str(120+15,110,200,12,"APģʽ:",12,0); 		//AP����״̬
	Show_Str(15,125,200,12,"��������:",12,0); 	//��������
	Show_Str(15,140,200,12,"��������:",12,0);	//��������
	atk_8266_wificonf_show(15,195,"������·�������߲���Ϊ:",(u8*)wifista_ssid,(u8*)wifista_encryption,(u8*)wifista_password);
	POINT_COLOR=BLUE;		
	Show_Str(48+15,110,200,12,(u8*)ATK_ESP8266_WORKMODE_TBL[netpro&0X03],12,0); 		//STA����״̬
	Show_Str(162+15,110,200,12,(u8*)ATK_ESP8266_WORKMODE_TBL[netpro>>4],12,0); 		//AP����״̬
	USART2_RX_STA=0;
	while(1)
	{
		key=KEY_Scan(0);
		if(key==WKUP_PRES)			//WK_UP �˳�����		 
		{ 
			res=0;	
			break;												 
		}
		else if(key==KEY0_PRES)	//KEY0 ��ID0�������� 
		{
			  sprintf((char*)p,"ATK-8266ģ��ID0������%02d\r\n",t/10);//��������
				Show_Str(15+54,125,200,12,p,12,0);
				atk_8266_send_cmd("AT+CIPSEND=0,25","OK",200);  //����ָ�����ȵ�����
				delay_ms(200);
				atk_8266_send_data(p,"OK",100);  //����ָ�����ȵ�����
				timex=100;
		}
		else if(key==KEY1_PRES)	//KEY1 ��ID1�������� 
		{
			  sprintf((char*)p,"ATK-8266ģ��ID1������%02d\r\n",t/10);//��������
				Show_Str(15+54,125,200,12,p,12,0);
				atk_8266_send_cmd("AT+CIPSEND=1,25","OK",200);  //����ָ�����ȵ�����
				delay_ms(200);
				atk_8266_send_data(p,"OK",100);  //����ָ�����ȵ�����
				timex=100;
		}
			
	 if(timex)timex--;
 	 if(timex==1)LCD_Fill(30+54,125,239,122,WHITE);
	 t++;
	 delay_ms(10);
	 if(USART2_RX_STA&0X8000)		//���յ�һ��������
	{ 
		rlen=USART2_RX_STA&0X7FFF;	//�õ����ν��յ������ݳ���
		USART2_RX_BUF[rlen]=0;		//��ӽ����� 
		printf("%s",USART2_RX_BUF);	//���͵�����   
		sprintf((char*)p,"�յ�%d�ֽ�,��������",rlen);//���յ����ֽ��� 
		LCD_Fill(15+54,140,239,130,WHITE);
		POINT_COLOR=BRED;
		Show_Str(15+54,140,156,12,p,12,0); 			//��ʾ���յ������ݳ���
		POINT_COLOR=BLUE;
		LCD_Fill(15,155,239,319,WHITE);
		Show_Str(15,155,180,190,USART2_RX_BUF,12,0);//��ʾ���յ�������  
		USART2_RX_STA=0;
		if(constate!='+')t=1000;		//״̬Ϊ��δ����,������������״̬
		else t=0;                   //״̬Ϊ�Ѿ�������,10����ټ��
	}  
	if(t==1000)//����10����û���յ��κ�����,��������ǲ��ǻ�����.
	{
		LCD_Fill(15+54,125,239,138,WHITE);
//		LCD_Fill(15+54,95,120,110,WHITE);
		constate=atk_8266_consta_check();//�õ�����״̬
		if(constate=='+')Show_Str(15+54,95,200,12,"���ӳɹ�",12,0);  //����״̬
		else Show_Str(15+54,95,200,12,"����ʧ��",12,0); 	 
		t=0;
	}
	if((t%20)==0)LED0=!LED0;
	atk_8266_at_response(1);
}
	myfree(p);		//�ͷ��ڴ� 
	return res;		
} 


























