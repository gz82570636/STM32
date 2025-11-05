#ifndef __BSP_MQ135_H
#define __BSP_MQ135_H

#include "stm32f10x.h"

// ADC 编号选择
#define ADC_APBxClock_FUN RCC_APB2PeriphClockCmd
#define ADCx ADC1
#define ADC_CLK RCC_APB2Periph_ADC1

// ADC GPIO宏定义
// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
#define ADC_GPIO_APBxClock_FUN RCC_APB2PeriphClockCmd
#define ADC_GPIO_CLK RCC_APB2Periph_GPIOA
#define ADC_PORT GPIOA
#define ADC_PIN GPIO_Pin_4
#define ADC_CHANNEL ADC_Channel_4

// ADC 中断相关宏定义
#define ADC_IRQ ADC1_2_IRQn
#define ADC_IRQHandler ADC1_2_IRQHandler

// DO 数字量GPIO宏定义
#define MQ135_GPIO_APBxClock_FUN RCC_APB2PeriphClockCmd
#define MQ135_GPIO_CLK RCC_APB2Periph_GPIOA
#define MQ135_PORT GPIOA 
#define MQ135_PIN GPIO_Pin_5

#define RL  1// 根据硬件原理图可知：RL = 1k */
#define R0  2/* MQ135在洁净空气中的阻值，官方数据手册没有给出，这是实验测试得出，想要 */
#define VC  5.0/* MQ135供电电压，根据实际供电修改，默认接5V */
#define A   4.17/* y=ax^b 的 a */
#define B   -2.28/* y=ax^b 的 b */

void MQ135_Init(void);
float MQ135_Get_PPM(void);

#endif /* __BSP_MQ135_H */
