/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */

// ����USART2���ڵ�DMA���ջ�������С����λ���ֽڣ�
// ����ʵ��ͨ���������ã�256�ֽ��ǳ������еȻ�������С
#define USART2_DMA_REC_SIZE 256  

/**
 * USART2����DMAͨ�����ݽṹ��
 * ���ڹ����ڽ���״̬�����ݺͳ�����Ϣ
 */
typedef struct {
    // USART2���ݽ�����ɱ�־λ��1�ֽڣ�
    // 0: δ�յ�������  1: �������ݵ�����ֶ����㣩
    uint8_t Usart2RecFlag;      

    // ��ǰDMA���յ������ݳ��ȣ�2�ֽڣ�
    // ��λ���ֽڣ���Χ��0~USART2_DMA_REC_SIZE
    uint16_t Usart2DMArecLen;   

    // DMA���ջ��������̶�256�ֽ����飩
    // �洢ʵ�ʽ��յ��Ĵ���ԭʼ����
    // ע�⣺���ݿ��ܰ���Э��ͷβ/У��λ�ȣ����������
    uint8_t Usart2DMARecBuff[USART2_DMA_REC_SIZE];  

} Usart2Type;  // �ṹ�����Ͷ������

void EnableIT();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

