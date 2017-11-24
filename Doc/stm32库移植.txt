———————
———————STM32Fxx文件库移植笔记————————

  1.下载官方库文件地址：http://www.st.com/zh/embedded-software/stm32-standard-peripheral-libraries.html?querycriteria=productId=LN1939

  2.固件库移植所需文件：

	1. STM32F4xx_DSP_StdPeriph_Lib_V1.8.0\Libraries\CMSIS\Include

    	   内核core_xx文件

	2.STM32F4xx_DSP_StdPeriph_Lib_V1.8.0\Libraries\CMSIS\Device\ST\STM32F4xx\Source\Templates\arm

	   启动文件startup_xx

	3.STM32F4xx_DSP_StdPeriph_Lib_V1.8.0\Libraries\STM32F4xx_StdPeriph_Driver

	   外设inc、src文件 ( stm32f4xx_fmc.c使用系列：stm32f42、stm32f43 )

	4.STM32F4xx_DSP_StdPeriph_Lib_V1.8.0\Libraries\CMSIS\Device\ST\STM32F4xx\Include

	  stm32f4xx、system_stm32f4xx；

	  STM32F4xx_DSP_StdPeriph_Lib_V1.8.0\Project\STM32F4xx_StdPeriph_Templates

	  main、stm32f4xx_conf、stm32f4xx_it、system_stm32f4xx；

  3.MDK建立工程导入文件，添加头文件目录，设置宏：STM32F40_41xxx,USE_STDPERIPH_DRIVER

  5.修改stm32f4xx_it.c 内容，删除#include "main.h",注释 void SysTick_Handler(void)；

  6.修改System_stm32f4xx.c #define PLL_M 8 ； 修改时钟频率；

    修改stm32f4xx.h #define HSE_VALUE ((uint32_t)8000000) ；

  7.添加SYSTEM文件，delay，sys，usart函数；

  8.USB串口调试，boot0，boot1： 3.3、0 ；复位 ；0、0 ；复位 ；0x08000000开始运行

  4.ST-Link调试 ：设置ST-Link Debugger 有SW JTAG ,SW 省接口，设置Flash Download 为对应芯片；

    ST-Link 设置boot0，boot1 ：0，0；