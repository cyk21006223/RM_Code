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
  |--FileName    : Task_CAN.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
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

/*CAN�����ܴ���*/
void CAN_TaskCreate(void);

/* ====================== CAN_ReceiverTask of begin =========================== */
/*CAN���ܱ���������ƾ��*/
extern TaskHandle_t CAN_ReceiveHandler;

/*CAN���ܱ����������*/
extern QueueHandle_t xCan1RxQueue;

/*������*/
void CAN1_ReceiveTask(void *pvParameters);
/* ====================== CAN_ReceiverTask of end =========================== */




#endif	// __TASK_CAN_H
/*-----------------------------------file of end------------------------------*/


