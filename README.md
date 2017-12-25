# 厦门理工学院创新创业项目

## 项目简介

### 项目经验
- [工作日志](/Project_Development_Experience/工作日志.md)
- [ESP8266使用经验](/Project_Development_Experience/ESP8266使用经验.md)
- [OLED使用经验](/Project_Development_Experience/OLED使用经验.md)
- [A4988驱动42步进电机](/Project_Development_Experience/A4988驱动42步进电机.md)
- [干簧管使用经验](/Project_Development_Experience/干簧管使用经验.md)
### 项目所用到材料

  1. 本项目主控芯片是STM32F407ZGT6

  2. 12V电源，12V转5V，3.3V电源转换模块，ESP8266WIFI模块，A4988+42步进电机，一个8口的药盒....

  3. 增加了干簧管传感器，APDS-9930姿态传感器，2.42寸OLED显示屏，SHT3x温湿度传感器。

### 现阶段项目实现的功能

1. 实现手机TCP测试软件，输入密码接入名为‘ESP8266’的WiFi，IP：194.168.4.1 port：8086

 2. 通过干簧管初始化1号药盒的位置，手机端发送 1-8 控制药盒到转到 1-8 的位置，OLED显示药盒号数

### 后期目标

1. 增加一个OLED显示屏显示温湿度，时间

2. 增加语音模块实现语音提醒功能

3. 手机APP开发，实现指令的发送，用药数据的处理分析

4. 设计原理图，用CAD画出电路板

### 项目原理图

   ![原理图](/Project_Image_Date/药盒工程图.jpg)

------
##### 1. 药盒初始化到1号位置
-----

  ![药盒初始化](/Project_Image_Date/初始化到1号.jpg)

----
##### 2. 手机发送控制命令
------

  ![手机控制命令](/Project_Image_Date/手机控制.png)

-----
##### 3. 药盒执行转到5号位置
-----

  ![药盒执行](/Project_Image_Date/药盒控制.jpg)
