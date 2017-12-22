# OLED使用经验

简述：项目使用的是2.42寸OLED，分辨率128*64，单色白，SPI四线通讯。
- 接线
- SSD1309驱动命令
- OLED初始化
- SSD驱动配置
- OLED功能函数
            -

### 一、接线

| 引脚 | 功能      | 接线 | STM32配置 |
| ---- | --------- | ---- | --------- |
| CS   | 片选      | PB_7 | OLED_CS   |
| DC   | 数据/命令 | PD_6 | OLED_RS   |
| RES  | 复位      | PD_7 | OLED_RST  |
| SDA  | 时钟线    | PC_6 | OLED_SCLK |
| SCL  | 数据线    | PC_7 | OLED_SDIN |

### 二、SSD驱动命令

1. 设置对比度

        OLED_WR_Byte(0xEF,OLED_CMD); //1~255;默认0X7F (亮度设置,越大越亮)

2. 关/开显示

        OLED_WR_Byte(0xAF,OLED_CMD); // AE/AF 关/开
3. 关/开电荷泵

        OLED_WR_Byte(0x8D,OLED_CMD); // 0x10~0x14
4. 设置页地址0~7

        B0~B7
5. 设置第八位高八位地址

        00~0F / 10~1F
### 三、OLED初始化

- 复位SSD1309
- 驱动IC初始化代码
- 开启显示
- 清0显存
- 开启显示

### 四、SSD驱动配置

    void OLED_Init(void)
    {
      GPIO_InitTypeDef  GPIO_InitStructure;

    	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD, ENABLE);//使能PORTA~E,PORTG时钟

    	//使用4线SPI 串口模式

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
      GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化

    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化

    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化

    	OLED_SDIN=1;
    	OLED_SCLK=1;

    	OLED_CS=1;
    	OLED_RS=1;

    	OLED_RST=0;
    	delay_ms(100);
    	OLED_RST=1;

    	OLED_WR_Byte(0xFD,OLED_CMD); //Command Lock
    	OLED_WR_Byte(0x12,OLED_CMD); //

    	OLED_WR_Byte(0xAE,OLED_CMD); //关闭显示
    	OLED_WR_Byte(0xD5,OLED_CMD); //设置时钟分频因子,震荡频率
    //	OLED_WR_Byte(80,OLED_CMD);   //[3:0],分频因子;[7:4],震荡频率
    	OLED_WR_Byte(0xA0,OLED_CMD); //

    	OLED_WR_Byte(0xA8,OLED_CMD); //设置驱动路数
    	OLED_WR_Byte(0X3F,OLED_CMD); //默认0X3F(1/64)
    	OLED_WR_Byte(0xD3,OLED_CMD); //设置显示偏移
    	OLED_WR_Byte(0X00,OLED_CMD); //默认为0

    	OLED_WR_Byte(0x40,OLED_CMD); //设置显示开始行 [5:0],行数.

    	OLED_WR_Byte(0x8D,OLED_CMD); //电荷泵设置
    	OLED_WR_Byte(0x14,OLED_CMD); //bit2，开启/关闭
    	OLED_WR_Byte(0x20,OLED_CMD); //设置内存地址模式
    	OLED_WR_Byte(0x02,OLED_CMD); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
    	OLED_WR_Byte(0xA1,OLED_CMD); //段重定义设置,bit0:0,0->0;1,0->127;
    //	OLED_WR_Byte(0xC0,OLED_CMD); //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
    	OLED_WR_Byte(0xC0,OLED_CMD); //Set COM Output Scan Direction / C8

    	OLED_WR_Byte(0xDA,OLED_CMD); //设置COM硬件引脚配置
    	OLED_WR_Byte(0x12,OLED_CMD); //[5:4]配置

    	OLED_WR_Byte(0x81,OLED_CMD); //对比度设置
    //	OLED_WR_Byte(0xEF,OLED_CMD); //1~255;默认0X7F (亮度设置,越大越亮)
    	OLED_WR_Byte(0xFF,OLED_CMD);

    	OLED_WR_Byte(0xD9,OLED_CMD); //设置预充电周期
    //	OLED_WR_Byte(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
    	OLED_WR_Byte(0x82,OLED_CMD); //

    	OLED_WR_Byte(0xDB,OLED_CMD); //设置VCOMH 电压倍率
    //	OLED_WR_Byte(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
    	OLED_WR_Byte(0x34,OLED_CMD);

    	OLED_WR_Byte(0xA4,OLED_CMD); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
    	OLED_WR_Byte(0xA6,OLED_CMD); //设置显示方式;bit0:1,反相显示;0,正常显示
    	OLED_WR_Byte(0xAF,OLED_CMD); //开启显示

    	OLED_Clear();
    }

### OLED功能函数
    - void OLED_WR_Byte(u8 dat,u8 cmd);    //发送命令/数据给OLED

    - void OLED_Display_On(void);      //开启OLED屏

    - void OLED_Display_Off(void);     //关闭OLED屏

    - void OLED_Refresh_Gram(void);  //刷新驱动缓存		

    - void OLED_Init(void);     //OLED初始化

    - void OLED_Clear(void);    //OLED清屏

    - void OLED_DrawPoint(u8 x,u8 y,u8 t);    //画点函数

    - void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);    //填充函数

    - void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);   //显示字符

    - void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);    //显示数字

    - void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);	  //显示字符串
