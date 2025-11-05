#ifndef __BSP__KEY_H
#define __BSP__KEY_H
#include "stm32f10x.h"
/*定义KEY连接的GPIO端口,用户只需要修改下面的代码即可改变控制的KEY引脚*/

#define KEY1_GPIO_PORT  GPIOB /*GPIO端口*/
#define KEY1_GPIO_CLK   RCC_APB2Periph_GPIOB /*GPIO端口时钟*/
#define KEY1_GPIO_PIN   GPIO_Pin_15 /*对应PIN脚*/

#define KEY2_GPIO_PORT  GPIOB /*GPIO端口*/
#define KEY2_GPIO_CLK   RCC_APB2Periph_GPIOB /*GPIO端口时钟*/
#define KEY2_GPIO_PIN   GPIO_Pin_14 /*对应PIN脚*/

#define KEY3_GPIO_PORT  GPIOB /*GPIO端口*/
#define KEY3_GPIO_CLK   RCC_APB2Periph_GPIOB /*GPIO端口时钟*/
#define KEY3_GPIO_PIN   GPIO_Pin_13 /*对应PIN脚*/

void KEY_GPIO_Config(void );

u8 KEY_Scan(void);

#endif 
