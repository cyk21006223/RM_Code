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
  |--FileName    : main.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ����                                                     
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
#include "Users.h"
#include "Task_Init.h"
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-18 20:49
  * @brief   ��ʼ��������
  * @param   void
  * @retval  void
  */
int main(void)
{
	xTaskCreate(TaskStart,           /* ������  */        
			   "TaskStart",         /* ������    */      
			   512,       			      /* ����ջ��С*/  
			   NULL,                 /* �������  */    
			   1,       			        /* �������ȼ�*/
			   &StartTaskHandler);   /* ������  */ 	
	
	/* �������ȣ���ʼִ������ */
	vTaskStartScheduler();
}



 



 
 
 
