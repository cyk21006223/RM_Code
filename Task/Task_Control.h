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
  |--FileName    : Task_Control.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
  |--Date        : 2019-02-20               
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
#ifndef __TASK_CONTROL_H 
#define __TASK_CONTROL_H 

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "Device_Flash.h"
#include "Chassis_Control.h"
#include "Cloud_Control.h"

/*�������񴴽�*/
void Control_TaskCreate(void);

/* =========================== DeviceFlash of begin =========================== */
/*֡��ˢ�¿��ƾ��*/
extern TaskHandle_t Device_FlashHandler;
/*֡��ˢ������*/
void Devices_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */


/* =========================== LED_FLASHING of begin =========================== */
 /*��ˮ�ƿ��ƾ��*/ 
extern TaskHandle_t LED_LightHandler;
/*LEDˢ������*/
void LED_LightTask(void *pvParameters);
/* =========================== LED_FLASHING of end =========================== */


/* =========================== Chassis of begin =========================== */
/*���̿���������*/  
extern TaskHandle_t Chassical_Handler;

/*����������ƺ���*/
void Chassical_Task(void *pvParameters);
/* =========================== Chassis of end =========================== */

/* =========================== Cloud of begin =========================== */
/*��̨����������*/
extern TaskHandle_t Cloud_Handler;  

/*��̨������ƺ���*/
extern void Cloud_Task(void *pvParameters);
/* =========================== Cloud of end =========================== */




#endif	// __TASK_CONTROL_H
/*-----------------------------------file of end------------------------------*/


