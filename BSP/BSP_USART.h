/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无，                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : BSP_USART.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无                                                       
  |--Date        : 2019-02-21               
  |--Libsupports : 
  |--Description :                                                       
  |--FunctionList                                                       
  |-------1. ....                                                       
  |          <version>:                                                       
  |     <modify staff>:                                                       
  |             <data>:                                                       
  |      <description>:                                                        
  |-------2. ...                                                       
  |-----------------------------declaration of end-----------------------------|
 **/
#ifndef __BSP_USART_H 
#define __BSP_USART_H 

#include "stm32f4xx.h"

#include "BSP_NVIC.h"
#include "stdio.h"
/* =========================== USART1 & DMA of begin =========================== */
#define USART1_TX_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define USART1_TX_GPIO_PORT         GPIOB
#define USART1_TX_Pin          	 	GPIO_Pin_6
#define USART1_TX_PINSOURCE			GPIO_PinSource6

#define USART1_RX_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define USART1_RX_GPIO_PORT         GPIOB
#define USART1_RX_Pin           	GPIO_Pin_7
#define USART1_RX_PINSOURCE			GPIO_PinSource7    

#define USART1_RX_ADDR						(uint32_t)(&USART1->DR)	
#define USART1_RX_DMA_CHANNEL           	DMA_Channel_4		
#define USART1_RX_DMA_STREAM           		DMA2_Stream2		

/* USART1(DR16)初始化*/
void USART1_QuickInit(uint32_t USART_BaudRate);

/*USART1_DMA初始化*/
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);
/* =========================== USART1 & DMA of end =========================== */


/* =========================== USART2 & DMA of begin =========================== */
#define USART2_TX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART2_TX_GPIO_PORT         GPIOD
#define USART2_TX_Pin          	 	GPIO_Pin_5
#define USART2_TX_PINSOURCE			GPIO_PinSource5

#define USART2_RX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART2_RX_GPIO_PORT         GPIOD
#define USART2_RX_Pin           	GPIO_Pin_6
#define USART2_RX_PINSOURCE			GPIO_PinSource6

#define USART2_RX_ADDR						(uint32_t)(&USART2->DR)	//串口1数据寄存器地址
#define USART2_RX_DMA_CHANNEL           	DMA_Channel_4		//DMA通道号
#define USART2_RX_DMA_STREAM           		DMA1_Stream5		//DMA数据流

/*USART2快速初始化*/
void USART2_QuickInit(uint32_t USART_BaudRate);

/*USART2通道和自瞄*/
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize);
/* =========================== USART2 & DMA of end =========================== */


/* =========================== USART3 & DMA of begin =========================== */

/* =========================== USART3 & DMA of end =========================== */


/* =========================== USART4 & DMA of begin =========================== */

/* =========================== USART4 & DMA of end =========================== */


/* =========================== USART6 & DMA of begin =========================== */
#define USART6_TX_GPIO_CLK          RCC_AHB1Periph_GPIOC
#define USART6_TX_GPIO_PORT         GPIOC
#define USART6_TX_Pin          	 	GPIO_Pin_6
#define USART6_TX_PINSOURCE			GPIO_PinSource6

#define USART6_RX_GPIO_CLK          RCC_AHB1Periph_GPIOC
#define USART6_RX_GPIO_PORT         GPIOC
#define USART6_RX_Pin           	GPIO_Pin_7
#define USART6_RX_PINSOURCE			GPIO_PinSource7

#define USART6_RX_ADDR						(uint32_t)(&USART6->DR)	
#define USART6_RX_DMA_CHANNEL           	DMA_Channel_5		
#define USART6_RX_DMA_STREAM           		DMA2_Stream1		

/*USART6初始化(IMU初始化)*/
void USART6_QuickInit(uint32_t USART_BaudRate);

/*USART6_DMA初始化*/
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize);
/* =========================== USART6 & DMA of end =========================== */

/* =========================== USART_PRINTF of begin =========================== */
/*USART使用printf，scanf端口设置*/
void USART_setPort(USART_TypeDef* USARTx);

/*重定向c库函数printf到串口，重定向后可使用printf函数*/
int fputc(int ch, FILE *f);

/*重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数*/
int fgetc(FILE *f);

/*ANO发送*/

/* =========================== USART_PRINTF of end =========================== */









#endif	// __BSP_USART_H
/*-----------------------------------file of end------------------------------*/


