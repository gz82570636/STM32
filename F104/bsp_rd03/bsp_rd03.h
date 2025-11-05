#ifndef __BSP__RD03__H__
#define __BSP__RD03__H__

#include "stm32f10x.h"
#include "stdio.h"
#include "bsp_usart3.h"
#include "bsp_usart1.h"

#define RD03_RUNNING_MODE 0x00000064

typedef struct
{
    uint8_t head[4]; //头部数据
    uint16_t data_size; //数据大小
    uint8_t body_state; //人体状态(有人或无人)
    uint8_t body_range; //人体范围
    uint8_t range_gate_energy[32];//
    uint8_t tail[4]; //尾部数据
    uint16_t rd03_firmware_protocol_version;//协议版本号
    uint16_t rd03_firmware_buffer_size;//缓冲器大小
}RD03_DataTypeDef;

extern RD03_DataTypeDef rd03data;//定义一个雷达数据的结构体

uint8_t RD03_DataHandler(uint32_t mode, USART_DataTypeDef* rx_data_buff); //雷达数据处理函数
uint8_t Rd03_Run_ModeData(USART_DataTypeDef* rx_data_buff); //向串口1发送接收的数据
uint32_t Check_RD03_DataMode(USART_DataTypeDef* rx_data_buff); //检测雷达数据模式
void Rd03_buff_Reset(USART_DataTypeDef* rx_data_buff); //缓冲器清零
void Usart_Task_Reset(USART_DataTypeDef* rx_data_buff); //串口任务复位
void Usart_Task_Init(void); //串口任务初始化
void Rd03_Task(USART_DataTypeDef* rx_data_buff); //雷达任务，完成信号灯的亮灭

#endif

