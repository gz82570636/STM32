#ifndef __BSP_FIRE_H
#define __BSP_FIRE_H

#include "stm32f10x.h"

//ADC编号选择
#define Flame_ADC_APBxClock_FUN RCC_APB2PeriphClockCmd
#define Flame_ADCx ADC2
#define Flame_ADC_CLK RCC_APB2Periph_ADC2

// ADC GPIO宏定义
#define Flame_ADC_GPIO_APBxClock_FUN RCC_APB2PeriphClockCmd
#define Flame_ADC_GPIO_CLK RCC_APB2Periph_GPIOA
#define Flame_ADC_PORT GPIOA
#define Flame_ADC_PIN GPIO_Pin_2
#define Flame_ADC_CHANNEL ADC_Channel_2

// DO 数字量GPIO宏定义
#define Flame_ADC_APBxClock_FUN RCC_APB2PeriphClockCmd
#define Flame_GPIO_CLK RCC_APB2Periph_GPIOA
#define Flame_PORT GPIOA
#define Flame_PIN GPIO_Pin_3

void Flame_Init(void);
uint16_t Flame_AD_Value(void);

#endif
