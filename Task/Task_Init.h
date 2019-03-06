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
  |--FileName    : Task_Init.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无                                                       
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

/*FreeRTOS相关头文件*/
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
/*任务函数*/
void TaskStart(void *pvParameters);

/*调用的句柄*/
extern TaskHandle_t StartTaskHandler;  
/* =========================== Start_Task of end =========================== */






#endif	// __TASK_INIT_H
/*-----------------------------------file of end------------------------------*/



           



















