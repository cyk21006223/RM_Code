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
  |--FileName    : Task_USART.c                                              
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
#include "Task_USART.h" 
    
/*-----------------------------------file of end------------------------------*/

/* =========================== USART1_DR16 of begin =========================== */
/*DR16（USART1）控制句柄*/
static TaskHandle_t USART1_ReceiverHandler = NULL;

/*USART1队列*/
QueueHandle_t xUsart1RxQueue = NULL; 

/*USART1任务函数*/
void USART1_ReceiveTask(void *pvParameters);
/* =========================== USART1_DR16 of end =========================== */

/* =========================== USART2 of begin =========================== */
/*Aim(USART2)控制句柄*/
static TaskHandle_t USART2_ReceiverHandler = NULL;

/*USART2控制队列*/
QueueHandle_t xUsart2RxQueue = NULL;

/*USART2任务函数*/
void USART2_ReceiveTask(void *pvParameters);
/* =========================== USART2 of end =========================== */


/* =========================== USART6_IMU of begin =========================== */
/*IMU（USART6）控制句柄*/
static TaskHandle_t USART6_ReceiverHandler = NULL;

/*USASRT6队列*/
QueueHandle_t xUsart6RxQueue = NULL;

/*IMU校验长度*/
extern uint16_t s_U6dataLength;

/*USART6任务函数*/
void USART6_ReceiveTask(void *pvParameters);
/* =========================== USART6_IMU of end =========================== */



void USART_TaskCreate(void)
{ 
  /*DR16数据传输队列创建*/
  xUsart1RxQueue = xQueueCreate(18u+2,(18u+2)*sizeof(uint8_t));

  xTaskCreate(USART1_ReceiveTask,           /* 任务函数  */        
				      "USART1_ReceiveTask",         /* 任务名    */      
				      128,       			      /* 任务栈大小*/  
				      NULL,                 /* 任务参数  */    
			        4,       			        /* 任务优先级*/
				      &USART1_ReceiverHandler);   /* 任务句柄  */
  
  /*Aim数据传输队列创建*/
  xUsart2RxQueue = xQueueCreate(10,(10)*sizeof(uint8_t));

  xTaskCreate(USART2_ReceiveTask,           /* 任务函数  */        
				      "USART2_ReceiveTask",         /* 任务名    */      
				      128,       			      /* 任务栈大小*/  
				      NULL,                 /* 任务参数  */    
			        4,       			        /* 任务优先级*/
				      &USART2_ReceiverHandler);   /* 任务句柄  */

  /*IMU数据传输队列创建*/
  xUsart6RxQueue = xQueueCreate(GY_IMU_BUFFSIZE,GY_IMU_BUFFSIZE*sizeof(uint8_t));

  xTaskCreate(USART6_ReceiveTask,           /* 任务函数  */        
				      "USART6_ReceiveTask",         /* 任务名    */      
				      128,       			      /* 任务栈大小*/  
				      NULL,                 /* 任务参数  */    
			        4,       			        /* 任务优先级*/
				      &USART6_ReceiverHandler);   /* 任务句柄  */
}

void USART1_ReceiveTask(void *pvParameters)
{
  /*DR16数据储存体*/
   uint8_t usart1RxBuffer[20];
   while(1)
   {
        xQueueReceive(xUsart1RxQueue, &usart1RxBuffer, portMAX_DELAY);
        DR16_Process(usart1RxBuffer);
	      GPIO_ToggleBits(GPIOE,GPIO_Pin_10);
        
   }
}

void USART2_ReceiveTask(void *pvParameters)
{
  /*Aim数据储存体*/
  uint8_t usart2RxBuffer[8];

  /*X轴Y轴数据储存结构体*/
	int Aiming_x,Aiming_y;
	
	/*停止标志位储存结构体*/
	int N_state;
  
  while(1)
  {
    /*直接把所有的判断都移动到任务里面以解决速度问题*/
    xQueueReceive(xUsart2RxQueue,&usart2RxBuffer,portMAX_DELAY);
    if(CV_RXBUFF[0] == 'S'||CV_RXBUFF[0] == 'N')
    {
      if(sscanf(usart2RxBuffer, "S%d,%d",&Aiming_x,&Aiming_y) == 2)
      {
        Aiming_Process(Aiming_x,Aiming_y);
        GPIO_ToggleBits(GPIOE,GPIO_Pin_12);
      }
      else if(sscanf(usart2RxBuffer, "N%d",&N_state) == 1)
      {
        if(N_state == 1000000)
        {
          GPIO_ToggleBits(GPIOE,GPIO_Pin_12);
        }
      }
    }  
  }
}

void USART6_ReceiveTask(void *pvParameters)
{
  /*IMU数据储存体*/
  uint8_t usart6RxBuffer[30];
  while(1)
  {
        xQueueReceive(xUsart6RxQueue,&usart6RxBuffer,portMAX_DELAY);
        IMU_getinfo(usart6RxBuffer,s_U6dataLength,&Cloud_IMU);
        GPIO_ToggleBits(GPIOE,GPIO_Pin_11);
  }
}


