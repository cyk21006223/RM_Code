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
  |--FileName    : Task_Control.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无                                                       
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

/*控制任务创建*/
void Control_TaskCreate(void);

/* =========================== DeviceFlash of begin =========================== */
/*帧率刷新控制句柄*/
extern TaskHandle_t Device_FlashHandler;
/*帧率刷新任务*/
void Devices_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */


/* =========================== LED_FLASHING of begin =========================== */
 /*流水灯控制句柄*/ 
extern TaskHandle_t LED_LightHandler;
/*LED刷新任务*/
void LED_LightTask(void *pvParameters);
/* =========================== LED_FLASHING of end =========================== */


/* =========================== Chassis of begin =========================== */
/*底盘控制任务句柄*/  
extern TaskHandle_t Chassical_Handler;

/*底盘任务控制函数*/
void Chassical_Task(void *pvParameters);
/* =========================== Chassis of end =========================== */

/* =========================== Cloud of begin =========================== */
/*云台控制任务句柄*/
extern TaskHandle_t Cloud_Handler;  

/*云台任务控制函数*/
extern void Cloud_Task(void *pvParameters);
/* =========================== Cloud of end =========================== */




#endif	// __TASK_CONTROL_H
/*-----------------------------------file of end------------------------------*/


