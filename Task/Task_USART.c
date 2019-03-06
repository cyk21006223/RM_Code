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
  |--FileName    : Task_USART.c                                              
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
#include "Task_USART.h" 
    
/*-----------------------------------file of end------------------------------*/

/* =========================== USART1_DR16 of begin =========================== */
/*DR16��USART1�����ƾ��*/
static TaskHandle_t USART1_ReceiverHandler = NULL;

/*USART1����*/
QueueHandle_t xUsart1RxQueue = NULL; 

/*USART1������*/
void USART1_ReceiveTask(void *pvParameters);
/* =========================== USART1_DR16 of end =========================== */

/* =========================== USART2 of begin =========================== */
/*Aim(USART2)���ƾ��*/
static TaskHandle_t USART2_ReceiverHandler = NULL;

/*USART2���ƶ���*/
QueueHandle_t xUsart2RxQueue = NULL;

/*USART2������*/
void USART2_ReceiveTask(void *pvParameters);
/* =========================== USART2 of end =========================== */


/* =========================== USART6_IMU of begin =========================== */
/*IMU��USART6�����ƾ��*/
static TaskHandle_t USART6_ReceiverHandler = NULL;

/*USASRT6����*/
QueueHandle_t xUsart6RxQueue = NULL;

/*IMUУ�鳤��*/
extern uint16_t s_U6dataLength;

/*USART6������*/
void USART6_ReceiveTask(void *pvParameters);
/* =========================== USART6_IMU of end =========================== */



void USART_TaskCreate(void)
{ 
  /*DR16���ݴ�����д���*/
  xUsart1RxQueue = xQueueCreate(18u+2,(18u+2)*sizeof(uint8_t));

  xTaskCreate(USART1_ReceiveTask,           /* ������  */        
				      "USART1_ReceiveTask",         /* ������    */      
				      128,       			      /* ����ջ��С*/  
				      NULL,                 /* �������  */    
			        4,       			        /* �������ȼ�*/
				      &USART1_ReceiverHandler);   /* ������  */
  
  /*Aim���ݴ�����д���*/
  xUsart2RxQueue = xQueueCreate(10,(10)*sizeof(uint8_t));

  xTaskCreate(USART2_ReceiveTask,           /* ������  */        
				      "USART2_ReceiveTask",         /* ������    */      
				      128,       			      /* ����ջ��С*/  
				      NULL,                 /* �������  */    
			        4,       			        /* �������ȼ�*/
				      &USART2_ReceiverHandler);   /* ������  */

  /*IMU���ݴ�����д���*/
  xUsart6RxQueue = xQueueCreate(GY_IMU_BUFFSIZE,GY_IMU_BUFFSIZE*sizeof(uint8_t));

  xTaskCreate(USART6_ReceiveTask,           /* ������  */        
				      "USART6_ReceiveTask",         /* ������    */      
				      128,       			      /* ����ջ��С*/  
				      NULL,                 /* �������  */    
			        4,       			        /* �������ȼ�*/
				      &USART6_ReceiverHandler);   /* ������  */
}

void USART1_ReceiveTask(void *pvParameters)
{
  /*DR16���ݴ�����*/
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
  /*Aim���ݴ�����*/
  uint8_t usart2RxBuffer[8];

  /*X��Y�����ݴ���ṹ��*/
	int Aiming_x,Aiming_y;
	
	/*ֹͣ��־λ����ṹ��*/
	int N_state;
  
  while(1)
  {
    /*ֱ�Ӱ����е��ж϶��ƶ������������Խ���ٶ�����*/
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
  /*IMU���ݴ�����*/
  uint8_t usart6RxBuffer[30];
  while(1)
  {
        xQueueReceive(xUsart6RxQueue,&usart6RxBuffer,portMAX_DELAY);
        IMU_getinfo(usart6RxBuffer,s_U6dataLength,&Cloud_IMU);
        GPIO_ToggleBits(GPIOE,GPIO_Pin_11);
  }
}


