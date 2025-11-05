#ifndef __BSP__OLED_H
#define __BSP__OLED_H
#include "stm32f10x.h"

#define SCL_GPIO_PORT  GPIOA
#define SCL_GPIO_PIN   GPIO_Pin_11
#define SCL_GPIO_CLK   RCC_APB2Periph_GPIOA


#define SDA_GPIO_PORT  GPIOA
#define SDA_GPIO_PIN   GPIO_Pin_12
#define SDA_GPIO_CLK   RCC_APB2Periph_GPIOA


void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif
