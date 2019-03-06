/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Task_CAN.c                                              
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
#include "Task_CAN.h" 
#include "Analysis.h"
/*-----------------------------------file of end------------------------------*/

/* ====================== CAN_ReceiverTask of begin =========================== */
static TaskHandle_t CAN_ReceiveHandler = NULL;/*CAN接受报文任务控制句柄*/
QueueHandle_t xCan1RxQueue = NULL;/*CAN接受报文任务队列*/
/* ====================== CAN_ReceiverTask of end =========================== */

void CAN_TaskCreate(void)
{
    /*队列创建*/
    xCan1RxQueue = xQueueCreate(20,sizeof(CanRxMsg));

    /*任务创建*/
    xTaskCreate(CAN1_ReceiveTask,           /* 任务函数  */        
				"CAN_ReceiveTask",         /* 任务名    */      
				128,       			      /* 任务栈大小*/  
				NULL,                 /* 任务参数  */    
			    4,       			        /* 任务优先级*/
				&CAN_ReceiveHandler);   /* 任务句柄  */
}


void CAN1_ReceiveTask(void *pvParameters)
{
    CanRxMsg RxMessage;
    while(1)
    {
        xQueueReceive(xCan1RxQueue,&RxMessage,portMAX_DELAY);
        Analysis_getinfo(RxMessage);
        GPIO_ToggleBits(GPIOE,GPIO_Pin_9);
    }
}





