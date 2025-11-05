#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

/**
 * 串口1宏定义
 */
#define DEBUG_USARTx               USART1
#define DEBUG_USART_CLK            RCC_APB2Periph_USART1
#define DEBUG_USART_APBxClkCmd     RCC_APB2PeriphClockCmd
#define DEBUG_USART_BAUDRATE       115200

// USART GPIO 引脚宏定义
#define DEBUG_USART_GPIO_CLK       (RCC_APB2Periph_GPIOA)
#define DEBUG_USART_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd

#define DEBUG_USART_TX_GPIO_PORT   GPIOA
#define DEBUG_USART_TX_GPIO_PIN    GPIO_Pin_9

#define DEBUG_USART_RX_GPIO_PORT   GPIOA
#define DEBUG_USART_RX_GPIO_PIN    GPIO_Pin_10

//中断
#define DEBUG_IRQ                  USART1_IRQn
#define DEBUG_IRQHANDLER           USART1_IRQHandler

void USART_NVIC_Config(void);    //中断控制配置
void USART_Config(void);         //串口1配置

void Usart_SendByte( uint8_t ch); //发送1个字节数据
void Usart_SendString(uint8_t  *str); //发送字符串
void Usart_SendHalfWord( uint16_t ch); //发送16位数据
void Usart_SendArray(uint8_t *array, uint16_t num);//发送数组,发送8位数据的数组
void Usart_SendString_Lenth(uint8_t *str, uint32_t num); //发送指定长度的字符串

#endif /* _USART_H */

