#ifndef __WIFI_H_
#define __WIFI_H_

#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "string.h"
#include "usart3.h"

extern const u8* wifiap_ssid;		//WIFI AP SSID
extern const u8* wifiap_password; 	//WIFI AP √‹¬Î

u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
u8 atk_8266_quit_trans(void);
void atk_8266_test(void);	
void  atk_8266_config(void);
u8* atk_8266_check_cmd(u8 *str);
void atk_8266_at_response(u8 mode);
u8 atk_8266_send_data(u8 *data,u8 *ack,u16 waittime);
u8 atk_8266_consta_check(void);

#endif

