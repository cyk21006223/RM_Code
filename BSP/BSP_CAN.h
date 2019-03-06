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
  |--FileName    : BSP_CAN.h                                                
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
#ifndef __BSP_CAN_H 
#define __BSP_CAN_H 

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "BSP_NVIC.h"

/*CAN1快速初始化*/
void CAN1_QuickInit(void);

/*CANx发送数据函数*/
void CAN_sendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, \
uint8_t data[8]);

/*CAN电流发送函数*/


#endif	// __BSP_CAN_H
/*-----------------------------------file of end------------------------------*/






