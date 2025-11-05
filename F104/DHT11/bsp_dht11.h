#ifndef  BSP_DHT11_H
#define  BSP_DHT11_H

#include "stm32f10x.h"
#include "Delay.h"

// DHT11数据类型定义
typedef struct
{
    uint8_t humi_int;    // 湿度的整数部分
    uint8_t humi_deci;   // 湿度的小数部分
    uint8_t temp_int;    // 温度的整数部分
    uint8_t temp_deci;   // 温度的小数部分
    uint8_t check_sum;   // 校验和
} DHT11_Data_TypeDef;

#define DHT11_GPIO_CLK    RCC_APB2Periph_GPIOB
#define DHT11_GPIO_PORT   GPIOB
#define DHT11_GPIO_PIN    GPIO_Pin_0

#define DHT11_Dout_0      GPIO_ResetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN) // 引脚输出0
#define DHT11_Dout_1      GPIO_SetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN)  // 引脚输出1
#define DHT11_Dout_IN()   GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) // 读输入信号

// 函数声明
void DHT11_Init(void);
uint8_t DHT11_Read_TempAndHumidity(DHT11_Data_TypeDef *DHT11_Data);

#endif
