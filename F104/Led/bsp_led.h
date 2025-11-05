#ifndef __BSP_GPIO_LED_H
#define __BSP_GPIO_LED_H

#include "stm32f10x.h"

/* 定义 LED 连接的GPIO端口，用户只需要修改下面的代码即可改变控制的LED引脚 */
//LED1
#define R_LED_GPIO_PORT         GPIOB                /* GPIO端口 */
#define R_LED_GPIO_CLK          RCC_APB2Periph_GPIOB  /* GPIO端口时钟 */
#define R_LED_GPIO_PIN          GPIO_Pin_1             /* 对应PIN脚 */

#define R_LED_OFF   GPIO_ResetBits(R_LED_GPIO_PORT, R_LED_GPIO_PIN)  //熄灭灯
#define R_LED_ON  GPIO_SetBits(R_LED_GPIO_PORT, R_LED_GPIO_PIN)    //点亮灯

//信号灯翻转
#define R_LED_TOGGLE  GPIO_WriteBit(R_LED_GPIO_PORT, R_LED_GPIO_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(R_LED_GPIO_PORT,R_LED_GPIO_PIN)))

//LED2（注释部分，未启用）
// #define G_LED_GPIO_PORT         GPIOB                /* GPIO端口 */
// #define G_LED_GPIO_CLK          RCC_APB2Periph_GPIOB  /* GPIO端口时钟 */
// #define G_LED_GPIO_PIN          GPIO_Pin_5             /* 对应PIN脚 */

// #define G_LED_ON   GPIO_ResetBits(G_LED_GPIO_PORT, G_LED_GPIO_PIN)  //点亮灯
// #define G_LED_OFF  GPIO_SetBits(G_LED_GPIO_PORT, G_LED_GPIO_PIN)    //熄灭灯

// //信号灯翻转
// #define G_LED_TOGGLE  GPIO_WriteBit(G_LED_GPIO_PORT, G_LED_GPIO_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(G_LED_GPIO_PORT, G_LED_GPIO_PIN)))

//LED3（注释部分，未启用）
// #define B_LED_GPIO_PORT         GPIOB                /* GPIO端口 */
// #define B_LED_GPIO_CLK          RCC_APB2Periph_GPIOB  /* GPIO端口时钟 */
// #define B_LED_GPIO_PIN          GPIO_Pin_8             /* 对应PIN脚 */

// #define B_LED_ON   GPIO_ResetBits(B_LED_GPIO_PORT, B_LED_GPIO_PIN)  //点亮灯
// #define B_LED_OFF  GPIO_SetBits(B_LED_GPIO_PORT, B_LED_GPIO_PIN)    //熄灭灯

// //信号灯翻转
// #define B_LED_TOGGLE  GPIO_WriteBit(B_LED_GPIO_PORT, B_LED_GPIO_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(B_LED_GPIO_PORT, B_LED_GPIO_PIN)))

void LED_GPIO_Config(void);

#endif /* __BSP_GPIO_LED_H */
