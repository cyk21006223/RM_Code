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
  |--FileName    : Task_USART.h                                                
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
#ifndef __TASK_USART_H 
#define __TASK_USART_H 

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stdio.h"

#include "DR16.h"
#include "IMU.h"
#include "Aiming_Control.h"
/*USART总体任务初始化函数*/
void USART_TaskCreate(void);

/* =========================== USART1_DR16 of begin =========================== */
/*DR16（USART1）控制句柄*/
extern TaskHandle_t USART1_ReceiverHandler;

/*USART1队列*/
extern QueueHandle_t xUsart1RxQueue;

/*USART1任务函数*/
void USART1_ReceiveTask(void *pvParameters);
/* =========================== USART1_DR16 of end =========================== */

/* =========================== USART2_Aim of begin =========================== */
/*Aim(USART2)控制句柄*/
extern TaskHandle_t USART2_ReceiverHandler;

/*USART2队列*/
extern QueueHandle_t xUsart2RxQueue;

/*USART2任务函数*/
void USART2_ReceiveTask(void *pvParameters);
/* =========================== USART2_Aim of end =========================== */


/* =========================== USART6_IMU of begin =========================== */
/*IMU（USART6）控制句柄*/
extern TaskHandle_t USART6_ReceiverHandler;

/*USASRT6队列*/
extern QueueHandle_t xUsart6RxQueue;

/*IMU校验长度*/
extern uint16_t s_U6dataLength;

/*USASRT6任务函数*/
void USART6_ReceiveTask(void *pvParameters);
/* =========================== USART6_IMU of end =========================== */









#endif	// __TASK_USART_H
/*-----------------------------------file of end------------------------------*/


