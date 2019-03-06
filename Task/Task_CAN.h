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
  |--FileName    : Task_CAN.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无                                                       
  |--Date        : 2019-02-19               
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
#ifndef __TASK_CAN_H 
#define __TASK_CAN_H 

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*CAN函数总创建*/
void CAN_TaskCreate(void);

/* ====================== CAN_ReceiverTask of begin =========================== */
/*CAN接受报文任务控制句柄*/
extern TaskHandle_t CAN_ReceiveHandler;

/*CAN接受报文任务队列*/
extern QueueHandle_t xCan1RxQueue;

/*任务函数*/
void CAN1_ReceiveTask(void *pvParameters);
/* ====================== CAN_ReceiverTask of end =========================== */




#endif	// __TASK_CAN_H
/*-----------------------------------file of end------------------------------*/


