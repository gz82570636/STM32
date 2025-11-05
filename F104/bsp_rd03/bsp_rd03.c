/*rd03通信协议 */
#include "bsp_rd03.h"
#include "string.h"
#include "bsp_led.h"

RD03_DataTypeDef rd03data;  //定义雷达数据

//清空接收Buff，准备接收反馈数据
void Rd03_buff_Reset(USART_DataTypeDef *rx_data_buff)
{
    memset(rx_data_buff->data, 0, rx_data_buff->len);
    rx_data_buff->flag = 0;
    rx_data_buff->len = 0;
}

/* RD03的数据处理函数
mode:RD03当前的工作模式
rx_data_buff:接收数据的缓冲区
返回值：0：检测无人 1：检测有人 其他：不合法数据
*/
uint8_t RD03_DataHandler(uint32_t mode, USART_DataTypeDef* rx_data_buff)
{
    if (mode == RD03_RUNNING_MODE)
    {
        return Rd03_Run_ModeData(rx_data_buff);
    }
    return 2;
}

//检查RD03的数据接收包的类型，数据包类型( 0xffffffff 是错误的返回值)
uint32_t Check_RD03_DataMode(USART_DataTypeDef* rx_data_buff)
{
    char run_mode_data_head_temp0[] = "ON";
    char run_mode_data_head_temp1[] = "OFF";
    char* p_check_rd03_data_mode_temp;
    p_check_rd03_data_mode_temp = (char*)rx_data_buff->data;
    uint32_t return_value = 0xffffffff;

    if (0x00 == strstr((char*)rx_data_buff->data, (char*)run_mode_data_head_temp0) - p_check_rd03_data_mode_temp)
    {
        return_value = RD03_RUNNING_MODE;
    }
    else if (0x00 == strstr((char*)rx_data_buff->data, (char*)run_mode_data_head_temp1) - p_check_rd03_data_mode_temp)
    {
        return_value = RD03_RUNNING_MODE;
    }
    return return_value;
}

//运行模式数据
uint8_t Rd03_Run_ModeData(USART_DataTypeDef* rx_data_buff)
{
    if (0x00 == (memcmp(rx_data_buff->data, "ON", strlen("ON"))))//字符串比较，雷达检测到有人
    {
        Usart_SendString((uint8_t*)"ON ");
        Usart_SendString((uint8_t*)rx_data_buff->data + strlen("ON") + 2);
        Usart_SendString((uint8_t*)"有人--距离(cm) 0x");
        Usart_SendString((uint8_t*)rx_data_buff->data + strlen("ON Range") + 2);
        return 1;
    }
    else if (0x00 == (memcmp(rx_data_buff->data, "OFF", strlen("OFF"))))//字符串比较，雷达检测到无人
    {
        Usart_SendString((uint8_t*)"OFF ");
        Usart_SendString((uint8_t*)"无人 ");
        return 0;
    }
    return 2;//用于填充数据，无实际作用
}

//Usart任务配置复位
void Usart_Task_Reset(USART_DataTypeDef* rx_data_buff)
{
    memset(rx_data_buff->data, 0, rx_data_buff->len);
    rx_data_buff->flag = 0;
    rx_data_buff->len = 0;
}

//串口任务初始化
void Usart_Task_Init(void)
{
    USART_Config(); //串口1初始化
    RD03_USART_Config();//串口3初始化
    Usart_Task_Reset(&rd03_receive_data);
}

//Rd03任务
void Rd03_Task(USART_DataTypeDef* rx_data_buff)//B与MCU之间的交互
{
    if (rx_data_buff->flag == 1)
    {
        Usart_SendString((uint8_t*)"<RD03->MCU>");//转发给PC
        switch (RD03_DataHandler(Check_RD03_DataMode(rx_data_buff), rx_data_buff))
        {
            case 0:
                R_LED_OFF;
                break;
            case 1:
                R_LED_ON;
                break;
            default:
                break;
        }
				Usart_Task_Reset(rx_data_buff);
    }  
}


