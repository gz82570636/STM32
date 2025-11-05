#include "bsp_usart3.h"
USART_DataTypeDef rd03_receive_data = {0};

void RD03_USART_NVIC_Config(void)
{
    NVIC_InitTypeDef nvic_initstructure;
    nvic_initstructure.NVIC_IRQChannel = RD03_IRQ;
    nvic_initstructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_initstructure.NVIC_IRQChannelSubPriority = 0;
    nvic_initstructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_initstructure);
}

void RD03_USART_Config(void)
{
    // 打开串口GPIO的时钟
    RCC_APB2PeriphClockCmd(RD03_USART_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(RD03_USART_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    // 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = RD03_USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RD03_USART_TX_GPIO_PORT, &GPIO_InitStructure);
    // 将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = RD03_USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(RD03_USART_RX_GPIO_PORT, &GPIO_InitStructure);
    // 配置串口的工作参数
    USART_InitTypeDef USART_InitStructure;
    // 配置波特率
    USART_InitStructure.USART_BaudRate = RD03_USART_BAUDRATE;
    // 配置数据字长
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    // 配置停止位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    // 配置校验位
    USART_InitStructure.USART_Parity = USART_Parity_No;
    // 配置硬件流控制
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    // 配置工作模式，收发一起
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    // 完成串口的初始化配置
    USART_Init(RD03_USARTx, &USART_InitStructure);

    RD03_USART_NVIC_Config();
    USART_ITConfig(RD03_USARTx, USART_IT_RXNE, ENABLE);
    USART_ITConfig(RD03_USARTx, USART_IT_IDLE, ENABLE);

    // 使能串口
    USART_Cmd(RD03_USARTx, ENABLE);
}

/*************** 发送一个字符 *******************/
void RD03_Usart_SendByte(uint8_t ch)
{
    /* 发送一个字节数据到USART */
    USART_SendData(RD03_USARTx, ch);
    /* 等待发送数据寄存器为空 */
    while (USART_GetFlagStatus(RD03_USARTx, USART_FLAG_TXE) == RESET);
}

void RD03_Usart_SendArray(uint8_t *array, uint16_t num)
{
    uint8_t i;
    for (i = 0; i < num; i++)
    {
        RD03_Usart_SendByte(array[i]);
    }
		/* 等待发送完成 */
   while(USART_GetFlagStatus(RD03_USARTx,USART_FLAG_TC)==RESET);
}

/***************** 发送字符串 ***********************/
void RD03_Usart_SendString(uint8_t *str)
{
    unsigned int k = 0;
    do
    {
        RD03_Usart_SendByte(*(str + k));
        k++;
    } while (*(str + k) != '\0');
    /* 等待发送完成 */
    while (USART_GetFlagStatus(RD03_USARTx, USART_FLAG_TC) == RESET)
        {}
}

/***************** 发送一个16位数 ***********************/
void RD03_Usart_SendHalfWord(uint16_t ch)
{
    uint8_t temp_h, temp_l;
    /* 取出高八位 */
    temp_h = (ch & 0XFF00) >> 8;
    /* 取出低八位 */
    temp_l = ch & 0XFF;
    /* 发送高八位 */
    USART_SendData(RD03_USARTx, temp_h);
    while (USART_GetFlagStatus(RD03_USARTx, USART_FLAG_TXE) == RESET);
    /* 发送低八位 */
    USART_SendData(RD03_USARTx, temp_l);
    while (USART_GetFlagStatus(RD03_USARTx, USART_FLAG_TXE) == RESET);
}

void RD03_Usart_SendString_Length(uint8_t *str, uint32_t num)
{
    unsigned int k = 0;
    do
    {
        RD03_Usart_SendByte(*(str + k));
        k++;
    } while (k < num);
    /* 等待发送完成 */
    while (USART_GetFlagStatus(RD03_USARTx, USART_FLAG_TC) == RESET);
}






