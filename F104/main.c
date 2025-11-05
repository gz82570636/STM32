//#include "stm32f10x.h"
//#include "bsp_led.h"
//#include "bsp_key.h"
//#include "bsp_oled.h"
//#include "bsp_dht11.h"
//#include "bsp_timer_servomotor.h"
//#include "bsp_timer_motor.h"
//#include "bsp_photoresistor.h"
//u8 Key_Num=0; //定义按键值

//extern __IO uint16_t ADC_ConvertedValue;

//int main(void)
//{
//    LED_GPIO_Config(); //LED灯初始化
//    KEY_GPIO_Config();//EO
//    GENERAL_TIM_Init();//定时器3初始化
//    Motor_Control_Config();//直流电机控制初始化
//    PhotoResistor_Init();//光敏传感器初始化
//    OLED_Init();
//    OLED_Clear();//清屏
//    while(1)
//    {
//        Key_Num=KEY_Scan();//扫描键值
//        OLED_ShowNum(1,1,ADC_ConvertedValue,4);

//        switch(Key_Num)
//        {
//					
//					
//        case 1:
//            set_steering_gear_angle(90);
//            Motor_SetSpeed(0);
//            break;
//        case 2:
//            Motor_SetSpeed(50);
//           set_steering_gear_angle(180);
//            break;
//        case 3:
//            Motor_SetSpeed(-50);
//            set_steering_gear_angle(0);
//            break;
//        default:
//            break;
//        }
//        Delay_ms(100); // 延时100ms
//    }
//}


#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_oled.h"
#include "bsp_dht11.h"
#include "bsp_timer_servomotor.h"
#include "bsp_timer_motor.h"
#include "bsp_photoresistor.h"
#include "stdio.h"
#include "bsp_usart1.h"
#include "bsp_usart3.h"
#include "bsp_rd03.h"
#include "delay.h"

u8 Key_Num = 0; //定义按键值
extern __IO uint16_t ADC_ConvertedValue;

int main()
{
    LED_GPIO_Config(); //LED灯初始化
    Usart_Task_Init();

    while (1)
    {
        Rd03_Task(&rd03_receive_data);
        Delay_ms(300);
    }
}


