/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,����,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Task_CAN.c                                              
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
#include "Task_CAN.h" 
#include "Analysis.h"
/*-----------------------------------file of end------------------------------*/

/* ====================== CAN_ReceiverTask of begin =========================== */
static TaskHandle_t CAN_ReceiveHandler = NULL;/*CAN���ܱ���������ƾ��*/
QueueHandle_t xCan1RxQueue = NULL;/*CAN���ܱ����������*/
/* ====================== CAN_ReceiverTask of end =========================== */

void CAN_TaskCreate(void)
{
    /*���д���*/
    xCan1RxQueue = xQueueCreate(20,sizeof(CanRxMsg));

    /*���񴴽�*/
    xTaskCreate(CAN1_ReceiveTask,           /* ������  */        
				"CAN_ReceiveTask",         /* ������    */      
				128,       			      /* ����ջ��С*/  
				NULL,                 /* �������  */    
			    4,       			        /* �������ȼ�*/
				&CAN_ReceiveHandler);   /* ������  */
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





