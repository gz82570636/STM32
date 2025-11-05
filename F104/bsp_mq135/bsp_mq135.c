#include "bsp_mq135.h"
#include "math.h"
__IO uint16_t ADC_ConvertedValue;

/**
 * @brief 空气检测模块的GPIO配置
 * @param 无
 * @retval 无
 */
 
static void MQ135_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 打开 ADC IO 端口时钟
    ADC_GPIO_APBxClock_FUN(ADC_GPIO_CLK, ENABLE);
    // 打开 数字量 IO 端口时钟
    MQ135_GPIO_APBxClock_FUN(MQ135_GPIO_CLK, ENABLE);

    // 配置 AO 模拟量 IO 引脚模式
    // 必须为模拟输入
    GPIO_InitStructure.GPIO_Pin = ADC_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    // 初始化 ADC IO
    GPIO_Init(ADC_PORT, &GPIO_InitStructure);

    // 配置 DO 数字量 IO 引脚模式
    // 浮空输入
    GPIO_InitStructure.GPIO_Pin = MQ135_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    // 初始化 MQ135 IO
    GPIO_Init(MQ135_PORT, &GPIO_InitStructure);
}




static void MQ135_ADC_Mode_Config(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    // 打开ADC时钟
    ADC_APBxClock_FUN(ADC_CLK, ENABLE);

    // ADC模式配置
    // 只使用一个ADC，属于独立模式
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    // 禁止扫描模式，单通道不需要
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    // 连续转换模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    // 不用外部触发转换，软件触发即可
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    // 转换结果右对齐
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    // 转换通道1个
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    // 初始化ADC
    ADC_Init(ADCx, &ADC_InitStructure);

    // 配置ADC时钟为PCLK2的8分频，即9MHz
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    // 配置ADC通道转换顺序和采样时间
    ADC_RegularChannelConfig(ADCx, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);

    // ADC转换结束产生中断，在中断服务程序中读取转换值
    ADC_ITConfig(ADCx, ADC_IT_EOC, ENABLE);

    // 开启ADC，并开始转换
    ADC_Cmd(ADCx, ENABLE);

    // 初始化ADC校准寄存器
    ADC_ResetCalibration(ADCx);
    // 等待校准寄存器初始化完成
    while (ADC_GetResetCalibrationStatus(ADCx));
    // ADC开始校准
    ADC_StartCalibration(ADCx);
    // 等待校准完成
    while (ADC_GetCalibrationStatus(ADCx));
		
		// 由于没有采用外部触发，所以使用软件触发ADC转换
    ADC_SoftwareStartConvCmd(ADCx, ENABLE);
}


/**
 * @brief ADC中断配置
 * @param 无
 * @retval 无
 */
static void MQ135_ADC_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    // 优先分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    // 配置中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief 空气检测模块初始化
 * @param 无
 * @retval 无
 */
void MQ135_Init(void)
{
    MQ135_GPIO_Config();
    MQ135_ADC_Mode_Config();
    MQ135_ADC_NVIC_Config();
}

/**
 * @brief ADC中断函数
 * @param 无
 * @retval 无
 */
void ADC_IRQHandler(void)
{
    if (ADC_GetITStatus(ADCx, ADC_IT_EOC) == SET)
    {
        // 读取ADC的转换值
        ADC_ConvertedValue = ADC_GetConversionValue(ADCx);
    }
    ADC_ClearITPendingBit(ADCx, ADC_IT_EOC);
}

float vrl = 0; /* AO输出的模拟电压 */
float Rs;  /* 当前传感器电阻 */
float ppm = 0; /* 污染物平均浓度 */

/**
 * @brief 求ppm
 * @param 无
 * @retval ppm
 * @note
 * 根据手册提供的各污染气体灵敏度 拟合成幂函数
 * 需要根据Rs/R0推算ppm，所以拟合函数时，x轴为Rs/R0，y轴为ppm，推导出y=ax^b
 * 表格没有每个点对应具体数值只能大致估计，所以测量值存在误差，想要完全精确请根据环境做多次标定
 */
float MQ135_Get_PPM(void)
{
    /* 读取AO输出电压 */
    vrl = (float)ADC_ConvertedValue / 4096 * VC;
    /* 换算Rs电阻 */
    Rs = (float)(VC - vrl) * RL / vrl;

    float Rs0 = Rs / R0; /* Rs/R0 */

    /* y=ax^b x为Rs/R0，ab的取值根据数据手册图表自行拟合成幂函数 */
    ppm = A * pow(Rs/R0,B);

    return ppm;
}