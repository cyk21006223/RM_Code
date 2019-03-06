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
  |--FileName    : main.c                                              
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
#include "Users.h"
#include "Task_Init.h"
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-18 20:49
  * @brief   初始化主函数
  * @param   void
  * @retval  void
  */
int main(void)
{
	xTaskCreate(TaskStart,           /* 任务函数  */        
			   "TaskStart",         /* 任务名    */      
			   512,       			      /* 任务栈大小*/  
			   NULL,                 /* 任务参数  */    
			   1,       			        /* 任务优先级*/
			   &StartTaskHandler);   /* 任务句柄  */ 	
	
	/* 启动调度，开始执行任务 */
	vTaskStartScheduler();
}



 



 
 
 
