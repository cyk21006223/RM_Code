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
  |--FileName    : Aiming_Control.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
  |--Date        : 2019-02-27               
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
#ifndef __AIMING_CONTROL_H 
#define __AIMING_CONTROL_H 

#include "Filter.h"
#include "stm32f4xx.h"
#include "BSP_USART.h"
/*�������ݴ�����*/
extern uint8_t CV_RXBUFF[8];

/*�����ʼ��*/
void Aiming_Init(void);

/*����ģʽ�ж�*/
void Aiming_Process(int Input_x,int Input_y);

#endif	// __AIMING_CONTROL_H
/*-----------------------------------file of end------------------------------*/


