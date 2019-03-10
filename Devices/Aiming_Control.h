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


/*�Ӿ���׼�ṹ��*/
typedef struct
{
  int Input_x;
  int Input_y;
	int LPF_x;
	int LPF_y;
  int Output_x;
  int Output_y;
}CV_t;

/*�������ݴ�����*/
extern uint8_t CV_RXBUFF[8];

/*�������ݴ���ṹ��*/
extern CV_t ControlVision;

/*�����ʼ��*/
void Aiming_Init(void);

/*���������ж�*/
void Aiming_Process(int Input_x,int Input_y,CV_t* CV);

#endif	// __AIMING_CONTROL_H
/*-----------------------------------file of end------------------------------*/


