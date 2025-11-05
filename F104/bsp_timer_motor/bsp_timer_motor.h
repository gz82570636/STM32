#ifndef __BSP_TIMER_MOTOR_H
#define __BSP_TIMER_MOTOR_H

#include "stm32f10x.h"

#define TIM_MOTOR               TIM2
#define TIM_MOTOR_RCC_CLK       RCC_APB1Periph_TIM2
#define TIM_MOTOR_Period        100
#define TIM_MOTOR_Prescaler     36

#define MOTOR_PWMA_CHANNEL      TIM_Channel_2

#define MOTOR_PWMA_GPIO_CLK     RCC_APB2Periph_GPIOA
#define MOTOR_PWMA_GPIO_PORT    GPIOA
#define MOTOR_PWMA_GPIO_PIN     GPIO_Pin_1

#define MOTOR_DRIVER_AIN1_CLK   RCC_APB2Periph_GPIOA
#define MOTOR_DRIVER_AIN1_PORT  GPIOA
#define MOTOR_DRIVER_AIN1_PIN   GPIO_Pin_4

#define MOTOR_DRIVER_AIN2_CLK   RCC_APB2Periph_GPIOA
#define MOTOR_DRIVER_AIN2_PORT  GPIOA
#define MOTOR_DRIVER_AIN2_PIN   GPIO_Pin_5

void Motor_Direction_GPIO_Config(void);
void Motor_Forward_Direction(void);
void Motor_Backward_Direction(void);
void Motor_Control_Config(void);
void Motor_SetSpeed(int8_t Speed);

#endif
