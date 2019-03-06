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
  |--FileName    : Task_USART.h                                                
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
#ifndef __TASK_USART_H 
#define __TASK_USART_H 

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stdio.h"

#include "DR16.h"
#include "IMU.h"
#include "Aiming_Control.h"
/*USART���������ʼ������*/
void USART_TaskCreate(void);

/* =========================== USART1_DR16 of begin =========================== */
/*DR16��USART1�����ƾ��*/
extern TaskHandle_t USART1_ReceiverHandler;

/*USART1����*/
extern QueueHandle_t xUsart1RxQueue;

/*USART1������*/
void USART1_ReceiveTask(void *pvParameters);
/* =========================== USART1_DR16 of end =========================== */

/* =========================== USART2_Aim of begin =========================== */
/*Aim(USART2)���ƾ��*/
extern TaskHandle_t USART2_ReceiverHandler;

/*USART2����*/
extern QueueHandle_t xUsart2RxQueue;

/*USART2������*/
void USART2_ReceiveTask(void *pvParameters);
/* =========================== USART2_Aim of end =========================== */


/* =========================== USART6_IMU of begin =========================== */
/*IMU��USART6�����ƾ��*/
extern TaskHandle_t USART6_ReceiverHandler;

/*USASRT6����*/
extern QueueHandle_t xUsart6RxQueue;

/*IMUУ�鳤��*/
extern uint16_t s_U6dataLength;

/*USASRT6������*/
void USART6_ReceiveTask(void *pvParameters);
/* =========================== USART6_IMU of end =========================== */









#endif	// __TASK_USART_H
/*-----------------------------------file of end------------------------------*/


