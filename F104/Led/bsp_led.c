#include "bsp_led.h"

void LED_GPIO_Config()
{
  RCC_APB2PeriphClockCmd(R_LED_GPIO_CLK,ENABLE);//打开时钟
	
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
  GPIO_InitStructure.GPIO_Pin=R_LED_GPIO_PIN;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(R_LED_GPIO_PORT,&GPIO_InitStructure);
	
	R_LED_OFF;
	
}
