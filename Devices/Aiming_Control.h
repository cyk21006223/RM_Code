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
  |--FileName    : Aiming_Control.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无                                                       
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


/*视觉瞄准结构体*/
typedef struct
{
  int Input_x;
  int Input_y;
	int LPF_x;
	int LPF_y;
  int Output_x;
  int Output_y;
}CV_t;

/*自瞄数据储存体*/
extern uint8_t CV_RXBUFF[8];

/*自瞄数据储存结构体*/
extern CV_t ControlVision;

/*自瞄初始化*/
void Aiming_Init(void);

/*自瞄数据判断*/
void Aiming_Process(int Input_x,int Input_y,CV_t* CV);

#endif	// __AIMING_CONTROL_H
/*-----------------------------------file of end------------------------------*/


