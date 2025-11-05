#include "bsp_timer_motor.h"

static void GPIO_Config(void) // 定时器复用口进行初始化
{
    GPIO_InitTypeDef gpio_instruct;
    RCC_APB2PeriphClockCmd(MOTOR_PWMA_GPIO_CLK, ENABLE); // 使能GPIO时钟
    // 初始化GPIO
    gpio_instruct.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_instruct.GPIO_Pin = MOTOR_PWMA_GPIO_PIN;
    gpio_instruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOTOR_PWMA_GPIO_PORT, &gpio_instruct);
}

static void TIM_Motor_Config(void)
{
    TIM_TimeBaseInitTypeDef tim_base_instruct;
    RCC_APB1PeriphClockCmd(TIM_MOTOR_RCC_CLK, ENABLE); // 使能TIMx时钟
    // 初始化TIMx时基单元
    tim_base_instruct.TIM_ClockDivision = TIM_CKD_DIV1;
    tim_base_instruct.TIM_CounterMode = TIM_CounterMode_Up;
    tim_base_instruct.TIM_Period = TIM_MOTOR_Period - 1;
    tim_base_instruct.TIM_Prescaler = TIM_MOTOR_Prescaler - 1;
    tim_base_instruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM_MOTOR,&tim_base_instruct);

    // 配置TIMx比较输出单元
    TIM_OCInitTypeDef tim_oc_instruct;
    tim_oc_instruct.TIM_OCMode = TIM_OCMode_PWM1;
    tim_oc_instruct.TIM_OutputState = TIM_OutputState_Enable;
    tim_oc_instruct.TIM_OutputNState = TIM_OutputNState_Disable;
    tim_oc_instruct.TIM_OCPolarity = TIM_OCPolarity_High;
    tim_oc_instruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
    tim_oc_instruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	  tim_oc_instruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
		tim_oc_instruct.TIM_Pulse = 0;
		TIM_OC2Init(TIM_MOTOR, &tim_oc_instruct);
		GPIO_Config();
		/* 使能TIMx */
		TIM_Cmd(TIM_MOTOR, ENABLE);
	}
static void Motor_Direction_GPIO_Config(void)   //方向控制GPIO,ENABLE);配置
{
				GPIO_InitTypeDef gpio_instruct;
				RCC_APB2PeriphClockCmd( MOTOR_DRIVER_AIN1_CLK|MOTOR_DRIVER_AIN2_CLK, ENABLE);
				//配置AIN1口
				gpio_instruct.GPIO_Mode = GPIO_Mode_Out_PP;
				gpio_instruct.GPIO_Pin = MOTOR_DRIVER_AIN1_PIN;
				gpio_instruct.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(MOTOR_DRIVER_AIN1_PORT, &gpio_instruct);
				//配置AIN2口
				gpio_instruct.GPIO_Pin = MOTOR_DRIVER_AIN2_PIN;
				GPIO_Init(MOTOR_DRIVER_AIN2_PORT, &gpio_instruct);
}

		/* 电机正转 */
void Motor_Forward_Direction(void)
{
				GPIO_SetBits(MOTOR_DRIVER_AIN2_PORT, MOTOR_DRIVER_AIN2_PIN);
				GPIO_ResetBits(MOTOR_DRIVER_AIN1_PORT, MOTOR_DRIVER_AIN1_PIN);
}

		/* 电机反转 */
void Motor_Backward_Direction(void)
{
				GPIO_SetBits(MOTOR_DRIVER_AIN1_PORT, MOTOR_DRIVER_AIN1_PIN);
				GPIO_ResetBits(MOTOR_DRIVER_AIN2_PORT, MOTOR_DRIVER_AIN2_PIN);
}
		//设置电机速度
void Motor_SetSpeed(int8_t Speed)
{
				if (Speed > 0) //正转
{
						if (Speed > 100) Speed = 100;
						Motor_Forward_Direction(); //设置正向
						TIM_SetCompare2(TIM_MOTOR, Speed);
}
				else //反转
{
						if (Speed < -100) Speed = -100;
						Motor_Backward_Direction();//设置反向
						TIM_SetCompare2(TIM_MOTOR, -Speed);
	}
}

void Motor_Control_Config()
{
				TIM_Motor_Config();
				Motor_Direction_GPIO_Config();
				Motor_SetSpeed(0);
}


