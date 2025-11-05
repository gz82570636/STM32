#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H

#include "stm32f10x.h"

//设置周期20ms，占空比为0.5ms-2ms变换的占空比的信号
#define 			GENERAL_TIM                TIM3
#define 			GENERAL_TIM_APBxClock_FUN   RCC_APB1PeriphClockCmd
#define 			GENERAL_TIM_CLK            RCC_APB1Periph_TIM3
#define 			GENERAL_TIM_Period         1000
#define 			GENERAL_TIM_Prescaler      1440
// TIM3 输出比较通道3
#define 		  GENERAL_TIM_CH3_GPIO_CLK   RCC_APB2Periph_GPIOB
#define 		  GENERAL_TIM_CH3_PORT       GPIOB
#define 		  GENERAL_TIM_CH3_PIN        GPIO_Pin_0

/***************************函数声明*******************************/
void GENERAL_TIM_Init(void);
void set_steering_gear_dutyfactor(uint16_t dutyfactor);
void set_steering_gear_angle(uint16_t angle);

#endif /* __BSP_GENERALTIME_H */

