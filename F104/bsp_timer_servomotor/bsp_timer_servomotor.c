#include "bsp_timer_servomotor.h"

static void GENERAL_TIM_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 输出比较通道3 GPIO 初始化
    RCC_APB2PeriphClockCmd(GENERAL_TIM_CH3_GPIO_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GENERAL_TIM_CH3_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GENERAL_TIM_CH3_PORT, &GPIO_InitStructure);
}

static void GENERAL_TIM_Mode_Config(void)
{
    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE); // 开启定时器时钟,即内部时钟CK_INT=72M

    /*-------------------------时基结构体初始化-------------------------*/
    // 配置周期，这里配置为100K
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    // 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period-1;
    // 驱动CNT计数器的时钟 = Fck_int/(psc+1)
    TIM_TimeBaseStructure.TIM_Prescaler=GENERAL_TIM_Prescaler-1;
    // 时钟分频因子 ，配置死区时间需要用到
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    // 计数器计数模式，设置为向上计数
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    // 重复计数器的值，没用到不用管
    TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    // 初始化定时器
    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

    /*-------------------------输出比较结构体初始化-------------------------*/
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    // 配置为PWM模式1
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    // 输出使能
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    // 输出通道电平极性配置
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    // 输出比较通道3
    TIM_OCInitStructure.TIM_Pulse = 0.5/20.0*GENERAL_TIM_Period; // 占空比配置
    TIM_OC3Init(GENERAL_TIM, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);

    // 使能计数器
    TIM_Cmd(GENERAL_TIM, ENABLE);
}

void GENERAL_TIM_Init(void)
{
    GENERAL_TIM_GPIO_Config();
    GENERAL_TIM_Mode_Config();
}

/**
 * @brief 设置舵机占空比
 * @param angle: 占空比，(0.5/20.0*PWM_PERIOD_COUNT 到 2.5/20.0*PWM_PERIOD_COUNT)
 * @retval 无
 */
void set_steering_gear_dutyfactor(uint16_t dutyfactor)
{
    #if 1
    {
			/* 对超过范围的占空比进行边界处理 */
        dutyfactor = 0.5 / 20.0*GENERAL_TIM_Period > dutyfactor ? 0.5/20.0*GENERAL_TIM_Period : dutyfactor;
        dutyfactor = 2.5 / 20.0*GENERAL_TIM_Period < dutyfactor ? 2.5/20.0*GENERAL_TIM_Period : dutyfactor;
    }
 #endif
		
    TIM_SetCompare3(TIM3, dutyfactor);
}

/**
 * @brief 设置舵机角度
 * @param angle_temp: 角度，(0 到 180（舵机为0°-180°）)
 * @retval 无
 */
void set_steering_gear_angle(uint16_t angle_temp)
{
    angle_temp = (0.5 + angle_temp / 180.0 * (2.5 - 0.5)) / 20.0 * GENERAL_TIM_Period;   // 计算角度对应的占空比
	
    set_steering_gear_dutyfactor(angle_temp);    // 设置占空比
}
