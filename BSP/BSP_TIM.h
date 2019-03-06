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
  |--FileName    : BSP_TIM.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
  |--Date        : 2019-02-24               
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
#ifndef __BSP_TIM_H 
#define __BSP_TIM_H 

#include "stm32f4xx.h"
#include "BSP_NVIC.h"
/* =========================== TIM5 of begin =========================== */
#define TIM5_CH1_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define TIM5_CH1_GPIO_PORT          GPIOA
#define TIM5_CH1_Pin          	 	GPIO_Pin_0
#define TIM5_CH1_PINSOURCE			GPIO_PinSource0
#define TIM5_CH1_ENABLE			    1

#define TIM5_CH2_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define TIM5_CH2_GPIO_PORT          GPIOA
#define TIM5_CH2_Pin          	 	GPIO_Pin_1
#define TIM5_CH2_PINSOURCE			GPIO_PinSource1
#define TIM5_CH2_ENABLE			    1

/*TIM5Ħ���ֳ�ʼ��*/
void TIM5_GPIOInit(void);

/*TIM5Ħ����PWM��ʼ��*/
void TIM5_PWMOutput(uint16_t prescaler, uint16_t period, uint16_t Pulse);

/* =========================== TIM5 of end =========================== */


#endif	// __BSP_TIM_H
/*-----------------------------------file of end------------------------------*/


