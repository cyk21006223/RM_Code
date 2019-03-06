/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���ޣ�                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : BSP_USART.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
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

/* USART1(DR16)��ʼ��*/
void USART1_QuickInit(uint32_t USART_BaudRate);

/*USART1_DMA��ʼ��*/
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

#define USART2_RX_ADDR						(uint32_t)(&USART2->DR)	//����1���ݼĴ�����ַ
#define USART2_RX_DMA_CHANNEL           	DMA_Channel_4		//DMAͨ����
#define USART2_RX_DMA_STREAM           		DMA1_Stream5		//DMA������

/*USART2���ٳ�ʼ��*/
void USART2_QuickInit(uint32_t USART_BaudRate);

/*USART2ͨ��������*/
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

/*USART6��ʼ��(IMU��ʼ��)*/
void USART6_QuickInit(uint32_t USART_BaudRate);

/*USART6_DMA��ʼ��*/
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize);
/* =========================== USART6 & DMA of end =========================== */

/* =========================== USART_PRINTF of begin =========================== */
/*USARTʹ��printf��scanf�˿�����*/
void USART_setPort(USART_TypeDef* USARTx);

/*�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����*/
int fputc(int ch, FILE *f);

/*�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���*/
int fgetc(FILE *f);

/*ANO����*/

/* =========================== USART_PRINTF of end =========================== */









#endif	// __BSP_USART_H
/*-----------------------------------file of end------------------------------*/


