#ifndef __BSP__USART3__H__
#define __BSP__USART3__H__
#include "stm32f10x.h"
#include "stdio.h"
#define DATA_SIZE 2048

typedef struct
{
    uint32_t flag;
    uint32_t len;
    uint8_t data[DATA_SIZE];
} USART_DataTypeDef;

extern USART_DataTypeDef rd03_receive_data; //RD03接收的数据

#define RD03_USARTx               USART3
#define RD03_USART_CLK            RCC_APB1Periph_USART3
#define RD03_USART_BAUDRATE       115200

#define RD03_IRQ                  USART3_IRQn
#define RD03_IRQHANDLER           USART3_IRQHandler

// USART GPIO 引脚宏定义
#define RD03_USART_GPIO_CLK       RCC_APB2Periph_GPIOB
#define RD03_USART_TX_GPIO_PORT   GPIOB
#define RD03_USART_TX_GPIO_PIN    GPIO_Pin_10
#define RD03_USART_RX_GPIO_PORT   GPIOB
#define RD03_USART_RX_GPIO_PIN    GPIO_Pin_11

void RD03_USART_NVIC_Config(void);
void RD03_USART_Config(void);
void RD03_Usart_SendByte(uint8_t ch);
void RD03_Usart_SendArray(uint8_t *array, uint16_t num);
void RD03_Usart_SendString(uint8_t *str);
void RD03_Usart_SendHalfWord(uint16_t ch);
void RD03_Usart_SendString_Lenth(uint8_t *str, uint32_t num);

#endif


