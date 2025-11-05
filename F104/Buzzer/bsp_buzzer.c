#include "bsp_buzzer.h"
void BUZZER_GPIO_Config()
{
	RCC_APB2PeriphClockCmd(BUZZER_GPIO_CLK,ENABLE);//打开时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=BUZZER_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(BUZZER_GPIO_PORT,&GPIO_InitStructure);
}
