#ifndef __BSP__BUZZER_H
#define __BSP__BUZZER_H
#include "stm32f10x.h"
/*定义BUZZER连接的GPIO端口，用户只需要修改下面的代码即可改变控制的BUZZER引脚*/
#define BUZZER_GPIO_PORT GPIOB /*GPIO端口*/
#define BUZZER_GPIO_CLK  RCC_APB2Periph_GPIOB /*GPIO端口时钟*/
#define BUZZER_GPIO_PIN  GPIO_Pin_9 /*对应PIN脚*/

#define BUZZER_OFF GPIO_ResetBits(BUZZER_GPIO_PORT,BUZZER_GPIO_PIN);//蜂鸣器不工作
#define BUZZER_ON GPIO_SetBits(BUZZER_GPIO_PORT,BUZZER_GPIO_PIN);//蜂鸣器工作
#define BUZZER_TOGGLE GPIO_WriteBit(BUZZER_GPIO_PORT,BUZZER_GPIO_PIN,(BitAction)(1-GPIO_ReadOutputDataBit(BUZZER_GPIO_PORT,BUZZER_GPIO_PIN)))

void BUZZER_GPIO_Config(void);

#endif 
