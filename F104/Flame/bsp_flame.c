#include "bsp_flame.h"

// 火焰传感器GPIO配置
static void Flame_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 打开 ADC IO端口时钟
    Flame_ADC_GPIO_APBxClock_FUN(Flame_ADC_GPIO_CLK, ENABLE);
    // 打开 数字量IO端口时钟
    Flame_ADC_GPIO_APBxClock_FUN(Flame_GPIO_CLK, ENABLE);

    // 配置 AO 模拟量 IO 引脚模式
    GPIO_InitStructure.GPIO_Pin = Flame_ADC_PIN; // 必须为模拟输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(Flame_ADC_PORT, &GPIO_InitStructure);

    // 配置 DO 数字量 IO 引脚模式
    GPIO_InitStructure.GPIO_Pin = Flame_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(Flame_PORT, &GPIO_InitStructure);
}

static void Flame_ADC_Mode_Config(void)
{
    ADC_InitTypeDef ADC_InitStructure; // 定义一个初始化结构体
    Flame_ADC_APBxClock_FUN(Flame_ADC_CLK, ENABLE); // 打开时钟

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // 只使用一个ADC，属于独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 禁用扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // 连续转换
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 不使用外部触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1; // 转换通道的个数为1个
    ADC_Init(Flame_ADCx, &ADC_InitStructure);

    // 配置ADC时钟为 PCLK2的6分频，即9MHz
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    // 配置 ADC 通道转换顺序和采样时间
    ADC_RegularChannelConfig(Flame_ADCx, Flame_ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);

    // 开启ADC，并开始转换
    ADC_Cmd(Flame_ADCx, ENABLE);

    // 初始化ADC校准寄存器
    ADC_ResetCalibration(Flame_ADCx);
    // 等待校准寄存器初始化完成
    while(ADC_GetResetCalibrationStatus(Flame_ADCx));

    // ADC开始校准
    ADC_StartCalibration(Flame_ADCx);
    // 等待校准完成
    while(ADC_GetCalibrationStatus(Flame_ADCx));

    // 由于没有采用外部触发，所以使用软件触发ADC转换
    ADC_SoftwareStartConvCmd(Flame_ADCx, ENABLE);
}

void Flame_Init(void) // 火焰传感器初始化
{
    Flame_GPIO_Config();
    Flame_ADC_Mode_Config();
}

uint16_t Flame_AD_Value(void)
{
    ADC_RegularChannelConfig(Flame_ADCx, Flame_ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(Flame_ADCx, ENABLE);
    while (ADC_GetFlagStatus(Flame_ADCx, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(Flame_ADCx);
}
