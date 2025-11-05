#include "bsp_key.h"
#include "Delay.h"
void KEY_GPIO_Config(void )
{
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);/*开启按键端口的时钟*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;//选择按键的引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//设置按键的引脚为上拉输入
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStructure);//使用结构体初始化按键
	
	GPIO_InitStructure.GPIO_Pin=KEY2_GPIO_PIN;//选择按键2的引脚
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStructure);//使用结构体初始化按键2
	
	GPIO_InitStructure.GPIO_Pin=KEY3_GPIO_PIN;//选择按键2的引脚
	GPIO_Init(KEY3_GPIO_PORT,&GPIO_InitStructure);//使用结构体初始化按键2
	
}

uint8_t KEY_Scan(void)
{
   uint8_t KeyNum = 0;
   if (GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN)== 0)
  {
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN)== 0);
		Delay_ms(20);
		KeyNum = 1;
  }
   if (GPIO_ReadInputDataBit(KEY2_GPIO_PORT, KEY2_GPIO_PIN)== 0)
    { 
	  Delay_ms(20);
		while (GPIO_ReadInputDataBit(KEY2_GPIO_PORT, KEY2_GPIO_PIN)== 0);
		Delay_ms(20);
		KeyNum = 2;
    }
		
	 if (GPIO_ReadInputDataBit(KEY3_GPIO_PORT, KEY3_GPIO_PIN)== 0)
    { 
	  Delay_ms(20);
		while (GPIO_ReadInputDataBit(KEY3_GPIO_PORT, KEY3_GPIO_PIN)== 0);
		Delay_ms(20);
		KeyNum = 3;
    }
		
 return KeyNum;
}
