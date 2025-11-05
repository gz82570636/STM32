#include "adc.h"         // ADC模数转换器驱动头文件
#include "nbdriver.h"    // NB-IoT通信模块驱动头文件

#define ADC_INTERVAL 3 * 1000    // ADC采样间隔：3秒（转换成毫秒）
#define UPLOAD_INTERVAL 10 * 1000 // 数据上传间隔：10秒（转换成毫秒）

// 定义全局变量
uint32_t AdcValue;       // 存储ADC采样值的变量
uint32_t ADTime;         // 记录上一次ADC采样的时间戳
uint32_t uploadTime;     // 记录上一次数据上传的时间戳

extern NB_TaskStatus NB_TaskStat;    // 声明外部变量：NB-IoT任务状态（来自其他文件）
extern ATCMD_index currentATIndex;   // 声明外部变量：当前AT指令执行进度（来自其他文件）

// 传感器任务函数：周期性采集ADC数据并通过NB-IoT上传
void SensorTask(){
    //--------------------------
    // ADC数据采集模块
    //--------------------------
    // 检查是否到达采样时间间隔（5秒）
    if(HAL_GetTick() - ADTime > ADC_INTERVAL) 
    {
        // 启动ADC转换
        HAL_ADC_Start(&hadc);  // hadc是ADC句柄（在别处定义）
        // 等待转换完成，超时时间1ms
        HAL_ADC_PollForConversion(&hadc, 1);

        // 检查转换完成标志位
        if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc), HAL_ADC_STATE_REG_EOC))
        {
            // 获取转换结果（12位分辨率，值范围0-4095）
            AdcValue = HAL_ADC_GetValue(&hadc);
            // 打印调试信息（需实现printf函数）
            printf("ADC= %d\n", AdcValue); 
            // 更新最后一次采样时间
            ADTime = HAL_GetTick();
        }
    }

    //--------------------------
    // 数据上传模块
    //--------------------------
    // 检查是否到达上传间隔（10秒）且当前AT指令正在执行AT_NSOSD
    if(HAL_GetTick() - uploadTime > UPLOAD_INTERVAL && currentATIndex == AT_NSOSD)
    {
        // 触发NB-IoT发送任务
        NB_TaskStat = NB_SEND;  // 设置任务状态为发送模式
        uploadTime = HAL_GetTick(); // 更新最后一次上传时间
        // 注意：原代码此处缺少括号，已修正为 HAL_GetTick()
    }
}