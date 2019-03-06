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
  |--FileName    : Task_Init.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
  |--Date        : 2019-02-18               
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
#ifndef __TASK_INIT_H 
#define __TASK_INIT_H 

/*FreeRTOS���ͷ�ļ�*/
#include "Task_CAN.h"
#include "Task_USART.h"
#include "Task_Control.h"

#include "Chassis_Control.h"
#include "Aiming_Control.h"

 #include "DR16.h"

#include "BSP_CAN.h"
#include "BSP_LED.h"
#include "BSP_USART.h"
#include "BSP_LASER.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/* =========================== Start_Task of begin =========================== */
/*������*/
void TaskStart(void *pvParameters);

/*���õľ��*/
extern TaskHandle_t StartTaskHandler;  
/* =========================== Start_Task of end =========================== */






#endif	// __TASK_INIT_H
/*-----------------------------------file of end------------------------------*/



           



















