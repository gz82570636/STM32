#ifndef __NB_
#define __NB_

#include <stm32f0xx.h>

#define RECVTIMEOUT 100 //每100毫秒我们查一次这个数据

typedef enum {
    SUCCESS_REC = 0,
    TIME_OUT,//超时
    NO_REC,//没有读
    ERROR_REC//读取错误
} ATStatus;

typedef enum {
    NB_IDILE = 0,//空闲状态
	NB_SEND,//发送状态
    NB_WAIT//等待
    
} NB_TaskStatus;//NB的任务状态

/**
 * @brief AT指令索引枚举定义
 * 
 * 该枚举定义了NB-IoT模块通信过程中使用的AT指令执行顺序，
 * 每个枚举值对应一个特定的AT指令操作步骤。
 * 主要用于控制AT指令的发送流程和状态跟踪。
 */
typedef enum {
    AT_NRB = 0,     ///< 发送AT+NRB指令（模块重启）
    AT_CSQ,         ///< 发送AT+CSQ指令（查询信号质量）
    AT_CGPADDR,     ///< 发送AT+CGPADDR指令（查询PDP地址）
    AT_NSOCR,       ///< 发送AT+NSOCR指令（创建Socket）
    AT_NSOCO,       ///< 发送AT+NSOCO指令（Socket连接）
    AT_NNMI,        ///< 发送AT+NNMI指令（设置数据接收模式）
    AT_NSORF,       ///< 发送AT+NSORF指令（接收数据）
    AT_NSOSD,       ///< 发送AT+NSOSD指令（发送数据）
    AT_NSOCL        ///< 发送AT+NSOCL指令（关闭Socket）
} ATCMD_index;

typedef struct {
    uint8_t ATSendStr[256];  //发送的AT指令字符串
		uint8_t ATRecStr[256];   //期望接收的AT回应字符串
    uint16_t TimeOut;   //等待超时时间
    ATStatus AtStat;    //发送AT指令之后的状态
    uint8_t retryNum;   //命令重试次数
} ATCMD_str;

void NB_init();
void NB_Task();
#endif

